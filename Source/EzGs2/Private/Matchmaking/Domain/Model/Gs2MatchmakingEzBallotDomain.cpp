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

#include "Matchmaking/Domain/Model/Gs2MatchmakingEzBallotDomain.h"

namespace Gs2::UE5::Matchmaking::Domain::Model
{

    TOptional<FString> FEzBallotDomain::Body() const
    {
        return Domain->Body;
    }

    TOptional<FString> FEzBallotDomain::Signature() const
    {
        return Domain->Signature;
    }

    TOptional<FString> FEzBallotDomain::NamespaceName() const
    {
        return Domain->NamespaceName;
    }

    TOptional<FString> FEzBallotDomain::UserId() const
    {
        return Domain->UserId;
    }

    TOptional<FString> FEzBallotDomain::RatingName() const
    {
        return Domain->RatingName;
    }

    TOptional<FString> FEzBallotDomain::GatheringName() const
    {
        return Domain->GatheringName;
    }

    TOptional<int32> FEzBallotDomain::NumberOfPlayer() const
    {
        return Domain->NumberOfPlayer;
    }

    TOptional<FString> FEzBallotDomain::KeyId() const
    {
        return Domain->KeyId;
    }

    FEzBallotDomain::FEzBallotDomain(
        Gs2::Matchmaking::Domain::Model::FBallotDomainPtr Domain,
        Gs2::UE5::Util::FGs2ConnectionPtr Connection
    ):
        Domain(Domain),
        ConnectionValue(Connection)
    {

    }

    FEzBallotDomain::FModelTask::FModelTask(
        TSharedPtr<FEzBallotDomain> Self
    ): Self(Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FEzBallotDomain::FModelTask::Action(
        TSharedPtr<Gs2::UE5::Matchmaking::Model::FEzBallotPtr> Result
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

    TSharedPtr<FAsyncTask<FEzBallotDomain::FModelTask>> FEzBallotDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FModelTask>>(this->AsShared());
    }

    Gs2::Core::Domain::CallbackID FEzBallotDomain::Subscribe(TFunction<void(Gs2::UE5::Matchmaking::Model::FEzBallotPtr)> Callback)
    {
        return Domain->Subscribe(
            [&](Gs2::Matchmaking::Model::FBallotPtr Item)
            {
                Callback(Gs2::UE5::Matchmaking::Model::FEzBallot::FromModel(Item));
            }
        );
    }

    void FEzBallotDomain::Unsubscribe(Gs2::Core::Domain::CallbackID CallbackId)
    {
        Domain->Unsubscribe(
            CallbackId
        );
    }
}
