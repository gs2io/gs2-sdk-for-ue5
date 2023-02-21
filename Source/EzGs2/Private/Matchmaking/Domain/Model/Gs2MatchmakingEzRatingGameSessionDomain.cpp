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

#include "Matchmaking/Domain/Model/Gs2MatchmakingEzRatingGameSessionDomain.h"

namespace Gs2::UE5::Matchmaking::Domain::Model
{

    TOptional<FString> FEzRatingGameSessionDomain::NamespaceName() const
    {
        return Domain->NamespaceName;
    }

    TOptional<FString> FEzRatingGameSessionDomain::UserId() const
    {
        return Domain->UserId();
    }

    TOptional<FString> FEzRatingGameSessionDomain::RatingName() const
    {
        return Domain->RatingName;
    }

    FEzRatingGameSessionDomain::FEzRatingGameSessionDomain(
        Gs2::Matchmaking::Domain::Model::FRatingAccessTokenDomainPtr Domain,
        Gs2::UE5::Util::FProfilePtr Profile
    ): Domain(Domain), ProfileValue(Profile) {

    }

    FEzRatingGameSessionDomain::FGetRatingTask::FGetRatingTask(
        TSharedPtr<FEzRatingGameSessionDomain> Self
    ): Self(Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FEzRatingGameSessionDomain::FGetRatingTask::Action(
        TSharedPtr<TSharedPtr<Gs2::UE5::Matchmaking::Model::FEzRating>> Result
    )
    {
        const auto Future = Self->ProfileValue->Run<FGetRatingTask>(
            [&]() -> Gs2::Core::Model::FGs2ErrorPtr {
                const auto Task = Self->Domain->Get(
                    MakeShared<Gs2::Matchmaking::Request::FGetRatingRequest>()
                );
                Task->StartSynchronousTask();
                if (Task->GetTask().IsError())
                {
                    Task->EnsureCompletion();
                    return Task->GetTask().Error();
                }
                *Result = Gs2::UE5::Matchmaking::Model::FEzRating::FromModel(
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

    TSharedPtr<FAsyncTask<FEzRatingGameSessionDomain::FGetRatingTask>> FEzRatingGameSessionDomain::GetRating(
    )
    {
        return Gs2::Core::Util::New<FAsyncTask<FGetRatingTask>>(
            this->AsShared()
        );
    }

    FEzRatingGameSessionDomain::FModelTask::FModelTask(
        TSharedPtr<FEzRatingGameSessionDomain> Self
    ): Self(Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FEzRatingGameSessionDomain::FModelTask::Action(
        TSharedPtr<Gs2::UE5::Matchmaking::Model::FEzRatingPtr> Result
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
                *Result = Gs2::UE5::Matchmaking::Model::FEzRating::FromModel(Task->GetTask().Result());
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

    TSharedPtr<FAsyncTask<FEzRatingGameSessionDomain::FModelTask>> FEzRatingGameSessionDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FModelTask>>(this->AsShared());
    }
}
