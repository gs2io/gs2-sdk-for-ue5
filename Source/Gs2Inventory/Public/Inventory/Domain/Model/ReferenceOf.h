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
#include "Inventory/Domain/Iterator/DescribeInventoriesIterator.h"
#include "Inventory/Domain/Iterator/DescribeInventoriesByUserIdIterator.h"
#include "Inventory/Domain/Iterator/DescribeItemSetsIterator.h"
#include "Inventory/Domain/Iterator/DescribeItemSetsByUserIdIterator.h"
#include "Inventory/Domain/Iterator/DescribeReferenceOfIterator.h"
#include "Inventory/Domain/Iterator/DescribeReferenceOfByUserIdIterator.h"

namespace Gs2::Inventory::Domain::Model
{
    class FNamespaceDomain;
    class FInventoryModelMasterDomain;
    class FInventoryModelDomain;
    class FItemModelMasterDomain;
    class FItemModelDomain;
    class FCurrentItemModelMasterDomain;
    class FInventoryDomain;
    class FInventoryAccessTokenDomain;
    class FItemSetDomain;
    class FItemSetAccessTokenDomain;
    class FReferenceOfDomain;
    class FReferenceOfAccessTokenDomain;
    class FUserDomain;
    class FUserAccessTokenDomain;
    class FItemSetEntry;

    class GS2INVENTORY_API FReferenceOfDomain:
        public TSharedFromThis<FReferenceOfDomain>
    {
        Core::Domain::FCacheDatabasePtr Cache;
        Gs2::Core::Domain::Model::FJobQueueDomainPtr JobQueueDomain;
        Gs2::Core::Domain::Model::FStampSheetConfigurationPtr StampSheetConfiguration;
        Gs2::Core::Net::Rest::FGs2RestSessionPtr Session;
        Gs2::Inventory::FGs2InventoryRestClientPtr Client;

        public:
        TOptional<FString> NamespaceName;
        TOptional<FString> UserId;
        TOptional<FString> InventoryName;
        TOptional<FString> ItemName;
        TOptional<FString> ItemSetName;
        TOptional<FString> ReferenceOf;
    private:

        FString ParentKey;

    public:

        FReferenceOfDomain(
            const Core::Domain::FCacheDatabasePtr Cache,
            const Gs2::Core::Domain::Model::FJobQueueDomainPtr JobQueueDomain,
            const Gs2::Core::Domain::Model::FStampSheetConfigurationPtr StampSheetConfiguration,
            const Gs2::Core::Net::Rest::FGs2RestSessionPtr Session,
            const TOptional<FString> NamespaceName,
            const TOptional<FString> UserId,
            const TOptional<FString> InventoryName,
            const TOptional<FString> ItemName,
            const TOptional<FString> ItemSetName,
            const TOptional<FString> ReferenceOf
            // ReSharper disable once CppMemberInitializersOrder
        );

        FReferenceOfDomain(
            const FReferenceOfDomain& From
        );

        class GS2INVENTORY_API FGetTask final :
            public Gs2::Core::Util::TGs2Future<TArray<FString>>,
            public TSharedFromThis<FGetTask>
        {
            const TSharedPtr<FReferenceOfDomain> Self;
            const Request::FGetReferenceOfByUserIdRequestPtr Request;
        public:
            explicit FGetTask(
                const TSharedPtr<FReferenceOfDomain> Self,
                const Request::FGetReferenceOfByUserIdRequestPtr Request
            );

            FGetTask(
                const FGetTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<TArray<FString>>> Result
            ) override;
        };
        friend FGetTask;

        TSharedPtr<FAsyncTask<FGetTask>> Get(
            Request::FGetReferenceOfByUserIdRequestPtr Request
        );

        class GS2INVENTORY_API FVerifyTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Inventory::Domain::Model::FReferenceOfDomain>,
            public TSharedFromThis<FVerifyTask>
        {
            const TSharedPtr<FReferenceOfDomain> Self;
            const Request::FVerifyReferenceOfByUserIdRequestPtr Request;
        public:
            explicit FVerifyTask(
                const TSharedPtr<FReferenceOfDomain> Self,
                const Request::FVerifyReferenceOfByUserIdRequestPtr Request
            );

            FVerifyTask(
                const FVerifyTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Inventory::Domain::Model::FReferenceOfDomain>> Result
            ) override;
        };
        friend FVerifyTask;

        TSharedPtr<FAsyncTask<FVerifyTask>> Verify(
            Request::FVerifyReferenceOfByUserIdRequestPtr Request
        );

        class GS2INVENTORY_API FDeleteTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Inventory::Domain::Model::FReferenceOfDomain>,
            public TSharedFromThis<FDeleteTask>
        {
            const TSharedPtr<FReferenceOfDomain> Self;
            const Request::FDeleteReferenceOfByUserIdRequestPtr Request;
        public:
            explicit FDeleteTask(
                const TSharedPtr<FReferenceOfDomain> Self,
                const Request::FDeleteReferenceOfByUserIdRequestPtr Request
            );

            FDeleteTask(
                const FDeleteTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Inventory::Domain::Model::FReferenceOfDomain>> Result
            ) override;
        };
        friend FDeleteTask;

        TSharedPtr<FAsyncTask<FDeleteTask>> Delete(
            Request::FDeleteReferenceOfByUserIdRequestPtr Request
        );

        static FString CreateCacheParentKey(
            TOptional<FString> NamespaceName,
            TOptional<FString> UserId,
            TOptional<FString> InventoryName,
            TOptional<FString> ItemName,
            TOptional<FString> ItemSetName,
            TOptional<FString> ReferenceOf,
            FString ChildType
        );

        static FString CreateCacheKey(
            TOptional<FString> ReferenceOf
        );

        class GS2INVENTORY_API FModelTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Inventory::Model::FItemSet>,
            public TSharedFromThis<FModelTask>
        {
            const TSharedPtr<FReferenceOfDomain> Self;
        public:
            explicit FModelTask(
                const TSharedPtr<FReferenceOfDomain> Self
            );

            FModelTask(
                const FModelTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Inventory::Model::FItemSet>> Result
            ) override;
        };
        friend FModelTask;

        TSharedPtr<FAsyncTask<FModelTask>> Model();

    };

    typedef TSharedPtr<FReferenceOfDomain> FReferenceOfDomainPtr;
}
