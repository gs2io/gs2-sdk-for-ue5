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

#include "Matchmaking/Domain/Model/SeasonAccessToken.h"
#include "Matchmaking/Domain/Model/Season.h"
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
#include "Matchmaking/Model/Cache/SeasonGathering.h"
#include "Matchmaking/Model/Cache/JoinedSeasonGathering.h"

#include "Core/Domain/Gs2.h"
#include "Core/Domain/Transaction/JobQueueJobDomainFactory.h"
#include "Core/Domain/Transaction/InternalTransactionDomainFactory.h"
#include "Core/Domain/Transaction/ManualTransactionAccessTokenDomain.h"

namespace Gs2::Matchmaking::Domain::Model
{

    FSeasonAccessTokenDomain::FSeasonAccessTokenDomain(
        const Core::Domain::FGs2Ptr& Gs2,
        const Matchmaking::Domain::FGs2MatchmakingDomainPtr& Service,
        const TOptional<FString> NamespaceName,
        const Gs2::Auth::Model::FAccessTokenPtr& AccessToken,
        const TOptional<FString> SeasonName,
        const TOptional<int64> Season
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Gs2(Gs2),
        Service(Service),
        Client(MakeShared<Gs2::Matchmaking::FGs2MatchmakingRestClient>(Gs2->RestSession)),
        NamespaceName(NamespaceName),
        AccessToken(AccessToken),
        SeasonName(SeasonName),
        Season(Season),
        ParentKey(Gs2::Matchmaking::Domain::Model::FUserDomain::CreateCacheParentKey(
            NamespaceName,
            UserId(),
            "Season"
        ))
    {
    }

    FSeasonAccessTokenDomain::FSeasonAccessTokenDomain(
        const FSeasonAccessTokenDomain& From
    ):
        Gs2(From.Gs2),
        Service(From.Service),
        Client(From.Client),
        NamespaceName(From.NamespaceName),
        AccessToken(From.AccessToken),
        SeasonName(From.SeasonName),
        Season(From.Season),
        ParentKey(From.ParentKey)
    {

    }

    Gs2::Matchmaking::Domain::Iterator::FDoSeasonMatchmakingIteratorPtr FSeasonAccessTokenDomain::DoSeasonMatchmaking(
    ) const
    {
        return MakeShared<Gs2::Matchmaking::Domain::Iterator::FDoSeasonMatchmakingIterator>(
            Gs2,
            Client,
            NamespaceName,
            SeasonName,
            AccessToken
        );
    }


    Gs2::Core::Domain::CallbackID FSeasonAccessTokenDomain::SubscribeDoSeasonMatchmaking(TFunction<void()> Callback){return Gs2->Cache->ListSubscribe(Gs2::Matchmaking::Model::FSeasonGathering::TypeName,Gs2::Matchmaking::Model::Cache::FSeasonGatheringCache::CreateCacheParentKey(NamespaceName,AccessToken.IsValid() ? AccessToken->GetUserId() : TOptional<FString>(),SeasonName,Season,AccessToken.IsValid() ? AccessToken->GetTimeOffset() : TOptional<int32>()),Callback,Callback);}
    void FSeasonAccessTokenDomain::UnsubscribeDoSeasonMatchmaking(Gs2::Core::Domain::CallbackID CallbackID){Gs2->Cache->ListUnsubscribe(Gs2::Matchmaking::Model::FSeasonGathering::TypeName,Gs2::Matchmaking::Model::Cache::FSeasonGatheringCache::CreateCacheParentKey(NamespaceName,AccessToken.IsValid() ? AccessToken->GetUserId() : TOptional<FString>(),SeasonName,Season,AccessToken.IsValid() ? AccessToken->GetTimeOffset() : TOptional<int32>()),CallbackID);}
    class FSeasonAccessTokenDomain::FCollectDoSeasonMatchmakingTask:public Gs2::Core::Util::TGs2Future<TArray<Gs2::Matchmaking::Model::FSeasonGatheringPtr>>,public TSharedFromThis<FCollectDoSeasonMatchmakingTask>{const TSharedPtr<FSeasonAccessTokenDomain> Self;const TFunction<void(TArray<Gs2::Matchmaking::Model::FSeasonGatheringPtr>)> OnCollected;public:FCollectDoSeasonMatchmakingTask(const TSharedPtr<FSeasonAccessTokenDomain>& Self,TFunction<void(TArray<Gs2::Matchmaking::Model::FSeasonGatheringPtr>)> OnCollected):Self(Self),OnCollected(OnCollected){}FCollectDoSeasonMatchmakingTask(const FCollectDoSeasonMatchmakingTask& From):TGs2Future(From),Self(From.Self),OnCollected(From.OnCollected){}Gs2::Core::Model::FGs2ErrorPtr Action(TSharedPtr<TSharedPtr<TArray<Gs2::Matchmaking::Model::FSeasonGatheringPtr>>> Result)override{TArray<Gs2::Matchmaking::Model::FSeasonGatheringPtr> Items;auto It=Self->DoSeasonMatchmaking()->begin();while(It.HasNext()){if(It.IsError())return It.Error();if(It.IsCurrentValid())Items.Add(It.Current());++It;}if(It.IsError())return It.Error();*Result=MakeShared<TArray<Gs2::Matchmaking::Model::FSeasonGatheringPtr>>(Items);if(OnCollected)OnCollected(Items);return nullptr;}};
    Gs2::Core::Domain::CallbackID FSeasonAccessTokenDomain::SubscribeDoSeasonMatchmaking(TFunction<void(TArray<Gs2::Matchmaking::Model::FSeasonGatheringPtr>)> Callback){const TWeakPtr<Gs2::Core::Domain::FGs2> WeakGs2=Gs2;const TWeakPtr<Matchmaking::Domain::FGs2MatchmakingDomain> WeakService=Service;const auto QN=NamespaceName;const auto QU=AccessToken.IsValid() ? AccessToken->GetUserId() : TOptional<FString>();
    const auto SourceToken=AccessToken;const auto QS=SeasonName;const auto QE=Season;const auto Parent=Gs2::Matchmaking::Model::Cache::FSeasonGatheringCache::CreateCacheParentKey(NamespaceName,AccessToken.IsValid() ? AccessToken->GetUserId() : TOptional<FString>(),SeasonName,Season,AccessToken.IsValid() ? AccessToken->GetTimeOffset() : TOptional<int32>());return Gs2->Cache->ListSubscribeTyped(Gs2::Matchmaking::Model::FSeasonGathering::TypeName,Parent,[Callback,WeakGs2](const TArray<FGs2ObjectPtr>& Values){if(!WeakGs2.Pin().IsValid())return;TArray<Gs2::Matchmaking::Model::FSeasonGatheringPtr> Out;for(const auto& V:Values)if(V.IsValid())Out.Add(StaticCastSharedPtr<Gs2::Matchmaking::Model::FSeasonGathering>(V));Callback(Out);},[WeakGs2,WeakService,Callback,QN,QU,QS,QE,SourceToken](){auto O=WeakGs2.Pin();if(!O.IsValid())return;auto D=MakeShared<FSeasonAccessTokenDomain>(O,WeakService.Pin(),QN,SourceToken,QS,QE);auto T=Gs2::Core::Util::New<FAsyncTask<FCollectDoSeasonMatchmakingTask>>(D,Callback);T->StartBackgroundTask();});}
    void FSeasonAccessTokenDomain::InvalidateDoSeasonMatchmaking(){Gs2->Cache->ClearListCache(Gs2::Matchmaking::Model::FSeasonGathering::TypeName,Gs2::Matchmaking::Model::Cache::FSeasonGatheringCache::CreateCacheParentKey(NamespaceName,AccessToken.IsValid() ? AccessToken->GetUserId() : TOptional<FString>(),SeasonName,Season,AccessToken.IsValid() ? AccessToken->GetTimeOffset() : TOptional<int32>()));}
    FSeasonAccessTokenDomain::FSubscribeDoSeasonMatchmakingWithInitialCallTask::FSubscribeDoSeasonMatchmakingWithInitialCallTask(const TSharedPtr<FSeasonAccessTokenDomain>& Self,TFunction<void(TArray<Gs2::Matchmaking::Model::FSeasonGatheringPtr>)> Callback):Self(Self),Callback(Callback){}
    FSeasonAccessTokenDomain::FSubscribeDoSeasonMatchmakingWithInitialCallTask::FSubscribeDoSeasonMatchmakingWithInitialCallTask(const FSubscribeDoSeasonMatchmakingWithInitialCallTask& From):TGs2Future(From),Self(From.Self),Callback(From.Callback){}
    Gs2::Core::Model::FGs2ErrorPtr FSeasonAccessTokenDomain::FSubscribeDoSeasonMatchmakingWithInitialCallTask::Action(TSharedPtr<TSharedPtr<Gs2::Core::Domain::CallbackID>> Result){auto T=Gs2::Core::Util::New<FAsyncTask<FCollectDoSeasonMatchmakingTask>>(Self,TFunction<void(TArray<Gs2::Matchmaking::Model::FSeasonGatheringPtr>)>());T->StartSynchronousTask();T->EnsureCompletion();if(T->GetTask().IsError())return T->GetTask().Error();auto V=T->GetTask().Result();auto ID=Self->SubscribeDoSeasonMatchmaking(Callback);Callback(*V);*Result=MakeShared<Gs2::Core::Domain::CallbackID>(ID);return nullptr;}
    TSharedPtr<FAsyncTask<FSeasonAccessTokenDomain::FSubscribeDoSeasonMatchmakingWithInitialCallTask>> FSeasonAccessTokenDomain::SubscribeDoSeasonMatchmakingWithInitialCall(TFunction<void(TArray<Gs2::Matchmaking::Model::FSeasonGatheringPtr>)> Callback){return Gs2::Core::Util::New<FAsyncTask<FSubscribeDoSeasonMatchmakingWithInitialCallTask>>(this->AsShared(),Callback);}

    TSharedPtr<Gs2::Matchmaking::Domain::Model::FSeasonGatheringAccessTokenDomain> FSeasonAccessTokenDomain::SeasonGathering(
        const int64 Tier,
        const FString SeasonGatheringName
    )
    {
        return MakeShared<Gs2::Matchmaking::Domain::Model::FSeasonGatheringAccessTokenDomain>(
            Gs2,
            Service,
            NamespaceName,
            AccessToken,
            SeasonName,
            Season,
            Tier,
            SeasonGatheringName == TEXT("") ? TOptional<FString>() : TOptional<FString>(SeasonGatheringName)
        );
    }

    Gs2::Matchmaking::Domain::Iterator::FDescribeJoinedSeasonGatheringsIteratorPtr FSeasonAccessTokenDomain::JoinedSeasonGatherings(
    ) const
    {
        return MakeShared<Gs2::Matchmaking::Domain::Iterator::FDescribeJoinedSeasonGatheringsIterator>(
            Gs2,
            Client,
            NamespaceName,
            AccessToken,
            SeasonName
        );
    }

    Gs2::Core::Domain::CallbackID FSeasonAccessTokenDomain::SubscribeJoinedSeasonGatherings(
    TFunction<void()> Callback
    )
    {
        return Gs2->Cache->ListSubscribe(
            Gs2::Matchmaking::Model::FJoinedSeasonGathering::TypeName,
            Gs2::Matchmaking::Model::Cache::FJoinedSeasonGatheringCache::CreateCacheParentKey(
                NamespaceName,
                AccessToken.IsValid() ? AccessToken->GetUserId() : TOptional<FString>(),
                SeasonName,
                Season,
                AccessToken.IsValid() ? AccessToken->GetTimeOffset() : TOptional<int32>()
            ),
            Callback,
            Callback
        );
    }
    void FSeasonAccessTokenDomain::UnsubscribeJoinedSeasonGatherings(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        Gs2->Cache->ListUnsubscribe(
            Gs2::Matchmaking::Model::FJoinedSeasonGathering::TypeName,
            Gs2::Matchmaking::Model::Cache::FJoinedSeasonGatheringCache::CreateCacheParentKey(
                NamespaceName,
                AccessToken.IsValid() ? AccessToken->GetUserId() : TOptional<FString>(),
                SeasonName,
                Season,
                AccessToken.IsValid() ? AccessToken->GetTimeOffset() : TOptional<int32>()
            ),
            CallbackID
        );
    }
    class FSeasonAccessTokenDomain::FCollectJoinedSeasonGatheringsTask : public Gs2::Core::Util::TGs2Future<TArray<Gs2::Matchmaking::Model::FJoinedSeasonGatheringPtr>>, public TSharedFromThis<FCollectJoinedSeasonGatheringsTask>
    {
        const TSharedPtr<FSeasonAccessTokenDomain> Self;
        const TFunction<void(TArray<Gs2::Matchmaking::Model::FJoinedSeasonGatheringPtr>)> OnCollected;

    public:
        explicit FCollectJoinedSeasonGatheringsTask(const TSharedPtr<FSeasonAccessTokenDomain>& Self, TFunction<void(TArray<Gs2::Matchmaking::Model::FJoinedSeasonGatheringPtr>)> OnCollected) : Self(Self), OnCollected(OnCollected) {}
        FCollectJoinedSeasonGatheringsTask(const FCollectJoinedSeasonGatheringsTask& From) : TGs2Future(From), Self(From.Self), OnCollected(From.OnCollected) {}
        virtual Gs2::Core::Model::FGs2ErrorPtr Action(TSharedPtr<TSharedPtr<TArray<Gs2::Matchmaking::Model::FJoinedSeasonGatheringPtr>>> Result) override
        {
            TArray<Gs2::Matchmaking::Model::FJoinedSeasonGatheringPtr> Items;
            auto Iterator = Self->JoinedSeasonGatherings()->begin();
            while (Iterator.HasNext())
            {
                if (Iterator.IsError()) return Iterator.Error();
                if (Iterator.IsCurrentValid()) Items.Add(Iterator.Current());
                ++Iterator;
            }
            if (Iterator.IsError()) return Iterator.Error();
            *Result = MakeShared<TArray<Gs2::Matchmaking::Model::FJoinedSeasonGatheringPtr>>(Items);
            if (OnCollected) OnCollected(Items);
            return nullptr;
        }
    };

    Gs2::Core::Domain::CallbackID FSeasonAccessTokenDomain::SubscribeJoinedSeasonGatherings(
        TFunction<void(TArray<Gs2::Matchmaking::Model::FJoinedSeasonGatheringPtr>)> Callback
    )
    {
        const TWeakPtr<Gs2::Core::Domain::FGs2> WeakGs2 = this->Gs2;
        const TWeakPtr<Matchmaking::Domain::FGs2MatchmakingDomain> WeakService = this->Service;
        const auto SourceToken = this->AccessToken;
        const TOptional<FString> RegisteredUserId = SourceToken.IsValid() ? TOptional<FString>(SourceToken->GetUserId()) : TOptional<FString>();
        const int32 RegisteredTimeOffset = SourceToken.IsValid() ? SourceToken->GetTimeOffset().Get(0) : 0;
        const auto QueryNamespaceName = NamespaceName;
        const auto QuerySeasonName = SeasonName;
        const auto QuerySeason = Season;
        const auto Parent = Gs2::Matchmaking::Model::Cache::FJoinedSeasonGatheringCache::CreateCacheParentKey(
        NamespaceName,
        AccessToken.IsValid() ? AccessToken->GetUserId() : TOptional<FString>(),
        SeasonName,
        Season,
        AccessToken.IsValid() ? AccessToken->GetTimeOffset() : TOptional<int32>()
    );
        return Gs2->Cache->ListSubscribeTyped(
            Gs2::Matchmaking::Model::FJoinedSeasonGathering::TypeName,
            Parent,
            [Callback, WeakGs2](const TArray<FGs2ObjectPtr>& Values)
            {
                if (!WeakGs2.Pin().IsValid()) return;
                TArray<Gs2::Matchmaking::Model::FJoinedSeasonGatheringPtr> TypedValues;
                for (const auto& Value : Values) if (Value.IsValid()) TypedValues.Add(StaticCastSharedPtr<Gs2::Matchmaking::Model::FJoinedSeasonGathering>(Value));
                Callback(TypedValues);
            },
            [WeakGs2, WeakService, Callback, QueryNamespaceName, QuerySeasonName, QuerySeason, SourceToken, RegisteredUserId, RegisteredTimeOffset]()
            {
                const auto Owner = WeakGs2.Pin();
                if (!Owner.IsValid() || !SourceToken.IsValid() || !RegisteredUserId.IsSet()) return;
                const auto TokenSnapshot = MakeShared<Gs2::Auth::Model::FAccessToken>(*SourceToken);
                if (TokenSnapshot->GetUserId() != RegisteredUserId || TokenSnapshot->GetTimeOffset().Get(0) != RegisteredTimeOffset) return;
                const auto Domain = MakeShared<FSeasonAccessTokenDomain>(Owner, WeakService.Pin(), QueryNamespaceName, TokenSnapshot, QuerySeasonName, QuerySeason);
                const auto Task = Gs2::Core::Util::New<FAsyncTask<FCollectJoinedSeasonGatheringsTask>>(Domain, Callback);
                Task->StartBackgroundTask();
            }
        );
    }

    void FSeasonAccessTokenDomain::InvalidateJoinedSeasonGatherings()
    {
        Gs2->Cache->ClearListCache(
            Gs2::Matchmaking::Model::FJoinedSeasonGathering::TypeName,
            Gs2::Matchmaking::Model::Cache::FJoinedSeasonGatheringCache::CreateCacheParentKey(
        NamespaceName,
        AccessToken.IsValid() ? AccessToken->GetUserId() : TOptional<FString>(),
        SeasonName,
        Season,
        AccessToken.IsValid() ? AccessToken->GetTimeOffset() : TOptional<int32>()
    )
        );
    }

    FSeasonAccessTokenDomain::FSubscribeJoinedSeasonGatheringsWithInitialCallTask::FSubscribeJoinedSeasonGatheringsWithInitialCallTask(const TSharedPtr<FSeasonAccessTokenDomain>& Self, TFunction<void(TArray<Gs2::Matchmaking::Model::FJoinedSeasonGatheringPtr>)> Callback) : Self(Self), Callback(Callback) {}
    FSeasonAccessTokenDomain::FSubscribeJoinedSeasonGatheringsWithInitialCallTask::FSubscribeJoinedSeasonGatheringsWithInitialCallTask(const FSubscribeJoinedSeasonGatheringsWithInitialCallTask& From) : TGs2Future(From), Self(From.Self), Callback(From.Callback) {}
    Gs2::Core::Model::FGs2ErrorPtr FSeasonAccessTokenDomain::FSubscribeJoinedSeasonGatheringsWithInitialCallTask::Action(TSharedPtr<TSharedPtr<Gs2::Core::Domain::CallbackID>> Result)
    {
        const auto Task = Gs2::Core::Util::New<FAsyncTask<FCollectJoinedSeasonGatheringsTask>>(Self, TFunction<void(TArray<Gs2::Matchmaking::Model::FJoinedSeasonGatheringPtr>)>());
        Task->StartSynchronousTask(); Task->EnsureCompletion();
        if (Task->GetTask().IsError()) return Task->GetTask().Error();
        const auto Values = Task->GetTask().Result();
        const auto CallbackId = Self->SubscribeJoinedSeasonGatherings(Callback);
        Callback(*Values); *Result = MakeShared<Gs2::Core::Domain::CallbackID>(CallbackId);
        return nullptr;
    }
    TSharedPtr<FAsyncTask<FSeasonAccessTokenDomain::FSubscribeJoinedSeasonGatheringsWithInitialCallTask>> FSeasonAccessTokenDomain::SubscribeJoinedSeasonGatheringsWithInitialCall(TFunction<void(TArray<Gs2::Matchmaking::Model::FJoinedSeasonGatheringPtr>)> Callback)
    {
        return Gs2::Core::Util::New<FAsyncTask<FSubscribeJoinedSeasonGatheringsWithInitialCallTask>>(this->AsShared(), Callback);
    }

    TSharedPtr<Gs2::Matchmaking::Domain::Model::FJoinedSeasonGatheringAccessTokenDomain> FSeasonAccessTokenDomain::JoinedSeasonGathering(
    )
    {
        return MakeShared<Gs2::Matchmaking::Domain::Model::FJoinedSeasonGatheringAccessTokenDomain>(
            Gs2,
            Service,
            NamespaceName,
            AccessToken,
            SeasonName,
            Season
        );
    }

    FString FSeasonAccessTokenDomain::CreateCacheParentKey(
        TOptional<FString> NamespaceName,
        TOptional<FString> UserId,
        TOptional<FString> SeasonName,
        TOptional<int64> Season,
        FString ChildType
    )
    {
        return FString("") +
            (NamespaceName.IsSet() ? *NamespaceName : "null") + ":" +
            (UserId.IsSet() ? *UserId : "null") + ":" +
            (SeasonName.IsSet() ? *SeasonName : "null") + ":" +
            (Season.IsSet() ? FString::FromInt(*Season) : "null") + ":" +
            ChildType;
    }

    FString FSeasonAccessTokenDomain::CreateCacheKey(
        TOptional<FString> SeasonName,
        TOptional<int64> Season
    )
    {
        return FString("") +
            (SeasonName.IsSet() ? *SeasonName : "null") + ":" + 
            (Season.IsSet() ? FString::FromInt(*Season) : "null");
    }
}

#if defined(_MSC_VER)
#pragma warning (pop)
#elif defined(__clang__)
#pragma clang diagnostic pop
#endif
