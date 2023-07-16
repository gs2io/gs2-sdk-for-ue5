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

#include "Showcase/Domain/Model/Gs2ShowcaseEzRandomDisplayItemGameSessionDomain.h"

namespace Gs2::UE5::Showcase::Domain::Model
{

    TOptional<FString> FEzRandomDisplayItemGameSessionDomain::TransactionId() const
    {
        return Domain->TransactionId;
    }

    TOptional<bool> FEzRandomDisplayItemGameSessionDomain::AutoRunStampSheet() const
    {
        return Domain->AutoRunStampSheet;
    }

    TOptional<FString> FEzRandomDisplayItemGameSessionDomain::NamespaceName() const
    {
        return Domain->NamespaceName;
    }

    TOptional<FString> FEzRandomDisplayItemGameSessionDomain::UserId() const
    {
        return Domain->UserId();
    }

    TOptional<FString> FEzRandomDisplayItemGameSessionDomain::ShowcaseName() const
    {
        return Domain->ShowcaseName;
    }

    TOptional<FString> FEzRandomDisplayItemGameSessionDomain::DisplayItemName() const
    {
        return Domain->DisplayItemName;
    }

    FEzRandomDisplayItemGameSessionDomain::FEzRandomDisplayItemGameSessionDomain(
        Gs2::Showcase::Domain::Model::FRandomDisplayItemAccessTokenDomainPtr Domain,
        Gs2::UE5::Util::FProfilePtr Profile
    ): Domain(Domain), ProfileValue(Profile) {

    }

    FEzRandomDisplayItemGameSessionDomain::FRandomShowcaseBuyTask::FRandomShowcaseBuyTask(
        TSharedPtr<FEzRandomDisplayItemGameSessionDomain> Self,
        TOptional<int32> Quantity,
        TOptional<TArray<TSharedPtr<Gs2::UE5::Showcase::Model::FEzConfig>>> Config
    ): Self(Self), Quantity(Quantity), Config(Config)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FEzRandomDisplayItemGameSessionDomain::FRandomShowcaseBuyTask::Action(
        TSharedPtr<TSharedPtr<Gs2::UE5::Showcase::Domain::Model::FEzRandomDisplayItemGameSessionDomain>> Result
    )
    {
        const auto Future = Self->ProfileValue->Run<FRandomShowcaseBuyTask>(
            [&]() -> Gs2::Core::Model::FGs2ErrorPtr {
                const auto Task = Self->Domain->RandomShowcaseBuy(
                    MakeShared<Gs2::Showcase::Request::FRandomShowcaseBuyRequest>()
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
                *Result = MakeShared<Gs2::UE5::Showcase::Domain::Model::FEzRandomDisplayItemGameSessionDomain>(
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

    TSharedPtr<FAsyncTask<FEzRandomDisplayItemGameSessionDomain::FRandomShowcaseBuyTask>> FEzRandomDisplayItemGameSessionDomain::RandomShowcaseBuy(
        TOptional<int32> Quantity,
        TOptional<TArray<TSharedPtr<Gs2::UE5::Showcase::Model::FEzConfig>>> Config
    )
    {
        return Gs2::Core::Util::New<FAsyncTask<FRandomShowcaseBuyTask>>(
            this->AsShared(),
            Quantity,
            Config
        );
    }

    FEzRandomDisplayItemGameSessionDomain::FModelTask::FModelTask(
        TSharedPtr<FEzRandomDisplayItemGameSessionDomain> Self
    ): Self(Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FEzRandomDisplayItemGameSessionDomain::FModelTask::Action(
        TSharedPtr<Gs2::UE5::Showcase::Model::FEzRandomDisplayItemPtr> Result
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
                *Result = Gs2::UE5::Showcase::Model::FEzRandomDisplayItem::FromModel(Task->GetTask().Result());
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

    TSharedPtr<FAsyncTask<FEzRandomDisplayItemGameSessionDomain::FModelTask>> FEzRandomDisplayItemGameSessionDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FModelTask>>(this->AsShared());
    }
}
