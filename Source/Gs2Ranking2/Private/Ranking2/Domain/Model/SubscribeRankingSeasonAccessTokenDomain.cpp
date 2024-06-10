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

#include "Ranking2/Domain/Model/SubscribeRankingSeasonAccessToken.h"
#include "Ranking2/Domain/Model/SubscribeRankingSeason.h"
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

    FSubscribeRankingSeasonAccessTokenDomain::FSubscribeRankingSeasonAccessTokenDomain(
        const Core::Domain::FGs2Ptr& Gs2,
        const Ranking2::Domain::FGs2Ranking2DomainPtr& Service,
        const TOptional<FString> NamespaceName,
        const Gs2::Auth::Model::FAccessTokenPtr& AccessToken,
        const TOptional<FString> RankingName,
        const TOptional<int64> Season
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Gs2(Gs2),
        Service(Service),
        Client(MakeShared<Gs2::Ranking2::FGs2Ranking2RestClient>(Gs2->RestSession)),
        NamespaceName(NamespaceName),
        AccessToken(AccessToken),
        RankingName(RankingName),
        Season(Season),
        ParentKey(Gs2::Ranking2::Domain::Model::FUserDomain::CreateCacheParentKey(
            NamespaceName,
            UserId(),
            "SubscribeRankingSeason"
        ))
    {
    }

    FSubscribeRankingSeasonAccessTokenDomain::FSubscribeRankingSeasonAccessTokenDomain(
        const FSubscribeRankingSeasonAccessTokenDomain& From
    ):
        Gs2(From.Gs2),
        Service(From.Service),
        Client(From.Client),
        NamespaceName(From.NamespaceName),
        AccessToken(From.AccessToken),
        RankingName(From.RankingName),
        Season(From.Season),
        ParentKey(From.ParentKey)
    {

    }

    FSubscribeRankingSeasonAccessTokenDomain::FPutSubscribeRankingScoreTask::FPutSubscribeRankingScoreTask(
        const TSharedPtr<FSubscribeRankingSeasonAccessTokenDomain>& Self,
        const Request::FPutSubscribeRankingScoreRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FSubscribeRankingSeasonAccessTokenDomain::FPutSubscribeRankingScoreTask::FPutSubscribeRankingScoreTask(
        const FPutSubscribeRankingScoreTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FSubscribeRankingSeasonAccessTokenDomain::FPutSubscribeRankingScoreTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Ranking2::Domain::Model::FSubscribeRankingScoreAccessTokenDomain>> Result
    )
    {
        Request
            ->WithContextStack(Self->Gs2->DefaultContextStack)
            ->WithNamespaceName(Self->NamespaceName)
            ->WithAccessToken(Self->AccessToken->GetToken())
            ->WithRankingName(Self->RankingName);
        const auto Future = Self->Client->PutSubscribeRankingScore(
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
                const auto ParentKey = Gs2::Ranking2::Domain::Model::FSubscribeRankingSeasonDomain::CreateCacheParentKey(
                    Self->NamespaceName,
                    Self->UserId(),
                    Self->RankingName,
                    FString::FromInt(*Self->Season),
                    "SubscribeRankingScore"
                );
                const auto Key = Gs2::Ranking2::Domain::Model::FSubscribeRankingScoreDomain::CreateCacheKey(
                );
                Self->Gs2->Cache->Put(
                    Gs2::Ranking2::Model::FSubscribeRankingScore::TypeName,
                    ParentKey,
                    Key,
                    ResultModel->GetItem(),
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );
            }
        }
        auto Domain = MakeShared<Gs2::Ranking2::Domain::Model::FSubscribeRankingScoreAccessTokenDomain>(
            Self->Gs2,
            Self->Service,
            Request->GetNamespaceName(),
            Self->AccessToken,
            ResultModel->GetItem()->GetRankingName(),
            ResultModel->GetItem()->GetSeason()
        );

        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FSubscribeRankingSeasonAccessTokenDomain::FPutSubscribeRankingScoreTask>> FSubscribeRankingSeasonAccessTokenDomain::PutSubscribeRankingScore(
        Request::FPutSubscribeRankingScoreRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FPutSubscribeRankingScoreTask>>(this->AsShared(), Request);
    }

    Gs2::Ranking2::Domain::Iterator::FDescribeSubscribeRankingScoresIteratorPtr FSubscribeRankingSeasonAccessTokenDomain::SubscribeRankingScores(
    ) const
    {
        return MakeShared<Gs2::Ranking2::Domain::Iterator::FDescribeSubscribeRankingScoresIterator>(
            Gs2,
            Client,
            NamespaceName,
            AccessToken,
            RankingName
        );
    }

    Gs2::Core::Domain::CallbackID FSubscribeRankingSeasonAccessTokenDomain::SubscribeSubscribeRankingScores(
    TFunction<void()> Callback
    )
    {
        return Gs2->Cache->ListSubscribe(
            Gs2::Ranking2::Model::FSubscribeRankingScore::TypeName,
            Gs2::Ranking2::Domain::Model::FSubscribeRankingSeasonDomain::CreateCacheParentKey(
                NamespaceName,
                UserId(),
                RankingName,
                FString::FromInt(*Season),
                "SubscribeRankingScore"
            ),
            Callback
        );
    }

    void FSubscribeRankingSeasonAccessTokenDomain::UnsubscribeSubscribeRankingScores(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        Gs2->Cache->ListUnsubscribe(
            Gs2::Ranking2::Model::FSubscribeRankingScore::TypeName,
            Gs2::Ranking2::Domain::Model::FSubscribeRankingSeasonDomain::CreateCacheParentKey(
                NamespaceName,
                UserId(),
                RankingName,
                FString::FromInt(*Season),
                "SubscribeRankingScore"
            ),
            CallbackID
        );
    }

    TSharedPtr<Gs2::Ranking2::Domain::Model::FSubscribeRankingScoreAccessTokenDomain> FSubscribeRankingSeasonAccessTokenDomain::SubscribeRankingScore(
    )
    {
        return MakeShared<Gs2::Ranking2::Domain::Model::FSubscribeRankingScoreAccessTokenDomain>(
            Gs2,
            Service,
            NamespaceName,
            AccessToken,
            RankingName,
            Season
        );
    }

    Gs2::Ranking2::Domain::Iterator::FDescribeSubscribeRankingsIteratorPtr FSubscribeRankingSeasonAccessTokenDomain::SubscribeRankings(
    ) const
    {
        return MakeShared<Gs2::Ranking2::Domain::Iterator::FDescribeSubscribeRankingsIterator>(
            Gs2,
            Client,
            NamespaceName,
            AccessToken,
            RankingName,
            Season
        );
    }

    Gs2::Core::Domain::CallbackID FSubscribeRankingSeasonAccessTokenDomain::SubscribeSubscribeRankings(
    TFunction<void()> Callback
    )
    {
        return Gs2->Cache->ListSubscribe(
            Gs2::Ranking2::Model::FSubscribeRankingData::TypeName,
            Gs2::Ranking2::Domain::Model::FSubscribeRankingSeasonDomain::CreateCacheParentKey(
                NamespaceName,
                UserId(),
                RankingName,
                FString::FromInt(*Season),
                "SubscribeRankingData"
            ),
            Callback
        );
    }

    void FSubscribeRankingSeasonAccessTokenDomain::UnsubscribeSubscribeRankings(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        Gs2->Cache->ListUnsubscribe(
            Gs2::Ranking2::Model::FSubscribeRankingData::TypeName,
            Gs2::Ranking2::Domain::Model::FSubscribeRankingSeasonDomain::CreateCacheParentKey(
                NamespaceName,
                UserId(),
                RankingName,
                FString::FromInt(*Season),
                "SubscribeRankingData"
            ),
            CallbackID
        );
    }

    TSharedPtr<Gs2::Ranking2::Domain::Model::FSubscribeRankingDataAccessTokenDomain> FSubscribeRankingSeasonAccessTokenDomain::SubscribeRankingData(
        const FString ScorerUserId
    )
    {
        return MakeShared<Gs2::Ranking2::Domain::Model::FSubscribeRankingDataAccessTokenDomain>(
            Gs2,
            Service,
            NamespaceName,
            AccessToken,
            RankingName,
            Season,
            ScorerUserId == TEXT("") ? TOptional<FString>() : TOptional<FString>(ScorerUserId)
        );
    }

    FString FSubscribeRankingSeasonAccessTokenDomain::CreateCacheParentKey(
        TOptional<FString> NamespaceName,
        TOptional<FString> UserId,
        TOptional<FString> RankingName,
        TOptional<FString> Season,
        FString ChildType
    )
    {
        return FString("") +
            (NamespaceName.IsSet() ? *NamespaceName : "null") + ":" +
            (UserId.IsSet() ? *UserId : "null") + ":" +
            (RankingName.IsSet() ? *RankingName : "null") + ":" +
            (Season.IsSet() ? *Season : "null") + ":" +
            ChildType;
    }

    FString FSubscribeRankingSeasonAccessTokenDomain::CreateCacheKey(
        TOptional<FString> RankingName,
        TOptional<FString> Season
    )
    {
        return FString("") +
            (RankingName.IsSet() ? *RankingName : "null") + ":" + 
            (Season.IsSet() ? *Season : "null");
    }
}

#if defined(_MSC_VER)
#pragma warning (pop)
#elif defined(__clang__)
#pragma clang diagnostic pop
#endif

