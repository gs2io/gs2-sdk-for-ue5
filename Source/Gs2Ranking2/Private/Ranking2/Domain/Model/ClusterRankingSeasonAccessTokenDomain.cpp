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
            Gs2::Ranking2::Domain::Model::FClusterRankingSeasonDomain::CreateCacheParentKey(
                NamespaceName,
                RankingName,
                ClusterName,
                Season,
                "ClusterRankingData"
            ),
            Callback
        );
    }

    void FClusterRankingSeasonAccessTokenDomain::UnsubscribeClusterRankings(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        Gs2->Cache->ListUnsubscribe(
            Gs2::Ranking2::Model::FClusterRankingData::TypeName,
            Gs2::Ranking2::Domain::Model::FClusterRankingSeasonDomain::CreateCacheParentKey(
                NamespaceName,
                RankingName,
                ClusterName,
                Season,
                "ClusterRankingData"
            ),
            CallbackID
        );
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
            ScorerUserId
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
            Gs2::Ranking2::Domain::Model::FClusterRankingSeasonDomain::CreateCacheParentKey(
                NamespaceName,
                RankingName,
                ClusterName,
                Season,
                "ClusterRankingReceivedReward"
            ),
            Callback
        );
    }

    void FClusterRankingSeasonAccessTokenDomain::UnsubscribeClusterRankingReceivedRewards(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        Gs2->Cache->ListUnsubscribe(
            Gs2::Ranking2::Model::FClusterRankingReceivedReward::TypeName,
            Gs2::Ranking2::Domain::Model::FClusterRankingSeasonDomain::CreateCacheParentKey(
                NamespaceName,
                RankingName,
                ClusterName,
                Season,
                "ClusterRankingReceivedReward"
            ),
            CallbackID
        );
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
            Gs2::Ranking2::Domain::Model::FClusterRankingSeasonDomain::CreateCacheParentKey(
                NamespaceName,
                RankingName,
                ClusterName,
                Season,
                "ClusterRankingScore"
            ),
            Callback
        );
    }

    void FClusterRankingSeasonAccessTokenDomain::UnsubscribeClusterRankingScores(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        Gs2->Cache->ListUnsubscribe(
            Gs2::Ranking2::Model::FClusterRankingScore::TypeName,
            Gs2::Ranking2::Domain::Model::FClusterRankingSeasonDomain::CreateCacheParentKey(
                NamespaceName,
                RankingName,
                ClusterName,
                Season,
                "ClusterRankingScore"
            ),
            CallbackID
        );
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

