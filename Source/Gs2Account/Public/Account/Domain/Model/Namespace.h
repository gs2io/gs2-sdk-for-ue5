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

    class GS2ACCOUNT_API FNamespaceDomain:
        public TSharedFromThis<FNamespaceDomain>
    {
        const Core::Domain::FGs2Ptr Gs2;
        const Account::Domain::FGs2AccountDomainPtr Service;
        const Gs2::Account::FGs2AccountRestClientPtr Client;

        public:
        TOptional<FString> Status;
        TOptional<FString> Url;
        TOptional<FString> UploadToken;
        TOptional<FString> UploadUrl;
        TOptional<FString> NextPageToken;
        TOptional<FString> GetStatus() const
        {
            return Status;
        }
        TOptional<FString> GetUrl() const
        {
            return Url;
        }
        TOptional<FString> GetUploadToken() const
        {
            return UploadToken;
        }
        TOptional<FString> GetUploadUrl() const
        {
            return UploadUrl;
        }
        TOptional<FString> GetNextPageToken() const
        {
            return NextPageToken;
        }
        TOptional<FString> NamespaceName;
    private:

        FString ParentKey;

    public:

        FNamespaceDomain(
            const Core::Domain::FGs2Ptr& Gs2,
            const Account::Domain::FGs2AccountDomainPtr& Service,
            const TOptional<FString> NamespaceName
            // ReSharper disable once CppMemberInitializersOrder
        );

        FNamespaceDomain(
            const FNamespaceDomain& From
        );

        class GS2ACCOUNT_API FGetStatusTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Account::Domain::Model::FNamespaceDomain>,
            public TSharedFromThis<FGetStatusTask>
        {
            const TSharedPtr<FNamespaceDomain> Self;
            const Request::FGetNamespaceStatusRequestPtr Request;
        public:
            explicit FGetStatusTask(
                const TSharedPtr<FNamespaceDomain>& Self,
                const Request::FGetNamespaceStatusRequestPtr Request
            );

            FGetStatusTask(
                const FGetStatusTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Account::Domain::Model::FNamespaceDomain>> Result
            ) override;
        };
        friend FGetStatusTask;

        TSharedPtr<FAsyncTask<FGetStatusTask>> GetStatus(
            Request::FGetNamespaceStatusRequestPtr Request
        );

        class GS2ACCOUNT_API FGetTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Account::Model::FNamespace>,
            public TSharedFromThis<FGetTask>
        {
            const TSharedPtr<FNamespaceDomain> Self;
            const Request::FGetNamespaceRequestPtr Request;
        public:
            explicit FGetTask(
                const TSharedPtr<FNamespaceDomain>& Self,
                const Request::FGetNamespaceRequestPtr Request
            );

            FGetTask(
                const FGetTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Account::Model::FNamespace>> Result
            ) override;
        };
        friend FGetTask;

        TSharedPtr<FAsyncTask<FGetTask>> Get(
            Request::FGetNamespaceRequestPtr Request
        );

        class GS2ACCOUNT_API FUpdateTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Account::Domain::Model::FNamespaceDomain>,
            public TSharedFromThis<FUpdateTask>
        {
            const TSharedPtr<FNamespaceDomain> Self;
            const Request::FUpdateNamespaceRequestPtr Request;
        public:
            explicit FUpdateTask(
                const TSharedPtr<FNamespaceDomain>& Self,
                const Request::FUpdateNamespaceRequestPtr Request
            );

            FUpdateTask(
                const FUpdateTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Account::Domain::Model::FNamespaceDomain>> Result
            ) override;
        };
        friend FUpdateTask;

        TSharedPtr<FAsyncTask<FUpdateTask>> Update(
            Request::FUpdateNamespaceRequestPtr Request
        );

        class GS2ACCOUNT_API FDeleteTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Account::Domain::Model::FNamespaceDomain>,
            public TSharedFromThis<FDeleteTask>
        {
            const TSharedPtr<FNamespaceDomain> Self;
            const Request::FDeleteNamespaceRequestPtr Request;
        public:
            explicit FDeleteTask(
                const TSharedPtr<FNamespaceDomain>& Self,
                const Request::FDeleteNamespaceRequestPtr Request
            );

            FDeleteTask(
                const FDeleteTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Account::Domain::Model::FNamespaceDomain>> Result
            ) override;
        };
        friend FDeleteTask;

        TSharedPtr<FAsyncTask<FDeleteTask>> Delete(
            Request::FDeleteNamespaceRequestPtr Request
        );

        class GS2ACCOUNT_API FCreateAccountTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Account::Domain::Model::FAccountDomain>,
            public TSharedFromThis<FCreateAccountTask>
        {
            const TSharedPtr<FNamespaceDomain> Self;
            const Request::FCreateAccountRequestPtr Request;
        public:
            explicit FCreateAccountTask(
                const TSharedPtr<FNamespaceDomain>& Self,
                const Request::FCreateAccountRequestPtr Request
            );

            FCreateAccountTask(
                const FCreateAccountTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Account::Domain::Model::FAccountDomain>> Result
            ) override;
        };
        friend FCreateAccountTask;

        TSharedPtr<FAsyncTask<FCreateAccountTask>> CreateAccount(
            Request::FCreateAccountRequestPtr Request
        );

        class GS2ACCOUNT_API FDoTakeOverTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Account::Domain::Model::FAccountDomain>,
            public TSharedFromThis<FDoTakeOverTask>
        {
            const TSharedPtr<FNamespaceDomain> Self;
            const Request::FDoTakeOverRequestPtr Request;
        public:
            explicit FDoTakeOverTask(
                const TSharedPtr<FNamespaceDomain>& Self,
                const Request::FDoTakeOverRequestPtr Request
            );

            FDoTakeOverTask(
                const FDoTakeOverTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Account::Domain::Model::FAccountDomain>> Result
            ) override;
        };
        friend FDoTakeOverTask;

        TSharedPtr<FAsyncTask<FDoTakeOverTask>> DoTakeOver(
            Request::FDoTakeOverRequestPtr Request
        );

        class GS2ACCOUNT_API FDoTakeOverOpenIdConnectTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Account::Domain::Model::FAccountDomain>,
            public TSharedFromThis<FDoTakeOverOpenIdConnectTask>
        {
            const TSharedPtr<FNamespaceDomain> Self;
            const Request::FDoTakeOverOpenIdConnectRequestPtr Request;
        public:
            explicit FDoTakeOverOpenIdConnectTask(
                const TSharedPtr<FNamespaceDomain>& Self,
                const Request::FDoTakeOverOpenIdConnectRequestPtr Request
            );

            FDoTakeOverOpenIdConnectTask(
                const FDoTakeOverOpenIdConnectTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Account::Domain::Model::FAccountDomain>> Result
            ) override;
        };
        friend FDoTakeOverOpenIdConnectTask;

        TSharedPtr<FAsyncTask<FDoTakeOverOpenIdConnectTask>> DoTakeOverOpenIdConnect(
            Request::FDoTakeOverOpenIdConnectRequestPtr Request
        );

        class GS2ACCOUNT_API FDeletePlatformIdByUserIdentifierTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Account::Domain::Model::FPlatformIdDomain>,
            public TSharedFromThis<FDeletePlatformIdByUserIdentifierTask>
        {
            const TSharedPtr<FNamespaceDomain> Self;
            const Request::FDeletePlatformIdByUserIdentifierRequestPtr Request;
        public:
            explicit FDeletePlatformIdByUserIdentifierTask(
                const TSharedPtr<FNamespaceDomain>& Self,
                const Request::FDeletePlatformIdByUserIdentifierRequestPtr Request
            );

            FDeletePlatformIdByUserIdentifierTask(
                const FDeletePlatformIdByUserIdentifierTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Account::Domain::Model::FPlatformIdDomain>> Result
            ) override;
        };
        friend FDeletePlatformIdByUserIdentifierTask;

        TSharedPtr<FAsyncTask<FDeletePlatformIdByUserIdentifierTask>> DeletePlatformIdByUserIdentifier(
            Request::FDeletePlatformIdByUserIdentifierRequestPtr Request
        );

        Gs2::Account::Domain::Iterator::FDescribeAccountsIteratorPtr Accounts(
        ) const;

        Gs2::Core::Domain::CallbackID SubscribeAccounts(
            TFunction<void()> Callback
        );

        void UnsubscribeAccounts(
            Gs2::Core::Domain::CallbackID CallbackID
        );

        TSharedPtr<Gs2::Account::Domain::Model::FAccountDomain> Account(
            const FString UserId
        );

        TSharedPtr<Gs2::Account::Domain::Model::FAccountAccessTokenDomain> AccessToken(
            Gs2::Auth::Model::FAccessTokenPtr AccessToken
        );

        TSharedPtr<Gs2::Account::Domain::Model::FCurrentModelMasterDomain> CurrentModelMaster(
        );

        Gs2::Account::Domain::Iterator::FDescribeTakeOverTypeModelsIteratorPtr TakeOverTypeModels(
        ) const;

        Gs2::Core::Domain::CallbackID SubscribeTakeOverTypeModels(
            TFunction<void()> Callback
        );

        void UnsubscribeTakeOverTypeModels(
            Gs2::Core::Domain::CallbackID CallbackID
        );

        TSharedPtr<Gs2::Account::Domain::Model::FTakeOverTypeModelDomain> TakeOverTypeModel(
            const int32 Type
        );

        Gs2::Account::Domain::Iterator::FDescribeTakeOverTypeModelMastersIteratorPtr TakeOverTypeModelMasters(
        ) const;

        Gs2::Core::Domain::CallbackID SubscribeTakeOverTypeModelMasters(
            TFunction<void()> Callback
        );

        void UnsubscribeTakeOverTypeModelMasters(
            Gs2::Core::Domain::CallbackID CallbackID
        );

        TSharedPtr<Gs2::Account::Domain::Model::FTakeOverTypeModelMasterDomain> TakeOverTypeModelMaster(
            const int32 Type
        );

        static FString CreateCacheParentKey(
            TOptional<FString> NamespaceName,
            FString ChildType
        );

        static FString CreateCacheKey(
            TOptional<FString> NamespaceName
        );

        class GS2ACCOUNT_API FModelTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Account::Model::FNamespace>,
            public TSharedFromThis<FModelTask>
        {
            const TSharedPtr<FNamespaceDomain> Self;
        public:
            explicit FModelTask(
                const TSharedPtr<FNamespaceDomain> Self
            );

            FModelTask(
                const FModelTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Account::Model::FNamespace>> Result
            ) override;
        };
        friend FModelTask;

        TSharedPtr<FAsyncTask<FModelTask>> Model();

        Gs2::Core::Domain::CallbackID Subscribe(
            TFunction<void(Gs2::Account::Model::FNamespacePtr)> Callback
        );

        void Unsubscribe(
            Gs2::Core::Domain::CallbackID CallbackID
        );

        class GS2ACCOUNT_API FDeleteTakeOverByUserIdentifierTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Account::Domain::Model::FTakeOverDomain>,
            public TSharedFromThis<FDeleteTakeOverByUserIdentifierTask>
        {
            const TSharedPtr<FNamespaceDomain> Self;
            const Request::FDeleteTakeOverByUserIdentifierRequestPtr Request;
        public:
            explicit FDeleteTakeOverByUserIdentifierTask(
                const TSharedPtr<FNamespaceDomain>& Self,
                const Request::FDeleteTakeOverByUserIdentifierRequestPtr Request
            );

            FDeleteTakeOverByUserIdentifierTask(
                const FDeleteTakeOverByUserIdentifierTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Account::Domain::Model::FTakeOverDomain>> Result
            ) override;
        };
        friend FDeleteTakeOverByUserIdentifierTask;

        TSharedPtr<FAsyncTask<FDeleteTakeOverByUserIdentifierTask>> DeleteTakeOverByUserIdentifier(
            Request::FDeleteTakeOverByUserIdentifierRequestPtr Request
        );

    };

    typedef TSharedPtr<FNamespaceDomain> FNamespaceDomainPtr;
}
