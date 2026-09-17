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

#include "Ranking2/Domain/Model/ClusterRankingModelMaster.h"
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
#include "Ranking2/Model/Cache/ClusterRankingModelMaster.h"

#include "Core/Domain/Gs2.h"
#include "Core/Domain/Transaction/JobQueueJobDomainFactory.h"
#include "Core/Domain/Transaction/InternalTransactionDomainFactory.h"
#include "Core/Domain/Transaction/ManualTransactionDomain.h"

namespace Gs2::Ranking2::Domain::Model
{

    FClusterRankingModelMasterDomain::FClusterRankingModelMasterDomain(
        const Core::Domain::FGs2Ptr& Gs2,
        const Ranking2::Domain::FGs2Ranking2DomainPtr& Service,
        const TOptional<FString> NamespaceName,
        const TOptional<FString> RankingName
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Gs2(Gs2),
        Service(Service),
        Client(MakeShared<Gs2::Ranking2::FGs2Ranking2RestClient>(Gs2->RestSession)),
        NamespaceName(NamespaceName),
        RankingName(RankingName),
        ParentKey(Gs2::Ranking2::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
            NamespaceName,
            "ClusterRankingModelMaster"
        ))
    {
    }

    FClusterRankingModelMasterDomain::FClusterRankingModelMasterDomain(
        const FClusterRankingModelMasterDomain& From
    ):
        Gs2(From.Gs2),
        Service(From.Service),
        Client(From.Client),
        NamespaceName(From.NamespaceName),
        RankingName(From.RankingName),
        ParentKey(From.ParentKey)
    {

    }

    FClusterRankingModelMasterDomain::FGetTask::FGetTask(
        const TSharedPtr<FClusterRankingModelMasterDomain>& Self,
        const Request::FGetClusterRankingModelMasterRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FClusterRankingModelMasterDomain::FGetTask::FGetTask(
        const FGetTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FClusterRankingModelMasterDomain::FGetTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Ranking2::Model::FClusterRankingModelMaster>> Result
    )
    {
        Request
            ->WithContextStack((!Request->GetContextStack().IsSet() || Request->GetContextStack()->IsEmpty()) ? Self->Gs2->DefaultContextStack : Request->GetContextStack())
            ->WithNamespaceName(Self->NamespaceName)
            ->WithRankingName(Self->RankingName);
        const auto Future = Self->Client->GetClusterRankingModelMaster(
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


        Gs2::Ranking2::Model::Cache::FClusterRankingModelMasterCache::Put(
            Self->Gs2->Cache,

            Request->GetNamespaceName(),
            Request->GetRankingName(),
            TOptional<int32>(),
            ResultModel->GetItem()
        );
            }
        *Result = ResultModel->GetItem();
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FClusterRankingModelMasterDomain::FGetTask>> FClusterRankingModelMasterDomain::Get(
        Request::FGetClusterRankingModelMasterRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FGetTask>>(this->AsShared(), Request);
    }

    FClusterRankingModelMasterDomain::FUpdateTask::FUpdateTask(
        const TSharedPtr<FClusterRankingModelMasterDomain>& Self,
        const Request::FUpdateClusterRankingModelMasterRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FClusterRankingModelMasterDomain::FUpdateTask::FUpdateTask(
        const FUpdateTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FClusterRankingModelMasterDomain::FUpdateTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Ranking2::Domain::Model::FClusterRankingModelMasterDomain>> Result
    )
    {
        Request
            ->WithContextStack((!Request->GetContextStack().IsSet() || Request->GetContextStack()->IsEmpty()) ? Self->Gs2->DefaultContextStack : Request->GetContextStack())
            ->WithNamespaceName(Self->NamespaceName)
            ->WithRankingName(Self->RankingName);
        const auto Future = Self->Client->UpdateClusterRankingModelMaster(
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


        Gs2::Ranking2::Model::Cache::FClusterRankingModelMasterCache::Put(
            Self->Gs2->Cache,

            Request->GetNamespaceName(),
            Request->GetRankingName(),
            TOptional<int32>(),
            ResultModel->GetItem()
        );
            }
        auto Domain = Self;

        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FClusterRankingModelMasterDomain::FUpdateTask>> FClusterRankingModelMasterDomain::Update(
        Request::FUpdateClusterRankingModelMasterRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FUpdateTask>>(this->AsShared(), Request);
    }

    FClusterRankingModelMasterDomain::FDeleteTask::FDeleteTask(
        const TSharedPtr<FClusterRankingModelMasterDomain>& Self,
        const Request::FDeleteClusterRankingModelMasterRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FClusterRankingModelMasterDomain::FDeleteTask::FDeleteTask(
        const FDeleteTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FClusterRankingModelMasterDomain::FDeleteTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Ranking2::Domain::Model::FClusterRankingModelMasterDomain>> Result
    )
    {
        Request
            ->WithContextStack((!Request->GetContextStack().IsSet() || Request->GetContextStack()->IsEmpty()) ? Self->Gs2->DefaultContextStack : Request->GetContextStack())
            ->WithNamespaceName(Self->NamespaceName)
            ->WithRankingName(Self->RankingName);
        const auto Future = Self->Client->DeleteClusterRankingModelMaster(
            Request
        );
        Future->StartSynchronousTask();
        if (Future->GetTask().IsError())
        {
            const auto Error = Future->GetTask().Error();
            if (Error.IsValid() && Error->IsChildOf(Gs2::Core::Model::FNotFoundError::Class))
            {
                *Result = Self;
                return nullptr;
            }
            return Error;
        }
        const auto ResultModel = Future->GetTask().Result();
        Future->EnsureCompletion();


              Gs2::Ranking2::Model::Cache::FClusterRankingModelMasterCache::Delete(
            Self->Gs2->Cache,

            Request->GetNamespaceName(),
            Request->GetRankingName(),
            TOptional<int32>()
        );
        auto Domain = Self;

        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FClusterRankingModelMasterDomain::FDeleteTask>> FClusterRankingModelMasterDomain::Delete(
        Request::FDeleteClusterRankingModelMasterRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FDeleteTask>>(this->AsShared(), Request);
    }

    FString FClusterRankingModelMasterDomain::CreateCacheParentKey(
        TOptional<FString> NamespaceName,
        TOptional<FString> RankingName,
        FString ChildType
    )
    {
        return FString("") +
            (NamespaceName.IsSet() ? *NamespaceName : "null") + ":" +
            (RankingName.IsSet() ? *RankingName : "null") + ":" +
            ChildType;
    }

    FString FClusterRankingModelMasterDomain::CreateCacheKey(
        TOptional<FString> RankingName
    )
    {
        return FString("") +
            (RankingName.IsSet() ? *RankingName : "null");
    }

    FClusterRankingModelMasterDomain::FModelTask::FModelTask(
        const TSharedPtr<FClusterRankingModelMasterDomain> Self
    ): Self(Self)
    {

    }

    FClusterRankingModelMasterDomain::FModelTask::FModelTask(
        const FModelTask& From
    ): TGs2Future(From), Self(From.Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FClusterRankingModelMasterDomain::FModelTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Ranking2::Model::FClusterRankingModelMaster>> Result
    )
    {
        const auto CacheParentKey = Gs2::Ranking2::Model::Cache::FClusterRankingModelMasterCache::CreateCacheParentKey(

            Self->NamespaceName,
            TOptional<int32>()
        );
        const auto CacheKey = Gs2::Ranking2::Model::Cache::FClusterRankingModelMasterCache::CreateCacheKey(

            Self->RankingName
        );
        return Self->Gs2->Cache->ExecuteWithKeyLock(
            Gs2::Ranking2::Model::FClusterRankingModelMaster::TypeName,
            CacheParentKey,
            CacheKey,
            [Self = Self, Result]() -> Gs2::Core::Model::FGs2ErrorPtr
            {
                Gs2::Ranking2::Model::FClusterRankingModelMasterPtr Value;
                const auto CacheHit = Gs2::Ranking2::Model::Cache::FClusterRankingModelMasterCache::TryGet(
                    Self->Gs2->Cache,

                    Self->NamespaceName,
                    Self->RankingName,
                    TOptional<int32>(),
                    &Value
                );
                if (CacheHit)
                {
                    *Result = Value;
                    return nullptr;
                }
                const auto Error = Gs2::Ranking2::Model::Cache::FClusterRankingModelMasterCache::Fetch(
                    Self->Gs2->Cache,

                    Self->NamespaceName,
                    Self->RankingName,
                    TOptional<int32>(),
                    [Self](Gs2::Ranking2::Model::FClusterRankingModelMasterPtr* OutItem) -> Gs2::Core::Model::FGs2ErrorPtr
                    {
                        const auto Future = Self->Get(
                            MakeShared<Gs2::Ranking2::Request::FGetClusterRankingModelMasterRequest>()
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

    TSharedPtr<FAsyncTask<FClusterRankingModelMasterDomain::FModelTask>> FClusterRankingModelMasterDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FClusterRankingModelMasterDomain::FModelTask>>(this->AsShared());
    }

    void FClusterRankingModelMasterDomain::Invalidate()
    {
        Gs2::Ranking2::Model::Cache::FClusterRankingModelMasterCache::Delete(
            Gs2->Cache,

            NamespaceName,
            RankingName,
            TOptional<int32>()
        );
    }

    FClusterRankingModelMasterDomain::FSubscribeWithInitialCallTask::FSubscribeWithInitialCallTask(
        const TSharedPtr<FClusterRankingModelMasterDomain>& Self,
        TFunction<void(Gs2::Ranking2::Model::FClusterRankingModelMasterPtr)> Callback
    ):
        Self(Self),
        Callback(Callback)
    {
    }

    FClusterRankingModelMasterDomain::FSubscribeWithInitialCallTask::FSubscribeWithInitialCallTask(
        const FSubscribeWithInitialCallTask& From
    ):
        TGs2Future(From),
        Self(From.Self),
        Callback(From.Callback)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FClusterRankingModelMasterDomain::FSubscribeWithInitialCallTask::Action(
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

    TSharedPtr<FAsyncTask<FClusterRankingModelMasterDomain::FSubscribeWithInitialCallTask>> FClusterRankingModelMasterDomain::SubscribeWithInitialCall(
        TFunction<void(Gs2::Ranking2::Model::FClusterRankingModelMasterPtr)> Callback
    )
    {
        return Gs2::Core::Util::New<FAsyncTask<FSubscribeWithInitialCallTask>>(this->AsShared(), Callback);
    }

    Gs2::Core::Domain::CallbackID FClusterRankingModelMasterDomain::Subscribe(
        TFunction<void(Gs2::Ranking2::Model::FClusterRankingModelMasterPtr)> Callback
    )
    {
        const auto SubscriptionParentKey = Gs2::Ranking2::Model::Cache::FClusterRankingModelMasterCache::CreateCacheParentKey(

            NamespaceName,
            TOptional<int32>()
        );
        const auto SubscriptionCacheKey = Gs2::Ranking2::Model::Cache::FClusterRankingModelMasterCache::CreateCacheKey(

            RankingName
        );
        const TWeakPtr<Gs2::Core::Domain::FGs2> WeakGs2 = Gs2;
        const TWeakPtr<Ranking2::Domain::FGs2Ranking2Domain> WeakService = Service;
        const FString RegisteredParentKey = SubscriptionParentKey;
        const TOptional<FString> QueryNamespaceName = NamespaceName;
        const TOptional<FString> QueryRankingName = RankingName;
        return Gs2->Cache->Subscribe(
            Gs2::Ranking2::Model::FClusterRankingModelMaster::TypeName,
            SubscriptionParentKey,
            SubscriptionCacheKey,
            [Callback](TSharedPtr<FGs2Object> obj)
            {
                Callback(StaticCastSharedPtr<Gs2::Ranking2::Model::FClusterRankingModelMaster>(obj));
            },
            [WeakGs2, WeakService, RegisteredParentKey, QueryNamespaceName, QueryRankingName]()
            {
                const auto Owner = WeakGs2.Pin();
                if (!Owner.IsValid())
                {
                    return;
                }
                const auto Domain = MakeShared<FClusterRankingModelMasterDomain>(
                    Owner,
                    WeakService.Pin(),
                    QueryNamespaceName,
                    QueryRankingName
                );
                Domain->ParentKey = RegisteredParentKey;
                const auto Task = Domain->Model();
                Task->StartBackgroundTask();
            }
        );
    }

    void FClusterRankingModelMasterDomain::Unsubscribe(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        const auto SubscriptionParentKey = Gs2::Ranking2::Model::Cache::FClusterRankingModelMasterCache::CreateCacheParentKey(

            NamespaceName,
            TOptional<int32>()
        );
        const auto SubscriptionCacheKey = Gs2::Ranking2::Model::Cache::FClusterRankingModelMasterCache::CreateCacheKey(

            RankingName
        );
        Gs2->Cache->Unsubscribe(
            Gs2::Ranking2::Model::FClusterRankingModelMaster::TypeName,
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
