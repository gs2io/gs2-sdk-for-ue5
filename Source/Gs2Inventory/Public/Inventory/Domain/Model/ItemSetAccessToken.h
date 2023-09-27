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
#include "Inventory/Gs2Inventory.h"
#include "Inventory/Domain/Model/ItemSetEntry.h"
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

    class GS2INVENTORY_API FItemSetAccessTokenDomain:
        public TSharedFromThis<FItemSetAccessTokenDomain>
    {
        Core::Domain::FCacheDatabasePtr Cache;
        Gs2::Core::Domain::Model::FJobQueueDomainPtr JobQueueDomain;
        Gs2::Core::Domain::Model::FStampSheetConfigurationPtr StampSheetConfiguration;
        Gs2::Core::Net::Rest::FGs2RestSessionPtr Session;
        Gs2::Inventory::FGs2InventoryRestClientPtr Client;

        public:
        TOptional<FString> Body;
        TOptional<FString> Signature;
        TOptional<int64> OverflowCount;
        TOptional<FString> GetBody() const
        {
            return Body;
        }
        TOptional<FString> GetSignature() const
        {
            return Signature;
        }
        TOptional<int64> GetOverflowCount() const
        {
            return OverflowCount;
        }
        TOptional<FString> NamespaceName;
        Gs2::Auth::Model::FAccessTokenPtr AccessToken;
        TOptional<FString> UserId() const { return AccessToken->GetUserId(); }
        TOptional<FString> InventoryName;
        TOptional<FString> ItemName;
        TOptional<FString> ItemSetName;
    private:

        FString ParentKey;

    public:

        FItemSetAccessTokenDomain(
            const Core::Domain::FCacheDatabasePtr Cache,
            const Gs2::Core::Domain::Model::FJobQueueDomainPtr JobQueueDomain,
            const Gs2::Core::Domain::Model::FStampSheetConfigurationPtr StampSheetConfiguration,
            const Gs2::Core::Net::Rest::FGs2RestSessionPtr Session,
            const TOptional<FString> NamespaceName,
            const Gs2::Auth::Model::FAccessTokenPtr AccessToken,
            const TOptional<FString> InventoryName,
            const TOptional<FString> ItemName,
            const TOptional<FString> ItemSetName
            // ReSharper disable once CppMemberInitializersOrder
        );

        FItemSetAccessTokenDomain(
            const FItemSetAccessTokenDomain& From
        );

        class GS2INVENTORY_API FGetTask final :
            public Gs2::Core::Util::TGs2Future<TArray<TSharedPtr<Gs2::Inventory::Model::FItemSet>>>,
            public TSharedFromThis<FGetTask>
        {
            const TSharedPtr<FItemSetAccessTokenDomain> Self;
            const Request::FGetItemSetRequestPtr Request;
        public:
            explicit FGetTask(
                const TSharedPtr<FItemSetAccessTokenDomain> Self,
                const Request::FGetItemSetRequestPtr Request
            );

            FGetTask(
                const FGetTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<TArray<TSharedPtr<Gs2::Inventory::Model::FItemSet>>>> Result
            ) override;
        };
        friend FGetTask;

        TSharedPtr<FAsyncTask<FGetTask>> Get(
            Request::FGetItemSetRequestPtr Request
        );

        class GS2INVENTORY_API FGetItemWithSignatureTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Inventory::Domain::Model::FItemSetAccessTokenDomain>,
            public TSharedFromThis<FGetItemWithSignatureTask>
        {
            const TSharedPtr<FItemSetAccessTokenDomain> Self;
            const Request::FGetItemWithSignatureRequestPtr Request;
        public:
            explicit FGetItemWithSignatureTask(
                const TSharedPtr<FItemSetAccessTokenDomain> Self,
                const Request::FGetItemWithSignatureRequestPtr Request
            );

            FGetItemWithSignatureTask(
                const FGetItemWithSignatureTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Inventory::Domain::Model::FItemSetAccessTokenDomain>> Result
            ) override;
        };
        friend FGetItemWithSignatureTask;

        TSharedPtr<FAsyncTask<FGetItemWithSignatureTask>> GetItemWithSignature(
            Request::FGetItemWithSignatureRequestPtr Request
        );

        class GS2INVENTORY_API FConsumeTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Inventory::Domain::Model::FItemSetAccessTokenDomain>,
            public TSharedFromThis<FConsumeTask>
        {
            const TSharedPtr<FItemSetAccessTokenDomain> Self;
            const Request::FConsumeItemSetRequestPtr Request;
        public:
            explicit FConsumeTask(
                const TSharedPtr<FItemSetAccessTokenDomain> Self,
                const Request::FConsumeItemSetRequestPtr Request
            );

            FConsumeTask(
                const FConsumeTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Inventory::Domain::Model::FItemSetAccessTokenDomain>> Result
            ) override;
        };
        friend FConsumeTask;

        TSharedPtr<FAsyncTask<FConsumeTask>> Consume(
            Request::FConsumeItemSetRequestPtr Request
        );

        class GS2INVENTORY_API FAddReferenceOfTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Inventory::Domain::Model::FReferenceOfAccessTokenDomain>,
            public TSharedFromThis<FAddReferenceOfTask>
        {
            const TSharedPtr<FItemSetAccessTokenDomain> Self;
            const Request::FAddReferenceOfRequestPtr Request;
        public:
            explicit FAddReferenceOfTask(
                const TSharedPtr<FItemSetAccessTokenDomain> Self,
                const Request::FAddReferenceOfRequestPtr Request
            );

            FAddReferenceOfTask(
                const FAddReferenceOfTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Inventory::Domain::Model::FReferenceOfAccessTokenDomain>> Result
            ) override;
        };
        friend FAddReferenceOfTask;

        TSharedPtr<FAsyncTask<FAddReferenceOfTask>> AddReferenceOf(
            Request::FAddReferenceOfRequestPtr Request
        );

        Gs2::Inventory::Domain::Iterator::FDescribeReferenceOfIteratorPtr ReferenceOves(
        ) const;

        TSharedPtr<Gs2::Inventory::Domain::Model::FReferenceOfAccessTokenDomain> ReferenceOf(
            const FString ReferenceOf
        ) const;

        static FString CreateCacheParentKey(
            TOptional<FString> NamespaceName,
            TOptional<FString> UserId,
            TOptional<FString> InventoryName,
            TOptional<FString> ItemName,
            TOptional<FString> ItemSetName,
            FString ChildType
        );

        static FString CreateCacheKey(
            TOptional<FString> ItemName,
            TOptional<FString> ItemSetName
        );

        class GS2INVENTORY_API FModelTask final :
            public Gs2::Core::Util::TGs2Future<TArray<Gs2::Inventory::Model::FItemSetPtr>>,
            public TSharedFromThis<FModelTask>
        {
            const TSharedPtr<FItemSetAccessTokenDomain> Self;
        public:
            explicit FModelTask(
                const TSharedPtr<FItemSetAccessTokenDomain> Self
            );

            FModelTask(
                const FModelTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<TArray<Gs2::Inventory::Model::FItemSetPtr>>> Result
            ) override;
        };
        friend FModelTask;

        TSharedPtr<FAsyncTask<FModelTask>> Model();

        Gs2::Core::Domain::CallbackID Subscribe(
            TFunction<void(TSharedPtr<Gs2::Inventory::Model::FItemSetEntry>)> Callback
        );

        void Unsubscribe(
            Gs2::Core::Domain::CallbackID CallbackID
        );

    };

    typedef TSharedPtr<FItemSetAccessTokenDomain> FItemSetAccessTokenDomainPtr;
}
