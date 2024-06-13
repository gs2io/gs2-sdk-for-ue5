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

#include "Enhance/Domain/Model/Gs2EnhanceEzEnhanceGameSessionDomain.h"

namespace Gs2::UE5::Enhance::Domain::Model
{

    TOptional<FString> FEzEnhanceGameSessionDomain::TransactionId() const
    {
        return Domain->TransactionId;
    }

    TOptional<bool> FEzEnhanceGameSessionDomain::AutoRunStampSheet() const
    {
        return Domain->AutoRunStampSheet;
    }

    TOptional<int64> FEzEnhanceGameSessionDomain::AcquireExperience() const
    {
        return Domain->AcquireExperience;
    }

    TOptional<float> FEzEnhanceGameSessionDomain::BonusRate() const
    {
        return Domain->BonusRate;
    }

    TOptional<FString> FEzEnhanceGameSessionDomain::NamespaceName() const
    {
        return Domain->NamespaceName;
    }

    TOptional<FString> FEzEnhanceGameSessionDomain::UserId() const
    {
        return Domain->UserId();
    }

    FEzEnhanceGameSessionDomain::FEzEnhanceGameSessionDomain(
        Gs2::Enhance::Domain::Model::FEnhanceAccessTokenDomainPtr Domain,
        Gs2::UE5::Util::IGameSessionPtr GameSession,
        Gs2::UE5::Util::FGs2ConnectionPtr Connection
    ):
        Domain(Domain),
        GameSession(GameSession),
        ConnectionValue(Connection)
    {

    }

    FEzEnhanceGameSessionDomain::FEnhanceTask::FEnhanceTask(
        TSharedPtr<FEzEnhanceGameSessionDomain> Self,
        FString RateName,
        FString TargetItemSetId,
        TArray<TSharedPtr<Gs2::UE5::Enhance::Model::FEzMaterial>> Materials,
        TOptional<TArray<TSharedPtr<Gs2::UE5::Enhance::Model::FEzConfig>>> Config
    ): Self(Self), RateName(RateName), TargetItemSetId(TargetItemSetId), Materials(Materials), Config(Config)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FEzEnhanceGameSessionDomain::FEnhanceTask::Action(
        TSharedPtr<TSharedPtr<Gs2::UE5::Enhance::Domain::Model::FEzEnhanceGameSessionDomain>> Result
    )
    {
        const auto Future = Self->ConnectionValue->Run(
            [&]() -> Gs2::Core::Model::FGs2ErrorPtr {
                const auto Task = Self->Domain->Direct(
                    MakeShared<Gs2::Enhance::Request::FDirectEnhanceRequest>()
                        ->WithRateName(RateName)
                        ->WithTargetItemSetId(TargetItemSetId)
                        ->WithMaterials([&]{
                            auto Arr = MakeShared<TArray<TSharedPtr<Gs2::Enhance::Model::FMaterial>>>();
                            for (auto Value : Materials) {
                                Arr->Add(Value->ToModel());
                            }
                            return Arr;
                        }())
                        ->WithConfig([&]{
                            auto Arr = MakeShared<TArray<TSharedPtr<Gs2::Enhance::Model::FConfig>>>();
                            if (!Config.IsSet()) {
                                return Arr;
                            }
                            for (auto Value : *Config) {
                                Arr->Add(Value->ToModel());
                            }
                            return Arr;
                        }())
                );
                Task->StartSynchronousTask();
                if (Task->GetTask().IsError())
                {
                    Task->EnsureCompletion();
                    return Task->GetTask().Error();
                }
                *Result = MakeShared<Gs2::UE5::Enhance::Domain::Model::FEzEnhanceGameSessionDomain>(
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

    TSharedPtr<FAsyncTask<FEzEnhanceGameSessionDomain::FEnhanceTask>> FEzEnhanceGameSessionDomain::Enhance(
        FString RateName,
        FString TargetItemSetId,
        TArray<TSharedPtr<Gs2::UE5::Enhance::Model::FEzMaterial>> Materials,
        TOptional<TArray<TSharedPtr<Gs2::UE5::Enhance::Model::FEzConfig>>> Config
    )
    {
        return Gs2::Core::Util::New<FAsyncTask<FEnhanceTask>>(
            this->AsShared(),
            RateName,
            TargetItemSetId,
            Materials,
            Config
        );
    }
}
