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

#include "Formation/Domain/Model/Gs2FormationEzPropertyFormGameSessionDomain.h"

namespace Gs2::UE5::Formation::Domain::Model
{

    TOptional<FString> FEzPropertyFormGameSessionDomain::Body() const
    {
        return Domain->Body;
    }

    TOptional<FString> FEzPropertyFormGameSessionDomain::Signature() const
    {
        return Domain->Signature;
    }

    TOptional<FString> FEzPropertyFormGameSessionDomain::TransactionId() const
    {
        return Domain->TransactionId;
    }

    TOptional<bool> FEzPropertyFormGameSessionDomain::AutoRunStampSheet() const
    {
        return Domain->AutoRunStampSheet;
    }

    TOptional<FString> FEzPropertyFormGameSessionDomain::NamespaceName() const
    {
        return Domain->NamespaceName;
    }

    TOptional<FString> FEzPropertyFormGameSessionDomain::UserId() const
    {
        return Domain->UserId();
    }

    TOptional<FString> FEzPropertyFormGameSessionDomain::PropertyFormModelName() const
    {
        return Domain->PropertyFormModelName;
    }

    TOptional<FString> FEzPropertyFormGameSessionDomain::PropertyId() const
    {
        return Domain->PropertyId;
    }

    FEzPropertyFormGameSessionDomain::FEzPropertyFormGameSessionDomain(
        Gs2::Formation::Domain::Model::FPropertyFormAccessTokenDomainPtr Domain,
        Gs2::UE5::Util::FProfilePtr Profile
    ): Domain(Domain), ProfileValue(Profile) {

    }

    FEzPropertyFormGameSessionDomain::FGetPropertyFormTask::FGetPropertyFormTask(
        TSharedPtr<FEzPropertyFormGameSessionDomain> Self
    ): Self(Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FEzPropertyFormGameSessionDomain::FGetPropertyFormTask::Action(
        TSharedPtr<TSharedPtr<Gs2::UE5::Formation::Model::FEzPropertyForm>> Result
    )
    {
        const auto Future = Self->ProfileValue->Run<FGetPropertyFormTask>(
            [&]() -> Gs2::Core::Model::FGs2ErrorPtr {
                const auto Task = Self->Domain->Get(
                    MakeShared<Gs2::Formation::Request::FGetPropertyFormRequest>()
                );
                Task->StartSynchronousTask();
                if (Task->GetTask().IsError())
                {
                    Task->EnsureCompletion();
                    return Task->GetTask().Error();
                }
                *Result = Gs2::UE5::Formation::Model::FEzPropertyForm::FromModel(
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

    TSharedPtr<FAsyncTask<FEzPropertyFormGameSessionDomain::FGetPropertyFormTask>> FEzPropertyFormGameSessionDomain::GetPropertyForm(
    )
    {
        return Gs2::Core::Util::New<FAsyncTask<FGetPropertyFormTask>>(
            this->AsShared()
        );
    }

    FEzPropertyFormGameSessionDomain::FGetPropertyFormWithSignatureTask::FGetPropertyFormWithSignatureTask(
        TSharedPtr<FEzPropertyFormGameSessionDomain> Self,
        FString KeyId
    ): Self(Self), KeyId(KeyId)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FEzPropertyFormGameSessionDomain::FGetPropertyFormWithSignatureTask::Action(
        TSharedPtr<TSharedPtr<Gs2::UE5::Formation::Domain::Model::FEzPropertyFormGameSessionDomain>> Result
    )
    {
        const auto Future = Self->ProfileValue->Run<FGetPropertyFormWithSignatureTask>(
            [&]() -> Gs2::Core::Model::FGs2ErrorPtr {
                const auto Task = Self->Domain->GetWithSignature(
                    MakeShared<Gs2::Formation::Request::FGetPropertyFormWithSignatureRequest>()
                        ->WithKeyId(KeyId)
                );
                Task->StartSynchronousTask();
                if (Task->GetTask().IsError())
                {
                    Task->EnsureCompletion();
                    return Task->GetTask().Error();
                }
                *Result = MakeShared<Gs2::UE5::Formation::Domain::Model::FEzPropertyFormGameSessionDomain>(
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

    TSharedPtr<FAsyncTask<FEzPropertyFormGameSessionDomain::FGetPropertyFormWithSignatureTask>> FEzPropertyFormGameSessionDomain::GetPropertyFormWithSignature(
        FString KeyId
    )
    {
        return Gs2::Core::Util::New<FAsyncTask<FGetPropertyFormWithSignatureTask>>(
            this->AsShared(),
            KeyId
        );
    }

    FEzPropertyFormGameSessionDomain::FSetPropertyFormTask::FSetPropertyFormTask(
        TSharedPtr<FEzPropertyFormGameSessionDomain> Self,
        TArray<TSharedPtr<Gs2::UE5::Formation::Model::FEzSlotWithSignature>> Slots,
        FString KeyId
    ): Self(Self), Slots(Slots), KeyId(KeyId)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FEzPropertyFormGameSessionDomain::FSetPropertyFormTask::Action(
        TSharedPtr<TSharedPtr<Gs2::UE5::Formation::Domain::Model::FEzPropertyFormGameSessionDomain>> Result
    )
    {
        const auto Future = Self->ProfileValue->Run<FSetPropertyFormTask>(
            [&]() -> Gs2::Core::Model::FGs2ErrorPtr {
                const auto Task = Self->Domain->SetWithSignature(
                    MakeShared<Gs2::Formation::Request::FSetPropertyFormWithSignatureRequest>()
                        ->WithSlots([&]{
                            auto Arr = MakeShared<TArray<TSharedPtr<Gs2::Formation::Model::FSlotWithSignature>>>();
                            for (auto Value : Slots) {
                                Arr->Add(Value->ToModel());
                            }
                            return Arr;
                        }())
                        ->WithKeyId(KeyId)
                );
                Task->StartSynchronousTask();
                if (Task->GetTask().IsError())
                {
                    Task->EnsureCompletion();
                    return Task->GetTask().Error();
                }
                *Result = MakeShared<Gs2::UE5::Formation::Domain::Model::FEzPropertyFormGameSessionDomain>(
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

    TSharedPtr<FAsyncTask<FEzPropertyFormGameSessionDomain::FSetPropertyFormTask>> FEzPropertyFormGameSessionDomain::SetPropertyForm(
        TArray<TSharedPtr<Gs2::UE5::Formation::Model::FEzSlotWithSignature>> Slots,
        FString KeyId
    )
    {
        return Gs2::Core::Util::New<FAsyncTask<FSetPropertyFormTask>>(
            this->AsShared(),
            Slots,
            KeyId
        );
    }

    FEzPropertyFormGameSessionDomain::FModelTask::FModelTask(
        TSharedPtr<FEzPropertyFormGameSessionDomain> Self
    ): Self(Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FEzPropertyFormGameSessionDomain::FModelTask::Action(
        TSharedPtr<Gs2::UE5::Formation::Model::FEzPropertyFormPtr> Result
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
                *Result = Gs2::UE5::Formation::Model::FEzPropertyForm::FromModel(Task->GetTask().Result());
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

    TSharedPtr<FAsyncTask<FEzPropertyFormGameSessionDomain::FModelTask>> FEzPropertyFormGameSessionDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FModelTask>>(this->AsShared());
    }
}
