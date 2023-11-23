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

#include "Inventory/Domain/Model/Gs2InventoryEzSimpleItemGameSessionDomain.h"

namespace Gs2::UE5::Inventory::Domain::Model
{

    TOptional<FString> FEzSimpleItemGameSessionDomain::Body() const
    {
        return Domain->Body;
    }

    TOptional<FString> FEzSimpleItemGameSessionDomain::Signature() const
    {
        return Domain->Signature;
    }

    TOptional<FString> FEzSimpleItemGameSessionDomain::NamespaceName() const
    {
        return Domain->NamespaceName;
    }

    TOptional<FString> FEzSimpleItemGameSessionDomain::UserId() const
    {
        return Domain->UserId();
    }

    TOptional<FString> FEzSimpleItemGameSessionDomain::InventoryName() const
    {
        return Domain->InventoryName;
    }

    TOptional<FString> FEzSimpleItemGameSessionDomain::ItemName() const
    {
        return Domain->ItemName;
    }

    FEzSimpleItemGameSessionDomain::FEzSimpleItemGameSessionDomain(
        Gs2::Inventory::Domain::Model::FSimpleItemAccessTokenDomainPtr Domain,
        Gs2::UE5::Util::FProfilePtr Profile
    ): Domain(Domain), ProfileValue(Profile) {

    }

    FEzSimpleItemGameSessionDomain::FGetSimpleItemWithSignatureTask::FGetSimpleItemWithSignatureTask(
        TSharedPtr<FEzSimpleItemGameSessionDomain> Self,
        TOptional<FString> KeyId
    ): Self(Self), KeyId(KeyId)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FEzSimpleItemGameSessionDomain::FGetSimpleItemWithSignatureTask::Action(
        TSharedPtr<TSharedPtr<Gs2::UE5::Inventory::Domain::Model::FEzSimpleItemGameSessionDomain>> Result
    )
    {
        const auto Future = Self->ProfileValue->Run<FGetSimpleItemWithSignatureTask>(
            [&]() -> Gs2::Core::Model::FGs2ErrorPtr {
                const auto Task = Self->Domain->GetWithSignature(
                    MakeShared<Gs2::Inventory::Request::FGetSimpleItemWithSignatureRequest>()
                        ->WithKeyId(KeyId)
                );
                Task->StartSynchronousTask();
                if (Task->GetTask().IsError())
                {
                    Task->EnsureCompletion();
                    return Task->GetTask().Error();
                }
                *Result = MakeShared<Gs2::UE5::Inventory::Domain::Model::FEzSimpleItemGameSessionDomain>(
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

    TSharedPtr<FAsyncTask<FEzSimpleItemGameSessionDomain::FGetSimpleItemWithSignatureTask>> FEzSimpleItemGameSessionDomain::GetSimpleItemWithSignature(
        TOptional<FString> KeyId
    )
    {
        return Gs2::Core::Util::New<FAsyncTask<FGetSimpleItemWithSignatureTask>>(
            this->AsShared(),
            KeyId
        );
    }

    FEzSimpleItemGameSessionDomain::FModelTask::FModelTask(
        TSharedPtr<FEzSimpleItemGameSessionDomain> Self
    ): Self(Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FEzSimpleItemGameSessionDomain::FModelTask::Action(
        TSharedPtr<Gs2::UE5::Inventory::Model::FEzSimpleItemPtr> Result
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

    TSharedPtr<FAsyncTask<FEzSimpleItemGameSessionDomain::FModelTask>> FEzSimpleItemGameSessionDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FModelTask>>(this->AsShared());
    }

    Gs2::Core::Domain::CallbackID FEzSimpleItemGameSessionDomain::Subscribe(TFunction<void(Gs2::UE5::Inventory::Model::FEzSimpleItemPtr)> Callback)
    {
        return Domain->Subscribe(
            [&](Gs2::Inventory::Model::FSimpleItemPtr Item)
            {
                Callback(Gs2::UE5::Inventory::Model::FEzSimpleItem::FromModel(Item));
            }
        );
    }

    void FEzSimpleItemGameSessionDomain::Unsubscribe(Gs2::Core::Domain::CallbackID CallbackId)
    {
        Domain->Unsubscribe(
            CallbackId
        );
    }
}
