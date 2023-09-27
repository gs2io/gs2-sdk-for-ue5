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

#include "Inventory/Domain/Model/Gs2InventoryEzItemSetDomain.h"

namespace Gs2::UE5::Inventory::Domain::Model
{

    TOptional<FString> FEzItemSetDomain::Body() const
    {
        return Domain->Body;
    }

    TOptional<FString> FEzItemSetDomain::Signature() const
    {
        return Domain->Signature;
    }

    TOptional<int64> FEzItemSetDomain::OverflowCount() const
    {
        return Domain->OverflowCount;
    }

    TOptional<FString> FEzItemSetDomain::NamespaceName() const
    {
        return Domain->NamespaceName;
    }

    TOptional<FString> FEzItemSetDomain::UserId() const
    {
        return Domain->UserId;
    }

    TOptional<FString> FEzItemSetDomain::InventoryName() const
    {
        return Domain->InventoryName;
    }

    TOptional<FString> FEzItemSetDomain::ItemName() const
    {
        return Domain->ItemName;
    }

    TOptional<FString> FEzItemSetDomain::ItemSetName() const
    {
        return Domain->ItemSetName;
    }

    FEzItemSetDomain::FEzItemSetDomain(
        Gs2::Inventory::Domain::Model::FItemSetDomainPtr Domain,
        Gs2::UE5::Util::FProfilePtr Profile
    ): Domain(Domain), ProfileValue(Profile) {

    }

    FEzItemSetDomain::FModelTask::FModelTask(
        TSharedPtr<FEzItemSetDomain> Self
    ): Self(Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FEzItemSetDomain::FModelTask::Action(
        TSharedPtr<TSharedPtr<TArray<Gs2::UE5::Inventory::Model::FEzItemSetPtr>>> Result
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
                *Result = MakeShared<TArray<Gs2::UE5::Inventory::Model::FEzItemSetPtr>>();
                for (auto Value : *Task->GetTask().Result()) {
                    (**Result).Add(Gs2::UE5::Inventory::Model::FEzItemSet::FromModel(Value));
                }
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

    TSharedPtr<FAsyncTask<FEzItemSetDomain::FModelTask>> FEzItemSetDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FModelTask>>(this->AsShared());
    }

    Gs2::Core::Domain::CallbackID FEzItemSetDomain::Subscribe(TFunction<void(TArray<Gs2::UE5::Inventory::Model::FEzItemSetPtr>)> Callback)
    {
        return Domain->Subscribe(
            [&](Gs2::Inventory::Model::FItemSetEntryPtr Item)
            {
                TArray<Gs2::UE5::Inventory::Model::FEzItemSetPtr> Arr;
                for (auto ItemSet : Item->Value)
                {
                    Arr.Add(Gs2::UE5::Inventory::Model::FEzItemSet::FromModel(ItemSet));
                }
                Callback(Arr);
            }
        );
    }

    void FEzItemSetDomain::Unsubscribe(Gs2::Core::Domain::CallbackID CallbackId)
    {
        Domain->Unsubscribe(
            CallbackId
        );
    }
}
