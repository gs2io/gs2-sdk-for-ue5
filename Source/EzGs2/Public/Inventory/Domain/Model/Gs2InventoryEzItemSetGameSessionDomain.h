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

#pragma once

#include "CoreMinimal.h"
#include "Inventory/Domain/Model/ItemSetAccessToken.h"
#include "Inventory/Model/Gs2InventoryEzInventoryModel.h"
#include "Inventory/Model/Gs2InventoryEzItemModel.h"
#include "Inventory/Model/Gs2InventoryEzInventory.h"
#include "Inventory/Model/Gs2InventoryEzItemSet.h"
#include "Inventory/Model/Gs2InventoryEzSimpleInventoryModel.h"
#include "Inventory/Model/Gs2InventoryEzSimpleItemModel.h"
#include "Inventory/Model/Gs2InventoryEzSimpleItem.h"
#include "Inventory/Model/Gs2InventoryEzBigInventoryModel.h"
#include "Inventory/Model/Gs2InventoryEzBigItemModel.h"
#include "Inventory/Model/Gs2InventoryEzBigItem.h"
#include "Inventory/Model/Gs2InventoryEzBigInventoryModel.h"
#include "Inventory/Model/Gs2InventoryEzBigItemModel.h"
#include "Inventory/Model/Gs2InventoryEzBigItem.h"
#include "Inventory/Model/Gs2InventoryEzConsumeCount.h"
#include "Inventory/Model/Gs2InventoryEzAcquireCount.h"
#include "Gs2InventoryEzReferenceOfGameSessionDomain.h"
#include "Gs2InventoryEzItemSetGameSessionDomain.h"
#include "Inventory/Domain/Iterator/Gs2InventoryEzDescribeItemSetsIterator.h"
#include "Auth/Model/Gs2AuthEzAccessToken.h"
#include "Util/Profile.h"

namespace Gs2::UE5::Inventory::Domain::Model
{

    class EZGS2_API FEzItemSetGameSessionDomain final :
        public TSharedFromThis<FEzItemSetGameSessionDomain>
    {
        Gs2::Inventory::Domain::Model::FItemSetAccessTokenDomainPtr Domain;
        Gs2::UE5::Util::FProfilePtr ProfileValue;

        public:
        TOptional<FString> Body() const;
        TOptional<FString> Signature() const;
        TOptional<int64> OverflowCount() const;
        TOptional<FString> NamespaceName() const;
        TOptional<FString> UserId() const;
        TOptional<FString> InventoryName() const;
        TOptional<FString> ItemName() const;
        TOptional<FString> ItemSetName() const;

        FEzItemSetGameSessionDomain(
            Gs2::Inventory::Domain::Model::FItemSetAccessTokenDomainPtr Domain,
            Gs2::UE5::Util::FProfilePtr Profile
        );

        class FGetItemTask :
            public Gs2::Core::Util::TGs2Future<TArray<TSharedPtr<Gs2::UE5::Inventory::Model::FEzItemSet>>>,
            public TSharedFromThis<FGetItemTask>
        {
            TSharedPtr<FEzItemSetGameSessionDomain> Self;

        public:
            explicit FGetItemTask(
                TSharedPtr<FEzItemSetGameSessionDomain> Self
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<TArray<TSharedPtr<Gs2::UE5::Inventory::Model::FEzItemSet>>>> Result
            ) override;
        };
        friend FGetItemTask;

        TSharedPtr<FAsyncTask<FGetItemTask>> GetItem(
        );

        class FGetItemWithSignatureTask :
            public Gs2::Core::Util::TGs2Future<Gs2::UE5::Inventory::Domain::Model::FEzItemSetGameSessionDomain>,
            public TSharedFromThis<FGetItemWithSignatureTask>
        {
            TSharedPtr<FEzItemSetGameSessionDomain> Self;
            FString KeyId;

        public:
            explicit FGetItemWithSignatureTask(
                TSharedPtr<FEzItemSetGameSessionDomain> Self,
                FString KeyId
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::UE5::Inventory::Domain::Model::FEzItemSetGameSessionDomain>> Result
            ) override;
        };
        friend FGetItemWithSignatureTask;

        TSharedPtr<FAsyncTask<FGetItemWithSignatureTask>> GetItemWithSignature(
            FString KeyId
        );

        class FConsumeTask :
            public Gs2::Core::Util::TGs2Future<Gs2::UE5::Inventory::Domain::Model::FEzItemSetGameSessionDomain>,
            public TSharedFromThis<FConsumeTask>
        {
            TSharedPtr<FEzItemSetGameSessionDomain> Self;
            int64 ConsumeCount;

        public:
            explicit FConsumeTask(
                TSharedPtr<FEzItemSetGameSessionDomain> Self,
                int64 ConsumeCount
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::UE5::Inventory::Domain::Model::FEzItemSetGameSessionDomain>> Result
            ) override;
        };
        friend FConsumeTask;

        TSharedPtr<FAsyncTask<FConsumeTask>> Consume(
            int64 ConsumeCount
        );

        Gs2::UE5::Inventory::Domain::Model::FEzReferenceOfGameSessionDomainPtr ReferenceOf(
            const FString ReferenceOf
        ) const;

        class FModelTask :
            public Gs2::Core::Util::TGs2Future<TArray<Gs2::UE5::Inventory::Model::FEzItemSetPtr>>,
            public TSharedFromThis<FModelTask>
        {
            TSharedPtr<FEzItemSetGameSessionDomain> Self;

        public:
            explicit FModelTask(
                TSharedPtr<FEzItemSetGameSessionDomain> Self
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<TArray<Gs2::UE5::Inventory::Model::FEzItemSetPtr>>> Result
            ) override;
        };

        TSharedPtr<FAsyncTask<FModelTask>> Model();

    };
    typedef TSharedPtr<FEzItemSetGameSessionDomain> FEzItemSetGameSessionDomainPtr;
}
