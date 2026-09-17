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
 * 
 * deny overwrite
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
#include "Matchmaking/Domain/Model/CurrentModelMaster.h"
#include "Matchmaking/Domain/Model/User.h"
#include "Matchmaking/Domain/Model/UserAccessToken.h"
#include "Matchmaking/Domain/Model/Season.h"
#include "Matchmaking/Domain/Model/SeasonAccessToken.h"
#include "Matchmaking/Domain/Model/SeasonModel.h"
#include "Matchmaking/Domain/Model/SeasonModelMaster.h"
#include "Matchmaking/Domain/Model/SeasonGathering.h"
#include "Matchmaking/Domain/Model/SeasonGatheringAccessToken.h"
#include "Matchmaking/Domain/Model/JoinedSeasonGathering.h"
#include "Matchmaking/Domain/Model/JoinedSeasonGatheringAccessToken.h"
#include "Matchmaking/Domain/Model/Rating.h"
#include "Matchmaking/Domain/Model/RatingAccessToken.h"
#include "Matchmaking/Domain/Model/Ballot.h"
#include "Matchmaking/Domain/Model/BallotAccessToken.h"
#include "Matchmaking/Domain/Model/Vote.h"

#include "Matchmaking/Model/Cache/Gathering.h"
#include "Matchmaking/Model/Cache/Rating.h"
#include "Core/Domain/Gs2.h"
#include "Core/Domain/Transaction/JobQueueJobDomainFactory.h"
#include "Core/Domain/Transaction/InternalTransactionDomainFactory.h"
#include "Core/Domain/Transaction/ManualTransactionAccessTokenDomain.h"

namespace Gs2::Matchmaking::Domain::Model
{

    FUserAccessTokenDomain::FUserAccessTokenDomain(
        const Core::Domain::FGs2Ptr& Gs2,
        const Matchmaking::Domain::FGs2MatchmakingDomainPtr& Service,
        const TOptional<FString> NamespaceName,
        const Gs2::Auth::Model::FAccessTokenPtr& AccessToken
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Gs2(Gs2),
        Service(Service),
        Client(MakeShared<Gs2::Matchmaking::FGs2MatchmakingRestClient>(Gs2->RestSession)),
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
        Gs2(From.Gs2),
        Service(From.Service),
        Client(From.Client),
        NamespaceName(From.NamespaceName),
        AccessToken(From.AccessToken),
        ParentKey(From.ParentKey)
    {

    }

    FUserAccessTokenDomain::FCreateGatheringTask::FCreateGatheringTask(
        const TSharedPtr<FUserAccessTokenDomain>& Self,
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
            ->WithContextStack(Self->Gs2->DefaultContextStack)
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
        const auto ResultModel = Future->GetTask().Result();
        Future->EnsureCompletion();
        auto Domain = MakeShared<Gs2::Matchmaking::Domain::Model::FGatheringAccessTokenDomain>(
            Self->Gs2,
            Self->Service,
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
            Gs2,
            Client,
            NamespaceName,
            AccessToken,
            Player
        );
    }


    Gs2::Core::Domain::CallbackID FUserAccessTokenDomain::SubscribeDoMatchmaking(TFunction<void()> Callback,const TSharedPtr<Gs2::Matchmaking::Model::FPlayer> Player){return Gs2->Cache->ListSubscribe(Gs2::Matchmaking::Model::FGathering::TypeName,Gs2::Matchmaking::Model::Cache::FGatheringCache::CreateCacheParentKey(NamespaceName,AccessToken.IsValid() ? AccessToken->GetUserId() : TOptional<FString>(),AccessToken.IsValid() ? AccessToken->GetTimeOffset() : TOptional<int32>()),Callback,Callback);}
    void FUserAccessTokenDomain::UnsubscribeDoMatchmaking(Gs2::Core::Domain::CallbackID CallbackID,const TSharedPtr<Gs2::Matchmaking::Model::FPlayer> Player){Gs2->Cache->ListUnsubscribe(Gs2::Matchmaking::Model::FGathering::TypeName,Gs2::Matchmaking::Model::Cache::FGatheringCache::CreateCacheParentKey(NamespaceName,AccessToken.IsValid() ? AccessToken->GetUserId() : TOptional<FString>(),AccessToken.IsValid() ? AccessToken->GetTimeOffset() : TOptional<int32>()),CallbackID);}
    class FUserAccessTokenDomain::FCollectDoMatchmakingTask:public Gs2::Core::Util::TGs2Future<TArray<Gs2::Matchmaking::Model::FGatheringPtr>>,public TSharedFromThis<FCollectDoMatchmakingTask>{const TSharedPtr<FUserAccessTokenDomain> Self;const TFunction<void(TArray<Gs2::Matchmaking::Model::FGatheringPtr>)> OnCollected;const TSharedPtr<Gs2::Matchmaking::Model::FPlayer> QueryPlayer;public:FCollectDoMatchmakingTask(const TSharedPtr<FUserAccessTokenDomain>& Self,TFunction<void(TArray<Gs2::Matchmaking::Model::FGatheringPtr>)> OnCollected,const TSharedPtr<Gs2::Matchmaking::Model::FPlayer> Player):Self(Self),OnCollected(OnCollected),QueryPlayer(Player){}FCollectDoMatchmakingTask(const FCollectDoMatchmakingTask& From):TGs2Future(From),Self(From.Self),OnCollected(From.OnCollected),QueryPlayer(From.QueryPlayer){}Gs2::Core::Model::FGs2ErrorPtr Action(TSharedPtr<TSharedPtr<TArray<Gs2::Matchmaking::Model::FGatheringPtr>>> Result)override{TArray<Gs2::Matchmaking::Model::FGatheringPtr> Items;auto It=Self->DoMatchmaking(QueryPlayer)->begin();while(It.HasNext()){if(It.IsError())return It.Error();if(It.IsCurrentValid())Items.Add(It.Current());++It;}if(It.IsError())return It.Error();*Result=MakeShared<TArray<Gs2::Matchmaking::Model::FGatheringPtr>>(Items);if(OnCollected)OnCollected(Items);return nullptr;}};
    Gs2::Core::Domain::CallbackID FUserAccessTokenDomain::SubscribeDoMatchmaking(TFunction<void(TArray<Gs2::Matchmaking::Model::FGatheringPtr>)> Callback,const TSharedPtr<Gs2::Matchmaking::Model::FPlayer> Player){const TWeakPtr<Gs2::Core::Domain::FGs2> WeakGs2=Gs2;const TWeakPtr<Matchmaking::Domain::FGs2MatchmakingDomain> WeakService=Service;const auto QN=NamespaceName;const auto QU=AccessToken.IsValid() ? AccessToken->GetUserId() : TOptional<FString>();
    const auto SourceToken=AccessToken;const auto QP=Player;const auto Parent=Gs2::Matchmaking::Model::Cache::FGatheringCache::CreateCacheParentKey(NamespaceName,AccessToken.IsValid() ? AccessToken->GetUserId() : TOptional<FString>(),AccessToken.IsValid() ? AccessToken->GetTimeOffset() : TOptional<int32>());return Gs2->Cache->ListSubscribeTyped(Gs2::Matchmaking::Model::FGathering::TypeName,Parent,[Callback,WeakGs2](const TArray<FGs2ObjectPtr>& Values){if(!WeakGs2.Pin().IsValid())return;TArray<Gs2::Matchmaking::Model::FGatheringPtr> Out;for(const auto& V:Values)if(V.IsValid())Out.Add(StaticCastSharedPtr<Gs2::Matchmaking::Model::FGathering>(V));Callback(Out);},[WeakGs2,WeakService,Callback,QN,QU,QP,SourceToken](){auto O=WeakGs2.Pin();if(!O.IsValid())return;auto D=MakeShared<FUserAccessTokenDomain>(O,WeakService.Pin(),QN,SourceToken);auto T=Gs2::Core::Util::New<FAsyncTask<FCollectDoMatchmakingTask>>(D,Callback,QP);T->StartBackgroundTask();});}
    void FUserAccessTokenDomain::InvalidateDoMatchmaking(const TSharedPtr<Gs2::Matchmaking::Model::FPlayer> Player){Gs2->Cache->ClearListCache(Gs2::Matchmaking::Model::FGathering::TypeName,Gs2::Matchmaking::Model::Cache::FGatheringCache::CreateCacheParentKey(NamespaceName,AccessToken.IsValid() ? AccessToken->GetUserId() : TOptional<FString>(),AccessToken.IsValid() ? AccessToken->GetTimeOffset() : TOptional<int32>()));}
    FUserAccessTokenDomain::FSubscribeDoMatchmakingWithInitialCallTask::FSubscribeDoMatchmakingWithInitialCallTask(const TSharedPtr<FUserAccessTokenDomain>& Self,TFunction<void(TArray<Gs2::Matchmaking::Model::FGatheringPtr>)> Callback,const TSharedPtr<Gs2::Matchmaking::Model::FPlayer> Player):Self(Self),Callback(Callback),QueryPlayer(Player){}
    FUserAccessTokenDomain::FSubscribeDoMatchmakingWithInitialCallTask::FSubscribeDoMatchmakingWithInitialCallTask(const FSubscribeDoMatchmakingWithInitialCallTask& From):TGs2Future(From),Self(From.Self),Callback(From.Callback),QueryPlayer(From.QueryPlayer){}
    Gs2::Core::Model::FGs2ErrorPtr FUserAccessTokenDomain::FSubscribeDoMatchmakingWithInitialCallTask::Action(TSharedPtr<TSharedPtr<Gs2::Core::Domain::CallbackID>> Result){auto T=Gs2::Core::Util::New<FAsyncTask<FCollectDoMatchmakingTask>>(Self,TFunction<void(TArray<Gs2::Matchmaking::Model::FGatheringPtr>)>(),QueryPlayer);T->StartSynchronousTask();T->EnsureCompletion();if(T->GetTask().IsError())return T->GetTask().Error();auto V=T->GetTask().Result();auto ID=Self->SubscribeDoMatchmaking(Callback,QueryPlayer);Callback(*V);*Result=MakeShared<Gs2::Core::Domain::CallbackID>(ID);return nullptr;}
    TSharedPtr<FAsyncTask<FUserAccessTokenDomain::FSubscribeDoMatchmakingWithInitialCallTask>> FUserAccessTokenDomain::SubscribeDoMatchmakingWithInitialCall(TFunction<void(TArray<Gs2::Matchmaking::Model::FGatheringPtr>)> Callback,const TSharedPtr<Gs2::Matchmaking::Model::FPlayer> Player){return Gs2::Core::Util::New<FAsyncTask<FSubscribeDoMatchmakingWithInitialCallTask>>(this->AsShared(),Callback,Player);}

    TSharedPtr<Gs2::Matchmaking::Domain::Model::FGatheringAccessTokenDomain> FUserAccessTokenDomain::Gathering(
        const FString GatheringName
    )
    {
        return MakeShared<Gs2::Matchmaking::Domain::Model::FGatheringAccessTokenDomain>(
            Gs2,
            Service,
            NamespaceName,
            AccessToken,
            GatheringName == TEXT("") ? TOptional<FString>() : TOptional<FString>(GatheringName)
        );
    }

    Gs2::Matchmaking::Domain::Iterator::FDescribeRatingsIteratorPtr FUserAccessTokenDomain::Ratings(
    ) const
    {
        return MakeShared<Gs2::Matchmaking::Domain::Iterator::FDescribeRatingsIterator>(
            Gs2,
            Client,
            NamespaceName,
            AccessToken
        );
    }

    Gs2::Core::Domain::CallbackID FUserAccessTokenDomain::SubscribeRatings(
    TFunction<void()> Callback
    )
    {
        return Gs2->Cache->ListSubscribe(
            Gs2::Matchmaking::Model::FRating::TypeName,
            Gs2::Matchmaking::Model::Cache::FRatingCache::CreateCacheParentKey(
                NamespaceName,
                AccessToken.IsValid() ? AccessToken->GetUserId() : TOptional<FString>(),
                AccessToken.IsValid() ? AccessToken->GetTimeOffset() : TOptional<int32>()
            ),
            Callback,
            Callback
        );
    }
    void FUserAccessTokenDomain::UnsubscribeRatings(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        Gs2->Cache->ListUnsubscribe(
            Gs2::Matchmaking::Model::FRating::TypeName,
            Gs2::Matchmaking::Model::Cache::FRatingCache::CreateCacheParentKey(
                NamespaceName,
                AccessToken.IsValid() ? AccessToken->GetUserId() : TOptional<FString>(),
                AccessToken.IsValid() ? AccessToken->GetTimeOffset() : TOptional<int32>()
            ),
            CallbackID
        );
    }
    class FUserAccessTokenDomain::FCollectRatingsTask : public Gs2::Core::Util::TGs2Future<TArray<Gs2::Matchmaking::Model::FRatingPtr>>, public TSharedFromThis<FCollectRatingsTask>
    {
        const TSharedPtr<FUserAccessTokenDomain> Self;
        const TFunction<void(TArray<Gs2::Matchmaking::Model::FRatingPtr>)> OnCollected;

    public:
        explicit FCollectRatingsTask(const TSharedPtr<FUserAccessTokenDomain>& Self, TFunction<void(TArray<Gs2::Matchmaking::Model::FRatingPtr>)> OnCollected) : Self(Self), OnCollected(OnCollected) {}
        FCollectRatingsTask(const FCollectRatingsTask& From) : TGs2Future(From), Self(From.Self), OnCollected(From.OnCollected) {}
        virtual Gs2::Core::Model::FGs2ErrorPtr Action(TSharedPtr<TSharedPtr<TArray<Gs2::Matchmaking::Model::FRatingPtr>>> Result) override
        {
            TArray<Gs2::Matchmaking::Model::FRatingPtr> Items;
            auto Iterator = Self->Ratings()->begin();
            while (Iterator.HasNext())
            {
                if (Iterator.IsError()) return Iterator.Error();
                if (Iterator.IsCurrentValid()) Items.Add(Iterator.Current());
                ++Iterator;
            }
            if (Iterator.IsError()) return Iterator.Error();
            *Result = MakeShared<TArray<Gs2::Matchmaking::Model::FRatingPtr>>(Items);
            if (OnCollected) OnCollected(Items);
            return nullptr;
        }
    };

    Gs2::Core::Domain::CallbackID FUserAccessTokenDomain::SubscribeRatings(
        TFunction<void(TArray<Gs2::Matchmaking::Model::FRatingPtr>)> Callback
    )
    {
        const TWeakPtr<Gs2::Core::Domain::FGs2> WeakGs2 = this->Gs2;
        const TWeakPtr<Matchmaking::Domain::FGs2MatchmakingDomain> WeakService = this->Service;
        const auto SourceToken = this->AccessToken;
        const TOptional<FString> RegisteredUserId = SourceToken.IsValid() ? TOptional<FString>(SourceToken->GetUserId()) : TOptional<FString>();
        const int32 RegisteredTimeOffset = SourceToken.IsValid() ? SourceToken->GetTimeOffset().Get(0) : 0;
        const auto QueryNamespaceName = NamespaceName;
        const auto Parent = Gs2::Matchmaking::Model::Cache::FRatingCache::CreateCacheParentKey(
        NamespaceName,
        AccessToken.IsValid() ? AccessToken->GetUserId() : TOptional<FString>(),
        AccessToken.IsValid() ? AccessToken->GetTimeOffset() : TOptional<int32>()
    );
        return Gs2->Cache->ListSubscribeTyped(
            Gs2::Matchmaking::Model::FRating::TypeName,
            Parent,
            [Callback, WeakGs2](const TArray<FGs2ObjectPtr>& Values)
            {
                if (!WeakGs2.Pin().IsValid()) return;
                TArray<Gs2::Matchmaking::Model::FRatingPtr> TypedValues;
                for (const auto& Value : Values) if (Value.IsValid()) TypedValues.Add(StaticCastSharedPtr<Gs2::Matchmaking::Model::FRating>(Value));
                Callback(TypedValues);
            },
            [WeakGs2, WeakService, Callback, QueryNamespaceName, SourceToken, RegisteredUserId, RegisteredTimeOffset]()
            {
                const auto Owner = WeakGs2.Pin();
                if (!Owner.IsValid() || !SourceToken.IsValid() || !RegisteredUserId.IsSet()) return;
                const auto TokenSnapshot = MakeShared<Gs2::Auth::Model::FAccessToken>(*SourceToken);
                if (TokenSnapshot->GetUserId() != RegisteredUserId || TokenSnapshot->GetTimeOffset().Get(0) != RegisteredTimeOffset) return;
                const auto Domain = MakeShared<FUserAccessTokenDomain>(Owner, WeakService.Pin(), QueryNamespaceName, TokenSnapshot);
                const auto Task = Gs2::Core::Util::New<FAsyncTask<FCollectRatingsTask>>(Domain, Callback);
                Task->StartBackgroundTask();
            }
        );
    }

    void FUserAccessTokenDomain::InvalidateRatings()
    {
        Gs2->Cache->ClearListCache(
            Gs2::Matchmaking::Model::FRating::TypeName,
            Gs2::Matchmaking::Model::Cache::FRatingCache::CreateCacheParentKey(
        NamespaceName,
        AccessToken.IsValid() ? AccessToken->GetUserId() : TOptional<FString>(),
        AccessToken.IsValid() ? AccessToken->GetTimeOffset() : TOptional<int32>()
    )
        );
    }

    FUserAccessTokenDomain::FSubscribeRatingsWithInitialCallTask::FSubscribeRatingsWithInitialCallTask(const TSharedPtr<FUserAccessTokenDomain>& Self, TFunction<void(TArray<Gs2::Matchmaking::Model::FRatingPtr>)> Callback) : Self(Self), Callback(Callback) {}
    FUserAccessTokenDomain::FSubscribeRatingsWithInitialCallTask::FSubscribeRatingsWithInitialCallTask(const FSubscribeRatingsWithInitialCallTask& From) : TGs2Future(From), Self(From.Self), Callback(From.Callback) {}
    Gs2::Core::Model::FGs2ErrorPtr FUserAccessTokenDomain::FSubscribeRatingsWithInitialCallTask::Action(TSharedPtr<TSharedPtr<Gs2::Core::Domain::CallbackID>> Result)
    {
        const auto Task = Gs2::Core::Util::New<FAsyncTask<FCollectRatingsTask>>(Self, TFunction<void(TArray<Gs2::Matchmaking::Model::FRatingPtr>)>());
        Task->StartSynchronousTask(); Task->EnsureCompletion();
        if (Task->GetTask().IsError()) return Task->GetTask().Error();
        const auto Values = Task->GetTask().Result();
        const auto CallbackId = Self->SubscribeRatings(Callback);
        Callback(*Values); *Result = MakeShared<Gs2::Core::Domain::CallbackID>(CallbackId);
        return nullptr;
    }
    TSharedPtr<FAsyncTask<FUserAccessTokenDomain::FSubscribeRatingsWithInitialCallTask>> FUserAccessTokenDomain::SubscribeRatingsWithInitialCall(TFunction<void(TArray<Gs2::Matchmaking::Model::FRatingPtr>)> Callback)
    {
        return Gs2::Core::Util::New<FAsyncTask<FSubscribeRatingsWithInitialCallTask>>(this->AsShared(), Callback);
    }

    TSharedPtr<Gs2::Matchmaking::Domain::Model::FRatingAccessTokenDomain> FUserAccessTokenDomain::Rating(
        const FString RatingName
    )
    {
        return MakeShared<Gs2::Matchmaking::Domain::Model::FRatingAccessTokenDomain>(
            Gs2,
            Service,
            NamespaceName,
            AccessToken,
            RatingName == TEXT("") ? TOptional<FString>() : TOptional<FString>(RatingName)
        );
    }

    TSharedPtr<Gs2::Matchmaking::Domain::Model::FBallotAccessTokenDomain> FUserAccessTokenDomain::Ballot(
        const FString RatingName,
        const FString GatheringName,
        const int32 NumberOfPlayer,
        const FString KeyId
    )
    {
        return MakeShared<Gs2::Matchmaking::Domain::Model::FBallotAccessTokenDomain>(
            Gs2,
            Service,
            NamespaceName,
            AccessToken,
            RatingName == TEXT("") ? TOptional<FString>() : TOptional<FString>(RatingName),
            GatheringName == TEXT("") ? TOptional<FString>() : TOptional<FString>(GatheringName),
            NumberOfPlayer,
            KeyId == TEXT("") ? TOptional<FString>() : TOptional<FString>(KeyId)
        );
    }

    TSharedPtr<Gs2::Matchmaking::Domain::Model::FSeasonAccessTokenDomain> FUserAccessTokenDomain::Season(
        const FString SeasonName,
        const TOptional<int64> Season
    )
    {
        return MakeShared<Gs2::Matchmaking::Domain::Model::FSeasonAccessTokenDomain>(
            Gs2,
            Service,
            NamespaceName,
            AccessToken,
            SeasonName == TEXT("") ? TOptional<FString>() : TOptional<FString>(SeasonName),
            Season
        );
    }

    FString FUserAccessTokenDomain::CreateCacheParentKey(
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

    FString FUserAccessTokenDomain::CreateCacheKey(
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

