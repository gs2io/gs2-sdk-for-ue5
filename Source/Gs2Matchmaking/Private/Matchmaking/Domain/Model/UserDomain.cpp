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

    FUserDomain::FUserDomain(
        const Core::Domain::FCacheDatabasePtr Cache,
        const Gs2::Core::Domain::Model::FJobQueueDomainPtr JobQueueDomain,
        const Gs2::Core::Domain::Model::FStampSheetConfigurationPtr StampSheetConfiguration,
        const Gs2::Core::Net::Rest::FGs2RestSessionPtr Session,
        const TOptional<FString> NamespaceName,
        const TOptional<FString> UserId
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Cache(Cache),
        JobQueueDomain(JobQueueDomain),
        StampSheetConfiguration(StampSheetConfiguration),
        Session(Session),
        Client(MakeShared<Gs2::Matchmaking::FGs2MatchmakingRestClient>(Session)),
        NamespaceName(NamespaceName),
        UserId(UserId),
        ParentKey(Gs2::Matchmaking::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
            NamespaceName,
            "User"
        ))
    {
    }

    FUserDomain::FUserDomain(
        const FUserDomain& From
    ):
        Cache(From.Cache),
        JobQueueDomain(From.JobQueueDomain),
        StampSheetConfiguration(From.StampSheetConfiguration),
        Session(From.Session),
        Client(From.Client)
    {

    }

    FUserDomain::FCreateGatheringTask::FCreateGatheringTask(
        const TSharedPtr<FUserDomain> Self,
        const Request::FCreateGatheringByUserIdRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FUserDomain::FCreateGatheringTask::FCreateGatheringTask(
        const FCreateGatheringTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FUserDomain::FCreateGatheringTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Matchmaking::Domain::Model::FGatheringDomain>> Result
    )
    {
        Request
            ->WithNamespaceName(Self->NamespaceName)
            ->WithUserId(Self->UserId);
        const auto Future = Self->Client->CreateGatheringByUserId(
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
                Self->Cache->Put<Gs2::Matchmaking::Model::FGathering>(
                    ParentKey,
                    Key,
                    ResultModel->GetItem(),
                    ResultModel->GetItem()->GetExpiresAt().IsSet() && *ResultModel->GetItem()->GetExpiresAt() != 0 ? FDateTime::FromUnixTimestamp(*ResultModel->GetItem()->GetExpiresAt() / 1000) : FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );
            }
        }
        auto Domain = MakeShared<Gs2::Matchmaking::Domain::Model::FGatheringDomain>(
            Self->Cache,
            Self->JobQueueDomain,
            Self->StampSheetConfiguration,
            Self->Session,
            Request->GetNamespaceName(),
            Request->GetUserId(),
            ResultModel->GetItem()->GetName()
        );

        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FUserDomain::FCreateGatheringTask>> FUserDomain::CreateGathering(
        Request::FCreateGatheringByUserIdRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FCreateGatheringTask>>(this->AsShared(), Request);
    }

    FUserDomain::FDeleteGatheringTask::FDeleteGatheringTask(
        const TSharedPtr<FUserDomain> Self,
        const Request::FDeleteGatheringRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FUserDomain::FDeleteGatheringTask::FDeleteGatheringTask(
        const FDeleteGatheringTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FUserDomain::FDeleteGatheringTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Matchmaking::Domain::Model::FGatheringDomain>> Result
    )
    {
        Request
            ->WithNamespaceName(Self->NamespaceName);
        const auto Future = Self->Client->DeleteGathering(
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
                Self->Cache->Delete<Gs2::Matchmaking::Model::FGathering>(ParentKey, Key);
            }
        }
        auto Domain = MakeShared<Gs2::Matchmaking::Domain::Model::FGatheringDomain>(
            Self->Cache,
            Self->JobQueueDomain,
            Self->StampSheetConfiguration,
            Self->Session,
            Request->GetNamespaceName(),
            Self->UserId,
            ResultModel->GetItem()->GetName()
        );

        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FUserDomain::FDeleteGatheringTask>> FUserDomain::DeleteGathering(
        Request::FDeleteGatheringRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FDeleteGatheringTask>>(this->AsShared(), Request);
    }

    FUserDomain::FPutResultTask::FPutResultTask(
        const TSharedPtr<FUserDomain> Self,
        const Request::FPutResultRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FUserDomain::FPutResultTask::FPutResultTask(
        const FPutResultTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FUserDomain::FPutResultTask::Action(
        TSharedPtr<TSharedPtr<TArray<TSharedPtr<Gs2::Matchmaking::Domain::Model::FRatingDomain>>>> Result
    )
    {
        Request
            ->WithNamespaceName(Self->NamespaceName);
        const auto Future = Self->Client->PutResult(
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
            {
                for (auto Item : *ResultModel->GetItems())
                {
                    const auto ParentKey = Gs2::Matchmaking::Domain::Model::FUserDomain::CreateCacheParentKey(
                        Self->NamespaceName,
                        Self->UserId,
                        "Rating"
                    );
                    const auto Key = Gs2::Matchmaking::Domain::Model::FRatingDomain::CreateCacheKey(
                        Item->GetName()
                    );
                    Self->Cache->Put<Gs2::Matchmaking::Model::FRating>(
                        ParentKey,
                        Key,
                        Item,
                        FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                    );
                }
            }
        }
        auto Domain = MakeShared<TArray<TSharedPtr<Gs2::Matchmaking::Domain::Model::FRatingDomain>>>();
        for (auto i=0; i<ResultModel->GetItems()->Num(); i++)
        {
            Domain->Add(
                MakeShared<Gs2::Matchmaking::Domain::Model::FRatingDomain>(
                    Self->Cache,
                    Self->JobQueueDomain,
                    Self->StampSheetConfiguration,
                    Self->Session,
                    Request->GetNamespaceName(),
                    (*ResultModel->GetItems())[i]->GetUserId(),
                    (*ResultModel->GetItems())[i]->GetName()
                )
            );
        }
        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FUserDomain::FPutResultTask>> FUserDomain::PutResult(
        Request::FPutResultRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FPutResultTask>>(this->AsShared(), Request);
    }

    Gs2::Matchmaking::Domain::Iterator::FDescribeGatheringsIteratorPtr FUserDomain::Gatherings(
    ) const
    {
        return MakeShared<Gs2::Matchmaking::Domain::Iterator::FDescribeGatheringsIterator>(
            Cache,
            Client,
            NamespaceName
        );
    }

    Gs2::Matchmaking::Domain::Iterator::FDoMatchmakingByPlayerIteratorPtr FUserDomain::DoMatchmakingByPlayer(
        const TSharedPtr<Gs2::Matchmaking::Model::FPlayer> Player
    ) const
    {
        return MakeShared<Gs2::Matchmaking::Domain::Iterator::FDoMatchmakingByPlayerIterator>(
            Cache,
            Client,
            NamespaceName,
            Player
        );
    }

    Gs2::Matchmaking::Domain::Iterator::FDoMatchmakingByUserIdIteratorPtr FUserDomain::DoMatchmaking(
        const TSharedPtr<Gs2::Matchmaking::Model::FPlayer> Player
    ) const
    {
        return MakeShared<Gs2::Matchmaking::Domain::Iterator::FDoMatchmakingByUserIdIterator>(
            Cache,
            Client,
            NamespaceName,
            UserId,
            Player
        );
    }

    TSharedPtr<Gs2::Matchmaking::Domain::Model::FGatheringDomain> FUserDomain::Gathering(
        const FString GatheringName
    ) const
    {
        return MakeShared<Gs2::Matchmaking::Domain::Model::FGatheringDomain>(
            Cache,
            JobQueueDomain,
            StampSheetConfiguration,
            Session,
            NamespaceName,
            UserId,
            GatheringName
        );
    }

    TSharedPtr<Gs2::Matchmaking::Domain::Model::FBallotDomain> FUserDomain::Ballot(
        const FString RatingName,
        const FString GatheringName,
        const int32 NumberOfPlayer,
        const FString KeyId
    ) const
    {
        return MakeShared<Gs2::Matchmaking::Domain::Model::FBallotDomain>(
            Cache,
            JobQueueDomain,
            StampSheetConfiguration,
            Session,
            NamespaceName,
            UserId,
            RatingName,
            GatheringName,
            NumberOfPlayer,
            KeyId
        );
    }

    Gs2::Matchmaking::Domain::Iterator::FDescribeRatingsByUserIdIteratorPtr FUserDomain::Ratings(
    ) const
    {
        return MakeShared<Gs2::Matchmaking::Domain::Iterator::FDescribeRatingsByUserIdIterator>(
            Cache,
            Client,
            NamespaceName,
            UserId
        );
    }

    TSharedPtr<Gs2::Matchmaking::Domain::Model::FRatingDomain> FUserDomain::Rating(
        const FString RatingName
    ) const
    {
        return MakeShared<Gs2::Matchmaking::Domain::Model::FRatingDomain>(
            Cache,
            JobQueueDomain,
            StampSheetConfiguration,
            Session,
            NamespaceName,
            UserId,
            RatingName
        );
    }

    FString FUserDomain::CreateCacheParentKey(
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

    FString FUserDomain::CreateCacheKey(
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

