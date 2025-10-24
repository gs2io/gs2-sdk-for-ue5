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

#include "Ranking2/Domain/Model/GlobalRankingSeasonAccessToken.h"
#include "Ranking2/Domain/Model/GlobalRankingSeason.h"
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

    FGlobalRankingSeasonAccessTokenDomain::FGlobalRankingSeasonAccessTokenDomain(
        const Core::Domain::FGs2Ptr& Gs2,
        const Ranking2::Domain::FGs2Ranking2DomainPtr& Service,
        const TOptional<FString> NamespaceName,
        const TOptional<FString> RankingName,
        const TOptional<int64> Season,
        const Gs2::Auth::Model::FAccessTokenPtr& AccessToken
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Gs2(Gs2),
        Service(Service),
        Client(MakeShared<Gs2::Ranking2::FGs2Ranking2RestClient>(Gs2->RestSession)),
        NamespaceName(NamespaceName),
        RankingName(RankingName),
        Season(Season),
        AccessToken(AccessToken),
        ParentKey(Gs2::Ranking2::Domain::Model::FGlobalRankingModelDomain::CreateCacheParentKey(
            NamespaceName,
            RankingName,
            "GlobalRankingSeason"
        ))
    {
    }

    FGlobalRankingSeasonAccessTokenDomain::FGlobalRankingSeasonAccessTokenDomain(
        const FGlobalRankingSeasonAccessTokenDomain& From
    ):
        Gs2(From.Gs2),
        Service(From.Service),
        Client(From.Client),
        NamespaceName(From.NamespaceName),
        RankingName(From.RankingName),
        Season(From.Season),
        AccessToken(From.AccessToken),
        ParentKey(From.ParentKey)
    {

    }

    FGlobalRankingSeasonAccessTokenDomain::FPutGlobalRankingScoreTask::FPutGlobalRankingScoreTask(
        const TSharedPtr<FGlobalRankingSeasonAccessTokenDomain>& Self,
        const Request::FPutGlobalRankingScoreRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FGlobalRankingSeasonAccessTokenDomain::FPutGlobalRankingScoreTask::FPutGlobalRankingScoreTask(
        const FPutGlobalRankingScoreTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FGlobalRankingSeasonAccessTokenDomain::FPutGlobalRankingScoreTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Ranking2::Domain::Model::FGlobalRankingScoreAccessTokenDomain>> Result
    )
    {
        Request
            ->WithContextStack(Self->Gs2->DefaultContextStack)
            ->WithNamespaceName(Self->NamespaceName)
            ->WithRankingName(Self->RankingName)
            ->WithAccessToken(Self->AccessToken->GetToken());
        const auto Future = Self->Client->PutGlobalRankingScore(
            Request
        );
        Future->StartSynchronousTask();
        if (Future->GetTask().IsError())
        {
            return Future->GetTask().Error();
        }
        const auto ResultModel = Future->GetTask().Result();
        Future->EnsureCompletion();
        auto Domain = MakeShared<Gs2::Ranking2::Domain::Model::FGlobalRankingScoreAccessTokenDomain>(
            Self->Gs2,
            Self->Service,
            Request->GetNamespaceName(),
            ResultModel->GetItem()->GetRankingName(),
            ResultModel->GetItem()->GetSeason(),
            Self->AccessToken
        );

        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FGlobalRankingSeasonAccessTokenDomain::FPutGlobalRankingScoreTask>> FGlobalRankingSeasonAccessTokenDomain::PutGlobalRankingScore(
        Request::FPutGlobalRankingScoreRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FPutGlobalRankingScoreTask>>(this->AsShared(), Request);
    }

    FGlobalRankingSeasonAccessTokenDomain::FGetGlobalRankingTask::FGetGlobalRankingTask(
        const TSharedPtr<FGlobalRankingSeasonAccessTokenDomain>& Self,
        const Request::FGetGlobalRankingRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FGlobalRankingSeasonAccessTokenDomain::FGetGlobalRankingTask::FGetGlobalRankingTask(
        const FGetGlobalRankingTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FGlobalRankingSeasonAccessTokenDomain::FGetGlobalRankingTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Ranking2::Domain::Model::FGlobalRankingDataAccessTokenDomain>> Result
    )
    {
        Request
            ->WithContextStack(Self->Gs2->DefaultContextStack)
            ->WithNamespaceName(Self->NamespaceName)
            ->WithRankingName(Self->RankingName)
            ->WithAccessToken(Self->AccessToken->GetToken())
            ->WithSeason(Self->Season);
        const auto Future = Self->Client->GetGlobalRanking(
            Request
        );
        Future->StartSynchronousTask();
        if (Future->GetTask().IsError())
        {
            return Future->GetTask().Error();
        }
        const auto ResultModel = Future->GetTask().Result();
        Future->EnsureCompletion();
        auto Domain = MakeShared<Gs2::Ranking2::Domain::Model::FGlobalRankingDataAccessTokenDomain>(
            Self->Gs2,
            Self->Service,
            Request->GetNamespaceName(),
            ResultModel->GetItem()->GetRankingName(),
            ResultModel->GetItem()->GetSeason(),
            Self->AccessToken,
            ResultModel->GetItem()->GetUserId()
        );

        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FGlobalRankingSeasonAccessTokenDomain::FGetGlobalRankingTask>> FGlobalRankingSeasonAccessTokenDomain::GetGlobalRanking(
        Request::FGetGlobalRankingRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FGetGlobalRankingTask>>(this->AsShared(), Request);
    }

    Gs2::Ranking2::Domain::Iterator::FDescribeGlobalRankingScoresIteratorPtr FGlobalRankingSeasonAccessTokenDomain::GlobalRankingScores(
    ) const
    {
        return MakeShared<Gs2::Ranking2::Domain::Iterator::FDescribeGlobalRankingScoresIterator>(
            Gs2,
            Client,
            NamespaceName,
            AccessToken,
            RankingName
        );
    }

    Gs2::Core::Domain::CallbackID FGlobalRankingSeasonAccessTokenDomain::SubscribeGlobalRankingScores(
    TFunction<void()> Callback
    )
    {
        return Gs2->Cache->ListSubscribe(
            Gs2::Ranking2::Model::FGlobalRankingScore::TypeName,
            Gs2::Ranking2::Domain::Model::FGlobalRankingSeasonDomain::CreateCacheParentKey(
                NamespaceName,
                RankingName,
                Season,
                "GlobalRankingScore"
            ),
            Callback
        );
    }

    void FGlobalRankingSeasonAccessTokenDomain::UnsubscribeGlobalRankingScores(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        Gs2->Cache->ListUnsubscribe(
            Gs2::Ranking2::Model::FGlobalRankingScore::TypeName,
            Gs2::Ranking2::Domain::Model::FGlobalRankingSeasonDomain::CreateCacheParentKey(
                NamespaceName,
                RankingName,
                Season,
                "GlobalRankingScore"
            ),
            CallbackID
        );
    }

    TSharedPtr<Gs2::Ranking2::Domain::Model::FGlobalRankingScoreAccessTokenDomain> FGlobalRankingSeasonAccessTokenDomain::GlobalRankingScore(
    )
    {
        return MakeShared<Gs2::Ranking2::Domain::Model::FGlobalRankingScoreAccessTokenDomain>(
            Gs2,
            Service,
            NamespaceName,
            RankingName,
            Season,
            AccessToken
        );
    }

    Gs2::Ranking2::Domain::Iterator::FDescribeGlobalRankingsIteratorPtr FGlobalRankingSeasonAccessTokenDomain::GlobalRankings(
    ) const
    {
        return MakeShared<Gs2::Ranking2::Domain::Iterator::FDescribeGlobalRankingsIterator>(
            Gs2,
            Client,
            NamespaceName,
            AccessToken,
            RankingName,
            Season
        );
    }

    Gs2::Core::Domain::CallbackID FGlobalRankingSeasonAccessTokenDomain::SubscribeGlobalRankings(
    TFunction<void()> Callback
    )
    {
        return Gs2->Cache->ListSubscribe(
            Gs2::Ranking2::Model::FGlobalRankingData::TypeName,
            Gs2::Ranking2::Domain::Model::FGlobalRankingSeasonDomain::CreateCacheParentKey(
                NamespaceName,
                RankingName,
                Season,
                "GlobalRankingData"
            ),
            Callback
        );
    }

    void FGlobalRankingSeasonAccessTokenDomain::UnsubscribeGlobalRankings(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        Gs2->Cache->ListUnsubscribe(
            Gs2::Ranking2::Model::FGlobalRankingData::TypeName,
            Gs2::Ranking2::Domain::Model::FGlobalRankingSeasonDomain::CreateCacheParentKey(
                NamespaceName,
                RankingName,
                Season,
                "GlobalRankingData"
            ),
            CallbackID
        );
    }

    TSharedPtr<Gs2::Ranking2::Domain::Model::FGlobalRankingDataAccessTokenDomain> FGlobalRankingSeasonAccessTokenDomain::GlobalRankingData(
        const TOptional<FString> ScorerUserId
    )
    {
        return MakeShared<Gs2::Ranking2::Domain::Model::FGlobalRankingDataAccessTokenDomain>(
            Gs2,
            Service,
            NamespaceName,
            RankingName,
            Season,
            AccessToken,
            ScorerUserId
        );
    }

    Gs2::Ranking2::Domain::Iterator::FDescribeGlobalRankingReceivedRewardsIteratorPtr FGlobalRankingSeasonAccessTokenDomain::GlobalRankingReceivedRewards(
    ) const
    {
        return MakeShared<Gs2::Ranking2::Domain::Iterator::FDescribeGlobalRankingReceivedRewardsIterator>(
            Gs2,
            Client,
            NamespaceName,
            AccessToken,
            RankingName,
            Season
        );
    }

    Gs2::Core::Domain::CallbackID FGlobalRankingSeasonAccessTokenDomain::SubscribeGlobalRankingReceivedRewards(
    TFunction<void()> Callback
    )
    {
        return Gs2->Cache->ListSubscribe(
            Gs2::Ranking2::Model::FGlobalRankingReceivedReward::TypeName,
            Gs2::Ranking2::Domain::Model::FGlobalRankingSeasonDomain::CreateCacheParentKey(
                NamespaceName,
                RankingName,
                Season,
                "GlobalRankingReceivedReward"
            ),
            Callback
        );
    }

    void FGlobalRankingSeasonAccessTokenDomain::UnsubscribeGlobalRankingReceivedRewards(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        Gs2->Cache->ListUnsubscribe(
            Gs2::Ranking2::Model::FGlobalRankingReceivedReward::TypeName,
            Gs2::Ranking2::Domain::Model::FGlobalRankingSeasonDomain::CreateCacheParentKey(
                NamespaceName,
                RankingName,
                Season,
                "GlobalRankingReceivedReward"
            ),
            CallbackID
        );
    }

    TSharedPtr<Gs2::Ranking2::Domain::Model::FGlobalRankingReceivedRewardAccessTokenDomain> FGlobalRankingSeasonAccessTokenDomain::GlobalRankingReceivedReward(
    )
    {
        return MakeShared<Gs2::Ranking2::Domain::Model::FGlobalRankingReceivedRewardAccessTokenDomain>(
            Gs2,
            Service,
            NamespaceName,
            RankingName,
            Season,
            AccessToken
        );
    }

    FString FGlobalRankingSeasonAccessTokenDomain::CreateCacheParentKey(
        TOptional<FString> NamespaceName,
        TOptional<FString> RankingName,
        TOptional<int64> Season,
        FString ChildType
    )
    {
        return FString("") +
            (NamespaceName.IsSet() ? *NamespaceName : "null") + ":" +
            (RankingName.IsSet() ? *RankingName : "null") + ":" +
            (Season.IsSet() ? FString::FromInt(*Season) : "null") + ":" +
            ChildType;
    }

    FString FGlobalRankingSeasonAccessTokenDomain::CreateCacheKey(
        TOptional<int64> Season
    )
    {
        return FString("") +
            (Season.IsSet() ? FString::FromInt(*Season) : "null");
    }
}

#if defined(_MSC_VER)
#pragma warning (pop)
#elif defined(__clang__)
#pragma clang diagnostic pop
#endif

