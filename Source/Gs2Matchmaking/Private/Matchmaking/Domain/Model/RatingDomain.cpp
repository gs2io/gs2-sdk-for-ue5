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

#include "Matchmaking/Domain/Model/Rating.h"
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

    FRatingDomain::FRatingDomain(
        const Core::Domain::FCacheDatabasePtr Cache,
        const Gs2::Core::Domain::Model::FJobQueueDomainPtr JobQueueDomain,
        const Gs2::Core::Domain::Model::FStampSheetConfigurationPtr StampSheetConfiguration,
        const Gs2::Core::Net::Rest::FGs2RestSessionPtr Session,
        const TOptional<FString> NamespaceName,
        const TOptional<FString> UserId,
        const TOptional<FString> RatingName
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Cache(Cache),
        JobQueueDomain(JobQueueDomain),
        StampSheetConfiguration(StampSheetConfiguration),
        Session(Session),
        Client(MakeShared<Gs2::Matchmaking::FGs2MatchmakingRestClient>(Session)),
        NamespaceName(NamespaceName),
        UserId(UserId),
        RatingName(RatingName),
        ParentKey(Gs2::Matchmaking::Domain::Model::FUserDomain::CreateCacheParentKey(
            NamespaceName,
            UserId,
            "Rating"
        ))
    {
    }

    FRatingDomain::FRatingDomain(
        const FRatingDomain& From
    ):
        Cache(From.Cache),
        JobQueueDomain(From.JobQueueDomain),
        StampSheetConfiguration(From.StampSheetConfiguration),
        Session(From.Session),
        Client(From.Client),
        NamespaceName(From.NamespaceName),
        UserId(From.UserId),
        RatingName(From.RatingName),
        ParentKey(From.ParentKey)
    {

    }

    FRatingDomain::FGetTask::FGetTask(
        const TSharedPtr<FRatingDomain> Self,
        const Request::FGetRatingByUserIdRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FRatingDomain::FGetTask::FGetTask(
        const FGetTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FRatingDomain::FGetTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Matchmaking::Model::FRating>> Result
    )
    {
        Request
            ->WithNamespaceName(Self->NamespaceName)
            ->WithUserId(Self->UserId)
            ->WithRatingName(Self->RatingName);
        const auto Future = Self->Client->GetRatingByUserId(
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
                    Self->UserId,
                    "Rating"
                );
                const auto Key = Gs2::Matchmaking::Domain::Model::FRatingDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetName()
                );
                Self->Cache->Put(
                    Gs2::Matchmaking::Model::FRating::TypeName,
                    ParentKey,
                    Key,
                    ResultModel->GetItem(),
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );
            }
        }
        *Result = ResultModel->GetItem();
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FRatingDomain::FGetTask>> FRatingDomain::Get(
        Request::FGetRatingByUserIdRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FGetTask>>(this->AsShared(), Request);
    }

    FRatingDomain::FDeleteTask::FDeleteTask(
        const TSharedPtr<FRatingDomain> Self,
        const Request::FDeleteRatingRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FRatingDomain::FDeleteTask::FDeleteTask(
        const FDeleteTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FRatingDomain::FDeleteTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Matchmaking::Domain::Model::FRatingDomain>> Result
    )
    {
        Request
            ->WithNamespaceName(Self->NamespaceName)
            ->WithUserId(Self->UserId)
            ->WithRatingName(Self->RatingName);
        const auto Future = Self->Client->DeleteRating(
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
                    Self->UserId,
                    "Rating"
                );
                const auto Key = Gs2::Matchmaking::Domain::Model::FRatingDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetName()
                );
                Self->Cache->Delete(Gs2::Matchmaking::Model::FRating::TypeName, ParentKey, Key);
            }
        }
        auto Domain = Self;

        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FRatingDomain::FDeleteTask>> FRatingDomain::Delete(
        Request::FDeleteRatingRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FDeleteTask>>(this->AsShared(), Request);
    }

    FString FRatingDomain::CreateCacheParentKey(
        TOptional<FString> NamespaceName,
        TOptional<FString> UserId,
        TOptional<FString> RatingName,
        FString ChildType
    )
    {
        return FString("") +
            (NamespaceName.IsSet() ? *NamespaceName : "null") + ":" +
            (UserId.IsSet() ? *UserId : "null") + ":" +
            (RatingName.IsSet() ? *RatingName : "null") + ":" +
            ChildType;
    }

    FString FRatingDomain::CreateCacheKey(
        TOptional<FString> RatingName
    )
    {
        return FString("") +
            (RatingName.IsSet() ? *RatingName : "null");
    }

    FRatingDomain::FModelTask::FModelTask(
        const TSharedPtr<FRatingDomain> Self
    ): Self(Self)
    {

    }

    FRatingDomain::FModelTask::FModelTask(
        const FModelTask& From
    ): TGs2Future(From), Self(From.Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FRatingDomain::FModelTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Matchmaking::Model::FRating>> Result
    )
    {
        // ReSharper disable once CppLocalVariableMayBeConst
        TSharedPtr<Gs2::Matchmaking::Model::FRating> Value;
        auto bCacheHit = Self->Cache->TryGet<Gs2::Matchmaking::Model::FRating>(
            Self->ParentKey,
            Gs2::Matchmaking::Domain::Model::FRatingDomain::CreateCacheKey(
                Self->RatingName
            ),
            &Value
        );
        if (!bCacheHit) {
            const auto Future = Self->Get(
                MakeShared<Gs2::Matchmaking::Request::FGetRatingByUserIdRequest>()
            );
            Future->StartSynchronousTask();
            if (Future->GetTask().IsError())
            {
                if (Future->GetTask().Error()->Type() != Gs2::Core::Model::FNotFoundError::TypeString)
                {
                    return Future->GetTask().Error();
                }

                const auto Key = Gs2::Matchmaking::Domain::Model::FRatingDomain::CreateCacheKey(
                    Self->RatingName
                );
                Self->Cache->Put(
                    Gs2::Matchmaking::Model::FRating::TypeName,
                    Self->ParentKey,
                    Key,
                    nullptr,
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );

                if (Future->GetTask().Error()->Detail(0)->GetComponent() != "rating")
                {
                    return Future->GetTask().Error();
                }
            }
            Self->Cache->TryGet<Gs2::Matchmaking::Model::FRating>(
                Self->ParentKey,
                Gs2::Matchmaking::Domain::Model::FRatingDomain::CreateCacheKey(
                    Self->RatingName
                ),
                &Value
            );
            Future->EnsureCompletion();
        }
        *Result = Value;

        return nullptr;
    }

    TSharedPtr<FAsyncTask<FRatingDomain::FModelTask>> FRatingDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FRatingDomain::FModelTask>>(this->AsShared());
    }

    Gs2::Core::Domain::CallbackID FRatingDomain::Subscribe(
        TFunction<void(Gs2::Matchmaking::Model::FRatingPtr)> Callback
    )
    {
        return Cache->Subscribe(
            Gs2::Matchmaking::Model::FRating::TypeName,
            ParentKey,
            Gs2::Matchmaking::Domain::Model::FRatingDomain::CreateCacheKey(
                RatingName
            ),
            [Callback](TSharedPtr<Gs2Object> obj)
            {
                Callback(StaticCastSharedPtr<Gs2::Matchmaking::Model::FRating>(obj));
            }
        );
    }

    void FRatingDomain::Unsubscribe(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        Cache->Unsubscribe(
            Gs2::Matchmaking::Model::FRating::TypeName,
            ParentKey,
            Gs2::Matchmaking::Domain::Model::FRatingDomain::CreateCacheKey(
                RatingName
            ),
            CallbackID
        );
    }
}

#if defined(_MSC_VER)
#pragma warning (pop)
#elif defined(__clang__)
#pragma clang diagnostic pop
#endif

