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
 *
 * deny overwrite
 */

#include "MegaField/Domain/Model/Gs2MegaFieldEzSpatialGameSessionDomain.h"

namespace Gs2::UE5::MegaField::Domain::Model
{

    TOptional<FString> FEzSpatialGameSessionDomain::NamespaceName() const
    {
        return Domain->NamespaceName;
    }

    TOptional<FString> FEzSpatialGameSessionDomain::UserId() const
    {
        return Domain->UserId();
    }

    TOptional<FString> FEzSpatialGameSessionDomain::AreaModelName() const
    {
        return Domain->AreaModelName;
    }

    TOptional<FString> FEzSpatialGameSessionDomain::LayerModelName() const
    {
        return Domain->LayerModelName;
    }

    FEzSpatialGameSessionDomain::FEzSpatialGameSessionDomain(
        Gs2::MegaField::Domain::Model::FSpatialAccessTokenDomainPtr Domain,
        Gs2::UE5::Util::FGameSessionPtr GameSession,
        Gs2::UE5::Util::FGs2ConnectionPtr Connection
    ):
        Domain(Domain),
        GameSession(GameSession),
        ConnectionValue(Connection)
    {

    }

    FEzSpatialGameSessionDomain::FUpdateTask::FUpdateTask(
        TSharedPtr<FEzSpatialGameSessionDomain> Self,
        Gs2::UE5::MegaField::Model::FEzMyPositionPtr Position,
        TOptional<TArray<TSharedPtr<Gs2::UE5::MegaField::Model::FEzScope>>> Scopes
    ): Self(Self), Position(Position), Scopes(Scopes)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FEzSpatialGameSessionDomain::FUpdateTask::Action(
        TSharedPtr<TSharedPtr<TArray<TSharedPtr<Gs2::UE5::MegaField::Domain::Model::FEzSpatialDomain>>>> Result
    )
    {
        const auto Future = Self->ConnectionValue->Run(
            [&]() -> Gs2::Core::Model::FGs2ErrorPtr {
                const auto Task = Self->Domain->Action(
                    MakeShared<Gs2::MegaField::Request::FActionRequest>()
                        ->WithPosition(Position == nullptr ? nullptr : Position->ToModel())
                        ->WithScopes([&]{
                            auto Arr = MakeShared<TArray<TSharedPtr<Gs2::MegaField::Model::FScope>>>();
                            if (!Scopes.IsSet()) {
                                return Arr;
                            }
                            for (auto Value : *Scopes) {
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
                *Result = MakeShared<TArray<TSharedPtr<Gs2::UE5::MegaField::Domain::Model::FEzSpatialDomain>>>();
                for (auto Value : *Task->GetTask().Result()) {
                    (**Result).Add(MakeShared<Gs2::UE5::MegaField::Domain::Model::FEzSpatialDomain>(
                        Value,
                        Self->ConnectionValue
                    ));
                }
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

    TSharedPtr<FAsyncTask<FEzSpatialGameSessionDomain::FUpdateTask>> FEzSpatialGameSessionDomain::Update(
        Gs2::UE5::MegaField::Model::FEzMyPositionPtr Position,
        TOptional<TArray<TSharedPtr<Gs2::UE5::MegaField::Model::FEzScope>>> Scopes
    )
    {
        return Gs2::Core::Util::New<FAsyncTask<FUpdateTask>>(
            this->AsShared(),
            Position,
            Scopes
        );
    }

    FEzSpatialGameSessionDomain::FModelTask::FModelTask(
        TSharedPtr<FEzSpatialGameSessionDomain> Self
    ): Self(Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FEzSpatialGameSessionDomain::FModelTask::Action(
        TSharedPtr<Gs2::UE5::MegaField::Model::FEzSpatialPtr> Result
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
                *Result = Gs2::UE5::MegaField::Model::FEzSpatial::FromModel(Task->GetTask().Result());
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

    TSharedPtr<FAsyncTask<FEzSpatialGameSessionDomain::FModelTask>> FEzSpatialGameSessionDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FModelTask>>(this->AsShared());
    }
}
