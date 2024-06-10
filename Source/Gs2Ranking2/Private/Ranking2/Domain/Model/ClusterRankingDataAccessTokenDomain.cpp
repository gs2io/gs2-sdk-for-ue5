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

#include "Ranking2/Domain/Model/ClusterRankingDataAccessToken.h"
#include "Ranking2/Domain/Model/ClusterRankingData.h"
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

    FClusterRankingDataAccessTokenDomain::FClusterRankingDataAccessTokenDomain(
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
            FString::FromInt(*Season),
            "ClusterRankingData"
        ))
    {
    }

    FClusterRankingDataAccessTokenDomain::FClusterRankingDataAccessTokenDomain(
        const FClusterRankingDataAccessTokenDomain& From
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

    FClusterRankingDataAccessTokenDomain::FGetClusterRankingTask::FGetClusterRankingTask(
        const TSharedPtr<FClusterRankingDataAccessTokenDomain>& Self,
        const Request::FGetClusterRankingRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FClusterRankingDataAccessTokenDomain::FGetClusterRankingTask::FGetClusterRankingTask(
        const FGetClusterRankingTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FClusterRankingDataAccessTokenDomain::FGetClusterRankingTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Ranking2::Domain::Model::FClusterRankingDataAccessTokenDomain>> Result
    )
    {
        Request
            ->WithContextStack(Self->Gs2->DefaultContextStack)
            ->WithNamespaceName(Self->NamespaceName)
            ->WithRankingName(Self->RankingName)
            ->WithClusterName(Self->ClusterName)
            ->WithSeason(Self->Season)
            ->WithAccessToken(Self->AccessToken->GetToken());
        const auto Future = Self->Client->GetClusterRanking(
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
                const auto ParentKey = Gs2::Ranking2::Domain::Model::FClusterRankingSeasonDomain::CreateCacheParentKey(
                    Self->NamespaceName,
                    Self->RankingName,
                    Self->ClusterName,
                    FString::FromInt(*Self->Season),
                    "ClusterRankingData"
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
        }
        auto Domain = Self;

        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FClusterRankingDataAccessTokenDomain::FGetClusterRankingTask>> FClusterRankingDataAccessTokenDomain::GetClusterRanking(
        Request::FGetClusterRankingRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FGetClusterRankingTask>>(this->AsShared(), Request);
    }

    FString FClusterRankingDataAccessTokenDomain::CreateCacheParentKey(
        TOptional<FString> NamespaceName,
        TOptional<FString> RankingName,
        TOptional<FString> ClusterName,
        TOptional<FString> Season,
        TOptional<FString> UserId,
        FString ChildType
    )
    {
        return FString("") +
            (NamespaceName.IsSet() ? *NamespaceName : "null") + ":" +
            (RankingName.IsSet() ? *RankingName : "null") + ":" +
            (ClusterName.IsSet() ? *ClusterName : "null") + ":" +
            (Season.IsSet() ? *Season : "null") + ":" +
            (UserId.IsSet() ? *UserId : "null") + ":" +
            ChildType;
    }

    FString FClusterRankingDataAccessTokenDomain::CreateCacheKey(
        TOptional<FString> UserId
    )
    {
        return FString("") +
            (UserId.IsSet() ? *UserId : "null");
    }

    FClusterRankingDataAccessTokenDomain::FModelTask::FModelTask(
        const TSharedPtr<FClusterRankingDataAccessTokenDomain> Self
    ): Self(Self)
    {

    }

    FClusterRankingDataAccessTokenDomain::FModelTask::FModelTask(
        const FModelTask& From
    ): TGs2Future(From), Self(From.Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FClusterRankingDataAccessTokenDomain::FModelTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Ranking2::Model::FClusterRankingData>> Result
    )
    {
        // ReSharper disable once CppLocalVariableMayBeConst
        TSharedPtr<Gs2::Ranking2::Model::FClusterRankingData> Value;
        auto bCacheHit = Self->Gs2->Cache->TryGet<Gs2::Ranking2::Model::FClusterRankingData>(
            Self->ParentKey,
            Gs2::Ranking2::Domain::Model::FClusterRankingDataDomain::CreateCacheKey(
                Self->UserId()
            ),
            &Value
        );
        *Result = Value;

        return nullptr;
    }

    TSharedPtr<FAsyncTask<FClusterRankingDataAccessTokenDomain::FModelTask>> FClusterRankingDataAccessTokenDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FClusterRankingDataAccessTokenDomain::FModelTask>>(this->AsShared());
    }

    Gs2::Core::Domain::CallbackID FClusterRankingDataAccessTokenDomain::Subscribe(
        TFunction<void(Gs2::Ranking2::Model::FClusterRankingDataPtr)> Callback
    )
    {
        return Gs2->Cache->Subscribe(
            Gs2::Ranking2::Model::FClusterRankingData::TypeName,
            ParentKey,
            Gs2::Ranking2::Domain::Model::FClusterRankingDataDomain::CreateCacheKey(
                UserId()
            ),
            [Callback](TSharedPtr<Gs2Object> obj)
            {
                Callback(StaticCastSharedPtr<Gs2::Ranking2::Model::FClusterRankingData>(obj));
            }
        );
    }

    void FClusterRankingDataAccessTokenDomain::Unsubscribe(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        Gs2->Cache->Unsubscribe(
            Gs2::Ranking2::Model::FClusterRankingData::TypeName,
            ParentKey,
            Gs2::Ranking2::Domain::Model::FClusterRankingDataDomain::CreateCacheKey(
                UserId()
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

