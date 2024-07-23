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
        RankingName(RankingName),
        ParentKey(Gs2::Ranking2::Domain::Model::FUserDomain::CreateCacheParentKey(
            NamespaceName,
            UserId(),
            "Subscribe"
        ))
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
        RankingName(From.RankingName),
        ParentKey(From.ParentKey)
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
        Request
            ->WithContextStack(Self->Gs2->DefaultContextStack)
            ->WithNamespaceName(Self->NamespaceName)
            ->WithRankingName(Self->RankingName)
            ->WithAccessToken(Self->AccessToken->GetToken());
        const auto Future = Self->Client->AddSubscribe(
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
                const auto ParentKey = Gs2::Ranking2::Domain::Model::FSubscribeDomain::CreateCacheParentKey(
                    Self->NamespaceName,
                    Self->UserId(),
                    Self->RankingName,
                    "SubscribeUser"
                );
                const auto Key = Gs2::Ranking2::Domain::Model::FSubscribeUserDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetTargetUserId()
                );
                Self->Gs2->Cache->Put(
                    Gs2::Ranking2::Model::FSubscribeUser::TypeName,
                    ParentKey,
                    Key,
                    ResultModel->GetItem(),
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );
            }
        }
        auto Domain = MakeShared<Gs2::Ranking2::Domain::Model::FSubscribeUserAccessTokenDomain>(
            Self->Gs2,
            Self->Service,
            Request->GetNamespaceName(),
            Self->AccessToken,
            ResultModel->GetItem()->GetRankingName(),
            ResultModel->GetItem()->GetTargetUserId()
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
        // ReSharper disable once CppLocalVariableMayBeConst
        TSharedPtr<Gs2::Ranking2::Model::FSubscribe> Value;
        auto bCacheHit = Self->Gs2->Cache->TryGet<Gs2::Ranking2::Model::FSubscribe>(
            Self->ParentKey,
            Gs2::Ranking2::Domain::Model::FSubscribeDomain::CreateCacheKey(
                Self->RankingName
            ),
            &Value
        );
        *Result = Value;

        return nullptr;
    }

    TSharedPtr<FAsyncTask<FSubscribeAccessTokenDomain::FModelTask>> FSubscribeAccessTokenDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FSubscribeAccessTokenDomain::FModelTask>>(this->AsShared());
    }

    Gs2::Core::Domain::CallbackID FSubscribeAccessTokenDomain::Subscribe(
        TFunction<void(Gs2::Ranking2::Model::FSubscribePtr)> Callback
    )
    {
        return Gs2->Cache->Subscribe(
            Gs2::Ranking2::Model::FSubscribe::TypeName,
            ParentKey,
            Gs2::Ranking2::Domain::Model::FSubscribeDomain::CreateCacheKey(
                RankingName
            ),
            [Callback](TSharedPtr<Gs2Object> obj)
            {
                Callback(StaticCastSharedPtr<Gs2::Ranking2::Model::FSubscribe>(obj));
            }
        );
    }

    void FSubscribeAccessTokenDomain::Unsubscribe(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        Gs2->Cache->Unsubscribe(
            Gs2::Ranking2::Model::FSubscribe::TypeName,
            ParentKey,
            Gs2::Ranking2::Domain::Model::FSubscribeDomain::CreateCacheKey(
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

