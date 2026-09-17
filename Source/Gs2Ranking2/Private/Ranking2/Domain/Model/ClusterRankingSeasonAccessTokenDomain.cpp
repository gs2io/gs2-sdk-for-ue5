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

#include "Ranking2/Domain/Model/ClusterRankingSeasonAccessToken.h"
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
#include "Core/Domain/Transaction/ManualTransactionAccessTokenDomain.h"

namespace Gs2::Ranking2::Domain::Model
{

    FClusterRankingSeasonAccessTokenDomain::FClusterRankingSeasonAccessTokenDomain(
        const Core::Domain::FGs2Ptr& Gs2,
        const Ranking2::Domain::FGs2Ranking2DomainPtr& Service,
        const TOptional<FString> NamespaceName,
        const TOptional<FString> RankingName,
        const TOptional<FString> ClusterName,
        const TOptional<int64> Season,
        const Gs2::Auth::Model::FAccessTokenPtr& AccessToken
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Gs2(Gs2),
        Service(Service),
        Client(MakeShared<Gs2::Ranking2::FGs2Ranking2RestClient>(Gs2->RestSession)),
        NamespaceName(NamespaceName),
        RankingName(RankingName),
        ClusterName(ClusterName),
        Season(Season),
        AccessToken(AccessToken),
        ParentKey(Gs2::Ranking2::Domain::Model::FClusterRankingModelDomain::CreateCacheParentKey(
            NamespaceName,
            RankingName,
            "ClusterRankingSeason"
        ))
    {
    }

    FClusterRankingSeasonAccessTokenDomain::FClusterRankingSeasonAccessTokenDomain(
        const FClusterRankingSeasonAccessTokenDomain& From
    ):
        Gs2(From.Gs2),
        Service(From.Service),
        Client(From.Client),
        NamespaceName(From.NamespaceName),
        RankingName(From.RankingName),
        ClusterName(From.ClusterName),
        Season(From.Season),
        AccessToken(From.AccessToken),
        ParentKey(From.ParentKey)
    {

    }

    FClusterRankingSeasonAccessTokenDomain::FGetClusterRankingTask::FGetClusterRankingTask(
        const TSharedPtr<FClusterRankingSeasonAccessTokenDomain>& Self,
        const Request::FGetClusterRankingRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FClusterRankingSeasonAccessTokenDomain::FGetClusterRankingTask::FGetClusterRankingTask(
        const FGetClusterRankingTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FClusterRankingSeasonAccessTokenDomain::FGetClusterRankingTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Ranking2::Domain::Model::FClusterRankingDataAccessTokenDomain>> Result
    )
    {
        Request
            ->WithContextStack(Self->Gs2->DefaultContextStack)
            ->WithNamespaceName(Self->NamespaceName)
            ->WithRankingName(Self->RankingName)
            ->WithClusterName(Self->ClusterName)
            ->WithAccessToken(Self->AccessToken->GetToken())
            ->WithSeason(Self->Season);
        const auto Future = Self->Client->GetClusterRanking(
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
        auto Domain = MakeShared<Gs2::Ranking2::Domain::Model::FClusterRankingDataAccessTokenDomain>(
            Self->Gs2,
            Self->Service,
            Request->GetNamespaceName(),
            ResultModel->GetItem()->GetRankingName(),
            ResultModel->GetItem()->GetClusterName(),
            ResultModel->GetItem()->GetSeason(),
            Self->AccessToken,
            ResultModel->GetItem()->GetUserId()
        );

        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FClusterRankingSeasonAccessTokenDomain::FGetClusterRankingTask>> FClusterRankingSeasonAccessTokenDomain::GetClusterRanking(
        Request::FGetClusterRankingRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FGetClusterRankingTask>>(this->AsShared(), Request);
    }

    FClusterRankingSeasonAccessTokenDomain::FPutClusterRankingScoreTask::FPutClusterRankingScoreTask(
        const TSharedPtr<FClusterRankingSeasonAccessTokenDomain>& Self,
        const Request::FPutClusterRankingScoreRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FClusterRankingSeasonAccessTokenDomain::FPutClusterRankingScoreTask::FPutClusterRankingScoreTask(
        const FPutClusterRankingScoreTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FClusterRankingSeasonAccessTokenDomain::FPutClusterRankingScoreTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Ranking2::Domain::Model::FClusterRankingScoreAccessTokenDomain>> Result
    )
    {
        Request
            ->WithContextStack(Self->Gs2->DefaultContextStack)
            ->WithNamespaceName(Self->NamespaceName)
            ->WithRankingName(Self->RankingName)
            ->WithClusterName(Self->ClusterName)
            ->WithAccessToken(Self->AccessToken->GetToken());
        const auto Future = Self->Client->PutClusterRankingScore(
            Request
        );
        Future->StartSynchronousTask();
        if (Future->GetTask().IsError())
        {
            return Future->GetTask().Error();
        }
        const auto ResultModel = Future->GetTask().Result();
        Future->EnsureCompletion();
        auto Domain = MakeShared<Gs2::Ranking2::Domain::Model::FClusterRankingScoreAccessTokenDomain>(
            Self->Gs2,
            Self->Service,
            Request->GetNamespaceName(),
            ResultModel->GetItem()->GetRankingName(),
            ResultModel->GetItem()->GetClusterName(),
            ResultModel->GetItem()->GetSeason(),
            Self->AccessToken
        );

        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FClusterRankingSeasonAccessTokenDomain::FPutClusterRankingScoreTask>> FClusterRankingSeasonAccessTokenDomain::PutClusterRankingScore(
        Request::FPutClusterRankingScoreRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FPutClusterRankingScoreTask>>(this->AsShared(), Request);
    }

    Gs2::Ranking2::Domain::Iterator::FDescribeClusterRankingsIteratorPtr FClusterRankingSeasonAccessTokenDomain::ClusterRankings(
    ) const
    {
        return MakeShared<Gs2::Ranking2::Domain::Iterator::FDescribeClusterRankingsIterator>(
            Gs2,
            Client,
            NamespaceName,
            AccessToken,
            RankingName,
            ClusterName,
            Season
        );
    }

    Gs2::Core::Domain::CallbackID FClusterRankingSeasonAccessTokenDomain::SubscribeClusterRankings(
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
                AccessToken.IsValid() ? AccessToken->GetTimeOffset() : TOptional<int32>()
            ),
            Callback,
            Callback
        );
    }
    void FClusterRankingSeasonAccessTokenDomain::UnsubscribeClusterRankings(
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
                AccessToken.IsValid() ? AccessToken->GetTimeOffset() : TOptional<int32>()
            ),
            CallbackID
        );
    }
    class FClusterRankingSeasonAccessTokenDomain::FCollectClusterRankingsTask : public Gs2::Core::Util::TGs2Future<TArray<Gs2::Ranking2::Model::FClusterRankingDataPtr>>, public TSharedFromThis<FCollectClusterRankingsTask>
    {
        const TSharedPtr<FClusterRankingSeasonAccessTokenDomain> Self;
        const TFunction<void(TArray<Gs2::Ranking2::Model::FClusterRankingDataPtr>)> OnCollected;

    public:
        explicit FCollectClusterRankingsTask(const TSharedPtr<FClusterRankingSeasonAccessTokenDomain>& Self, TFunction<void(TArray<Gs2::Ranking2::Model::FClusterRankingDataPtr>)> OnCollected) : Self(Self), OnCollected(OnCollected) {}
        FCollectClusterRankingsTask(const FCollectClusterRankingsTask& From) : TGs2Future(From), Self(From.Self), OnCollected(From.OnCollected) {}
        virtual Gs2::Core::Model::FGs2ErrorPtr Action(TSharedPtr<TSharedPtr<TArray<Gs2::Ranking2::Model::FClusterRankingDataPtr>>> Result) override
        {
            TArray<Gs2::Ranking2::Model::FClusterRankingDataPtr> Items;
            auto Iterator = Self->ClusterRankings()->begin();
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

    Gs2::Core::Domain::CallbackID FClusterRankingSeasonAccessTokenDomain::SubscribeClusterRankings(
        TFunction<void(TArray<Gs2::Ranking2::Model::FClusterRankingDataPtr>)> Callback
    )
    {
        const TWeakPtr<Gs2::Core::Domain::FGs2> WeakGs2 = this->Gs2;
        const TWeakPtr<Ranking2::Domain::FGs2Ranking2Domain> WeakService = this->Service;
        const auto SourceToken = this->AccessToken;
        const TOptional<FString> RegisteredUserId = SourceToken.IsValid() ? TOptional<FString>(SourceToken->GetUserId()) : TOptional<FString>();
        const int32 RegisteredTimeOffset = SourceToken.IsValid() ? SourceToken->GetTimeOffset().Get(0) : 0;
        const auto QueryNamespaceName = NamespaceName;
        const auto QueryRankingName = RankingName;
        const auto QueryClusterName = ClusterName;
        const auto QuerySeason = Season;
        const auto Parent = Gs2::Ranking2::Model::Cache::FClusterRankingDataCache::CreateCacheParentKey(
        NamespaceName,
        RankingName,
        ClusterName,
        Season,
        AccessToken.IsValid() ? AccessToken->GetTimeOffset() : TOptional<int32>()
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
            [WeakGs2, WeakService, Callback, QueryNamespaceName, QueryRankingName, QueryClusterName, QuerySeason, SourceToken, RegisteredUserId, RegisteredTimeOffset]()
            {
                const auto Owner = WeakGs2.Pin();
                if (!Owner.IsValid() || !SourceToken.IsValid() || !RegisteredUserId.IsSet()) return;
                const auto TokenSnapshot = MakeShared<Gs2::Auth::Model::FAccessToken>(*SourceToken);
                if (TokenSnapshot->GetUserId() != RegisteredUserId || TokenSnapshot->GetTimeOffset().Get(0) != RegisteredTimeOffset) return;
                const auto Domain = MakeShared<FClusterRankingSeasonAccessTokenDomain>(Owner, WeakService.Pin(), QueryNamespaceName, QueryRankingName, QueryClusterName, QuerySeason, TokenSnapshot);
                const auto Task = Gs2::Core::Util::New<FAsyncTask<FCollectClusterRankingsTask>>(Domain, Callback);
                Task->StartBackgroundTask();
            }
        );
    }

    void FClusterRankingSeasonAccessTokenDomain::InvalidateClusterRankings()
    {
        Gs2->Cache->ClearListCache(
            Gs2::Ranking2::Model::FClusterRankingData::TypeName,
            Gs2::Ranking2::Model::Cache::FClusterRankingDataCache::CreateCacheParentKey(
        NamespaceName,
        RankingName,
        ClusterName,
        Season,
        AccessToken.IsValid() ? AccessToken->GetTimeOffset() : TOptional<int32>()
    )
        );
    }

    FClusterRankingSeasonAccessTokenDomain::FSubscribeClusterRankingsWithInitialCallTask::FSubscribeClusterRankingsWithInitialCallTask(const TSharedPtr<FClusterRankingSeasonAccessTokenDomain>& Self, TFunction<void(TArray<Gs2::Ranking2::Model::FClusterRankingDataPtr>)> Callback) : Self(Self), Callback(Callback) {}
    FClusterRankingSeasonAccessTokenDomain::FSubscribeClusterRankingsWithInitialCallTask::FSubscribeClusterRankingsWithInitialCallTask(const FSubscribeClusterRankingsWithInitialCallTask& From) : TGs2Future(From), Self(From.Self), Callback(From.Callback) {}
    Gs2::Core::Model::FGs2ErrorPtr FClusterRankingSeasonAccessTokenDomain::FSubscribeClusterRankingsWithInitialCallTask::Action(TSharedPtr<TSharedPtr<Gs2::Core::Domain::CallbackID>> Result)
    {
        const auto Task = Gs2::Core::Util::New<FAsyncTask<FCollectClusterRankingsTask>>(Self, TFunction<void(TArray<Gs2::Ranking2::Model::FClusterRankingDataPtr>)>());
        Task->StartSynchronousTask(); Task->EnsureCompletion();
        if (Task->GetTask().IsError()) return Task->GetTask().Error();
        const auto Values = Task->GetTask().Result();
        const auto CallbackId = Self->SubscribeClusterRankings(Callback);
        Callback(*Values); *Result = MakeShared<Gs2::Core::Domain::CallbackID>(CallbackId);
        return nullptr;
    }
    TSharedPtr<FAsyncTask<FClusterRankingSeasonAccessTokenDomain::FSubscribeClusterRankingsWithInitialCallTask>> FClusterRankingSeasonAccessTokenDomain::SubscribeClusterRankingsWithInitialCall(TFunction<void(TArray<Gs2::Ranking2::Model::FClusterRankingDataPtr>)> Callback)
    {
        return Gs2::Core::Util::New<FAsyncTask<FSubscribeClusterRankingsWithInitialCallTask>>(this->AsShared(), Callback);
    }

    TSharedPtr<Gs2::Ranking2::Domain::Model::FClusterRankingDataAccessTokenDomain> FClusterRankingSeasonAccessTokenDomain::ClusterRankingData(
        const TOptional<FString> ScorerUserId
    )
    {
        return MakeShared<Gs2::Ranking2::Domain::Model::FClusterRankingDataAccessTokenDomain>(
            Gs2,
            Service,
            NamespaceName,
            RankingName,
            ClusterName,
            Season,
            AccessToken,
            ScorerUserId.IsSet() ? ScorerUserId : AccessToken->GetUserId()
        );
    }

    Gs2::Ranking2::Domain::Iterator::FDescribeClusterRankingReceivedRewardsIteratorPtr FClusterRankingSeasonAccessTokenDomain::ClusterRankingReceivedRewards(
    ) const
    {
        return MakeShared<Gs2::Ranking2::Domain::Iterator::FDescribeClusterRankingReceivedRewardsIterator>(
            Gs2,
            Client,
            NamespaceName,
            AccessToken,
            RankingName,
            ClusterName,
            Season
        );
    }

    Gs2::Core::Domain::CallbackID FClusterRankingSeasonAccessTokenDomain::SubscribeClusterRankingReceivedRewards(
    TFunction<void()> Callback
    )
    {
        return Gs2->Cache->ListSubscribe(
            Gs2::Ranking2::Model::FClusterRankingReceivedReward::TypeName,
            Gs2::Ranking2::Model::Cache::FClusterRankingReceivedRewardCache::CreateCacheParentKey(
                NamespaceName,
                AccessToken.IsValid() ? AccessToken->GetUserId() : TOptional<FString>(),
                RankingName,
                AccessToken.IsValid() ? AccessToken->GetTimeOffset() : TOptional<int32>()
            ),
            Callback,
            Callback
        );
    }
    void FClusterRankingSeasonAccessTokenDomain::UnsubscribeClusterRankingReceivedRewards(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        Gs2->Cache->ListUnsubscribe(
            Gs2::Ranking2::Model::FClusterRankingReceivedReward::TypeName,
            Gs2::Ranking2::Model::Cache::FClusterRankingReceivedRewardCache::CreateCacheParentKey(
                NamespaceName,
                AccessToken.IsValid() ? AccessToken->GetUserId() : TOptional<FString>(),
                RankingName,
                AccessToken.IsValid() ? AccessToken->GetTimeOffset() : TOptional<int32>()
            ),
            CallbackID
        );
    }
    class FClusterRankingSeasonAccessTokenDomain::FCollectClusterRankingReceivedRewardsTask : public Gs2::Core::Util::TGs2Future<TArray<Gs2::Ranking2::Model::FClusterRankingReceivedRewardPtr>>, public TSharedFromThis<FCollectClusterRankingReceivedRewardsTask>
    {
        const TSharedPtr<FClusterRankingSeasonAccessTokenDomain> Self;
        const TFunction<void(TArray<Gs2::Ranking2::Model::FClusterRankingReceivedRewardPtr>)> OnCollected;

    public:
        explicit FCollectClusterRankingReceivedRewardsTask(const TSharedPtr<FClusterRankingSeasonAccessTokenDomain>& Self, TFunction<void(TArray<Gs2::Ranking2::Model::FClusterRankingReceivedRewardPtr>)> OnCollected) : Self(Self), OnCollected(OnCollected) {}
        FCollectClusterRankingReceivedRewardsTask(const FCollectClusterRankingReceivedRewardsTask& From) : TGs2Future(From), Self(From.Self), OnCollected(From.OnCollected) {}
        virtual Gs2::Core::Model::FGs2ErrorPtr Action(TSharedPtr<TSharedPtr<TArray<Gs2::Ranking2::Model::FClusterRankingReceivedRewardPtr>>> Result) override
        {
            TArray<Gs2::Ranking2::Model::FClusterRankingReceivedRewardPtr> Items;
            auto Iterator = Self->ClusterRankingReceivedRewards()->begin();
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

    Gs2::Core::Domain::CallbackID FClusterRankingSeasonAccessTokenDomain::SubscribeClusterRankingReceivedRewards(
        TFunction<void(TArray<Gs2::Ranking2::Model::FClusterRankingReceivedRewardPtr>)> Callback
    )
    {
        const TWeakPtr<Gs2::Core::Domain::FGs2> WeakGs2 = this->Gs2;
        const TWeakPtr<Ranking2::Domain::FGs2Ranking2Domain> WeakService = this->Service;
        const auto SourceToken = this->AccessToken;
        const TOptional<FString> RegisteredUserId = SourceToken.IsValid() ? TOptional<FString>(SourceToken->GetUserId()) : TOptional<FString>();
        const int32 RegisteredTimeOffset = SourceToken.IsValid() ? SourceToken->GetTimeOffset().Get(0) : 0;
        const auto QueryNamespaceName = NamespaceName;
        const auto QueryRankingName = RankingName;
        const auto QueryClusterName = ClusterName;
        const auto QuerySeason = Season;
        const auto Parent = Gs2::Ranking2::Model::Cache::FClusterRankingReceivedRewardCache::CreateCacheParentKey(
        NamespaceName,
        AccessToken.IsValid() ? AccessToken->GetUserId() : TOptional<FString>(),
        RankingName,
        AccessToken.IsValid() ? AccessToken->GetTimeOffset() : TOptional<int32>()
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
            [WeakGs2, WeakService, Callback, QueryNamespaceName, QueryRankingName, QueryClusterName, QuerySeason, SourceToken, RegisteredUserId, RegisteredTimeOffset]()
            {
                const auto Owner = WeakGs2.Pin();
                if (!Owner.IsValid() || !SourceToken.IsValid() || !RegisteredUserId.IsSet()) return;
                const auto TokenSnapshot = MakeShared<Gs2::Auth::Model::FAccessToken>(*SourceToken);
                if (TokenSnapshot->GetUserId() != RegisteredUserId || TokenSnapshot->GetTimeOffset().Get(0) != RegisteredTimeOffset) return;
                const auto Domain = MakeShared<FClusterRankingSeasonAccessTokenDomain>(Owner, WeakService.Pin(), QueryNamespaceName, QueryRankingName, QueryClusterName, QuerySeason, TokenSnapshot);
                const auto Task = Gs2::Core::Util::New<FAsyncTask<FCollectClusterRankingReceivedRewardsTask>>(Domain, Callback);
                Task->StartBackgroundTask();
            }
        );
    }

    void FClusterRankingSeasonAccessTokenDomain::InvalidateClusterRankingReceivedRewards()
    {
        Gs2->Cache->ClearListCache(
            Gs2::Ranking2::Model::FClusterRankingReceivedReward::TypeName,
            Gs2::Ranking2::Model::Cache::FClusterRankingReceivedRewardCache::CreateCacheParentKey(
        NamespaceName,
        AccessToken.IsValid() ? AccessToken->GetUserId() : TOptional<FString>(),
        RankingName,
        AccessToken.IsValid() ? AccessToken->GetTimeOffset() : TOptional<int32>()
    )
        );
    }

    FClusterRankingSeasonAccessTokenDomain::FSubscribeClusterRankingReceivedRewardsWithInitialCallTask::FSubscribeClusterRankingReceivedRewardsWithInitialCallTask(const TSharedPtr<FClusterRankingSeasonAccessTokenDomain>& Self, TFunction<void(TArray<Gs2::Ranking2::Model::FClusterRankingReceivedRewardPtr>)> Callback) : Self(Self), Callback(Callback) {}
    FClusterRankingSeasonAccessTokenDomain::FSubscribeClusterRankingReceivedRewardsWithInitialCallTask::FSubscribeClusterRankingReceivedRewardsWithInitialCallTask(const FSubscribeClusterRankingReceivedRewardsWithInitialCallTask& From) : TGs2Future(From), Self(From.Self), Callback(From.Callback) {}
    Gs2::Core::Model::FGs2ErrorPtr FClusterRankingSeasonAccessTokenDomain::FSubscribeClusterRankingReceivedRewardsWithInitialCallTask::Action(TSharedPtr<TSharedPtr<Gs2::Core::Domain::CallbackID>> Result)
    {
        const auto Task = Gs2::Core::Util::New<FAsyncTask<FCollectClusterRankingReceivedRewardsTask>>(Self, TFunction<void(TArray<Gs2::Ranking2::Model::FClusterRankingReceivedRewardPtr>)>());
        Task->StartSynchronousTask(); Task->EnsureCompletion();
        if (Task->GetTask().IsError()) return Task->GetTask().Error();
        const auto Values = Task->GetTask().Result();
        const auto CallbackId = Self->SubscribeClusterRankingReceivedRewards(Callback);
        Callback(*Values); *Result = MakeShared<Gs2::Core::Domain::CallbackID>(CallbackId);
        return nullptr;
    }
    TSharedPtr<FAsyncTask<FClusterRankingSeasonAccessTokenDomain::FSubscribeClusterRankingReceivedRewardsWithInitialCallTask>> FClusterRankingSeasonAccessTokenDomain::SubscribeClusterRankingReceivedRewardsWithInitialCall(TFunction<void(TArray<Gs2::Ranking2::Model::FClusterRankingReceivedRewardPtr>)> Callback)
    {
        return Gs2::Core::Util::New<FAsyncTask<FSubscribeClusterRankingReceivedRewardsWithInitialCallTask>>(this->AsShared(), Callback);
    }

    TSharedPtr<Gs2::Ranking2::Domain::Model::FClusterRankingReceivedRewardAccessTokenDomain> FClusterRankingSeasonAccessTokenDomain::ClusterRankingReceivedReward(
    )
    {
        return MakeShared<Gs2::Ranking2::Domain::Model::FClusterRankingReceivedRewardAccessTokenDomain>(
            Gs2,
            Service,
            NamespaceName,
            RankingName,
            ClusterName,
            Season,
            AccessToken
        );
    }

    Gs2::Ranking2::Domain::Iterator::FDescribeClusterRankingScoresIteratorPtr FClusterRankingSeasonAccessTokenDomain::ClusterRankingScores(
    ) const
    {
        return MakeShared<Gs2::Ranking2::Domain::Iterator::FDescribeClusterRankingScoresIterator>(
            Gs2,
            Client,
            NamespaceName,
            AccessToken,
            RankingName,
            ClusterName,
            Season
        );
    }

    Gs2::Core::Domain::CallbackID FClusterRankingSeasonAccessTokenDomain::SubscribeClusterRankingScores(
    TFunction<void()> Callback
    )
    {
        return Gs2->Cache->ListSubscribe(
            Gs2::Ranking2::Model::FClusterRankingScore::TypeName,
            Gs2::Ranking2::Model::Cache::FClusterRankingScoreCache::CreateCacheParentKey(
                NamespaceName,
                AccessToken.IsValid() ? AccessToken->GetUserId() : TOptional<FString>(),
                RankingName,
                AccessToken.IsValid() ? AccessToken->GetTimeOffset() : TOptional<int32>()
            ),
            Callback,
            Callback
        );
    }
    void FClusterRankingSeasonAccessTokenDomain::UnsubscribeClusterRankingScores(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        Gs2->Cache->ListUnsubscribe(
            Gs2::Ranking2::Model::FClusterRankingScore::TypeName,
            Gs2::Ranking2::Model::Cache::FClusterRankingScoreCache::CreateCacheParentKey(
                NamespaceName,
                AccessToken.IsValid() ? AccessToken->GetUserId() : TOptional<FString>(),
                RankingName,
                AccessToken.IsValid() ? AccessToken->GetTimeOffset() : TOptional<int32>()
            ),
            CallbackID
        );
    }
    class FClusterRankingSeasonAccessTokenDomain::FCollectClusterRankingScoresTask : public Gs2::Core::Util::TGs2Future<TArray<Gs2::Ranking2::Model::FClusterRankingScorePtr>>, public TSharedFromThis<FCollectClusterRankingScoresTask>
    {
        const TSharedPtr<FClusterRankingSeasonAccessTokenDomain> Self;
        const TFunction<void(TArray<Gs2::Ranking2::Model::FClusterRankingScorePtr>)> OnCollected;

    public:
        explicit FCollectClusterRankingScoresTask(const TSharedPtr<FClusterRankingSeasonAccessTokenDomain>& Self, TFunction<void(TArray<Gs2::Ranking2::Model::FClusterRankingScorePtr>)> OnCollected) : Self(Self), OnCollected(OnCollected) {}
        FCollectClusterRankingScoresTask(const FCollectClusterRankingScoresTask& From) : TGs2Future(From), Self(From.Self), OnCollected(From.OnCollected) {}
        virtual Gs2::Core::Model::FGs2ErrorPtr Action(TSharedPtr<TSharedPtr<TArray<Gs2::Ranking2::Model::FClusterRankingScorePtr>>> Result) override
        {
            TArray<Gs2::Ranking2::Model::FClusterRankingScorePtr> Items;
            auto Iterator = Self->ClusterRankingScores()->begin();
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

    Gs2::Core::Domain::CallbackID FClusterRankingSeasonAccessTokenDomain::SubscribeClusterRankingScores(
        TFunction<void(TArray<Gs2::Ranking2::Model::FClusterRankingScorePtr>)> Callback
    )
    {
        const TWeakPtr<Gs2::Core::Domain::FGs2> WeakGs2 = this->Gs2;
        const TWeakPtr<Ranking2::Domain::FGs2Ranking2Domain> WeakService = this->Service;
        const auto SourceToken = this->AccessToken;
        const TOptional<FString> RegisteredUserId = SourceToken.IsValid() ? TOptional<FString>(SourceToken->GetUserId()) : TOptional<FString>();
        const int32 RegisteredTimeOffset = SourceToken.IsValid() ? SourceToken->GetTimeOffset().Get(0) : 0;
        const auto QueryNamespaceName = NamespaceName;
        const auto QueryRankingName = RankingName;
        const auto QueryClusterName = ClusterName;
        const auto QuerySeason = Season;
        const auto Parent = Gs2::Ranking2::Model::Cache::FClusterRankingScoreCache::CreateCacheParentKey(
        NamespaceName,
        AccessToken.IsValid() ? AccessToken->GetUserId() : TOptional<FString>(),
        RankingName,
        AccessToken.IsValid() ? AccessToken->GetTimeOffset() : TOptional<int32>()
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
            [WeakGs2, WeakService, Callback, QueryNamespaceName, QueryRankingName, QueryClusterName, QuerySeason, SourceToken, RegisteredUserId, RegisteredTimeOffset]()
            {
                const auto Owner = WeakGs2.Pin();
                if (!Owner.IsValid() || !SourceToken.IsValid() || !RegisteredUserId.IsSet()) return;
                const auto TokenSnapshot = MakeShared<Gs2::Auth::Model::FAccessToken>(*SourceToken);
                if (TokenSnapshot->GetUserId() != RegisteredUserId || TokenSnapshot->GetTimeOffset().Get(0) != RegisteredTimeOffset) return;
                const auto Domain = MakeShared<FClusterRankingSeasonAccessTokenDomain>(Owner, WeakService.Pin(), QueryNamespaceName, QueryRankingName, QueryClusterName, QuerySeason, TokenSnapshot);
                const auto Task = Gs2::Core::Util::New<FAsyncTask<FCollectClusterRankingScoresTask>>(Domain, Callback);
                Task->StartBackgroundTask();
            }
        );
    }

    void FClusterRankingSeasonAccessTokenDomain::InvalidateClusterRankingScores()
    {
        Gs2->Cache->ClearListCache(
            Gs2::Ranking2::Model::FClusterRankingScore::TypeName,
            Gs2::Ranking2::Model::Cache::FClusterRankingScoreCache::CreateCacheParentKey(
        NamespaceName,
        AccessToken.IsValid() ? AccessToken->GetUserId() : TOptional<FString>(),
        RankingName,
        AccessToken.IsValid() ? AccessToken->GetTimeOffset() : TOptional<int32>()
    )
        );
    }

    FClusterRankingSeasonAccessTokenDomain::FSubscribeClusterRankingScoresWithInitialCallTask::FSubscribeClusterRankingScoresWithInitialCallTask(const TSharedPtr<FClusterRankingSeasonAccessTokenDomain>& Self, TFunction<void(TArray<Gs2::Ranking2::Model::FClusterRankingScorePtr>)> Callback) : Self(Self), Callback(Callback) {}
    FClusterRankingSeasonAccessTokenDomain::FSubscribeClusterRankingScoresWithInitialCallTask::FSubscribeClusterRankingScoresWithInitialCallTask(const FSubscribeClusterRankingScoresWithInitialCallTask& From) : TGs2Future(From), Self(From.Self), Callback(From.Callback) {}
    Gs2::Core::Model::FGs2ErrorPtr FClusterRankingSeasonAccessTokenDomain::FSubscribeClusterRankingScoresWithInitialCallTask::Action(TSharedPtr<TSharedPtr<Gs2::Core::Domain::CallbackID>> Result)
    {
        const auto Task = Gs2::Core::Util::New<FAsyncTask<FCollectClusterRankingScoresTask>>(Self, TFunction<void(TArray<Gs2::Ranking2::Model::FClusterRankingScorePtr>)>());
        Task->StartSynchronousTask(); Task->EnsureCompletion();
        if (Task->GetTask().IsError()) return Task->GetTask().Error();
        const auto Values = Task->GetTask().Result();
        const auto CallbackId = Self->SubscribeClusterRankingScores(Callback);
        Callback(*Values); *Result = MakeShared<Gs2::Core::Domain::CallbackID>(CallbackId);
        return nullptr;
    }
    TSharedPtr<FAsyncTask<FClusterRankingSeasonAccessTokenDomain::FSubscribeClusterRankingScoresWithInitialCallTask>> FClusterRankingSeasonAccessTokenDomain::SubscribeClusterRankingScoresWithInitialCall(TFunction<void(TArray<Gs2::Ranking2::Model::FClusterRankingScorePtr>)> Callback)
    {
        return Gs2::Core::Util::New<FAsyncTask<FSubscribeClusterRankingScoresWithInitialCallTask>>(this->AsShared(), Callback);
    }

    TSharedPtr<Gs2::Ranking2::Domain::Model::FClusterRankingScoreAccessTokenDomain> FClusterRankingSeasonAccessTokenDomain::ClusterRankingScore(
    )
    {
        return MakeShared<Gs2::Ranking2::Domain::Model::FClusterRankingScoreAccessTokenDomain>(
            Gs2,
            Service,
            NamespaceName,
            RankingName,
            ClusterName,
            Season,
            AccessToken
        );
    }

    FString FClusterRankingSeasonAccessTokenDomain::CreateCacheParentKey(
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

    FString FClusterRankingSeasonAccessTokenDomain::CreateCacheKey(
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

