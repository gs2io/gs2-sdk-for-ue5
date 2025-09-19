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
#include "Stamina/Domain/Iterator/DescribeNamespacesIterator.h"
#include "Stamina/Domain/Iterator/DescribeStaminaModelMastersIterator.h"
#include "Stamina/Domain/Iterator/DescribeMaxStaminaTableMastersIterator.h"
#include "Stamina/Domain/Iterator/DescribeRecoverIntervalTableMastersIterator.h"
#include "Stamina/Domain/Iterator/DescribeRecoverValueTableMastersIterator.h"
#include "Stamina/Domain/Iterator/DescribeStaminaModelsIterator.h"
#include "Stamina/Domain/Iterator/DescribeStaminasIterator.h"
#include "Stamina/Domain/Iterator/DescribeStaminasByUserIdIterator.h"

namespace Gs2::Core::Domain
{
    class FGs2;
    typedef TSharedPtr<FGs2> FGs2Ptr;
}

namespace Gs2::Stamina::Domain
{
    class FGs2StaminaDomain;
    typedef TSharedPtr<FGs2StaminaDomain> FGs2StaminaDomainPtr;
}

namespace Gs2::Stamina::Domain::Model
{
    class FNamespaceDomain;
    class FStaminaModelMasterDomain;
    class FMaxStaminaTableMasterDomain;
    class FRecoverIntervalTableMasterDomain;
    class FRecoverValueTableMasterDomain;
    class FCurrentStaminaMasterDomain;
    class FStaminaModelDomain;
    class FStaminaDomain;
    class FStaminaAccessTokenDomain;
    class FUserDomain;
    class FUserAccessTokenDomain;

    class GS2STAMINA_API FNamespaceDomain:
        public TSharedFromThis<FNamespaceDomain>
    {
        const Core::Domain::FGs2Ptr Gs2;
        const Stamina::Domain::FGs2StaminaDomainPtr Service;
        const Gs2::Stamina::FGs2StaminaRestClientPtr Client;

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
            const Stamina::Domain::FGs2StaminaDomainPtr& Service,
            const TOptional<FString> NamespaceName
            // ReSharper disable once CppMemberInitializersOrder
        );

        FNamespaceDomain(
            const FNamespaceDomain& From
        );

        class GS2STAMINA_API FGetStatusTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Stamina::Domain::Model::FNamespaceDomain>,
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
                TSharedPtr<TSharedPtr<Gs2::Stamina::Domain::Model::FNamespaceDomain>> Result
            ) override;
        };
        friend FGetStatusTask;

        TSharedPtr<FAsyncTask<FGetStatusTask>> GetStatus(
            Request::FGetNamespaceStatusRequestPtr Request
        );

        class GS2STAMINA_API FGetTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Stamina::Model::FNamespace>,
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
                TSharedPtr<TSharedPtr<Gs2::Stamina::Model::FNamespace>> Result
            ) override;
        };
        friend FGetTask;

        TSharedPtr<FAsyncTask<FGetTask>> Get(
            Request::FGetNamespaceRequestPtr Request
        );

        class GS2STAMINA_API FUpdateTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Stamina::Domain::Model::FNamespaceDomain>,
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
                TSharedPtr<TSharedPtr<Gs2::Stamina::Domain::Model::FNamespaceDomain>> Result
            ) override;
        };
        friend FUpdateTask;

        TSharedPtr<FAsyncTask<FUpdateTask>> Update(
            Request::FUpdateNamespaceRequestPtr Request
        );

        class GS2STAMINA_API FDeleteTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Stamina::Domain::Model::FNamespaceDomain>,
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
                TSharedPtr<TSharedPtr<Gs2::Stamina::Domain::Model::FNamespaceDomain>> Result
            ) override;
        };
        friend FDeleteTask;

        TSharedPtr<FAsyncTask<FDeleteTask>> Delete(
            Request::FDeleteNamespaceRequestPtr Request
        );

        class GS2STAMINA_API FCreateMaxStaminaTableMasterTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Stamina::Domain::Model::FMaxStaminaTableMasterDomain>,
            public TSharedFromThis<FCreateMaxStaminaTableMasterTask>
        {
            const TSharedPtr<FNamespaceDomain> Self;
            const Request::FCreateMaxStaminaTableMasterRequestPtr Request;
        public:
            explicit FCreateMaxStaminaTableMasterTask(
                const TSharedPtr<FNamespaceDomain>& Self,
                const Request::FCreateMaxStaminaTableMasterRequestPtr Request
            );

            FCreateMaxStaminaTableMasterTask(
                const FCreateMaxStaminaTableMasterTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Stamina::Domain::Model::FMaxStaminaTableMasterDomain>> Result
            ) override;
        };
        friend FCreateMaxStaminaTableMasterTask;

        TSharedPtr<FAsyncTask<FCreateMaxStaminaTableMasterTask>> CreateMaxStaminaTableMaster(
            Request::FCreateMaxStaminaTableMasterRequestPtr Request
        );

        class GS2STAMINA_API FCreateRecoverIntervalTableMasterTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Stamina::Domain::Model::FRecoverIntervalTableMasterDomain>,
            public TSharedFromThis<FCreateRecoverIntervalTableMasterTask>
        {
            const TSharedPtr<FNamespaceDomain> Self;
            const Request::FCreateRecoverIntervalTableMasterRequestPtr Request;
        public:
            explicit FCreateRecoverIntervalTableMasterTask(
                const TSharedPtr<FNamespaceDomain>& Self,
                const Request::FCreateRecoverIntervalTableMasterRequestPtr Request
            );

            FCreateRecoverIntervalTableMasterTask(
                const FCreateRecoverIntervalTableMasterTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Stamina::Domain::Model::FRecoverIntervalTableMasterDomain>> Result
            ) override;
        };
        friend FCreateRecoverIntervalTableMasterTask;

        TSharedPtr<FAsyncTask<FCreateRecoverIntervalTableMasterTask>> CreateRecoverIntervalTableMaster(
            Request::FCreateRecoverIntervalTableMasterRequestPtr Request
        );

        class GS2STAMINA_API FCreateRecoverValueTableMasterTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Stamina::Domain::Model::FRecoverValueTableMasterDomain>,
            public TSharedFromThis<FCreateRecoverValueTableMasterTask>
        {
            const TSharedPtr<FNamespaceDomain> Self;
            const Request::FCreateRecoverValueTableMasterRequestPtr Request;
        public:
            explicit FCreateRecoverValueTableMasterTask(
                const TSharedPtr<FNamespaceDomain>& Self,
                const Request::FCreateRecoverValueTableMasterRequestPtr Request
            );

            FCreateRecoverValueTableMasterTask(
                const FCreateRecoverValueTableMasterTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Stamina::Domain::Model::FRecoverValueTableMasterDomain>> Result
            ) override;
        };
        friend FCreateRecoverValueTableMasterTask;

        TSharedPtr<FAsyncTask<FCreateRecoverValueTableMasterTask>> CreateRecoverValueTableMaster(
            Request::FCreateRecoverValueTableMasterRequestPtr Request
        );

        class GS2STAMINA_API FCreateStaminaModelMasterTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Stamina::Domain::Model::FStaminaModelMasterDomain>,
            public TSharedFromThis<FCreateStaminaModelMasterTask>
        {
            const TSharedPtr<FNamespaceDomain> Self;
            const Request::FCreateStaminaModelMasterRequestPtr Request;
        public:
            explicit FCreateStaminaModelMasterTask(
                const TSharedPtr<FNamespaceDomain>& Self,
                const Request::FCreateStaminaModelMasterRequestPtr Request
            );

            FCreateStaminaModelMasterTask(
                const FCreateStaminaModelMasterTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Stamina::Domain::Model::FStaminaModelMasterDomain>> Result
            ) override;
        };
        friend FCreateStaminaModelMasterTask;

        TSharedPtr<FAsyncTask<FCreateStaminaModelMasterTask>> CreateStaminaModelMaster(
            Request::FCreateStaminaModelMasterRequestPtr Request
        );

        TSharedPtr<Gs2::Stamina::Domain::Model::FCurrentStaminaMasterDomain> CurrentStaminaMaster(
        );

        Gs2::Stamina::Domain::Iterator::FDescribeMaxStaminaTableMastersIteratorPtr MaxStaminaTableMasters(
        ) const;

        Gs2::Core::Domain::CallbackID SubscribeMaxStaminaTableMasters(
            TFunction<void()> Callback
        );

        void UnsubscribeMaxStaminaTableMasters(
            Gs2::Core::Domain::CallbackID CallbackID
        );

        TSharedPtr<Gs2::Stamina::Domain::Model::FMaxStaminaTableMasterDomain> MaxStaminaTableMaster(
            const FString MaxStaminaTableName
        );

        Gs2::Stamina::Domain::Iterator::FDescribeStaminaModelsIteratorPtr StaminaModels(
        ) const;

        Gs2::Core::Domain::CallbackID SubscribeStaminaModels(
            TFunction<void()> Callback
        );

        void UnsubscribeStaminaModels(
            Gs2::Core::Domain::CallbackID CallbackID
        );

        TSharedPtr<Gs2::Stamina::Domain::Model::FStaminaModelDomain> StaminaModel(
            const FString StaminaName
        );

        TSharedPtr<Gs2::Stamina::Domain::Model::FUserDomain> User(
            const FString UserId
        );

        TSharedPtr<Gs2::Stamina::Domain::Model::FUserAccessTokenDomain> AccessToken(
            Gs2::Auth::Model::FAccessTokenPtr AccessToken
        );

        Gs2::Stamina::Domain::Iterator::FDescribeRecoverIntervalTableMastersIteratorPtr RecoverIntervalTableMasters(
            const TOptional<FString> NamePrefix = TOptional<FString>()
        ) const;

        Gs2::Core::Domain::CallbackID SubscribeRecoverIntervalTableMasters(
            TFunction<void()> Callback
        );

        void UnsubscribeRecoverIntervalTableMasters(
            Gs2::Core::Domain::CallbackID CallbackID
        );

        TSharedPtr<Gs2::Stamina::Domain::Model::FRecoverIntervalTableMasterDomain> RecoverIntervalTableMaster(
            const FString RecoverIntervalTableName
        );

        Gs2::Stamina::Domain::Iterator::FDescribeRecoverValueTableMastersIteratorPtr RecoverValueTableMasters(
            const TOptional<FString> NamePrefix = TOptional<FString>()
        ) const;

        Gs2::Core::Domain::CallbackID SubscribeRecoverValueTableMasters(
            TFunction<void()> Callback
        );

        void UnsubscribeRecoverValueTableMasters(
            Gs2::Core::Domain::CallbackID CallbackID
        );

        TSharedPtr<Gs2::Stamina::Domain::Model::FRecoverValueTableMasterDomain> RecoverValueTableMaster(
            const FString RecoverValueTableName
        );

        Gs2::Stamina::Domain::Iterator::FDescribeStaminaModelMastersIteratorPtr StaminaModelMasters(
            const TOptional<FString> NamePrefix = TOptional<FString>()
        ) const;

        Gs2::Core::Domain::CallbackID SubscribeStaminaModelMasters(
            TFunction<void()> Callback
        );

        void UnsubscribeStaminaModelMasters(
            Gs2::Core::Domain::CallbackID CallbackID
        );

        TSharedPtr<Gs2::Stamina::Domain::Model::FStaminaModelMasterDomain> StaminaModelMaster(
            const FString StaminaName
        );

        static FString CreateCacheParentKey(
            TOptional<FString> NamespaceName,
            FString ChildType
        );

        static FString CreateCacheKey(
            TOptional<FString> NamespaceName
        );

        class GS2STAMINA_API FModelTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Stamina::Model::FNamespace>,
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
                TSharedPtr<TSharedPtr<Gs2::Stamina::Model::FNamespace>> Result
            ) override;
        };
        friend FModelTask;

        TSharedPtr<FAsyncTask<FModelTask>> Model();

        Gs2::Core::Domain::CallbackID Subscribe(
            TFunction<void(Gs2::Stamina::Model::FNamespacePtr)> Callback
        );

        void Unsubscribe(
            Gs2::Core::Domain::CallbackID CallbackID
        );

    };

    typedef TSharedPtr<FNamespaceDomain> FNamespaceDomainPtr;
}
