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

#include "Experience/Domain/Model/Gs2ExperienceEzStatusGameSessionDomain.h"

namespace Gs2::UE5::Experience::Domain::Model
{

    TOptional<FString> FEzStatusGameSessionDomain::Body() const
    {
        return Domain->Body;
    }

    TOptional<FString> FEzStatusGameSessionDomain::Signature() const
    {
        return Domain->Signature;
    }

    TOptional<FString> FEzStatusGameSessionDomain::NamespaceName() const
    {
        return Domain->NamespaceName;
    }

    TOptional<FString> FEzStatusGameSessionDomain::UserId() const
    {
        return Domain->UserId();
    }

    TOptional<FString> FEzStatusGameSessionDomain::ExperienceName() const
    {
        return Domain->ExperienceName;
    }

    TOptional<FString> FEzStatusGameSessionDomain::PropertyId() const
    {
        return Domain->PropertyId;
    }

    FEzStatusGameSessionDomain::FEzStatusGameSessionDomain(
        Gs2::Experience::Domain::Model::FStatusAccessTokenDomainPtr Domain,
        Gs2::UE5::Util::IGameSessionPtr GameSession,
        Gs2::UE5::Util::FGs2ConnectionPtr Connection
    ):
        Domain(Domain),
        GameSession(GameSession),
        ConnectionValue(Connection)
    {

    }

    FEzStatusGameSessionDomain::FGetStatusWithSignatureTask::FGetStatusWithSignatureTask(
        TSharedPtr<FEzStatusGameSessionDomain> Self,
        TOptional<FString> KeyId
    ): Self(Self), KeyId(KeyId)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FEzStatusGameSessionDomain::FGetStatusWithSignatureTask::Action(
        TSharedPtr<TSharedPtr<Gs2::UE5::Experience::Domain::Model::FEzStatusGameSessionDomain>> Result
    )
    {
        const auto Future = Self->ConnectionValue->Run(
            [&]() -> Gs2::Core::Model::FGs2ErrorPtr {
                const auto Task = Self->Domain->GetWithSignature(
                    MakeShared<Gs2::Experience::Request::FGetStatusWithSignatureRequest>()
                        ->WithKeyId(KeyId)
                );
                Task->StartSynchronousTask();
                if (Task->GetTask().IsError())
                {
                    Task->EnsureCompletion();
                    return Task->GetTask().Error();
                }
                *Result = MakeShared<Gs2::UE5::Experience::Domain::Model::FEzStatusGameSessionDomain>(
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

    TSharedPtr<FAsyncTask<FEzStatusGameSessionDomain::FGetStatusWithSignatureTask>> FEzStatusGameSessionDomain::GetStatusWithSignature(
        TOptional<FString> KeyId
    )
    {
        return Gs2::Core::Util::New<FAsyncTask<FGetStatusWithSignatureTask>>(
            this->AsShared(),
            KeyId
        );
    }

    FEzStatusGameSessionDomain::FModelTask::FModelTask(
        TSharedPtr<FEzStatusGameSessionDomain> Self
    ): Self(Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FEzStatusGameSessionDomain::FModelTask::Action(
        TSharedPtr<Gs2::UE5::Experience::Model::FEzStatusPtr> Result
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
                *Result = Gs2::UE5::Experience::Model::FEzStatus::FromModel(Task->GetTask().Result());
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

    TSharedPtr<FAsyncTask<FEzStatusGameSessionDomain::FModelTask>> FEzStatusGameSessionDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FModelTask>>(this->AsShared());
    }

    Gs2::Core::Domain::CallbackID FEzStatusGameSessionDomain::Subscribe(TFunction<void(Gs2::UE5::Experience::Model::FEzStatusPtr)> Callback)
    {
        return Domain->Subscribe(
            [&](Gs2::Experience::Model::FStatusPtr Item)
            {
                Callback(Gs2::UE5::Experience::Model::FEzStatus::FromModel(Item));
            }
        );
    }

    void FEzStatusGameSessionDomain::Unsubscribe(Gs2::Core::Domain::CallbackID CallbackId)
    {
        Domain->Unsubscribe(
            CallbackId
        );
    }
}
