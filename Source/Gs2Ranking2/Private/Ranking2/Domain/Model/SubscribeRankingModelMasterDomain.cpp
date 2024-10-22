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

#include "Ranking2/Domain/Model/SubscribeRankingModelMaster.h"
#include "Ranking2/Domain/Model/Namespace.h"
#include "Ranking2/Domain/Model/GlobalRankingModel.h"
#include "Ranking2/Domain/Model/GlobalRankingModelMaster.h"
#include "Ranking2/Domain/Model/GlobalRankingScore.h"
#include "Ranking2/Domain/Model/GlobalRankingScoreAccessToken.h"
#include "Ranking2/Domain/Model/GlobalRankingReceivedReward.h"
#include "Ranking2/Domain/Model/GlobalRankingReceivedRewardAccessToken.h"
#include "Ranking2/Domain/Model/GlobalRankingSeason.h"
#include "Ranking2/Domain/Model/GlobalRankingData.h"
#include "Ranking2/Domain/Model/GlobalRankingDataAccessToken.h"
#include "Ranking2/Domain/Model/ClusterRankingModel.h"
#include "Ranking2/Domain/Model/ClusterRankingModelMaster.h"
#include "Ranking2/Domain/Model/ClusterRankingScore.h"
#include "Ranking2/Domain/Model/ClusterRankingScoreAccessToken.h"
#include "Ranking2/Domain/Model/ClusterRankingReceivedReward.h"
#include "Ranking2/Domain/Model/ClusterRankingReceivedRewardAccessToken.h"
#include "Ranking2/Domain/Model/ClusterRankingSeason.h"
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
#include "Core/Domain/Transaction/ManualTransactionDomain.h"

namespace Gs2::Ranking2::Domain::Model
{

    FSubscribeRankingModelMasterDomain::FSubscribeRankingModelMasterDomain(
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
            "SubscribeRankingModelMaster"
        ))
    {
    }

    FSubscribeRankingModelMasterDomain::FSubscribeRankingModelMasterDomain(
        const FSubscribeRankingModelMasterDomain& From
    ):
        Gs2(From.Gs2),
        Service(From.Service),
        Client(From.Client),
        NamespaceName(From.NamespaceName),
        RankingName(From.RankingName),
        ParentKey(From.ParentKey)
    {

    }

    FSubscribeRankingModelMasterDomain::FGetTask::FGetTask(
        const TSharedPtr<FSubscribeRankingModelMasterDomain>& Self,
        const Request::FGetSubscribeRankingModelMasterRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FSubscribeRankingModelMasterDomain::FGetTask::FGetTask(
        const FGetTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FSubscribeRankingModelMasterDomain::FGetTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Ranking2::Model::FSubscribeRankingModelMaster>> Result
    )
    {
        Request
            ->WithContextStack(Self->Gs2->DefaultContextStack)
            ->WithNamespaceName(Self->NamespaceName)
            ->WithRankingName(Self->RankingName);
        const auto Future = Self->Client->GetSubscribeRankingModelMaster(
            Request
        );
        Future->StartSynchronousTask();
        if (Future->GetTask().IsError())
        {
            return Future->GetTask().Error();
        }
        const auto RequestModel = Request;
        const auto ResultModel = Future->GetTask().Result();
        Future->EnsureCompletion();
        if (ResultModel != nullptr) {
            
            if (ResultModel->GetItem() != nullptr)
            {
                const auto ParentKey = Gs2::Ranking2::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
                    Self->NamespaceName,
                    "SubscribeRankingModelMaster"
                );
                const auto Key = Gs2::Ranking2::Domain::Model::FSubscribeRankingModelMasterDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetName()
                );
                Self->Gs2->Cache->Put(
                    Gs2::Ranking2::Model::FSubscribeRankingModelMaster::TypeName,
                    ParentKey,
                    Key,
                    ResultModel->GetItem(),
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );
            }
        }
        *Result = ResultModel->GetItem();
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FSubscribeRankingModelMasterDomain::FGetTask>> FSubscribeRankingModelMasterDomain::Get(
        Request::FGetSubscribeRankingModelMasterRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FGetTask>>(this->AsShared(), Request);
    }

    FSubscribeRankingModelMasterDomain::FUpdateTask::FUpdateTask(
        const TSharedPtr<FSubscribeRankingModelMasterDomain>& Self,
        const Request::FUpdateSubscribeRankingModelMasterRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FSubscribeRankingModelMasterDomain::FUpdateTask::FUpdateTask(
        const FUpdateTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FSubscribeRankingModelMasterDomain::FUpdateTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Ranking2::Domain::Model::FSubscribeRankingModelMasterDomain>> Result
    )
    {
        Request
            ->WithContextStack(Self->Gs2->DefaultContextStack)
            ->WithNamespaceName(Self->NamespaceName)
            ->WithRankingName(Self->RankingName);
        const auto Future = Self->Client->UpdateSubscribeRankingModelMaster(
            Request
        );
        Future->StartSynchronousTask();
        if (Future->GetTask().IsError())
        {
            return Future->GetTask().Error();
        }
        const auto RequestModel = Request;
        const auto ResultModel = Future->GetTask().Result();
        Future->EnsureCompletion();
        if (ResultModel != nullptr) {
            
            if (ResultModel->GetItem() != nullptr)
            {
                const auto ParentKey = Gs2::Ranking2::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
                    Self->NamespaceName,
                    "SubscribeRankingModelMaster"
                );
                const auto Key = Gs2::Ranking2::Domain::Model::FSubscribeRankingModelMasterDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetName()
                );
                Self->Gs2->Cache->Put(
                    Gs2::Ranking2::Model::FSubscribeRankingModelMaster::TypeName,
                    ParentKey,
                    Key,
                    ResultModel->GetItem(),
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );
            }
        }
        auto Domain = Self;

        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FSubscribeRankingModelMasterDomain::FUpdateTask>> FSubscribeRankingModelMasterDomain::Update(
        Request::FUpdateSubscribeRankingModelMasterRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FUpdateTask>>(this->AsShared(), Request);
    }

    FSubscribeRankingModelMasterDomain::FDeleteTask::FDeleteTask(
        const TSharedPtr<FSubscribeRankingModelMasterDomain>& Self,
        const Request::FDeleteSubscribeRankingModelMasterRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FSubscribeRankingModelMasterDomain::FDeleteTask::FDeleteTask(
        const FDeleteTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FSubscribeRankingModelMasterDomain::FDeleteTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Ranking2::Domain::Model::FSubscribeRankingModelMasterDomain>> Result
    )
    {
        Request
            ->WithContextStack(Self->Gs2->DefaultContextStack)
            ->WithNamespaceName(Self->NamespaceName)
            ->WithRankingName(Self->RankingName);
        const auto Future = Self->Client->DeleteSubscribeRankingModelMaster(
            Request
        );
        Future->StartSynchronousTask();
        if (Future->GetTask().IsError())
        {
            return Future->GetTask().Error();
        }
        const auto RequestModel = Request;
        const auto ResultModel = Future->GetTask().Result();
        Future->EnsureCompletion();
        if (ResultModel != nullptr) {
            
            if (ResultModel->GetItem() != nullptr)
            {
                const auto ParentKey = Gs2::Ranking2::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
                    Self->NamespaceName,
                    "SubscribeRankingModelMaster"
                );
                const auto Key = Gs2::Ranking2::Domain::Model::FSubscribeRankingModelMasterDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetName()
                );
                Self->Gs2->Cache->Delete(Gs2::Ranking2::Model::FSubscribeRankingModelMaster::TypeName, ParentKey, Key);
            }
        }
        auto Domain = Self;

        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FSubscribeRankingModelMasterDomain::FDeleteTask>> FSubscribeRankingModelMasterDomain::Delete(
        Request::FDeleteSubscribeRankingModelMasterRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FDeleteTask>>(this->AsShared(), Request);
    }

    FString FSubscribeRankingModelMasterDomain::CreateCacheParentKey(
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

    FString FSubscribeRankingModelMasterDomain::CreateCacheKey(
        TOptional<FString> RankingName
    )
    {
        return FString("") +
            (RankingName.IsSet() ? *RankingName : "null");
    }

    FSubscribeRankingModelMasterDomain::FModelTask::FModelTask(
        const TSharedPtr<FSubscribeRankingModelMasterDomain> Self
    ): Self(Self)
    {

    }

    FSubscribeRankingModelMasterDomain::FModelTask::FModelTask(
        const FModelTask& From
    ): TGs2Future(From), Self(From.Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FSubscribeRankingModelMasterDomain::FModelTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Ranking2::Model::FSubscribeRankingModelMaster>> Result
    )
    {
        // ReSharper disable once CppLocalVariableMayBeConst
        TSharedPtr<Gs2::Ranking2::Model::FSubscribeRankingModelMaster> Value;
        auto bCacheHit = Self->Gs2->Cache->TryGet<Gs2::Ranking2::Model::FSubscribeRankingModelMaster>(
            Self->ParentKey,
            Gs2::Ranking2::Domain::Model::FSubscribeRankingModelMasterDomain::CreateCacheKey(
                Self->RankingName
            ),
            &Value
        );
        if (!bCacheHit) {
            const auto Future = Self->Get(
                MakeShared<Gs2::Ranking2::Request::FGetSubscribeRankingModelMasterRequest>()
            );
            Future->StartSynchronousTask();
            if (Future->GetTask().IsError())
            {
                if (Future->GetTask().Error()->Type() != Gs2::Core::Model::FNotFoundError::TypeString)
                {
                    return Future->GetTask().Error();
                }

                const auto Key = Gs2::Ranking2::Domain::Model::FSubscribeRankingModelMasterDomain::CreateCacheKey(
                    Self->RankingName
                );
                Self->Gs2->Cache->Put(
                    Gs2::Ranking2::Model::FSubscribeRankingModelMaster::TypeName,
                    Self->ParentKey,
                    Key,
                    nullptr,
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );

                if (Future->GetTask().Error()->Detail(0)->GetComponent() != "subscribeRankingModelMaster")
                {
                    return Future->GetTask().Error();
                }
            }
            Self->Gs2->Cache->TryGet<Gs2::Ranking2::Model::FSubscribeRankingModelMaster>(
                Self->ParentKey,
                Gs2::Ranking2::Domain::Model::FSubscribeRankingModelMasterDomain::CreateCacheKey(
                    Self->RankingName
                ),
                &Value
            );
            Future->EnsureCompletion();
        }
        *Result = Value;

        return nullptr;
    }

    TSharedPtr<FAsyncTask<FSubscribeRankingModelMasterDomain::FModelTask>> FSubscribeRankingModelMasterDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FSubscribeRankingModelMasterDomain::FModelTask>>(this->AsShared());
    }

    Gs2::Core::Domain::CallbackID FSubscribeRankingModelMasterDomain::Subscribe(
        TFunction<void(Gs2::Ranking2::Model::FSubscribeRankingModelMasterPtr)> Callback
    )
    {
        return Gs2->Cache->Subscribe(
            Gs2::Ranking2::Model::FSubscribeRankingModelMaster::TypeName,
            ParentKey,
            Gs2::Ranking2::Domain::Model::FSubscribeRankingModelMasterDomain::CreateCacheKey(
                RankingName
            ),
            [Callback](TSharedPtr<FGs2Object> obj)
            {
                Callback(StaticCastSharedPtr<Gs2::Ranking2::Model::FSubscribeRankingModelMaster>(obj));
            }
        );
    }

    void FSubscribeRankingModelMasterDomain::Unsubscribe(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        Gs2->Cache->Unsubscribe(
            Gs2::Ranking2::Model::FSubscribeRankingModelMaster::TypeName,
            ParentKey,
            Gs2::Ranking2::Domain::Model::FSubscribeRankingModelMasterDomain::CreateCacheKey(
                RankingName
            ),
            CallbackID
        );
    }
}

#if defined(_MSC_VER)
#pragma warning (pop)
#elif defined(__clang__)
#pragma clang diagnostic pop
#endif

