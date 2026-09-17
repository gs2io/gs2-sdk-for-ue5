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

#include "Money2/Domain/SpeculativeExecutor/Acquire/DepositByUserIdSpeculativeExecutor.h"
#include "Money2/Model/Cache/Wallet.h"
#include "Money2/Model/DepositTransaction.h"
#include "Money2/Model/WalletSummary.h"

#include "Core/Domain/Gs2.h"
#include "Core/Domain/SpeculativeExecutor/PreparedSpeculativeCommit.h"
#include "Money2/Domain/Gs2Money2.h"

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

        static FString ExpectedWalletId(
            const Gs2::Core::Domain::FGs2Ptr& Domain,
            const FString& NamespaceName,
            const FString& UserId,
            const TOptional<int32>& Slot
        )
        {
            return FString::Printf(
                TEXT("grn:gs2:%s:%s:money2:%s:user:%s:wallet:%s"),
                *Domain->RestSession->RegionName(), *Domain->RestSession->OwnerId(),
                *NamespaceName, *UserId, *LexToString(Slot.Get(0))
            );
        }

        static bool IsExpected(
            const FWalletPtr& Item,
            const FString& ExpectedId,
            const FString& UserId,
            const TOptional<int32>& Slot
        )
        {
            return Item.IsValid() && Item->GetWalletId().IsSet() && *Item->GetWalletId() == ExpectedId &&
                Item->GetUserId().IsSet() && *Item->GetUserId() == UserId && Item->GetSlot() == Slot;
        }

        static FWalletSummaryPtr CalculateSummary(
            const TSharedPtr<TArray<FDepositTransactionPtr>>& Transactions
        )
        {
            int64 Paid = 0;
            int64 Free = 0;
            if (Transactions.IsValid()) {
                for (const auto& Transaction : *Transactions) {
                    if (!Transaction.IsValid() || !Transaction->GetCount().IsSet()) continue;
                    if (Transaction->GetPrice().IsSet() && *Transaction->GetPrice() > 0) Paid += *Transaction->GetCount();
                    else if (Transaction->GetPrice().IsSet() && *Transaction->GetPrice() == 0) Free += *Transaction->GetCount();
                    if (Paid > INT32_MAX || Free > INT32_MAX || Paid < INT32_MIN || Free < INT32_MIN) return nullptr;
                }
            }
            const int64 Total = Paid + Free;
            if (Total > INT32_MAX || Total < INT32_MIN) return nullptr;
            return MakeShared<Gs2::Money2::Model::FWalletSummary>()
                ->WithPaid(static_cast<int32>(Paid))
                ->WithFree(static_cast<int32>(Free))
                ->WithTotal(static_cast<int32>(Total));
        }

        static FWalletPtr CloneWallet(const FWalletPtr& Source)
        {
            if (!Source.IsValid()) return nullptr;
            auto Clone = MakeShared<FWallet>(*Source);
            if (const auto Summary = Source->GetSummary()) Clone->WithSummary(MakeShared<Gs2::Money2::Model::FWalletSummary>(*Summary));
            const auto Existing = Source->GetDepositTransactions();
            if (!Existing.IsValid()) return Clone;
            auto Transactions = MakeShared<TArray<FDepositTransactionPtr>>();
            for (const auto& Transaction : *Existing) {
                if (Transaction.IsValid()) Transactions->Add(MakeShared<FDepositTransaction>(*Transaction));
            }
            return Clone->WithDepositTransactions(Transactions);
        }

        static FWalletPtr SyncFreeWallet(const FWalletPtr& Item, const FWalletPtr& Source)
        {
            if (!Item.IsValid() || !Source.IsValid()) return nullptr;
            auto Clone = CloneWallet(Item);
            if (!Clone.IsValid()) return nullptr;
            auto Transactions = MakeShared<TArray<FDepositTransactionPtr>>();
            if (const auto Existing = Clone->GetDepositTransactions()) {
                for (const auto& Transaction : *Existing) {
                    if (Transaction.IsValid() && Transaction->GetPrice().IsSet() && *Transaction->GetPrice() > 0)
                    {
                        Transactions->Add(Transaction);
                    }
                }
            }
            if (const auto Existing = Source->GetDepositTransactions()) {
                for (const auto& Transaction : *Existing) {
                    if (Transaction.IsValid() && Transaction->GetPrice().IsSet() && *Transaction->GetPrice() == 0)
                    {
                        if (Transaction->GetCount().IsSet() && *Transaction->GetCount() > 0) Transactions->Add(MakeShared<FDepositTransaction>(*Transaction));
                        break;
                    }
                }
            }
            const auto Summary = CalculateSummary(Transactions);
            if (!Summary.IsValid()) return nullptr;
            return Clone->WithDepositTransactions(Transactions)->WithSummary(Summary);
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
            if (!Item.IsValid() || !Item->GetSharedFreeCurrency().Get(false) || !Slot.IsSet() || *Slot == 0) return Item;
            FWalletPtr CachedShared;
            if (!FWalletCache::TryGet(Domain->Cache, NamespaceName, UserId, 0, TimeOffset, &CachedShared) || !CachedShared.IsValid()) {
                SharedFreeUnavailable = true;
                return Item;
            }
            SharedWallet = CachedShared;
            return SyncFreeWallet(Item, CachedShared);
        }

        static Gs2::Money2::Request::FDepositByUserIdRequestPtr CloneRequest(
            const Gs2::Money2::Request::FDepositByUserIdRequestPtr& Request
        )
        {
            if (!Request.IsValid()) return nullptr;
            auto Clone = MakeShared<Gs2::Money2::Request::FDepositByUserIdRequest>()
                ->WithContextStack(Request->GetContextStack())
                ->WithNamespaceName(Request->GetNamespaceName())
                ->WithUserId(Request->GetUserId())
                ->WithSlot(Request->GetSlot())
                ->WithTimeOffsetToken(Request->GetTimeOffsetToken())
                ->WithDuplicationAvoider(Request->GetDuplicationAvoider());
            const auto Existing = Request->GetDepositTransactions();
            if (!Existing.IsValid()) return Clone;
            auto Transactions = MakeShared<TArray<FDepositTransactionPtr>>();
            for (const auto& Transaction : *Existing) {
                if (Transaction.IsValid()) {
                    Transactions->Add(MakeShared<FDepositTransaction>(*Transaction));
                }
            }
            return Clone->WithDepositTransactions(Transactions);
        }

        static Gs2::Money2::Request::FDepositByUserIdRequestPtr SpeculativeRequest(
            const Gs2::Money2::Request::FDepositByUserIdRequestPtr& Request,
            bool SharedFreeUnavailable
        )
        {
            if (!SharedFreeUnavailable) return Request;
            auto Paid = MakeShared<TArray<FDepositTransactionPtr>>();
            if (Request.IsValid() && Request->GetDepositTransactions().IsValid()) {
                for (const auto& Transaction : *Request->GetDepositTransactions()) {
                    if (Transaction.IsValid() && Transaction->GetPrice().IsSet() && *Transaction->GetPrice() > 0)
                        Paid->Add(Transaction);
                }
            }
            if (Paid->Num() == 0) return nullptr;
            const auto Clone = CloneRequest(Request);
            return Clone.IsValid() ? Clone->WithDepositTransactions(Paid) : nullptr;
        }

        static FWalletPtr TransformWallet(
            const FWalletPtr& Source,
            const Gs2::Money2::Request::FDepositByUserIdRequestPtr& Request
        )
        {
            if (!Source.IsValid() || !Request.IsValid() || !Request->GetDepositTransactions().IsValid()) return nullptr;
            auto Clone = CloneWallet(Source);
            if (!Clone.IsValid()) return nullptr;
            auto Transactions = MakeShared<TArray<FDepositTransactionPtr>>();
            if (const auto Existing = Clone->GetDepositTransactions()) {
                for (const auto& Transaction : *Existing) {
                    if (Transaction.IsValid()) Transactions->Add(Transaction);
                }
            }
            for (const auto& Deposit : *Request->GetDepositTransactions()) {
                if (!Deposit.IsValid()) continue;
                if (Deposit->GetPrice().IsSet() && *Deposit->GetPrice() == 0) {
                    TOptional<int32> FreeCount;
                    TOptional<int64> FreeDepositedAt;
                    for (const auto& Existing : *Transactions) {
                        if (Existing.IsValid() && Existing->GetPrice().IsSet() && *Existing->GetPrice() == 0) {
                            FreeCount = Existing->GetCount();
                            FreeDepositedAt = Existing->GetDepositedAt();
                            break;
                        }
                    }
                    for (int32 Index = Transactions->Num() - 1; Index >= 0; --Index) {
                        if ((*Transactions)[Index].IsValid() && (*Transactions)[Index]->GetPrice().IsSet() && *(*Transactions)[Index]->GetPrice() == 0) Transactions->RemoveAt(Index);
                    }
                    if (Deposit->GetCount().IsSet()) {
                        const int64 Value = static_cast<int64>(FreeCount.Get(0)) + *Deposit->GetCount();
                        if (Value > INT32_MAX || Value < INT32_MIN) return nullptr;
                        if (Value > 0) {
                        Transactions->Add(MakeShared<FDepositTransaction>()
                            ->WithPrice(0.0)
                            ->WithCurrency(TOptional<FString>())
                            ->WithCount(static_cast<int32>(Value))
                            ->WithDepositedAt(Deposit->GetDepositedAt().IsSet() ? Deposit->GetDepositedAt() : FreeDepositedAt));
                        }
                    }
                } else {
                    Transactions->Add(MakeShared<FDepositTransaction>(*Deposit));
                }
            }
            const auto Summary = CalculateSummary(Transactions);
            if (!Summary.IsValid()) return nullptr;
            return Clone->WithDepositTransactions(Transactions)->WithSummary(Summary)->WithRevision(0);
        }
    }

    FString FDepositByUserIdSpeculativeExecutor::Action()
    {
        return FString("Gs2Money2:DepositByUserId");
    }

    Gs2::Core::Model::FGs2ErrorPtr FDepositByUserIdSpeculativeExecutor::Transform(
        const Gs2::Core::Domain::FGs2Ptr& Domain,
        const Gs2::Auth::Model::FAccessTokenPtr& AccessToken,
        const Gs2::Money2::Request::FDepositByUserIdRequestPtr& Request,
        Gs2::Money2::Model::FWalletPtr Item
    )
    {
        const auto Changed = TransformWallet(Item, Request);
        if (Item.IsValid() && Changed.IsValid()) *Item = *Changed;
        return nullptr;
    }

    FDepositByUserIdSpeculativeExecutor::FCommitTask::FCommitTask(
        const Gs2::Core::Domain::FGs2Ptr& Domain,
        const Gs2::Money2::Domain::FGs2Money2DomainPtr& Service,
        const Gs2::Auth::Model::FAccessTokenPtr& AccessToken,
        const Gs2::Money2::Request::FDepositByUserIdRequestPtr& Request
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
        const auto Prepared = CloneRequest(Request);
        Gs2::Auth::Model::FAccessTokenPtr PreparedAccessToken;
        if (AccessToken.IsValid()) PreparedAccessToken = MakeShared<Gs2::Auth::Model::FAccessToken>(*AccessToken);
        if (Prepared.IsValid() && Prepared->GetUserId().IsSet() && *Prepared->GetUserId() == TEXT("#{userId}")) Prepared->WithUserId(PreparedAccessToken.IsValid() ? PreparedAccessToken->GetUserId() : TOptional<FString>());
        if (!Domain.IsValid() || !Domain->RestSession.IsValid() || !Prepared.IsValid() || !PreparedAccessToken.IsValid() ||
            !Prepared->GetNamespaceName().IsSet() || !PreparedAccessToken->GetUserId().IsSet() || Prepared->GetUserId() != PreparedAccessToken->GetUserId() ||
            !Prepared->GetSlot().IsSet() || !Prepared->GetDepositTransactions().IsValid()) return nullptr;
        const auto UserId = *PreparedAccessToken->GetUserId();
        const auto TimeOffset = PreparedAccessToken->GetTimeOffset();
        FWalletPtr PreparedItem;
        const bool Found = FWalletCache::TryGet(Domain->Cache, Prepared->GetNamespaceName(), UserId, Prepared->GetSlot(), TimeOffset, &PreparedItem);
        const auto ExpectedId = ExpectedWalletId(Domain, *Prepared->GetNamespaceName(), UserId, Prepared->GetSlot());
        if (!Found || !IsExpected(PreparedItem, ExpectedId, UserId, Prepared->GetSlot())) return nullptr;
        FWalletPtr PreparedShared;
        bool PreparedSharedUnavailable = false;
        SynchronizeSharedFree(Domain, PreparedItem, *Prepared->GetNamespaceName(), UserId, Prepared->GetSlot(), TimeOffset, PreparedShared, PreparedSharedUnavailable);
        if (!SpeculativeRequest(Prepared, PreparedSharedUnavailable).IsValid() || (PreparedShared.IsValid() && !IsExpected(PreparedShared, ExpectedWalletId(Domain, *Prepared->GetNamespaceName(), UserId, 0), UserId, 0))) return nullptr;
        *Result = Gs2::Core::Domain::SpeculativeExecutor::FPreparedSpeculativeCommit::WrapLegacy(MakeShared<TFunction<void()>>([DomainCopy = Domain, Prepared, UserId, TimeOffset]()
        {
            FWalletPtr Live;
            if (!FWalletCache::TryGet(DomainCopy->Cache, Prepared->GetNamespaceName(), UserId, Prepared->GetSlot(), TimeOffset, &Live)) return;
            if (!IsExpected(Live, ExpectedWalletId(DomainCopy, *Prepared->GetNamespaceName(), UserId, Prepared->GetSlot()), UserId, Prepared->GetSlot())) return;
            FWalletPtr Shared;
            bool SharedUnavailable = false;
            const auto Source = SynchronizeSharedFree(DomainCopy, Live, *Prepared->GetNamespaceName(), UserId, Prepared->GetSlot(), TimeOffset, Shared, SharedUnavailable);
            const auto RequestToApply = SpeculativeRequest(Prepared, SharedUnavailable);
            if (!RequestToApply.IsValid() || (Shared.IsValid() && !IsExpected(Shared, ExpectedWalletId(DomainCopy, *Prepared->GetNamespaceName(), UserId, 0), UserId, 0))) return;
            const auto PreviousFree = Source.IsValid() && Source->GetSummary().IsValid() ? Source->GetSummary()->GetFree() : TOptional<int32>();
            const auto Changed = TransformWallet(Source, RequestToApply);
            if (!Changed.IsValid()) return;
            if (Shared.IsValid() && PreviousFree != (Changed->GetSummary().IsValid() ? Changed->GetSummary()->GetFree() : TOptional<int32>())) {
                const auto ChangedShared = SyncFreeWallet(Shared, Changed);
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
        const Gs2::Money2::Domain::FGs2Money2DomainPtr& Service,
        const Gs2::Auth::Model::FAccessTokenPtr& AccessToken,
        const Gs2::Money2::Request::FDepositByUserIdRequestPtr& Request
    )
    {
        return Gs2::Core::Util::New<FAsyncTask<FCommitTask>>(Domain, Service, AccessToken, Request);
    }

    Gs2::Money2::Request::FDepositByUserIdRequestPtr FDepositByUserIdSpeculativeExecutor::Rate(
        const Gs2::Money2::Request::FDepositByUserIdRequestPtr& Request,
        const double Rate
    )
    {
        return Request;
    }

    Gs2::Money2::Request::FDepositByUserIdRequestPtr FDepositByUserIdSpeculativeExecutor::Rate(
        const Gs2::Money2::Request::FDepositByUserIdRequestPtr& Request,
        TBigInt<1024, false> Rate
    )
    {
        return Request;
    }
}
