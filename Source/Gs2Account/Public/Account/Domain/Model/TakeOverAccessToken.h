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

// ReSharper disable CppUnusedIncludeDirective

#pragma once

#include "Core/Domain/Gs2Core.h"
#include "Auth/Gs2Auth.h"
#include "Account/Gs2Account.h"
#include "Account/Domain/Iterator/DescribeNamespacesIterator.h"
#include "Account/Domain/Iterator/DescribeAccountsIterator.h"
#include "Account/Domain/Iterator/DescribeTakeOversIterator.h"
#include "Account/Domain/Iterator/DescribeTakeOversByUserIdIterator.h"
#include "Account/Domain/Iterator/DescribePlatformIdsIterator.h"
#include "Account/Domain/Iterator/DescribePlatformIdsByUserIdIterator.h"
#include "Account/Domain/Iterator/DescribeTakeOverTypeModelsIterator.h"
#include "Account/Domain/Iterator/DescribeTakeOverTypeModelMastersIterator.h"

namespace Gs2::Core::Domain
{
    class FGs2;
    typedef TSharedPtr<FGs2> FGs2Ptr;
}

namespace Gs2::Account::Domain
{
    class FGs2AccountDomain;
    typedef TSharedPtr<FGs2AccountDomain> FGs2AccountDomainPtr;
}

namespace Gs2::Account::Domain::Model
{
    class FNamespaceDomain;
    class FAccountDomain;
    class FAccountAccessTokenDomain;
    class FTakeOverDomain;
    class FTakeOverAccessTokenDomain;
    class FPlatformIdDomain;
    class FPlatformIdAccessTokenDomain;
    class FDataOwnerDomain;
    class FDataOwnerAccessTokenDomain;
    class FTakeOverTypeModelDomain;
    class FTakeOverTypeModelMasterDomain;
    class FCurrentModelMasterDomain;

    class GS2ACCOUNT_API FTakeOverAccessTokenDomain:
        public TSharedFromThis<FTakeOverAccessTokenDomain>
    {
        const Core::Domain::FGs2Ptr Gs2;
        const Account::Domain::FGs2AccountDomainPtr Service;
        const Gs2::Account::FGs2AccountRestClientPtr Client;

        public:
        TOptional<FString> AuthorizationUrl;
        TOptional<FString> Payload;
        TOptional<FString> GetAuthorizationUrl() const
        {
            return AuthorizationUrl;
        }
        TOptional<FString> GetPayload() const
        {
            return Payload;
        }
        TOptional<FString> NamespaceName;
        Gs2::Auth::Model::FAccessTokenPtr AccessToken;
        TOptional<FString> UserId() const { return AccessToken->GetUserId(); }
        TOptional<int32> Type;
    private:

        FString ParentKey;

    public:

        FTakeOverAccessTokenDomain(
            const Core::Domain::FGs2Ptr& Gs2,
            const Account::Domain::FGs2AccountDomainPtr& Service,
            const TOptional<FString> NamespaceName,
            const Gs2::Auth::Model::FAccessTokenPtr& AccessToken,
            const TOptional<int32> Type
            // ReSharper disable once CppMemberInitializersOrder
        );

        FTakeOverAccessTokenDomain(
            const FTakeOverAccessTokenDomain& From
        );

        class GS2ACCOUNT_API FCreateTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Account::Domain::Model::FTakeOverAccessTokenDomain>,
            public TSharedFromThis<FCreateTask>
        {
            const TSharedPtr<FTakeOverAccessTokenDomain> Self;
            const Request::FCreateTakeOverRequestPtr Request;
        public:
            explicit FCreateTask(
                const TSharedPtr<FTakeOverAccessTokenDomain>& Self,
                const Request::FCreateTakeOverRequestPtr Request
            );

            FCreateTask(
                const FCreateTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Account::Domain::Model::FTakeOverAccessTokenDomain>> Result
            ) override;
        };
        friend FCreateTask;

        TSharedPtr<FAsyncTask<FCreateTask>> Create(
            Request::FCreateTakeOverRequestPtr Request
        );

        class GS2ACCOUNT_API FCreateOpenIdConnectTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Account::Domain::Model::FTakeOverAccessTokenDomain>,
            public TSharedFromThis<FCreateOpenIdConnectTask>
        {
            const TSharedPtr<FTakeOverAccessTokenDomain> Self;
            const Request::FCreateTakeOverOpenIdConnectRequestPtr Request;
        public:
            explicit FCreateOpenIdConnectTask(
                const TSharedPtr<FTakeOverAccessTokenDomain>& Self,
                const Request::FCreateTakeOverOpenIdConnectRequestPtr Request
            );

            FCreateOpenIdConnectTask(
                const FCreateOpenIdConnectTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Account::Domain::Model::FTakeOverAccessTokenDomain>> Result
            ) override;
        };
        friend FCreateOpenIdConnectTask;

        TSharedPtr<FAsyncTask<FCreateOpenIdConnectTask>> CreateOpenIdConnect(
            Request::FCreateTakeOverOpenIdConnectRequestPtr Request
        );

        class GS2ACCOUNT_API FGetTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Account::Model::FTakeOver>,
            public TSharedFromThis<FGetTask>
        {
            const TSharedPtr<FTakeOverAccessTokenDomain> Self;
            const Request::FGetTakeOverRequestPtr Request;
        public:
            explicit FGetTask(
                const TSharedPtr<FTakeOverAccessTokenDomain>& Self,
                const Request::FGetTakeOverRequestPtr Request
            );

            FGetTask(
                const FGetTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Account::Model::FTakeOver>> Result
            ) override;
        };
        friend FGetTask;

        TSharedPtr<FAsyncTask<FGetTask>> Get(
            Request::FGetTakeOverRequestPtr Request
        );

        class GS2ACCOUNT_API FUpdateTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Account::Domain::Model::FTakeOverAccessTokenDomain>,
            public TSharedFromThis<FUpdateTask>
        {
            const TSharedPtr<FTakeOverAccessTokenDomain> Self;
            const Request::FUpdateTakeOverRequestPtr Request;
        public:
            explicit FUpdateTask(
                const TSharedPtr<FTakeOverAccessTokenDomain>& Self,
                const Request::FUpdateTakeOverRequestPtr Request
            );

            FUpdateTask(
                const FUpdateTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Account::Domain::Model::FTakeOverAccessTokenDomain>> Result
            ) override;
        };
        friend FUpdateTask;

        TSharedPtr<FAsyncTask<FUpdateTask>> Update(
            Request::FUpdateTakeOverRequestPtr Request
        );

        class GS2ACCOUNT_API FDeleteTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Account::Domain::Model::FTakeOverAccessTokenDomain>,
            public TSharedFromThis<FDeleteTask>
        {
            const TSharedPtr<FTakeOverAccessTokenDomain> Self;
            const Request::FDeleteTakeOverRequestPtr Request;
        public:
            explicit FDeleteTask(
                const TSharedPtr<FTakeOverAccessTokenDomain>& Self,
                const Request::FDeleteTakeOverRequestPtr Request
            );

            FDeleteTask(
                const FDeleteTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Account::Domain::Model::FTakeOverAccessTokenDomain>> Result
            ) override;
        };
        friend FDeleteTask;

        TSharedPtr<FAsyncTask<FDeleteTask>> Delete(
            Request::FDeleteTakeOverRequestPtr Request
        );

        static FString CreateCacheParentKey(
            TOptional<FString> NamespaceName,
            TOptional<FString> UserId,
            TOptional<int32> Type,
            FString ChildType
        );

        static FString CreateCacheKey(
            TOptional<int32> Type
        );

        class GS2ACCOUNT_API FModelTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Account::Model::FTakeOver>,
            public TSharedFromThis<FModelTask>
        {
            const TSharedPtr<FTakeOverAccessTokenDomain> Self;
        public:
            explicit FModelTask(
                const TSharedPtr<FTakeOverAccessTokenDomain> Self
            );

            FModelTask(
                const FModelTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Account::Model::FTakeOver>> Result
            ) override;
        };
        friend FModelTask;

        TSharedPtr<FAsyncTask<FModelTask>> Model();

        Gs2::Core::Domain::CallbackID Subscribe(
            TFunction<void(Gs2::Account::Model::FTakeOverPtr)> Callback
        );

        void Unsubscribe(
            Gs2::Core::Domain::CallbackID CallbackID
        );

    };

    typedef TSharedPtr<FTakeOverAccessTokenDomain> FTakeOverAccessTokenDomainPtr;
}
