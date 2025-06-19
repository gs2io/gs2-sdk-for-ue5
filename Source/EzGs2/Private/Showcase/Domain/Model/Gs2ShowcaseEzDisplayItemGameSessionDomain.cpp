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

#include "Showcase/Domain/Model/Gs2ShowcaseEzDisplayItemGameSessionDomain.h"

namespace Gs2::UE5::Showcase::Domain::Model
{

    TOptional<FString> FEzDisplayItemGameSessionDomain::NamespaceName() const
    {
        return Domain->NamespaceName;
    }

    TOptional<FString> FEzDisplayItemGameSessionDomain::UserId() const
    {
        return Domain->UserId();
    }

    TOptional<FString> FEzDisplayItemGameSessionDomain::ShowcaseName() const
    {
        return Domain->ShowcaseName;
    }

    TOptional<FString> FEzDisplayItemGameSessionDomain::DisplayItemId() const
    {
        return Domain->DisplayItemId;
    }

    FEzDisplayItemGameSessionDomain::FEzDisplayItemGameSessionDomain(
        Gs2::Showcase::Domain::Model::FDisplayItemAccessTokenDomainPtr Domain,
        Gs2::UE5::Util::IGameSessionPtr GameSession,
        Gs2::UE5::Util::FGs2ConnectionPtr Connection
    ):
        Domain(Domain),
        GameSession(GameSession),
        ConnectionValue(Connection)
    {

    }

    FEzDisplayItemGameSessionDomain::FBuyTask::FBuyTask(
        TSharedPtr<FEzDisplayItemGameSessionDomain> Self,
        TOptional<int32> Quantity,
        TOptional<TArray<TSharedPtr<Gs2::UE5::Showcase::Model::FEzConfig>>> Config
    ): Self(Self), Quantity(Quantity), Config(Config)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FEzDisplayItemGameSessionDomain::FBuyTask::Action(
        TSharedPtr<TSharedPtr<Gs2::UE5::Core::Domain::FEzTransactionGameSessionDomain>> Result
    )
    {
        const auto Future = Self->ConnectionValue->Run(
            [&]() -> Gs2::Core::Model::FGs2ErrorPtr {
                const auto Task = Self->Domain->Buy(
                    MakeShared<Gs2::Showcase::Request::FBuyRequest>()
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
                *Result = MakeShared<Gs2::UE5::Core::Domain::FEzTransactionGameSessionDomain>(
                    Task->GetTask().Result(),
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

    TSharedPtr<FAsyncTask<FEzDisplayItemGameSessionDomain::FBuyTask>> FEzDisplayItemGameSessionDomain::Buy(
        TOptional<int32> Quantity,
        TOptional<TArray<TSharedPtr<Gs2::UE5::Showcase::Model::FEzConfig>>> Config
    )
    {
        return Gs2::Core::Util::New<FAsyncTask<FBuyTask>>(
            this->AsShared(),
            Quantity,
            Config
        );
    }

    FEzDisplayItemGameSessionDomain::FModelTask::FModelTask(
        TSharedPtr<FEzDisplayItemGameSessionDomain> Self
    ): Self(Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FEzDisplayItemGameSessionDomain::FModelTask::Action(
        TSharedPtr<Gs2::UE5::Showcase::Model::FEzDisplayItemPtr> Result
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
                *Result = Gs2::UE5::Showcase::Model::FEzDisplayItem::FromModel(Task->GetTask().Result());
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

    TSharedPtr<FAsyncTask<FEzDisplayItemGameSessionDomain::FModelTask>> FEzDisplayItemGameSessionDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FModelTask>>(this->AsShared());
    }

    Gs2::Core::Domain::CallbackID FEzDisplayItemGameSessionDomain::Subscribe(TFunction<void(Gs2::UE5::Showcase::Model::FEzDisplayItemPtr)> Callback)
    {
        return Domain->Subscribe(
            [&](Gs2::Showcase::Model::FDisplayItemPtr Item)
            {
                Callback(Gs2::UE5::Showcase::Model::FEzDisplayItem::FromModel(Item));
            }
        );
    }

    void FEzDisplayItemGameSessionDomain::Unsubscribe(Gs2::Core::Domain::CallbackID CallbackId)
    {
        Domain->Unsubscribe(
            CallbackId
        );
    }
}
