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

#include "Money/Domain/SpeculativeExecutor/Acquire/DepositByUserIdSpeculativeExecutor.h"
#include "Money/Domain/Gs2Money.h"
#include "Money/Model/Cache/Wallet.h"
#include "Money/Model/WalletDetail.h"

#include "Core/Domain/Gs2.h"
#include "Core/Domain/SpeculativeExecutor/PreparedSpeculativeCommit.h"

namespace Gs2::Money::Domain::SpeculativeExecutor
{

    namespace
    {
        using FWallet = Gs2::Money::Model::FWallet;
        using FWalletPtr = Gs2::Money::Model::FWalletPtr;
        using FWalletDetail = Gs2::Money::Model::FWalletDetail;
        using FWalletDetailPtr = Gs2::Money::Model::FWalletDetailPtr;
        using FWalletCache = Gs2::Money::Model::Cache::FWalletCache;

        static FString ExpectedWalletId(
            const Gs2::Core::Domain::FGs2Ptr& Domain,
            const FString& NamespaceName,
            const FString& UserId,
            const TOptional<int32>& Slot
        )
        {
            return FString::Printf(
                TEXT("grn:gs2:%s:%s:money:%s:user:%s:wallet:%s"),
                *Domain->RestSession->RegionName(),
                *Domain->RestSession->OwnerId(),
                *NamespaceName,
                *UserId,
                *LexToString(Slot.Get(0))
            );
        }

        static bool IsExpected(
            const FWalletPtr& Item,
            const FString& ExpectedId,
            const FString& UserId,
            const TOptional<int32>& Slot
        )
        {
            return Item.IsValid() && Item->GetWalletId().IsSet() &&
                *Item->GetWalletId() == ExpectedId && Item->GetUserId().IsSet() &&
                *Item->GetUserId() == UserId && Item->GetSlot() == Slot;
        }

        static FWalletPtr SyncFreeWallet(
            const FWalletPtr& Item,
            const FWalletPtr& Source
        )
        {
            if (!Item.IsValid() || !Source.IsValid()) return nullptr;
            auto Clone = FWallet::FromJson(Item->ToJson());
            if (!Clone.IsValid()) return nullptr;
            auto Details = MakeShared<TArray<FWalletDetailPtr>>();
            if (const auto Existing = Clone->GetDetail()) {
                for (const auto& Detail : *Existing) {
                    if (Detail.IsValid()) Details->Add(FWalletDetail::FromJson(Detail->ToJson()));
                }
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

        static FWalletPtr SynchronizeSharedFree(
            const Gs2::Core::Domain::FGs2Ptr& Domain,
            const FWalletPtr& Item,
            const FString& NamespaceName,
            const FString& UserId,
            const TOptional<int32>& Slot,
            const TOptional<int32>& TimeOffset,
            FWalletPtr& SharedWallet,
            bool& SharedFreeUnavailable
        )
        {
            SharedWallet = nullptr;
            SharedFreeUnavailable = false;
            if (!Item.IsValid() || !Item->GetShareFree().Get(false) ||
                !Slot.IsSet() || *Slot == 0) return Item;

            FWalletPtr CachedSharedWallet;
            if (!FWalletCache::TryGet(
                    Domain->Cache, NamespaceName, UserId, 0, TimeOffset,
                    &CachedSharedWallet) || !CachedSharedWallet.IsValid()) {
                SharedFreeUnavailable = true;
                return Item;
            }
            SharedWallet = CachedSharedWallet;
            return SyncFreeWallet(Item, CachedSharedWallet);
        }

        static FWalletPtr TransformWallet(
            const FWalletPtr& Source,
            const Gs2::Money::Request::FDepositByUserIdRequestPtr& Request
        )
        {
            if (!Source.IsValid() || !Request.IsValid() ||
                !Request->GetPrice().IsSet() || !Request->GetCount().IsSet()) return nullptr;
            auto Clone = FWallet::FromJson(Source->ToJson());
            if (!Clone.IsValid()) return nullptr;
            const float UnitPrice = FMath::CeilToFloat(
                *Request->GetPrice() * 10000.0f / static_cast<float>(*Request->GetCount())
            ) / 10000.0f;
            auto Details = MakeShared<TArray<FWalletDetailPtr>>();
            if (const auto Existing = Clone->GetDetail()) {
                for (const auto& Detail : *Existing) {
                    if (Detail.IsValid()) Details->Add(FWalletDetail::FromJson(Detail->ToJson()));
                }
            }
            FWalletDetailPtr Target;
            for (const auto& Detail : *Details) {
                if (Detail.IsValid() && Detail->GetPrice().IsSet() && *Detail->GetPrice() == UnitPrice) {
                    Target = Detail;
                    break;
                }
            }
            if (!Target.IsValid()) {
                Target = MakeShared<FWalletDetail>()->WithPrice(UnitPrice)->WithCount(0);
                Details->Add(Target);
            }
            const int64 Count = *Request->GetCount();
            if (Target->GetCount().IsSet()) {
                const int64 Value = static_cast<int64>(*Target->GetCount()) + Count;
                if (Value < INT32_MIN || Value > INT32_MAX) return nullptr;
                Target->WithCount(static_cast<int32>(Value));
            }
            const bool Paid = *Request->GetPrice() > 0;
            const auto Previous = Paid ? Clone->GetPaid() : Clone->GetFree();
            if (Previous.IsSet()) {
                const int64 Value = static_cast<int64>(*Previous) + Count;
                if (Value < INT32_MIN || Value > INT32_MAX) return nullptr;
                if (Paid) Clone->WithPaid(static_cast<int32>(Value));
                else Clone->WithFree(static_cast<int32>(Value));
            }
            Clone->WithDetail(Details)->WithRevision(0);
            return Clone;
        }
    }

    FString FDepositByUserIdSpeculativeExecutor::Action()
    {
        return FString("Gs2Money:DepositByUserId");
    }

    Gs2::Core::Model::FGs2ErrorPtr FDepositByUserIdSpeculativeExecutor::Transform(
        const Gs2::Core::Domain::FGs2Ptr& Domain,
        const Gs2::Auth::Model::FAccessTokenPtr& AccessToken,
        const Gs2::Money::Request::FDepositByUserIdRequestPtr& Request,
        Gs2::Money::Model::FWalletPtr Item
    )
    {
        const auto Changed = TransformWallet(Item, Request);
        if (Item.IsValid() && Changed.IsValid()) *Item = *Changed;
        return nullptr;
    }

    FDepositByUserIdSpeculativeExecutor::FCommitTask::FCommitTask(
        const Gs2::Core::Domain::FGs2Ptr& Domain,
        const Gs2::Money::Domain::FGs2MoneyDomainPtr& Service,
        const Gs2::Auth::Model::FAccessTokenPtr& AccessToken,
        const Gs2::Money::Request::FDepositByUserIdRequestPtr& Request
    ):
        Domain(Domain),
        Service(Service),
        AccessToken(AccessToken),
        Request(Request)
    {

    }

    FDepositByUserIdSpeculativeExecutor::FCommitTask::FCommitTask(
        const FCommitTask& From
    ):
        Domain(From.Domain),
        Service(From.Service),
        AccessToken(From.AccessToken),
        Request(From.Request)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FDepositByUserIdSpeculativeExecutor::FCommitTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Core::Domain::SpeculativeExecutor::FPreparedSpeculativeCommit>> Result
    )
    {
        *Result = nullptr;
        const auto Prepared = Request.IsValid() ? Gs2::Money::Request::FDepositByUserIdRequest::FromJson(Request->ToJson()) : nullptr;
        Gs2::Auth::Model::FAccessTokenPtr PreparedAccessToken;
        if (AccessToken.IsValid()) PreparedAccessToken = MakeShared<Gs2::Auth::Model::FAccessToken>(*AccessToken);
        if (Prepared.IsValid() && Prepared->GetUserId().IsSet() && *Prepared->GetUserId() == TEXT("#{userId}"))
            Prepared->WithUserId(PreparedAccessToken.IsValid() ? PreparedAccessToken->GetUserId() : TOptional<FString>());
        if (!Domain.IsValid() || !Domain->RestSession.IsValid() || !Prepared.IsValid() ||
            !PreparedAccessToken.IsValid() || !Prepared->GetNamespaceName().IsSet() ||
            !PreparedAccessToken->GetUserId().IsSet() || Prepared->GetUserId() != PreparedAccessToken->GetUserId() ||
            !Prepared->GetSlot().IsSet() || !Prepared->GetPrice().IsSet() || !Prepared->GetCount().IsSet()) return nullptr;
        const auto UserId = *PreparedAccessToken->GetUserId();
        const auto TimeOffset = PreparedAccessToken->GetTimeOffset();
        FWalletPtr PreparedItem;
        const bool Found = FWalletCache::TryGet(Domain->Cache, Prepared->GetNamespaceName(), UserId, Prepared->GetSlot(), TimeOffset, &PreparedItem);
        const auto ExpectedId = ExpectedWalletId(Domain, *Prepared->GetNamespaceName(), UserId, Prepared->GetSlot());
        if (!Found || !IsExpected(PreparedItem, ExpectedId, UserId, Prepared->GetSlot())) return nullptr;
        FWalletPtr PreparedShared;
        bool PreparedSharedUnavailable = false;
        SynchronizeSharedFree(Domain, PreparedItem, *Prepared->GetNamespaceName(), UserId, Prepared->GetSlot(), TimeOffset, PreparedShared, PreparedSharedUnavailable);
        if ((PreparedSharedUnavailable && !(*Prepared->GetPrice() > 0)) ||
            (PreparedShared.IsValid() && !IsExpected(PreparedShared, ExpectedWalletId(Domain, *Prepared->GetNamespaceName(), UserId, 0), UserId, 0))) return nullptr;
        *Result = Gs2::Core::Domain::SpeculativeExecutor::FPreparedSpeculativeCommit::WrapLegacy(MakeShared<TFunction<void()>>([DomainCopy = Domain, Prepared, UserId, TimeOffset]()
        {
            FWalletPtr Live;
            if (!FWalletCache::TryGet(DomainCopy->Cache, Prepared->GetNamespaceName(), UserId, Prepared->GetSlot(), TimeOffset, &Live)) return;
            const auto ExpectedId = ExpectedWalletId(DomainCopy, *Prepared->GetNamespaceName(), UserId, Prepared->GetSlot());
            if (!IsExpected(Live, ExpectedId, UserId, Prepared->GetSlot())) return;
            FWalletPtr Shared;
            bool SharedUnavailable = false;
            const auto Source = SynchronizeSharedFree(DomainCopy, Live, *Prepared->GetNamespaceName(), UserId, Prepared->GetSlot(), TimeOffset, Shared, SharedUnavailable);
            if ((SharedUnavailable && !(*Prepared->GetPrice() > 0)) || (Shared.IsValid() && !IsExpected(Shared, ExpectedWalletId(DomainCopy, *Prepared->GetNamespaceName(), UserId, 0), UserId, 0))) return;
            const auto PreviousFree = Source.IsValid() ? Source->GetFree() : TOptional<int32>();
            const auto Changed = TransformWallet(Source, Prepared);
            if (!Changed.IsValid()) return;
            if (Shared.IsValid() && PreviousFree != Changed->GetFree()) {
                auto ChangedShared = SyncFreeWallet(Shared, Changed);
                if (!ChangedShared.IsValid()) return;
                ChangedShared->WithRevision(0);
                FWalletCache::Put(DomainCopy->Cache, *Prepared->GetNamespaceName(), UserId, 0, TimeOffset, ChangedShared);
            }
            FWalletCache::Put(DomainCopy->Cache, *Prepared->GetNamespaceName(), UserId, Prepared->GetSlot(), TimeOffset, Changed);
        }));
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FDepositByUserIdSpeculativeExecutor::FCommitTask>> FDepositByUserIdSpeculativeExecutor::Execute(
        const Gs2::Core::Domain::FGs2Ptr& Domain,
        const Gs2::Money::Domain::FGs2MoneyDomainPtr& Service,
        const Gs2::Auth::Model::FAccessTokenPtr& AccessToken,
        const Gs2::Money::Request::FDepositByUserIdRequestPtr& Request
    )
    {
        return Gs2::Core::Util::New<FAsyncTask<FCommitTask>>(Domain, Service, AccessToken, Request);
    }

    Gs2::Money::Request::FDepositByUserIdRequestPtr FDepositByUserIdSpeculativeExecutor::Rate(
        const Gs2::Money::Request::FDepositByUserIdRequestPtr& Request,
        const double Rate
    )
    {
        if (Request->GetCount().IsSet())
        {
            Request->WithCount(*Request->GetCount() * Rate);
        }
        return Request;
    }

    Gs2::Money::Request::FDepositByUserIdRequestPtr FDepositByUserIdSpeculativeExecutor::Rate(
        const Gs2::Money::Request::FDepositByUserIdRequestPtr& Request,
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
