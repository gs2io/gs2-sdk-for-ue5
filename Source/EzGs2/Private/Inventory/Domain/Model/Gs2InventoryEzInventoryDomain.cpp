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

#include "Inventory/Domain/Model/Gs2InventoryEzInventoryDomain.h"

namespace Gs2::UE5::Inventory::Domain::Model
{

    TOptional<int64> FEzInventoryDomain::OverflowCount() const
    {
        return Domain->OverflowCount;
    }

    TOptional<FString> FEzInventoryDomain::NextPageToken() const
    {
        return Domain->NextPageToken;
    }

    TOptional<FString> FEzInventoryDomain::NamespaceName() const
    {
        return Domain->NamespaceName;
    }

    TOptional<FString> FEzInventoryDomain::UserId() const
    {
        return Domain->UserId;
    }

    TOptional<FString> FEzInventoryDomain::InventoryName() const
    {
        return Domain->InventoryName;
    }

    FEzInventoryDomain::FEzInventoryDomain(
        Gs2::Inventory::Domain::Model::FInventoryDomainPtr Domain,
        Gs2::UE5::Util::FProfilePtr Profile
    ): Domain(Domain), ProfileValue(Profile) {

    }

    Gs2::UE5::Inventory::Domain::Model::FEzItemSetDomainPtr FEzInventoryDomain::ItemSet(
        const FString ItemName,
        const TOptional<FString> ItemSetName
    ) const
    {
        return MakeShared<Gs2::UE5::Inventory::Domain::Model::FEzItemSetDomain>(
            Domain->ItemSet(
                ItemName,
                ItemSetName
            ),
            ProfileValue
        );
    }

    FEzInventoryDomain::FModelTask::FModelTask(
        TSharedPtr<FEzInventoryDomain> Self
    ): Self(Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FEzInventoryDomain::FModelTask::Action(
        TSharedPtr<Gs2::UE5::Inventory::Model::FEzInventoryPtr> Result
    )
    {
        const auto Future = Self->ProfileValue->Run<FModelTask>(
            [&]() -> Gs2::Core::Model::FGs2ErrorPtr {
                const auto Task = Self->Domain->Model();
                Task->StartSynchronousTask();
                if (Task->GetTask().IsError())
                {
                    Task->EnsureCompletion();
                    return Task->GetTask().Error();
                }
                *Result = Gs2::UE5::Inventory::Model::FEzInventory::FromModel(Task->GetTask().Result());
                Task->EnsureCompletion();
                return nullptr;
            },
            nullptr
        );
        Future->StartSynchronousTask();
        if (Future->GetTask().IsError())
        {
            Future->EnsureCompletion();
            return Future->GetTask().Error();
        }
        Future->EnsureCompletion();
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FEzInventoryDomain::FModelTask>> FEzInventoryDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FModelTask>>(this->AsShared());
    }

    Gs2::Core::Domain::CallbackID FEzInventoryDomain::Subscribe(TFunction<void(Gs2::UE5::Inventory::Model::FEzInventoryPtr)> Callback)
    {
        return Domain->Subscribe(
            [&](Gs2::Inventory::Model::FInventoryPtr Item)
            {
                Callback(Gs2::UE5::Inventory::Model::FEzInventory::FromModel(Item));
            }
        );
    }

    void FEzInventoryDomain::Unsubscribe(Gs2::Core::Domain::CallbackID CallbackId)
    {
        Domain->Unsubscribe(
            CallbackId
        );
    }
}
