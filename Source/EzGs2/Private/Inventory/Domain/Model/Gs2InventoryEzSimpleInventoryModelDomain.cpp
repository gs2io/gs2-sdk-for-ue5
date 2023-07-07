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

#include "Inventory/Domain/Model/Gs2InventoryEzSimpleInventoryModelDomain.h"

namespace Gs2::UE5::Inventory::Domain::Model
{

    TOptional<FString> FEzSimpleInventoryModelDomain::NamespaceName() const
    {
        return Domain->NamespaceName;
    }

    TOptional<FString> FEzSimpleInventoryModelDomain::InventoryName() const
    {
        return Domain->InventoryName;
    }

    FEzSimpleInventoryModelDomain::FEzSimpleInventoryModelDomain(
        Gs2::Inventory::Domain::Model::FSimpleInventoryModelDomainPtr Domain,
        Gs2::UE5::Util::FProfilePtr Profile
    ): Domain(Domain), ProfileValue(Profile) {

    }

    FEzSimpleInventoryModelDomain::FGetSimpleInventoryModelTask::FGetSimpleInventoryModelTask(
        TSharedPtr<FEzSimpleInventoryModelDomain> Self
    ): Self(Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FEzSimpleInventoryModelDomain::FGetSimpleInventoryModelTask::Action(
        TSharedPtr<TSharedPtr<Gs2::UE5::Inventory::Model::FEzSimpleInventoryModel>> Result
    )
    {
        const auto Future = Self->ProfileValue->Run<FGetSimpleInventoryModelTask>(
            [&]() -> Gs2::Core::Model::FGs2ErrorPtr {
                const auto Task = Self->Domain->Get(
                    MakeShared<Gs2::Inventory::Request::FGetSimpleInventoryModelRequest>()
                );
                Task->StartSynchronousTask();
                if (Task->GetTask().IsError())
                {
                    Task->EnsureCompletion();
                    return Task->GetTask().Error();
                }
                *Result = Gs2::UE5::Inventory::Model::FEzSimpleInventoryModel::FromModel(
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

    TSharedPtr<FAsyncTask<FEzSimpleInventoryModelDomain::FGetSimpleInventoryModelTask>> FEzSimpleInventoryModelDomain::GetSimpleInventoryModel(
    )
    {
        return Gs2::Core::Util::New<FAsyncTask<FGetSimpleInventoryModelTask>>(
            this->AsShared()
        );
    }

    Gs2::UE5::Inventory::Domain::Iterator::FEzDescribeSimpleItemModelsIteratorPtr FEzSimpleInventoryModelDomain::SimpleItemModels(
    ) const
    {
        return MakeShared<Gs2::UE5::Inventory::Domain::Iterator::FEzDescribeSimpleItemModelsIterator>(
            Domain->SimpleItemModels(
            )
        );
    }

    Gs2::UE5::Inventory::Domain::Model::FEzSimpleItemModelDomainPtr FEzSimpleInventoryModelDomain::SimpleItemModel(
        const FString ItemName
    ) const
    {
        return MakeShared<Gs2::UE5::Inventory::Domain::Model::FEzSimpleItemModelDomain>(
            Domain->SimpleItemModel(
                ItemName
            ),
            ProfileValue
        );
    }

    FEzSimpleInventoryModelDomain::FModelTask::FModelTask(
        TSharedPtr<FEzSimpleInventoryModelDomain> Self
    ): Self(Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FEzSimpleInventoryModelDomain::FModelTask::Action(
        TSharedPtr<Gs2::UE5::Inventory::Model::FEzSimpleInventoryModelPtr> Result
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
                *Result = Gs2::UE5::Inventory::Model::FEzSimpleInventoryModel::FromModel(Task->GetTask().Result());
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

    TSharedPtr<FAsyncTask<FEzSimpleInventoryModelDomain::FModelTask>> FEzSimpleInventoryModelDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FModelTask>>(this->AsShared());
    }
}
