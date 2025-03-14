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
 */

// ReSharper disable CppUnusedIncludeDirective

#pragma once

#include "Core/Domain/Gs2Core.h"
#include "Auth/Gs2Auth.h"
#include "Money2/Gs2Money2.h"
#include "Money2/Domain/Iterator/DescribeNamespacesIterator.h"
#include "Money2/Domain/Iterator/DescribeWalletsIterator.h"
#include "Money2/Domain/Iterator/DescribeWalletsByUserIdIterator.h"
#include "Money2/Domain/Iterator/DescribeEventsByUserIdIterator.h"
#include "Money2/Domain/Iterator/DescribeSubscriptionStatusesIterator.h"
#include "Money2/Domain/Iterator/DescribeSubscriptionStatusesByUserIdIterator.h"
#include "Money2/Domain/Iterator/DescribeRefundHistoriesByUserIdIterator.h"
#include "Money2/Domain/Iterator/DescribeRefundHistoriesByDateIterator.h"
#include "Money2/Domain/Iterator/DescribeStoreContentModelsIterator.h"
#include "Money2/Domain/Iterator/DescribeStoreContentModelMastersIterator.h"
#include "Money2/Domain/Iterator/DescribeStoreSubscriptionContentModelsIterator.h"
#include "Money2/Domain/Iterator/DescribeStoreSubscriptionContentModelMastersIterator.h"
#include "Money2/Domain/Iterator/DescribeDailyTransactionHistoriesByCurrencyIterator.h"
#include "Money2/Domain/Iterator/DescribeDailyTransactionHistoriesIterator.h"
#include "Money2/Domain/Iterator/DescribeUnusedBalancesIterator.h"

namespace Gs2::Core::Domain
{
    class FGs2;
    typedef TSharedPtr<FGs2> FGs2Ptr;
}

namespace Gs2::Money2::Domain
{
    class FGs2Money2Domain;
    typedef TSharedPtr<FGs2Money2Domain> FGs2Money2DomainPtr;
}

namespace Gs2::Money2::Domain::Model
{
    class FNamespaceDomain;
    class FUserDomain;
    class FUserAccessTokenDomain;
    class FWalletDomain;
    class FWalletAccessTokenDomain;
    class FEventDomain;
    class FEventAccessTokenDomain;
    class FSubscriptionStatusDomain;
    class FSubscriptionStatusAccessTokenDomain;
    class FRefundHistoryDomain;
    class FStoreContentModelDomain;
    class FStoreContentModelMasterDomain;
    class FStoreSubscriptionContentModelDomain;
    class FStoreSubscriptionContentModelMasterDomain;
    class FCurrentModelMasterDomain;
    class FDailyTransactionHistoryDomain;
    class FUnusedBalanceDomain;

    class GS2MONEY2_API FUserAccessTokenDomain:
        public TSharedFromThis<FUserAccessTokenDomain>
    {
        const Core::Domain::FGs2Ptr Gs2;
        const Money2::Domain::FGs2Money2DomainPtr Service;
        const Gs2::Money2::FGs2Money2RestClientPtr Client;

        public:
        TSharedPtr<TArray<TSharedPtr<Gs2::Money2::Model::FDepositTransaction>>> WithdrawTransactions;
        TOptional<FString> NextPageToken;
        TSharedPtr<TArray<TSharedPtr<Gs2::Money2::Model::FDepositTransaction>>> GetWithdrawTransactions() const
        {
            return WithdrawTransactions;
        }
        TOptional<FString> GetNextPageToken() const
        {
            return NextPageToken;
        }
        TOptional<FString> NamespaceName;
        Gs2::Auth::Model::FAccessTokenPtr AccessToken;
        TOptional<FString> UserId() const { return AccessToken->GetUserId(); }
    private:

        FString ParentKey;

    public:

        FUserAccessTokenDomain(
            const Core::Domain::FGs2Ptr& Gs2,
            const Money2::Domain::FGs2Money2DomainPtr& Service,
            const TOptional<FString> NamespaceName,
            const Gs2::Auth::Model::FAccessTokenPtr& AccessToken
            // ReSharper disable once CppMemberInitializersOrder
        );

        FUserAccessTokenDomain(
            const FUserAccessTokenDomain& From
        );

        class GS2MONEY2_API FVerifyReceiptTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Money2::Domain::Model::FEventAccessTokenDomain>,
            public TSharedFromThis<FVerifyReceiptTask>
        {
            const TSharedPtr<FUserAccessTokenDomain> Self;
            const Request::FVerifyReceiptRequestPtr Request;
        public:
            explicit FVerifyReceiptTask(
                const TSharedPtr<FUserAccessTokenDomain>& Self,
                const Request::FVerifyReceiptRequestPtr Request
            );

            FVerifyReceiptTask(
                const FVerifyReceiptTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Money2::Domain::Model::FEventAccessTokenDomain>> Result
            ) override;
        };
        friend FVerifyReceiptTask;

        TSharedPtr<FAsyncTask<FVerifyReceiptTask>> VerifyReceipt(
            Request::FVerifyReceiptRequestPtr Request
        );

        class GS2MONEY2_API FAllocateSubscriptionStatusTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Money2::Domain::Model::FSubscriptionStatusAccessTokenDomain>,
            public TSharedFromThis<FAllocateSubscriptionStatusTask>
        {
            const TSharedPtr<FUserAccessTokenDomain> Self;
            const Request::FAllocateSubscriptionStatusRequestPtr Request;
        public:
            explicit FAllocateSubscriptionStatusTask(
                const TSharedPtr<FUserAccessTokenDomain>& Self,
                const Request::FAllocateSubscriptionStatusRequestPtr Request
            );

            FAllocateSubscriptionStatusTask(
                const FAllocateSubscriptionStatusTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Money2::Domain::Model::FSubscriptionStatusAccessTokenDomain>> Result
            ) override;
        };
        friend FAllocateSubscriptionStatusTask;

        TSharedPtr<FAsyncTask<FAllocateSubscriptionStatusTask>> AllocateSubscriptionStatus(
            Request::FAllocateSubscriptionStatusRequestPtr Request
        );

        class GS2MONEY2_API FTakeoverSubscriptionStatusTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Money2::Domain::Model::FSubscriptionStatusAccessTokenDomain>,
            public TSharedFromThis<FTakeoverSubscriptionStatusTask>
        {
            const TSharedPtr<FUserAccessTokenDomain> Self;
            const Request::FTakeoverSubscriptionStatusRequestPtr Request;
        public:
            explicit FTakeoverSubscriptionStatusTask(
                const TSharedPtr<FUserAccessTokenDomain>& Self,
                const Request::FTakeoverSubscriptionStatusRequestPtr Request
            );

            FTakeoverSubscriptionStatusTask(
                const FTakeoverSubscriptionStatusTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Money2::Domain::Model::FSubscriptionStatusAccessTokenDomain>> Result
            ) override;
        };
        friend FTakeoverSubscriptionStatusTask;

        TSharedPtr<FAsyncTask<FTakeoverSubscriptionStatusTask>> TakeoverSubscriptionStatus(
            Request::FTakeoverSubscriptionStatusRequestPtr Request
        );

        Gs2::Money2::Domain::Iterator::FDescribeWalletsIteratorPtr Wallets(
        ) const;

        Gs2::Core::Domain::CallbackID SubscribeWallets(
            TFunction<void()> Callback
        );

        void UnsubscribeWallets(
            Gs2::Core::Domain::CallbackID CallbackID
        );

        TSharedPtr<Gs2::Money2::Domain::Model::FWalletAccessTokenDomain> Wallet(
            const int32 Slot
        );

        TSharedPtr<Gs2::Money2::Domain::Model::FEventAccessTokenDomain> Event(
            const FString TransactionId
        );

        Gs2::Money2::Domain::Iterator::FDescribeSubscriptionStatusesIteratorPtr SubscriptionStatuses(
        ) const;

        Gs2::Core::Domain::CallbackID SubscribeSubscriptionStatuses(
            TFunction<void()> Callback
        );

        void UnsubscribeSubscriptionStatuses(
            Gs2::Core::Domain::CallbackID CallbackID
        );

        TSharedPtr<Gs2::Money2::Domain::Model::FSubscriptionStatusAccessTokenDomain> SubscriptionStatus(
            const FString ContentName
        );

        static FString CreateCacheParentKey(
            TOptional<FString> NamespaceName,
            TOptional<FString> UserId,
            FString ChildType
        );

        static FString CreateCacheKey(
            TOptional<FString> UserId
        );

    };

    typedef TSharedPtr<FUserAccessTokenDomain> FUserAccessTokenDomainPtr;
}
