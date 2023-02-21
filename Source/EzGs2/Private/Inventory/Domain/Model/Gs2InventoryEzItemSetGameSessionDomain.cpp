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

#include "Inventory/Domain/Model/Gs2InventoryEzItemSetGameSessionDomain.h"

namespace Gs2::UE5::Inventory::Domain::Model
{

    TOptional<FString> FEzItemSetGameSessionDomain::Body() const
    {
        return Domain->Body;
    }

    TOptional<FString> FEzItemSetGameSessionDomain::Signature() const
    {
        return Domain->Signature;
    }

    TOptional<int64> FEzItemSetGameSessionDomain::OverflowCount() const
    {
        return Domain->OverflowCount;
    }

    TOptional<FString> FEzItemSetGameSessionDomain::NamespaceName() const
    {
        return Domain->NamespaceName;
    }

    TOptional<FString> FEzItemSetGameSessionDomain::UserId() const
    {
        return Domain->UserId();
    }

    TOptional<FString> FEzItemSetGameSessionDomain::InventoryName() const
    {
        return Domain->InventoryName;
    }

    TOptional<FString> FEzItemSetGameSessionDomain::ItemName() const
    {
        return Domain->ItemName;
    }

    TOptional<FString> FEzItemSetGameSessionDomain::ItemSetName() const
    {
        return Domain->ItemSetName;
    }

    FEzItemSetGameSessionDomain::FEzItemSetGameSessionDomain(
        Gs2::Inventory::Domain::Model::FItemSetAccessTokenDomainPtr Domain,
        Gs2::UE5::Util::FProfilePtr Profile
    ): Domain(Domain), ProfileValue(Profile) {

    }

    FEzItemSetGameSessionDomain::FGetItemTask::FGetItemTask(
        TSharedPtr<FEzItemSetGameSessionDomain> Self
    ): Self(Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FEzItemSetGameSessionDomain::FGetItemTask::Action(
        TSharedPtr<TSharedPtr<TArray<TSharedPtr<Gs2::UE5::Inventory::Model::FEzItemSet>>>> Result
    )
    {
        const auto Future = Self->ProfileValue->Run<FGetItemTask>(
            [&]() -> Gs2::Core::Model::FGs2ErrorPtr {
                const auto Task = Self->Domain->Get(
                    MakeShared<Gs2::Inventory::Request::FGetItemSetRequest>()
                );
                Task->StartSynchronousTask();
                if (Task->GetTask().IsError())
                {
                    Task->EnsureCompletion();
                    return Task->GetTask().Error();
                }
                *Result = MakeShared<TArray<TSharedPtr<Gs2::UE5::Inventory::Model::FEzItemSet>>>();
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

    TSharedPtr<FAsyncTask<FEzItemSetGameSessionDomain::FGetItemTask>> FEzItemSetGameSessionDomain::GetItem(
    )
    {
        return Gs2::Core::Util::New<FAsyncTask<FGetItemTask>>(
            this->AsShared()
        );
    }

    FEzItemSetGameSessionDomain::FGetItemWithSignatureTask::FGetItemWithSignatureTask(
        TSharedPtr<FEzItemSetGameSessionDomain> Self,
        FString KeyId
    ): Self(Self), KeyId(KeyId)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FEzItemSetGameSessionDomain::FGetItemWithSignatureTask::Action(
        TSharedPtr<TSharedPtr<Gs2::UE5::Inventory::Domain::Model::FEzItemSetGameSessionDomain>> Result
    )
    {
        const auto Future = Self->ProfileValue->Run<FGetItemWithSignatureTask>(
            [&]() -> Gs2::Core::Model::FGs2ErrorPtr {
                const auto Task = Self->Domain->GetItemWithSignature(
                    MakeShared<Gs2::Inventory::Request::FGetItemWithSignatureRequest>()
                        ->WithKeyId(KeyId)
                );
                Task->StartSynchronousTask();
                if (Task->GetTask().IsError())
                {
                    Task->EnsureCompletion();
                    return Task->GetTask().Error();
                }
                *Result = MakeShared<Gs2::UE5::Inventory::Domain::Model::FEzItemSetGameSessionDomain>(
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

    TSharedPtr<FAsyncTask<FEzItemSetGameSessionDomain::FGetItemWithSignatureTask>> FEzItemSetGameSessionDomain::GetItemWithSignature(
        FString KeyId
    )
    {
        return Gs2::Core::Util::New<FAsyncTask<FGetItemWithSignatureTask>>(
            this->AsShared(),
            KeyId
        );
    }

    FEzItemSetGameSessionDomain::FConsumeTask::FConsumeTask(
        TSharedPtr<FEzItemSetGameSessionDomain> Self,
        int64 ConsumeCount
    ): Self(Self), ConsumeCount(ConsumeCount)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FEzItemSetGameSessionDomain::FConsumeTask::Action(
        TSharedPtr<TSharedPtr<Gs2::UE5::Inventory::Domain::Model::FEzItemSetGameSessionDomain>> Result
    )
    {
        const auto Future = Self->ProfileValue->Run<FConsumeTask>(
            [&]() -> Gs2::Core::Model::FGs2ErrorPtr {
                const auto Task = Self->Domain->Consume(
                    MakeShared<Gs2::Inventory::Request::FConsumeItemSetRequest>()
                        ->WithConsumeCount(ConsumeCount)
                );
                Task->StartSynchronousTask();
                if (Task->GetTask().IsError())
                {
                    Task->EnsureCompletion();
                    return Task->GetTask().Error();
                }
                *Result = MakeShared<Gs2::UE5::Inventory::Domain::Model::FEzItemSetGameSessionDomain>(
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

    TSharedPtr<FAsyncTask<FEzItemSetGameSessionDomain::FConsumeTask>> FEzItemSetGameSessionDomain::Consume(
        int64 ConsumeCount
    )
    {
        return Gs2::Core::Util::New<FAsyncTask<FConsumeTask>>(
            this->AsShared(),
            ConsumeCount
        );
    }

    Gs2::UE5::Inventory::Domain::Model::FEzReferenceOfGameSessionDomainPtr FEzItemSetGameSessionDomain::ReferenceOf(
        const FString ReferenceOf
    ) const
    {
        return MakeShared<Gs2::UE5::Inventory::Domain::Model::FEzReferenceOfGameSessionDomain>(
            Domain->ReferenceOf(
                ReferenceOf
            ),
            ProfileValue
        );
    }

    FEzItemSetGameSessionDomain::FModelTask::FModelTask(
        TSharedPtr<FEzItemSetGameSessionDomain> Self
    ): Self(Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FEzItemSetGameSessionDomain::FModelTask::Action(
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

    TSharedPtr<FAsyncTask<FEzItemSetGameSessionDomain::FModelTask>> FEzItemSetGameSessionDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FModelTask>>(this->AsShared());
    }
}
