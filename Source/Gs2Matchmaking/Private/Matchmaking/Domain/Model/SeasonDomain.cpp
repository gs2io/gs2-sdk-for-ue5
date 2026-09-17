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
#include "Matchmaking/Model/Cache/JoinedSeasonGathering.h"

#include "Matchmaking/Model/Cache/SeasonGathering.h"
#include "Core/Domain/Gs2.h"
#include "Core/Domain/Transaction/JobQueueJobDomainFactory.h"
#include "Core/Domain/Transaction/InternalTransactionDomainFactory.h"
#include "Core/Domain/Transaction/ManualTransactionDomain.h"

namespace Gs2::Matchmaking::Domain::Model
{

    FSeasonDomain::FSeasonDomain(
        const Core::Domain::FGs2Ptr& Gs2,
        const Matchmaking::Domain::FGs2MatchmakingDomainPtr& Service,
        const TOptional<FString> NamespaceName,
        const TOptional<FString> UserId,
        const TOptional<FString> SeasonName,
        const TOptional<int64> Season
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Gs2(Gs2),
        Service(Service),
        Client(MakeShared<Gs2::Matchmaking::FGs2MatchmakingRestClient>(Gs2->RestSession)),
        NamespaceName(NamespaceName),
        UserId(UserId),
        SeasonName(SeasonName),
        Season(Season),
        ParentKey(Gs2::Matchmaking::Domain::Model::FUserDomain::CreateCacheParentKey(
            NamespaceName,
            UserId,
            "Season"
        ))
    {
    }

    FSeasonDomain::FSeasonDomain(
        const FSeasonDomain& From
    ):
        Gs2(From.Gs2),
        Service(From.Service),
        Client(From.Client),
        NamespaceName(From.NamespaceName),
        UserId(From.UserId),
        SeasonName(From.SeasonName),
        Season(From.Season),
        ParentKey(From.ParentKey)
    {

    }

    Gs2::Matchmaking::Domain::Iterator::FDescribeSeasonGatheringsIteratorPtr FSeasonDomain::SeasonGatherings(
        const TOptional<int64> Tier
    ) const
    {
        return MakeShared<Gs2::Matchmaking::Domain::Iterator::FDescribeSeasonGatheringsIterator>(
            Gs2,
            Client,
            NamespaceName,
            SeasonName,
            Season,
            Tier
        );
    }

    Gs2::Core::Domain::CallbackID FSeasonDomain::SubscribeSeasonGatherings(
    TFunction<void()> Callback, const TOptional<int64> Tier
    )
    {
        return Gs2->Cache->ListSubscribe(
            Gs2::Matchmaking::Model::FSeasonGathering::TypeName,
            Gs2::Matchmaking::Model::Cache::FSeasonGatheringCache::CreateCacheParentKey(
                NamespaceName,
                UserId,
                SeasonName,
                Season,
                TOptional<int32>()
            ),
            Callback,
            Callback
        );
    }
    void FSeasonDomain::UnsubscribeSeasonGatherings(

        Gs2::Core::Domain::CallbackID CallbackID, const TOptional<int64> Tier
    )
    {
        Gs2->Cache->ListUnsubscribe(
            Gs2::Matchmaking::Model::FSeasonGathering::TypeName,
            Gs2::Matchmaking::Model::Cache::FSeasonGatheringCache::CreateCacheParentKey(
                NamespaceName,
                UserId,
                SeasonName,
                Season,
                TOptional<int32>()
            ),
            CallbackID
        );
    }
    class FSeasonDomain::FCollectSeasonGatheringsTask : public Gs2::Core::Util::TGs2Future<TArray<Gs2::Matchmaking::Model::FSeasonGatheringPtr>>, public TSharedFromThis<FCollectSeasonGatheringsTask>
    {
        const TSharedPtr<FSeasonDomain> Self;
        const TFunction<void(TArray<Gs2::Matchmaking::Model::FSeasonGatheringPtr>)> OnCollected;
    const TOptional<int64> QueryTier;
    public:
        explicit FCollectSeasonGatheringsTask(const TSharedPtr<FSeasonDomain>& Self, TFunction<void(TArray<Gs2::Matchmaking::Model::FSeasonGatheringPtr>)> OnCollected,const TOptional<int64> Tier) : Self(Self), OnCollected(OnCollected), QueryTier(Tier) {}
        FCollectSeasonGatheringsTask(const FCollectSeasonGatheringsTask& From) : TGs2Future(From), Self(From.Self), OnCollected(From.OnCollected), QueryTier(From.QueryTier) {}
        virtual Gs2::Core::Model::FGs2ErrorPtr Action(TSharedPtr<TSharedPtr<TArray<Gs2::Matchmaking::Model::FSeasonGatheringPtr>>> Result) override
        {
            TArray<Gs2::Matchmaking::Model::FSeasonGatheringPtr> Items;
            auto Iterator = Self->SeasonGatherings(QueryTier)->begin();
            while (Iterator.HasNext())
            {
                if (Iterator.IsError()) return Iterator.Error();
                if (Iterator.IsCurrentValid()) Items.Add(Iterator.Current());
                ++Iterator;
            }
            if (Iterator.IsError()) return Iterator.Error();
            *Result = MakeShared<TArray<Gs2::Matchmaking::Model::FSeasonGatheringPtr>>(Items);
            if (OnCollected) OnCollected(Items);
            return nullptr;
        }
    };

    Gs2::Core::Domain::CallbackID FSeasonDomain::SubscribeSeasonGatherings(
        TFunction<void(TArray<Gs2::Matchmaking::Model::FSeasonGatheringPtr>)> Callback,const TOptional<int64> Tier
    )
    {
        const TWeakPtr<Gs2::Core::Domain::FGs2> WeakGs2 = this->Gs2;
        const TWeakPtr<Matchmaking::Domain::FGs2MatchmakingDomain> WeakService = this->Service;
        const auto QueryNamespaceName = NamespaceName;
        const auto QueryUserId = UserId;
        const auto QuerySeasonName = SeasonName;
        const auto QuerySeason = Season;
        const auto QueryTier = Tier;
        const auto Parent = Gs2::Matchmaking::Model::Cache::FSeasonGatheringCache::CreateCacheParentKey(
        NamespaceName,
        UserId,
        SeasonName,
        Season,
        TOptional<int32>()
    );
        return Gs2->Cache->ListSubscribeTyped(
            Gs2::Matchmaking::Model::FSeasonGathering::TypeName,
            Parent,
            [Callback, WeakGs2](const TArray<FGs2ObjectPtr>& Values)
            {
                if (!WeakGs2.Pin().IsValid()) return;
                TArray<Gs2::Matchmaking::Model::FSeasonGatheringPtr> TypedValues;
                for (const auto& Value : Values) if (Value.IsValid()) TypedValues.Add(StaticCastSharedPtr<Gs2::Matchmaking::Model::FSeasonGathering>(Value));
                Callback(TypedValues);
            },
            [WeakGs2, WeakService, Callback, QueryNamespaceName, QueryUserId, QuerySeasonName, QuerySeason, QueryTier]()
            {
                const auto Owner = WeakGs2.Pin();
                if (!Owner.IsValid()) return;
                const auto Domain = MakeShared<FSeasonDomain>(Owner, WeakService.Pin(), QueryNamespaceName, QueryUserId, QuerySeasonName, QuerySeason);
                const auto Task = Gs2::Core::Util::New<FAsyncTask<FCollectSeasonGatheringsTask>>(Domain, Callback, QueryTier);
                Task->StartBackgroundTask();
            }
        );
    }

    void FSeasonDomain::InvalidateSeasonGatherings(const TOptional<int64> Tier)
    {
        Gs2->Cache->ClearListCache(
            Gs2::Matchmaking::Model::FSeasonGathering::TypeName,
            Gs2::Matchmaking::Model::Cache::FSeasonGatheringCache::CreateCacheParentKey(
        NamespaceName,
        UserId,
        SeasonName,
        Season,
        TOptional<int32>()
    )
        );
    }

    FSeasonDomain::FSubscribeSeasonGatheringsWithInitialCallTask::FSubscribeSeasonGatheringsWithInitialCallTask(const TSharedPtr<FSeasonDomain>& Self, TFunction<void(TArray<Gs2::Matchmaking::Model::FSeasonGatheringPtr>)> Callback,const TOptional<int64> Tier) : Self(Self), Callback(Callback), QueryTier(Tier) {}
    FSeasonDomain::FSubscribeSeasonGatheringsWithInitialCallTask::FSubscribeSeasonGatheringsWithInitialCallTask(const FSubscribeSeasonGatheringsWithInitialCallTask& From) : TGs2Future(From), Self(From.Self), Callback(From.Callback), QueryTier(From.QueryTier) {}
    Gs2::Core::Model::FGs2ErrorPtr FSeasonDomain::FSubscribeSeasonGatheringsWithInitialCallTask::Action(TSharedPtr<TSharedPtr<Gs2::Core::Domain::CallbackID>> Result)
    {
        const auto Task = Gs2::Core::Util::New<FAsyncTask<FCollectSeasonGatheringsTask>>(Self, TFunction<void(TArray<Gs2::Matchmaking::Model::FSeasonGatheringPtr>)>(), QueryTier);
        Task->StartSynchronousTask(); Task->EnsureCompletion();
        if (Task->GetTask().IsError()) return Task->GetTask().Error();
        const auto Values = Task->GetTask().Result();
        const auto CallbackId = Self->SubscribeSeasonGatherings(Callback, QueryTier);
        Callback(*Values); *Result = MakeShared<Gs2::Core::Domain::CallbackID>(CallbackId);
        return nullptr;
    }
    TSharedPtr<FAsyncTask<FSeasonDomain::FSubscribeSeasonGatheringsWithInitialCallTask>> FSeasonDomain::SubscribeSeasonGatheringsWithInitialCall(TFunction<void(TArray<Gs2::Matchmaking::Model::FSeasonGatheringPtr>)> Callback,const TOptional<int64> Tier)
    {
        return Gs2::Core::Util::New<FAsyncTask<FSubscribeSeasonGatheringsWithInitialCallTask>>(this->AsShared(), Callback, Tier);
    }

    Gs2::Matchmaking::Domain::Iterator::FDescribeMatchmakingSeasonGatheringsIteratorPtr FSeasonDomain::MatchmakingSeasonGatherings(
        const TOptional<int64> Tier
    ) const
    {
        return MakeShared<Gs2::Matchmaking::Domain::Iterator::FDescribeMatchmakingSeasonGatheringsIterator>(
            Gs2,
            Client,
            NamespaceName,
            SeasonName,
            Season,
            Tier
        );
    }

    Gs2::Core::Domain::CallbackID FSeasonDomain::SubscribeMatchmakingSeasonGatherings(
    TFunction<void()> Callback, const TOptional<int64> Tier
    )
    {
        return Gs2->Cache->ListSubscribe(
            Gs2::Matchmaking::Model::FSeasonGathering::TypeName,
            Gs2::Matchmaking::Model::Cache::FSeasonGatheringCache::CreateCacheParentKey(
                NamespaceName,
                UserId,
                SeasonName,
                Season,
                TOptional<int32>()
            ),
            Callback,
            Callback
        );
    }
    void FSeasonDomain::UnsubscribeMatchmakingSeasonGatherings(

        Gs2::Core::Domain::CallbackID CallbackID, const TOptional<int64> Tier
    )
    {
        Gs2->Cache->ListUnsubscribe(
            Gs2::Matchmaking::Model::FSeasonGathering::TypeName,
            Gs2::Matchmaking::Model::Cache::FSeasonGatheringCache::CreateCacheParentKey(
                NamespaceName,
                UserId,
                SeasonName,
                Season,
                TOptional<int32>()
            ),
            CallbackID
        );
    }
    class FSeasonDomain::FCollectMatchmakingSeasonGatheringsTask : public Gs2::Core::Util::TGs2Future<TArray<Gs2::Matchmaking::Model::FSeasonGatheringPtr>>, public TSharedFromThis<FCollectMatchmakingSeasonGatheringsTask>
    {
        const TSharedPtr<FSeasonDomain> Self;
        const TFunction<void(TArray<Gs2::Matchmaking::Model::FSeasonGatheringPtr>)> OnCollected;
    const TOptional<int64> QueryTier;
    public:
        explicit FCollectMatchmakingSeasonGatheringsTask(const TSharedPtr<FSeasonDomain>& Self, TFunction<void(TArray<Gs2::Matchmaking::Model::FSeasonGatheringPtr>)> OnCollected,const TOptional<int64> Tier) : Self(Self), OnCollected(OnCollected), QueryTier(Tier) {}
        FCollectMatchmakingSeasonGatheringsTask(const FCollectMatchmakingSeasonGatheringsTask& From) : TGs2Future(From), Self(From.Self), OnCollected(From.OnCollected), QueryTier(From.QueryTier) {}
        virtual Gs2::Core::Model::FGs2ErrorPtr Action(TSharedPtr<TSharedPtr<TArray<Gs2::Matchmaking::Model::FSeasonGatheringPtr>>> Result) override
        {
            TArray<Gs2::Matchmaking::Model::FSeasonGatheringPtr> Items;
            auto Iterator = Self->MatchmakingSeasonGatherings(QueryTier)->begin();
            while (Iterator.HasNext())
            {
                if (Iterator.IsError()) return Iterator.Error();
                if (Iterator.IsCurrentValid()) Items.Add(Iterator.Current());
                ++Iterator;
            }
            if (Iterator.IsError()) return Iterator.Error();
            *Result = MakeShared<TArray<Gs2::Matchmaking::Model::FSeasonGatheringPtr>>(Items);
            if (OnCollected) OnCollected(Items);
            return nullptr;
        }
    };

    Gs2::Core::Domain::CallbackID FSeasonDomain::SubscribeMatchmakingSeasonGatherings(
        TFunction<void(TArray<Gs2::Matchmaking::Model::FSeasonGatheringPtr>)> Callback,const TOptional<int64> Tier
    )
    {
        const TWeakPtr<Gs2::Core::Domain::FGs2> WeakGs2 = this->Gs2;
        const TWeakPtr<Matchmaking::Domain::FGs2MatchmakingDomain> WeakService = this->Service;
        const auto QueryNamespaceName = NamespaceName;
        const auto QueryUserId = UserId;
        const auto QuerySeasonName = SeasonName;
        const auto QuerySeason = Season;
        const auto QueryTier = Tier;
        const auto Parent = Gs2::Matchmaking::Model::Cache::FSeasonGatheringCache::CreateCacheParentKey(
        NamespaceName,
        UserId,
        SeasonName,
        Season,
        TOptional<int32>()
    );
        return Gs2->Cache->ListSubscribeTyped(
            Gs2::Matchmaking::Model::FSeasonGathering::TypeName,
            Parent,
            [Callback, WeakGs2](const TArray<FGs2ObjectPtr>& Values)
            {
                if (!WeakGs2.Pin().IsValid()) return;
                TArray<Gs2::Matchmaking::Model::FSeasonGatheringPtr> TypedValues;
                for (const auto& Value : Values) if (Value.IsValid()) TypedValues.Add(StaticCastSharedPtr<Gs2::Matchmaking::Model::FSeasonGathering>(Value));
                Callback(TypedValues);
            },
            [WeakGs2, WeakService, Callback, QueryNamespaceName, QueryUserId, QuerySeasonName, QuerySeason, QueryTier]()
            {
                const auto Owner = WeakGs2.Pin();
                if (!Owner.IsValid()) return;
                const auto Domain = MakeShared<FSeasonDomain>(Owner, WeakService.Pin(), QueryNamespaceName, QueryUserId, QuerySeasonName, QuerySeason);
                const auto Task = Gs2::Core::Util::New<FAsyncTask<FCollectMatchmakingSeasonGatheringsTask>>(Domain, Callback, QueryTier);
                Task->StartBackgroundTask();
            }
        );
    }

    void FSeasonDomain::InvalidateMatchmakingSeasonGatherings(const TOptional<int64> Tier)
    {
        Gs2->Cache->ClearListCache(
            Gs2::Matchmaking::Model::FSeasonGathering::TypeName,
            Gs2::Matchmaking::Model::Cache::FSeasonGatheringCache::CreateCacheParentKey(
        NamespaceName,
        UserId,
        SeasonName,
        Season,
        TOptional<int32>()
    )
        );
    }

    FSeasonDomain::FSubscribeMatchmakingSeasonGatheringsWithInitialCallTask::FSubscribeMatchmakingSeasonGatheringsWithInitialCallTask(const TSharedPtr<FSeasonDomain>& Self, TFunction<void(TArray<Gs2::Matchmaking::Model::FSeasonGatheringPtr>)> Callback,const TOptional<int64> Tier) : Self(Self), Callback(Callback), QueryTier(Tier) {}
    FSeasonDomain::FSubscribeMatchmakingSeasonGatheringsWithInitialCallTask::FSubscribeMatchmakingSeasonGatheringsWithInitialCallTask(const FSubscribeMatchmakingSeasonGatheringsWithInitialCallTask& From) : TGs2Future(From), Self(From.Self), Callback(From.Callback), QueryTier(From.QueryTier) {}
    Gs2::Core::Model::FGs2ErrorPtr FSeasonDomain::FSubscribeMatchmakingSeasonGatheringsWithInitialCallTask::Action(TSharedPtr<TSharedPtr<Gs2::Core::Domain::CallbackID>> Result)
    {
        const auto Task = Gs2::Core::Util::New<FAsyncTask<FCollectMatchmakingSeasonGatheringsTask>>(Self, TFunction<void(TArray<Gs2::Matchmaking::Model::FSeasonGatheringPtr>)>(), QueryTier);
        Task->StartSynchronousTask(); Task->EnsureCompletion();
        if (Task->GetTask().IsError()) return Task->GetTask().Error();
        const auto Values = Task->GetTask().Result();
        const auto CallbackId = Self->SubscribeMatchmakingSeasonGatherings(Callback, QueryTier);
        Callback(*Values); *Result = MakeShared<Gs2::Core::Domain::CallbackID>(CallbackId);
        return nullptr;
    }
    TSharedPtr<FAsyncTask<FSeasonDomain::FSubscribeMatchmakingSeasonGatheringsWithInitialCallTask>> FSeasonDomain::SubscribeMatchmakingSeasonGatheringsWithInitialCall(TFunction<void(TArray<Gs2::Matchmaking::Model::FSeasonGatheringPtr>)> Callback,const TOptional<int64> Tier)
    {
        return Gs2::Core::Util::New<FAsyncTask<FSubscribeMatchmakingSeasonGatheringsWithInitialCallTask>>(this->AsShared(), Callback, Tier);
    }

    Gs2::Matchmaking::Domain::Iterator::FDoSeasonMatchmakingByUserIdIteratorPtr FSeasonDomain::DoSeasonMatchmaking(
        const TOptional<FString> TimeOffsetToken
    ) const
    {
        return MakeShared<Gs2::Matchmaking::Domain::Iterator::FDoSeasonMatchmakingByUserIdIterator>(
            Gs2,
            Client,
            NamespaceName,
            SeasonName,
            UserId,
            TimeOffsetToken
        );
    }


    Gs2::Core::Domain::CallbackID FSeasonDomain::SubscribeDoSeasonMatchmaking(TFunction<void()> Callback){return Gs2->Cache->ListSubscribe(Gs2::Matchmaking::Model::FSeasonGathering::TypeName,Gs2::Matchmaking::Model::Cache::FSeasonGatheringCache::CreateCacheParentKey(NamespaceName,UserId,SeasonName,Season,TOptional<int32>()),Callback,Callback);}
    void FSeasonDomain::UnsubscribeDoSeasonMatchmaking(Gs2::Core::Domain::CallbackID CallbackID){Gs2->Cache->ListUnsubscribe(Gs2::Matchmaking::Model::FSeasonGathering::TypeName,Gs2::Matchmaking::Model::Cache::FSeasonGatheringCache::CreateCacheParentKey(NamespaceName,UserId,SeasonName,Season,TOptional<int32>()),CallbackID);}
    class FSeasonDomain::FCollectDoSeasonMatchmakingTask:public Gs2::Core::Util::TGs2Future<TArray<Gs2::Matchmaking::Model::FSeasonGatheringPtr>>,public TSharedFromThis<FCollectDoSeasonMatchmakingTask>{const TSharedPtr<FSeasonDomain> Self;const TFunction<void(TArray<Gs2::Matchmaking::Model::FSeasonGatheringPtr>)> OnCollected;public:FCollectDoSeasonMatchmakingTask(const TSharedPtr<FSeasonDomain>& Self,TFunction<void(TArray<Gs2::Matchmaking::Model::FSeasonGatheringPtr>)> OnCollected):Self(Self),OnCollected(OnCollected){}FCollectDoSeasonMatchmakingTask(const FCollectDoSeasonMatchmakingTask& From):TGs2Future(From),Self(From.Self),OnCollected(From.OnCollected){}Gs2::Core::Model::FGs2ErrorPtr Action(TSharedPtr<TSharedPtr<TArray<Gs2::Matchmaking::Model::FSeasonGatheringPtr>>> Result)override{TArray<Gs2::Matchmaking::Model::FSeasonGatheringPtr> Items;auto It=Self->DoSeasonMatchmaking()->begin();while(It.HasNext()){if(It.IsError())return It.Error();if(It.IsCurrentValid())Items.Add(It.Current());++It;}if(It.IsError())return It.Error();*Result=MakeShared<TArray<Gs2::Matchmaking::Model::FSeasonGatheringPtr>>(Items);if(OnCollected)OnCollected(Items);return nullptr;}};
    Gs2::Core::Domain::CallbackID FSeasonDomain::SubscribeDoSeasonMatchmaking(TFunction<void(TArray<Gs2::Matchmaking::Model::FSeasonGatheringPtr>)> Callback){const TWeakPtr<Gs2::Core::Domain::FGs2> WeakGs2=Gs2;const TWeakPtr<Matchmaking::Domain::FGs2MatchmakingDomain> WeakService=Service;const auto QN=NamespaceName;const auto QU=UserId;const auto QS=SeasonName;const auto QE=Season;const auto Parent=Gs2::Matchmaking::Model::Cache::FSeasonGatheringCache::CreateCacheParentKey(NamespaceName,UserId,SeasonName,Season,TOptional<int32>());return Gs2->Cache->ListSubscribeTyped(Gs2::Matchmaking::Model::FSeasonGathering::TypeName,Parent,[Callback,WeakGs2](const TArray<FGs2ObjectPtr>& Values){if(!WeakGs2.Pin().IsValid())return;TArray<Gs2::Matchmaking::Model::FSeasonGatheringPtr> Out;for(const auto& V:Values)if(V.IsValid())Out.Add(StaticCastSharedPtr<Gs2::Matchmaking::Model::FSeasonGathering>(V));Callback(Out);},[WeakGs2,WeakService,Callback,QN,QU,QS,QE](){auto O=WeakGs2.Pin();if(!O.IsValid())return;auto D=MakeShared<FSeasonDomain>(O,WeakService.Pin(),QN,QU,QS,QE);auto T=Gs2::Core::Util::New<FAsyncTask<FCollectDoSeasonMatchmakingTask>>(D,Callback);T->StartBackgroundTask();});}
    void FSeasonDomain::InvalidateDoSeasonMatchmaking(){Gs2->Cache->ClearListCache(Gs2::Matchmaking::Model::FSeasonGathering::TypeName,Gs2::Matchmaking::Model::Cache::FSeasonGatheringCache::CreateCacheParentKey(NamespaceName,UserId,SeasonName,Season,TOptional<int32>()));}
    FSeasonDomain::FSubscribeDoSeasonMatchmakingWithInitialCallTask::FSubscribeDoSeasonMatchmakingWithInitialCallTask(const TSharedPtr<FSeasonDomain>& Self,TFunction<void(TArray<Gs2::Matchmaking::Model::FSeasonGatheringPtr>)> Callback):Self(Self),Callback(Callback){}
    FSeasonDomain::FSubscribeDoSeasonMatchmakingWithInitialCallTask::FSubscribeDoSeasonMatchmakingWithInitialCallTask(const FSubscribeDoSeasonMatchmakingWithInitialCallTask& From):TGs2Future(From),Self(From.Self),Callback(From.Callback){}
    Gs2::Core::Model::FGs2ErrorPtr FSeasonDomain::FSubscribeDoSeasonMatchmakingWithInitialCallTask::Action(TSharedPtr<TSharedPtr<Gs2::Core::Domain::CallbackID>> Result){auto T=Gs2::Core::Util::New<FAsyncTask<FCollectDoSeasonMatchmakingTask>>(Self,TFunction<void(TArray<Gs2::Matchmaking::Model::FSeasonGatheringPtr>)>());T->StartSynchronousTask();T->EnsureCompletion();if(T->GetTask().IsError())return T->GetTask().Error();auto V=T->GetTask().Result();auto ID=Self->SubscribeDoSeasonMatchmaking(Callback);Callback(*V);*Result=MakeShared<Gs2::Core::Domain::CallbackID>(ID);return nullptr;}
    TSharedPtr<FAsyncTask<FSeasonDomain::FSubscribeDoSeasonMatchmakingWithInitialCallTask>> FSeasonDomain::SubscribeDoSeasonMatchmakingWithInitialCall(TFunction<void(TArray<Gs2::Matchmaking::Model::FSeasonGatheringPtr>)> Callback){return Gs2::Core::Util::New<FAsyncTask<FSubscribeDoSeasonMatchmakingWithInitialCallTask>>(this->AsShared(),Callback);}

    TSharedPtr<Gs2::Matchmaking::Domain::Model::FSeasonGatheringDomain> FSeasonDomain::SeasonGathering(
        const int64 Tier,
        const FString SeasonGatheringName
    )
    {
        return MakeShared<Gs2::Matchmaking::Domain::Model::FSeasonGatheringDomain>(
            Gs2,
            Service,
            NamespaceName,
            UserId,
            SeasonName,
            Season,
            Tier,
            SeasonGatheringName == TEXT("") ? TOptional<FString>() : TOptional<FString>(SeasonGatheringName)
        );
    }

    Gs2::Matchmaking::Domain::Iterator::FDescribeJoinedSeasonGatheringsByUserIdIteratorPtr FSeasonDomain::JoinedSeasonGatherings(
        const TOptional<FString> TimeOffsetToken
    ) const
    {
        return MakeShared<Gs2::Matchmaking::Domain::Iterator::FDescribeJoinedSeasonGatheringsByUserIdIterator>(
            Gs2,
            Client,
            NamespaceName,
            UserId,
            SeasonName,
            TimeOffsetToken
        );
    }

    Gs2::Core::Domain::CallbackID FSeasonDomain::SubscribeJoinedSeasonGatherings(
    TFunction<void()> Callback
    )
    {
        return Gs2->Cache->ListSubscribe(
            Gs2::Matchmaking::Model::FJoinedSeasonGathering::TypeName,
            Gs2::Matchmaking::Model::Cache::FJoinedSeasonGatheringCache::CreateCacheParentKey(
                NamespaceName,
                UserId,
                SeasonName,
                Season,
                TOptional<int32>()
            ),
            Callback,
            Callback
        );
    }
    void FSeasonDomain::UnsubscribeJoinedSeasonGatherings(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        Gs2->Cache->ListUnsubscribe(
            Gs2::Matchmaking::Model::FJoinedSeasonGathering::TypeName,
            Gs2::Matchmaking::Model::Cache::FJoinedSeasonGatheringCache::CreateCacheParentKey(
                NamespaceName,
                UserId,
                SeasonName,
                Season,
                TOptional<int32>()
            ),
            CallbackID
        );
    }
    class FSeasonDomain::FCollectJoinedSeasonGatheringsTask : public Gs2::Core::Util::TGs2Future<TArray<Gs2::Matchmaking::Model::FJoinedSeasonGatheringPtr>>, public TSharedFromThis<FCollectJoinedSeasonGatheringsTask>
    {
        const TSharedPtr<FSeasonDomain> Self;
        const TFunction<void(TArray<Gs2::Matchmaking::Model::FJoinedSeasonGatheringPtr>)> OnCollected;
    const TOptional<FString> QueryTimeOffsetToken;
    public:
        explicit FCollectJoinedSeasonGatheringsTask(const TSharedPtr<FSeasonDomain>& Self, TFunction<void(TArray<Gs2::Matchmaking::Model::FJoinedSeasonGatheringPtr>)> OnCollected,const TOptional<FString> TimeOffsetToken) : Self(Self), OnCollected(OnCollected), QueryTimeOffsetToken(TimeOffsetToken) {}
        FCollectJoinedSeasonGatheringsTask(const FCollectJoinedSeasonGatheringsTask& From) : TGs2Future(From), Self(From.Self), OnCollected(From.OnCollected), QueryTimeOffsetToken(From.QueryTimeOffsetToken) {}
        virtual Gs2::Core::Model::FGs2ErrorPtr Action(TSharedPtr<TSharedPtr<TArray<Gs2::Matchmaking::Model::FJoinedSeasonGatheringPtr>>> Result) override
        {
            TArray<Gs2::Matchmaking::Model::FJoinedSeasonGatheringPtr> Items;
            auto Iterator = Self->JoinedSeasonGatherings(QueryTimeOffsetToken)->begin();
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

    Gs2::Core::Domain::CallbackID FSeasonDomain::SubscribeJoinedSeasonGatherings(
        TFunction<void(TArray<Gs2::Matchmaking::Model::FJoinedSeasonGatheringPtr>)> Callback,const TOptional<FString> TimeOffsetToken
    )
    {
        const TWeakPtr<Gs2::Core::Domain::FGs2> WeakGs2 = this->Gs2;
        const TWeakPtr<Matchmaking::Domain::FGs2MatchmakingDomain> WeakService = this->Service;
        const auto QueryNamespaceName = NamespaceName;
        const auto QueryUserId = UserId;
        const auto QuerySeasonName = SeasonName;
        const auto QuerySeason = Season;
        const auto QueryTimeOffsetToken = TimeOffsetToken;
        const auto Parent = Gs2::Matchmaking::Model::Cache::FJoinedSeasonGatheringCache::CreateCacheParentKey(
        NamespaceName,
        UserId,
        SeasonName,
        Season,
        TOptional<int32>()
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
            [WeakGs2, WeakService, Callback, QueryNamespaceName, QueryUserId, QuerySeasonName, QuerySeason, QueryTimeOffsetToken]()
            {
                const auto Owner = WeakGs2.Pin();
                if (!Owner.IsValid()) return;
                const auto Domain = MakeShared<FSeasonDomain>(Owner, WeakService.Pin(), QueryNamespaceName, QueryUserId, QuerySeasonName, QuerySeason);
                const auto Task = Gs2::Core::Util::New<FAsyncTask<FCollectJoinedSeasonGatheringsTask>>(Domain, Callback, QueryTimeOffsetToken);
                Task->StartBackgroundTask();
            }
        );
    }

    void FSeasonDomain::InvalidateJoinedSeasonGatherings(const TOptional<FString> TimeOffsetToken)
    {
        Gs2->Cache->ClearListCache(
            Gs2::Matchmaking::Model::FJoinedSeasonGathering::TypeName,
            Gs2::Matchmaking::Model::Cache::FJoinedSeasonGatheringCache::CreateCacheParentKey(
        NamespaceName,
        UserId,
        SeasonName,
        Season,
        TOptional<int32>()
    )
        );
    }

    FSeasonDomain::FSubscribeJoinedSeasonGatheringsWithInitialCallTask::FSubscribeJoinedSeasonGatheringsWithInitialCallTask(const TSharedPtr<FSeasonDomain>& Self, TFunction<void(TArray<Gs2::Matchmaking::Model::FJoinedSeasonGatheringPtr>)> Callback,const TOptional<FString> TimeOffsetToken) : Self(Self), Callback(Callback), QueryTimeOffsetToken(TimeOffsetToken) {}
    FSeasonDomain::FSubscribeJoinedSeasonGatheringsWithInitialCallTask::FSubscribeJoinedSeasonGatheringsWithInitialCallTask(const FSubscribeJoinedSeasonGatheringsWithInitialCallTask& From) : TGs2Future(From), Self(From.Self), Callback(From.Callback), QueryTimeOffsetToken(From.QueryTimeOffsetToken) {}
    Gs2::Core::Model::FGs2ErrorPtr FSeasonDomain::FSubscribeJoinedSeasonGatheringsWithInitialCallTask::Action(TSharedPtr<TSharedPtr<Gs2::Core::Domain::CallbackID>> Result)
    {
        const auto Task = Gs2::Core::Util::New<FAsyncTask<FCollectJoinedSeasonGatheringsTask>>(Self, TFunction<void(TArray<Gs2::Matchmaking::Model::FJoinedSeasonGatheringPtr>)>(), QueryTimeOffsetToken);
        Task->StartSynchronousTask(); Task->EnsureCompletion();
        if (Task->GetTask().IsError()) return Task->GetTask().Error();
        const auto Values = Task->GetTask().Result();
        const auto CallbackId = Self->SubscribeJoinedSeasonGatherings(Callback, QueryTimeOffsetToken);
        Callback(*Values); *Result = MakeShared<Gs2::Core::Domain::CallbackID>(CallbackId);
        return nullptr;
    }
    TSharedPtr<FAsyncTask<FSeasonDomain::FSubscribeJoinedSeasonGatheringsWithInitialCallTask>> FSeasonDomain::SubscribeJoinedSeasonGatheringsWithInitialCall(TFunction<void(TArray<Gs2::Matchmaking::Model::FJoinedSeasonGatheringPtr>)> Callback,const TOptional<FString> TimeOffsetToken)
    {
        return Gs2::Core::Util::New<FAsyncTask<FSubscribeJoinedSeasonGatheringsWithInitialCallTask>>(this->AsShared(), Callback, TimeOffsetToken);
    }

    TSharedPtr<Gs2::Matchmaking::Domain::Model::FJoinedSeasonGatheringDomain> FSeasonDomain::JoinedSeasonGathering(
    )
    {
        return MakeShared<Gs2::Matchmaking::Domain::Model::FJoinedSeasonGatheringDomain>(
            Gs2,
            Service,
            NamespaceName,
            UserId,
            SeasonName,
            Season
        );
    }

    FString FSeasonDomain::CreateCacheParentKey(
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
            (Season.IsSet() ? FString::Printf(TEXT("%lld"), *Season) : "null") + ":" +
            ChildType;
    }

    FString FSeasonDomain::CreateCacheKey(
        TOptional<FString> SeasonName,
        TOptional<FString> Season
    )
    {
        return FString("") +
            (SeasonName.IsSet() ? *SeasonName : "null") + ":" + 
            (Season.IsSet() ? *Season : "null");
    }
}

#if defined(_MSC_VER)
#pragma warning (pop)
#elif defined(__clang__)
#pragma clang diagnostic pop
#endif
