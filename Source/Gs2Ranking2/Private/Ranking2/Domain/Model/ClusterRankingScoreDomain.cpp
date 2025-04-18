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
#include "Core/Domain/Transaction/ManualTransactionDomain.h"

namespace Gs2::Ranking2::Domain::Model
{

    FClusterRankingScoreDomain::FClusterRankingScoreDomain(
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
        ParentKey(Gs2::Ranking2::Domain::Model::FClusterRankingSeasonDomain::CreateCacheParentKey(
            NamespaceName,
            RankingName,
            ClusterName,
            Season,
            "ClusterRankingScore"
        ))
    {
    }

    FClusterRankingScoreDomain::FClusterRankingScoreDomain(
        const FClusterRankingScoreDomain& From
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

    FClusterRankingScoreDomain::FGetTask::FGetTask(
        const TSharedPtr<FClusterRankingScoreDomain>& Self,
        const Request::FGetClusterRankingScoreByUserIdRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FClusterRankingScoreDomain::FGetTask::FGetTask(
        const FGetTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FClusterRankingScoreDomain::FGetTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Ranking2::Model::FClusterRankingScore>> Result
    )
    {
        Request
            ->WithContextStack(Self->Gs2->DefaultContextStack)
            ->WithNamespaceName(Self->NamespaceName)
            ->WithRankingName(Self->RankingName)
            ->WithClusterName(Self->ClusterName)
            ->WithUserId(Self->UserId)
            ->WithSeason(Self->Season);
        *Result = ResultModel->GetItem();
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FClusterRankingScoreDomain::FGetTask>> FClusterRankingScoreDomain::Get(
        Request::FGetClusterRankingScoreByUserIdRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FGetTask>>(this->AsShared(), Request);
    }

    FClusterRankingScoreDomain::FDeleteTask::FDeleteTask(
        const TSharedPtr<FClusterRankingScoreDomain>& Self,
        const Request::FDeleteClusterRankingScoreByUserIdRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FClusterRankingScoreDomain::FDeleteTask::FDeleteTask(
        const FDeleteTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FClusterRankingScoreDomain::FDeleteTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Ranking2::Domain::Model::FClusterRankingScoreDomain>> Result
    )
    {
        Request
            ->WithContextStack(Self->Gs2->DefaultContextStack)
            ->WithNamespaceName(Self->NamespaceName)
            ->WithRankingName(Self->RankingName)
            ->WithClusterName(Self->ClusterName)
            ->WithUserId(Self->UserId)
            ->WithSeason(Self->Season);
        auto Domain = Self;

        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FClusterRankingScoreDomain::FDeleteTask>> FClusterRankingScoreDomain::Delete(
        Request::FDeleteClusterRankingScoreByUserIdRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FDeleteTask>>(this->AsShared(), Request);
    }

    FClusterRankingScoreDomain::FVerifyTask::FVerifyTask(
        const TSharedPtr<FClusterRankingScoreDomain>& Self,
        const Request::FVerifyClusterRankingScoreByUserIdRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FClusterRankingScoreDomain::FVerifyTask::FVerifyTask(
        const FVerifyTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FClusterRankingScoreDomain::FVerifyTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Ranking2::Domain::Model::FClusterRankingScoreDomain>> Result
    )
    {
        Request
            ->WithContextStack(Self->Gs2->DefaultContextStack)
            ->WithNamespaceName(Self->NamespaceName)
            ->WithUserId(Self->UserId)
            ->WithRankingName(Self->RankingName)
            ->WithClusterName(Self->ClusterName)
            ->WithSeason(Self->Season);
        auto Domain = Self;

        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FClusterRankingScoreDomain::FVerifyTask>> FClusterRankingScoreDomain::Verify(
        Request::FVerifyClusterRankingScoreByUserIdRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FVerifyTask>>(this->AsShared(), Request);
    }

    FString FClusterRankingScoreDomain::CreateCacheParentKey(
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

    FString FClusterRankingScoreDomain::CreateCacheKey(
        TOptional<FString> ClusterName,
        TOptional<FString> Season,
        TOptional<FString> UserId
    )
    {
        return FString("") +
            (ClusterName.IsSet() ? *ClusterName : "null") + ":" + 
            (Season.IsSet() ? *Season : "null") + ":" + 
            (UserId.IsSet() ? *UserId : "null");
    }

    FClusterRankingScoreDomain::FModelTask::FModelTask(
        const TSharedPtr<FClusterRankingScoreDomain> Self
    ): Self(Self)
    {

    }

    FClusterRankingScoreDomain::FModelTask::FModelTask(
        const FModelTask& From
    ): TGs2Future(From), Self(From.Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FClusterRankingScoreDomain::FModelTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Ranking2::Model::FClusterRankingScore>> Result
    )
    {
        // ReSharper disable once CppLocalVariableMayBeConst
        TSharedPtr<Gs2::Ranking2::Model::FClusterRankingScore> Value;
        auto bCacheHit = Self->Gs2->Cache->TryGet<Gs2::Ranking2::Model::FClusterRankingScore>(
            Self->ParentKey,
            Gs2::Ranking2::Domain::Model::FClusterRankingScoreDomain::CreateCacheKey(
                Self->ClusterName,
                Self->Season.IsSet() ? FString::FromInt(*Self->Season) : TOptional<FString>(),
                Self->UserId
            ),
            &Value
        );
        if (!bCacheHit) {
            const auto Future = Self->Get(
                MakeShared<Gs2::Ranking2::Request::FGetClusterRankingScoreByUserIdRequest>()
            );
            Future->StartSynchronousTask();
            if (Future->GetTask().IsError())
            {
                if (Future->GetTask().Error()->Type() != Gs2::Core::Model::FNotFoundError::TypeString)
                {
                    return Future->GetTask().Error();
                }

                const auto Key = Gs2::Ranking2::Domain::Model::FClusterRankingScoreDomain::CreateCacheKey(
                    Self->ClusterName,
                    Self->Season.IsSet() ? FString::FromInt(*Self->Season) : TOptional<FString>(),
                    Self->UserId
                );
                Self->Gs2->Cache->Put(
                    Gs2::Ranking2::Model::FClusterRankingScore::TypeName,
                    Self->ParentKey,
                    Key,
                    nullptr,
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );

                if (Future->GetTask().Error()->Detail(0)->GetComponent() != "clusterRankingScore")
                {
                    return Future->GetTask().Error();
                }
            }
            Self->Gs2->Cache->TryGet<Gs2::Ranking2::Model::FClusterRankingScore>(
                Self->ParentKey,
                Gs2::Ranking2::Domain::Model::FClusterRankingScoreDomain::CreateCacheKey(
                    Self->ClusterName,
                    Self->Season.IsSet() ? FString::FromInt(*Self->Season) : TOptional<FString>(),
                    Self->UserId
                ),
                &Value
            );
            Future->EnsureCompletion();
        }
        *Result = Value;

        return nullptr;
    }

    TSharedPtr<FAsyncTask<FClusterRankingScoreDomain::FModelTask>> FClusterRankingScoreDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FClusterRankingScoreDomain::FModelTask>>(this->AsShared());
    }

    Gs2::Core::Domain::CallbackID FClusterRankingScoreDomain::Subscribe(
        TFunction<void(Gs2::Ranking2::Model::FClusterRankingScorePtr)> Callback
    )
    {
        return Gs2->Cache->Subscribe(
            Gs2::Ranking2::Model::FClusterRankingScore::TypeName,
            ParentKey,
            Gs2::Ranking2::Domain::Model::FClusterRankingScoreDomain::CreateCacheKey(
                ClusterName,
                Season.IsSet() ? FString::FromInt(*Season) : TOptional<FString>(),
                UserId
            ),
            [Callback](TSharedPtr<FGs2Object> obj)
            {
                Callback(StaticCastSharedPtr<Gs2::Ranking2::Model::FClusterRankingScore>(obj));
            }
        );
    }

    void FClusterRankingScoreDomain::Unsubscribe(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        Gs2->Cache->Unsubscribe(
            Gs2::Ranking2::Model::FClusterRankingScore::TypeName,
            ParentKey,
            Gs2::Ranking2::Domain::Model::FClusterRankingScoreDomain::CreateCacheKey(
                ClusterName,
                Season.IsSet() ? FString::FromInt(*Season) : TOptional<FString>(),
                UserId
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

