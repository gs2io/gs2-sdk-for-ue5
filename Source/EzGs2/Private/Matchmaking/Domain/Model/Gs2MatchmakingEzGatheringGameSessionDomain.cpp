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

#include "Matchmaking/Domain/Model/Gs2MatchmakingEzGatheringGameSessionDomain.h"

namespace Gs2::UE5::Matchmaking::Domain::Model
{

    TOptional<FString> FEzGatheringGameSessionDomain::NamespaceName() const
    {
        return Domain->NamespaceName;
    }

    TOptional<FString> FEzGatheringGameSessionDomain::UserId() const
    {
        return Domain->UserId();
    }

    TOptional<FString> FEzGatheringGameSessionDomain::GatheringName() const
    {
        return Domain->GatheringName;
    }

    FEzGatheringGameSessionDomain::FEzGatheringGameSessionDomain(
        Gs2::Matchmaking::Domain::Model::FGatheringAccessTokenDomainPtr Domain,
        Gs2::UE5::Util::FGameSessionPtr GameSession,
        Gs2::UE5::Util::FGs2ConnectionPtr Connection
    ):
        Domain(Domain),
        GameSession(GameSession),
        ConnectionValue(Connection)
    {

    }

    FEzGatheringGameSessionDomain::FUpdateGatheringTask::FUpdateGatheringTask(
        TSharedPtr<FEzGatheringGameSessionDomain> Self,
        TOptional<TArray<TSharedPtr<Gs2::UE5::Matchmaking::Model::FEzAttributeRange>>> AttributeRanges
    ): Self(Self), AttributeRanges(AttributeRanges)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FEzGatheringGameSessionDomain::FUpdateGatheringTask::Action(
        TSharedPtr<TSharedPtr<Gs2::UE5::Matchmaking::Domain::Model::FEzGatheringGameSessionDomain>> Result
    )
    {
        const auto Future = Self->ConnectionValue->Run(
            [&]() -> Gs2::Core::Model::FGs2ErrorPtr {
                const auto Task = Self->Domain->Update(
                    MakeShared<Gs2::Matchmaking::Request::FUpdateGatheringRequest>()
                        ->WithAttributeRanges([&]{
                            auto Arr = MakeShared<TArray<TSharedPtr<Gs2::Matchmaking::Model::FAttributeRange>>>();
                            if (!AttributeRanges.IsSet()) {
                                return Arr;
                            }
                            for (auto Value : *AttributeRanges) {
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
                *Result = MakeShared<Gs2::UE5::Matchmaking::Domain::Model::FEzGatheringGameSessionDomain>(
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

    TSharedPtr<FAsyncTask<FEzGatheringGameSessionDomain::FUpdateGatheringTask>> FEzGatheringGameSessionDomain::UpdateGathering(
        TOptional<TArray<TSharedPtr<Gs2::UE5::Matchmaking::Model::FEzAttributeRange>>> AttributeRanges
    )
    {
        return Gs2::Core::Util::New<FAsyncTask<FUpdateGatheringTask>>(
            this->AsShared(),
            AttributeRanges
        );
    }

    FEzGatheringGameSessionDomain::FCancelMatchmakingTask::FCancelMatchmakingTask(
        TSharedPtr<FEzGatheringGameSessionDomain> Self
    ): Self(Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FEzGatheringGameSessionDomain::FCancelMatchmakingTask::Action(
        TSharedPtr<TSharedPtr<Gs2::UE5::Matchmaking::Domain::Model::FEzGatheringGameSessionDomain>> Result
    )
    {
        const auto Future = Self->ConnectionValue->Run(
            [&]() -> Gs2::Core::Model::FGs2ErrorPtr {
                const auto Task = Self->Domain->CancelMatchmaking(
                    MakeShared<Gs2::Matchmaking::Request::FCancelMatchmakingRequest>()
                );
                Task->StartSynchronousTask();
                if (Task->GetTask().IsError())
                {
                    Task->EnsureCompletion();
                    return Task->GetTask().Error();
                }
                *Result = MakeShared<Gs2::UE5::Matchmaking::Domain::Model::FEzGatheringGameSessionDomain>(
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

    TSharedPtr<FAsyncTask<FEzGatheringGameSessionDomain::FCancelMatchmakingTask>> FEzGatheringGameSessionDomain::CancelMatchmaking(
    )
    {
        return Gs2::Core::Util::New<FAsyncTask<FCancelMatchmakingTask>>(
            this->AsShared()
        );
    }

    FEzGatheringGameSessionDomain::FEarlyCompleteMatchmakingTask::FEarlyCompleteMatchmakingTask(
        TSharedPtr<FEzGatheringGameSessionDomain> Self
    ): Self(Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FEzGatheringGameSessionDomain::FEarlyCompleteMatchmakingTask::Action(
        TSharedPtr<TSharedPtr<Gs2::UE5::Matchmaking::Domain::Model::FEzGatheringGameSessionDomain>> Result
    )
    {
        const auto Future = Self->ConnectionValue->Run(
            [&]() -> Gs2::Core::Model::FGs2ErrorPtr {
                const auto Task = Self->Domain->EarlyComplete(
                    MakeShared<Gs2::Matchmaking::Request::FEarlyCompleteRequest>()
                );
                Task->StartSynchronousTask();
                if (Task->GetTask().IsError())
                {
                    Task->EnsureCompletion();
                    return Task->GetTask().Error();
                }
                *Result = MakeShared<Gs2::UE5::Matchmaking::Domain::Model::FEzGatheringGameSessionDomain>(
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

    TSharedPtr<FAsyncTask<FEzGatheringGameSessionDomain::FEarlyCompleteMatchmakingTask>> FEzGatheringGameSessionDomain::EarlyCompleteMatchmaking(
    )
    {
        return Gs2::Core::Util::New<FAsyncTask<FEarlyCompleteMatchmakingTask>>(
            this->AsShared()
        );
    }

    FEzGatheringGameSessionDomain::FModelTask::FModelTask(
        TSharedPtr<FEzGatheringGameSessionDomain> Self
    ): Self(Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FEzGatheringGameSessionDomain::FModelTask::Action(
        TSharedPtr<Gs2::UE5::Matchmaking::Model::FEzGatheringPtr> Result
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
                *Result = Gs2::UE5::Matchmaking::Model::FEzGathering::FromModel(Task->GetTask().Result());
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

    TSharedPtr<FAsyncTask<FEzGatheringGameSessionDomain::FModelTask>> FEzGatheringGameSessionDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FModelTask>>(this->AsShared());
    }

    Gs2::Core::Domain::CallbackID FEzGatheringGameSessionDomain::Subscribe(TFunction<void(Gs2::UE5::Matchmaking::Model::FEzGatheringPtr)> Callback)
    {
        return Domain->Subscribe(
            [&](Gs2::Matchmaking::Model::FGatheringPtr Item)
            {
                Callback(Gs2::UE5::Matchmaking::Model::FEzGathering::FromModel(Item));
            }
        );
    }

    void FEzGatheringGameSessionDomain::Unsubscribe(Gs2::Core::Domain::CallbackID CallbackId)
    {
        Domain->Unsubscribe(
            CallbackId
        );
    }
}
