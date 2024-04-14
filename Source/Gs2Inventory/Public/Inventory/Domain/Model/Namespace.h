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
#include "Inventory/Domain/Iterator/DescribeNamespacesIterator.h"
#include "Inventory/Domain/Iterator/DescribeInventoryModelMastersIterator.h"
#include "Inventory/Domain/Iterator/DescribeInventoryModelsIterator.h"
#include "Inventory/Domain/Iterator/DescribeItemModelMastersIterator.h"
#include "Inventory/Domain/Iterator/DescribeItemModelsIterator.h"
#include "Inventory/Domain/Iterator/DescribeSimpleInventoryModelMastersIterator.h"
#include "Inventory/Domain/Iterator/DescribeSimpleInventoryModelsIterator.h"
#include "Inventory/Domain/Iterator/DescribeSimpleItemModelMastersIterator.h"
#include "Inventory/Domain/Iterator/DescribeSimpleItemModelsIterator.h"
#include "Inventory/Domain/Iterator/DescribeBigInventoryModelMastersIterator.h"
#include "Inventory/Domain/Iterator/DescribeBigInventoryModelsIterator.h"
#include "Inventory/Domain/Iterator/DescribeBigItemModelMastersIterator.h"
#include "Inventory/Domain/Iterator/DescribeBigItemModelsIterator.h"
#include "Inventory/Domain/Iterator/DescribeInventoriesIterator.h"
#include "Inventory/Domain/Iterator/DescribeInventoriesByUserIdIterator.h"
#include "Inventory/Domain/Iterator/DescribeItemSetsIterator.h"
#include "Inventory/Domain/Iterator/DescribeItemSetsByUserIdIterator.h"
#include "Inventory/Domain/Iterator/DescribeReferenceOfIterator.h"
#include "Inventory/Domain/Iterator/DescribeReferenceOfByUserIdIterator.h"
#include "Inventory/Domain/Iterator/DescribeSimpleItemsIterator.h"
#include "Inventory/Domain/Iterator/DescribeSimpleItemsByUserIdIterator.h"
#include "Inventory/Domain/Iterator/DescribeBigItemsIterator.h"
#include "Inventory/Domain/Iterator/DescribeBigItemsByUserIdIterator.h"

namespace Gs2::Core::Domain
{
    class FGs2;
    typedef TSharedPtr<FGs2> FGs2Ptr;
}

namespace Gs2::Inventory::Domain
{
    class FGs2InventoryDomain;
    typedef TSharedPtr<FGs2InventoryDomain> FGs2InventoryDomainPtr;
}

namespace Gs2::Inventory::Domain::Model
{
    class FNamespaceDomain;
    class FInventoryModelMasterDomain;
    class FInventoryModelDomain;
    class FItemModelMasterDomain;
    class FItemModelDomain;
    class FSimpleInventoryModelMasterDomain;
    class FSimpleInventoryModelDomain;
    class FSimpleItemModelMasterDomain;
    class FSimpleItemModelDomain;
    class FBigInventoryModelMasterDomain;
    class FBigInventoryModelDomain;
    class FBigItemModelMasterDomain;
    class FBigItemModelDomain;
    class FCurrentItemModelMasterDomain;
    class FInventoryDomain;
    class FInventoryAccessTokenDomain;
    class FItemSetDomain;
    class FItemSetAccessTokenDomain;
    class FReferenceOfDomain;
    class FReferenceOfAccessTokenDomain;
    class FSimpleInventoryDomain;
    class FSimpleInventoryAccessTokenDomain;
    class FSimpleItemDomain;
    class FSimpleItemAccessTokenDomain;
    class FBigInventoryDomain;
    class FBigInventoryAccessTokenDomain;
    class FBigItemDomain;
    class FBigItemAccessTokenDomain;
    class FUserDomain;
    class FUserAccessTokenDomain;
    class FItemSetEntry;

    class GS2INVENTORY_API FNamespaceDomain:
        public TSharedFromThis<FNamespaceDomain>
    {
        const Core::Domain::FGs2Ptr Gs2;
        const Inventory::Domain::FGs2InventoryDomainPtr Service;
        const Gs2::Inventory::FGs2InventoryRestClientPtr Client;

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
            const Inventory::Domain::FGs2InventoryDomainPtr& Service,
            const TOptional<FString> NamespaceName
            // ReSharper disable once CppMemberInitializersOrder
        );

        FNamespaceDomain(
            const FNamespaceDomain& From
        );

        class GS2INVENTORY_API FGetStatusTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Inventory::Domain::Model::FNamespaceDomain>,
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
                TSharedPtr<TSharedPtr<Gs2::Inventory::Domain::Model::FNamespaceDomain>> Result
            ) override;
        };
        friend FGetStatusTask;

        TSharedPtr<FAsyncTask<FGetStatusTask>> GetStatus(
            Request::FGetNamespaceStatusRequestPtr Request
        );

        class GS2INVENTORY_API FGetTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Inventory::Model::FNamespace>,
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
                TSharedPtr<TSharedPtr<Gs2::Inventory::Model::FNamespace>> Result
            ) override;
        };
        friend FGetTask;

        TSharedPtr<FAsyncTask<FGetTask>> Get(
            Request::FGetNamespaceRequestPtr Request
        );

        class GS2INVENTORY_API FUpdateTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Inventory::Domain::Model::FNamespaceDomain>,
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
                TSharedPtr<TSharedPtr<Gs2::Inventory::Domain::Model::FNamespaceDomain>> Result
            ) override;
        };
        friend FUpdateTask;

        TSharedPtr<FAsyncTask<FUpdateTask>> Update(
            Request::FUpdateNamespaceRequestPtr Request
        );

        class GS2INVENTORY_API FDeleteTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Inventory::Domain::Model::FNamespaceDomain>,
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
                TSharedPtr<TSharedPtr<Gs2::Inventory::Domain::Model::FNamespaceDomain>> Result
            ) override;
        };
        friend FDeleteTask;

        TSharedPtr<FAsyncTask<FDeleteTask>> Delete(
            Request::FDeleteNamespaceRequestPtr Request
        );

        class GS2INVENTORY_API FCreateSimpleInventoryModelMasterTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Inventory::Domain::Model::FSimpleInventoryModelMasterDomain>,
            public TSharedFromThis<FCreateSimpleInventoryModelMasterTask>
        {
            const TSharedPtr<FNamespaceDomain> Self;
            const Request::FCreateSimpleInventoryModelMasterRequestPtr Request;
        public:
            explicit FCreateSimpleInventoryModelMasterTask(
                const TSharedPtr<FNamespaceDomain>& Self,
                const Request::FCreateSimpleInventoryModelMasterRequestPtr Request
            );

            FCreateSimpleInventoryModelMasterTask(
                const FCreateSimpleInventoryModelMasterTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Inventory::Domain::Model::FSimpleInventoryModelMasterDomain>> Result
            ) override;
        };
        friend FCreateSimpleInventoryModelMasterTask;

        TSharedPtr<FAsyncTask<FCreateSimpleInventoryModelMasterTask>> CreateSimpleInventoryModelMaster(
            Request::FCreateSimpleInventoryModelMasterRequestPtr Request
        );

        class GS2INVENTORY_API FCreateBigInventoryModelMasterTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Inventory::Domain::Model::FBigInventoryModelMasterDomain>,
            public TSharedFromThis<FCreateBigInventoryModelMasterTask>
        {
            const TSharedPtr<FNamespaceDomain> Self;
            const Request::FCreateBigInventoryModelMasterRequestPtr Request;
        public:
            explicit FCreateBigInventoryModelMasterTask(
                const TSharedPtr<FNamespaceDomain>& Self,
                const Request::FCreateBigInventoryModelMasterRequestPtr Request
            );

            FCreateBigInventoryModelMasterTask(
                const FCreateBigInventoryModelMasterTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Inventory::Domain::Model::FBigInventoryModelMasterDomain>> Result
            ) override;
        };
        friend FCreateBigInventoryModelMasterTask;

        TSharedPtr<FAsyncTask<FCreateBigInventoryModelMasterTask>> CreateBigInventoryModelMaster(
            Request::FCreateBigInventoryModelMasterRequestPtr Request
        );

        class GS2INVENTORY_API FCreateInventoryModelMasterTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Inventory::Domain::Model::FInventoryModelMasterDomain>,
            public TSharedFromThis<FCreateInventoryModelMasterTask>
        {
            const TSharedPtr<FNamespaceDomain> Self;
            const Request::FCreateInventoryModelMasterRequestPtr Request;
        public:
            explicit FCreateInventoryModelMasterTask(
                const TSharedPtr<FNamespaceDomain>& Self,
                const Request::FCreateInventoryModelMasterRequestPtr Request
            );

            FCreateInventoryModelMasterTask(
                const FCreateInventoryModelMasterTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Inventory::Domain::Model::FInventoryModelMasterDomain>> Result
            ) override;
        };
        friend FCreateInventoryModelMasterTask;

        TSharedPtr<FAsyncTask<FCreateInventoryModelMasterTask>> CreateInventoryModelMaster(
            Request::FCreateInventoryModelMasterRequestPtr Request
        );

        TSharedPtr<Gs2::Inventory::Domain::Model::FCurrentItemModelMasterDomain> CurrentItemModelMaster(
        );

        Gs2::Inventory::Domain::Iterator::FDescribeInventoryModelsIteratorPtr InventoryModels(
        ) const;

        Gs2::Core::Domain::CallbackID SubscribeInventoryModels(
            TFunction<void()> Callback
        );

        void UnsubscribeInventoryModels(
            Gs2::Core::Domain::CallbackID CallbackID
        );

        TSharedPtr<Gs2::Inventory::Domain::Model::FInventoryModelDomain> InventoryModel(
            const FString InventoryName
        );

        TSharedPtr<Gs2::Inventory::Domain::Model::FUserDomain> User(
            const FString UserId
        );

        TSharedPtr<Gs2::Inventory::Domain::Model::FUserAccessTokenDomain> AccessToken(
            Gs2::Auth::Model::FAccessTokenPtr AccessToken
        );

        Gs2::Inventory::Domain::Iterator::FDescribeSimpleInventoryModelMastersIteratorPtr SimpleInventoryModelMasters(
        ) const;

        Gs2::Core::Domain::CallbackID SubscribeSimpleInventoryModelMasters(
            TFunction<void()> Callback
        );

        void UnsubscribeSimpleInventoryModelMasters(
            Gs2::Core::Domain::CallbackID CallbackID
        );

        TSharedPtr<Gs2::Inventory::Domain::Model::FSimpleInventoryModelMasterDomain> SimpleInventoryModelMaster(
            const FString InventoryName
        );

        Gs2::Inventory::Domain::Iterator::FDescribeSimpleInventoryModelsIteratorPtr SimpleInventoryModels(
        ) const;

        Gs2::Core::Domain::CallbackID SubscribeSimpleInventoryModels(
            TFunction<void()> Callback
        );

        void UnsubscribeSimpleInventoryModels(
            Gs2::Core::Domain::CallbackID CallbackID
        );

        TSharedPtr<Gs2::Inventory::Domain::Model::FSimpleInventoryModelDomain> SimpleInventoryModel(
            const FString InventoryName
        );

        Gs2::Inventory::Domain::Iterator::FDescribeBigInventoryModelsIteratorPtr BigInventoryModels(
        ) const;

        Gs2::Core::Domain::CallbackID SubscribeBigInventoryModels(
            TFunction<void()> Callback
        );

        void UnsubscribeBigInventoryModels(
            Gs2::Core::Domain::CallbackID CallbackID
        );

        TSharedPtr<Gs2::Inventory::Domain::Model::FBigInventoryModelDomain> BigInventoryModel(
            const FString InventoryName
        );

        Gs2::Inventory::Domain::Iterator::FDescribeBigInventoryModelMastersIteratorPtr BigInventoryModelMasters(
        ) const;

        Gs2::Core::Domain::CallbackID SubscribeBigInventoryModelMasters(
            TFunction<void()> Callback
        );

        void UnsubscribeBigInventoryModelMasters(
            Gs2::Core::Domain::CallbackID CallbackID
        );

        TSharedPtr<Gs2::Inventory::Domain::Model::FBigInventoryModelMasterDomain> BigInventoryModelMaster(
            const FString InventoryName
        );

        Gs2::Inventory::Domain::Iterator::FDescribeInventoryModelMastersIteratorPtr InventoryModelMasters(
        ) const;

        Gs2::Core::Domain::CallbackID SubscribeInventoryModelMasters(
            TFunction<void()> Callback
        );

        void UnsubscribeInventoryModelMasters(
            Gs2::Core::Domain::CallbackID CallbackID
        );

        TSharedPtr<Gs2::Inventory::Domain::Model::FInventoryModelMasterDomain> InventoryModelMaster(
            const FString InventoryName
        );

        static FString CreateCacheParentKey(
            TOptional<FString> NamespaceName,
            FString ChildType
        );

        static FString CreateCacheKey(
            TOptional<FString> NamespaceName
        );

        class GS2INVENTORY_API FModelTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Inventory::Model::FNamespace>,
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
                TSharedPtr<TSharedPtr<Gs2::Inventory::Model::FNamespace>> Result
            ) override;
        };
        friend FModelTask;

        TSharedPtr<FAsyncTask<FModelTask>> Model();

        Gs2::Core::Domain::CallbackID Subscribe(
            TFunction<void(Gs2::Inventory::Model::FNamespacePtr)> Callback
        );

        void Unsubscribe(
            Gs2::Core::Domain::CallbackID CallbackID
        );

    };

    typedef TSharedPtr<FNamespaceDomain> FNamespaceDomainPtr;
}
