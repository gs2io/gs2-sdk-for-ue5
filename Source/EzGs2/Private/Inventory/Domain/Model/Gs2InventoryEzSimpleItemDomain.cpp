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

#include "Inventory/Domain/Model/Gs2InventoryEzSimpleItemDomain.h"

namespace Gs2::UE5::Inventory::Domain::Model
{

    TOptional<FString> FEzSimpleItemDomain::Body() const
    {
        return Domain->Body;
    }

    TOptional<FString> FEzSimpleItemDomain::Signature() const
    {
        return Domain->Signature;
    }

    TOptional<FString> FEzSimpleItemDomain::NamespaceName() const
    {
        return Domain->NamespaceName;
    }

    TOptional<FString> FEzSimpleItemDomain::UserId() const
    {
        return Domain->UserId;
    }

    TOptional<FString> FEzSimpleItemDomain::InventoryName() const
    {
        return Domain->InventoryName;
    }

    TOptional<FString> FEzSimpleItemDomain::ItemName() const
    {
        return Domain->ItemName;
    }

    FEzSimpleItemDomain::FEzSimpleItemDomain(
        Gs2::Inventory::Domain::Model::FSimpleItemDomainPtr Domain,
        Gs2::UE5::Util::FGs2ConnectionPtr Connection
    ):
        Domain(Domain),
        ConnectionValue(Connection)
    {

    }

    FEzSimpleItemDomain::FModelTask::FModelTask(
        TSharedPtr<FEzSimpleItemDomain> Self
    ): Self(Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FEzSimpleItemDomain::FModelTask::Action(
        TSharedPtr<Gs2::UE5::Inventory::Model::FEzSimpleItemPtr> Result
    )
    {
        const auto Future = Self->ConnectionValue->Run(
            [&]() -> Gs2::Core::Model::FGs2ErrorPtr {
                const auto Task = Self->Domain->Model();
                Task->StartSynchronousTask();
                if (Task->GetTask().IsError())
                {
                    Task->EnsureCompletion();
                    return Task->GetTask().Error();
                }
                *Result = Gs2::UE5::Inventory::Model::FEzSimpleItem::FromModel(Task->GetTask().Result());
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

    TSharedPtr<FAsyncTask<FEzSimpleItemDomain::FModelTask>> FEzSimpleItemDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FModelTask>>(this->AsShared());
    }

    Gs2::Core::Domain::CallbackID FEzSimpleItemDomain::Subscribe(TFunction<void(Gs2::UE5::Inventory::Model::FEzSimpleItemPtr)> Callback)
    {
        return Domain->Subscribe(
            [&](Gs2::Inventory::Model::FSimpleItemPtr Item)
            {
                Callback(Gs2::UE5::Inventory::Model::FEzSimpleItem::FromModel(Item));
            }
        );
    }

    void FEzSimpleItemDomain::Unsubscribe(Gs2::Core::Domain::CallbackID CallbackId)
    {
        Domain->Unsubscribe(
            CallbackId
        );
    }
}
