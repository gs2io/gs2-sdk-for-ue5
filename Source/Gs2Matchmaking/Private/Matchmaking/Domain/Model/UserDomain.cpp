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

#include "Core/Domain/Gs2.h"
#include "Core/Domain/Model/AutoStampSheetDomain.h"
#include "Core/Domain/Model/StampSheetDomain.h"

namespace Gs2::Matchmaking::Domain::Model
{

    FUserDomain::FUserDomain(
        const Core::Domain::FGs2Ptr& Gs2,
        const Matchmaking::Domain::FGs2MatchmakingDomainPtr& Service,
        const TOptional<FString> NamespaceName,
        const TOptional<FString> UserId
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Gs2(Gs2),
        Service(Service),
        Client(MakeShared<Gs2::Matchmaking::FGs2MatchmakingRestClient>(Gs2->RestSession)),
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
        Gs2(From.Gs2),
        Service(From.Service),
        Client(From.Client),
        NamespaceName(From.NamespaceName),
        UserId(From.UserId),
        ParentKey(From.ParentKey)
    {

    }

    FUserDomain::FCreateGatheringTask::FCreateGatheringTask(
        const TSharedPtr<FUserDomain>& Self,
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
                Self->Gs2->Cache->Put(
                    Gs2::Matchmaking::Model::FGathering::TypeName,
                    ParentKey,
                    Key,
                    ResultModel->GetItem(),
                    ResultModel->GetItem()->GetExpiresAt().IsSet() && *ResultModel->GetItem()->GetExpiresAt() != 0 ? FDateTime::FromUnixTimestamp(*ResultModel->GetItem()->GetExpiresAt() / 1000) : FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );
            }
        }
        auto Domain = MakeShared<Gs2::Matchmaking::Domain::Model::FGatheringDomain>(
            Self->Gs2,
            Self->Service,
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
        const TSharedPtr<FUserDomain>& Self,
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
                Self->Gs2->Cache->Delete(Gs2::Matchmaking::Model::FGathering::TypeName, ParentKey, Key);
            }
        }
        auto Domain = MakeShared<Gs2::Matchmaking::Domain::Model::FGatheringDomain>(
            Self->Gs2,
            Self->Service,
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
        const TSharedPtr<FUserDomain>& Self,
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
                    Self->Gs2->Cache->Put(
                        Gs2::Matchmaking::Model::FRating::TypeName,
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
                    Self->Gs2,
                    Self->Service,
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
            Gs2->Cache,
            Client,
            NamespaceName
        );
    }

    Gs2::Core::Domain::CallbackID FUserDomain::SubscribeGatherings(
    TFunction<void()> Callback
    )
    {
        return Gs2->Cache->ListSubscribe(
            Gs2::Matchmaking::Model::FGathering::TypeName,
            Gs2::Matchmaking::Domain::Model::FUserDomain::CreateCacheParentKey(
                NamespaceName,
                TOptional<FString>("Singleton"),
                "Gathering"
            ),
            Callback
        );
    }

    void FUserDomain::UnsubscribeGatherings(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        Gs2->Cache->ListUnsubscribe(
            Gs2::Matchmaking::Model::FGathering::TypeName,
            Gs2::Matchmaking::Domain::Model::FUserDomain::CreateCacheParentKey(
                NamespaceName,
                TOptional<FString>("Singleton"),
                "Gathering"
            ),
            CallbackID
        );
    }

    Gs2::Matchmaking::Domain::Iterator::FDoMatchmakingByPlayerIteratorPtr FUserDomain::DoMatchmakingByPlayer(
        const TSharedPtr<Gs2::Matchmaking::Model::FPlayer> Player
    ) const
    {
        return MakeShared<Gs2::Matchmaking::Domain::Iterator::FDoMatchmakingByPlayerIterator>(
            Gs2->Cache,
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
            Gs2->Cache,
            Client,
            NamespaceName,
            UserId,
            Player
        );
    }

    TSharedPtr<Gs2::Matchmaking::Domain::Model::FGatheringDomain> FUserDomain::Gathering(
        const FString GatheringName
    )
    {
        return MakeShared<Gs2::Matchmaking::Domain::Model::FGatheringDomain>(
            Gs2,
            Service,
            NamespaceName,
            UserId,
            GatheringName == TEXT("") ? TOptional<FString>() : TOptional<FString>(GatheringName)
        );
    }

    TSharedPtr<Gs2::Matchmaking::Domain::Model::FBallotDomain> FUserDomain::Ballot(
        const FString RatingName,
        const FString GatheringName,
        const int32 NumberOfPlayer,
        const FString KeyId
    )
    {
        return MakeShared<Gs2::Matchmaking::Domain::Model::FBallotDomain>(
            Gs2,
            Service,
            NamespaceName,
            UserId,
            RatingName == TEXT("") ? TOptional<FString>() : TOptional<FString>(RatingName),
            GatheringName == TEXT("") ? TOptional<FString>() : TOptional<FString>(GatheringName),
            NumberOfPlayer,
            KeyId == TEXT("") ? TOptional<FString>() : TOptional<FString>(KeyId)
        );
    }

    Gs2::Matchmaking::Domain::Iterator::FDescribeRatingsByUserIdIteratorPtr FUserDomain::Ratings(
    ) const
    {
        return MakeShared<Gs2::Matchmaking::Domain::Iterator::FDescribeRatingsByUserIdIterator>(
            Gs2->Cache,
            Client,
            NamespaceName,
            UserId
        );
    }

    Gs2::Core::Domain::CallbackID FUserDomain::SubscribeRatings(
    TFunction<void()> Callback
    )
    {
        return Gs2->Cache->ListSubscribe(
            Gs2::Matchmaking::Model::FRating::TypeName,
            Gs2::Matchmaking::Domain::Model::FUserDomain::CreateCacheParentKey(
                NamespaceName,
                UserId,
                "Rating"
            ),
            Callback
        );
    }

    void FUserDomain::UnsubscribeRatings(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        Gs2->Cache->ListUnsubscribe(
            Gs2::Matchmaking::Model::FRating::TypeName,
            Gs2::Matchmaking::Domain::Model::FUserDomain::CreateCacheParentKey(
                NamespaceName,
                UserId,
                "Rating"
            ),
            CallbackID
        );
    }

    TSharedPtr<Gs2::Matchmaking::Domain::Model::FRatingDomain> FUserDomain::Rating(
        const FString RatingName
    )
    {
        return MakeShared<Gs2::Matchmaking::Domain::Model::FRatingDomain>(
            Gs2,
            Service,
            NamespaceName,
            UserId,
            RatingName == TEXT("") ? TOptional<FString>() : TOptional<FString>(RatingName)
        );
    }

    FString FUserDomain::CreateCacheParentKey(
        TOptional<FString> NamespaceName,
        TOptional<FString> UserId,
        FString ChildType
    )
    {
        return FString("") +
            (NamespaceName.IsSet() ? *NamespaceName : "null") + ":" +
            (UserId.IsSet() ? *UserId : "null") + ":" +
            ChildType;
    }

    FString FUserDomain::CreateCacheKey(
        TOptional<FString> UserId
    )
    {
        return FString("") +
            (UserId.IsSet() ? *UserId : "null");
    }
}

#if defined(_MSC_VER)
#pragma warning (pop)
#elif defined(__clang__)
#pragma clang diagnostic pop
#endif

