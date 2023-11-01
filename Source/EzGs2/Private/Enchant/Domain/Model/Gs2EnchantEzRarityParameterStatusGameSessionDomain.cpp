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

#include "Enchant/Domain/Model/Gs2EnchantEzRarityParameterStatusGameSessionDomain.h"

namespace Gs2::UE5::Enchant::Domain::Model
{

    TOptional<FString> FEzRarityParameterStatusGameSessionDomain::NamespaceName() const
    {
        return Domain->NamespaceName;
    }

    TOptional<FString> FEzRarityParameterStatusGameSessionDomain::UserId() const
    {
        return Domain->UserId();
    }

    TOptional<FString> FEzRarityParameterStatusGameSessionDomain::ParameterName() const
    {
        return Domain->ParameterName;
    }

    TOptional<FString> FEzRarityParameterStatusGameSessionDomain::PropertyId() const
    {
        return Domain->PropertyId;
    }

    FEzRarityParameterStatusGameSessionDomain::FEzRarityParameterStatusGameSessionDomain(
        Gs2::Enchant::Domain::Model::FRarityParameterStatusAccessTokenDomainPtr Domain,
        Gs2::UE5::Util::FProfilePtr Profile
    ): Domain(Domain), ProfileValue(Profile) {

    }

    FEzRarityParameterStatusGameSessionDomain::FVerifyRarityParameterStatusTask::FVerifyRarityParameterStatusTask(
        TSharedPtr<FEzRarityParameterStatusGameSessionDomain> Self,
        FString VerifyType,
        FString ParameterValueName,
        int32 ParameterCount
    ): Self(Self), VerifyType(VerifyType), ParameterValueName(ParameterValueName), ParameterCount(ParameterCount)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FEzRarityParameterStatusGameSessionDomain::FVerifyRarityParameterStatusTask::Action(
        TSharedPtr<TSharedPtr<Gs2::UE5::Enchant::Domain::Model::FEzRarityParameterStatusGameSessionDomain>> Result
    )
    {
        const auto Future = Self->ProfileValue->Run<FVerifyRarityParameterStatusTask>(
            [&]() -> Gs2::Core::Model::FGs2ErrorPtr {
                const auto Task = Self->Domain->Verify(
                    MakeShared<Gs2::Enchant::Request::FVerifyRarityParameterStatusRequest>()
                        ->WithVerifyType(VerifyType)
                        ->WithParameterValueName(ParameterValueName)
                        ->WithParameterCount(ParameterCount)
                );
                Task->StartSynchronousTask();
                if (Task->GetTask().IsError())
                {
                    Task->EnsureCompletion();
                    return Task->GetTask().Error();
                }
                *Result = MakeShared<Gs2::UE5::Enchant::Domain::Model::FEzRarityParameterStatusGameSessionDomain>(
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

    TSharedPtr<FAsyncTask<FEzRarityParameterStatusGameSessionDomain::FVerifyRarityParameterStatusTask>> FEzRarityParameterStatusGameSessionDomain::VerifyRarityParameterStatus(
        FString VerifyType,
        FString ParameterValueName,
        int32 ParameterCount
    )
    {
        return Gs2::Core::Util::New<FAsyncTask<FVerifyRarityParameterStatusTask>>(
            this->AsShared(),
            VerifyType,
            ParameterValueName,
            ParameterCount
        );
    }

    FEzRarityParameterStatusGameSessionDomain::FModelTask::FModelTask(
        TSharedPtr<FEzRarityParameterStatusGameSessionDomain> Self
    ): Self(Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FEzRarityParameterStatusGameSessionDomain::FModelTask::Action(
        TSharedPtr<Gs2::UE5::Enchant::Model::FEzRarityParameterStatusPtr> Result
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
                *Result = Gs2::UE5::Enchant::Model::FEzRarityParameterStatus::FromModel(Task->GetTask().Result());
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

    TSharedPtr<FAsyncTask<FEzRarityParameterStatusGameSessionDomain::FModelTask>> FEzRarityParameterStatusGameSessionDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FModelTask>>(this->AsShared());
    }

    Gs2::Core::Domain::CallbackID FEzRarityParameterStatusGameSessionDomain::Subscribe(TFunction<void(Gs2::UE5::Enchant::Model::FEzRarityParameterStatusPtr)> Callback)
    {
        return Domain->Subscribe(
            [&](Gs2::Enchant::Model::FRarityParameterStatusPtr Item)
            {
                Callback(Gs2::UE5::Enchant::Model::FEzRarityParameterStatus::FromModel(Item));
            }
        );
    }

    void FEzRarityParameterStatusGameSessionDomain::Unsubscribe(Gs2::Core::Domain::CallbackID CallbackId)
    {
        Domain->Unsubscribe(
            CallbackId
        );
    }
}
