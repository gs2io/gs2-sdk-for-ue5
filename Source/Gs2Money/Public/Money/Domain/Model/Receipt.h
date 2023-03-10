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

    class GS2MONEY_API FReceiptDomain:
        public TSharedFromThis<FReceiptDomain>
    {
        Core::Domain::FCacheDatabasePtr Cache;
        Gs2::Core::Domain::Model::FJobQueueDomainPtr JobQueueDomain;
        Gs2::Core::Domain::Model::FStampSheetConfigurationPtr StampSheetConfiguration;
        Gs2::Core::Net::Rest::FGs2RestSessionPtr Session;
        Gs2::Money::FGs2MoneyRestClientPtr Client;

        public:
        TOptional<FString> NamespaceName;
        TOptional<FString> UserId;
        TOptional<FString> TransactionId;
    private:

        FString ParentKey;

    public:

        FReceiptDomain(
            const Core::Domain::FCacheDatabasePtr Cache,
            const Gs2::Core::Domain::Model::FJobQueueDomainPtr JobQueueDomain,
            const Gs2::Core::Domain::Model::FStampSheetConfigurationPtr StampSheetConfiguration,
            const Gs2::Core::Net::Rest::FGs2RestSessionPtr Session,
            const TOptional<FString> NamespaceName,
            const TOptional<FString> UserId,
            const TOptional<FString> TransactionId
            // ReSharper disable once CppMemberInitializersOrder
        );

        FReceiptDomain(
            const FReceiptDomain& From
        );

        class GS2MONEY_API FGetByUserIdAndTransactionIdTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Money::Domain::Model::FReceiptDomain>,
            public TSharedFromThis<FGetByUserIdAndTransactionIdTask>
        {
            const TSharedPtr<FReceiptDomain> Self;
            const Request::FGetByUserIdAndTransactionIdRequestPtr Request;
        public:
            explicit FGetByUserIdAndTransactionIdTask(
                const TSharedPtr<FReceiptDomain> Self,
                const Request::FGetByUserIdAndTransactionIdRequestPtr Request
            );

            FGetByUserIdAndTransactionIdTask(
                const FGetByUserIdAndTransactionIdTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Money::Domain::Model::FReceiptDomain>> Result
            ) override;
        };
        friend FGetByUserIdAndTransactionIdTask;

        TSharedPtr<FAsyncTask<FGetByUserIdAndTransactionIdTask>> GetByUserIdAndTransactionId(
            Request::FGetByUserIdAndTransactionIdRequestPtr Request
        );

        static FString CreateCacheParentKey(
            TOptional<FString> NamespaceName,
            TOptional<FString> UserId,
            TOptional<FString> TransactionId,
            FString ChildType
        );

        static FString CreateCacheKey(
            TOptional<FString> TransactionId
        );

        class GS2MONEY_API FModelTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Money::Model::FReceipt>,
            public TSharedFromThis<FModelTask>
        {
            const TSharedPtr<FReceiptDomain> Self;
        public:
            explicit FModelTask(
                const TSharedPtr<FReceiptDomain> Self
            );

            FModelTask(
                const FModelTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Money::Model::FReceipt>> Result
            ) override;
        };
        friend FModelTask;

        TSharedPtr<FAsyncTask<FModelTask>> Model();

    };

    typedef TSharedPtr<FReceiptDomain> FReceiptDomainPtr;
}
