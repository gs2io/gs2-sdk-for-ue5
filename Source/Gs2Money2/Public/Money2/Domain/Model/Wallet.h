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
#include "Money2/Domain/Iterator/DescribeNamespacesIterator.h"
#include "Money2/Domain/Iterator/DescribeWalletsIterator.h"
#include "Money2/Domain/Iterator/DescribeWalletsByUserIdIterator.h"
#include "Money2/Domain/Iterator/DescribeEventsByUserIdIterator.h"
#include "Money2/Domain/Iterator/DescribeStoreContentModelsIterator.h"
#include "Money2/Domain/Iterator/DescribeStoreContentModelMastersIterator.h"

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
    class FStoreContentModelDomain;
    class FStoreContentModelMasterDomain;
    class FCurrentModelMasterDomain;

    class GS2MONEY2_API FWalletDomain:
        public TSharedFromThis<FWalletDomain>
    {
        const Core::Domain::FGs2Ptr Gs2;
        const Money2::Domain::FGs2Money2DomainPtr Service;
        const Gs2::Money2::FGs2Money2RestClientPtr Client;

        public:
        TSharedPtr<TArray<TSharedPtr<Gs2::Money2::Model::FDepositTransaction>>> WithdrawTransactions;
        TSharedPtr<TArray<TSharedPtr<Gs2::Money2::Model::FDepositTransaction>>> GetWithdrawTransactions() const
        {
            return WithdrawTransactions;
        }
        TOptional<FString> NamespaceName;
        TOptional<FString> UserId;
        TOptional<int32> Slot;
    private:

        FString ParentKey;

    public:

        FWalletDomain(
            const Core::Domain::FGs2Ptr& Gs2,
            const Money2::Domain::FGs2Money2DomainPtr& Service,
            const TOptional<FString> NamespaceName,
            const TOptional<FString> UserId,
            const TOptional<int32> Slot
            // ReSharper disable once CppMemberInitializersOrder
        );

        FWalletDomain(
            const FWalletDomain& From
        );

        class GS2MONEY2_API FGetTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Money2::Model::FWallet>,
            public TSharedFromThis<FGetTask>
        {
            const TSharedPtr<FWalletDomain> Self;
            const Request::FGetWalletByUserIdRequestPtr Request;
        public:
            explicit FGetTask(
                const TSharedPtr<FWalletDomain>& Self,
                const Request::FGetWalletByUserIdRequestPtr Request
            );

            FGetTask(
                const FGetTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Money2::Model::FWallet>> Result
            ) override;
        };
        friend FGetTask;

        TSharedPtr<FAsyncTask<FGetTask>> Get(
            Request::FGetWalletByUserIdRequestPtr Request
        );

        class GS2MONEY2_API FDepositTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Money2::Domain::Model::FWalletDomain>,
            public TSharedFromThis<FDepositTask>
        {
            const TSharedPtr<FWalletDomain> Self;
            const Request::FDepositByUserIdRequestPtr Request;
        public:
            explicit FDepositTask(
                const TSharedPtr<FWalletDomain>& Self,
                const Request::FDepositByUserIdRequestPtr Request
            );

            FDepositTask(
                const FDepositTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Money2::Domain::Model::FWalletDomain>> Result
            ) override;
        };
        friend FDepositTask;

        TSharedPtr<FAsyncTask<FDepositTask>> Deposit(
            Request::FDepositByUserIdRequestPtr Request
        );

        class GS2MONEY2_API FWithdrawTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Money2::Domain::Model::FWalletDomain>,
            public TSharedFromThis<FWithdrawTask>
        {
            const TSharedPtr<FWalletDomain> Self;
            const Request::FWithdrawByUserIdRequestPtr Request;
        public:
            explicit FWithdrawTask(
                const TSharedPtr<FWalletDomain>& Self,
                const Request::FWithdrawByUserIdRequestPtr Request
            );

            FWithdrawTask(
                const FWithdrawTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Money2::Domain::Model::FWalletDomain>> Result
            ) override;
        };
        friend FWithdrawTask;

        TSharedPtr<FAsyncTask<FWithdrawTask>> Withdraw(
            Request::FWithdrawByUserIdRequestPtr Request
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

        class GS2MONEY2_API FModelTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Money2::Model::FWallet>,
            public TSharedFromThis<FModelTask>
        {
            const TSharedPtr<FWalletDomain> Self;
        public:
            explicit FModelTask(
                const TSharedPtr<FWalletDomain> Self
            );

            FModelTask(
                const FModelTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Money2::Model::FWallet>> Result
            ) override;
        };
        friend FModelTask;

        TSharedPtr<FAsyncTask<FModelTask>> Model();

        Gs2::Core::Domain::CallbackID Subscribe(
            TFunction<void(Gs2::Money2::Model::FWalletPtr)> Callback
        );

        void Unsubscribe(
            Gs2::Core::Domain::CallbackID CallbackID
        );

    };

    typedef TSharedPtr<FWalletDomain> FWalletDomainPtr;
}
