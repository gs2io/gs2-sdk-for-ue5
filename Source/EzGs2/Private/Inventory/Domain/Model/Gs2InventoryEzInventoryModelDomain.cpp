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

#include "Inventory/Domain/Model/Gs2InventoryEzInventoryModelDomain.h"

namespace Gs2::UE5::Inventory::Domain::Model
{

    TOptional<FString> FEzInventoryModelDomain::NamespaceName() const
    {
        return Domain->NamespaceName;
    }

    TOptional<FString> FEzInventoryModelDomain::InventoryName() const
    {
        return Domain->InventoryName;
    }

    FEzInventoryModelDomain::FEzInventoryModelDomain(
        Gs2::Inventory::Domain::Model::FInventoryModelDomainPtr Domain,
        Gs2::UE5::Util::FProfilePtr Profile
    ): Domain(Domain), ProfileValue(Profile) {

    }

    FEzInventoryModelDomain::FGetInventoryModelTask::FGetInventoryModelTask(
        TSharedPtr<FEzInventoryModelDomain> Self
    ): Self(Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FEzInventoryModelDomain::FGetInventoryModelTask::Action(
        TSharedPtr<TSharedPtr<Gs2::UE5::Inventory::Model::FEzInventoryModel>> Result
    )
    {
        const auto Future = Self->ProfileValue->Run<FGetInventoryModelTask>(
            [&]() -> Gs2::Core::Model::FGs2ErrorPtr {
                const auto Task = Self->Domain->Get(
                    MakeShared<Gs2::Inventory::Request::FGetInventoryModelRequest>()
                );
                Task->StartSynchronousTask();
                if (Task->GetTask().IsError())
                {
                    Task->EnsureCompletion();
                    return Task->GetTask().Error();
                }
                *Result = Gs2::UE5::Inventory::Model::FEzInventoryModel::FromModel(
                    Task->GetTask().Result()
                );
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

    TSharedPtr<FAsyncTask<FEzInventoryModelDomain::FGetInventoryModelTask>> FEzInventoryModelDomain::GetInventoryModel(
    )
    {
        return Gs2::Core::Util::New<FAsyncTask<FGetInventoryModelTask>>(
            this->AsShared()
        );
    }

    Gs2::UE5::Inventory::Domain::Iterator::FEzDescribeItemModelsIteratorPtr FEzInventoryModelDomain::ItemModels(
    ) const
    {
        return MakeShared<Gs2::UE5::Inventory::Domain::Iterator::FEzDescribeItemModelsIterator>(
            Domain->ItemModels(
            )
        );
    }

    Gs2::UE5::Inventory::Domain::Model::FEzItemModelDomainPtr FEzInventoryModelDomain::ItemModel(
        const FString ItemName
    ) const
    {
        return MakeShared<Gs2::UE5::Inventory::Domain::Model::FEzItemModelDomain>(
            Domain->ItemModel(
                ItemName
            ),
            ProfileValue
        );
    }

    FEzInventoryModelDomain::FModelTask::FModelTask(
        TSharedPtr<FEzInventoryModelDomain> Self
    ): Self(Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FEzInventoryModelDomain::FModelTask::Action(
        TSharedPtr<Gs2::UE5::Inventory::Model::FEzInventoryModelPtr> Result
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
                *Result = Gs2::UE5::Inventory::Model::FEzInventoryModel::FromModel(Task->GetTask().Result());
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

    TSharedPtr<FAsyncTask<FEzInventoryModelDomain::FModelTask>> FEzInventoryModelDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FModelTask>>(this->AsShared());
    }
}
