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
#include "Inventory/Domain/Model/SimpleItemAccessToken.h"
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
#include "Gs2InventoryEzSimpleItemGameSessionDomain.h"
#include "Inventory/Domain/Iterator/Gs2InventoryEzDescribeSimpleItemsIterator.h"
#include "Auth/Model/Gs2AuthEzAccessToken.h"
#include "Util/Profile.h"

namespace Gs2::UE5::Inventory::Domain::Model
{

    class EZGS2_API FEzSimpleItemGameSessionDomain final :
        public TSharedFromThis<FEzSimpleItemGameSessionDomain>
    {
        Gs2::Inventory::Domain::Model::FSimpleItemAccessTokenDomainPtr Domain;
        Gs2::UE5::Util::FProfilePtr ProfileValue;

        public:
        TOptional<FString> Body() const;
        TOptional<FString> Signature() const;
        TOptional<FString> NamespaceName() const;
        TOptional<FString> UserId() const;
        TOptional<FString> InventoryName() const;
        TOptional<FString> ItemName() const;

        FEzSimpleItemGameSessionDomain(
            Gs2::Inventory::Domain::Model::FSimpleItemAccessTokenDomainPtr Domain,
            Gs2::UE5::Util::FProfilePtr Profile
        );

        class FGetSimpleItemWithSignatureTask :
            public Gs2::Core::Util::TGs2Future<Gs2::UE5::Inventory::Domain::Model::FEzSimpleItemGameSessionDomain>,
            public TSharedFromThis<FGetSimpleItemWithSignatureTask>
        {
            TSharedPtr<FEzSimpleItemGameSessionDomain> Self;
            FString KeyId;

        public:
            explicit FGetSimpleItemWithSignatureTask(
                TSharedPtr<FEzSimpleItemGameSessionDomain> Self,
                FString KeyId
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::UE5::Inventory::Domain::Model::FEzSimpleItemGameSessionDomain>> Result
            ) override;
        };
        friend FGetSimpleItemWithSignatureTask;

        TSharedPtr<FAsyncTask<FGetSimpleItemWithSignatureTask>> GetSimpleItemWithSignature(
            FString KeyId
        );

        class FModelTask :
            public Gs2::Core::Util::TGs2Future<Gs2::UE5::Inventory::Model::FEzSimpleItem>,
            public TSharedFromThis<FModelTask>
        {
            TSharedPtr<FEzSimpleItemGameSessionDomain> Self;

        public:
            explicit FModelTask(
                TSharedPtr<FEzSimpleItemGameSessionDomain> Self
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<Gs2::UE5::Inventory::Model::FEzSimpleItemPtr> Result
            ) override;
        };

        TSharedPtr<FAsyncTask<FModelTask>> Model();

        Gs2::Core::Domain::CallbackID Subscribe(TFunction<void(Gs2::UE5::Inventory::Model::FEzSimpleItemPtr)> Callback);

        void Unsubscribe(Gs2::Core::Domain::CallbackID CallbackId);

    };
    typedef TSharedPtr<FEzSimpleItemGameSessionDomain> FEzSimpleItemGameSessionDomainPtr;
}
