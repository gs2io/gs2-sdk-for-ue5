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

    TOptional<int64> FEzStaminaGameSessionDomain::OverflowValue() const
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
        Gs2::UE5::Util::FProfilePtr Profile
    ): Domain(Domain), ProfileValue(Profile) {

    }

    FEzStaminaGameSessionDomain::FGetStaminaTask::FGetStaminaTask(
        TSharedPtr<FEzStaminaGameSessionDomain> Self
    ): Self(Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FEzStaminaGameSessionDomain::FGetStaminaTask::Action(
        TSharedPtr<TSharedPtr<Gs2::UE5::Stamina::Model::FEzStamina>> Result
    )
    {
        const auto Future = Self->ProfileValue->Run<FGetStaminaTask>(
            [&]() -> Gs2::Core::Model::FGs2ErrorPtr {
                const auto Task = Self->Domain->Get(
                    MakeShared<Gs2::Stamina::Request::FGetStaminaRequest>()
                );
                Task->StartSynchronousTask();
                if (Task->GetTask().IsError())
                {
                    Task->EnsureCompletion();
                    return Task->GetTask().Error();
                }
                *Result = Gs2::UE5::Stamina::Model::FEzStamina::FromModel(
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

    TSharedPtr<FAsyncTask<FEzStaminaGameSessionDomain::FGetStaminaTask>> FEzStaminaGameSessionDomain::GetStamina(
    )
    {
        return Gs2::Core::Util::New<FAsyncTask<FGetStaminaTask>>(
            this->AsShared()
        );
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
        const auto Future = Self->ProfileValue->Run<FConsumeTask>(
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

    TSharedPtr<FAsyncTask<FEzStaminaGameSessionDomain::FConsumeTask>> FEzStaminaGameSessionDomain::Consume(
        int32 ConsumeValue
    )
    {
        return Gs2::Core::Util::New<FAsyncTask<FConsumeTask>>(
            this->AsShared(),
            ConsumeValue
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
        const auto Future = Self->ProfileValue->Run<FModelTask>(
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
}
