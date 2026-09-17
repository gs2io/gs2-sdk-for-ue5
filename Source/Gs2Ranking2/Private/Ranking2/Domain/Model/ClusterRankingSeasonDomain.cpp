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

#include "Ranking2/Domain/Model/ClusterRankingSeason.h"
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

#include "Ranking2/Model/Cache/ClusterRankingReceivedReward.h"
#include "Ranking2/Model/Cache/ClusterRankingScore.h"
#include "Ranking2/Model/Cache/ClusterRankingData.h"
#include "Core/Domain/Gs2.h"
#include "Core/Domain/Transaction/JobQueueJobDomainFactory.h"
#include "Core/Domain/Transaction/InternalTransactionDomainFactory.h"
#include "Core/Domain/Transaction/ManualTransactionDomain.h"

namespace Gs2::Ranking2::Domain::Model
{

    FClusterRankingSeasonDomain::FClusterRankingSeasonDomain(
        const Core::Domain::FGs2Ptr& Gs2,
        const Ranking2::Domain::FGs2Ranking2DomainPtr& Service,
        const TOptional<FString> NamespaceName,
        const TOptional<FString> RankingName,
        const TOptional<FString> ClusterName,
        const TOptional<int64> Season,
        const TOptional<FString> UserId
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Gs2(Gs2),
        Service(Service),
        Client(MakeShared<Gs2::Ranking2::FGs2Ranking2RestClient>(Gs2->RestSession)),
        NamespaceName(NamespaceName),
        RankingName(RankingName),
        ClusterName(ClusterName),
        Season(Season),
        UserId(UserId),
        ParentKey(Gs2::Ranking2::Domain::Model::FClusterRankingModelDomain::CreateCacheParentKey(
            NamespaceName,
            RankingName,
            "ClusterRankingSeason"
        ))
    {
    }

    FClusterRankingSeasonDomain::FClusterRankingSeasonDomain(
        const FClusterRankingSeasonDomain& From
    ):
        Gs2(From.Gs2),
        Service(From.Service),
        Client(From.Client),
        NamespaceName(From.NamespaceName),
        RankingName(From.RankingName),
        ClusterName(From.ClusterName),
        Season(From.Season),
        UserId(From.UserId),
        ParentKey(From.ParentKey)
    {

    }

    FClusterRankingSeasonDomain::FGetClusterRankingTask::FGetClusterRankingTask(
        const TSharedPtr<FClusterRankingSeasonDomain>& Self,
        const Request::FGetClusterRankingByUserIdRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FClusterRankingSeasonDomain::FGetClusterRankingTask::FGetClusterRankingTask(
        const FGetClusterRankingTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FClusterRankingSeasonDomain::FGetClusterRankingTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Ranking2::Domain::Model::FClusterRankingDataDomain>> Result
    )
    {
        Request
            ->WithContextStack(Self->Gs2->DefaultContextStack)
            ->WithNamespaceName(Self->NamespaceName)
            ->WithRankingName(Self->RankingName)
            ->WithClusterName(Self->ClusterName)
            ->WithUserId(Self->UserId)
            ->WithSeason(Self->Season);
        const auto Future = Self->Client->GetClusterRankingByUserId(
            Request
        );
        Future->StartSynchronousTask();
        if (Future->GetTask().IsError())
        {
            return Future->GetTask().Error();
        }
        const auto ResultModel = Future->GetTask().Result();
        Future->EnsureCompletion();
        if (ResultModel->GetItem() != nullptr)
        {
            const auto ParentKey = Gs2::Ranking2::Domain::Model::FClusterRankingSeasonDomain::CreateCacheParentKey(
                Request->GetNamespaceName(),
                ResultModel->GetItem()->GetRankingName(),
                ResultModel->GetItem()->GetClusterName(),
                ResultModel->GetItem()->GetSeason(),
                TEXT("ClusterRankingData")
            );
            const auto Key = Gs2::Ranking2::Domain::Model::FClusterRankingDataDomain::CreateCacheKey(
                ResultModel->GetItem()->GetUserId()
            );
            Self->Gs2->Cache->Put(
                Gs2::Ranking2::Model::FClusterRankingData::TypeName,
                ParentKey,
                Key,
                ResultModel->GetItem(),
                FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
            );
        }
        auto Domain = MakeShared<Gs2::Ranking2::Domain::Model::FClusterRankingDataDomain>(
            Self->Gs2,
            Self->Service,
            Request->GetNamespaceName(),
            ResultModel->GetItem()->GetRankingName(),
            ResultModel->GetItem()->GetClusterName(),
            ResultModel->GetItem()->GetSeason(),
            ResultModel->GetItem()->GetUserId(),
            ResultModel->GetItem()->GetUserId()
        );

        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FClusterRankingSeasonDomain::FGetClusterRankingTask>> FClusterRankingSeasonDomain::GetClusterRanking(
        Request::FGetClusterRankingByUserIdRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FGetClusterRankingTask>>(this->AsShared(), Request);
    }

    FClusterRankingSeasonDomain::FPutClusterRankingScoreTask::FPutClusterRankingScoreTask(
        const TSharedPtr<FClusterRankingSeasonDomain>& Self,
        const Request::FPutClusterRankingScoreByUserIdRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FClusterRankingSeasonDomain::FPutClusterRankingScoreTask::FPutClusterRankingScoreTask(
        const FPutClusterRankingScoreTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FClusterRankingSeasonDomain::FPutClusterRankingScoreTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Ranking2::Domain::Model::FClusterRankingScoreDomain>> Result
    )
    {
        Request
            ->WithContextStack(Self->Gs2->DefaultContextStack)
            ->WithNamespaceName(Self->NamespaceName)
            ->WithRankingName(Self->RankingName)
            ->WithClusterName(Self->ClusterName)
            ->WithUserId(Self->UserId);
        const auto Future = Self->Client->PutClusterRankingScoreByUserId(
            Request
        );
        Future->StartSynchronousTask();
        if (Future->GetTask().IsError())
        {
            return Future->GetTask().Error();
        }
        const auto ResultModel = Future->GetTask().Result();
        Future->EnsureCompletion();
        auto Domain = MakeShared<Gs2::Ranking2::Domain::Model::FClusterRankingScoreDomain>(
            Self->Gs2,
            Self->Service,
            Request->GetNamespaceName(),
            ResultModel->GetItem()->GetRankingName(),
            ResultModel->GetItem()->GetClusterName(),
            ResultModel->GetItem()->GetSeason(),
            ResultModel->GetItem()->GetUserId()
        );

        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FClusterRankingSeasonDomain::FPutClusterRankingScoreTask>> FClusterRankingSeasonDomain::PutClusterRankingScore(
        Request::FPutClusterRankingScoreByUserIdRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FPutClusterRankingScoreTask>>(this->AsShared(), Request);
    }

    Gs2::Ranking2::Domain::Iterator::FDescribeClusterRankingsByUserIdIteratorPtr FClusterRankingSeasonDomain::ClusterRankings(
        const TOptional<FString> TimeOffsetToken
    ) const
    {
        return MakeShared<Gs2::Ranking2::Domain::Iterator::FDescribeClusterRankingsByUserIdIterator>(
            Gs2,
            Client,
            NamespaceName,
            UserId,
            RankingName,
            ClusterName,
            Season,
            TimeOffsetToken
        );
    }

    Gs2::Core::Domain::CallbackID FClusterRankingSeasonDomain::SubscribeClusterRankings(
    TFunction<void()> Callback
    )
    {
        return Gs2->Cache->ListSubscribe(
            Gs2::Ranking2::Model::FClusterRankingData::TypeName,
            Gs2::Ranking2::Model::Cache::FClusterRankingDataCache::CreateCacheParentKey(
                NamespaceName,
                RankingName,
                ClusterName,
                Season,
                TOptional<int32>()
            ),
            Callback,
            Callback
        );
    }
    void FClusterRankingSeasonDomain::UnsubscribeClusterRankings(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        Gs2->Cache->ListUnsubscribe(
            Gs2::Ranking2::Model::FClusterRankingData::TypeName,
            Gs2::Ranking2::Model::Cache::FClusterRankingDataCache::CreateCacheParentKey(
                NamespaceName,
                RankingName,
                ClusterName,
                Season,
                TOptional<int32>()
            ),
            CallbackID
        );
    }
    class FClusterRankingSeasonDomain::FCollectClusterRankingsTask : public Gs2::Core::Util::TGs2Future<TArray<Gs2::Ranking2::Model::FClusterRankingDataPtr>>, public TSharedFromThis<FCollectClusterRankingsTask>
    {
        const TSharedPtr<FClusterRankingSeasonDomain> Self;
        const TFunction<void(TArray<Gs2::Ranking2::Model::FClusterRankingDataPtr>)> OnCollected;
    const TOptional<FString> QueryTimeOffsetToken;
    public:
        explicit FCollectClusterRankingsTask(const TSharedPtr<FClusterRankingSeasonDomain>& Self, TFunction<void(TArray<Gs2::Ranking2::Model::FClusterRankingDataPtr>)> OnCollected,const TOptional<FString> TimeOffsetToken) : Self(Self), OnCollected(OnCollected), QueryTimeOffsetToken(TimeOffsetToken) {}
        FCollectClusterRankingsTask(const FCollectClusterRankingsTask& From) : TGs2Future(From), Self(From.Self), OnCollected(From.OnCollected), QueryTimeOffsetToken(From.QueryTimeOffsetToken) {}
        virtual Gs2::Core::Model::FGs2ErrorPtr Action(TSharedPtr<TSharedPtr<TArray<Gs2::Ranking2::Model::FClusterRankingDataPtr>>> Result) override
        {
            TArray<Gs2::Ranking2::Model::FClusterRankingDataPtr> Items;
            auto Iterator = Self->ClusterRankings(QueryTimeOffsetToken)->begin();
            while (Iterator.HasNext())
            {
                if (Iterator.IsError()) return Iterator.Error();
                if (Iterator.IsCurrentValid()) Items.Add(Iterator.Current());
                ++Iterator;
            }
            if (Iterator.IsError()) return Iterator.Error();
            *Result = MakeShared<TArray<Gs2::Ranking2::Model::FClusterRankingDataPtr>>(Items);
            if (OnCollected) OnCollected(Items);
            return nullptr;
        }
    };

    Gs2::Core::Domain::CallbackID FClusterRankingSeasonDomain::SubscribeClusterRankings(
        TFunction<void(TArray<Gs2::Ranking2::Model::FClusterRankingDataPtr>)> Callback,const TOptional<FString> TimeOffsetToken
    )
    {
        const TWeakPtr<Gs2::Core::Domain::FGs2> WeakGs2 = this->Gs2;
        const TWeakPtr<Ranking2::Domain::FGs2Ranking2Domain> WeakService = this->Service;
        const auto QueryNamespaceName = NamespaceName;
        const auto QueryRankingName = RankingName;
        const auto QueryClusterName = ClusterName;
        const auto QuerySeason = Season;
        const auto QueryUserId = UserId;
        const auto QueryTimeOffsetToken = TimeOffsetToken;
        const auto Parent = Gs2::Ranking2::Model::Cache::FClusterRankingDataCache::CreateCacheParentKey(
        NamespaceName,
        RankingName,
        ClusterName,
        Season,
        TOptional<int32>()
    );
        return Gs2->Cache->ListSubscribeTyped(
            Gs2::Ranking2::Model::FClusterRankingData::TypeName,
            Parent,
            [Callback, WeakGs2](const TArray<FGs2ObjectPtr>& Values)
            {
                if (!WeakGs2.Pin().IsValid()) return;
                TArray<Gs2::Ranking2::Model::FClusterRankingDataPtr> TypedValues;
                for (const auto& Value : Values) if (Value.IsValid()) TypedValues.Add(StaticCastSharedPtr<Gs2::Ranking2::Model::FClusterRankingData>(Value));
                Callback(TypedValues);
            },
            [WeakGs2, WeakService, Callback, QueryNamespaceName, QueryRankingName, QueryClusterName, QuerySeason, QueryUserId, QueryTimeOffsetToken]()
            {
                const auto Owner = WeakGs2.Pin();
                if (!Owner.IsValid()) return;
                const auto Domain = MakeShared<FClusterRankingSeasonDomain>(Owner, WeakService.Pin(), QueryNamespaceName, QueryRankingName, QueryClusterName, QuerySeason, QueryUserId);
                const auto Task = Gs2::Core::Util::New<FAsyncTask<FCollectClusterRankingsTask>>(Domain, Callback, QueryTimeOffsetToken);
                Task->StartBackgroundTask();
            }
        );
    }

    void FClusterRankingSeasonDomain::InvalidateClusterRankings(const TOptional<FString> TimeOffsetToken)
    {
        Gs2->Cache->ClearListCache(
            Gs2::Ranking2::Model::FClusterRankingData::TypeName,
            Gs2::Ranking2::Model::Cache::FClusterRankingDataCache::CreateCacheParentKey(
        NamespaceName,
        RankingName,
        ClusterName,
        Season,
        TOptional<int32>()
    )
        );
    }

    FClusterRankingSeasonDomain::FSubscribeClusterRankingsWithInitialCallTask::FSubscribeClusterRankingsWithInitialCallTask(const TSharedPtr<FClusterRankingSeasonDomain>& Self, TFunction<void(TArray<Gs2::Ranking2::Model::FClusterRankingDataPtr>)> Callback,const TOptional<FString> TimeOffsetToken) : Self(Self), Callback(Callback), QueryTimeOffsetToken(TimeOffsetToken) {}
    FClusterRankingSeasonDomain::FSubscribeClusterRankingsWithInitialCallTask::FSubscribeClusterRankingsWithInitialCallTask(const FSubscribeClusterRankingsWithInitialCallTask& From) : TGs2Future(From), Self(From.Self), Callback(From.Callback), QueryTimeOffsetToken(From.QueryTimeOffsetToken) {}
    Gs2::Core::Model::FGs2ErrorPtr FClusterRankingSeasonDomain::FSubscribeClusterRankingsWithInitialCallTask::Action(TSharedPtr<TSharedPtr<Gs2::Core::Domain::CallbackID>> Result)
    {
        const auto Task = Gs2::Core::Util::New<FAsyncTask<FCollectClusterRankingsTask>>(Self, TFunction<void(TArray<Gs2::Ranking2::Model::FClusterRankingDataPtr>)>(), QueryTimeOffsetToken);
        Task->StartSynchronousTask(); Task->EnsureCompletion();
        if (Task->GetTask().IsError()) return Task->GetTask().Error();
        const auto Values = Task->GetTask().Result();
        const auto CallbackId = Self->SubscribeClusterRankings(Callback, QueryTimeOffsetToken);
        Callback(*Values); *Result = MakeShared<Gs2::Core::Domain::CallbackID>(CallbackId);
        return nullptr;
    }
    TSharedPtr<FAsyncTask<FClusterRankingSeasonDomain::FSubscribeClusterRankingsWithInitialCallTask>> FClusterRankingSeasonDomain::SubscribeClusterRankingsWithInitialCall(TFunction<void(TArray<Gs2::Ranking2::Model::FClusterRankingDataPtr>)> Callback,const TOptional<FString> TimeOffsetToken)
    {
        return Gs2::Core::Util::New<FAsyncTask<FSubscribeClusterRankingsWithInitialCallTask>>(this->AsShared(), Callback, TimeOffsetToken);
    }

    TSharedPtr<Gs2::Ranking2::Domain::Model::FClusterRankingDataDomain> FClusterRankingSeasonDomain::ClusterRankingData(
        const TOptional<FString> ScorerUserId
    )
    {
        return MakeShared<Gs2::Ranking2::Domain::Model::FClusterRankingDataDomain>(
            Gs2,
            Service,
            NamespaceName,
            RankingName,
            ClusterName,
            Season,
            UserId,
            ScorerUserId
        );
    }

    Gs2::Ranking2::Domain::Iterator::FDescribeClusterRankingReceivedRewardsByUserIdIteratorPtr FClusterRankingSeasonDomain::ClusterRankingReceivedRewards(
        const TOptional<FString> TimeOffsetToken
    ) const
    {
        return MakeShared<Gs2::Ranking2::Domain::Iterator::FDescribeClusterRankingReceivedRewardsByUserIdIterator>(
            Gs2,
            Client,
            NamespaceName,
            UserId,
            RankingName,
            ClusterName,
            Season,
            TimeOffsetToken
        );
    }

    Gs2::Core::Domain::CallbackID FClusterRankingSeasonDomain::SubscribeClusterRankingReceivedRewards(
    TFunction<void()> Callback
    )
    {
        return Gs2->Cache->ListSubscribe(
            Gs2::Ranking2::Model::FClusterRankingReceivedReward::TypeName,
            Gs2::Ranking2::Model::Cache::FClusterRankingReceivedRewardCache::CreateCacheParentKey(
                NamespaceName,
                UserId,
                RankingName,
                TOptional<int32>()
            ),
            Callback,
            Callback
        );
    }
    void FClusterRankingSeasonDomain::UnsubscribeClusterRankingReceivedRewards(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        Gs2->Cache->ListUnsubscribe(
            Gs2::Ranking2::Model::FClusterRankingReceivedReward::TypeName,
            Gs2::Ranking2::Model::Cache::FClusterRankingReceivedRewardCache::CreateCacheParentKey(
                NamespaceName,
                UserId,
                RankingName,
                TOptional<int32>()
            ),
            CallbackID
        );
    }
    class FClusterRankingSeasonDomain::FCollectClusterRankingReceivedRewardsTask : public Gs2::Core::Util::TGs2Future<TArray<Gs2::Ranking2::Model::FClusterRankingReceivedRewardPtr>>, public TSharedFromThis<FCollectClusterRankingReceivedRewardsTask>
    {
        const TSharedPtr<FClusterRankingSeasonDomain> Self;
        const TFunction<void(TArray<Gs2::Ranking2::Model::FClusterRankingReceivedRewardPtr>)> OnCollected;
    const TOptional<FString> QueryTimeOffsetToken;
    public:
        explicit FCollectClusterRankingReceivedRewardsTask(const TSharedPtr<FClusterRankingSeasonDomain>& Self, TFunction<void(TArray<Gs2::Ranking2::Model::FClusterRankingReceivedRewardPtr>)> OnCollected,const TOptional<FString> TimeOffsetToken) : Self(Self), OnCollected(OnCollected), QueryTimeOffsetToken(TimeOffsetToken) {}
        FCollectClusterRankingReceivedRewardsTask(const FCollectClusterRankingReceivedRewardsTask& From) : TGs2Future(From), Self(From.Self), OnCollected(From.OnCollected), QueryTimeOffsetToken(From.QueryTimeOffsetToken) {}
        virtual Gs2::Core::Model::FGs2ErrorPtr Action(TSharedPtr<TSharedPtr<TArray<Gs2::Ranking2::Model::FClusterRankingReceivedRewardPtr>>> Result) override
        {
            TArray<Gs2::Ranking2::Model::FClusterRankingReceivedRewardPtr> Items;
            auto Iterator = Self->ClusterRankingReceivedRewards(QueryTimeOffsetToken)->begin();
            while (Iterator.HasNext())
            {
                if (Iterator.IsError()) return Iterator.Error();
                if (Iterator.IsCurrentValid()) Items.Add(Iterator.Current());
                ++Iterator;
            }
            if (Iterator.IsError()) return Iterator.Error();
            *Result = MakeShared<TArray<Gs2::Ranking2::Model::FClusterRankingReceivedRewardPtr>>(Items);
            if (OnCollected) OnCollected(Items);
            return nullptr;
        }
    };

    Gs2::Core::Domain::CallbackID FClusterRankingSeasonDomain::SubscribeClusterRankingReceivedRewards(
        TFunction<void(TArray<Gs2::Ranking2::Model::FClusterRankingReceivedRewardPtr>)> Callback,const TOptional<FString> TimeOffsetToken
    )
    {
        const TWeakPtr<Gs2::Core::Domain::FGs2> WeakGs2 = this->Gs2;
        const TWeakPtr<Ranking2::Domain::FGs2Ranking2Domain> WeakService = this->Service;
        const auto QueryNamespaceName = NamespaceName;
        const auto QueryRankingName = RankingName;
        const auto QueryClusterName = ClusterName;
        const auto QuerySeason = Season;
        const auto QueryUserId = UserId;
        const auto QueryTimeOffsetToken = TimeOffsetToken;
        const auto Parent = Gs2::Ranking2::Model::Cache::FClusterRankingReceivedRewardCache::CreateCacheParentKey(
        NamespaceName,
        UserId,
        RankingName,
        TOptional<int32>()
    );
        return Gs2->Cache->ListSubscribeTyped(
            Gs2::Ranking2::Model::FClusterRankingReceivedReward::TypeName,
            Parent,
            [Callback, WeakGs2](const TArray<FGs2ObjectPtr>& Values)
            {
                if (!WeakGs2.Pin().IsValid()) return;
                TArray<Gs2::Ranking2::Model::FClusterRankingReceivedRewardPtr> TypedValues;
                for (const auto& Value : Values) if (Value.IsValid()) TypedValues.Add(StaticCastSharedPtr<Gs2::Ranking2::Model::FClusterRankingReceivedReward>(Value));
                Callback(TypedValues);
            },
            [WeakGs2, WeakService, Callback, QueryNamespaceName, QueryRankingName, QueryClusterName, QuerySeason, QueryUserId, QueryTimeOffsetToken]()
            {
                const auto Owner = WeakGs2.Pin();
                if (!Owner.IsValid()) return;
                const auto Domain = MakeShared<FClusterRankingSeasonDomain>(Owner, WeakService.Pin(), QueryNamespaceName, QueryRankingName, QueryClusterName, QuerySeason, QueryUserId);
                const auto Task = Gs2::Core::Util::New<FAsyncTask<FCollectClusterRankingReceivedRewardsTask>>(Domain, Callback, QueryTimeOffsetToken);
                Task->StartBackgroundTask();
            }
        );
    }

    void FClusterRankingSeasonDomain::InvalidateClusterRankingReceivedRewards(const TOptional<FString> TimeOffsetToken)
    {
        Gs2->Cache->ClearListCache(
            Gs2::Ranking2::Model::FClusterRankingReceivedReward::TypeName,
            Gs2::Ranking2::Model::Cache::FClusterRankingReceivedRewardCache::CreateCacheParentKey(
        NamespaceName,
        UserId,
        RankingName,
        TOptional<int32>()
    )
        );
    }

    FClusterRankingSeasonDomain::FSubscribeClusterRankingReceivedRewardsWithInitialCallTask::FSubscribeClusterRankingReceivedRewardsWithInitialCallTask(const TSharedPtr<FClusterRankingSeasonDomain>& Self, TFunction<void(TArray<Gs2::Ranking2::Model::FClusterRankingReceivedRewardPtr>)> Callback,const TOptional<FString> TimeOffsetToken) : Self(Self), Callback(Callback), QueryTimeOffsetToken(TimeOffsetToken) {}
    FClusterRankingSeasonDomain::FSubscribeClusterRankingReceivedRewardsWithInitialCallTask::FSubscribeClusterRankingReceivedRewardsWithInitialCallTask(const FSubscribeClusterRankingReceivedRewardsWithInitialCallTask& From) : TGs2Future(From), Self(From.Self), Callback(From.Callback), QueryTimeOffsetToken(From.QueryTimeOffsetToken) {}
    Gs2::Core::Model::FGs2ErrorPtr FClusterRankingSeasonDomain::FSubscribeClusterRankingReceivedRewardsWithInitialCallTask::Action(TSharedPtr<TSharedPtr<Gs2::Core::Domain::CallbackID>> Result)
    {
        const auto Task = Gs2::Core::Util::New<FAsyncTask<FCollectClusterRankingReceivedRewardsTask>>(Self, TFunction<void(TArray<Gs2::Ranking2::Model::FClusterRankingReceivedRewardPtr>)>(), QueryTimeOffsetToken);
        Task->StartSynchronousTask(); Task->EnsureCompletion();
        if (Task->GetTask().IsError()) return Task->GetTask().Error();
        const auto Values = Task->GetTask().Result();
        const auto CallbackId = Self->SubscribeClusterRankingReceivedRewards(Callback, QueryTimeOffsetToken);
        Callback(*Values); *Result = MakeShared<Gs2::Core::Domain::CallbackID>(CallbackId);
        return nullptr;
    }
    TSharedPtr<FAsyncTask<FClusterRankingSeasonDomain::FSubscribeClusterRankingReceivedRewardsWithInitialCallTask>> FClusterRankingSeasonDomain::SubscribeClusterRankingReceivedRewardsWithInitialCall(TFunction<void(TArray<Gs2::Ranking2::Model::FClusterRankingReceivedRewardPtr>)> Callback,const TOptional<FString> TimeOffsetToken)
    {
        return Gs2::Core::Util::New<FAsyncTask<FSubscribeClusterRankingReceivedRewardsWithInitialCallTask>>(this->AsShared(), Callback, TimeOffsetToken);
    }

    TSharedPtr<Gs2::Ranking2::Domain::Model::FClusterRankingReceivedRewardDomain> FClusterRankingSeasonDomain::ClusterRankingReceivedReward(
    )
    {
        return MakeShared<Gs2::Ranking2::Domain::Model::FClusterRankingReceivedRewardDomain>(
            Gs2,
            Service,
            NamespaceName,
            RankingName,
            ClusterName,
            Season,
            UserId
        );
    }

    Gs2::Ranking2::Domain::Iterator::FDescribeClusterRankingScoresByUserIdIteratorPtr FClusterRankingSeasonDomain::ClusterRankingScores(
        const TOptional<FString> TimeOffsetToken
    ) const
    {
        return MakeShared<Gs2::Ranking2::Domain::Iterator::FDescribeClusterRankingScoresByUserIdIterator>(
            Gs2,
            Client,
            NamespaceName,
            UserId,
            RankingName,
            ClusterName,
            Season,
            TimeOffsetToken
        );
    }

    Gs2::Core::Domain::CallbackID FClusterRankingSeasonDomain::SubscribeClusterRankingScores(
    TFunction<void()> Callback
    )
    {
        return Gs2->Cache->ListSubscribe(
            Gs2::Ranking2::Model::FClusterRankingScore::TypeName,
            Gs2::Ranking2::Model::Cache::FClusterRankingScoreCache::CreateCacheParentKey(
                NamespaceName,
                UserId,
                RankingName,
                TOptional<int32>()
            ),
            Callback,
            Callback
        );
    }
    void FClusterRankingSeasonDomain::UnsubscribeClusterRankingScores(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        Gs2->Cache->ListUnsubscribe(
            Gs2::Ranking2::Model::FClusterRankingScore::TypeName,
            Gs2::Ranking2::Model::Cache::FClusterRankingScoreCache::CreateCacheParentKey(
                NamespaceName,
                UserId,
                RankingName,
                TOptional<int32>()
            ),
            CallbackID
        );
    }
    class FClusterRankingSeasonDomain::FCollectClusterRankingScoresTask : public Gs2::Core::Util::TGs2Future<TArray<Gs2::Ranking2::Model::FClusterRankingScorePtr>>, public TSharedFromThis<FCollectClusterRankingScoresTask>
    {
        const TSharedPtr<FClusterRankingSeasonDomain> Self;
        const TFunction<void(TArray<Gs2::Ranking2::Model::FClusterRankingScorePtr>)> OnCollected;
    const TOptional<FString> QueryTimeOffsetToken;
    public:
        explicit FCollectClusterRankingScoresTask(const TSharedPtr<FClusterRankingSeasonDomain>& Self, TFunction<void(TArray<Gs2::Ranking2::Model::FClusterRankingScorePtr>)> OnCollected,const TOptional<FString> TimeOffsetToken) : Self(Self), OnCollected(OnCollected), QueryTimeOffsetToken(TimeOffsetToken) {}
        FCollectClusterRankingScoresTask(const FCollectClusterRankingScoresTask& From) : TGs2Future(From), Self(From.Self), OnCollected(From.OnCollected), QueryTimeOffsetToken(From.QueryTimeOffsetToken) {}
        virtual Gs2::Core::Model::FGs2ErrorPtr Action(TSharedPtr<TSharedPtr<TArray<Gs2::Ranking2::Model::FClusterRankingScorePtr>>> Result) override
        {
            TArray<Gs2::Ranking2::Model::FClusterRankingScorePtr> Items;
            auto Iterator = Self->ClusterRankingScores(QueryTimeOffsetToken)->begin();
            while (Iterator.HasNext())
            {
                if (Iterator.IsError()) return Iterator.Error();
                if (Iterator.IsCurrentValid()) Items.Add(Iterator.Current());
                ++Iterator;
            }
            if (Iterator.IsError()) return Iterator.Error();
            *Result = MakeShared<TArray<Gs2::Ranking2::Model::FClusterRankingScorePtr>>(Items);
            if (OnCollected) OnCollected(Items);
            return nullptr;
        }
    };

    Gs2::Core::Domain::CallbackID FClusterRankingSeasonDomain::SubscribeClusterRankingScores(
        TFunction<void(TArray<Gs2::Ranking2::Model::FClusterRankingScorePtr>)> Callback,const TOptional<FString> TimeOffsetToken
    )
    {
        const TWeakPtr<Gs2::Core::Domain::FGs2> WeakGs2 = this->Gs2;
        const TWeakPtr<Ranking2::Domain::FGs2Ranking2Domain> WeakService = this->Service;
        const auto QueryNamespaceName = NamespaceName;
        const auto QueryRankingName = RankingName;
        const auto QueryClusterName = ClusterName;
        const auto QuerySeason = Season;
        const auto QueryUserId = UserId;
        const auto QueryTimeOffsetToken = TimeOffsetToken;
        const auto Parent = Gs2::Ranking2::Model::Cache::FClusterRankingScoreCache::CreateCacheParentKey(
        NamespaceName,
        UserId,
        RankingName,
        TOptional<int32>()
    );
        return Gs2->Cache->ListSubscribeTyped(
            Gs2::Ranking2::Model::FClusterRankingScore::TypeName,
            Parent,
            [Callback, WeakGs2](const TArray<FGs2ObjectPtr>& Values)
            {
                if (!WeakGs2.Pin().IsValid()) return;
                TArray<Gs2::Ranking2::Model::FClusterRankingScorePtr> TypedValues;
                for (const auto& Value : Values) if (Value.IsValid()) TypedValues.Add(StaticCastSharedPtr<Gs2::Ranking2::Model::FClusterRankingScore>(Value));
                Callback(TypedValues);
            },
            [WeakGs2, WeakService, Callback, QueryNamespaceName, QueryRankingName, QueryClusterName, QuerySeason, QueryUserId, QueryTimeOffsetToken]()
            {
                const auto Owner = WeakGs2.Pin();
                if (!Owner.IsValid()) return;
                const auto Domain = MakeShared<FClusterRankingSeasonDomain>(Owner, WeakService.Pin(), QueryNamespaceName, QueryRankingName, QueryClusterName, QuerySeason, QueryUserId);
                const auto Task = Gs2::Core::Util::New<FAsyncTask<FCollectClusterRankingScoresTask>>(Domain, Callback, QueryTimeOffsetToken);
                Task->StartBackgroundTask();
            }
        );
    }

    void FClusterRankingSeasonDomain::InvalidateClusterRankingScores(const TOptional<FString> TimeOffsetToken)
    {
        Gs2->Cache->ClearListCache(
            Gs2::Ranking2::Model::FClusterRankingScore::TypeName,
            Gs2::Ranking2::Model::Cache::FClusterRankingScoreCache::CreateCacheParentKey(
        NamespaceName,
        UserId,
        RankingName,
        TOptional<int32>()
    )
        );
    }

    FClusterRankingSeasonDomain::FSubscribeClusterRankingScoresWithInitialCallTask::FSubscribeClusterRankingScoresWithInitialCallTask(const TSharedPtr<FClusterRankingSeasonDomain>& Self, TFunction<void(TArray<Gs2::Ranking2::Model::FClusterRankingScorePtr>)> Callback,const TOptional<FString> TimeOffsetToken) : Self(Self), Callback(Callback), QueryTimeOffsetToken(TimeOffsetToken) {}
    FClusterRankingSeasonDomain::FSubscribeClusterRankingScoresWithInitialCallTask::FSubscribeClusterRankingScoresWithInitialCallTask(const FSubscribeClusterRankingScoresWithInitialCallTask& From) : TGs2Future(From), Self(From.Self), Callback(From.Callback), QueryTimeOffsetToken(From.QueryTimeOffsetToken) {}
    Gs2::Core::Model::FGs2ErrorPtr FClusterRankingSeasonDomain::FSubscribeClusterRankingScoresWithInitialCallTask::Action(TSharedPtr<TSharedPtr<Gs2::Core::Domain::CallbackID>> Result)
    {
        const auto Task = Gs2::Core::Util::New<FAsyncTask<FCollectClusterRankingScoresTask>>(Self, TFunction<void(TArray<Gs2::Ranking2::Model::FClusterRankingScorePtr>)>(), QueryTimeOffsetToken);
        Task->StartSynchronousTask(); Task->EnsureCompletion();
        if (Task->GetTask().IsError()) return Task->GetTask().Error();
        const auto Values = Task->GetTask().Result();
        const auto CallbackId = Self->SubscribeClusterRankingScores(Callback, QueryTimeOffsetToken);
        Callback(*Values); *Result = MakeShared<Gs2::Core::Domain::CallbackID>(CallbackId);
        return nullptr;
    }
    TSharedPtr<FAsyncTask<FClusterRankingSeasonDomain::FSubscribeClusterRankingScoresWithInitialCallTask>> FClusterRankingSeasonDomain::SubscribeClusterRankingScoresWithInitialCall(TFunction<void(TArray<Gs2::Ranking2::Model::FClusterRankingScorePtr>)> Callback,const TOptional<FString> TimeOffsetToken)
    {
        return Gs2::Core::Util::New<FAsyncTask<FSubscribeClusterRankingScoresWithInitialCallTask>>(this->AsShared(), Callback, TimeOffsetToken);
    }

    TSharedPtr<Gs2::Ranking2::Domain::Model::FClusterRankingScoreDomain> FClusterRankingSeasonDomain::ClusterRankingScore(
    )
    {
        return MakeShared<Gs2::Ranking2::Domain::Model::FClusterRankingScoreDomain>(
            Gs2,
            Service,
            NamespaceName,
            RankingName,
            ClusterName,
            Season,
            UserId
        );
    }

    FString FClusterRankingSeasonDomain::CreateCacheParentKey(
        TOptional<FString> NamespaceName,
        TOptional<FString> RankingName,
        TOptional<FString> ClusterName,
        TOptional<int64> Season,
        FString ChildType
    )
    {
        return FString("") +
            (NamespaceName.IsSet() ? *NamespaceName : "null") + ":" +
            (RankingName.IsSet() ? *RankingName : "null") + ":" +
            (ClusterName.IsSet() ? *ClusterName : "null") + ":" +
            (Season.IsSet() ? FString::FromInt(*Season) : "null") + ":" +
            ChildType;
    }

    FString FClusterRankingSeasonDomain::CreateCacheKey(
        TOptional<FString> ClusterName,
        TOptional<int64> Season
    )
    {
        return FString("") +
            (ClusterName.IsSet() ? *ClusterName : "null") + ":" + 
            (Season.IsSet() ? FString::FromInt(*Season) : "null");
    }
}

#if defined(_MSC_VER)
#pragma warning (pop)
#elif defined(__clang__)
#pragma clang diagnostic pop
#endif

