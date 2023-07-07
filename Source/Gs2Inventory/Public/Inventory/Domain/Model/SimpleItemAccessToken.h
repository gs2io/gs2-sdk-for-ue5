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
#include "Inventory/Gs2Inventory.h"
#include "Inventory/Domain/Iterator/DescribeNamespacesIterator.h"
#include "Inventory/Domain/Iterator/DescribeInventoryModelMastersIterator.h"
#include "Inventory/Domain/Iterator/DescribeInventoryModelsIterator.h"
#include "Inventory/Domain/Iterator/DescribeItemModelMastersIterator.h"
#include "Inventory/Domain/Iterator/DescribeItemModelsIterator.h"
#include "Inventory/Domain/Iterator/DescribeSimpleInventoryModelMastersIterator.h"
#include "Inventory/Domain/Iterator/DescribeSimpleInventoryModelsIterator.h"
#include "Inventory/Domain/Iterator/DescribeSimpleItemModelMastersIterator.h"
#include "Inventory/Domain/Iterator/DescribeSimpleItemModelsIterator.h"
#include "Inventory/Domain/Iterator/DescribeInventoriesIterator.h"
#include "Inventory/Domain/Iterator/DescribeInventoriesByUserIdIterator.h"
#include "Inventory/Domain/Iterator/DescribeItemSetsIterator.h"
#include "Inventory/Domain/Iterator/DescribeItemSetsByUserIdIterator.h"
#include "Inventory/Domain/Iterator/DescribeReferenceOfIterator.h"
#include "Inventory/Domain/Iterator/DescribeReferenceOfByUserIdIterator.h"
#include "Inventory/Domain/Iterator/DescribeSimpleItemsIterator.h"
#include "Inventory/Domain/Iterator/DescribeSimpleItemsByUserIdIterator.h"

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
    class FUserDomain;
    class FUserAccessTokenDomain;
    class FItemSetEntry;

    class GS2INVENTORY_API FSimpleItemAccessTokenDomain:
        public TSharedFromThis<FSimpleItemAccessTokenDomain>
    {
        Core::Domain::FCacheDatabasePtr Cache;
        Gs2::Core::Domain::Model::FJobQueueDomainPtr JobQueueDomain;
        Gs2::Core::Domain::Model::FStampSheetConfigurationPtr StampSheetConfiguration;
        Gs2::Core::Net::Rest::FGs2RestSessionPtr Session;
        Gs2::Inventory::FGs2InventoryRestClientPtr Client;

        public:
        TOptional<FString> Body;
        TOptional<FString> Signature;
        TOptional<FString> GetBody() const
        {
            return Body;
        }
        TOptional<FString> GetSignature() const
        {
            return Signature;
        }
        TOptional<FString> NamespaceName;
        Gs2::Auth::Model::FAccessTokenPtr AccessToken;
        TOptional<FString> UserId() const { return AccessToken->GetUserId(); }
        TOptional<FString> InventoryName;
        TOptional<FString> ItemName;
    private:

        FString ParentKey;

    public:

        FSimpleItemAccessTokenDomain(
            const Core::Domain::FCacheDatabasePtr Cache,
            const Gs2::Core::Domain::Model::FJobQueueDomainPtr JobQueueDomain,
            const Gs2::Core::Domain::Model::FStampSheetConfigurationPtr StampSheetConfiguration,
            const Gs2::Core::Net::Rest::FGs2RestSessionPtr Session,
            const TOptional<FString> NamespaceName,
            const Gs2::Auth::Model::FAccessTokenPtr AccessToken,
            const TOptional<FString> InventoryName,
            const TOptional<FString> ItemName
            // ReSharper disable once CppMemberInitializersOrder
        );

        FSimpleItemAccessTokenDomain(
            const FSimpleItemAccessTokenDomain& From
        );

        class GS2INVENTORY_API FGetTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Inventory::Model::FSimpleItem>,
            public TSharedFromThis<FGetTask>
        {
            const TSharedPtr<FSimpleItemAccessTokenDomain> Self;
            const Request::FGetSimpleItemRequestPtr Request;
        public:
            explicit FGetTask(
                const TSharedPtr<FSimpleItemAccessTokenDomain> Self,
                const Request::FGetSimpleItemRequestPtr Request
            );

            FGetTask(
                const FGetTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Inventory::Model::FSimpleItem>> Result
            ) override;
        };
        friend FGetTask;

        TSharedPtr<FAsyncTask<FGetTask>> Get(
            Request::FGetSimpleItemRequestPtr Request
        );

        class GS2INVENTORY_API FGetWithSignatureTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Inventory::Domain::Model::FSimpleItemAccessTokenDomain>,
            public TSharedFromThis<FGetWithSignatureTask>
        {
            const TSharedPtr<FSimpleItemAccessTokenDomain> Self;
            const Request::FGetSimpleItemWithSignatureRequestPtr Request;
        public:
            explicit FGetWithSignatureTask(
                const TSharedPtr<FSimpleItemAccessTokenDomain> Self,
                const Request::FGetSimpleItemWithSignatureRequestPtr Request
            );

            FGetWithSignatureTask(
                const FGetWithSignatureTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Inventory::Domain::Model::FSimpleItemAccessTokenDomain>> Result
            ) override;
        };
        friend FGetWithSignatureTask;

        TSharedPtr<FAsyncTask<FGetWithSignatureTask>> GetWithSignature(
            Request::FGetSimpleItemWithSignatureRequestPtr Request
        );

        static FString CreateCacheParentKey(
            TOptional<FString> NamespaceName,
            TOptional<FString> UserId,
            TOptional<FString> InventoryName,
            TOptional<FString> ItemName,
            FString ChildType
        );

        static FString CreateCacheKey(
            TOptional<FString> ItemName
        );

        class GS2INVENTORY_API FModelTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Inventory::Model::FSimpleItem>,
            public TSharedFromThis<FModelTask>
        {
            const TSharedPtr<FSimpleItemAccessTokenDomain> Self;
        public:
            explicit FModelTask(
                const TSharedPtr<FSimpleItemAccessTokenDomain> Self
            );

            FModelTask(
                const FModelTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Inventory::Model::FSimpleItem>> Result
            ) override;
        };
        friend FModelTask;

        TSharedPtr<FAsyncTask<FModelTask>> Model();

    };

    typedef TSharedPtr<FSimpleItemAccessTokenDomain> FSimpleItemAccessTokenDomainPtr;
}
