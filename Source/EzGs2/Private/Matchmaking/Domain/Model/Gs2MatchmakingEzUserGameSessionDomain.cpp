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

#include "Matchmaking/Domain/Model/Gs2MatchmakingEzUserGameSessionDomain.h"

namespace Gs2::UE5::Matchmaking::Domain::Model
{

    TOptional<FString> FEzUserGameSessionDomain::NextPageToken() const
    {
        return Domain->NextPageToken;
    }

    TOptional<FString> FEzUserGameSessionDomain::MatchmakingContextToken() const
    {
        return Domain->MatchmakingContextToken;
    }

    TOptional<FString> FEzUserGameSessionDomain::NamespaceName() const
    {
        return Domain->NamespaceName;
    }

    TOptional<FString> FEzUserGameSessionDomain::UserId() const
    {
        return Domain->UserId();
    }

    FEzUserGameSessionDomain::FEzUserGameSessionDomain(
        Gs2::Matchmaking::Domain::Model::FUserAccessTokenDomainPtr Domain,
        Gs2::UE5::Util::FProfilePtr Profile
    ): Domain(Domain), ProfileValue(Profile) {

    }

    FEzUserGameSessionDomain::FCreateGatheringTask::FCreateGatheringTask(
        TSharedPtr<FEzUserGameSessionDomain> Self,
        Gs2::UE5::Matchmaking::Model::FEzPlayerPtr Player,
        TOptional<TArray<TSharedPtr<Gs2::UE5::Matchmaking::Model::FEzAttributeRange>>> AttributeRanges,
        TOptional<TArray<TSharedPtr<Gs2::UE5::Matchmaking::Model::FEzCapacityOfRole>>> CapacityOfRoles,
        TOptional<TArray<FString>> AllowUserIds,
        TOptional<int64> ExpiresAt,
        Gs2::UE5::Matchmaking::Model::FEzTimeSpanPtr ExpiresAtTimeSpan
    ): Self(Self), Player(Player), AttributeRanges(AttributeRanges), CapacityOfRoles(CapacityOfRoles), AllowUserIds(AllowUserIds), ExpiresAt(ExpiresAt), ExpiresAtTimeSpan(ExpiresAtTimeSpan)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FEzUserGameSessionDomain::FCreateGatheringTask::Action(
        TSharedPtr<TSharedPtr<Gs2::UE5::Matchmaking::Domain::Model::FEzGatheringGameSessionDomain>> Result
    )
    {
        const auto Future = Self->ProfileValue->Run<FCreateGatheringTask>(
            [&]() -> Gs2::Core::Model::FGs2ErrorPtr {
                const auto Task = Self->Domain->CreateGathering(
                    MakeShared<Gs2::Matchmaking::Request::FCreateGatheringRequest>()
                        ->WithPlayer(Player->ToModel())
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
                        ->WithCapacityOfRoles([&]{
                            auto Arr = MakeShared<TArray<TSharedPtr<Gs2::Matchmaking::Model::FCapacityOfRole>>>();
                            if (!CapacityOfRoles.IsSet()) {
                                return Arr;
                            }
                            for (auto Value : *CapacityOfRoles) {
                                Arr->Add(Value->ToModel());
                            }
                            return Arr;
                        }())
                        ->WithAllowUserIds([&]{
                            auto Arr = MakeShared<TArray<FString>>();
                            if (!AllowUserIds.IsSet()) {
                                return Arr;
                            }
                            for (auto Value : *AllowUserIds) {
                                Arr->Add(Value);
                            }
                            return Arr;
                        }())
                        ->WithExpiresAt(ExpiresAt)
                        ->WithExpiresAtTimeSpan(ExpiresAtTimeSpan->ToModel())
                );
                Task->StartSynchronousTask();
                if (Task->GetTask().IsError())
                {
                    Task->EnsureCompletion();
                    return Task->GetTask().Error();
                }
                *Result = MakeShared<Gs2::UE5::Matchmaking::Domain::Model::FEzGatheringGameSessionDomain>(
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

    TSharedPtr<FAsyncTask<FEzUserGameSessionDomain::FCreateGatheringTask>> FEzUserGameSessionDomain::CreateGathering(
        Gs2::UE5::Matchmaking::Model::FEzPlayerPtr Player,
        TOptional<TArray<TSharedPtr<Gs2::UE5::Matchmaking::Model::FEzAttributeRange>>> AttributeRanges,
        TOptional<TArray<TSharedPtr<Gs2::UE5::Matchmaking::Model::FEzCapacityOfRole>>> CapacityOfRoles,
        TOptional<TArray<FString>> AllowUserIds,
        TOptional<int64> ExpiresAt,
        Gs2::UE5::Matchmaking::Model::FEzTimeSpanPtr ExpiresAtTimeSpan
    )
    {
        return Gs2::Core::Util::New<FAsyncTask<FCreateGatheringTask>>(
            this->AsShared(),
            Player,
            AttributeRanges,
            CapacityOfRoles,
            AllowUserIds,
            ExpiresAt,
            ExpiresAtTimeSpan
        );
    }

    Gs2::UE5::Matchmaking::Domain::Iterator::FEzDoMatchmakingIteratorPtr FEzUserGameSessionDomain::DoMatchmaking(
          const Gs2::UE5::Matchmaking::Model::FEzPlayerPtr Player
    ) const
    {
        return MakeShared<Gs2::UE5::Matchmaking::Domain::Iterator::FEzDoMatchmakingIterator>(
            Domain->DoMatchmaking(
                Player->ToModel()
            )
        );
    }

    Gs2::UE5::Matchmaking::Domain::Model::FEzGatheringGameSessionDomainPtr FEzUserGameSessionDomain::Gathering(
        const FString GatheringName
    ) const
    {
        return MakeShared<Gs2::UE5::Matchmaking::Domain::Model::FEzGatheringGameSessionDomain>(
            Domain->Gathering(
                GatheringName
            ),
            ProfileValue
        );
    }

    Gs2::UE5::Matchmaking::Domain::Model::FEzBallotGameSessionDomainPtr FEzUserGameSessionDomain::Ballot(
        const FString RatingName,
        const FString GatheringName,
        const int32 NumberOfPlayer,
        const FString KeyId
    ) const
    {
        return MakeShared<Gs2::UE5::Matchmaking::Domain::Model::FEzBallotGameSessionDomain>(
            Domain->Ballot(
                RatingName,
                GatheringName,
                NumberOfPlayer,
                KeyId
            ),
            ProfileValue
        );
    }

    Gs2::UE5::Matchmaking::Domain::Iterator::FEzDescribeRatingsIteratorPtr FEzUserGameSessionDomain::Ratings(
    ) const
    {
        return MakeShared<Gs2::UE5::Matchmaking::Domain::Iterator::FEzDescribeRatingsIterator>(
            Domain->Ratings(
            )
        );
    }

    Gs2::UE5::Matchmaking::Domain::Model::FEzRatingGameSessionDomainPtr FEzUserGameSessionDomain::Rating(
        const FString RatingName
    ) const
    {
        return MakeShared<Gs2::UE5::Matchmaking::Domain::Model::FEzRatingGameSessionDomain>(
            Domain->Rating(
                RatingName
            ),
            ProfileValue
        );
    }
}
