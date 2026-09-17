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

#include "Ranking2/Domain/Model/SubscribeRankingSeason.h"
#include "Ranking2/Domain/Model/Namespace.h"
#include "Ranking2/Domain/Model/GlobalRankingModel.h"
#include "Ranking2/Domain/Model/GlobalRankingModelMaster.h"
#include "Ranking2/Domain/Model/GlobalRankingScore.h"
#include "Ranking2/Domain/Model/GlobalRankingScoreAccessToken.h"
#include "Ranking2/Domain/Model/GlobalRankingReceivedReward.h"
#include "Ranking2/Domain/Model/GlobalRankingReceivedRewardAccessToken.h"
#include "Ranking2/Domain/Model/GlobalRankingSeason.h"
#include "Ranking2/Domain/Model/GlobalRankingSeasonAccessToken.h"
#include "Ranking2/Domain/Model/GlobalRankingData.h"
#include "Ranking2/Domain/Model/GlobalRankingDataAccessToken.h"
#include "Ranking2/Domain/Model/ClusterRankingModel.h"
#include "Ranking2/Domain/Model/ClusterRankingModelMaster.h"
#include "Ranking2/Domain/Model/ClusterRankingScore.h"
#include "Ranking2/Domain/Model/ClusterRankingScoreAccessToken.h"
#include "Ranking2/Domain/Model/ClusterRankingReceivedReward.h"
#include "Ranking2/Domain/Model/ClusterRankingReceivedRewardAccessToken.h"
#include "Ranking2/Domain/Model/ClusterRankingSeason.h"
#include "Ranking2/Domain/Model/ClusterRankingSeasonAccessToken.h"
#include "Ranking2/Domain/Model/ClusterRankingData.h"
#include "Ranking2/Domain/Model/ClusterRankingDataAccessToken.h"
#include "Ranking2/Domain/Model/SubscribeRankingModel.h"
#include "Ranking2/Domain/Model/SubscribeRankingModelMaster.h"
#include "Ranking2/Domain/Model/SubscribeRankingSeason.h"
#include "Ranking2/Domain/Model/SubscribeRankingSeasonAccessToken.h"
#include "Ranking2/Domain/Model/Subscribe.h"
#include "Ranking2/Domain/Model/SubscribeAccessToken.h"
#include "Ranking2/Domain/Model/SubscribeRankingScore.h"
#include "Ranking2/Domain/Model/SubscribeRankingScoreAccessToken.h"
#include "Ranking2/Domain/Model/SubscribeRankingData.h"
#include "Ranking2/Domain/Model/SubscribeRankingDataAccessToken.h"
#include "Ranking2/Domain/Model/CurrentRankingMaster.h"
#include "Ranking2/Domain/Model/SubscribeUser.h"
#include "Ranking2/Domain/Model/SubscribeUserAccessToken.h"
#include "Ranking2/Domain/Model/User.h"
#include "Ranking2/Domain/Model/UserAccessToken.h"
#include "Ranking2/Model/Cache/SubscribeRankingScore.h"
#include "Ranking2/Model/Cache/SubscribeRankingData.h"

#include "Core/Domain/Gs2.h"
#include "Core/Domain/Transaction/JobQueueJobDomainFactory.h"
#include "Core/Domain/Transaction/InternalTransactionDomainFactory.h"
#include "Core/Domain/Transaction/ManualTransactionDomain.h"

namespace Gs2::Ranking2::Domain::Model
{

    FSubscribeRankingSeasonDomain::FSubscribeRankingSeasonDomain(
        const Core::Domain::FGs2Ptr& Gs2,
        const Ranking2::Domain::FGs2Ranking2DomainPtr& Service,
        const TOptional<FString> NamespaceName,
        const TOptional<FString> RankingName,
        const TOptional<int64> Season,
        const TOptional<FString> UserId
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Gs2(Gs2),
        Service(Service),
        Client(MakeShared<Gs2::Ranking2::FGs2Ranking2RestClient>(Gs2->RestSession)),
        NamespaceName(NamespaceName),
        RankingName(RankingName),
        Season(Season),
        UserId(UserId),
        ParentKey(Gs2::Ranking2::Domain::Model::FSubscribeRankingModelDomain::CreateCacheParentKey(
            NamespaceName,
            RankingName,
            "SubscribeRankingSeason"
        ))
    {
    }

    FSubscribeRankingSeasonDomain::FSubscribeRankingSeasonDomain(
        const FSubscribeRankingSeasonDomain& From
    ):
        Gs2(From.Gs2),
        Service(From.Service),
        Client(From.Client),
        NamespaceName(From.NamespaceName),
        RankingName(From.RankingName),
        Season(From.Season),
        UserId(From.UserId),
        ParentKey(From.ParentKey)
    {

    }

    FSubscribeRankingSeasonDomain::FPutSubscribeRankingScoreTask::FPutSubscribeRankingScoreTask(
        const TSharedPtr<FSubscribeRankingSeasonDomain>& Self,
        const Request::FPutSubscribeRankingScoreByUserIdRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FSubscribeRankingSeasonDomain::FPutSubscribeRankingScoreTask::FPutSubscribeRankingScoreTask(
        const FPutSubscribeRankingScoreTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FSubscribeRankingSeasonDomain::FPutSubscribeRankingScoreTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Ranking2::Domain::Model::FSubscribeRankingScoreDomain>> Result
    )
    {
        Request
            ->WithContextStack((!Request->GetContextStack().IsSet() || Request->GetContextStack()->IsEmpty()) ? Self->Gs2->DefaultContextStack : Request->GetContextStack())
            ->WithNamespaceName(Self->NamespaceName)
            ->WithRankingName(Self->RankingName)
            ->WithUserId(Self->UserId);
        const auto Future = Self->Client->PutSubscribeRankingScoreByUserId(
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

        if (!ResultModel.IsValid() || !ResultModel->GetItem().IsValid())
            {
              const auto Details = MakeShared<TArray<TSharedPtr<Gs2::Core::Model::FGs2ErrorDetail>>>();
                Details->Add(MakeShared<Gs2::Core::Model::FGs2ErrorDetail>(TEXT("result.item"), TEXT("result.item is invalid."), TEXT("invalid_response")));
                return MakeShared<Gs2::Core::Model::FUnknownError>(Details);
              }if (!ResultModel.IsValid() || !(ResultModel->GetItem()->GetUserId()).IsSet())
            {
              const auto Details = MakeShared<TArray<TSharedPtr<Gs2::Core::Model::FGs2ErrorDetail>>>();
                Details->Add(MakeShared<Gs2::Core::Model::FGs2ErrorDetail>(TEXT("userId"), TEXT("userId is invalid."), TEXT("invalid_response")));
                return MakeShared<Gs2::Core::Model::FUnknownError>(Details);
              }
        Gs2::Ranking2::Model::Cache::FSubscribeRankingScoreCache::Put(
            Self->Gs2->Cache,

            Request->GetNamespaceName(),
            ResultModel->GetItem()->GetRankingName(),
            ResultModel->GetItem()->GetSeason().Get(int64{}),
            ResultModel->GetItem()->GetUserId(),
            TOptional<int32>(),
            ResultModel->GetItem()
        );
            }
        auto Domain = MakeShared<Gs2::Ranking2::Domain::Model::FSubscribeRankingScoreDomain>(
            Self->Gs2,
            Self->Service,
            Request->GetNamespaceName(),
            ResultModel->GetItem()->GetRankingName(),
            ResultModel->GetItem()->GetSeason(),
            ResultModel->GetItem()->GetUserId()
        );

        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FSubscribeRankingSeasonDomain::FPutSubscribeRankingScoreTask>> FSubscribeRankingSeasonDomain::PutSubscribeRankingScore(
        Request::FPutSubscribeRankingScoreByUserIdRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FPutSubscribeRankingScoreTask>>(this->AsShared(), Request);
    }

    Gs2::Ranking2::Domain::Iterator::FDescribeSubscribeRankingScoresByUserIdIteratorPtr FSubscribeRankingSeasonDomain::SubscribeRankingScores(
        const TOptional<FString> TimeOffsetToken
    ) const
    {
        return MakeShared<Gs2::Ranking2::Domain::Iterator::FDescribeSubscribeRankingScoresByUserIdIterator>(
            Gs2,
            Client,
            NamespaceName,
            UserId,
            RankingName,
            TimeOffsetToken
        );
    }

    Gs2::Core::Domain::CallbackID FSubscribeRankingSeasonDomain::SubscribeSubscribeRankingScores(
    TFunction<void()> Callback

    )
    {
        return Gs2->Cache->ListSubscribe(
            Gs2::Ranking2::Model::FSubscribeRankingScore::TypeName,
            Gs2::Ranking2::Model::Cache::FSubscribeRankingScoreCache::CreateCacheParentKey(
                NamespaceName,
                UserId,
                RankingName,
                TOptional<int32>()
            ),
            Callback,
            Callback
        );
    }
    void FSubscribeRankingSeasonDomain::UnsubscribeSubscribeRankingScores(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        Gs2->Cache->ListUnsubscribe(
            Gs2::Ranking2::Model::FSubscribeRankingScore::TypeName,
            Gs2::Ranking2::Model::Cache::FSubscribeRankingScoreCache::CreateCacheParentKey(
                NamespaceName,
                UserId,
                RankingName,
                TOptional<int32>()
            ),
            CallbackID
        );
    }
    class FSubscribeRankingSeasonDomain::FCollectSubscribeRankingScoresTask : public Gs2::Core::Util::TGs2Future<TArray<Gs2::Ranking2::Model::FSubscribeRankingScorePtr>>, public TSharedFromThis<FCollectSubscribeRankingScoresTask>
    {
        const TSharedPtr<FSubscribeRankingSeasonDomain> Self;
        const TFunction<void(TArray<Gs2::Ranking2::Model::FSubscribeRankingScorePtr>)> OnCollected;
    const TOptional<FString> QueryTimeOffsetToken;
    public:
        explicit FCollectSubscribeRankingScoresTask(const TSharedPtr<FSubscribeRankingSeasonDomain>& Self, TFunction<void(TArray<Gs2::Ranking2::Model::FSubscribeRankingScorePtr>)> OnCollected,const TOptional<FString> TimeOffsetToken) : Self(Self), OnCollected(OnCollected), QueryTimeOffsetToken(TimeOffsetToken) {}
        FCollectSubscribeRankingScoresTask(const FCollectSubscribeRankingScoresTask& From) : TGs2Future(From), Self(From.Self), OnCollected(From.OnCollected), QueryTimeOffsetToken(From.QueryTimeOffsetToken) {}
        virtual Gs2::Core::Model::FGs2ErrorPtr Action(TSharedPtr<TSharedPtr<TArray<Gs2::Ranking2::Model::FSubscribeRankingScorePtr>>> Result) override
        {
            TArray<Gs2::Ranking2::Model::FSubscribeRankingScorePtr> Items;
            auto Iterator = Self->SubscribeRankingScores(QueryTimeOffsetToken)->begin();
            while (Iterator.HasNext())
            {
                if (Iterator.IsError()) return Iterator.Error();
                if (Iterator.IsCurrentValid()) Items.Add(Iterator.Current());
                ++Iterator;
            }
            if (Iterator.IsError()) return Iterator.Error();
            *Result = MakeShared<TArray<Gs2::Ranking2::Model::FSubscribeRankingScorePtr>>(Items);
            if (OnCollected) OnCollected(Items);
            return nullptr;
        }
    };

    Gs2::Core::Domain::CallbackID FSubscribeRankingSeasonDomain::SubscribeSubscribeRankingScores(
        TFunction<void(TArray<Gs2::Ranking2::Model::FSubscribeRankingScorePtr>)> Callback,const TOptional<FString> TimeOffsetToken
    )
    {
        const TWeakPtr<Gs2::Core::Domain::FGs2> WeakGs2 = this->Gs2;
        const TWeakPtr<Ranking2::Domain::FGs2Ranking2Domain> WeakService = this->Service;
        const auto QueryNamespaceName = NamespaceName;
        const auto QueryRankingName = RankingName;
        const auto QuerySeason = Season;
        const auto QueryUserId = UserId;
        const auto QueryTimeOffsetToken = TimeOffsetToken;
        const auto Parent = Gs2::Ranking2::Model::Cache::FSubscribeRankingScoreCache::CreateCacheParentKey(
        NamespaceName,
        UserId,
        RankingName,
        TOptional<int32>()
    );
        return Gs2->Cache->ListSubscribeTyped(
            Gs2::Ranking2::Model::FSubscribeRankingScore::TypeName,
            Parent,
            [Callback, WeakGs2](const TArray<FGs2ObjectPtr>& Values)
            {
                if (!WeakGs2.Pin().IsValid()) return;
                TArray<Gs2::Ranking2::Model::FSubscribeRankingScorePtr> TypedValues;
                for (const auto& Value : Values) if (Value.IsValid()) TypedValues.Add(StaticCastSharedPtr<Gs2::Ranking2::Model::FSubscribeRankingScore>(Value));
                Callback(TypedValues);
            },
            [WeakGs2, WeakService, Callback, QueryNamespaceName, QueryRankingName, QuerySeason, QueryUserId, QueryTimeOffsetToken]()
            {
                const auto Owner = WeakGs2.Pin();
                if (!Owner.IsValid()) return;
                const auto Domain = MakeShared<FSubscribeRankingSeasonDomain>(Owner, WeakService.Pin(), QueryNamespaceName, QueryRankingName, QuerySeason, QueryUserId);
                const auto Task = Gs2::Core::Util::New<FAsyncTask<FCollectSubscribeRankingScoresTask>>(Domain, Callback, QueryTimeOffsetToken);
                Task->StartBackgroundTask();
            }
        );
    }

    void FSubscribeRankingSeasonDomain::InvalidateSubscribeRankingScores(const TOptional<FString> TimeOffsetToken)
    {
        Gs2->Cache->ClearListCache(
            Gs2::Ranking2::Model::FSubscribeRankingScore::TypeName,
            Gs2::Ranking2::Model::Cache::FSubscribeRankingScoreCache::CreateCacheParentKey(
        NamespaceName,
        UserId,
        RankingName,
        TOptional<int32>()
    )
        );
    }

    FSubscribeRankingSeasonDomain::FSubscribeSubscribeRankingScoresWithInitialCallTask::FSubscribeSubscribeRankingScoresWithInitialCallTask(const TSharedPtr<FSubscribeRankingSeasonDomain>& Self, TFunction<void(TArray<Gs2::Ranking2::Model::FSubscribeRankingScorePtr>)> Callback,const TOptional<FString> TimeOffsetToken) : Self(Self), Callback(Callback), QueryTimeOffsetToken(TimeOffsetToken) {}
    FSubscribeRankingSeasonDomain::FSubscribeSubscribeRankingScoresWithInitialCallTask::FSubscribeSubscribeRankingScoresWithInitialCallTask(const FSubscribeSubscribeRankingScoresWithInitialCallTask& From) : TGs2Future(From), Self(From.Self), Callback(From.Callback), QueryTimeOffsetToken(From.QueryTimeOffsetToken) {}
    Gs2::Core::Model::FGs2ErrorPtr FSubscribeRankingSeasonDomain::FSubscribeSubscribeRankingScoresWithInitialCallTask::Action(TSharedPtr<TSharedPtr<Gs2::Core::Domain::CallbackID>> Result)
    {
        const auto Task = Gs2::Core::Util::New<FAsyncTask<FCollectSubscribeRankingScoresTask>>(Self, TFunction<void(TArray<Gs2::Ranking2::Model::FSubscribeRankingScorePtr>)>(), QueryTimeOffsetToken);
        Task->StartSynchronousTask(); Task->EnsureCompletion();
        if (Task->GetTask().IsError()) return Task->GetTask().Error();
        const auto Values = Task->GetTask().Result();
        const auto CallbackId = Self->SubscribeSubscribeRankingScores(Callback, QueryTimeOffsetToken);
        Callback(*Values); *Result = MakeShared<Gs2::Core::Domain::CallbackID>(CallbackId);
        return nullptr;
    }
    TSharedPtr<FAsyncTask<FSubscribeRankingSeasonDomain::FSubscribeSubscribeRankingScoresWithInitialCallTask>> FSubscribeRankingSeasonDomain::SubscribeSubscribeRankingScoresWithInitialCall(TFunction<void(TArray<Gs2::Ranking2::Model::FSubscribeRankingScorePtr>)> Callback,const TOptional<FString> TimeOffsetToken)
    {
        return Gs2::Core::Util::New<FAsyncTask<FSubscribeSubscribeRankingScoresWithInitialCallTask>>(this->AsShared(), Callback, TimeOffsetToken);
    }

    TSharedPtr<Gs2::Ranking2::Domain::Model::FSubscribeRankingScoreDomain> FSubscribeRankingSeasonDomain::SubscribeRankingScore(
    )
    {
        return MakeShared<Gs2::Ranking2::Domain::Model::FSubscribeRankingScoreDomain>(
            Gs2,
            Service,
            NamespaceName,
            RankingName,
            Season,
            UserId
        );
    }

    Gs2::Ranking2::Domain::Iterator::FDescribeSubscribeRankingsByUserIdIteratorPtr FSubscribeRankingSeasonDomain::SubscribeRankings(
        const TOptional<FString> TimeOffsetToken
    ) const
    {
        return MakeShared<Gs2::Ranking2::Domain::Iterator::FDescribeSubscribeRankingsByUserIdIterator>(
            Gs2,
            Client,
            NamespaceName,
            UserId,
            RankingName,
            Season,
            TimeOffsetToken
        );
    }

    Gs2::Core::Domain::CallbackID FSubscribeRankingSeasonDomain::SubscribeSubscribeRankings(
    TFunction<void()> Callback

    )
    {
        return Gs2->Cache->ListSubscribe(
            Gs2::Ranking2::Model::FSubscribeRankingData::TypeName,
            Gs2::Ranking2::Model::Cache::FSubscribeRankingDataCache::CreateCacheParentKey(
                NamespaceName,
                RankingName,
                Season,
                TOptional<int32>()
            ),
            Callback,
            Callback
        );
    }
    void FSubscribeRankingSeasonDomain::UnsubscribeSubscribeRankings(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        Gs2->Cache->ListUnsubscribe(
            Gs2::Ranking2::Model::FSubscribeRankingData::TypeName,
            Gs2::Ranking2::Model::Cache::FSubscribeRankingDataCache::CreateCacheParentKey(
                NamespaceName,
                RankingName,
                Season,
                TOptional<int32>()
            ),
            CallbackID
        );
    }
    class FSubscribeRankingSeasonDomain::FCollectSubscribeRankingsTask : public Gs2::Core::Util::TGs2Future<TArray<Gs2::Ranking2::Model::FSubscribeRankingDataPtr>>, public TSharedFromThis<FCollectSubscribeRankingsTask>
    {
        const TSharedPtr<FSubscribeRankingSeasonDomain> Self;
        const TFunction<void(TArray<Gs2::Ranking2::Model::FSubscribeRankingDataPtr>)> OnCollected;
    const TOptional<FString> QueryTimeOffsetToken;
    public:
        explicit FCollectSubscribeRankingsTask(const TSharedPtr<FSubscribeRankingSeasonDomain>& Self, TFunction<void(TArray<Gs2::Ranking2::Model::FSubscribeRankingDataPtr>)> OnCollected,const TOptional<FString> TimeOffsetToken) : Self(Self), OnCollected(OnCollected), QueryTimeOffsetToken(TimeOffsetToken) {}
        FCollectSubscribeRankingsTask(const FCollectSubscribeRankingsTask& From) : TGs2Future(From), Self(From.Self), OnCollected(From.OnCollected), QueryTimeOffsetToken(From.QueryTimeOffsetToken) {}
        virtual Gs2::Core::Model::FGs2ErrorPtr Action(TSharedPtr<TSharedPtr<TArray<Gs2::Ranking2::Model::FSubscribeRankingDataPtr>>> Result) override
        {
            TArray<Gs2::Ranking2::Model::FSubscribeRankingDataPtr> Items;
            auto Iterator = Self->SubscribeRankings(QueryTimeOffsetToken)->begin();
            while (Iterator.HasNext())
            {
                if (Iterator.IsError()) return Iterator.Error();
                if (Iterator.IsCurrentValid()) Items.Add(Iterator.Current());
                ++Iterator;
            }
            if (Iterator.IsError()) return Iterator.Error();
            *Result = MakeShared<TArray<Gs2::Ranking2::Model::FSubscribeRankingDataPtr>>(Items);
            if (OnCollected) OnCollected(Items);
            return nullptr;
        }
    };

    Gs2::Core::Domain::CallbackID FSubscribeRankingSeasonDomain::SubscribeSubscribeRankings(
        TFunction<void(TArray<Gs2::Ranking2::Model::FSubscribeRankingDataPtr>)> Callback,const TOptional<FString> TimeOffsetToken
    )
    {
        const TWeakPtr<Gs2::Core::Domain::FGs2> WeakGs2 = this->Gs2;
        const TWeakPtr<Ranking2::Domain::FGs2Ranking2Domain> WeakService = this->Service;
        const auto QueryNamespaceName = NamespaceName;
        const auto QueryRankingName = RankingName;
        const auto QuerySeason = Season;
        const auto QueryUserId = UserId;
        const auto QueryTimeOffsetToken = TimeOffsetToken;
        const auto Parent = Gs2::Ranking2::Model::Cache::FSubscribeRankingDataCache::CreateCacheParentKey(
        NamespaceName,
        RankingName,
        Season,
        TOptional<int32>()
    );
        return Gs2->Cache->ListSubscribeTyped(
            Gs2::Ranking2::Model::FSubscribeRankingData::TypeName,
            Parent,
            [Callback, WeakGs2](const TArray<FGs2ObjectPtr>& Values)
            {
                if (!WeakGs2.Pin().IsValid()) return;
                TArray<Gs2::Ranking2::Model::FSubscribeRankingDataPtr> TypedValues;
                for (const auto& Value : Values) if (Value.IsValid()) TypedValues.Add(StaticCastSharedPtr<Gs2::Ranking2::Model::FSubscribeRankingData>(Value));
                Callback(TypedValues);
            },
            [WeakGs2, WeakService, Callback, QueryNamespaceName, QueryRankingName, QuerySeason, QueryUserId, QueryTimeOffsetToken]()
            {
                const auto Owner = WeakGs2.Pin();
                if (!Owner.IsValid()) return;
                const auto Domain = MakeShared<FSubscribeRankingSeasonDomain>(Owner, WeakService.Pin(), QueryNamespaceName, QueryRankingName, QuerySeason, QueryUserId);
                const auto Task = Gs2::Core::Util::New<FAsyncTask<FCollectSubscribeRankingsTask>>(Domain, Callback, QueryTimeOffsetToken);
                Task->StartBackgroundTask();
            }
        );
    }

    void FSubscribeRankingSeasonDomain::InvalidateSubscribeRankings(const TOptional<FString> TimeOffsetToken)
    {
        Gs2->Cache->ClearListCache(
            Gs2::Ranking2::Model::FSubscribeRankingData::TypeName,
            Gs2::Ranking2::Model::Cache::FSubscribeRankingDataCache::CreateCacheParentKey(
        NamespaceName,
        RankingName,
        Season,
        TOptional<int32>()
    )
        );
    }

    FSubscribeRankingSeasonDomain::FSubscribeSubscribeRankingsWithInitialCallTask::FSubscribeSubscribeRankingsWithInitialCallTask(const TSharedPtr<FSubscribeRankingSeasonDomain>& Self, TFunction<void(TArray<Gs2::Ranking2::Model::FSubscribeRankingDataPtr>)> Callback,const TOptional<FString> TimeOffsetToken) : Self(Self), Callback(Callback), QueryTimeOffsetToken(TimeOffsetToken) {}
    FSubscribeRankingSeasonDomain::FSubscribeSubscribeRankingsWithInitialCallTask::FSubscribeSubscribeRankingsWithInitialCallTask(const FSubscribeSubscribeRankingsWithInitialCallTask& From) : TGs2Future(From), Self(From.Self), Callback(From.Callback), QueryTimeOffsetToken(From.QueryTimeOffsetToken) {}
    Gs2::Core::Model::FGs2ErrorPtr FSubscribeRankingSeasonDomain::FSubscribeSubscribeRankingsWithInitialCallTask::Action(TSharedPtr<TSharedPtr<Gs2::Core::Domain::CallbackID>> Result)
    {
        const auto Task = Gs2::Core::Util::New<FAsyncTask<FCollectSubscribeRankingsTask>>(Self, TFunction<void(TArray<Gs2::Ranking2::Model::FSubscribeRankingDataPtr>)>(), QueryTimeOffsetToken);
        Task->StartSynchronousTask(); Task->EnsureCompletion();
        if (Task->GetTask().IsError()) return Task->GetTask().Error();
        const auto Values = Task->GetTask().Result();
        const auto CallbackId = Self->SubscribeSubscribeRankings(Callback, QueryTimeOffsetToken);
        Callback(*Values); *Result = MakeShared<Gs2::Core::Domain::CallbackID>(CallbackId);
        return nullptr;
    }
    TSharedPtr<FAsyncTask<FSubscribeRankingSeasonDomain::FSubscribeSubscribeRankingsWithInitialCallTask>> FSubscribeRankingSeasonDomain::SubscribeSubscribeRankingsWithInitialCall(TFunction<void(TArray<Gs2::Ranking2::Model::FSubscribeRankingDataPtr>)> Callback,const TOptional<FString> TimeOffsetToken)
    {
        return Gs2::Core::Util::New<FAsyncTask<FSubscribeSubscribeRankingsWithInitialCallTask>>(this->AsShared(), Callback, TimeOffsetToken);
    }

    TSharedPtr<Gs2::Ranking2::Domain::Model::FSubscribeRankingDataDomain> FSubscribeRankingSeasonDomain::SubscribeRankingData(
        const FString ScorerUserId
    )
    {
        return MakeShared<Gs2::Ranking2::Domain::Model::FSubscribeRankingDataDomain>(
            Gs2,
            Service,
            NamespaceName,
            RankingName,
            Season,
            UserId,
            ScorerUserId == TEXT("") ? TOptional<FString>() : TOptional<FString>(ScorerUserId)
        );
    }

    FString FSubscribeRankingSeasonDomain::CreateCacheParentKey(
        TOptional<FString> NamespaceName,
        TOptional<FString> RankingName,
        TOptional<int64> Season,
        FString ChildType
    )
    {
        return FString("") +
            (NamespaceName.IsSet() ? *NamespaceName : "null") + ":" +
            (RankingName.IsSet() ? *RankingName : "null") + ":" +
            (Season.IsSet() ? FString::FromInt(*Season) : "null") + ":" +
            ChildType;
    }

    FString FSubscribeRankingSeasonDomain::CreateCacheKey(
        TOptional<int64> Season
    )
    {
        return FString("") +
            (Season.IsSet() ? FString::FromInt(*Season) : "null");
    }
}

#if defined(_MSC_VER)
#pragma warning (pop)
#elif defined(__clang__)
#pragma clang diagnostic pop
#endif
