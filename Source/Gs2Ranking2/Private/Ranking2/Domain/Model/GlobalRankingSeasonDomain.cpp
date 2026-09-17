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

#include "Ranking2/Domain/Model/GlobalRankingSeason.h"
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

#include "Ranking2/Model/Cache/GlobalRankingReceivedReward.h"
#include "Ranking2/Model/Cache/GlobalRankingScore.h"
#include "Ranking2/Model/Cache/GlobalRankingData.h"
#include "Core/Domain/Gs2.h"
#include "Core/Domain/Transaction/JobQueueJobDomainFactory.h"
#include "Core/Domain/Transaction/InternalTransactionDomainFactory.h"
#include "Core/Domain/Transaction/ManualTransactionDomain.h"

namespace Gs2::Ranking2::Domain::Model
{

    FGlobalRankingSeasonDomain::FGlobalRankingSeasonDomain(
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
        ParentKey(Gs2::Ranking2::Domain::Model::FGlobalRankingModelDomain::CreateCacheParentKey(
            NamespaceName,
            RankingName,
            "GlobalRankingSeason"
        ))
    {
    }

    FGlobalRankingSeasonDomain::FGlobalRankingSeasonDomain(
        const FGlobalRankingSeasonDomain& From
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

    FGlobalRankingSeasonDomain::FPutGlobalRankingScoreTask::FPutGlobalRankingScoreTask(
        const TSharedPtr<FGlobalRankingSeasonDomain>& Self,
        const Request::FPutGlobalRankingScoreByUserIdRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FGlobalRankingSeasonDomain::FPutGlobalRankingScoreTask::FPutGlobalRankingScoreTask(
        const FPutGlobalRankingScoreTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FGlobalRankingSeasonDomain::FPutGlobalRankingScoreTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Ranking2::Domain::Model::FGlobalRankingScoreDomain>> Result
    )
    {
        Request
            ->WithContextStack(Self->Gs2->DefaultContextStack)
            ->WithNamespaceName(Self->NamespaceName)
            ->WithRankingName(Self->RankingName)
            ->WithUserId(Self->UserId);
        const auto Future = Self->Client->PutGlobalRankingScoreByUserId(
            Request
        );
        Future->StartSynchronousTask();
        if (Future->GetTask().IsError())
        {
            return Future->GetTask().Error();
        }
        const auto ResultModel = Future->GetTask().Result();
        Future->EnsureCompletion();
        auto Domain = MakeShared<Gs2::Ranking2::Domain::Model::FGlobalRankingScoreDomain>(
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

    TSharedPtr<FAsyncTask<FGlobalRankingSeasonDomain::FPutGlobalRankingScoreTask>> FGlobalRankingSeasonDomain::PutGlobalRankingScore(
        Request::FPutGlobalRankingScoreByUserIdRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FPutGlobalRankingScoreTask>>(this->AsShared(), Request);
    }

    FGlobalRankingSeasonDomain::FGetGlobalRankingTask::FGetGlobalRankingTask(
        const TSharedPtr<FGlobalRankingSeasonDomain>& Self,
        const Request::FGetGlobalRankingByUserIdRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FGlobalRankingSeasonDomain::FGetGlobalRankingTask::FGetGlobalRankingTask(
        const FGetGlobalRankingTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FGlobalRankingSeasonDomain::FGetGlobalRankingTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Ranking2::Domain::Model::FGlobalRankingDataDomain>> Result
    )
    {
        Request
            ->WithContextStack(Self->Gs2->DefaultContextStack)
            ->WithNamespaceName(Self->NamespaceName)
            ->WithRankingName(Self->RankingName)
            ->WithUserId(Self->UserId)
            ->WithSeason(Self->Season);
        const auto Future = Self->Client->GetGlobalRankingByUserId(
            Request
        );
        Future->StartSynchronousTask();
        if (Future->GetTask().IsError())
        {
            return Future->GetTask().Error();
        }
        const auto ResultModel = Future->GetTask().Result();
        Future->EnsureCompletion();
        auto Domain = MakeShared<Gs2::Ranking2::Domain::Model::FGlobalRankingDataDomain>(
            Self->Gs2,
            Self->Service,
            Request->GetNamespaceName(),
            ResultModel->GetItem()->GetRankingName(),
            ResultModel->GetItem()->GetSeason(),
            ResultModel->GetItem()->GetUserId(),
            ResultModel->GetItem()->GetUserId()
        );

        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FGlobalRankingSeasonDomain::FGetGlobalRankingTask>> FGlobalRankingSeasonDomain::GetGlobalRanking(
        Request::FGetGlobalRankingByUserIdRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FGetGlobalRankingTask>>(this->AsShared(), Request);
    }

    Gs2::Ranking2::Domain::Iterator::FDescribeGlobalRankingScoresByUserIdIteratorPtr FGlobalRankingSeasonDomain::GlobalRankingScores(
        const TOptional<FString> TimeOffsetToken
    ) const
    {
        return MakeShared<Gs2::Ranking2::Domain::Iterator::FDescribeGlobalRankingScoresByUserIdIterator>(
            Gs2,
            Client,
            NamespaceName,
            UserId,
            RankingName,
            TimeOffsetToken
        );
    }

    Gs2::Core::Domain::CallbackID FGlobalRankingSeasonDomain::SubscribeGlobalRankingScores(
    TFunction<void()> Callback
    )
    {
        return Gs2->Cache->ListSubscribe(
            Gs2::Ranking2::Model::FGlobalRankingScore::TypeName,
            Gs2::Ranking2::Model::Cache::FGlobalRankingScoreCache::CreateCacheParentKey(
                NamespaceName,
                UserId,
                RankingName,
                TOptional<int32>()
            ),
            Callback,
            Callback
        );
    }
    void FGlobalRankingSeasonDomain::UnsubscribeGlobalRankingScores(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        Gs2->Cache->ListUnsubscribe(
            Gs2::Ranking2::Model::FGlobalRankingScore::TypeName,
            Gs2::Ranking2::Model::Cache::FGlobalRankingScoreCache::CreateCacheParentKey(
                NamespaceName,
                UserId,
                RankingName,
                TOptional<int32>()
            ),
            CallbackID
        );
    }
    class FGlobalRankingSeasonDomain::FCollectGlobalRankingScoresTask : public Gs2::Core::Util::TGs2Future<TArray<Gs2::Ranking2::Model::FGlobalRankingScorePtr>>, public TSharedFromThis<FCollectGlobalRankingScoresTask>
    {
        const TSharedPtr<FGlobalRankingSeasonDomain> Self;
        const TFunction<void(TArray<Gs2::Ranking2::Model::FGlobalRankingScorePtr>)> OnCollected;
    const TOptional<FString> QueryTimeOffsetToken;
    public:
        explicit FCollectGlobalRankingScoresTask(const TSharedPtr<FGlobalRankingSeasonDomain>& Self, TFunction<void(TArray<Gs2::Ranking2::Model::FGlobalRankingScorePtr>)> OnCollected,const TOptional<FString> TimeOffsetToken) : Self(Self), OnCollected(OnCollected), QueryTimeOffsetToken(TimeOffsetToken) {}
        FCollectGlobalRankingScoresTask(const FCollectGlobalRankingScoresTask& From) : TGs2Future(From), Self(From.Self), OnCollected(From.OnCollected), QueryTimeOffsetToken(From.QueryTimeOffsetToken) {}
        virtual Gs2::Core::Model::FGs2ErrorPtr Action(TSharedPtr<TSharedPtr<TArray<Gs2::Ranking2::Model::FGlobalRankingScorePtr>>> Result) override
        {
            TArray<Gs2::Ranking2::Model::FGlobalRankingScorePtr> Items;
            auto Iterator = Self->GlobalRankingScores(QueryTimeOffsetToken)->begin();
            while (Iterator.HasNext())
            {
                if (Iterator.IsError()) return Iterator.Error();
                if (Iterator.IsCurrentValid()) Items.Add(Iterator.Current());
                ++Iterator;
            }
            if (Iterator.IsError()) return Iterator.Error();
            *Result = MakeShared<TArray<Gs2::Ranking2::Model::FGlobalRankingScorePtr>>(Items);
            if (OnCollected) OnCollected(Items);
            return nullptr;
        }
    };

    Gs2::Core::Domain::CallbackID FGlobalRankingSeasonDomain::SubscribeGlobalRankingScores(
        TFunction<void(TArray<Gs2::Ranking2::Model::FGlobalRankingScorePtr>)> Callback,const TOptional<FString> TimeOffsetToken
    )
    {
        const TWeakPtr<Gs2::Core::Domain::FGs2> WeakGs2 = this->Gs2;
        const TWeakPtr<Ranking2::Domain::FGs2Ranking2Domain> WeakService = this->Service;
        const auto QueryNamespaceName = NamespaceName;
        const auto QueryRankingName = RankingName;
        const auto QuerySeason = Season;
        const auto QueryUserId = UserId;
        const auto QueryTimeOffsetToken = TimeOffsetToken;
        const auto Parent = Gs2::Ranking2::Model::Cache::FGlobalRankingScoreCache::CreateCacheParentKey(
        NamespaceName,
        UserId,
        RankingName,
        TOptional<int32>()
    );
        return Gs2->Cache->ListSubscribeTyped(
            Gs2::Ranking2::Model::FGlobalRankingScore::TypeName,
            Parent,
            [Callback, WeakGs2](const TArray<FGs2ObjectPtr>& Values)
            {
                if (!WeakGs2.Pin().IsValid()) return;
                TArray<Gs2::Ranking2::Model::FGlobalRankingScorePtr> TypedValues;
                for (const auto& Value : Values) if (Value.IsValid()) TypedValues.Add(StaticCastSharedPtr<Gs2::Ranking2::Model::FGlobalRankingScore>(Value));
                Callback(TypedValues);
            },
            [WeakGs2, WeakService, Callback, QueryNamespaceName, QueryRankingName, QuerySeason, QueryUserId, QueryTimeOffsetToken]()
            {
                const auto Owner = WeakGs2.Pin();
                if (!Owner.IsValid()) return;
                const auto Domain = MakeShared<FGlobalRankingSeasonDomain>(Owner, WeakService.Pin(), QueryNamespaceName, QueryRankingName, QuerySeason, QueryUserId);
                const auto Task = Gs2::Core::Util::New<FAsyncTask<FCollectGlobalRankingScoresTask>>(Domain, Callback, QueryTimeOffsetToken);
                Task->StartBackgroundTask();
            }
        );
    }

    void FGlobalRankingSeasonDomain::InvalidateGlobalRankingScores(const TOptional<FString> TimeOffsetToken)
    {
        Gs2->Cache->ClearListCache(
            Gs2::Ranking2::Model::FGlobalRankingScore::TypeName,
            Gs2::Ranking2::Model::Cache::FGlobalRankingScoreCache::CreateCacheParentKey(
        NamespaceName,
        UserId,
        RankingName,
        TOptional<int32>()
    )
        );
    }

    FGlobalRankingSeasonDomain::FSubscribeGlobalRankingScoresWithInitialCallTask::FSubscribeGlobalRankingScoresWithInitialCallTask(const TSharedPtr<FGlobalRankingSeasonDomain>& Self, TFunction<void(TArray<Gs2::Ranking2::Model::FGlobalRankingScorePtr>)> Callback,const TOptional<FString> TimeOffsetToken) : Self(Self), Callback(Callback), QueryTimeOffsetToken(TimeOffsetToken) {}
    FGlobalRankingSeasonDomain::FSubscribeGlobalRankingScoresWithInitialCallTask::FSubscribeGlobalRankingScoresWithInitialCallTask(const FSubscribeGlobalRankingScoresWithInitialCallTask& From) : TGs2Future(From), Self(From.Self), Callback(From.Callback), QueryTimeOffsetToken(From.QueryTimeOffsetToken) {}
    Gs2::Core::Model::FGs2ErrorPtr FGlobalRankingSeasonDomain::FSubscribeGlobalRankingScoresWithInitialCallTask::Action(TSharedPtr<TSharedPtr<Gs2::Core::Domain::CallbackID>> Result)
    {
        const auto Task = Gs2::Core::Util::New<FAsyncTask<FCollectGlobalRankingScoresTask>>(Self, TFunction<void(TArray<Gs2::Ranking2::Model::FGlobalRankingScorePtr>)>(), QueryTimeOffsetToken);
        Task->StartSynchronousTask(); Task->EnsureCompletion();
        if (Task->GetTask().IsError()) return Task->GetTask().Error();
        const auto Values = Task->GetTask().Result();
        const auto CallbackId = Self->SubscribeGlobalRankingScores(Callback, QueryTimeOffsetToken);
        Callback(*Values); *Result = MakeShared<Gs2::Core::Domain::CallbackID>(CallbackId);
        return nullptr;
    }
    TSharedPtr<FAsyncTask<FGlobalRankingSeasonDomain::FSubscribeGlobalRankingScoresWithInitialCallTask>> FGlobalRankingSeasonDomain::SubscribeGlobalRankingScoresWithInitialCall(TFunction<void(TArray<Gs2::Ranking2::Model::FGlobalRankingScorePtr>)> Callback,const TOptional<FString> TimeOffsetToken)
    {
        return Gs2::Core::Util::New<FAsyncTask<FSubscribeGlobalRankingScoresWithInitialCallTask>>(this->AsShared(), Callback, TimeOffsetToken);
    }

    TSharedPtr<Gs2::Ranking2::Domain::Model::FGlobalRankingScoreDomain> FGlobalRankingSeasonDomain::GlobalRankingScore(
    )
    {
        return MakeShared<Gs2::Ranking2::Domain::Model::FGlobalRankingScoreDomain>(
            Gs2,
            Service,
            NamespaceName,
            RankingName,
            Season,
            UserId
        );
    }

    Gs2::Ranking2::Domain::Iterator::FDescribeGlobalRankingsByUserIdIteratorPtr FGlobalRankingSeasonDomain::GlobalRankings(
        const TOptional<FString> TimeOffsetToken
    ) const
    {
        return MakeShared<Gs2::Ranking2::Domain::Iterator::FDescribeGlobalRankingsByUserIdIterator>(
            Gs2,
            Client,
            NamespaceName,
            UserId,
            RankingName,
            Season,
            TimeOffsetToken
        );
    }

    Gs2::Core::Domain::CallbackID FGlobalRankingSeasonDomain::SubscribeGlobalRankings(
    TFunction<void()> Callback
    )
    {
        return Gs2->Cache->ListSubscribe(
            Gs2::Ranking2::Model::FGlobalRankingData::TypeName,
            Gs2::Ranking2::Model::Cache::FGlobalRankingDataCache::CreateCacheParentKey(
                NamespaceName,
                RankingName,
                Season,
                TOptional<int32>()
            ),
            Callback,
            Callback
        );
    }
    void FGlobalRankingSeasonDomain::UnsubscribeGlobalRankings(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        Gs2->Cache->ListUnsubscribe(
            Gs2::Ranking2::Model::FGlobalRankingData::TypeName,
            Gs2::Ranking2::Model::Cache::FGlobalRankingDataCache::CreateCacheParentKey(
                NamespaceName,
                RankingName,
                Season,
                TOptional<int32>()
            ),
            CallbackID
        );
    }
    class FGlobalRankingSeasonDomain::FCollectGlobalRankingsTask : public Gs2::Core::Util::TGs2Future<TArray<Gs2::Ranking2::Model::FGlobalRankingDataPtr>>, public TSharedFromThis<FCollectGlobalRankingsTask>
    {
        const TSharedPtr<FGlobalRankingSeasonDomain> Self;
        const TFunction<void(TArray<Gs2::Ranking2::Model::FGlobalRankingDataPtr>)> OnCollected;
    const TOptional<FString> QueryTimeOffsetToken;
    public:
        explicit FCollectGlobalRankingsTask(const TSharedPtr<FGlobalRankingSeasonDomain>& Self, TFunction<void(TArray<Gs2::Ranking2::Model::FGlobalRankingDataPtr>)> OnCollected,const TOptional<FString> TimeOffsetToken) : Self(Self), OnCollected(OnCollected), QueryTimeOffsetToken(TimeOffsetToken) {}
        FCollectGlobalRankingsTask(const FCollectGlobalRankingsTask& From) : TGs2Future(From), Self(From.Self), OnCollected(From.OnCollected), QueryTimeOffsetToken(From.QueryTimeOffsetToken) {}
        virtual Gs2::Core::Model::FGs2ErrorPtr Action(TSharedPtr<TSharedPtr<TArray<Gs2::Ranking2::Model::FGlobalRankingDataPtr>>> Result) override
        {
            TArray<Gs2::Ranking2::Model::FGlobalRankingDataPtr> Items;
            auto Iterator = Self->GlobalRankings(QueryTimeOffsetToken)->begin();
            while (Iterator.HasNext())
            {
                if (Iterator.IsError()) return Iterator.Error();
                if (Iterator.IsCurrentValid()) Items.Add(Iterator.Current());
                ++Iterator;
            }
            if (Iterator.IsError()) return Iterator.Error();
            *Result = MakeShared<TArray<Gs2::Ranking2::Model::FGlobalRankingDataPtr>>(Items);
            if (OnCollected) OnCollected(Items);
            return nullptr;
        }
    };

    Gs2::Core::Domain::CallbackID FGlobalRankingSeasonDomain::SubscribeGlobalRankings(
        TFunction<void(TArray<Gs2::Ranking2::Model::FGlobalRankingDataPtr>)> Callback,const TOptional<FString> TimeOffsetToken
    )
    {
        const TWeakPtr<Gs2::Core::Domain::FGs2> WeakGs2 = this->Gs2;
        const TWeakPtr<Ranking2::Domain::FGs2Ranking2Domain> WeakService = this->Service;
        const auto QueryNamespaceName = NamespaceName;
        const auto QueryRankingName = RankingName;
        const auto QuerySeason = Season;
        const auto QueryUserId = UserId;
        const auto QueryTimeOffsetToken = TimeOffsetToken;
        const auto Parent = Gs2::Ranking2::Model::Cache::FGlobalRankingDataCache::CreateCacheParentKey(
        NamespaceName,
        RankingName,
        Season,
        TOptional<int32>()
    );
        return Gs2->Cache->ListSubscribeTyped(
            Gs2::Ranking2::Model::FGlobalRankingData::TypeName,
            Parent,
            [Callback, WeakGs2](const TArray<FGs2ObjectPtr>& Values)
            {
                if (!WeakGs2.Pin().IsValid()) return;
                TArray<Gs2::Ranking2::Model::FGlobalRankingDataPtr> TypedValues;
                for (const auto& Value : Values) if (Value.IsValid()) TypedValues.Add(StaticCastSharedPtr<Gs2::Ranking2::Model::FGlobalRankingData>(Value));
                Callback(TypedValues);
            },
            [WeakGs2, WeakService, Callback, QueryNamespaceName, QueryRankingName, QuerySeason, QueryUserId, QueryTimeOffsetToken]()
            {
                const auto Owner = WeakGs2.Pin();
                if (!Owner.IsValid()) return;
                const auto Domain = MakeShared<FGlobalRankingSeasonDomain>(Owner, WeakService.Pin(), QueryNamespaceName, QueryRankingName, QuerySeason, QueryUserId);
                const auto Task = Gs2::Core::Util::New<FAsyncTask<FCollectGlobalRankingsTask>>(Domain, Callback, QueryTimeOffsetToken);
                Task->StartBackgroundTask();
            }
        );
    }

    void FGlobalRankingSeasonDomain::InvalidateGlobalRankings(const TOptional<FString> TimeOffsetToken)
    {
        Gs2->Cache->ClearListCache(
            Gs2::Ranking2::Model::FGlobalRankingData::TypeName,
            Gs2::Ranking2::Model::Cache::FGlobalRankingDataCache::CreateCacheParentKey(
        NamespaceName,
        RankingName,
        Season,
        TOptional<int32>()
    )
        );
    }

    FGlobalRankingSeasonDomain::FSubscribeGlobalRankingsWithInitialCallTask::FSubscribeGlobalRankingsWithInitialCallTask(const TSharedPtr<FGlobalRankingSeasonDomain>& Self, TFunction<void(TArray<Gs2::Ranking2::Model::FGlobalRankingDataPtr>)> Callback,const TOptional<FString> TimeOffsetToken) : Self(Self), Callback(Callback), QueryTimeOffsetToken(TimeOffsetToken) {}
    FGlobalRankingSeasonDomain::FSubscribeGlobalRankingsWithInitialCallTask::FSubscribeGlobalRankingsWithInitialCallTask(const FSubscribeGlobalRankingsWithInitialCallTask& From) : TGs2Future(From), Self(From.Self), Callback(From.Callback), QueryTimeOffsetToken(From.QueryTimeOffsetToken) {}
    Gs2::Core::Model::FGs2ErrorPtr FGlobalRankingSeasonDomain::FSubscribeGlobalRankingsWithInitialCallTask::Action(TSharedPtr<TSharedPtr<Gs2::Core::Domain::CallbackID>> Result)
    {
        const auto Task = Gs2::Core::Util::New<FAsyncTask<FCollectGlobalRankingsTask>>(Self, TFunction<void(TArray<Gs2::Ranking2::Model::FGlobalRankingDataPtr>)>(), QueryTimeOffsetToken);
        Task->StartSynchronousTask(); Task->EnsureCompletion();
        if (Task->GetTask().IsError()) return Task->GetTask().Error();
        const auto Values = Task->GetTask().Result();
        const auto CallbackId = Self->SubscribeGlobalRankings(Callback, QueryTimeOffsetToken);
        Callback(*Values); *Result = MakeShared<Gs2::Core::Domain::CallbackID>(CallbackId);
        return nullptr;
    }
    TSharedPtr<FAsyncTask<FGlobalRankingSeasonDomain::FSubscribeGlobalRankingsWithInitialCallTask>> FGlobalRankingSeasonDomain::SubscribeGlobalRankingsWithInitialCall(TFunction<void(TArray<Gs2::Ranking2::Model::FGlobalRankingDataPtr>)> Callback,const TOptional<FString> TimeOffsetToken)
    {
        return Gs2::Core::Util::New<FAsyncTask<FSubscribeGlobalRankingsWithInitialCallTask>>(this->AsShared(), Callback, TimeOffsetToken);
    }

    TSharedPtr<Gs2::Ranking2::Domain::Model::FGlobalRankingDataDomain> FGlobalRankingSeasonDomain::GlobalRankingData(
        const TOptional<FString> ScorerUserId
    )
    {
        return MakeShared<Gs2::Ranking2::Domain::Model::FGlobalRankingDataDomain>(
            Gs2,
            Service,
            NamespaceName,
            RankingName,
            Season,
            UserId,
            ScorerUserId
        );
    }

    Gs2::Ranking2::Domain::Iterator::FDescribeGlobalRankingReceivedRewardsByUserIdIteratorPtr FGlobalRankingSeasonDomain::GlobalRankingReceivedRewards(
        const TOptional<FString> TimeOffsetToken
    ) const
    {
        return MakeShared<Gs2::Ranking2::Domain::Iterator::FDescribeGlobalRankingReceivedRewardsByUserIdIterator>(
            Gs2,
            Client,
            NamespaceName,
            UserId,
            RankingName,
            Season,
            TimeOffsetToken
        );
    }

    Gs2::Core::Domain::CallbackID FGlobalRankingSeasonDomain::SubscribeGlobalRankingReceivedRewards(
    TFunction<void()> Callback
    )
    {
        return Gs2->Cache->ListSubscribe(
            Gs2::Ranking2::Model::FGlobalRankingReceivedReward::TypeName,
            Gs2::Ranking2::Model::Cache::FGlobalRankingReceivedRewardCache::CreateCacheParentKey(
                NamespaceName,
                UserId,
                RankingName,
                TOptional<int32>()
            ),
            Callback,
            Callback
        );
    }
    void FGlobalRankingSeasonDomain::UnsubscribeGlobalRankingReceivedRewards(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        Gs2->Cache->ListUnsubscribe(
            Gs2::Ranking2::Model::FGlobalRankingReceivedReward::TypeName,
            Gs2::Ranking2::Model::Cache::FGlobalRankingReceivedRewardCache::CreateCacheParentKey(
                NamespaceName,
                UserId,
                RankingName,
                TOptional<int32>()
            ),
            CallbackID
        );
    }
    class FGlobalRankingSeasonDomain::FCollectGlobalRankingReceivedRewardsTask : public Gs2::Core::Util::TGs2Future<TArray<Gs2::Ranking2::Model::FGlobalRankingReceivedRewardPtr>>, public TSharedFromThis<FCollectGlobalRankingReceivedRewardsTask>
    {
        const TSharedPtr<FGlobalRankingSeasonDomain> Self;
        const TFunction<void(TArray<Gs2::Ranking2::Model::FGlobalRankingReceivedRewardPtr>)> OnCollected;
    const TOptional<FString> QueryTimeOffsetToken;
    public:
        explicit FCollectGlobalRankingReceivedRewardsTask(const TSharedPtr<FGlobalRankingSeasonDomain>& Self, TFunction<void(TArray<Gs2::Ranking2::Model::FGlobalRankingReceivedRewardPtr>)> OnCollected,const TOptional<FString> TimeOffsetToken) : Self(Self), OnCollected(OnCollected), QueryTimeOffsetToken(TimeOffsetToken) {}
        FCollectGlobalRankingReceivedRewardsTask(const FCollectGlobalRankingReceivedRewardsTask& From) : TGs2Future(From), Self(From.Self), OnCollected(From.OnCollected), QueryTimeOffsetToken(From.QueryTimeOffsetToken) {}
        virtual Gs2::Core::Model::FGs2ErrorPtr Action(TSharedPtr<TSharedPtr<TArray<Gs2::Ranking2::Model::FGlobalRankingReceivedRewardPtr>>> Result) override
        {
            TArray<Gs2::Ranking2::Model::FGlobalRankingReceivedRewardPtr> Items;
            auto Iterator = Self->GlobalRankingReceivedRewards(QueryTimeOffsetToken)->begin();
            while (Iterator.HasNext())
            {
                if (Iterator.IsError()) return Iterator.Error();
                if (Iterator.IsCurrentValid()) Items.Add(Iterator.Current());
                ++Iterator;
            }
            if (Iterator.IsError()) return Iterator.Error();
            *Result = MakeShared<TArray<Gs2::Ranking2::Model::FGlobalRankingReceivedRewardPtr>>(Items);
            if (OnCollected) OnCollected(Items);
            return nullptr;
        }
    };

    Gs2::Core::Domain::CallbackID FGlobalRankingSeasonDomain::SubscribeGlobalRankingReceivedRewards(
        TFunction<void(TArray<Gs2::Ranking2::Model::FGlobalRankingReceivedRewardPtr>)> Callback,const TOptional<FString> TimeOffsetToken
    )
    {
        const TWeakPtr<Gs2::Core::Domain::FGs2> WeakGs2 = this->Gs2;
        const TWeakPtr<Ranking2::Domain::FGs2Ranking2Domain> WeakService = this->Service;
        const auto QueryNamespaceName = NamespaceName;
        const auto QueryRankingName = RankingName;
        const auto QuerySeason = Season;
        const auto QueryUserId = UserId;
        const auto QueryTimeOffsetToken = TimeOffsetToken;
        const auto Parent = Gs2::Ranking2::Model::Cache::FGlobalRankingReceivedRewardCache::CreateCacheParentKey(
        NamespaceName,
        UserId,
        RankingName,
        TOptional<int32>()
    );
        return Gs2->Cache->ListSubscribeTyped(
            Gs2::Ranking2::Model::FGlobalRankingReceivedReward::TypeName,
            Parent,
            [Callback, WeakGs2](const TArray<FGs2ObjectPtr>& Values)
            {
                if (!WeakGs2.Pin().IsValid()) return;
                TArray<Gs2::Ranking2::Model::FGlobalRankingReceivedRewardPtr> TypedValues;
                for (const auto& Value : Values) if (Value.IsValid()) TypedValues.Add(StaticCastSharedPtr<Gs2::Ranking2::Model::FGlobalRankingReceivedReward>(Value));
                Callback(TypedValues);
            },
            [WeakGs2, WeakService, Callback, QueryNamespaceName, QueryRankingName, QuerySeason, QueryUserId, QueryTimeOffsetToken]()
            {
                const auto Owner = WeakGs2.Pin();
                if (!Owner.IsValid()) return;
                const auto Domain = MakeShared<FGlobalRankingSeasonDomain>(Owner, WeakService.Pin(), QueryNamespaceName, QueryRankingName, QuerySeason, QueryUserId);
                const auto Task = Gs2::Core::Util::New<FAsyncTask<FCollectGlobalRankingReceivedRewardsTask>>(Domain, Callback, QueryTimeOffsetToken);
                Task->StartBackgroundTask();
            }
        );
    }

    void FGlobalRankingSeasonDomain::InvalidateGlobalRankingReceivedRewards(const TOptional<FString> TimeOffsetToken)
    {
        Gs2->Cache->ClearListCache(
            Gs2::Ranking2::Model::FGlobalRankingReceivedReward::TypeName,
            Gs2::Ranking2::Model::Cache::FGlobalRankingReceivedRewardCache::CreateCacheParentKey(
        NamespaceName,
        UserId,
        RankingName,
        TOptional<int32>()
    )
        );
    }

    FGlobalRankingSeasonDomain::FSubscribeGlobalRankingReceivedRewardsWithInitialCallTask::FSubscribeGlobalRankingReceivedRewardsWithInitialCallTask(const TSharedPtr<FGlobalRankingSeasonDomain>& Self, TFunction<void(TArray<Gs2::Ranking2::Model::FGlobalRankingReceivedRewardPtr>)> Callback,const TOptional<FString> TimeOffsetToken) : Self(Self), Callback(Callback), QueryTimeOffsetToken(TimeOffsetToken) {}
    FGlobalRankingSeasonDomain::FSubscribeGlobalRankingReceivedRewardsWithInitialCallTask::FSubscribeGlobalRankingReceivedRewardsWithInitialCallTask(const FSubscribeGlobalRankingReceivedRewardsWithInitialCallTask& From) : TGs2Future(From), Self(From.Self), Callback(From.Callback), QueryTimeOffsetToken(From.QueryTimeOffsetToken) {}
    Gs2::Core::Model::FGs2ErrorPtr FGlobalRankingSeasonDomain::FSubscribeGlobalRankingReceivedRewardsWithInitialCallTask::Action(TSharedPtr<TSharedPtr<Gs2::Core::Domain::CallbackID>> Result)
    {
        const auto Task = Gs2::Core::Util::New<FAsyncTask<FCollectGlobalRankingReceivedRewardsTask>>(Self, TFunction<void(TArray<Gs2::Ranking2::Model::FGlobalRankingReceivedRewardPtr>)>(), QueryTimeOffsetToken);
        Task->StartSynchronousTask(); Task->EnsureCompletion();
        if (Task->GetTask().IsError()) return Task->GetTask().Error();
        const auto Values = Task->GetTask().Result();
        const auto CallbackId = Self->SubscribeGlobalRankingReceivedRewards(Callback, QueryTimeOffsetToken);
        Callback(*Values); *Result = MakeShared<Gs2::Core::Domain::CallbackID>(CallbackId);
        return nullptr;
    }
    TSharedPtr<FAsyncTask<FGlobalRankingSeasonDomain::FSubscribeGlobalRankingReceivedRewardsWithInitialCallTask>> FGlobalRankingSeasonDomain::SubscribeGlobalRankingReceivedRewardsWithInitialCall(TFunction<void(TArray<Gs2::Ranking2::Model::FGlobalRankingReceivedRewardPtr>)> Callback,const TOptional<FString> TimeOffsetToken)
    {
        return Gs2::Core::Util::New<FAsyncTask<FSubscribeGlobalRankingReceivedRewardsWithInitialCallTask>>(this->AsShared(), Callback, TimeOffsetToken);
    }

    TSharedPtr<Gs2::Ranking2::Domain::Model::FGlobalRankingReceivedRewardDomain> FGlobalRankingSeasonDomain::GlobalRankingReceivedReward(
    )
    {
        return MakeShared<Gs2::Ranking2::Domain::Model::FGlobalRankingReceivedRewardDomain>(
            Gs2,
            Service,
            NamespaceName,
            RankingName,
            Season,
            UserId
        );
    }

    FString FGlobalRankingSeasonDomain::CreateCacheParentKey(
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

    FString FGlobalRankingSeasonDomain::CreateCacheKey(
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

