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

#include "Matchmaking/Domain/Model/Gs2MatchmakingEzNamespaceDomain.h"

namespace Gs2::UE5::Matchmaking::Domain::Model
{

    TOptional<FString> FEzNamespaceDomain::Status() const
    {
        return Domain->Status;
    }

    TOptional<FString> FEzNamespaceDomain::Url() const
    {
        return Domain->Url;
    }

    TOptional<FString> FEzNamespaceDomain::UploadToken() const
    {
        return Domain->UploadToken;
    }

    TOptional<FString> FEzNamespaceDomain::UploadUrl() const
    {
        return Domain->UploadUrl;
    }

    TOptional<FString> FEzNamespaceDomain::NextPageToken() const
    {
        return Domain->NextPageToken;
    }

    TOptional<FString> FEzNamespaceDomain::NamespaceName() const
    {
        return Domain->NamespaceName;
    }

    FEzNamespaceDomain::FEzNamespaceDomain(
        Gs2::Matchmaking::Domain::Model::FNamespaceDomainPtr Domain,
        Gs2::UE5::Util::FGs2ConnectionPtr Connection
    ):
        Domain(Domain),
        ConnectionValue(Connection)
    {

    }

    FEzNamespaceDomain::FVoteTask::FVoteTask(
        TSharedPtr<FEzNamespaceDomain> Self,
        FString BallotBody,
        FString BallotSignature,
        TOptional<TArray<TSharedPtr<Gs2::UE5::Matchmaking::Model::FEzGameResult>>> GameResults,
        TOptional<FString> KeyId
    ): Self(Self), BallotBody(BallotBody), BallotSignature(BallotSignature), GameResults(GameResults), KeyId(KeyId)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FEzNamespaceDomain::FVoteTask::Action(
        TSharedPtr<TSharedPtr<Gs2::UE5::Matchmaking::Domain::Model::FEzBallotDomain>> Result
    )
    {
        const auto Future = Self->ConnectionValue->Run(
            [&]() -> Gs2::Core::Model::FGs2ErrorPtr {
                const auto Task = Self->Domain->Vote(
                    MakeShared<Gs2::Matchmaking::Request::FVoteRequest>()
                        ->WithBallotBody(BallotBody)
                        ->WithBallotSignature(BallotSignature)
                        ->WithGameResults([&]{
                            auto Arr = MakeShared<TArray<TSharedPtr<Gs2::Matchmaking::Model::FGameResult>>>();
                            if (!GameResults.IsSet()) {
                                return Arr;
                            }
                            for (auto Value : *GameResults) {
                                Arr->Add(Value->ToModel());
                            }
                            return Arr;
                        }())
                        ->WithKeyId(KeyId)
                );
                Task->StartSynchronousTask();
                if (Task->GetTask().IsError())
                {
                    Task->EnsureCompletion();
                    return Task->GetTask().Error();
                }
                *Result = MakeShared<Gs2::UE5::Matchmaking::Domain::Model::FEzBallotDomain>(
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

    TSharedPtr<FAsyncTask<FEzNamespaceDomain::FVoteTask>> FEzNamespaceDomain::Vote(
        FString BallotBody,
        FString BallotSignature,
        TOptional<TArray<TSharedPtr<Gs2::UE5::Matchmaking::Model::FEzGameResult>>> GameResults,
        TOptional<FString> KeyId
    )
    {
        return Gs2::Core::Util::New<FAsyncTask<FVoteTask>>(
            this->AsShared(),
            BallotBody,
            BallotSignature,
            GameResults,
            KeyId
        );
    }

    FEzNamespaceDomain::FVoteMultipleTask::FVoteMultipleTask(
        TSharedPtr<FEzNamespaceDomain> Self,
        TOptional<TArray<TSharedPtr<Gs2::UE5::Matchmaking::Model::FEzSignedBallot>>> SignedBallots,
        TOptional<TArray<TSharedPtr<Gs2::UE5::Matchmaking::Model::FEzGameResult>>> GameResults,
        TOptional<FString> KeyId
    ): Self(Self), SignedBallots(SignedBallots), GameResults(GameResults), KeyId(KeyId)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FEzNamespaceDomain::FVoteMultipleTask::Action(
        TSharedPtr<TSharedPtr<Gs2::UE5::Matchmaking::Domain::Model::FEzBallotDomain>> Result
    )
    {
        const auto Future = Self->ConnectionValue->Run(
            [&]() -> Gs2::Core::Model::FGs2ErrorPtr {
                const auto Task = Self->Domain->VoteMultiple(
                    MakeShared<Gs2::Matchmaking::Request::FVoteMultipleRequest>()
                        ->WithSignedBallots([&]{
                            auto Arr = MakeShared<TArray<TSharedPtr<Gs2::Matchmaking::Model::FSignedBallot>>>();
                            if (!SignedBallots.IsSet()) {
                                return Arr;
                            }
                            for (auto Value : *SignedBallots) {
                                Arr->Add(Value->ToModel());
                            }
                            return Arr;
                        }())
                        ->WithGameResults([&]{
                            auto Arr = MakeShared<TArray<TSharedPtr<Gs2::Matchmaking::Model::FGameResult>>>();
                            if (!GameResults.IsSet()) {
                                return Arr;
                            }
                            for (auto Value : *GameResults) {
                                Arr->Add(Value->ToModel());
                            }
                            return Arr;
                        }())
                        ->WithKeyId(KeyId)
                );
                Task->StartSynchronousTask();
                if (Task->GetTask().IsError())
                {
                    Task->EnsureCompletion();
                    return Task->GetTask().Error();
                }
                *Result = MakeShared<Gs2::UE5::Matchmaking::Domain::Model::FEzBallotDomain>(
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

    TSharedPtr<FAsyncTask<FEzNamespaceDomain::FVoteMultipleTask>> FEzNamespaceDomain::VoteMultiple(
        TOptional<TArray<TSharedPtr<Gs2::UE5::Matchmaking::Model::FEzSignedBallot>>> SignedBallots,
        TOptional<TArray<TSharedPtr<Gs2::UE5::Matchmaking::Model::FEzGameResult>>> GameResults,
        TOptional<FString> KeyId
    )
    {
        return Gs2::Core::Util::New<FAsyncTask<FVoteMultipleTask>>(
            this->AsShared(),
            SignedBallots,
            GameResults,
            KeyId
        );
    }

    Gs2::UE5::Matchmaking::Domain::Model::FEzUserDomainPtr FEzNamespaceDomain::User(
        const FString UserId
    ) const
    {
        return MakeShared<Gs2::UE5::Matchmaking::Domain::Model::FEzUserDomain>(
            Domain->User(
                UserId
            ),
            ConnectionValue
        );
    }

    Gs2::UE5::Matchmaking::Domain::Model::FEzUserGameSessionDomainPtr FEzNamespaceDomain::Me(
        Gs2::UE5::Util::IGameSessionPtr GameSession
    ) const
    {
        return MakeShared<Gs2::UE5::Matchmaking::Domain::Model::FEzUserGameSessionDomain>(
            Domain->AccessToken(
                GameSession->AccessToken()
            ),
            GameSession,
            ConnectionValue
        );
    }

    Gs2::UE5::Matchmaking::Domain::Iterator::FEzDescribeRatingModelsIteratorPtr FEzNamespaceDomain::RatingModels(
    ) const
    {
        return MakeShared<Gs2::UE5::Matchmaking::Domain::Iterator::FEzDescribeRatingModelsIterator>(
            Domain,
            ConnectionValue
        );
    }

    Gs2::Core::Domain::CallbackID FEzNamespaceDomain::SubscribeRatingModels(TFunction<void()> Callback)
    {
        return Domain->SubscribeRatingModels(
            Callback
        );
    }

    void FEzNamespaceDomain::UnsubscribeRatingModels(Gs2::Core::Domain::CallbackID CallbackId)
    {
        Domain->UnsubscribeRatingModels(
            CallbackId
        );
    }

    Gs2::UE5::Matchmaking::Domain::Model::FEzRatingModelDomainPtr FEzNamespaceDomain::RatingModel(
        const FString RatingName
    ) const
    {
        return MakeShared<Gs2::UE5::Matchmaking::Domain::Model::FEzRatingModelDomain>(
            Domain->RatingModel(
                RatingName
            ),
            ConnectionValue
        );
    }

    Gs2::UE5::Matchmaking::Domain::Iterator::FEzDescribeSeasonModelsIteratorPtr FEzNamespaceDomain::SeasonModels(
    ) const
    {
        return MakeShared<Gs2::UE5::Matchmaking::Domain::Iterator::FEzDescribeSeasonModelsIterator>(
            Domain,
            ConnectionValue
        );
    }

    Gs2::Core::Domain::CallbackID FEzNamespaceDomain::SubscribeSeasonModels(TFunction<void()> Callback)
    {
        return Domain->SubscribeSeasonModels(
            Callback
        );
    }

    void FEzNamespaceDomain::UnsubscribeSeasonModels(Gs2::Core::Domain::CallbackID CallbackId)
    {
        Domain->UnsubscribeSeasonModels(
            CallbackId
        );
    }

    Gs2::UE5::Matchmaking::Domain::Model::FEzSeasonModelDomainPtr FEzNamespaceDomain::SeasonModel(
        const FString SeasonName
    ) const
    {
        return MakeShared<Gs2::UE5::Matchmaking::Domain::Model::FEzSeasonModelDomain>(
            Domain->SeasonModel(
                SeasonName
            ),
            ConnectionValue
        );
    }
}
