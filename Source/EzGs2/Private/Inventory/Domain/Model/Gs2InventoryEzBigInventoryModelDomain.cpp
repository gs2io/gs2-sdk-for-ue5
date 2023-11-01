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

#include "Inventory/Domain/Model/Gs2InventoryEzBigInventoryModelDomain.h"

namespace Gs2::UE5::Inventory::Domain::Model
{

    TOptional<FString> FEzBigInventoryModelDomain::NamespaceName() const
    {
        return Domain->NamespaceName;
    }

    TOptional<FString> FEzBigInventoryModelDomain::InventoryName() const
    {
        return Domain->InventoryName;
    }

    FEzBigInventoryModelDomain::FEzBigInventoryModelDomain(
        Gs2::Inventory::Domain::Model::FBigInventoryModelDomainPtr Domain,
        Gs2::UE5::Util::FProfilePtr Profile
    ): Domain(Domain), ProfileValue(Profile) {

    }

    Gs2::UE5::Inventory::Domain::Iterator::FEzDescribeBigItemModelsIteratorPtr FEzBigInventoryModelDomain::BigItemModels(
    ) const
    {
        return MakeShared<Gs2::UE5::Inventory::Domain::Iterator::FEzDescribeBigItemModelsIterator>(
            Domain->BigItemModels(
            )
        );
    }

    Gs2::Core::Domain::CallbackID FEzBigInventoryModelDomain::SubscribeBigItemModels(TFunction<void()> Callback)
    {
        return Domain->SubscribeBigItemModels(
            Callback
        );
    }

    void FEzBigInventoryModelDomain::UnsubscribeBigItemModels(Gs2::Core::Domain::CallbackID CallbackId)
    {
        Domain->UnsubscribeBigItemModels(
            CallbackId
        );
    }

    Gs2::UE5::Inventory::Domain::Model::FEzBigItemModelDomainPtr FEzBigInventoryModelDomain::BigItemModel(
        const FString ItemName
    ) const
    {
        return MakeShared<Gs2::UE5::Inventory::Domain::Model::FEzBigItemModelDomain>(
            Domain->BigItemModel(
                ItemName
            ),
            ProfileValue
        );
    }

    FEzBigInventoryModelDomain::FModelTask::FModelTask(
        TSharedPtr<FEzBigInventoryModelDomain> Self
    ): Self(Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FEzBigInventoryModelDomain::FModelTask::Action(
        TSharedPtr<Gs2::UE5::Inventory::Model::FEzBigInventoryModelPtr> Result
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
                *Result = Gs2::UE5::Inventory::Model::FEzBigInventoryModel::FromModel(Task->GetTask().Result());
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

    TSharedPtr<FAsyncTask<FEzBigInventoryModelDomain::FModelTask>> FEzBigInventoryModelDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FModelTask>>(this->AsShared());
    }

    Gs2::Core::Domain::CallbackID FEzBigInventoryModelDomain::Subscribe(TFunction<void(Gs2::UE5::Inventory::Model::FEzBigInventoryModelPtr)> Callback)
    {
        return Domain->Subscribe(
            [&](Gs2::Inventory::Model::FBigInventoryModelPtr Item)
            {
                Callback(Gs2::UE5::Inventory::Model::FEzBigInventoryModel::FromModel(Item));
            }
        );
    }

    void FEzBigInventoryModelDomain::Unsubscribe(Gs2::Core::Domain::CallbackID CallbackId)
    {
        Domain->Unsubscribe(
            CallbackId
        );
    }
}
