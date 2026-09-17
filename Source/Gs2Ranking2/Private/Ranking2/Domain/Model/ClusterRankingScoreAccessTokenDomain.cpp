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

#include "Ranking2/Domain/Model/ClusterRankingScoreAccessToken.h"
#include "Ranking2/Domain/Model/ClusterRankingScore.h"
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

#include "Core/Domain/Gs2.h"
#include "Core/Domain/Transaction/JobQueueJobDomainFactory.h"
#include "Core/Domain/Transaction/InternalTransactionDomainFactory.h"
#include "Core/Domain/Transaction/ManualTransactionAccessTokenDomain.h"

namespace Gs2::Ranking2::Domain::Model
{

    FClusterRankingScoreAccessTokenDomain::FClusterRankingScoreAccessTokenDomain(
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
        ParentKey(Gs2::Ranking2::Domain::Model::FClusterRankingSeasonDomain::CreateCacheParentKey(
            NamespaceName,
            RankingName,
            ClusterName,
            Season,
            "ClusterRankingScore"
        ))
    {
    }

    FClusterRankingScoreAccessTokenDomain::FClusterRankingScoreAccessTokenDomain(
        const FClusterRankingScoreAccessTokenDomain& From
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

    FClusterRankingScoreAccessTokenDomain::FGetTask::FGetTask(
        const TSharedPtr<FClusterRankingScoreAccessTokenDomain>& Self,
        const Request::FGetClusterRankingScoreRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FClusterRankingScoreAccessTokenDomain::FGetTask::FGetTask(
        const FGetTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FClusterRankingScoreAccessTokenDomain::FGetTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Ranking2::Model::FClusterRankingScore>> Result
    )
    {
        Request
            ->WithContextStack(Self->Gs2->DefaultContextStack)
            ->WithNamespaceName(Self->NamespaceName)
            ->WithRankingName(Self->RankingName)
            ->WithClusterName(Self->ClusterName)
            ->WithAccessToken(Self->AccessToken->GetToken())
            ->WithSeason(Self->Season);
        const auto Future = Self->Client->GetClusterRankingScore(
            Request
        );
        Future->StartSynchronousTask();
        if (Future->GetTask().IsError())
        {
            return Future->GetTask().Error();
        }
        const auto ResultModel = Future->GetTask().Result();
        Future->EnsureCompletion();
        const auto Item = ResultModel.IsValid() ? ResultModel->GetItem() : nullptr;
        if (Item.IsValid())
        {
            const TOptional<int64> ResolvedSeason(Item->GetSeason().Get(static_cast<int64>(0)));
            const auto ResponseParentKey = Gs2::Ranking2::Domain::Model::FClusterRankingSeasonDomain::CreateCacheParentKey(
                Request->GetNamespaceName(),
                Item->GetRankingName(),
                Item->GetClusterName(),
                ResolvedSeason,
                "ClusterRankingScore"
            );
            const auto ResponseKey = Gs2::Ranking2::Domain::Model::FClusterRankingScoreDomain::CreateCacheKey(
                Item->GetClusterName(),
                ResolvedSeason,
                Item->GetUserId()
            );
            Self->Gs2->Cache->Put(
                Gs2::Ranking2::Model::FClusterRankingScore::TypeName,
                ResponseParentKey,
                ResponseKey,
                Item,
                FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
            );
            if (!Request->GetSeason().IsSet())
            {
                const TOptional<int64> UnspecifiedSeason;
                const auto AliasParentKey = Gs2::Ranking2::Domain::Model::FClusterRankingSeasonDomain::CreateCacheParentKey(
                    Request->GetNamespaceName(),
                    Item->GetRankingName(),
                    Item->GetClusterName(),
                    UnspecifiedSeason,
                    "ClusterRankingScore"
                );
                const auto AliasKey = Gs2::Ranking2::Domain::Model::FClusterRankingScoreDomain::CreateCacheKey(
                    Item->GetClusterName(),
                    UnspecifiedSeason,
                    Item->GetUserId()
                );
                Self->Gs2->Cache->Put(
                    Gs2::Ranking2::Model::FClusterRankingScore::TypeName,
                    AliasParentKey,
                    AliasKey,
                    Item,
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );
            }
        }
        *Result = Item;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FClusterRankingScoreAccessTokenDomain::FGetTask>> FClusterRankingScoreAccessTokenDomain::Get(
        Request::FGetClusterRankingScoreRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FGetTask>>(this->AsShared(), Request);
    }

    FClusterRankingScoreAccessTokenDomain::FVerifyTask::FVerifyTask(
        const TSharedPtr<FClusterRankingScoreAccessTokenDomain>& Self,
        const Request::FVerifyClusterRankingScoreRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FClusterRankingScoreAccessTokenDomain::FVerifyTask::FVerifyTask(
        const FVerifyTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FClusterRankingScoreAccessTokenDomain::FVerifyTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Ranking2::Domain::Model::FClusterRankingScoreAccessTokenDomain>> Result
    )
    {
        Request
            ->WithContextStack(Self->Gs2->DefaultContextStack)
            ->WithNamespaceName(Self->NamespaceName)
            ->WithAccessToken(Self->AccessToken->GetToken())
            ->WithRankingName(Self->RankingName)
            ->WithClusterName(Self->ClusterName)
            ->WithSeason(Self->Season);
        const auto Future = Self->Client->VerifyClusterRankingScore(
            Request
        );
        Future->StartSynchronousTask();
        if (Future->GetTask().IsError())
        {
            return Future->GetTask().Error();
        }
        const auto ResultModel = Future->GetTask().Result();
        auto Domain = Self;

        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FClusterRankingScoreAccessTokenDomain::FVerifyTask>> FClusterRankingScoreAccessTokenDomain::Verify(
        Request::FVerifyClusterRankingScoreRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FVerifyTask>>(this->AsShared(), Request);
    }

    FString FClusterRankingScoreAccessTokenDomain::CreateCacheParentKey(
        TOptional<FString> NamespaceName,
        TOptional<FString> RankingName,
        TOptional<FString> ClusterName,
        TOptional<int64> Season,
        TOptional<FString> UserId,
        FString ChildType
    )
    {
        return FString("") +
            (NamespaceName.IsSet() ? *NamespaceName : "null") + ":" +
            (RankingName.IsSet() ? *RankingName : "null") + ":" +
            (ClusterName.IsSet() ? *ClusterName : "null") + ":" +
            (Season.IsSet() ? FString::FromInt(*Season) : "null") + ":" +
            (UserId.IsSet() ? *UserId : "null") + ":" +
            ChildType;
    }

    FString FClusterRankingScoreAccessTokenDomain::CreateCacheKey(
        TOptional<FString> ClusterName,
        TOptional<int64> Season,
        TOptional<FString> UserId
    )
    {
        return FString("") +
            (ClusterName.IsSet() ? *ClusterName : "null") + ":" + 
            (Season.IsSet() ? FString::FromInt(*Season) : "null") + ":" + 
            (UserId.IsSet() ? *UserId : "null");
    }

    FClusterRankingScoreAccessTokenDomain::FModelTask::FModelTask(
        const TSharedPtr<FClusterRankingScoreAccessTokenDomain> Self
    ): Self(Self)
    {

    }

    FClusterRankingScoreAccessTokenDomain::FModelTask::FModelTask(
        const FModelTask& From
    ): TGs2Future(From), Self(From.Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FClusterRankingScoreAccessTokenDomain::FModelTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Ranking2::Model::FClusterRankingScore>> Result
    )
    {
        const auto CacheParentKey = Gs2::Ranking2::Model::Cache::FClusterRankingScoreCache::CreateCacheParentKey(

            Self->NamespaceName,
            Self->AccessToken.IsValid() ? Self->UserId() : TOptional<FString>(),
            Self->RankingName,
            Self->AccessToken.IsValid() ? Self->AccessToken->GetTimeOffset() : TOptional<int32>()
        );
        const auto CacheKey = Gs2::Ranking2::Model::Cache::FClusterRankingScoreCache::CreateCacheKey(

            Self->ClusterName,
            Self->Season,
            Self->AccessToken.IsValid() ? Self->UserId() : TOptional<FString>()
        );
        return Self->Gs2->Cache->ExecuteWithKeyLock(
            Gs2::Ranking2::Model::FClusterRankingScore::TypeName,
            CacheParentKey,
            CacheKey,
            [Self = Self, Result]() -> Gs2::Core::Model::FGs2ErrorPtr
            {
                Gs2::Ranking2::Model::FClusterRankingScorePtr Value;
                const auto CacheHit = Gs2::Ranking2::Model::Cache::FClusterRankingScoreCache::TryGet(
                    Self->Gs2->Cache,

                    Self->NamespaceName,
                    Self->RankingName,
                    Self->ClusterName,
                    Self->Season,
                    Self->AccessToken.IsValid() ? Self->UserId() : TOptional<FString>(),
                    Self->AccessToken.IsValid() ? Self->AccessToken->GetTimeOffset() : TOptional<int32>(),
                    &Value
                );
                if (CacheHit)
                {
                    *Result = Value;
                    return nullptr;
                }
                const auto Error = Gs2::Ranking2::Model::Cache::FClusterRankingScoreCache::Fetch(
                    Self->Gs2->Cache,

                    Self->NamespaceName,
                    Self->RankingName,
                    Self->ClusterName,
                    Self->Season,
                    Self->AccessToken.IsValid() ? Self->UserId() : TOptional<FString>(),
                    Self->AccessToken.IsValid() ? Self->AccessToken->GetTimeOffset() : TOptional<int32>(),
                    [Self](Gs2::Ranking2::Model::FClusterRankingScorePtr* OutItem) -> Gs2::Core::Model::FGs2ErrorPtr
                    {
                        const auto Future = Self->Get(
                            MakeShared<Gs2::Ranking2::Request::FGetClusterRankingScoreRequest>()
                        );
                        Future->StartSynchronousTask();
                        if (Future->GetTask().IsError()) return Future->GetTask().Error();
                        *OutItem = Future->GetTask().Result();
                        Future->EnsureCompletion();
                        return nullptr;
                    },
                    &Value
                );
                if (Error.IsValid()) return Error;
                *Result = Value;
                return nullptr;
            }
        );
    }

    TSharedPtr<FAsyncTask<FClusterRankingScoreAccessTokenDomain::FModelTask>> FClusterRankingScoreAccessTokenDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FClusterRankingScoreAccessTokenDomain::FModelTask>>(this->AsShared());
    }

    void FClusterRankingScoreAccessTokenDomain::Invalidate()
    {
        Gs2::Ranking2::Model::Cache::FClusterRankingScoreCache::Delete(
            Gs2->Cache,

            NamespaceName,
            RankingName,
            ClusterName,
            Season,
            AccessToken.IsValid() ? UserId() : TOptional<FString>(),
            AccessToken.IsValid() ? AccessToken->GetTimeOffset() : TOptional<int32>()
        );
    }

    FClusterRankingScoreAccessTokenDomain::FSubscribeWithInitialCallTask::FSubscribeWithInitialCallTask(
        const TSharedPtr<FClusterRankingScoreAccessTokenDomain>& Self,
        TFunction<void(Gs2::Ranking2::Model::FClusterRankingScorePtr)> Callback
    ):
        Self(Self),
        Callback(Callback)
    {
    }

    FClusterRankingScoreAccessTokenDomain::FSubscribeWithInitialCallTask::FSubscribeWithInitialCallTask(
        const FSubscribeWithInitialCallTask& From
    ):
        TGs2Future(From),
        Self(From.Self),
        Callback(From.Callback)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FClusterRankingScoreAccessTokenDomain::FSubscribeWithInitialCallTask::Action(
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

    TSharedPtr<FAsyncTask<FClusterRankingScoreAccessTokenDomain::FSubscribeWithInitialCallTask>> FClusterRankingScoreAccessTokenDomain::SubscribeWithInitialCall(
        TFunction<void(Gs2::Ranking2::Model::FClusterRankingScorePtr)> Callback
    )
    {
        return Gs2::Core::Util::New<FAsyncTask<FSubscribeWithInitialCallTask>>(this->AsShared(), Callback);
    }

    Gs2::Core::Domain::CallbackID FClusterRankingScoreAccessTokenDomain::Subscribe(
        TFunction<void(Gs2::Ranking2::Model::FClusterRankingScorePtr)> Callback
    )
    {
        const auto SubscriptionParentKey = Gs2::Ranking2::Model::Cache::FClusterRankingScoreCache::CreateCacheParentKey(

            NamespaceName,
            AccessToken.IsValid() ? UserId() : TOptional<FString>(),
            RankingName,
            AccessToken.IsValid() ? AccessToken->GetTimeOffset() : TOptional<int32>()
        );
        const auto SubscriptionCacheKey = Gs2::Ranking2::Model::Cache::FClusterRankingScoreCache::CreateCacheKey(

            ClusterName,
            Season,
            AccessToken.IsValid() ? UserId() : TOptional<FString>()
        );
        const TWeakPtr<Gs2::Core::Domain::FGs2> WeakGs2 = Gs2;
        const TWeakPtr<Ranking2::Domain::FGs2Ranking2Domain> WeakService = Service;
        const FString RegisteredParentKey = SubscriptionParentKey;
        const TOptional<FString> QueryNamespaceName = NamespaceName;
        const TOptional<FString> QueryRankingName = RankingName;
        const TOptional<FString> QueryClusterName = ClusterName;
        const TOptional<int64> QuerySeason = Season;
        const auto SourceToken = AccessToken;
        const TOptional<FString> RegisteredUserId = SourceToken.IsValid()
            ? TOptional<FString>(SourceToken->GetUserId())
            : TOptional<FString>();
        const int32 RegisteredTimeOffset = SourceToken.IsValid() ? SourceToken->GetTimeOffset().Get(0) : 0;
        return Gs2->Cache->Subscribe(
            Gs2::Ranking2::Model::FClusterRankingScore::TypeName,
            SubscriptionParentKey,
            SubscriptionCacheKey,
            [Callback](TSharedPtr<FGs2Object> obj)
            {
                Callback(StaticCastSharedPtr<Gs2::Ranking2::Model::FClusterRankingScore>(obj));
            },
            [WeakGs2, WeakService, RegisteredParentKey, QueryNamespaceName, QueryRankingName, QueryClusterName, QuerySeason, SourceToken, RegisteredUserId, RegisteredTimeOffset]()
            {
                const auto Owner = WeakGs2.Pin();
                if (!Owner.IsValid() || !SourceToken.IsValid() || !RegisteredUserId.IsSet())
                {
                    return;
                }
                const auto TokenSnapshot = MakeShared<Gs2::Auth::Model::FAccessToken>(*SourceToken);
                if (TokenSnapshot->GetUserId() != RegisteredUserId || TokenSnapshot->GetTimeOffset().Get(0) != RegisteredTimeOffset)
                {
                    return;
                }
                const auto Domain = MakeShared<FClusterRankingScoreAccessTokenDomain>(
                    Owner,
                    WeakService.Pin(),
                    QueryNamespaceName,
                    QueryRankingName,
                    QueryClusterName,
                    QuerySeason,
                    TokenSnapshot
                );
                Domain->ParentKey = RegisteredParentKey;
                const auto Task = Domain->Model();
                Task->StartBackgroundTask();
            }
        );
    }

    void FClusterRankingScoreAccessTokenDomain::Unsubscribe(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        const auto SubscriptionParentKey = Gs2::Ranking2::Model::Cache::FClusterRankingScoreCache::CreateCacheParentKey(

            NamespaceName,
            AccessToken.IsValid() ? UserId() : TOptional<FString>(),
            RankingName,
            AccessToken.IsValid() ? AccessToken->GetTimeOffset() : TOptional<int32>()
        );
        const auto SubscriptionCacheKey = Gs2::Ranking2::Model::Cache::FClusterRankingScoreCache::CreateCacheKey(

            ClusterName,
            Season,
            AccessToken.IsValid() ? UserId() : TOptional<FString>()
        );
        Gs2->Cache->Unsubscribe(
            Gs2::Ranking2::Model::FClusterRankingScore::TypeName,
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

