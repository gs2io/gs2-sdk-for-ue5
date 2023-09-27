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
#include "Money/Gs2Money.h"
#include "Money/Domain/Iterator/DescribeNamespacesIterator.h"
#include "Money/Domain/Iterator/DescribeWalletsIterator.h"
#include "Money/Domain/Iterator/DescribeWalletsByUserIdIterator.h"
#include "Money/Domain/Iterator/DescribeReceiptsIterator.h"

namespace Gs2::Money::Domain::Model
{
    class FNamespaceDomain;
    class FUserDomain;
    class FUserAccessTokenDomain;
    class FWalletDomain;
    class FWalletAccessTokenDomain;
    class FReceiptDomain;
    class FReceiptAccessTokenDomain;

    class GS2MONEY_API FUserDomain:
        public TSharedFromThis<FUserDomain>
    {
        Core::Domain::FCacheDatabasePtr Cache;
        Gs2::Core::Domain::Model::FJobQueueDomainPtr JobQueueDomain;
        Gs2::Core::Domain::Model::FStampSheetConfigurationPtr StampSheetConfiguration;
        Gs2::Core::Net::Rest::FGs2RestSessionPtr Session;
        Gs2::Money::FGs2MoneyRestClientPtr Client;

        public:
        TOptional<float> Price;
        TOptional<FString> NextPageToken;
        TOptional<float> GetPrice() const
        {
            return Price;
        }
        TOptional<FString> GetNextPageToken() const
        {
            return NextPageToken;
        }
        TOptional<FString> NamespaceName;
        TOptional<FString> UserId;
    private:

        FString ParentKey;

    public:

        FUserDomain(
            const Core::Domain::FCacheDatabasePtr Cache,
            const Gs2::Core::Domain::Model::FJobQueueDomainPtr JobQueueDomain,
            const Gs2::Core::Domain::Model::FStampSheetConfigurationPtr StampSheetConfiguration,
            const Gs2::Core::Net::Rest::FGs2RestSessionPtr Session,
            const TOptional<FString> NamespaceName,
            const TOptional<FString> UserId
            // ReSharper disable once CppMemberInitializersOrder
        );

        FUserDomain(
            const FUserDomain& From
        );

        class GS2MONEY_API FRecordReceiptTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Money::Domain::Model::FReceiptDomain>,
            public TSharedFromThis<FRecordReceiptTask>
        {
            const TSharedPtr<FUserDomain> Self;
            const Request::FRecordReceiptRequestPtr Request;
        public:
            explicit FRecordReceiptTask(
                const TSharedPtr<FUserDomain> Self,
                const Request::FRecordReceiptRequestPtr Request
            );

            FRecordReceiptTask(
                const FRecordReceiptTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Money::Domain::Model::FReceiptDomain>> Result
            ) override;
        };
        friend FRecordReceiptTask;

        TSharedPtr<FAsyncTask<FRecordReceiptTask>> RecordReceipt(
            Request::FRecordReceiptRequestPtr Request
        );

        class GS2MONEY_API FRevertRecordReceiptTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Money::Domain::Model::FReceiptDomain>,
            public TSharedFromThis<FRevertRecordReceiptTask>
        {
            const TSharedPtr<FUserDomain> Self;
            const Request::FRevertRecordReceiptRequestPtr Request;
        public:
            explicit FRevertRecordReceiptTask(
                const TSharedPtr<FUserDomain> Self,
                const Request::FRevertRecordReceiptRequestPtr Request
            );

            FRevertRecordReceiptTask(
                const FRevertRecordReceiptTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Money::Domain::Model::FReceiptDomain>> Result
            ) override;
        };
        friend FRevertRecordReceiptTask;

        TSharedPtr<FAsyncTask<FRevertRecordReceiptTask>> RevertRecordReceipt(
            Request::FRevertRecordReceiptRequestPtr Request
        );

        Gs2::Money::Domain::Iterator::FDescribeWalletsByUserIdIteratorPtr Wallets(
        ) const;

        Gs2::Core::Domain::CallbackID SubscribeWallets(
            TFunction<void()> Callback
        );

        void UnsubscribeWallets(
            Gs2::Core::Domain::CallbackID CallbackID
        );

        TSharedPtr<Gs2::Money::Domain::Model::FWalletDomain> Wallet(
            const int32 Slot
        ) const;

        Gs2::Money::Domain::Iterator::FDescribeReceiptsIteratorPtr Receipts(
            const TOptional<int32> Slot,
            const TOptional<int64> Begin,
            const TOptional<int64> End
        ) const;

        Gs2::Core::Domain::CallbackID SubscribeReceipts(
            TFunction<void()> Callback
        );

        void UnsubscribeReceipts(
            Gs2::Core::Domain::CallbackID CallbackID
        );

        TSharedPtr<Gs2::Money::Domain::Model::FReceiptDomain> Receipt(
            const FString TransactionId
        ) const;

        static FString CreateCacheParentKey(
            TOptional<FString> NamespaceName,
            TOptional<FString> UserId,
            FString ChildType
        );

        static FString CreateCacheKey(
            TOptional<FString> UserId
        );

    };

    typedef TSharedPtr<FUserDomain> FUserDomainPtr;
}
