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

#include "Showcase/Domain/Model/Gs2ShowcaseEzShowcaseGameSessionDomain.h"

namespace Gs2::UE5::Showcase::Domain::Model
{

    TOptional<FString> FEzShowcaseGameSessionDomain::TransactionId() const
    {
        return Domain->TransactionId;
    }

    TOptional<bool> FEzShowcaseGameSessionDomain::AutoRunStampSheet() const
    {
        return Domain->AutoRunStampSheet;
    }

    TOptional<FString> FEzShowcaseGameSessionDomain::NamespaceName() const
    {
        return Domain->NamespaceName;
    }

    TOptional<FString> FEzShowcaseGameSessionDomain::UserId() const
    {
        return Domain->UserId();
    }

    TOptional<FString> FEzShowcaseGameSessionDomain::ShowcaseName() const
    {
        return Domain->ShowcaseName;
    }

    FEzShowcaseGameSessionDomain::FEzShowcaseGameSessionDomain(
        Gs2::Showcase::Domain::Model::FShowcaseAccessTokenDomainPtr Domain,
        Gs2::UE5::Util::FProfilePtr Profile
    ): Domain(Domain), ProfileValue(Profile) {

    }

    FEzShowcaseGameSessionDomain::FGetShowcaseTask::FGetShowcaseTask(
        TSharedPtr<FEzShowcaseGameSessionDomain> Self
    ): Self(Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FEzShowcaseGameSessionDomain::FGetShowcaseTask::Action(
        TSharedPtr<TSharedPtr<Gs2::UE5::Showcase::Model::FEzShowcase>> Result
    )
    {
        const auto Future = Self->ProfileValue->Run<FGetShowcaseTask>(
            [&]() -> Gs2::Core::Model::FGs2ErrorPtr {
                const auto Task = Self->Domain->Get(
                    MakeShared<Gs2::Showcase::Request::FGetShowcaseRequest>()
                );
                Task->StartSynchronousTask();
                if (Task->GetTask().IsError())
                {
                    Task->EnsureCompletion();
                    return Task->GetTask().Error();
                }
                *Result = Gs2::UE5::Showcase::Model::FEzShowcase::FromModel(
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

    TSharedPtr<FAsyncTask<FEzShowcaseGameSessionDomain::FGetShowcaseTask>> FEzShowcaseGameSessionDomain::GetShowcase(
    )
    {
        return Gs2::Core::Util::New<FAsyncTask<FGetShowcaseTask>>(
            this->AsShared()
        );
    }

    FEzShowcaseGameSessionDomain::FBuyTask::FBuyTask(
        TSharedPtr<FEzShowcaseGameSessionDomain> Self,
        TOptional<FString> DisplayItemId,
        TOptional<int32> Quantity,
        TOptional<TArray<TSharedPtr<Gs2::UE5::Showcase::Model::FEzConfig>>> Config
    ): Self(Self), DisplayItemId(DisplayItemId), Quantity(Quantity), Config(Config)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FEzShowcaseGameSessionDomain::FBuyTask::Action(
        TSharedPtr<TSharedPtr<Gs2::UE5::Showcase::Domain::Model::FEzShowcaseGameSessionDomain>> Result
    )
    {
        const auto Future = Self->ProfileValue->Run<FBuyTask>(
            [&]() -> Gs2::Core::Model::FGs2ErrorPtr {
                const auto Task = Self->Domain->Buy(
                    MakeShared<Gs2::Showcase::Request::FBuyRequest>()
                        ->WithDisplayItemId(DisplayItemId)
                        ->WithQuantity(Quantity)
                        ->WithConfig([&]{
                            auto Arr = MakeShared<TArray<TSharedPtr<Gs2::Showcase::Model::FConfig>>>();
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
                *Result = MakeShared<Gs2::UE5::Showcase::Domain::Model::FEzShowcaseGameSessionDomain>(
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

    TSharedPtr<FAsyncTask<FEzShowcaseGameSessionDomain::FBuyTask>> FEzShowcaseGameSessionDomain::Buy(
        TOptional<FString> DisplayItemId,
        TOptional<int32> Quantity,
        TOptional<TArray<TSharedPtr<Gs2::UE5::Showcase::Model::FEzConfig>>> Config
    )
    {
        return Gs2::Core::Util::New<FAsyncTask<FBuyTask>>(
            this->AsShared(),
            DisplayItemId,
            Quantity,
            Config
        );
    }

    FEzShowcaseGameSessionDomain::FModelTask::FModelTask(
        TSharedPtr<FEzShowcaseGameSessionDomain> Self
    ): Self(Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FEzShowcaseGameSessionDomain::FModelTask::Action(
        TSharedPtr<Gs2::UE5::Showcase::Model::FEzShowcasePtr> Result
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
                *Result = Gs2::UE5::Showcase::Model::FEzShowcase::FromModel(Task->GetTask().Result());
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

    TSharedPtr<FAsyncTask<FEzShowcaseGameSessionDomain::FModelTask>> FEzShowcaseGameSessionDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FModelTask>>(this->AsShared());
    }
}
