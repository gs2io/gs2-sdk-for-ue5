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

    class GS2MONEY_API FWalletAccessTokenDomain:
        public TSharedFromThis<FWalletAccessTokenDomain>
    {
        Core::Domain::FCacheDatabasePtr Cache;
        Gs2::Core::Domain::Model::FJobQueueDomainPtr JobQueueDomain;
        Gs2::Core::Domain::Model::FStampSheetConfigurationPtr StampSheetConfiguration;
        Gs2::Core::Net::Rest::FGs2RestSessionPtr Session;
        Gs2::Money::FGs2MoneyRestClientPtr Client;

        public:
        TOptional<float> Price;
        TOptional<float> GetPrice() const
        {
            return Price;
        }
        TOptional<FString> NamespaceName;
        Gs2::Auth::Model::FAccessTokenPtr AccessToken;
        TOptional<FString> UserId() const { return AccessToken->GetUserId(); }
        TOptional<int32> Slot;
    private:

        FString ParentKey;

    public:

        FWalletAccessTokenDomain(
            const Core::Domain::FCacheDatabasePtr Cache,
            const Gs2::Core::Domain::Model::FJobQueueDomainPtr JobQueueDomain,
            const Gs2::Core::Domain::Model::FStampSheetConfigurationPtr StampSheetConfiguration,
            const Gs2::Core::Net::Rest::FGs2RestSessionPtr Session,
            const TOptional<FString> NamespaceName,
            const Gs2::Auth::Model::FAccessTokenPtr AccessToken,
            const TOptional<int32> Slot
            // ReSharper disable once CppMemberInitializersOrder
        );

        FWalletAccessTokenDomain(
            const FWalletAccessTokenDomain& From
        );

        class GS2MONEY_API FGetTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Money::Model::FWallet>,
            public TSharedFromThis<FGetTask>
        {
            const TSharedPtr<FWalletAccessTokenDomain> Self;
            const Request::FGetWalletRequestPtr Request;
        public:
            explicit FGetTask(
                const TSharedPtr<FWalletAccessTokenDomain> Self,
                const Request::FGetWalletRequestPtr Request
            );

            FGetTask(
                const FGetTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Money::Model::FWallet>> Result
            ) override;
        };
        friend FGetTask;

        TSharedPtr<FAsyncTask<FGetTask>> Get(
            Request::FGetWalletRequestPtr Request
        );

        class GS2MONEY_API FWithdrawTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Money::Domain::Model::FWalletAccessTokenDomain>,
            public TSharedFromThis<FWithdrawTask>
        {
            const TSharedPtr<FWalletAccessTokenDomain> Self;
            const Request::FWithdrawRequestPtr Request;
        public:
            explicit FWithdrawTask(
                const TSharedPtr<FWalletAccessTokenDomain> Self,
                const Request::FWithdrawRequestPtr Request
            );

            FWithdrawTask(
                const FWithdrawTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Money::Domain::Model::FWalletAccessTokenDomain>> Result
            ) override;
        };
        friend FWithdrawTask;

        TSharedPtr<FAsyncTask<FWithdrawTask>> Withdraw(
            Request::FWithdrawRequestPtr Request
        );

        static FString CreateCacheParentKey(
            TOptional<FString> NamespaceName,
            TOptional<FString> UserId,
            TOptional<FString> Slot,
            FString ChildType
        );

        static FString CreateCacheKey(
            TOptional<FString> Slot
        );

        class GS2MONEY_API FModelTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Money::Model::FWallet>,
            public TSharedFromThis<FModelTask>
        {
            const TSharedPtr<FWalletAccessTokenDomain> Self;
        public:
            explicit FModelTask(
                const TSharedPtr<FWalletAccessTokenDomain> Self
            );

            FModelTask(
                const FModelTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Money::Model::FWallet>> Result
            ) override;
        };
        friend FModelTask;

        TSharedPtr<FAsyncTask<FModelTask>> Model();

    };

    typedef TSharedPtr<FWalletAccessTokenDomain> FWalletAccessTokenDomainPtr;
}
