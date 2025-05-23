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

#include "Formation/Domain/Model/Gs2FormationEzFormGameSessionDomain.h"

namespace Gs2::UE5::Formation::Domain::Model
{

    TOptional<FString> FEzFormGameSessionDomain::Body() const
    {
        return Domain->Body;
    }

    TOptional<FString> FEzFormGameSessionDomain::Signature() const
    {
        return Domain->Signature;
    }

    TOptional<FString> FEzFormGameSessionDomain::NamespaceName() const
    {
        return Domain->NamespaceName;
    }

    TOptional<FString> FEzFormGameSessionDomain::UserId() const
    {
        return Domain->UserId();
    }

    TOptional<FString> FEzFormGameSessionDomain::MoldModelName() const
    {
        return Domain->MoldModelName;
    }

    TOptional<int32> FEzFormGameSessionDomain::Index() const
    {
        return Domain->Index;
    }

    FEzFormGameSessionDomain::FEzFormGameSessionDomain(
        Gs2::Formation::Domain::Model::FFormAccessTokenDomainPtr Domain,
        Gs2::UE5::Util::IGameSessionPtr GameSession,
        Gs2::UE5::Util::FGs2ConnectionPtr Connection
    ):
        Domain(Domain),
        GameSession(GameSession),
        ConnectionValue(Connection)
    {

    }

    FEzFormGameSessionDomain::FGetFormWithSignatureTask::FGetFormWithSignatureTask(
        TSharedPtr<FEzFormGameSessionDomain> Self,
        TOptional<FString> KeyId
    ): Self(Self), KeyId(KeyId)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FEzFormGameSessionDomain::FGetFormWithSignatureTask::Action(
        TSharedPtr<TSharedPtr<Gs2::UE5::Formation::Domain::Model::FEzFormGameSessionDomain>> Result
    )
    {
        const auto Future = Self->ConnectionValue->Run(
            [&]() -> Gs2::Core::Model::FGs2ErrorPtr {
                const auto Task = Self->Domain->GetWithSignature(
                    MakeShared<Gs2::Formation::Request::FGetFormWithSignatureRequest>()
                        ->WithKeyId(KeyId)
                );
                Task->StartSynchronousTask();
                if (Task->GetTask().IsError())
                {
                    Task->EnsureCompletion();
                    return Task->GetTask().Error();
                }
                *Result = MakeShared<Gs2::UE5::Formation::Domain::Model::FEzFormGameSessionDomain>(
                    Task->GetTask().Result(),
                    Self->GameSession,
                    Self->ConnectionValue
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

    TSharedPtr<FAsyncTask<FEzFormGameSessionDomain::FGetFormWithSignatureTask>> FEzFormGameSessionDomain::GetFormWithSignature(
        TOptional<FString> KeyId
    )
    {
        return Gs2::Core::Util::New<FAsyncTask<FGetFormWithSignatureTask>>(
            this->AsShared(),
            KeyId
        );
    }

    FEzFormGameSessionDomain::FSetFormTask::FSetFormTask(
        TSharedPtr<FEzFormGameSessionDomain> Self,
        TArray<TSharedPtr<Gs2::UE5::Formation::Model::FEzSlotWithSignature>> Slots,
        TOptional<FString> KeyId
    ): Self(Self), Slots(Slots), KeyId(KeyId)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FEzFormGameSessionDomain::FSetFormTask::Action(
        TSharedPtr<TSharedPtr<Gs2::UE5::Formation::Domain::Model::FEzFormGameSessionDomain>> Result
    )
    {
        const auto Future = Self->ConnectionValue->Run(
            [&]() -> Gs2::Core::Model::FGs2ErrorPtr {
                const auto Task = Self->Domain->SetWithSignature(
                    MakeShared<Gs2::Formation::Request::FSetFormWithSignatureRequest>()
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
                *Result = MakeShared<Gs2::UE5::Formation::Domain::Model::FEzFormGameSessionDomain>(
                    Task->GetTask().Result(),
                    Self->GameSession,
                    Self->ConnectionValue
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

    TSharedPtr<FAsyncTask<FEzFormGameSessionDomain::FSetFormTask>> FEzFormGameSessionDomain::SetForm(
        TArray<TSharedPtr<Gs2::UE5::Formation::Model::FEzSlotWithSignature>> Slots,
        TOptional<FString> KeyId
    )
    {
        return Gs2::Core::Util::New<FAsyncTask<FSetFormTask>>(
            this->AsShared(),
            Slots,
            KeyId
        );
    }

    FEzFormGameSessionDomain::FDeleteFormTask::FDeleteFormTask(
        TSharedPtr<FEzFormGameSessionDomain> Self
    ): Self(Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FEzFormGameSessionDomain::FDeleteFormTask::Action(
        TSharedPtr<TSharedPtr<Gs2::UE5::Formation::Domain::Model::FEzFormGameSessionDomain>> Result
    )
    {
        const auto Future = Self->ConnectionValue->Run(
            [&]() -> Gs2::Core::Model::FGs2ErrorPtr {
                const auto Task = Self->Domain->Delete(
                    MakeShared<Gs2::Formation::Request::FDeleteFormRequest>()
                );
                Task->StartSynchronousTask();
                if (Task->GetTask().IsError())
                {
                    Task->EnsureCompletion();
                    return Task->GetTask().Error();
                }
                *Result = MakeShared<Gs2::UE5::Formation::Domain::Model::FEzFormGameSessionDomain>(
                    Task->GetTask().Result(),
                    Self->GameSession,
                    Self->ConnectionValue
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

    TSharedPtr<FAsyncTask<FEzFormGameSessionDomain::FDeleteFormTask>> FEzFormGameSessionDomain::DeleteForm(
    )
    {
        return Gs2::Core::Util::New<FAsyncTask<FDeleteFormTask>>(
            this->AsShared()
        );
    }

    FEzFormGameSessionDomain::FModelTask::FModelTask(
        TSharedPtr<FEzFormGameSessionDomain> Self
    ): Self(Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FEzFormGameSessionDomain::FModelTask::Action(
        TSharedPtr<Gs2::UE5::Formation::Model::FEzFormPtr> Result
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
                *Result = Gs2::UE5::Formation::Model::FEzForm::FromModel(Task->GetTask().Result());
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

    TSharedPtr<FAsyncTask<FEzFormGameSessionDomain::FModelTask>> FEzFormGameSessionDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FModelTask>>(this->AsShared());
    }

    Gs2::Core::Domain::CallbackID FEzFormGameSessionDomain::Subscribe(TFunction<void(Gs2::UE5::Formation::Model::FEzFormPtr)> Callback)
    {
        return Domain->Subscribe(
            [&](Gs2::Formation::Model::FFormPtr Item)
            {
                Callback(Gs2::UE5::Formation::Model::FEzForm::FromModel(Item));
            }
        );
    }

    void FEzFormGameSessionDomain::Unsubscribe(Gs2::Core::Domain::CallbackID CallbackId)
    {
        Domain->Unsubscribe(
            CallbackId
        );
    }
}
