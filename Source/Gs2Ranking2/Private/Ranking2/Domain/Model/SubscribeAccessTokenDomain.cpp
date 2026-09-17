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

#include "Ranking2/Domain/Model/SubscribeAccessToken.h"
#include "Ranking2/Domain/Model/Subscribe.h"
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
#include "Ranking2/Model/Cache/Subscribe.h"
#include "Ranking2/Model/Cache/SubscribeUser.h"

#include "Core/Domain/Gs2.h"
#include "Core/Domain/Transaction/JobQueueJobDomainFactory.h"
#include "Core/Domain/Transaction/InternalTransactionDomainFactory.h"
#include "Core/Domain/Transaction/ManualTransactionAccessTokenDomain.h"

namespace Gs2::Ranking2::Domain::Model
{

    FSubscribeAccessTokenDomain::FSubscribeAccessTokenDomain(
        const Core::Domain::FGs2Ptr& Gs2,
        const Ranking2::Domain::FGs2Ranking2DomainPtr& Service,
        const TOptional<FString> NamespaceName,
        const Gs2::Auth::Model::FAccessTokenPtr& AccessToken,
        const TOptional<FString> RankingName
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Gs2(Gs2),
        Service(Service),
        Client(MakeShared<Gs2::Ranking2::FGs2Ranking2RestClient>(Gs2->RestSession)),
        NamespaceName(NamespaceName),
        AccessToken(AccessToken),
        RankingName(RankingName)
    {
    }

    FSubscribeAccessTokenDomain::FSubscribeAccessTokenDomain(
        const FSubscribeAccessTokenDomain& From
    ):
        Gs2(From.Gs2),
        Service(From.Service),
        Client(From.Client),
        NamespaceName(From.NamespaceName),
        AccessToken(From.AccessToken),
        RankingName(From.RankingName)
    {

    }

    FSubscribeAccessTokenDomain::FAddTask::FAddTask(
        const TSharedPtr<FSubscribeAccessTokenDomain>& Self,
        const Request::FAddSubscribeRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FSubscribeAccessTokenDomain::FAddTask::FAddTask(
        const FAddTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FSubscribeAccessTokenDomain::FAddTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Ranking2::Domain::Model::FSubscribeUserAccessTokenDomain>> Result
    )
    {
        const auto RequestNamespaceName = Self->NamespaceName;
        const auto RequestRankingName = Self->RankingName;
        const auto SourceToken = Self->AccessToken;
        const auto RequestUserId = SourceToken.IsValid()
            ? SourceToken->GetUserId()
            : TOptional<FString>();
        const auto RequestTimeOffset = SourceToken.IsValid()
            ? SourceToken->GetTimeOffset()
            : TOptional<int32>();
        const auto RequestAccessToken = SourceToken.IsValid()
            ? SourceToken->GetToken()
            : TOptional<FString>();
        Request
            ->WithContextStack((!Request->GetContextStack().IsSet() || Request->GetContextStack()->IsEmpty())
                ? Self->Gs2->DefaultContextStack
                : Request->GetContextStack())
            ->WithNamespaceName(RequestNamespaceName)
            ->WithRankingName(RequestRankingName)
            ->WithAccessToken(RequestAccessToken);
        const auto Future = Self->Client->AddSubscribe(
            Request
        );
        Future->StartSynchronousTask();
        if (Future->GetTask().IsError())
        {
            return Future->GetTask().Error();
        }
        const auto ResultModel = Future->GetTask().Result();
        Future->EnsureCompletion();
        const auto ResultItem = ResultModel.IsValid() ? ResultModel->GetItem() : nullptr;
        if (ResultItem.IsValid())
        {
            Gs2::Ranking2::Model::Cache::FSubscribeUserCache::Put(
                Self->Gs2->Cache,
                RequestNamespaceName,
                RequestUserId,
                RequestRankingName,
                ResultItem->GetTargetUserId(),
                RequestTimeOffset,
                ResultItem
            );
        }
        auto Domain = MakeShared<Gs2::Ranking2::Domain::Model::FSubscribeUserAccessTokenDomain>(
            Self->Gs2,
            Self->Service,
            RequestNamespaceName,
            SourceToken,
            ResultItem.IsValid() ? ResultItem->GetRankingName() : TOptional<FString>(),
            ResultItem.IsValid() ? ResultItem->GetTargetUserId() : TOptional<FString>()
        );

        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FSubscribeAccessTokenDomain::FAddTask>> FSubscribeAccessTokenDomain::Add(
        Request::FAddSubscribeRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FAddTask>>(this->AsShared(), Request);
    }

    TSharedPtr<Gs2::Ranking2::Domain::Model::FSubscribeUserAccessTokenDomain> FSubscribeAccessTokenDomain::SubscribeUser(
        const FString TargetUserId
    )
    {
        return MakeShared<Gs2::Ranking2::Domain::Model::FSubscribeUserAccessTokenDomain>(
            Gs2,
            Service,
            NamespaceName,
            AccessToken,
            RankingName,
            TargetUserId == TEXT("") ? TOptional<FString>() : TOptional<FString>(TargetUserId)
        );
    }

    FString FSubscribeAccessTokenDomain::CreateCacheParentKey(
        TOptional<FString> NamespaceName,
        TOptional<FString> UserId,
        TOptional<FString> RankingName,
        FString ChildType
    )
    {
        return FString("") +
            (NamespaceName.IsSet() ? *NamespaceName : "null") + ":" +
            (UserId.IsSet() ? *UserId : "null") + ":" +
            (RankingName.IsSet() ? *RankingName : "null") + ":" +
            ChildType;
    }

    FString FSubscribeAccessTokenDomain::CreateCacheKey(
        TOptional<FString> RankingName
    )
    {
        return FString("") +
            (RankingName.IsSet() ? *RankingName : "null");
    }

    FSubscribeAccessTokenDomain::FModelTask::FModelTask(
        const TSharedPtr<FSubscribeAccessTokenDomain> Self
    ): Self(Self)
    {

    }

    FSubscribeAccessTokenDomain::FModelTask::FModelTask(
        const FModelTask& From
    ): TGs2Future(From), Self(From.Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FSubscribeAccessTokenDomain::FModelTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Ranking2::Model::FSubscribe>> Result
    )
    {
        const auto Parent = Gs2::Ranking2::Model::Cache::FSubscribeCache::CreateCacheParentKey(
            Self->NamespaceName,
            Self->AccessToken.IsValid() ? Self->AccessToken->GetUserId() : TOptional<FString>(),
            Self->AccessToken.IsValid() ? Self->AccessToken->GetTimeOffset() : TOptional<int32>()
        );
        const auto CacheKey = Gs2::Ranking2::Model::Cache::FSubscribeCache::CreateCacheKey(Self->RankingName);
        return Self->Gs2->Cache->ExecuteWithKeyLock(
            Gs2::Ranking2::Model::FSubscribe::TypeName,
            Parent,
            CacheKey,
            [this, Result, CacheKey]() -> Gs2::Core::Model::FGs2ErrorPtr
            {
                Gs2::Ranking2::Model::FSubscribePtr Value;
                if (Gs2::Ranking2::Model::Cache::FSubscribeCache::TryGet(
                    Self->Gs2->Cache,
                    Self->NamespaceName,
                    Self->AccessToken.IsValid() ? Self->AccessToken->GetUserId() : TOptional<FString>(),
                    Self->RankingName,
                    Self->AccessToken.IsValid() ? Self->AccessToken->GetTimeOffset() : TOptional<int32>(),
                    &Value
                ))
                {
                    *Result = Value;
                }

                return nullptr;
            }
        );
    }

    TSharedPtr<FAsyncTask<FSubscribeAccessTokenDomain::FModelTask>> FSubscribeAccessTokenDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FSubscribeAccessTokenDomain::FModelTask>>(this->AsShared());
    }

    FSubscribeAccessTokenDomain::FSubscribeWithInitialCallTask::FSubscribeWithInitialCallTask(
        const TSharedPtr<FSubscribeAccessTokenDomain> Self,
        const TFunction<void(Gs2::Ranking2::Model::FSubscribePtr)>& Callback
    ): Self(Self), Callback(Callback)
    {
    }

    FSubscribeAccessTokenDomain::FSubscribeWithInitialCallTask::FSubscribeWithInitialCallTask(
        const FSubscribeWithInitialCallTask& From
    ): TGs2Future(From), Self(From.Self), Callback(From.Callback)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FSubscribeAccessTokenDomain::FSubscribeWithInitialCallTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Core::Domain::CallbackID>> Result
    )
    {
        const auto Future = Self->Model();
        Future->StartSynchronousTask();
        Future->EnsureCompletion();
        if (Future->GetTask().IsError())
        {
            return Future->GetTask().Error();
        }
        const auto Item = Future->GetTask().Result();
        const auto ID = Self->Subscribe(Callback);
        Callback(Item);
        *Result = MakeShared<Gs2::Core::Domain::CallbackID>(ID);
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FSubscribeAccessTokenDomain::FSubscribeWithInitialCallTask>> FSubscribeAccessTokenDomain::SubscribeWithInitialCall(
        TFunction<void(Gs2::Ranking2::Model::FSubscribePtr)> Callback
    )
    {
        return Gs2::Core::Util::New<FAsyncTask<FSubscribeWithInitialCallTask>>(this->AsShared(), Callback);
    }

    void FSubscribeAccessTokenDomain::Invalidate()
    {
        Gs2::Ranking2::Model::Cache::FSubscribeCache::Delete(
            Gs2->Cache,
            NamespaceName,
            AccessToken.IsValid() ? AccessToken->GetUserId() : TOptional<FString>(),
            RankingName,
            AccessToken.IsValid() ? AccessToken->GetTimeOffset() : TOptional<int32>()
        );
    }

    Gs2::Core::Domain::CallbackID FSubscribeAccessTokenDomain::Subscribe(
        TFunction<void(Gs2::Ranking2::Model::FSubscribePtr)> Callback
    )
    {
        const TWeakPtr<Gs2::Core::Domain::FGs2> WeakGs2 = Gs2;
        const TWeakPtr<Ranking2::Domain::FGs2Ranking2Domain> WeakService = Service;
        const TOptional<FString> QueryNamespaceName = NamespaceName;
        const TOptional<FString> QueryRankingName = RankingName;
        const auto SourceToken = AccessToken;
        const TOptional<FString> RegisteredUserId = SourceToken.IsValid()
            ? SourceToken->GetUserId()
            : TOptional<FString>();
        const TOptional<int32> RegisteredTimeOffset = SourceToken.IsValid()
            ? SourceToken->GetTimeOffset()
            : TOptional<int32>();
        const auto OwnerSubscriptionParentKey = Gs2::Ranking2::Model::Cache::FSubscribeCache::CreateCacheParentKey(
            QueryNamespaceName,
            RegisteredUserId,
            RegisteredTimeOffset
        );
        const auto OwnerSubscriptionKey = Gs2::Ranking2::Model::Cache::FSubscribeCache::CreateCacheKey(
            QueryRankingName
        );
        return Gs2->Cache->Subscribe(
            Gs2::Ranking2::Model::FSubscribe::TypeName,
            OwnerSubscriptionParentKey,
            OwnerSubscriptionKey,
            [Callback](TSharedPtr<FGs2Object> obj)
            {
                Callback(StaticCastSharedPtr<Gs2::Ranking2::Model::FSubscribe>(obj));
            },
            [WeakGs2, WeakService, QueryNamespaceName, QueryRankingName, SourceToken, RegisteredUserId, RegisteredTimeOffset]()
            {
                const auto Owner = WeakGs2.Pin();
                if (!Owner.IsValid() || !SourceToken.IsValid() || !RegisteredUserId.IsSet())
                {
                    return;
                }
                const auto TokenSnapshot = MakeShared<Gs2::Auth::Model::FAccessToken>(*SourceToken);
                if (TokenSnapshot->GetUserId() != RegisteredUserId || TokenSnapshot->GetTimeOffset() != RegisteredTimeOffset)
                {
                    return;
                }
                const auto Domain = MakeShared<FSubscribeAccessTokenDomain>(
                    Owner,
                    WeakService.Pin(),
                    QueryNamespaceName,
                    TokenSnapshot,
                    QueryRankingName
                );
                const auto Task = Domain->Model();
                Task->StartBackgroundTask();
            }
        );
    }

    void FSubscribeAccessTokenDomain::Unsubscribe(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        Gs2->Cache->Unsubscribe(
            Gs2::Ranking2::Model::FSubscribe::TypeName,
            Gs2::Ranking2::Model::Cache::FSubscribeCache::CreateCacheParentKey(
                NamespaceName,
                AccessToken.IsValid() ? AccessToken->GetUserId() : TOptional<FString>(),
                AccessToken.IsValid() ? AccessToken->GetTimeOffset() : TOptional<int32>()
            ),
            Gs2::Ranking2::Model::Cache::FSubscribeCache::CreateCacheKey(RankingName),
            CallbackID
        );
    }
}

#if defined(_MSC_VER)
#pragma warning (pop)
#elif defined(__clang__)
#pragma clang diagnostic pop
#endif

