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

#include "Ranking/Domain/Model/Gs2RankingEzSubscribeUserGameSessionDomain.h"

namespace Gs2::UE5::Ranking::Domain::Model
{

    TOptional<FString> FEzSubscribeUserGameSessionDomain::NamespaceName() const
    {
        return Domain->NamespaceName;
    }

    TOptional<FString> FEzSubscribeUserGameSessionDomain::UserId() const
    {
        return Domain->UserId();
    }

    TOptional<FString> FEzSubscribeUserGameSessionDomain::CategoryName() const
    {
        return Domain->CategoryName;
    }

    TOptional<FString> FEzSubscribeUserGameSessionDomain::AdditionalScopeName() const
    {
        return Domain->AdditionalScopeName;
    }

    TOptional<FString> FEzSubscribeUserGameSessionDomain::TargetUserId() const
    {
        return Domain->TargetUserId;
    }

    FEzSubscribeUserGameSessionDomain::FEzSubscribeUserGameSessionDomain(
        Gs2::Ranking::Domain::Model::FSubscribeUserAccessTokenDomainPtr Domain,
        Gs2::UE5::Util::FGameSessionPtr GameSession,
        Gs2::UE5::Util::FGs2ConnectionPtr Connection
    ):
        Domain(Domain),
        GameSession(GameSession),
        ConnectionValue(Connection)
    {

    }

    FEzSubscribeUserGameSessionDomain::FUnsubscribeTask::FUnsubscribeTask(
        TSharedPtr<FEzSubscribeUserGameSessionDomain> Self
    ): Self(Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FEzSubscribeUserGameSessionDomain::FUnsubscribeTask::Action(
        TSharedPtr<TSharedPtr<Gs2::UE5::Ranking::Domain::Model::FEzSubscribeUserGameSessionDomain>> Result
    )
    {
        const auto Future = Self->ConnectionValue->Run(
            [&]() -> Gs2::Core::Model::FGs2ErrorPtr {
                const auto Task = Self->Domain->Unsubscribe(
                    MakeShared<Gs2::Ranking::Request::FUnsubscribeRequest>()
                );
                Task->StartSynchronousTask();
                if (Task->GetTask().IsError())
                {
                    Task->EnsureCompletion();
                    return Task->GetTask().Error();
                }
                *Result = MakeShared<Gs2::UE5::Ranking::Domain::Model::FEzSubscribeUserGameSessionDomain>(
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

    TSharedPtr<FAsyncTask<FEzSubscribeUserGameSessionDomain::FUnsubscribeTask>> FEzSubscribeUserGameSessionDomain::Unsubscribe(
    )
    {
        return Gs2::Core::Util::New<FAsyncTask<FUnsubscribeTask>>(
            this->AsShared()
        );
    }

    FEzSubscribeUserGameSessionDomain::FModelTask::FModelTask(
        TSharedPtr<FEzSubscribeUserGameSessionDomain> Self
    ): Self(Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FEzSubscribeUserGameSessionDomain::FModelTask::Action(
        TSharedPtr<Gs2::UE5::Ranking::Model::FEzSubscribeUserPtr> Result
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
                *Result = Gs2::UE5::Ranking::Model::FEzSubscribeUser::FromModel(Task->GetTask().Result());
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

    TSharedPtr<FAsyncTask<FEzSubscribeUserGameSessionDomain::FModelTask>> FEzSubscribeUserGameSessionDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FModelTask>>(this->AsShared());
    }

    Gs2::Core::Domain::CallbackID FEzSubscribeUserGameSessionDomain::Subscribe(TFunction<void(Gs2::UE5::Ranking::Model::FEzSubscribeUserPtr)> Callback)
    {
        return Domain->Subscribe(
            [&](Gs2::Ranking::Model::FSubscribeUserPtr Item)
            {
                Callback(Gs2::UE5::Ranking::Model::FEzSubscribeUser::FromModel(Item));
            }
        );
    }

    void FEzSubscribeUserGameSessionDomain::Unsubscribe(Gs2::Core::Domain::CallbackID CallbackId)
    {
        Domain->Unsubscribe(
            CallbackId
        );
    }
}
