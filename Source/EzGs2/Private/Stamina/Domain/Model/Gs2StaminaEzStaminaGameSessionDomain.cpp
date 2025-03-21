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

#include "Stamina/Domain/Model/Gs2StaminaEzStaminaGameSessionDomain.h"

namespace Gs2::UE5::Stamina::Domain::Model
{

    TOptional<int32> FEzStaminaGameSessionDomain::OverflowValue() const
    {
        return Domain->OverflowValue;
    }

    TOptional<FString> FEzStaminaGameSessionDomain::NamespaceName() const
    {
        return Domain->NamespaceName;
    }

    TOptional<FString> FEzStaminaGameSessionDomain::UserId() const
    {
        return Domain->UserId();
    }

    TOptional<FString> FEzStaminaGameSessionDomain::StaminaName() const
    {
        return Domain->StaminaName;
    }

    FEzStaminaGameSessionDomain::FEzStaminaGameSessionDomain(
        Gs2::Stamina::Domain::Model::FStaminaAccessTokenDomainPtr Domain,
        Gs2::UE5::Util::IGameSessionPtr GameSession,
        Gs2::UE5::Util::FGs2ConnectionPtr Connection
    ):
        Domain(Domain),
        GameSession(GameSession),
        ConnectionValue(Connection)
    {

    }

    FEzStaminaGameSessionDomain::FConsumeTask::FConsumeTask(
        TSharedPtr<FEzStaminaGameSessionDomain> Self,
        int32 ConsumeValue
    ): Self(Self), ConsumeValue(ConsumeValue)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FEzStaminaGameSessionDomain::FConsumeTask::Action(
        TSharedPtr<TSharedPtr<Gs2::UE5::Stamina::Domain::Model::FEzStaminaGameSessionDomain>> Result
    )
    {
        const auto Future = Self->ConnectionValue->Run(
            [&]() -> Gs2::Core::Model::FGs2ErrorPtr {
                const auto Task = Self->Domain->Consume(
                    MakeShared<Gs2::Stamina::Request::FConsumeStaminaRequest>()
                        ->WithConsumeValue(ConsumeValue)
                );
                Task->StartSynchronousTask();
                if (Task->GetTask().IsError())
                {
                    Task->EnsureCompletion();
                    return Task->GetTask().Error();
                }
                *Result = MakeShared<Gs2::UE5::Stamina::Domain::Model::FEzStaminaGameSessionDomain>(
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

    TSharedPtr<FAsyncTask<FEzStaminaGameSessionDomain::FConsumeTask>> FEzStaminaGameSessionDomain::Consume(
        int32 ConsumeValue
    )
    {
        return Gs2::Core::Util::New<FAsyncTask<FConsumeTask>>(
            this->AsShared(),
            ConsumeValue
        );
    }

    FEzStaminaGameSessionDomain::FApplyTask::FApplyTask(
        TSharedPtr<FEzStaminaGameSessionDomain> Self
    ): Self(Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FEzStaminaGameSessionDomain::FApplyTask::Action(
        TSharedPtr<TSharedPtr<Gs2::UE5::Stamina::Domain::Model::FEzStaminaGameSessionDomain>> Result
    )
    {
        const auto Future = Self->ConnectionValue->Run(
            [&]() -> Gs2::Core::Model::FGs2ErrorPtr {
                const auto Task = Self->Domain->Apply(
                    MakeShared<Gs2::Stamina::Request::FApplyStaminaRequest>()
                );
                Task->StartSynchronousTask();
                if (Task->GetTask().IsError())
                {
                    Task->EnsureCompletion();
                    return Task->GetTask().Error();
                }
                *Result = MakeShared<Gs2::UE5::Stamina::Domain::Model::FEzStaminaGameSessionDomain>(
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

    TSharedPtr<FAsyncTask<FEzStaminaGameSessionDomain::FApplyTask>> FEzStaminaGameSessionDomain::Apply(
    )
    {
        return Gs2::Core::Util::New<FAsyncTask<FApplyTask>>(
            this->AsShared()
        );
    }

    FEzStaminaGameSessionDomain::FSetMaxValueTask::FSetMaxValueTask(
        TSharedPtr<FEzStaminaGameSessionDomain> Self,
        FString SignedStatusBody,
        FString SignedStatusSignature,
        TOptional<FString> KeyId
    ): Self(Self), SignedStatusBody(SignedStatusBody), SignedStatusSignature(SignedStatusSignature), KeyId(KeyId)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FEzStaminaGameSessionDomain::FSetMaxValueTask::Action(
        TSharedPtr<TSharedPtr<Gs2::UE5::Stamina::Domain::Model::FEzStaminaGameSessionDomain>> Result
    )
    {
        const auto Future = Self->ConnectionValue->Run(
            [&]() -> Gs2::Core::Model::FGs2ErrorPtr {
                const auto Task = Self->Domain->SetMaxValueByStatus(
                    MakeShared<Gs2::Stamina::Request::FSetMaxValueByStatusRequest>()
                        ->WithKeyId(KeyId)
                        ->WithSignedStatusBody(SignedStatusBody)
                        ->WithSignedStatusSignature(SignedStatusSignature)
                );
                Task->StartSynchronousTask();
                if (Task->GetTask().IsError())
                {
                    Task->EnsureCompletion();
                    return Task->GetTask().Error();
                }
                *Result = MakeShared<Gs2::UE5::Stamina::Domain::Model::FEzStaminaGameSessionDomain>(
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

    TSharedPtr<FAsyncTask<FEzStaminaGameSessionDomain::FSetMaxValueTask>> FEzStaminaGameSessionDomain::SetMaxValue(
        FString SignedStatusBody,
        FString SignedStatusSignature,
        TOptional<FString> KeyId
    )
    {
        return Gs2::Core::Util::New<FAsyncTask<FSetMaxValueTask>>(
            this->AsShared(),
            SignedStatusBody,
            SignedStatusSignature,
            KeyId
        );
    }

    FEzStaminaGameSessionDomain::FSetRecoverIntervalTask::FSetRecoverIntervalTask(
        TSharedPtr<FEzStaminaGameSessionDomain> Self,
        FString SignedStatusBody,
        FString SignedStatusSignature,
        TOptional<FString> KeyId
    ): Self(Self), SignedStatusBody(SignedStatusBody), SignedStatusSignature(SignedStatusSignature), KeyId(KeyId)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FEzStaminaGameSessionDomain::FSetRecoverIntervalTask::Action(
        TSharedPtr<TSharedPtr<Gs2::UE5::Stamina::Domain::Model::FEzStaminaGameSessionDomain>> Result
    )
    {
        const auto Future = Self->ConnectionValue->Run(
            [&]() -> Gs2::Core::Model::FGs2ErrorPtr {
                const auto Task = Self->Domain->SetRecoverIntervalByStatus(
                    MakeShared<Gs2::Stamina::Request::FSetRecoverIntervalByStatusRequest>()
                        ->WithKeyId(KeyId)
                        ->WithSignedStatusBody(SignedStatusBody)
                        ->WithSignedStatusSignature(SignedStatusSignature)
                );
                Task->StartSynchronousTask();
                if (Task->GetTask().IsError())
                {
                    Task->EnsureCompletion();
                    return Task->GetTask().Error();
                }
                *Result = MakeShared<Gs2::UE5::Stamina::Domain::Model::FEzStaminaGameSessionDomain>(
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

    TSharedPtr<FAsyncTask<FEzStaminaGameSessionDomain::FSetRecoverIntervalTask>> FEzStaminaGameSessionDomain::SetRecoverInterval(
        FString SignedStatusBody,
        FString SignedStatusSignature,
        TOptional<FString> KeyId
    )
    {
        return Gs2::Core::Util::New<FAsyncTask<FSetRecoverIntervalTask>>(
            this->AsShared(),
            SignedStatusBody,
            SignedStatusSignature,
            KeyId
        );
    }

    FEzStaminaGameSessionDomain::FSetRecoverValueTask::FSetRecoverValueTask(
        TSharedPtr<FEzStaminaGameSessionDomain> Self,
        FString SignedStatusBody,
        FString SignedStatusSignature,
        TOptional<FString> KeyId
    ): Self(Self), SignedStatusBody(SignedStatusBody), SignedStatusSignature(SignedStatusSignature), KeyId(KeyId)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FEzStaminaGameSessionDomain::FSetRecoverValueTask::Action(
        TSharedPtr<TSharedPtr<Gs2::UE5::Stamina::Domain::Model::FEzStaminaGameSessionDomain>> Result
    )
    {
        const auto Future = Self->ConnectionValue->Run(
            [&]() -> Gs2::Core::Model::FGs2ErrorPtr {
                const auto Task = Self->Domain->SetRecoverValueByStatus(
                    MakeShared<Gs2::Stamina::Request::FSetRecoverValueByStatusRequest>()
                        ->WithKeyId(KeyId)
                        ->WithSignedStatusBody(SignedStatusBody)
                        ->WithSignedStatusSignature(SignedStatusSignature)
                );
                Task->StartSynchronousTask();
                if (Task->GetTask().IsError())
                {
                    Task->EnsureCompletion();
                    return Task->GetTask().Error();
                }
                *Result = MakeShared<Gs2::UE5::Stamina::Domain::Model::FEzStaminaGameSessionDomain>(
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

    TSharedPtr<FAsyncTask<FEzStaminaGameSessionDomain::FSetRecoverValueTask>> FEzStaminaGameSessionDomain::SetRecoverValue(
        FString SignedStatusBody,
        FString SignedStatusSignature,
        TOptional<FString> KeyId
    )
    {
        return Gs2::Core::Util::New<FAsyncTask<FSetRecoverValueTask>>(
            this->AsShared(),
            SignedStatusBody,
            SignedStatusSignature,
            KeyId
        );
    }

    FEzStaminaGameSessionDomain::FModelTask::FModelTask(
        TSharedPtr<FEzStaminaGameSessionDomain> Self
    ): Self(Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FEzStaminaGameSessionDomain::FModelTask::Action(
        TSharedPtr<Gs2::UE5::Stamina::Model::FEzStaminaPtr> Result
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
                *Result = Gs2::UE5::Stamina::Model::FEzStamina::FromModel(Task->GetTask().Result());
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

    TSharedPtr<FAsyncTask<FEzStaminaGameSessionDomain::FModelTask>> FEzStaminaGameSessionDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FModelTask>>(this->AsShared());
    }

    Gs2::Core::Domain::CallbackID FEzStaminaGameSessionDomain::Subscribe(TFunction<void(Gs2::UE5::Stamina::Model::FEzStaminaPtr)> Callback)
    {
        return Domain->Subscribe(
            [&](Gs2::Stamina::Model::FStaminaPtr Item)
            {
                Callback(Gs2::UE5::Stamina::Model::FEzStamina::FromModel(Item));
            }
        );
    }

    void FEzStaminaGameSessionDomain::Unsubscribe(Gs2::Core::Domain::CallbackID CallbackId)
    {
        Domain->Unsubscribe(
            CallbackId
        );
    }
}
