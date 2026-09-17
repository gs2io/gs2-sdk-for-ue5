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

#include "Money2/Domain/SpeculativeExecutor/Consume/WithdrawByUserIdSpeculativeExecutor.h"
#include "Money2/Model/Cache/Wallet.h"
#include "Money2/Model/DepositTransaction.h"
#include "Money2/Model/WalletSummary.h"
#include "Money2/Domain/Gs2Money2.h"

#include "Auth/Model/AccessToken.h"
#include "Core/Domain/Gs2.h"
#include "Core/Domain/SpeculativeExecutor/PreparedSpeculativeCommit.h"

namespace Gs2::Money2::Domain::SpeculativeExecutor
{

    namespace
    {
        using FWallet = Gs2::Money2::Model::FWallet;
        using FWalletPtr = Gs2::Money2::Model::FWalletPtr;
        using FDepositTransaction = Gs2::Money2::Model::FDepositTransaction;
        using FDepositTransactionPtr = Gs2::Money2::Model::FDepositTransactionPtr;
        using FWalletSummaryPtr = Gs2::Money2::Model::FWalletSummaryPtr;
        using FWalletCache = Gs2::Money2::Model::Cache::FWalletCache;

        static FString Money2WithdrawExpectedWalletId(const Gs2::Core::Domain::FGs2Ptr& Domain, const FString& NamespaceName, const FString& UserId, const TOptional<int32>& Slot)
        {
            return FString::Printf(TEXT("grn:gs2:%s:%s:money2:%s:user:%s:wallet:%s"), *Domain->RestSession->RegionName(), *Domain->RestSession->OwnerId(), *NamespaceName, *UserId, *LexToString(Slot.Get(0)));
        }

        static bool Money2WithdrawIsExpected(const FWalletPtr& Item, const FString& ExpectedId, const FString& UserId, const TOptional<int32>& Slot)
        {
            return Item.IsValid() && Item->GetWalletId().IsSet() && *Item->GetWalletId() == ExpectedId && Item->GetUserId().IsSet() && *Item->GetUserId() == UserId && Item->GetSlot() == Slot;
        }

        static FWalletSummaryPtr Money2WithdrawCalculateSummary(const TSharedPtr<TArray<FDepositTransactionPtr>>& Transactions)
        {
            int64 Paid = 0;
            int64 Free = 0;
            if (Transactions.IsValid()) {
                for (const auto& Transaction : *Transactions) {
                    if (!Transaction.IsValid() || !Transaction->GetCount().IsSet()) continue;
                    if (Transaction->GetPrice().IsSet() && *Transaction->GetPrice() > 0) Paid += *Transaction->GetCount();
                    else if (Transaction->GetPrice().IsSet() && *Transaction->GetPrice() == 0) Free += *Transaction->GetCount();
                    if (Paid < INT32_MIN || Paid > INT32_MAX || Free < INT32_MIN || Free > INT32_MAX) return nullptr;
                }
            }
            const int64 Total = Paid + Free;
            if (Total < INT32_MIN || Total > INT32_MAX) return nullptr;
            return MakeShared<Gs2::Money2::Model::FWalletSummary>()->WithPaid(static_cast<int32>(Paid))->WithFree(static_cast<int32>(Free))->WithTotal(static_cast<int32>(Total));
        }

        static FWalletPtr Money2WithdrawCloneWallet(const FWalletPtr& Source)
        {
            if (!Source.IsValid()) return nullptr;
            auto Clone = MakeShared<FWallet>(*Source);
            if (const auto Summary = Source->GetSummary()) Clone->WithSummary(MakeShared<Gs2::Money2::Model::FWalletSummary>(*Summary));
            const auto Existing = Source->GetDepositTransactions();
            if (!Existing.IsValid()) return Clone;
            auto Transactions = MakeShared<TArray<FDepositTransactionPtr>>();
            for (const auto& Transaction : *Existing) if (Transaction.IsValid()) Transactions->Add(MakeShared<FDepositTransaction>(*Transaction));
            return Clone->WithDepositTransactions(Transactions);
        }

        static FWalletPtr Money2WithdrawSyncFreeWallet(const FWalletPtr& Item, const FWalletPtr& Source)
        {
            if (!Item.IsValid() || !Source.IsValid()) return nullptr;
            auto Clone = Money2WithdrawCloneWallet(Item);
            if (!Clone.IsValid()) return nullptr;
            auto Transactions = MakeShared<TArray<FDepositTransactionPtr>>();
            if (const auto Existing = Clone->GetDepositTransactions()) {
                for (const auto& Transaction : *Existing) if (Transaction.IsValid() && Transaction->GetPrice().IsSet() && *Transaction->GetPrice() > 0) Transactions->Add(Transaction);
            }
            if (const auto Existing = Source->GetDepositTransactions()) {
                for (const auto& Transaction : *Existing) {
                    if (Transaction.IsValid() && Transaction->GetPrice().IsSet() && *Transaction->GetPrice() == 0) {
                        if (Transaction->GetCount().IsSet() && *Transaction->GetCount() > 0) Transactions->Add(MakeShared<FDepositTransaction>(*Transaction));
                        break;
                    }
                }
            }
            const auto Summary = Money2WithdrawCalculateSummary(Transactions);
            if (!Summary.IsValid()) return nullptr;
            return Clone->WithDepositTransactions(Transactions)->WithSummary(Summary);
        }

        static FWalletPtr Money2WithdrawSynchronizeSharedFree(const Gs2::Core::Domain::FGs2Ptr& Domain, const FWalletPtr& Item, const FString& NamespaceName, const FString& UserId, const TOptional<int32>& Slot, const TOptional<int32>& TimeOffset, FWalletPtr& SharedWallet, bool& SharedFreeUnavailable)
        {
            SharedWallet = nullptr;
            SharedFreeUnavailable = false;
            if (!Item.IsValid() || !Item->GetSharedFreeCurrency().Get(false) || !Slot.IsSet() || *Slot == 0) return Item;
            FWalletPtr CachedShared;
            if (!FWalletCache::TryGet(Domain->Cache, NamespaceName, UserId, 0, TimeOffset, &CachedShared) || !CachedShared.IsValid()) {
                SharedFreeUnavailable = true;
                return Item;
            }
            SharedWallet = CachedShared;
            return Money2WithdrawSyncFreeWallet(Item, CachedShared);
        }

        static FWalletPtr Money2WithdrawTransformWallet(const FWalletPtr& Source, const Gs2::Money2::Request::FWithdrawByUserIdRequestPtr& Request)
        {
            if (!Source.IsValid() || !Request.IsValid() || !Request->GetWithdrawCount().IsSet()) return nullptr;
            auto Clone = Money2WithdrawCloneWallet(Source);
            if (!Clone.IsValid()) return nullptr;
            auto Transactions = MakeShared<TArray<FDepositTransactionPtr>>();
            if (const auto Existing = Clone->GetDepositTransactions()) for (const auto& Transaction : *Existing) if (Transaction.IsValid()) Transactions->Add(Transaction);
            int64 Remaining = *Request->GetWithdrawCount();
            if (!Request->GetPaidOnly().Get(false)) {
                FDepositTransactionPtr Free;
                for (const auto& Transaction : *Transactions) {
                    if (Transaction->GetPrice().IsSet() && *Transaction->GetPrice() == 0) { Free = Transaction; break; }
                }
                if (Free.IsValid()) {
                    const int64 Consumed = FMath::Min<int64>(Free->GetCount().Get(0), Remaining);
                    const int64 NewRemaining = Remaining - Consumed;
                    const int64 FreeCount = static_cast<int64>(Free->GetCount().Get(0)) - Consumed;
                    if (NewRemaining < INT32_MIN || NewRemaining > INT32_MAX || FreeCount < INT32_MIN || FreeCount > INT32_MAX) return nullptr;
                    Remaining = NewRemaining;
                    for (int32 Index = Transactions->Num() - 1; Index >= 0; --Index) if ((*Transactions)[Index]->GetPrice().IsSet() && *(*Transactions)[Index]->GetPrice() == 0) Transactions->RemoveAt(Index);
                    if (FreeCount > 0) {
                        Free->WithCount(static_cast<int32>(FreeCount));
                        Transactions->Add(Free);
                    }
                }
            }
            for (int32 Index = 0; Index < Transactions->Num() && Remaining > 0; ++Index) {
                const auto Transaction = (*Transactions)[Index];
                if (Transaction->GetCount().Get(0) <= 0) continue;
                if (!Transaction->GetPrice().IsSet()) return nullptr;
                if (*Transaction->GetPrice() == 0) continue;
                const int64 Consumed = FMath::Min<int64>(*Transaction->GetCount(), Remaining);
                const int64 NewCount = static_cast<int64>(*Transaction->GetCount()) - Consumed;
                const int64 NewRemaining = Remaining - Consumed;
                if (NewCount < INT32_MIN || NewCount > INT32_MAX || NewRemaining < INT32_MIN || NewRemaining > INT32_MAX) return nullptr;
                const double UnitPrice = *Transaction->GetPrice() / static_cast<double>(*Transaction->GetCount());
                Transaction->WithCount(static_cast<int32>(NewCount))->WithPrice(UnitPrice * static_cast<double>(NewCount));
                Remaining = NewRemaining;
            }
            for (int32 Index = Transactions->Num() - 1; Index >= 0; --Index) if (Transactions->GetData()[Index]->GetCount().Get(0) <= 0) Transactions->RemoveAt(Index);
            if (Remaining > 0) return nullptr;
            const auto Summary = Money2WithdrawCalculateSummary(Transactions);
            if (!Summary.IsValid()) return nullptr;
            return Clone->WithDepositTransactions(Transactions)->WithSummary(Summary)->WithRevision(0);
        }

        static void Money2WithdrawPutWalletRaw(const Gs2::Core::Domain::FGs2Ptr& Domain, const TOptional<FString>& NamespaceName, const TOptional<FString>& UserId, const TOptional<int32>& Slot, const TOptional<int32>& TimeOffset, const FWalletPtr& Item)
        {
            if (!Domain.IsValid() || !Domain->Cache.IsValid() || !UserId.IsSet()) return;
            const auto ParentKey = FWalletCache::CreateCacheParentKey(NamespaceName, UserId, TimeOffset);
            if (Item.IsValid() && Item->GetSharedFreeCurrency().Get(false) && Slot.Get(0) == 0 && Item->GetRevision().Get(0) != 0) {
                Domain->Cache->ClearListCache(FWallet::TypeName, ParentKey);
            }
            Domain->Cache->Put(
                FWallet::TypeName,
                ParentKey,
                FWalletCache::CreateCacheKey(Slot),
                Item,
                FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
            );
        }
    }

    FString FWithdrawByUserIdSpeculativeExecutor::Action()
    {
        return FString("Gs2Money2:WithdrawByUserId");
    }

    Gs2::Core::Model::FGs2ErrorPtr FWithdrawByUserIdSpeculativeExecutor::Transform(
        const Gs2::Core::Domain::FGs2Ptr& Domain,
        const Gs2::Auth::Model::FAccessTokenPtr& AccessToken,
        const Gs2::Money2::Request::FWithdrawByUserIdRequestPtr& Request,
        Gs2::Money2::Model::FWalletPtr Item
    )
    {
        const auto Changed = Money2WithdrawTransformWallet(Item, Request);
        if (Item.IsValid() && Changed.IsValid()) *Item = *Changed;
        return nullptr;
    }

    FWithdrawByUserIdSpeculativeExecutor::FCommitTask::FCommitTask(
        const Gs2::Core::Domain::FGs2Ptr& Domain,
        const Gs2::Money2::Domain::FGs2Money2DomainPtr& Service,
        const Gs2::Auth::Model::FAccessTokenPtr& AccessToken,
        const Gs2::Money2::Request::FWithdrawByUserIdRequestPtr& Request
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
        const auto Prepared = Request.IsValid() ? Gs2::Money2::Request::FWithdrawByUserIdRequest::FromJson(Request->ToJson()) : nullptr;
        Gs2::Auth::Model::FAccessTokenPtr PreparedAccessToken;
        if (AccessToken.IsValid()) PreparedAccessToken = MakeShared<Gs2::Auth::Model::FAccessToken>(*AccessToken);
        if (Prepared.IsValid() && Prepared->GetUserId().IsSet() && *Prepared->GetUserId() == TEXT("#{userId}")) Prepared->WithUserId(PreparedAccessToken.IsValid() ? PreparedAccessToken->GetUserId() : TOptional<FString>());
        if (!Domain.IsValid() || !Domain->RestSession.IsValid() || !Prepared.IsValid() || !PreparedAccessToken.IsValid() || !Prepared->GetNamespaceName().IsSet() || Prepared->GetNamespaceName()->IsEmpty() || !PreparedAccessToken->GetUserId().IsSet() || PreparedAccessToken->GetUserId()->IsEmpty() || Prepared->GetUserId() != PreparedAccessToken->GetUserId() || !Prepared->GetSlot().IsSet() || !Prepared->GetWithdrawCount().IsSet()) return nullptr;
        const auto UserId = *PreparedAccessToken->GetUserId();
        const auto TimeOffset = PreparedAccessToken->GetTimeOffset();
        FWalletPtr PreparedItem;
        const bool Found = FWalletCache::TryGet(Domain->Cache, Prepared->GetNamespaceName(), UserId, Prepared->GetSlot(), TimeOffset, &PreparedItem);
        const auto ExpectedId = Money2WithdrawExpectedWalletId(Domain, *Prepared->GetNamespaceName(), UserId, Prepared->GetSlot());
        if (!Found || !Money2WithdrawIsExpected(PreparedItem, ExpectedId, UserId, Prepared->GetSlot())) return nullptr;
        FWalletPtr PreparedShared;
        bool PreparedSharedUnavailable = false;
        Money2WithdrawSynchronizeSharedFree(Domain, PreparedItem, *Prepared->GetNamespaceName(), UserId, Prepared->GetSlot(), TimeOffset, PreparedShared, PreparedSharedUnavailable);
        if ((PreparedSharedUnavailable && !Prepared->GetPaidOnly().Get(false)) || (PreparedShared.IsValid() && !Money2WithdrawIsExpected(PreparedShared, Money2WithdrawExpectedWalletId(Domain, *Prepared->GetNamespaceName(), UserId, 0), UserId, 0))) return nullptr;
        *Result = Gs2::Core::Domain::SpeculativeExecutor::FPreparedSpeculativeCommit::WrapLegacy(MakeShared<TFunction<void()>>([DomainCopy = Domain, Prepared, UserId, TimeOffset]()
        {
            FWalletPtr Live;
            if (!FWalletCache::TryGet(DomainCopy->Cache, Prepared->GetNamespaceName(), UserId, Prepared->GetSlot(), TimeOffset, &Live) || !Money2WithdrawIsExpected(Live, Money2WithdrawExpectedWalletId(DomainCopy, *Prepared->GetNamespaceName(), UserId, Prepared->GetSlot()), UserId, Prepared->GetSlot())) return;
            FWalletPtr Shared;
            bool SharedUnavailable = false;
            const auto Source = Money2WithdrawSynchronizeSharedFree(DomainCopy, Live, *Prepared->GetNamespaceName(), UserId, Prepared->GetSlot(), TimeOffset, Shared, SharedUnavailable);
            if ((SharedUnavailable && !Prepared->GetPaidOnly().Get(false)) || (Shared.IsValid() && !Money2WithdrawIsExpected(Shared, Money2WithdrawExpectedWalletId(DomainCopy, *Prepared->GetNamespaceName(), UserId, 0), UserId, 0)) || !Source.IsValid()) return;
            const auto PreviousFree = Source->GetSummary().IsValid() ? Source->GetSummary()->GetFree() : TOptional<int32>();
            const auto Changed = Money2WithdrawTransformWallet(Source, Prepared);
            if (!Changed.IsValid()) return;
            if (Shared.IsValid() && PreviousFree != (Changed->GetSummary().IsValid() ? Changed->GetSummary()->GetFree() : TOptional<int32>())) {
                const auto ChangedShared = Money2WithdrawSyncFreeWallet(Shared, Changed);
                if (!ChangedShared.IsValid()) return;
                ChangedShared->WithRevision(0);
                Money2WithdrawPutWalletRaw(DomainCopy, *Prepared->GetNamespaceName(), UserId, 0, TimeOffset, ChangedShared);
            }
            Money2WithdrawPutWalletRaw(DomainCopy, *Prepared->GetNamespaceName(), UserId, Prepared->GetSlot(), TimeOffset, Changed);
        }));
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FWithdrawByUserIdSpeculativeExecutor::FCommitTask>> FWithdrawByUserIdSpeculativeExecutor::Execute(
        const Gs2::Core::Domain::FGs2Ptr& Domain,
        const Gs2::Money2::Domain::FGs2Money2DomainPtr& Service,
        const Gs2::Auth::Model::FAccessTokenPtr& AccessToken,
        const Gs2::Money2::Request::FWithdrawByUserIdRequestPtr& Request
    )
    {
        return Gs2::Core::Util::New<FAsyncTask<FCommitTask>>(Domain, Service, AccessToken, Request);
    }

    Gs2::Money2::Request::FWithdrawByUserIdRequestPtr FWithdrawByUserIdSpeculativeExecutor::Rate(
        const Gs2::Money2::Request::FWithdrawByUserIdRequestPtr& Request,
        const double Rate
    )
    {
        if (Request->GetWithdrawCount().IsSet())
        {
            Request->WithWithdrawCount(*Request->GetWithdrawCount() * Rate);
        }
        return Request;
    }

    Gs2::Money2::Request::FWithdrawByUserIdRequestPtr FWithdrawByUserIdSpeculativeExecutor::Rate(
        const Gs2::Money2::Request::FWithdrawByUserIdRequestPtr& Request,
        TBigInt<1024, false> Rate
    )
    {
        if (Request->GetWithdrawCount().IsSet())
        {
            Rate.Multiply(*Request->GetWithdrawCount());
            Request->WithWithdrawCount(Rate.ToInt());
        }
        return Request;
    }
}
