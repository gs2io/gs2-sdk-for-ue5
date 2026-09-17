/*
 * Copyright 2016 Game Server Services, Inc. or its affiliates. All Rights
 * Reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License").
 * You may not use this file except in compliance with the License.
 * A copy of the License is located at
 *
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 * or in the "license" file accompanying this file. This file is distributed
 * on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either
 * express or implied. See the License for the specific language governing
 * permissions and limitations under the License.
 *
 * deny overwrite
 */

#if defined(_MSC_VER)
#pragma warning (push)
#pragma warning (disable: 4458) // Declaration hides class member
#elif defined(__clang__)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wshadow" // declaration shadows a field of
#endif

#include "Money/Domain/SpeculativeExecutor/Consume/WithdrawByUserIdSpeculativeExecutor.h"
#include "Money/Model/Cache/Wallet.h"
#include "Money/Model/WalletDetail.h"

#include "Auth/Model/AccessToken.h"
#include "Core/Domain/Gs2.h"
#include "Core/Domain/SpeculativeExecutor/PreparedSpeculativeCommit.h"
#include "Money/Domain/Gs2Money.h"

namespace Gs2::Money::Domain::SpeculativeExecutor
{

    namespace
    {
        using FWallet = Gs2::Money::Model::FWallet;
        using FWalletPtr = Gs2::Money::Model::FWalletPtr;
        using FWalletDetail = Gs2::Money::Model::FWalletDetail;
        using FWalletDetailPtr = Gs2::Money::Model::FWalletDetailPtr;
        using FWalletCache = Gs2::Money::Model::Cache::FWalletCache;

        static FString WithdrawExpectedWalletId(const Gs2::Core::Domain::FGs2Ptr& Domain, const FString& NamespaceName, const FString& UserId, const TOptional<int32>& Slot)
        {
            return FString::Printf(TEXT("grn:gs2:%s:%s:money:%s:user:%s:wallet:%s"), *Domain->RestSession->RegionName(), *Domain->RestSession->OwnerId(), *NamespaceName, *UserId, *LexToString(Slot.Get(0)));
        }

        static bool WithdrawIsExpected(const FWalletPtr& Item, const FString& ExpectedId, const FString& UserId, const TOptional<int32>& Slot)
        {
            return Item.IsValid() && Item->GetWalletId().IsSet() && *Item->GetWalletId() == ExpectedId && Item->GetUserId().IsSet() && *Item->GetUserId() == UserId && Item->GetSlot() == Slot;
        }

        static FWalletPtr WithdrawCloneWallet(const FWalletPtr& Source)
        {
            if (!Source.IsValid()) return nullptr;
            auto Clone = MakeShared<FWallet>(*Source);
            const auto Existing = Source->GetDetail();
            if (!Existing.IsValid()) return Clone;
            auto Details = MakeShared<TArray<FWalletDetailPtr>>();
            for (const auto& Detail : *Existing) {
                if (Detail.IsValid()) Details->Add(MakeShared<FWalletDetail>(*Detail));
            }
            return Clone->WithDetail(Details);
        }

        static FWalletPtr WithdrawSyncFreeWallet(const FWalletPtr& Item, const FWalletPtr& Source)
        {
            if (!Item.IsValid() || !Source.IsValid()) return nullptr;
            auto Clone = WithdrawCloneWallet(Item);
            if (!Clone.IsValid()) return nullptr;
            auto Details = MakeShared<TArray<FWalletDetailPtr>>();
            if (const auto Existing = Clone->GetDetail()) {
                for (const auto& Detail : *Existing) if (Detail.IsValid()) Details->Add(Detail);
            }
            FWalletDetailPtr FreeDetail;
            for (const auto& Detail : *Details) {
                if (Detail.IsValid() && Detail->GetPrice().IsSet() && *Detail->GetPrice() == 0) {
                    FreeDetail = Detail;
                    break;
                }
            }
            if (!FreeDetail.IsValid()) {
                FreeDetail = MakeShared<FWalletDetail>()->WithPrice(0.0f);
                Details->Add(FreeDetail);
            }
            TOptional<int32> FreeCount;
            if (const auto Existing = Source->GetDetail()) {
                for (const auto& Detail : *Existing) {
                    if (Detail.IsValid() && Detail->GetPrice().IsSet() && *Detail->GetPrice() == 0) {
                        FreeCount = Detail->GetCount();
                        break;
                    }
                }
            }
            if (!FreeCount.IsSet()) FreeCount = Source->GetFree();
            if (!FreeCount.IsSet()) FreeCount = 0;
            FreeDetail->WithCount(FreeCount);
            return Clone->WithFree(Source->GetFree())->WithDetail(Details);
        }

        static FWalletPtr WithdrawSynchronizeSharedFree(const Gs2::Core::Domain::FGs2Ptr& Domain, const FWalletPtr& Item, const FString& NamespaceName, const FString& UserId, const TOptional<int32>& Slot, const TOptional<int32>& TimeOffset, FWalletPtr& SharedWallet, bool& SharedFreeUnavailable)
        {
            SharedWallet = nullptr;
            SharedFreeUnavailable = false;
            if (!Item.IsValid() || !Item->GetShareFree().Get(false) || !Slot.IsSet() || *Slot == 0) return Item;
            FWalletPtr CachedShared;
            if (!FWalletCache::TryGet(Domain->Cache, NamespaceName, UserId, 0, TimeOffset, &CachedShared) || !CachedShared.IsValid()) {
                SharedFreeUnavailable = true;
                return Item;
            }
            SharedWallet = CachedShared;
            return WithdrawSyncFreeWallet(Item, CachedShared);
        }

        static FWalletPtr WithdrawTransformWallet(const FWalletPtr& Source, const Gs2::Money::Request::FWithdrawByUserIdRequestPtr& Request)
        {
            if (!Source.IsValid() || !Request.IsValid() || !Request->GetCount().IsSet()) return nullptr;
            auto Clone = WithdrawCloneWallet(Source);
            if (!Clone.IsValid()) return nullptr;
            if (*Request->GetCount() <= 0) return Clone->WithRevision(0);
            auto Details = MakeShared<TArray<FWalletDetailPtr>>();
            if (const auto Existing = Clone->GetDetail()) {
                for (const auto& Detail : *Existing) if (Detail.IsValid()) Details->Add(Detail);
            }
            int64 Remaining = *Request->GetCount();
            const bool PaidOnly = Request->GetPaidOnly().Get(false);
            while (Remaining > 0) {
                FWalletDetailPtr Target;
                if (!PaidOnly) {
                    for (const auto& Detail : *Details) {
                        if (Detail->GetPrice().IsSet() && *Detail->GetPrice() == 0 && Detail->GetCount().IsSet() && *Detail->GetCount() > 0) {
                            Target = Detail;
                            break;
                        }
                    }
                }
                if (!Target.IsValid()) {
                    float BestPrice = TNumericLimits<float>::Lowest();
                    for (const auto& Detail : *Details) {
                        if (!Detail->GetCount().IsSet() || *Detail->GetCount() <= 0 || (PaidOnly && (!Detail->GetPrice().IsSet() || *Detail->GetPrice() <= 0))) continue;
                        if (!Target.IsValid() || Detail->GetPrice().Get(0.0f) > BestPrice) {
                            Target = Detail;
                            BestPrice = Detail->GetPrice().Get(0.0f);
                        }
                    }
                }
                if (!Target.IsValid()) return nullptr;
                const int64 Consumed = FMath::Min<int64>(*Target->GetCount(), Remaining);
                const int64 NewCount = static_cast<int64>(*Target->GetCount()) - Consumed;
                const int64 NewRemaining = Remaining - Consumed;
                if (NewCount < INT32_MIN || NewCount > INT32_MAX || NewRemaining < INT32_MIN || NewRemaining > INT32_MAX) return nullptr;
                Target->WithCount(static_cast<int32>(NewCount));
                if (Target->GetPrice().IsSet() && *Target->GetPrice() == 0) {
                    if (Clone->GetFree().IsSet()) {
                        const int64 Value = static_cast<int64>(*Clone->GetFree()) - Consumed;
                        if (Value < INT32_MIN || Value > INT32_MAX) return nullptr;
                        Clone->WithFree(static_cast<int32>(Value));
                    }
                } else {
                    if (Clone->GetPaid().IsSet()) {
                        const int64 Value = static_cast<int64>(*Clone->GetPaid()) - Consumed;
                        if (Value < INT32_MIN || Value > INT32_MAX) return nullptr;
                        Clone->WithPaid(static_cast<int32>(Value));
                    }
                }
                Remaining = NewRemaining;
                if (*Target->GetCount() == 0) Details->Remove(Target);
            }
            Details->Sort([](const FWalletDetailPtr& A, const FWalletDetailPtr& B) { return A->GetPrice().Get(0.0f) > B->GetPrice().Get(0.0f); });
            return Clone->WithDetail(Details)->WithRevision(0);
        }
    }

    FString FWithdrawByUserIdSpeculativeExecutor::Action()
    {
        return FString("Gs2Money:WithdrawByUserId");
    }

    Gs2::Core::Model::FGs2ErrorPtr FWithdrawByUserIdSpeculativeExecutor::Transform(
        const Gs2::Core::Domain::FGs2Ptr& Domain,
        const Gs2::Auth::Model::FAccessTokenPtr& AccessToken,
        const Gs2::Money::Request::FWithdrawByUserIdRequestPtr& Request,
        Gs2::Money::Model::FWalletPtr Item
    )
    {
        const auto Changed = WithdrawTransformWallet(Item, Request);
        if (Item.IsValid() && Changed.IsValid()) *Item = *Changed;
        return nullptr;
    }

    FWithdrawByUserIdSpeculativeExecutor::FCommitTask::FCommitTask(
        const Gs2::Core::Domain::FGs2Ptr& Domain,
        const Gs2::Money::Domain::FGs2MoneyDomainPtr& Service,
        const Gs2::Auth::Model::FAccessTokenPtr& AccessToken,
        const Gs2::Money::Request::FWithdrawByUserIdRequestPtr& Request
    ):
        Domain(Domain),
        Service(Service),
        AccessToken(AccessToken),
        Request(Request)
    {

    }

    FWithdrawByUserIdSpeculativeExecutor::FCommitTask::FCommitTask(
        const FCommitTask& From
    ):
        Domain(From.Domain),
        Service(From.Service),
        AccessToken(From.AccessToken),
        Request(From.Request)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FWithdrawByUserIdSpeculativeExecutor::FCommitTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Core::Domain::SpeculativeExecutor::FPreparedSpeculativeCommit>> Result
    )
    {
        *Result = nullptr;
        const auto Prepared = Request.IsValid() ? Gs2::Money::Request::FWithdrawByUserIdRequest::FromJson(Request->ToJson()) : nullptr;
        Gs2::Auth::Model::FAccessTokenPtr PreparedAccessToken;
        if (AccessToken.IsValid()) PreparedAccessToken = MakeShared<Gs2::Auth::Model::FAccessToken>(*AccessToken);
        if (Prepared.IsValid() && Prepared->GetUserId().IsSet() && *Prepared->GetUserId() == TEXT("#{userId}")) Prepared->WithUserId(PreparedAccessToken.IsValid() ? PreparedAccessToken->GetUserId() : TOptional<FString>());
        if (!Domain.IsValid() || !Domain->RestSession.IsValid() || !Prepared.IsValid() || !PreparedAccessToken.IsValid() || !Prepared->GetNamespaceName().IsSet() || Prepared->GetNamespaceName()->IsEmpty() || !PreparedAccessToken->GetUserId().IsSet() || PreparedAccessToken->GetUserId()->IsEmpty() || Prepared->GetUserId() != PreparedAccessToken->GetUserId() || !Prepared->GetSlot().IsSet() || !Prepared->GetCount().IsSet()) return nullptr;
        const auto UserId = *PreparedAccessToken->GetUserId();
        const auto TimeOffset = PreparedAccessToken->GetTimeOffset();
        FWalletPtr PreparedItem;
        const bool Found = FWalletCache::TryGet(Domain->Cache, Prepared->GetNamespaceName(), UserId, Prepared->GetSlot(), TimeOffset, &PreparedItem);
        const auto ExpectedId = WithdrawExpectedWalletId(Domain, *Prepared->GetNamespaceName(), UserId, Prepared->GetSlot());
        if (!Found || !WithdrawIsExpected(PreparedItem, ExpectedId, UserId, Prepared->GetSlot())) return nullptr;
        FWalletPtr PreparedShared;
        bool PreparedSharedUnavailable = false;
        WithdrawSynchronizeSharedFree(Domain, PreparedItem, *Prepared->GetNamespaceName(), UserId, Prepared->GetSlot(), TimeOffset, PreparedShared, PreparedSharedUnavailable);
        if ((PreparedSharedUnavailable && *Prepared->GetCount() > 0 && !Prepared->GetPaidOnly().Get(false)) || (PreparedShared.IsValid() && !WithdrawIsExpected(PreparedShared, WithdrawExpectedWalletId(Domain, *Prepared->GetNamespaceName(), UserId, 0), UserId, 0))) return nullptr;
        *Result = Gs2::Core::Domain::SpeculativeExecutor::FPreparedSpeculativeCommit::WrapLegacy(MakeShared<TFunction<void()>>([DomainCopy = Domain, Prepared, UserId, TimeOffset]()
        {
            FWalletPtr Live;
            if (!FWalletCache::TryGet(DomainCopy->Cache, Prepared->GetNamespaceName(), UserId, Prepared->GetSlot(), TimeOffset, &Live) || !WithdrawIsExpected(Live, WithdrawExpectedWalletId(DomainCopy, *Prepared->GetNamespaceName(), UserId, Prepared->GetSlot()), UserId, Prepared->GetSlot())) return;
            FWalletPtr Shared;
            bool SharedUnavailable = false;
            const auto Source = WithdrawSynchronizeSharedFree(DomainCopy, Live, *Prepared->GetNamespaceName(), UserId, Prepared->GetSlot(), TimeOffset, Shared, SharedUnavailable);
            if ((SharedUnavailable && *Prepared->GetCount() > 0 && !Prepared->GetPaidOnly().Get(false)) || (Shared.IsValid() && !WithdrawIsExpected(Shared, WithdrawExpectedWalletId(DomainCopy, *Prepared->GetNamespaceName(), UserId, 0), UserId, 0)) || !Source.IsValid()) return;
            const auto PreviousFree = Source->GetFree();
            const auto Changed = WithdrawTransformWallet(Source, Prepared);
            if (!Changed.IsValid()) return;
            if (Shared.IsValid() && PreviousFree != Changed->GetFree()) {
                const auto ChangedShared = WithdrawSyncFreeWallet(Shared, Changed);
                if (!ChangedShared.IsValid()) return;
                ChangedShared->WithRevision(0);
                FWalletCache::Put(DomainCopy->Cache, *Prepared->GetNamespaceName(), UserId, 0, TimeOffset, ChangedShared);
            }
            FWalletCache::Put(DomainCopy->Cache, *Prepared->GetNamespaceName(), UserId, Prepared->GetSlot(), TimeOffset, Changed);
        }));
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FWithdrawByUserIdSpeculativeExecutor::FCommitTask>> FWithdrawByUserIdSpeculativeExecutor::Execute(
        const Gs2::Core::Domain::FGs2Ptr& Domain,
        const Gs2::Money::Domain::FGs2MoneyDomainPtr& Service,
        const Gs2::Auth::Model::FAccessTokenPtr& AccessToken,
        const Gs2::Money::Request::FWithdrawByUserIdRequestPtr& Request
    )
    {
        return Gs2::Core::Util::New<FAsyncTask<FCommitTask>>(Domain, Service, AccessToken, Request);
    }

    Gs2::Money::Request::FWithdrawByUserIdRequestPtr FWithdrawByUserIdSpeculativeExecutor::Rate(
        const Gs2::Money::Request::FWithdrawByUserIdRequestPtr& Request,
        const double Rate
    )
    {
        if (Request->GetCount().IsSet())
        {
            Request->WithCount(*Request->GetCount() * Rate);
        }
        return Request;
    }

    Gs2::Money::Request::FWithdrawByUserIdRequestPtr FWithdrawByUserIdSpeculativeExecutor::Rate(
        const Gs2::Money::Request::FWithdrawByUserIdRequestPtr& Request,
        TBigInt<1024, false> Rate
    )
    {
        if (Request->GetCount().IsSet())
        {
            Rate.Multiply(*Request->GetCount());
            Request->WithCount(Rate.ToInt());
        }
        return Request;
    }
}
