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

    class GS2ACCOUNT_API FPlatformIdAccessTokenDomain:
        public TSharedFromThis<FPlatformIdAccessTokenDomain>
    {
        const Core::Domain::FGs2Ptr Gs2;
        const Account::Domain::FGs2AccountDomainPtr Service;
        const Gs2::Account::FGs2AccountRestClientPtr Client;

        public:
        TOptional<FString> NamespaceName;
        Gs2::Auth::Model::FAccessTokenPtr AccessToken;
        TOptional<FString> UserId() const { return AccessToken->GetUserId(); }
        TOptional<int32> Type;
        TOptional<FString> UserIdentifier;
    private:

        FString ParentKey;

    public:

        FPlatformIdAccessTokenDomain(
            const Core::Domain::FGs2Ptr& Gs2,
            const Account::Domain::FGs2AccountDomainPtr& Service,
            const TOptional<FString> NamespaceName,
            const Gs2::Auth::Model::FAccessTokenPtr& AccessToken,
            const TOptional<int32> Type,
            const TOptional<FString> UserIdentifier
            // ReSharper disable once CppMemberInitializersOrder
        );

        FPlatformIdAccessTokenDomain(
            const FPlatformIdAccessTokenDomain& From
        );

        class GS2ACCOUNT_API FGetTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Account::Model::FPlatformId>,
            public TSharedFromThis<FGetTask>
        {
            const TSharedPtr<FPlatformIdAccessTokenDomain> Self;
            const Request::FGetPlatformIdRequestPtr Request;
        public:
            explicit FGetTask(
                const TSharedPtr<FPlatformIdAccessTokenDomain>& Self,
                const Request::FGetPlatformIdRequestPtr Request
            );

            FGetTask(
                const FGetTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Account::Model::FPlatformId>> Result
            ) override;
        };
        friend FGetTask;

        TSharedPtr<FAsyncTask<FGetTask>> Get(
            Request::FGetPlatformIdRequestPtr Request
        );

        class GS2ACCOUNT_API FCreateTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Account::Domain::Model::FPlatformIdAccessTokenDomain>,
            public TSharedFromThis<FCreateTask>
        {
            const TSharedPtr<FPlatformIdAccessTokenDomain> Self;
            const Request::FCreatePlatformIdRequestPtr Request;
        public:
            explicit FCreateTask(
                const TSharedPtr<FPlatformIdAccessTokenDomain>& Self,
                const Request::FCreatePlatformIdRequestPtr Request
            );

            FCreateTask(
                const FCreateTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Account::Domain::Model::FPlatformIdAccessTokenDomain>> Result
            ) override;
        };
        friend FCreateTask;

        TSharedPtr<FAsyncTask<FCreateTask>> Create(
            Request::FCreatePlatformIdRequestPtr Request
        );

        class GS2ACCOUNT_API FFindTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Account::Model::FPlatformUser>,
            public TSharedFromThis<FFindTask>
        {
            const TSharedPtr<FPlatformIdAccessTokenDomain> Self;
            const Request::FFindPlatformIdRequestPtr Request;
        public:
            explicit FFindTask(
                const TSharedPtr<FPlatformIdAccessTokenDomain>& Self,
                const Request::FFindPlatformIdRequestPtr Request
            );

            FFindTask(
                const FFindTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Account::Model::FPlatformUser>> Result
            ) override;
        };
        friend FFindTask;

        TSharedPtr<FAsyncTask<FFindTask>> Find(
            Request::FFindPlatformIdRequestPtr Request
        );

        class GS2ACCOUNT_API FDeleteTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Account::Domain::Model::FPlatformIdAccessTokenDomain>,
            public TSharedFromThis<FDeleteTask>
        {
            const TSharedPtr<FPlatformIdAccessTokenDomain> Self;
            const Request::FDeletePlatformIdRequestPtr Request;
        public:
            explicit FDeleteTask(
                const TSharedPtr<FPlatformIdAccessTokenDomain>& Self,
                const Request::FDeletePlatformIdRequestPtr Request
            );

            FDeleteTask(
                const FDeleteTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Account::Domain::Model::FPlatformIdAccessTokenDomain>> Result
            ) override;
        };
        friend FDeleteTask;

        TSharedPtr<FAsyncTask<FDeleteTask>> Delete(
            Request::FDeletePlatformIdRequestPtr Request
        );

        static FString CreateCacheParentKey(
            TOptional<FString> NamespaceName,
            TOptional<FString> UserId,
            TOptional<FString> Type,
            TOptional<FString> UserIdentifier,
            FString ChildType
        );

        static FString CreateCacheKey(
            TOptional<FString> Type,
            TOptional<FString> UserIdentifier
        );

        class GS2ACCOUNT_API FModelTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Account::Model::FPlatformId>,
            public TSharedFromThis<FModelTask>
        {
            const TSharedPtr<FPlatformIdAccessTokenDomain> Self;
        public:
            explicit FModelTask(
                const TSharedPtr<FPlatformIdAccessTokenDomain> Self
            );

            FModelTask(
                const FModelTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Account::Model::FPlatformId>> Result
            ) override;
        };
        friend FModelTask;

        TSharedPtr<FAsyncTask<FModelTask>> Model();

        Gs2::Core::Domain::CallbackID Subscribe(
            TFunction<void(Gs2::Account::Model::FPlatformIdPtr)> Callback
        );

        void Unsubscribe(
            Gs2::Core::Domain::CallbackID CallbackID
        );

    };

    typedef TSharedPtr<FPlatformIdAccessTokenDomain> FPlatformIdAccessTokenDomainPtr;
}
