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

#include "Inventory/Domain/Model/Gs2InventoryEzBigItemGameSessionDomain.h"

namespace Gs2::UE5::Inventory::Domain::Model
{

    TOptional<FString> FEzBigItemGameSessionDomain::NamespaceName() const
    {
        return Domain->NamespaceName;
    }

    TOptional<FString> FEzBigItemGameSessionDomain::UserId() const
    {
        return Domain->UserId();
    }

    TOptional<FString> FEzBigItemGameSessionDomain::InventoryName() const
    {
        return Domain->InventoryName;
    }

    TOptional<FString> FEzBigItemGameSessionDomain::ItemName() const
    {
        return Domain->ItemName;
    }

    FEzBigItemGameSessionDomain::FEzBigItemGameSessionDomain(
        Gs2::Inventory::Domain::Model::FBigItemAccessTokenDomainPtr Domain,
        Gs2::UE5::Util::FProfilePtr Profile
    ): Domain(Domain), ProfileValue(Profile) {

    }

    FEzBigItemGameSessionDomain::FConsumeBigItemTask::FConsumeBigItemTask(
        TSharedPtr<FEzBigItemGameSessionDomain> Self,
        FString ConsumeCount
    ): Self(Self), ConsumeCount(ConsumeCount)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FEzBigItemGameSessionDomain::FConsumeBigItemTask::Action(
        TSharedPtr<TSharedPtr<Gs2::UE5::Inventory::Domain::Model::FEzBigItemGameSessionDomain>> Result
    )
    {
        const auto Future = Self->ProfileValue->Run<FConsumeBigItemTask>(
            [&]() -> Gs2::Core::Model::FGs2ErrorPtr {
                const auto Task = Self->Domain->Consume(
                    MakeShared<Gs2::Inventory::Request::FConsumeBigItemRequest>()
                        ->WithConsumeCount(ConsumeCount)
                );
                Task->StartSynchronousTask();
                if (Task->GetTask().IsError())
                {
                    Task->EnsureCompletion();
                    return Task->GetTask().Error();
                }
                *Result = MakeShared<Gs2::UE5::Inventory::Domain::Model::FEzBigItemGameSessionDomain>(
                    Task->GetTask().Result(),
                    Self->ProfileValue
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

    TSharedPtr<FAsyncTask<FEzBigItemGameSessionDomain::FConsumeBigItemTask>> FEzBigItemGameSessionDomain::ConsumeBigItem(
        FString ConsumeCount
    )
    {
        return Gs2::Core::Util::New<FAsyncTask<FConsumeBigItemTask>>(
            this->AsShared(),
            ConsumeCount
        );
    }

    FEzBigItemGameSessionDomain::FModelTask::FModelTask(
        TSharedPtr<FEzBigItemGameSessionDomain> Self
    ): Self(Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FEzBigItemGameSessionDomain::FModelTask::Action(
        TSharedPtr<Gs2::UE5::Inventory::Model::FEzBigItemPtr> Result
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
                *Result = Gs2::UE5::Inventory::Model::FEzBigItem::FromModel(Task->GetTask().Result());
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

    TSharedPtr<FAsyncTask<FEzBigItemGameSessionDomain::FModelTask>> FEzBigItemGameSessionDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FModelTask>>(this->AsShared());
    }

    Gs2::Core::Domain::CallbackID FEzBigItemGameSessionDomain::Subscribe(TFunction<void(Gs2::UE5::Inventory::Model::FEzBigItemPtr)> Callback)
    {
        return Domain->Subscribe(
            [&](Gs2::Inventory::Model::FBigItemPtr Item)
            {
                Callback(Gs2::UE5::Inventory::Model::FEzBigItem::FromModel(Item));
            }
        );
    }

    void FEzBigItemGameSessionDomain::Unsubscribe(Gs2::Core::Domain::CallbackID CallbackId)
    {
        Domain->Unsubscribe(
            CallbackId
        );
    }
}
