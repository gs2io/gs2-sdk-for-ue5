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

#include "Matchmaking/Domain/Model/GatheringAccessToken.h"
#include "Matchmaking/Domain/Model/Gathering.h"
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

    FGatheringAccessTokenDomain::FGatheringAccessTokenDomain(
        const Core::Domain::FCacheDatabasePtr Cache,
        const Gs2::Core::Domain::Model::FJobQueueDomainPtr JobQueueDomain,
        const Gs2::Core::Domain::Model::FStampSheetConfigurationPtr StampSheetConfiguration,
        const Gs2::Core::Net::Rest::FGs2RestSessionPtr Session,
        const TOptional<FString> NamespaceName,
        const Gs2::Auth::Model::FAccessTokenPtr AccessToken,
        const TOptional<FString> GatheringName
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Cache(Cache),
        JobQueueDomain(JobQueueDomain),
        StampSheetConfiguration(StampSheetConfiguration),
        Session(Session),
        Client(MakeShared<Gs2::Matchmaking::FGs2MatchmakingRestClient>(Session)),
        NamespaceName(NamespaceName),
        AccessToken(AccessToken),
        GatheringName(GatheringName),
        ParentKey(Gs2::Matchmaking::Domain::Model::FUserDomain::CreateCacheParentKey(
            NamespaceName,
            TOptional<FString>("Singleton"),
            "Gathering"
        ))
    {
    }

    FGatheringAccessTokenDomain::FGatheringAccessTokenDomain(
        const FGatheringAccessTokenDomain& From
    ):
        Cache(From.Cache),
        JobQueueDomain(From.JobQueueDomain),
        StampSheetConfiguration(From.StampSheetConfiguration),
        Session(From.Session),
        Client(From.Client)
    {

    }

    FGatheringAccessTokenDomain::FUpdateTask::FUpdateTask(
        const TSharedPtr<FGatheringAccessTokenDomain> Self,
        const Request::FUpdateGatheringRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FGatheringAccessTokenDomain::FUpdateTask::FUpdateTask(
        const FUpdateTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FGatheringAccessTokenDomain::FUpdateTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Matchmaking::Domain::Model::FGatheringAccessTokenDomain>> Result
    )
    {
        Request
            ->WithNamespaceName(Self->NamespaceName)
            ->WithAccessToken(Self->AccessToken->GetToken())
            ->WithGatheringName(Self->GatheringName);
        const auto Future = Self->Client->UpdateGathering(
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
        auto Domain = Self;

        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FGatheringAccessTokenDomain::FUpdateTask>> FGatheringAccessTokenDomain::Update(
        Request::FUpdateGatheringRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FUpdateTask>>(this->AsShared(), Request);
    }

    FGatheringAccessTokenDomain::FCancelMatchmakingTask::FCancelMatchmakingTask(
        const TSharedPtr<FGatheringAccessTokenDomain> Self,
        const Request::FCancelMatchmakingRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FGatheringAccessTokenDomain::FCancelMatchmakingTask::FCancelMatchmakingTask(
        const FCancelMatchmakingTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FGatheringAccessTokenDomain::FCancelMatchmakingTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Matchmaking::Domain::Model::FGatheringAccessTokenDomain>> Result
    )
    {
        Request
            ->WithNamespaceName(Self->NamespaceName)
            ->WithAccessToken(Self->AccessToken->GetToken())
            ->WithGatheringName(Self->GatheringName);
        const auto Future = Self->Client->CancelMatchmaking(
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
                Self->Cache->Delete(Gs2::Matchmaking::Model::FGathering::TypeName, ParentKey, Key);
            }
        }
        auto Domain = Self;

        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FGatheringAccessTokenDomain::FCancelMatchmakingTask>> FGatheringAccessTokenDomain::CancelMatchmaking(
        Request::FCancelMatchmakingRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FCancelMatchmakingTask>>(this->AsShared(), Request);
    }

    FString FGatheringAccessTokenDomain::CreateCacheParentKey(
        TOptional<FString> NamespaceName,
        TOptional<FString> UserId,
        TOptional<FString> GatheringName,
        FString ChildType
    )
    {
        return FString() +
            (NamespaceName.IsSet() ? *NamespaceName : "null") + ":" +
            (UserId.IsSet() ? *UserId : "null") + ":" +
            (GatheringName.IsSet() ? *GatheringName : "null") + ":" +
            ChildType;
    }

    FString FGatheringAccessTokenDomain::CreateCacheKey(
        TOptional<FString> GatheringName
    )
    {
        return FString() +
            (GatheringName.IsSet() ? *GatheringName : "null");
    }

    FGatheringAccessTokenDomain::FModelTask::FModelTask(
        const TSharedPtr<FGatheringAccessTokenDomain> Self
    ): Self(Self)
    {

    }

    FGatheringAccessTokenDomain::FModelTask::FModelTask(
        const FModelTask& From
    ): TGs2Future(From), Self(From.Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FGatheringAccessTokenDomain::FModelTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Matchmaking::Model::FGathering>> Result
    )
    {
        // ReSharper disable once CppLocalVariableMayBeConst
        auto Value = Self->Cache->Get<Gs2::Matchmaking::Model::FGathering>(
            Self->ParentKey,
            Gs2::Matchmaking::Domain::Model::FGatheringDomain::CreateCacheKey(
                Self->GatheringName
            )
        );
        *Result = Value;

        return nullptr;
    }

    TSharedPtr<FAsyncTask<FGatheringAccessTokenDomain::FModelTask>> FGatheringAccessTokenDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FGatheringAccessTokenDomain::FModelTask>>(this->AsShared());
    }
}

#if defined(_MSC_VER)
#pragma warning (pop)
#elif defined(__clang__)
#pragma clang diagnostic pop
#endif

