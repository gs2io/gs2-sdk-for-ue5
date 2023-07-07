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

#include "Inventory/Domain/Model/Gs2InventoryEzSimpleItemModelDomain.h"

namespace Gs2::UE5::Inventory::Domain::Model
{

    TOptional<FString> FEzSimpleItemModelDomain::NamespaceName() const
    {
        return Domain->NamespaceName;
    }

    TOptional<FString> FEzSimpleItemModelDomain::InventoryName() const
    {
        return Domain->InventoryName;
    }

    TOptional<FString> FEzSimpleItemModelDomain::ItemName() const
    {
        return Domain->ItemName;
    }

    FEzSimpleItemModelDomain::FEzSimpleItemModelDomain(
        Gs2::Inventory::Domain::Model::FSimpleItemModelDomainPtr Domain,
        Gs2::UE5::Util::FProfilePtr Profile
    ): Domain(Domain), ProfileValue(Profile) {

    }

    FEzSimpleItemModelDomain::FGetSimpleItemModelTask::FGetSimpleItemModelTask(
        TSharedPtr<FEzSimpleItemModelDomain> Self
    ): Self(Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FEzSimpleItemModelDomain::FGetSimpleItemModelTask::Action(
        TSharedPtr<TSharedPtr<Gs2::UE5::Inventory::Model::FEzSimpleItemModel>> Result
    )
    {
        const auto Future = Self->ProfileValue->Run<FGetSimpleItemModelTask>(
            [&]() -> Gs2::Core::Model::FGs2ErrorPtr {
                const auto Task = Self->Domain->Get(
                    MakeShared<Gs2::Inventory::Request::FGetSimpleItemModelRequest>()
                );
                Task->StartSynchronousTask();
                if (Task->GetTask().IsError())
                {
                    Task->EnsureCompletion();
                    return Task->GetTask().Error();
                }
                *Result = Gs2::UE5::Inventory::Model::FEzSimpleItemModel::FromModel(
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

    TSharedPtr<FAsyncTask<FEzSimpleItemModelDomain::FGetSimpleItemModelTask>> FEzSimpleItemModelDomain::GetSimpleItemModel(
    )
    {
        return Gs2::Core::Util::New<FAsyncTask<FGetSimpleItemModelTask>>(
            this->AsShared()
        );
    }

    FEzSimpleItemModelDomain::FModelTask::FModelTask(
        TSharedPtr<FEzSimpleItemModelDomain> Self
    ): Self(Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FEzSimpleItemModelDomain::FModelTask::Action(
        TSharedPtr<Gs2::UE5::Inventory::Model::FEzSimpleItemModelPtr> Result
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
                *Result = Gs2::UE5::Inventory::Model::FEzSimpleItemModel::FromModel(Task->GetTask().Result());
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

    TSharedPtr<FAsyncTask<FEzSimpleItemModelDomain::FModelTask>> FEzSimpleItemModelDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FModelTask>>(this->AsShared());
    }
}
