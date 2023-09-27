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

#include "Matchmaking/Domain/Model/Gs2MatchmakingEzBallotGameSessionDomain.h"

namespace Gs2::UE5::Matchmaking::Domain::Model
{

    TOptional<FString> FEzBallotGameSessionDomain::Body() const
    {
        return Domain->Body;
    }

    TOptional<FString> FEzBallotGameSessionDomain::Signature() const
    {
        return Domain->Signature;
    }

    TOptional<FString> FEzBallotGameSessionDomain::NamespaceName() const
    {
        return Domain->NamespaceName;
    }

    TOptional<FString> FEzBallotGameSessionDomain::UserId() const
    {
        return Domain->UserId();
    }

    TOptional<FString> FEzBallotGameSessionDomain::RatingName() const
    {
        return Domain->RatingName;
    }

    TOptional<FString> FEzBallotGameSessionDomain::GatheringName() const
    {
        return Domain->GatheringName;
    }

    TOptional<int32> FEzBallotGameSessionDomain::NumberOfPlayer() const
    {
        return Domain->NumberOfPlayer;
    }

    TOptional<FString> FEzBallotGameSessionDomain::KeyId() const
    {
        return Domain->KeyId;
    }

    FEzBallotGameSessionDomain::FEzBallotGameSessionDomain(
        Gs2::Matchmaking::Domain::Model::FBallotAccessTokenDomainPtr Domain,
        Gs2::UE5::Util::FProfilePtr Profile
    ): Domain(Domain), ProfileValue(Profile) {

    }

    FEzBallotGameSessionDomain::FCreateVoteTask::FCreateVoteTask(
        TSharedPtr<FEzBallotGameSessionDomain> Self
    ): Self(Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FEzBallotGameSessionDomain::FCreateVoteTask::Action(
        TSharedPtr<TSharedPtr<Gs2::UE5::Matchmaking::Domain::Model::FEzBallotGameSessionDomain>> Result
    )
    {
        const auto Future = Self->ProfileValue->Run<FCreateVoteTask>(
            [&]() -> Gs2::Core::Model::FGs2ErrorPtr {
                const auto Task = Self->Domain->Get(
                    MakeShared<Gs2::Matchmaking::Request::FGetBallotRequest>()
                );
                Task->StartSynchronousTask();
                if (Task->GetTask().IsError())
                {
                    Task->EnsureCompletion();
                    return Task->GetTask().Error();
                }
                *Result = MakeShared<Gs2::UE5::Matchmaking::Domain::Model::FEzBallotGameSessionDomain>(
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

    TSharedPtr<FAsyncTask<FEzBallotGameSessionDomain::FCreateVoteTask>> FEzBallotGameSessionDomain::CreateVote(
    )
    {
        return Gs2::Core::Util::New<FAsyncTask<FCreateVoteTask>>(
            this->AsShared()
        );
    }

    FEzBallotGameSessionDomain::FModelTask::FModelTask(
        TSharedPtr<FEzBallotGameSessionDomain> Self
    ): Self(Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FEzBallotGameSessionDomain::FModelTask::Action(
        TSharedPtr<Gs2::UE5::Matchmaking::Model::FEzBallotPtr> Result
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
                *Result = Gs2::UE5::Matchmaking::Model::FEzBallot::FromModel(Task->GetTask().Result());
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

    TSharedPtr<FAsyncTask<FEzBallotGameSessionDomain::FModelTask>> FEzBallotGameSessionDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FModelTask>>(this->AsShared());
    }

    Gs2::Core::Domain::CallbackID FEzBallotGameSessionDomain::Subscribe(TFunction<void(Gs2::UE5::Matchmaking::Model::FEzBallotPtr)> Callback)
    {
        return Domain->Subscribe(
            [&](Gs2::Matchmaking::Model::FBallotPtr Item)
            {
                Callback(Gs2::UE5::Matchmaking::Model::FEzBallot::FromModel(Item));
            }
        );
    }

    void FEzBallotGameSessionDomain::Unsubscribe(Gs2::Core::Domain::CallbackID CallbackId)
    {
        Domain->Unsubscribe(
            CallbackId
        );
    }
}
