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

#include "Ranking2/Domain/Model/ClusterRankingData.h"
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
#include "Ranking2/Model/Cache/ClusterRankingData.h"

#include "Core/Domain/Gs2.h"
#include "Core/Domain/Transaction/JobQueueJobDomainFactory.h"
#include "Core/Domain/Transaction/InternalTransactionDomainFactory.h"
#include "Core/Domain/Transaction/ManualTransactionDomain.h"

namespace Gs2::Ranking2::Domain::Model
{

    FClusterRankingDataDomain::FClusterRankingDataDomain(
        const Core::Domain::FGs2Ptr& Gs2,
        const Ranking2::Domain::FGs2Ranking2DomainPtr& Service,
        const TOptional<FString> NamespaceName,
        const TOptional<FString> RankingName,
        const TOptional<FString> ClusterName,
        const TOptional<int64> Season,
        const TOptional<FString> UserId,
        const TOptional<FString> ScorerUserId
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
        ScorerUserId(ScorerUserId),
        ParentKey(Gs2::Ranking2::Domain::Model::FClusterRankingSeasonDomain::CreateCacheParentKey(
            NamespaceName,
            RankingName,
            ClusterName,
            Season,
            "ClusterRankingData"
        ))
    {
    }

    FClusterRankingDataDomain::FClusterRankingDataDomain(
        const FClusterRankingDataDomain& From
    ):
        Gs2(From.Gs2),
        Service(From.Service),
        Client(From.Client),
        NamespaceName(From.NamespaceName),
        RankingName(From.RankingName),
        ClusterName(From.ClusterName),
        Season(From.Season),
        UserId(From.UserId),
        ScorerUserId(From.ScorerUserId),
        ParentKey(From.ParentKey)
    {

    }

    FString FClusterRankingDataDomain::CreateCacheParentKey(
        TOptional<FString> NamespaceName,
        TOptional<FString> RankingName,
        TOptional<FString> ClusterName,
        TOptional<int64> Season,
        TOptional<FString> ScorerUserId,
        FString ChildType
    )
    {
        return FString("") +
            (NamespaceName.IsSet() ? *NamespaceName : "null") + ":" +
            (RankingName.IsSet() ? *RankingName : "null") + ":" +
            (ClusterName.IsSet() ? *ClusterName : "null") + ":" +
            (Season.IsSet() ? FString::FromInt(*Season) : "null") + ":" +
            (ScorerUserId.IsSet() ? *ScorerUserId : "null") + ":" +
            ChildType;
    }

    FString FClusterRankingDataDomain::CreateCacheKey(
        TOptional<FString> ScorerUserId
    )
    {
        return FString("") +
            (ScorerUserId.IsSet() ? *ScorerUserId : "null");
    }

    FClusterRankingDataDomain::FModelTask::FModelTask(
        const TSharedPtr<FClusterRankingDataDomain> Self
    ): Self(Self)
    {

    }

    FClusterRankingDataDomain::FModelTask::FModelTask(
        const FModelTask& From
    ): TGs2Future(From), Self(From.Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FClusterRankingDataDomain::FModelTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Ranking2::Model::FClusterRankingData>> Result
    )
    {
        const auto CacheParentKey = Gs2::Ranking2::Model::Cache::FClusterRankingDataCache::CreateCacheParentKey(

            Self->NamespaceName,
            Self->RankingName,
            Self->ClusterName,
            Self->Season,
            TOptional<int32>()
        );
        const auto CacheKey = Gs2::Ranking2::Model::Cache::FClusterRankingDataCache::CreateCacheKey(

            Self->ScorerUserId
        );
        return Self->Gs2->Cache->ExecuteWithKeyLock(
            Gs2::Ranking2::Model::FClusterRankingData::TypeName,
            CacheParentKey,
            CacheKey,
            [Self = Self, Result]() -> Gs2::Core::Model::FGs2ErrorPtr
            {
                Gs2::Ranking2::Model::FClusterRankingDataPtr Value;
                const auto CacheHit = Gs2::Ranking2::Model::Cache::FClusterRankingDataCache::TryGet(
                    Self->Gs2->Cache,

                    Self->NamespaceName,
                    Self->RankingName,
                    Self->ClusterName,
                    Self->Season,
                    Self->ScorerUserId,
                    TOptional<int32>(),
                    &Value
                );
                if (CacheHit)
                {
                    *Result = Value;
                    return nullptr;
                }
                *Result = Value;
                return nullptr;
            }
        );
    }

    TSharedPtr<FAsyncTask<FClusterRankingDataDomain::FModelTask>> FClusterRankingDataDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FClusterRankingDataDomain::FModelTask>>(this->AsShared());
    }

    void FClusterRankingDataDomain::Invalidate()
    {
        Gs2::Ranking2::Model::Cache::FClusterRankingDataCache::Delete(
            Gs2->Cache,

            NamespaceName,
            RankingName,
            ClusterName,
            Season,
            ScorerUserId,
            TOptional<int32>()
        );
    }

    FClusterRankingDataDomain::FSubscribeWithInitialCallTask::FSubscribeWithInitialCallTask(
        const TSharedPtr<FClusterRankingDataDomain>& Self,
        TFunction<void(Gs2::Ranking2::Model::FClusterRankingDataPtr)> Callback
    ):
        Self(Self),
        Callback(Callback)
    {
    }

    FClusterRankingDataDomain::FSubscribeWithInitialCallTask::FSubscribeWithInitialCallTask(
        const FSubscribeWithInitialCallTask& From
    ):
        TGs2Future(From),
        Self(From.Self),
        Callback(From.Callback)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FClusterRankingDataDomain::FSubscribeWithInitialCallTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Core::Domain::CallbackID>> Result
    )
    {
        const auto Task = Self->Model();
        Task->StartSynchronousTask();
        Task->EnsureCompletion();
        if (Task->GetTask().IsError()) return Task->GetTask().Error();
        const auto Item = Task->GetTask().Result();
        const auto CallbackId = Self->Subscribe(Callback);
        Callback(Item);
        *Result = MakeShared<Gs2::Core::Domain::CallbackID>(CallbackId);
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FClusterRankingDataDomain::FSubscribeWithInitialCallTask>> FClusterRankingDataDomain::SubscribeWithInitialCall(
        TFunction<void(Gs2::Ranking2::Model::FClusterRankingDataPtr)> Callback
    )
    {
        return Gs2::Core::Util::New<FAsyncTask<FSubscribeWithInitialCallTask>>(this->AsShared(), Callback);
    }

    Gs2::Core::Domain::CallbackID FClusterRankingDataDomain::Subscribe(
        TFunction<void(Gs2::Ranking2::Model::FClusterRankingDataPtr)> Callback
    )
    {
        const auto SubscriptionParentKey = Gs2::Ranking2::Model::Cache::FClusterRankingDataCache::CreateCacheParentKey(

            NamespaceName,
            RankingName,
            ClusterName,
            Season,
            TOptional<int32>()
        );
        const auto SubscriptionCacheKey = Gs2::Ranking2::Model::Cache::FClusterRankingDataCache::CreateCacheKey(

            ScorerUserId
        );
        const TWeakPtr<Gs2::Core::Domain::FGs2> WeakGs2 = Gs2;
        const TWeakPtr<Ranking2::Domain::FGs2Ranking2Domain> WeakService = Service;
        const FString RegisteredParentKey = SubscriptionParentKey;
        const TOptional<FString> QueryNamespaceName = NamespaceName;
        const TOptional<FString> QueryRankingName = RankingName;
        const TOptional<FString> QueryClusterName = ClusterName;
        const TOptional<int64> QuerySeason = Season;
        const TOptional<FString> QueryUserId = UserId;
        const TOptional<FString> QueryScorerUserId = ScorerUserId;
        return Gs2->Cache->Subscribe(
            Gs2::Ranking2::Model::FClusterRankingData::TypeName,
            SubscriptionParentKey,
            SubscriptionCacheKey,
            [Callback](TSharedPtr<FGs2Object> obj)
            {
                Callback(StaticCastSharedPtr<Gs2::Ranking2::Model::FClusterRankingData>(obj));
            },
            [WeakGs2, WeakService, RegisteredParentKey, QueryNamespaceName, QueryRankingName, QueryClusterName, QuerySeason, QueryUserId, QueryScorerUserId]()
            {
                const auto Owner = WeakGs2.Pin();
                if (!Owner.IsValid())
                {
                    return;
                }
                const auto Domain = MakeShared<FClusterRankingDataDomain>(
                    Owner,
                    WeakService.Pin(),
                    QueryNamespaceName,
                    QueryRankingName,
                    QueryClusterName,
                    QuerySeason,
                    QueryUserId,
                    QueryScorerUserId
                );
                Domain->ParentKey = RegisteredParentKey;
                const auto Task = Domain->Model();
                Task->StartBackgroundTask();
            }
        );
    }

    void FClusterRankingDataDomain::Unsubscribe(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        const auto SubscriptionParentKey = Gs2::Ranking2::Model::Cache::FClusterRankingDataCache::CreateCacheParentKey(

            NamespaceName,
            RankingName,
            ClusterName,
            Season,
            TOptional<int32>()
        );
        const auto SubscriptionCacheKey = Gs2::Ranking2::Model::Cache::FClusterRankingDataCache::CreateCacheKey(

            ScorerUserId
        );
        Gs2->Cache->Unsubscribe(
            Gs2::Ranking2::Model::FClusterRankingData::TypeName,
            SubscriptionParentKey,
            SubscriptionCacheKey,
            CallbackID
        );
    }
}

#if defined(_MSC_VER)
#pragma warning (pop)
#elif defined(__clang__)
#pragma clang diagnostic pop
#endif
