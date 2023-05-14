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

#if defined(_MSC_VER)
#pragma warning (push)
#pragma warning (disable: 4458) // Declaration hides class member
#elif defined(__clang__)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wshadow" // declaration shadows a field of
#endif

#include "Matchmaking/Domain/Model/UserAccessToken.h"
#include "Matchmaking/Domain/Model/User.h"
#include "Matchmaking/Domain/Model/Namespace.h"
#include "Matchmaking/Domain/Model/Gathering.h"
#include "Matchmaking/Domain/Model/GatheringAccessToken.h"
#include "Matchmaking/Domain/Model/RatingModelMaster.h"
#include "Matchmaking/Domain/Model/RatingModel.h"
#include "Matchmaking/Domain/Model/CurrentRatingModelMaster.h"
#include "Matchmaking/Domain/Model/Rating.h"
#include "Matchmaking/Domain/Model/RatingAccessToken.h"
#include "Matchmaking/Domain/Model/Ballot.h"
#include "Matchmaking/Domain/Model/BallotAccessToken.h"
#include "Matchmaking/Domain/Model/Vote.h"
#include "Matchmaking/Domain/Model/User.h"
#include "Matchmaking/Domain/Model/UserAccessToken.h"

#include "Core/Domain/Model/AutoStampSheetDomain.h"
#include "Core/Domain/Model/StampSheetDomain.h"

namespace Gs2::Matchmaking::Domain::Model
{

    FUserAccessTokenDomain::FUserAccessTokenDomain(
        const Core::Domain::FCacheDatabasePtr Cache,
        const Gs2::Core::Domain::Model::FJobQueueDomainPtr JobQueueDomain,
        const Gs2::Core::Domain::Model::FStampSheetConfigurationPtr StampSheetConfiguration,
        const Gs2::Core::Net::Rest::FGs2RestSessionPtr Session,
        const TOptional<FString> NamespaceName,
        const Gs2::Auth::Model::FAccessTokenPtr AccessToken
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Cache(Cache),
        JobQueueDomain(JobQueueDomain),
        StampSheetConfiguration(StampSheetConfiguration),
        Session(Session),
        Client(MakeShared<Gs2::Matchmaking::FGs2MatchmakingRestClient>(Session)),
        NamespaceName(NamespaceName),
        AccessToken(AccessToken),
        ParentKey(Gs2::Matchmaking::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
            NamespaceName,
            "User"
        ))
    {
    }

    FUserAccessTokenDomain::FUserAccessTokenDomain(
        const FUserAccessTokenDomain& From
    ):
        Cache(From.Cache),
        JobQueueDomain(From.JobQueueDomain),
        StampSheetConfiguration(From.StampSheetConfiguration),
        Session(From.Session),
        Client(From.Client)
    {

    }

    FUserAccessTokenDomain::FCreateGatheringTask::FCreateGatheringTask(
        const TSharedPtr<FUserAccessTokenDomain> Self,
        const Request::FCreateGatheringRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FUserAccessTokenDomain::FCreateGatheringTask::FCreateGatheringTask(
        const FCreateGatheringTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FUserAccessTokenDomain::FCreateGatheringTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Matchmaking::Domain::Model::FGatheringAccessTokenDomain>> Result
    )
    {
        Request
            ->WithNamespaceName(Self->NamespaceName)
            ->WithAccessToken(Self->AccessToken->GetToken());
        const auto Future = Self->Client->CreateGathering(
            Request
        );
        Future->StartSynchronousTask();
        if (Future->GetTask().IsError())
        {
            return Future->GetTask().Error();
        }
        const auto RequestModel = Request;
        const auto ResultModel = Future->GetTask().Result();
        Future->EnsureCompletion();
        if (ResultModel != nullptr) {
            
            if (ResultModel->GetItem() != nullptr)
            {
                const auto ParentKey = Gs2::Matchmaking::Domain::Model::FUserDomain::CreateCacheParentKey(
                    Self->NamespaceName,
                    TOptional<FString>("Singleton"),
                    "Gathering"
                );
                const auto Key = Gs2::Matchmaking::Domain::Model::FGatheringDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetName()
                );
                Self->Cache->Put(
                    Gs2::Matchmaking::Model::FGathering::TypeName,
                    ParentKey,
                    Key,
                    ResultModel->GetItem(),
                    ResultModel->GetItem()->GetExpiresAt().IsSet() && *ResultModel->GetItem()->GetExpiresAt() != 0 ? FDateTime::FromUnixTimestamp(*ResultModel->GetItem()->GetExpiresAt() / 1000) : FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );
            }
        }
        auto Domain = MakeShared<Gs2::Matchmaking::Domain::Model::FGatheringAccessTokenDomain>(
            Self->Cache,
            Self->JobQueueDomain,
            Self->StampSheetConfiguration,
            Self->Session,
            Request->GetNamespaceName(),
            Self->AccessToken,
            ResultModel->GetItem()->GetName()
        );

        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FUserAccessTokenDomain::FCreateGatheringTask>> FUserAccessTokenDomain::CreateGathering(
        Request::FCreateGatheringRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FCreateGatheringTask>>(this->AsShared(), Request);
    }

    Gs2::Matchmaking::Domain::Iterator::FDoMatchmakingIteratorPtr FUserAccessTokenDomain::DoMatchmaking(
        const TSharedPtr<Gs2::Matchmaking::Model::FPlayer> Player
    ) const
    {
        return MakeShared<Gs2::Matchmaking::Domain::Iterator::FDoMatchmakingIterator>(
            Cache,
            Client,
            NamespaceName,
            AccessToken,
            Player
        );
    }

    TSharedPtr<Gs2::Matchmaking::Domain::Model::FGatheringAccessTokenDomain> FUserAccessTokenDomain::Gathering(
        const FString GatheringName
    ) const
    {
        return MakeShared<Gs2::Matchmaking::Domain::Model::FGatheringAccessTokenDomain>(
            Cache,
            JobQueueDomain,
            StampSheetConfiguration,
            Session,
            NamespaceName,
            AccessToken,
            GatheringName
        );
    }

    TSharedPtr<Gs2::Matchmaking::Domain::Model::FBallotAccessTokenDomain> FUserAccessTokenDomain::Ballot(
        const FString RatingName,
        const FString GatheringName,
        const int32 NumberOfPlayer,
        const FString KeyId
    ) const
    {
        return MakeShared<Gs2::Matchmaking::Domain::Model::FBallotAccessTokenDomain>(
            Cache,
            JobQueueDomain,
            StampSheetConfiguration,
            Session,
            NamespaceName,
            AccessToken,
            RatingName,
            GatheringName,
            NumberOfPlayer,
            KeyId
        );
    }

    Gs2::Matchmaking::Domain::Iterator::FDescribeRatingsIteratorPtr FUserAccessTokenDomain::Ratings(
    ) const
    {
        return MakeShared<Gs2::Matchmaking::Domain::Iterator::FDescribeRatingsIterator>(
            Cache,
            Client,
            NamespaceName,
            AccessToken
        );
    }

    TSharedPtr<Gs2::Matchmaking::Domain::Model::FRatingAccessTokenDomain> FUserAccessTokenDomain::Rating(
        const FString RatingName
    ) const
    {
        return MakeShared<Gs2::Matchmaking::Domain::Model::FRatingAccessTokenDomain>(
            Cache,
            JobQueueDomain,
            StampSheetConfiguration,
            Session,
            NamespaceName,
            AccessToken,
            RatingName
        );
    }

    FString FUserAccessTokenDomain::CreateCacheParentKey(
        TOptional<FString> NamespaceName,
        TOptional<FString> UserId,
        FString ChildType
    )
    {
        return FString() +
            (NamespaceName.IsSet() ? *NamespaceName : "null") + ":" +
            (UserId.IsSet() ? *UserId : "null") + ":" +
            ChildType;
    }

    FString FUserAccessTokenDomain::CreateCacheKey(
        TOptional<FString> UserId
    )
    {
        return FString() +
            (UserId.IsSet() ? *UserId : "null");
    }
}

#if defined(_MSC_VER)
#pragma warning (pop)
#elif defined(__clang__)
#pragma clang diagnostic pop
#endif

