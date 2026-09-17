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
#include "Matchmaking/Model/Cache/Ballot.h"
#include "Matchmaking/Model/Cache/SeasonGathering.h"
#include "Matchmaking/Model/Cache/JoinedSeasonGathering.h"

#include "Core/Domain/Gs2.h"
#include "Core/Domain/Transaction/JobQueueJobDomainFactory.h"
#include "Core/Domain/Transaction/InternalTransactionDomainFactory.h"
#include "Core/Domain/Transaction/ManualTransactionDomain.h"

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
            ->WithContextStack((!Request->GetContextStack().IsSet() || Request->GetContextStack()->IsEmpty()) ? Self->Gs2->DefaultContextStack : Request->GetContextStack())
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
        const auto ResultModel = Future->GetTask().Result();
        Future->EnsureCompletion();

            if (ResultModel.IsValid() && ResultModel->GetItem() != nullptr)
            {


        Gs2::Matchmaking::Model::Cache::FGatheringCache::Put(
            Self->Gs2->Cache,

            Request->GetNamespaceName(),
            Request->GetUserId(),
            ResultModel->GetItem()->GetName(),
            TOptional<int32>(),
            ResultModel->GetItem()
        );
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
            ->WithContextStack((!Request->GetContextStack().IsSet() || Request->GetContextStack()->IsEmpty()) ? Self->Gs2->DefaultContextStack : Request->GetContextStack())
            ->WithNamespaceName(Self->NamespaceName);
        const auto Future = Self->Client->DeleteGathering(
            Request
        );
        Future->StartSynchronousTask();
        if (Future->GetTask().IsError())
        {
            return Future->GetTask().Error();
        }
        const auto ResultModel = Future->GetTask().Result();
        Future->EnsureCompletion();


              Gs2::Matchmaking::Model::Cache::FGatheringCache::Delete(
            Self->Gs2->Cache,

            Request->GetNamespaceName(),
            Self->UserId,
            Request->GetGatheringName(),
            TOptional<int32>()
        );
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
            ->WithContextStack((!Request->GetContextStack().IsSet() || Request->GetContextStack()->IsEmpty()) ? Self->Gs2->DefaultContextStack : Request->GetContextStack())
            ->WithNamespaceName(Self->NamespaceName);
        const auto Future = Self->Client->PutResult(
            Request
        );
        Future->StartSynchronousTask();
        if (Future->GetTask().IsError())
        {
            return Future->GetTask().Error();
        }
        const auto ResultModel = Future->GetTask().Result();
        Future->EnsureCompletion();
        if (ResultModel.IsValid() && ResultModel->GetItems().IsValid())
        {
            for (const auto& Item : *ResultModel->GetItems())
            {
                if (!Item.IsValid()) continue;
                Gs2::Matchmaking::Model::Cache::FRatingCache::Put(
                    Self->Gs2->Cache,
                    Request->GetNamespaceName(), Item->GetUserId(), Item->GetName(),
                    TOptional<int32>(), Item
                );
            }
        }

        auto Domain = MakeShared<TArray<TSharedPtr<Gs2::Matchmaking::Domain::Model::FRatingDomain>>>();
        if (ResultModel.IsValid() && ResultModel->GetItems().IsValid())
        {
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
            Gs2,
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
            Gs2::Matchmaking::Model::Cache::FGatheringCache::CreateCacheParentKey(
                NamespaceName,
                TOptional<FString>(),
                TOptional<int32>()
            ),
            Callback,
            Callback
        );
    }
    void FUserDomain::UnsubscribeGatherings(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        Gs2->Cache->ListUnsubscribe(
            Gs2::Matchmaking::Model::FGathering::TypeName,
            Gs2::Matchmaking::Model::Cache::FGatheringCache::CreateCacheParentKey(
                NamespaceName,
                TOptional<FString>(),
                TOptional<int32>()
            ),
            CallbackID
        );
    }
    class FUserDomain::FCollectGatheringsTask : public Gs2::Core::Util::TGs2Future<TArray<Gs2::Matchmaking::Model::FGatheringPtr>>, public TSharedFromThis<FCollectGatheringsTask>
    {
        const TSharedPtr<FUserDomain> Self;
        const TFunction<void(TArray<Gs2::Matchmaking::Model::FGatheringPtr>)> OnCollected;

    public:
        explicit FCollectGatheringsTask(const TSharedPtr<FUserDomain>& Self, TFunction<void(TArray<Gs2::Matchmaking::Model::FGatheringPtr>)> OnCollected) : Self(Self), OnCollected(OnCollected) {}
        FCollectGatheringsTask(const FCollectGatheringsTask& From) : TGs2Future(From), Self(From.Self), OnCollected(From.OnCollected) {}
        virtual Gs2::Core::Model::FGs2ErrorPtr Action(TSharedPtr<TSharedPtr<TArray<Gs2::Matchmaking::Model::FGatheringPtr>>> Result) override
        {
            TArray<Gs2::Matchmaking::Model::FGatheringPtr> Items;
            auto Iterator = Self->Gatherings()->begin();
            while (Iterator.HasNext())
            {
                if (Iterator.IsError()) return Iterator.Error();
                if (Iterator.IsCurrentValid()) Items.Add(Iterator.Current());
                ++Iterator;
            }
            if (Iterator.IsError()) return Iterator.Error();
            *Result = MakeShared<TArray<Gs2::Matchmaking::Model::FGatheringPtr>>(Items);
            if (OnCollected) OnCollected(Items);
            return nullptr;
        }
    };

    Gs2::Core::Domain::CallbackID FUserDomain::SubscribeGatherings(
        TFunction<void(TArray<Gs2::Matchmaking::Model::FGatheringPtr>)> Callback
    )
    {
        const TWeakPtr<Gs2::Core::Domain::FGs2> WeakGs2 = this->Gs2;
        const TWeakPtr<Matchmaking::Domain::FGs2MatchmakingDomain> WeakService = this->Service;
        const auto QueryNamespaceName = NamespaceName;
        const auto QueryUserId = UserId;
        const auto Parent = Gs2::Matchmaking::Model::Cache::FGatheringCache::CreateCacheParentKey(
        NamespaceName,
        TOptional<FString>(),
        TOptional<int32>()
    );
        return Gs2->Cache->ListSubscribeTyped(
            Gs2::Matchmaking::Model::FGathering::TypeName,
            Parent,
            [Callback, WeakGs2](const TArray<FGs2ObjectPtr>& Values)
            {
                if (!WeakGs2.Pin().IsValid()) return;
                TArray<Gs2::Matchmaking::Model::FGatheringPtr> TypedValues;
                for (const auto& Value : Values) if (Value.IsValid()) TypedValues.Add(StaticCastSharedPtr<Gs2::Matchmaking::Model::FGathering>(Value));
                Callback(TypedValues);
            },
            [WeakGs2, WeakService, Callback, QueryNamespaceName, QueryUserId]()
            {
                const auto Owner = WeakGs2.Pin();
                if (!Owner.IsValid()) return;
                const auto Domain = MakeShared<FUserDomain>(Owner, WeakService.Pin(), QueryNamespaceName, QueryUserId);
                const auto Task = Gs2::Core::Util::New<FAsyncTask<FCollectGatheringsTask>>(Domain, Callback);
                Task->StartBackgroundTask();
            }
        );
    }

    void FUserDomain::InvalidateGatherings()
    {
        Gs2->Cache->ClearListCache(
            Gs2::Matchmaking::Model::FGathering::TypeName,
            Gs2::Matchmaking::Model::Cache::FGatheringCache::CreateCacheParentKey(
        NamespaceName,
        TOptional<FString>(),
        TOptional<int32>()
    )
        );
    }

    FUserDomain::FSubscribeGatheringsWithInitialCallTask::FSubscribeGatheringsWithInitialCallTask(const TSharedPtr<FUserDomain>& Self, TFunction<void(TArray<Gs2::Matchmaking::Model::FGatheringPtr>)> Callback) : Self(Self), Callback(Callback) {}
    FUserDomain::FSubscribeGatheringsWithInitialCallTask::FSubscribeGatheringsWithInitialCallTask(const FSubscribeGatheringsWithInitialCallTask& From) : TGs2Future(From), Self(From.Self), Callback(From.Callback) {}
    Gs2::Core::Model::FGs2ErrorPtr FUserDomain::FSubscribeGatheringsWithInitialCallTask::Action(TSharedPtr<TSharedPtr<Gs2::Core::Domain::CallbackID>> Result)
    {
        const auto Task = Gs2::Core::Util::New<FAsyncTask<FCollectGatheringsTask>>(Self, TFunction<void(TArray<Gs2::Matchmaking::Model::FGatheringPtr>)>());
        Task->StartSynchronousTask(); Task->EnsureCompletion();
        if (Task->GetTask().IsError()) return Task->GetTask().Error();
        const auto Values = Task->GetTask().Result();
        const auto CallbackId = Self->SubscribeGatherings(Callback);
        Callback(*Values); *Result = MakeShared<Gs2::Core::Domain::CallbackID>(CallbackId);
        return nullptr;
    }
    TSharedPtr<FAsyncTask<FUserDomain::FSubscribeGatheringsWithInitialCallTask>> FUserDomain::SubscribeGatheringsWithInitialCall(TFunction<void(TArray<Gs2::Matchmaking::Model::FGatheringPtr>)> Callback)
    {
        return Gs2::Core::Util::New<FAsyncTask<FSubscribeGatheringsWithInitialCallTask>>(this->AsShared(), Callback);
    }

    Gs2::Matchmaking::Domain::Iterator::FDoMatchmakingByPlayerIteratorPtr FUserDomain::DoMatchmakingByPlayer(
        const TSharedPtr<Gs2::Matchmaking::Model::FPlayer> Player
    ) const
    {
        return MakeShared<Gs2::Matchmaking::Domain::Iterator::FDoMatchmakingByPlayerIterator>(
            Gs2,
            Client,
            NamespaceName,
            Player
        );
    }

    Gs2::Matchmaking::Domain::Iterator::FDoMatchmakingByUserIdIteratorPtr FUserDomain::DoMatchmaking(
        const TSharedPtr<Gs2::Matchmaking::Model::FPlayer> Player,
        const TOptional<FString> TimeOffsetToken
    ) const
    {
        return MakeShared<Gs2::Matchmaking::Domain::Iterator::FDoMatchmakingByUserIdIterator>(
            Gs2,
            Client,
            NamespaceName,
            UserId,
            Player,
            TimeOffsetToken
        );
    }


    Gs2::Core::Domain::CallbackID FUserDomain::SubscribeDoMatchmakingByPlayer(TFunction<void()> Callback,const TSharedPtr<Gs2::Matchmaking::Model::FPlayer> Player){return Gs2->Cache->ListSubscribe(Gs2::Matchmaking::Model::FGathering::TypeName,Gs2::Matchmaking::Model::Cache::FGatheringCache::CreateCacheParentKey(NamespaceName,UserId,TOptional<int32>()),Callback,Callback);}
    void FUserDomain::UnsubscribeDoMatchmakingByPlayer(Gs2::Core::Domain::CallbackID CallbackID,const TSharedPtr<Gs2::Matchmaking::Model::FPlayer> Player){Gs2->Cache->ListUnsubscribe(Gs2::Matchmaking::Model::FGathering::TypeName,Gs2::Matchmaking::Model::Cache::FGatheringCache::CreateCacheParentKey(NamespaceName,UserId,TOptional<int32>()),CallbackID);}
    class FUserDomain::FCollectDoMatchmakingByPlayerTask:public Gs2::Core::Util::TGs2Future<TArray<Gs2::Matchmaking::Model::FGatheringPtr>>,public TSharedFromThis<FCollectDoMatchmakingByPlayerTask>{const TSharedPtr<FUserDomain> Self;const TFunction<void(TArray<Gs2::Matchmaking::Model::FGatheringPtr>)> OnCollected;const TSharedPtr<Gs2::Matchmaking::Model::FPlayer> QueryPlayer;public:FCollectDoMatchmakingByPlayerTask(const TSharedPtr<FUserDomain>& Self,TFunction<void(TArray<Gs2::Matchmaking::Model::FGatheringPtr>)> OnCollected,const TSharedPtr<Gs2::Matchmaking::Model::FPlayer> Player):Self(Self),OnCollected(OnCollected),QueryPlayer(Player){}FCollectDoMatchmakingByPlayerTask(const FCollectDoMatchmakingByPlayerTask& From):TGs2Future(From),Self(From.Self),OnCollected(From.OnCollected),QueryPlayer(From.QueryPlayer){}Gs2::Core::Model::FGs2ErrorPtr Action(TSharedPtr<TSharedPtr<TArray<Gs2::Matchmaking::Model::FGatheringPtr>>> Result)override{TArray<Gs2::Matchmaking::Model::FGatheringPtr> Items;auto It=Self->DoMatchmakingByPlayer(QueryPlayer)->begin();while(It.HasNext()){if(It.IsError())return It.Error();if(It.IsCurrentValid())Items.Add(It.Current());++It;}if(It.IsError())return It.Error();*Result=MakeShared<TArray<Gs2::Matchmaking::Model::FGatheringPtr>>(Items);if(OnCollected)OnCollected(Items);return nullptr;}};
    Gs2::Core::Domain::CallbackID FUserDomain::SubscribeDoMatchmakingByPlayer(TFunction<void(TArray<Gs2::Matchmaking::Model::FGatheringPtr>)> Callback,const TSharedPtr<Gs2::Matchmaking::Model::FPlayer> Player){const TWeakPtr<Gs2::Core::Domain::FGs2> WeakGs2=Gs2;const TWeakPtr<Matchmaking::Domain::FGs2MatchmakingDomain> WeakService=Service;const auto QN=NamespaceName;const auto QU=UserId;const auto QP=Player;const auto Parent=Gs2::Matchmaking::Model::Cache::FGatheringCache::CreateCacheParentKey(NamespaceName,UserId,TOptional<int32>());return Gs2->Cache->ListSubscribeTyped(Gs2::Matchmaking::Model::FGathering::TypeName,Parent,[Callback,WeakGs2](const TArray<FGs2ObjectPtr>& Values){if(!WeakGs2.Pin().IsValid())return;TArray<Gs2::Matchmaking::Model::FGatheringPtr> Out;for(const auto& V:Values)if(V.IsValid())Out.Add(StaticCastSharedPtr<Gs2::Matchmaking::Model::FGathering>(V));Callback(Out);},[WeakGs2,WeakService,Callback,QN,QU,QP](){auto O=WeakGs2.Pin();if(!O.IsValid())return;auto D=MakeShared<FUserDomain>(O,WeakService.Pin(),QN,QU);auto T=Gs2::Core::Util::New<FAsyncTask<FCollectDoMatchmakingByPlayerTask>>(D,Callback,QP);T->StartBackgroundTask();});}
    void FUserDomain::InvalidateDoMatchmakingByPlayer(const TSharedPtr<Gs2::Matchmaking::Model::FPlayer> Player){Gs2->Cache->ClearListCache(Gs2::Matchmaking::Model::FGathering::TypeName,Gs2::Matchmaking::Model::Cache::FGatheringCache::CreateCacheParentKey(NamespaceName,UserId,TOptional<int32>()));}
    FUserDomain::FSubscribeDoMatchmakingByPlayerWithInitialCallTask::FSubscribeDoMatchmakingByPlayerWithInitialCallTask(const TSharedPtr<FUserDomain>& Self,TFunction<void(TArray<Gs2::Matchmaking::Model::FGatheringPtr>)> Callback,const TSharedPtr<Gs2::Matchmaking::Model::FPlayer> Player):Self(Self),Callback(Callback),QueryPlayer(Player){}
    FUserDomain::FSubscribeDoMatchmakingByPlayerWithInitialCallTask::FSubscribeDoMatchmakingByPlayerWithInitialCallTask(const FSubscribeDoMatchmakingByPlayerWithInitialCallTask& From):TGs2Future(From),Self(From.Self),Callback(From.Callback),QueryPlayer(From.QueryPlayer){}
    Gs2::Core::Model::FGs2ErrorPtr FUserDomain::FSubscribeDoMatchmakingByPlayerWithInitialCallTask::Action(TSharedPtr<TSharedPtr<Gs2::Core::Domain::CallbackID>> Result){auto T=Gs2::Core::Util::New<FAsyncTask<FCollectDoMatchmakingByPlayerTask>>(Self,TFunction<void(TArray<Gs2::Matchmaking::Model::FGatheringPtr>)>(),QueryPlayer);T->StartSynchronousTask();T->EnsureCompletion();if(T->GetTask().IsError())return T->GetTask().Error();auto V=T->GetTask().Result();auto ID=Self->SubscribeDoMatchmakingByPlayer(Callback,QueryPlayer);Callback(*V);*Result=MakeShared<Gs2::Core::Domain::CallbackID>(ID);return nullptr;}
    TSharedPtr<FAsyncTask<FUserDomain::FSubscribeDoMatchmakingByPlayerWithInitialCallTask>> FUserDomain::SubscribeDoMatchmakingByPlayerWithInitialCall(TFunction<void(TArray<Gs2::Matchmaking::Model::FGatheringPtr>)> Callback,const TSharedPtr<Gs2::Matchmaking::Model::FPlayer> Player){return Gs2::Core::Util::New<FAsyncTask<FSubscribeDoMatchmakingByPlayerWithInitialCallTask>>(this->AsShared(),Callback,Player);}

    Gs2::Core::Domain::CallbackID FUserDomain::SubscribeDoMatchmaking(TFunction<void()> Callback,const TSharedPtr<Gs2::Matchmaking::Model::FPlayer> Player){return Gs2->Cache->ListSubscribe(Gs2::Matchmaking::Model::FGathering::TypeName,Gs2::Matchmaking::Model::Cache::FGatheringCache::CreateCacheParentKey(NamespaceName,UserId,TOptional<int32>()),Callback,Callback);}
    void FUserDomain::UnsubscribeDoMatchmaking(Gs2::Core::Domain::CallbackID CallbackID,const TSharedPtr<Gs2::Matchmaking::Model::FPlayer> Player){Gs2->Cache->ListUnsubscribe(Gs2::Matchmaking::Model::FGathering::TypeName,Gs2::Matchmaking::Model::Cache::FGatheringCache::CreateCacheParentKey(NamespaceName,UserId,TOptional<int32>()),CallbackID);}
    class FUserDomain::FCollectDoMatchmakingTask:public Gs2::Core::Util::TGs2Future<TArray<Gs2::Matchmaking::Model::FGatheringPtr>>,public TSharedFromThis<FCollectDoMatchmakingTask>{const TSharedPtr<FUserDomain> Self;const TFunction<void(TArray<Gs2::Matchmaking::Model::FGatheringPtr>)> OnCollected;const TSharedPtr<Gs2::Matchmaking::Model::FPlayer> QueryPlayer;public:FCollectDoMatchmakingTask(const TSharedPtr<FUserDomain>& Self,TFunction<void(TArray<Gs2::Matchmaking::Model::FGatheringPtr>)> OnCollected,const TSharedPtr<Gs2::Matchmaking::Model::FPlayer> Player):Self(Self),OnCollected(OnCollected),QueryPlayer(Player){}FCollectDoMatchmakingTask(const FCollectDoMatchmakingTask& From):TGs2Future(From),Self(From.Self),OnCollected(From.OnCollected),QueryPlayer(From.QueryPlayer){}Gs2::Core::Model::FGs2ErrorPtr Action(TSharedPtr<TSharedPtr<TArray<Gs2::Matchmaking::Model::FGatheringPtr>>> Result)override{TArray<Gs2::Matchmaking::Model::FGatheringPtr> Items;auto It=Self->DoMatchmaking(QueryPlayer)->begin();while(It.HasNext()){if(It.IsError())return It.Error();if(It.IsCurrentValid())Items.Add(It.Current());++It;}if(It.IsError())return It.Error();*Result=MakeShared<TArray<Gs2::Matchmaking::Model::FGatheringPtr>>(Items);if(OnCollected)OnCollected(Items);return nullptr;}};
    Gs2::Core::Domain::CallbackID FUserDomain::SubscribeDoMatchmaking(TFunction<void(TArray<Gs2::Matchmaking::Model::FGatheringPtr>)> Callback,const TSharedPtr<Gs2::Matchmaking::Model::FPlayer> Player){const TWeakPtr<Gs2::Core::Domain::FGs2> WeakGs2=Gs2;const TWeakPtr<Matchmaking::Domain::FGs2MatchmakingDomain> WeakService=Service;const auto QN=NamespaceName;const auto QU=UserId;const auto QP=Player;const auto Parent=Gs2::Matchmaking::Model::Cache::FGatheringCache::CreateCacheParentKey(NamespaceName,UserId,TOptional<int32>());return Gs2->Cache->ListSubscribeTyped(Gs2::Matchmaking::Model::FGathering::TypeName,Parent,[Callback,WeakGs2](const TArray<FGs2ObjectPtr>& Values){if(!WeakGs2.Pin().IsValid())return;TArray<Gs2::Matchmaking::Model::FGatheringPtr> Out;for(const auto& V:Values)if(V.IsValid())Out.Add(StaticCastSharedPtr<Gs2::Matchmaking::Model::FGathering>(V));Callback(Out);},[WeakGs2,WeakService,Callback,QN,QU,QP](){auto O=WeakGs2.Pin();if(!O.IsValid())return;auto D=MakeShared<FUserDomain>(O,WeakService.Pin(),QN,QU);auto T=Gs2::Core::Util::New<FAsyncTask<FCollectDoMatchmakingTask>>(D,Callback,QP);T->StartBackgroundTask();});}
    void FUserDomain::InvalidateDoMatchmaking(const TSharedPtr<Gs2::Matchmaking::Model::FPlayer> Player){Gs2->Cache->ClearListCache(Gs2::Matchmaking::Model::FGathering::TypeName,Gs2::Matchmaking::Model::Cache::FGatheringCache::CreateCacheParentKey(NamespaceName,UserId,TOptional<int32>()));}
    FUserDomain::FSubscribeDoMatchmakingWithInitialCallTask::FSubscribeDoMatchmakingWithInitialCallTask(const TSharedPtr<FUserDomain>& Self,TFunction<void(TArray<Gs2::Matchmaking::Model::FGatheringPtr>)> Callback,const TSharedPtr<Gs2::Matchmaking::Model::FPlayer> Player):Self(Self),Callback(Callback),QueryPlayer(Player){}
    FUserDomain::FSubscribeDoMatchmakingWithInitialCallTask::FSubscribeDoMatchmakingWithInitialCallTask(const FSubscribeDoMatchmakingWithInitialCallTask& From):TGs2Future(From),Self(From.Self),Callback(From.Callback),QueryPlayer(From.QueryPlayer){}
    Gs2::Core::Model::FGs2ErrorPtr FUserDomain::FSubscribeDoMatchmakingWithInitialCallTask::Action(TSharedPtr<TSharedPtr<Gs2::Core::Domain::CallbackID>> Result){auto T=Gs2::Core::Util::New<FAsyncTask<FCollectDoMatchmakingTask>>(Self,TFunction<void(TArray<Gs2::Matchmaking::Model::FGatheringPtr>)>(),QueryPlayer);T->StartSynchronousTask();T->EnsureCompletion();if(T->GetTask().IsError())return T->GetTask().Error();auto V=T->GetTask().Result();auto ID=Self->SubscribeDoMatchmaking(Callback,QueryPlayer);Callback(*V);*Result=MakeShared<Gs2::Core::Domain::CallbackID>(ID);return nullptr;}
    TSharedPtr<FAsyncTask<FUserDomain::FSubscribeDoMatchmakingWithInitialCallTask>> FUserDomain::SubscribeDoMatchmakingWithInitialCall(TFunction<void(TArray<Gs2::Matchmaking::Model::FGatheringPtr>)> Callback,const TSharedPtr<Gs2::Matchmaking::Model::FPlayer> Player){return Gs2::Core::Util::New<FAsyncTask<FSubscribeDoMatchmakingWithInitialCallTask>>(this->AsShared(),Callback,Player);}

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

    Gs2::Matchmaking::Domain::Iterator::FDescribeRatingsByUserIdIteratorPtr FUserDomain::Ratings(
        const TOptional<FString> TimeOffsetToken
    ) const
    {
        return MakeShared<Gs2::Matchmaking::Domain::Iterator::FDescribeRatingsByUserIdIterator>(
            Gs2,
            Client,
            NamespaceName,
            UserId,
            TimeOffsetToken
        );
    }

    Gs2::Core::Domain::CallbackID FUserDomain::SubscribeRatings(
    TFunction<void()> Callback

    )
    {
        return Gs2->Cache->ListSubscribe(
            Gs2::Matchmaking::Model::FRating::TypeName,
            Gs2::Matchmaking::Model::Cache::FRatingCache::CreateCacheParentKey(
                NamespaceName,
                UserId,
                TOptional<int32>()
            ),
            Callback,
            Callback
        );
    }
    void FUserDomain::UnsubscribeRatings(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        Gs2->Cache->ListUnsubscribe(
            Gs2::Matchmaking::Model::FRating::TypeName,
            Gs2::Matchmaking::Model::Cache::FRatingCache::CreateCacheParentKey(
                NamespaceName,
                UserId,
                TOptional<int32>()
            ),
            CallbackID
        );
    }
    class FUserDomain::FCollectRatingsTask : public Gs2::Core::Util::TGs2Future<TArray<Gs2::Matchmaking::Model::FRatingPtr>>, public TSharedFromThis<FCollectRatingsTask>
    {
        const TSharedPtr<FUserDomain> Self;
        const TFunction<void(TArray<Gs2::Matchmaking::Model::FRatingPtr>)> OnCollected;
    const TOptional<FString> QueryTimeOffsetToken;
    public:
        explicit FCollectRatingsTask(const TSharedPtr<FUserDomain>& Self, TFunction<void(TArray<Gs2::Matchmaking::Model::FRatingPtr>)> OnCollected,const TOptional<FString> TimeOffsetToken) : Self(Self), OnCollected(OnCollected), QueryTimeOffsetToken(TimeOffsetToken) {}
        FCollectRatingsTask(const FCollectRatingsTask& From) : TGs2Future(From), Self(From.Self), OnCollected(From.OnCollected), QueryTimeOffsetToken(From.QueryTimeOffsetToken) {}
        virtual Gs2::Core::Model::FGs2ErrorPtr Action(TSharedPtr<TSharedPtr<TArray<Gs2::Matchmaking::Model::FRatingPtr>>> Result) override
        {
            TArray<Gs2::Matchmaking::Model::FRatingPtr> Items;
            auto Iterator = Self->Ratings(QueryTimeOffsetToken)->begin();
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

    Gs2::Core::Domain::CallbackID FUserDomain::SubscribeRatings(
        TFunction<void(TArray<Gs2::Matchmaking::Model::FRatingPtr>)> Callback,const TOptional<FString> TimeOffsetToken
    )
    {
        const TWeakPtr<Gs2::Core::Domain::FGs2> WeakGs2 = this->Gs2;
        const TWeakPtr<Matchmaking::Domain::FGs2MatchmakingDomain> WeakService = this->Service;
        const auto QueryNamespaceName = NamespaceName;
        const auto QueryUserId = UserId;
        const auto QueryTimeOffsetToken = TimeOffsetToken;
        const auto Parent = Gs2::Matchmaking::Model::Cache::FRatingCache::CreateCacheParentKey(
        NamespaceName,
        UserId,
        TOptional<int32>()
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
            [WeakGs2, WeakService, Callback, QueryNamespaceName, QueryUserId, QueryTimeOffsetToken]()
            {
                const auto Owner = WeakGs2.Pin();
                if (!Owner.IsValid()) return;
                const auto Domain = MakeShared<FUserDomain>(Owner, WeakService.Pin(), QueryNamespaceName, QueryUserId);
                const auto Task = Gs2::Core::Util::New<FAsyncTask<FCollectRatingsTask>>(Domain, Callback, QueryTimeOffsetToken);
                Task->StartBackgroundTask();
            }
        );
    }

    void FUserDomain::InvalidateRatings(const TOptional<FString> TimeOffsetToken)
    {
        Gs2->Cache->ClearListCache(
            Gs2::Matchmaking::Model::FRating::TypeName,
            Gs2::Matchmaking::Model::Cache::FRatingCache::CreateCacheParentKey(
        NamespaceName,
        UserId,
        TOptional<int32>()
    )
        );
    }

    FUserDomain::FSubscribeRatingsWithInitialCallTask::FSubscribeRatingsWithInitialCallTask(const TSharedPtr<FUserDomain>& Self, TFunction<void(TArray<Gs2::Matchmaking::Model::FRatingPtr>)> Callback,const TOptional<FString> TimeOffsetToken) : Self(Self), Callback(Callback), QueryTimeOffsetToken(TimeOffsetToken) {}
    FUserDomain::FSubscribeRatingsWithInitialCallTask::FSubscribeRatingsWithInitialCallTask(const FSubscribeRatingsWithInitialCallTask& From) : TGs2Future(From), Self(From.Self), Callback(From.Callback), QueryTimeOffsetToken(From.QueryTimeOffsetToken) {}
    Gs2::Core::Model::FGs2ErrorPtr FUserDomain::FSubscribeRatingsWithInitialCallTask::Action(TSharedPtr<TSharedPtr<Gs2::Core::Domain::CallbackID>> Result)
    {
        const auto Task = Gs2::Core::Util::New<FAsyncTask<FCollectRatingsTask>>(Self, TFunction<void(TArray<Gs2::Matchmaking::Model::FRatingPtr>)>(), QueryTimeOffsetToken);
        Task->StartSynchronousTask(); Task->EnsureCompletion();
        if (Task->GetTask().IsError()) return Task->GetTask().Error();
        const auto Values = Task->GetTask().Result();
        const auto CallbackId = Self->SubscribeRatings(Callback, QueryTimeOffsetToken);
        Callback(*Values); *Result = MakeShared<Gs2::Core::Domain::CallbackID>(CallbackId);
        return nullptr;
    }
    TSharedPtr<FAsyncTask<FUserDomain::FSubscribeRatingsWithInitialCallTask>> FUserDomain::SubscribeRatingsWithInitialCall(TFunction<void(TArray<Gs2::Matchmaking::Model::FRatingPtr>)> Callback,const TOptional<FString> TimeOffsetToken)
    {
        return Gs2::Core::Util::New<FAsyncTask<FSubscribeRatingsWithInitialCallTask>>(this->AsShared(), Callback, TimeOffsetToken);
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

    TSharedPtr<Gs2::Matchmaking::Domain::Model::FSeasonDomain> FUserDomain::Season(
        const FString SeasonName,
        const int64 Season
    )
    {
        return MakeShared<Gs2::Matchmaking::Domain::Model::FSeasonDomain>(
            Gs2,
            Service,
            NamespaceName,
            UserId,
            SeasonName == TEXT("") ? TOptional<FString>() : TOptional<FString>(SeasonName),
            Season
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
