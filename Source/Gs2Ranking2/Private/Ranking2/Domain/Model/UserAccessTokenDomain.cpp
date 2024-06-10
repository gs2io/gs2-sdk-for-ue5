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

#include "Ranking2/Domain/Model/UserAccessToken.h"
#include "Ranking2/Domain/Model/User.h"
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

    FUserAccessTokenDomain::FUserAccessTokenDomain(
        const Core::Domain::FGs2Ptr& Gs2,
        const Ranking2::Domain::FGs2Ranking2DomainPtr& Service,
        const TOptional<FString> NamespaceName,
        const Gs2::Auth::Model::FAccessTokenPtr& AccessToken
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Gs2(Gs2),
        Service(Service),
        Client(MakeShared<Gs2::Ranking2::FGs2Ranking2RestClient>(Gs2->RestSession)),
        NamespaceName(NamespaceName),
        AccessToken(AccessToken),
        ParentKey(Gs2::Ranking2::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
            NamespaceName,
            "User"
        ))
    {
    }

    FUserAccessTokenDomain::FUserAccessTokenDomain(
        const FUserAccessTokenDomain& From
    ):
        Gs2(From.Gs2),
        Service(From.Service),
        Client(From.Client),
        NamespaceName(From.NamespaceName),
        AccessToken(From.AccessToken),
        ParentKey(From.ParentKey)
    {

    }

    FUserAccessTokenDomain::FPutGlobalRankingScoreTask::FPutGlobalRankingScoreTask(
        const TSharedPtr<FUserAccessTokenDomain>& Self,
        const Request::FPutGlobalRankingScoreRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FUserAccessTokenDomain::FPutGlobalRankingScoreTask::FPutGlobalRankingScoreTask(
        const FPutGlobalRankingScoreTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FUserAccessTokenDomain::FPutGlobalRankingScoreTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Ranking2::Domain::Model::FGlobalRankingScoreAccessTokenDomain>> Result
    )
    {
        Request
            ->WithContextStack(Self->Gs2->DefaultContextStack)
            ->WithNamespaceName(Self->NamespaceName)
            ->WithAccessToken(Self->AccessToken->GetToken());
        const auto Future = Self->Client->PutGlobalRankingScore(
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
                const auto ParentKey = Gs2::Ranking2::Domain::Model::FUserDomain::CreateCacheParentKey(
                    Self->NamespaceName,
                    Self->UserId(),
                    "GlobalRankingScore"
                );
                const auto Key = Gs2::Ranking2::Domain::Model::FGlobalRankingScoreDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetRankingName(),
                    ResultModel->GetItem()->GetSeason().IsSet() ? FString::FromInt(*ResultModel->GetItem()->GetSeason()) : TOptional<FString>()
                );
                Self->Gs2->Cache->Put(
                    Gs2::Ranking2::Model::FGlobalRankingScore::TypeName,
                    ParentKey,
                    Key,
                    ResultModel->GetItem(),
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );
            }
        }
        auto Domain = MakeShared<Gs2::Ranking2::Domain::Model::FGlobalRankingScoreAccessTokenDomain>(
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

    TSharedPtr<FAsyncTask<FUserAccessTokenDomain::FPutGlobalRankingScoreTask>> FUserAccessTokenDomain::PutGlobalRankingScore(
        Request::FPutGlobalRankingScoreRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FPutGlobalRankingScoreTask>>(this->AsShared(), Request);
    }

    FUserAccessTokenDomain::FPutClusterRankingScoreTask::FPutClusterRankingScoreTask(
        const TSharedPtr<FUserAccessTokenDomain>& Self,
        const Request::FPutClusterRankingScoreRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FUserAccessTokenDomain::FPutClusterRankingScoreTask::FPutClusterRankingScoreTask(
        const FPutClusterRankingScoreTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FUserAccessTokenDomain::FPutClusterRankingScoreTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Ranking2::Domain::Model::FClusterRankingScoreAccessTokenDomain>> Result
    )
    {
        Request
            ->WithContextStack(Self->Gs2->DefaultContextStack)
            ->WithNamespaceName(Self->NamespaceName)
            ->WithAccessToken(Self->AccessToken->GetToken());
        const auto Future = Self->Client->PutClusterRankingScore(
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
                const auto ParentKey = Gs2::Ranking2::Domain::Model::FUserDomain::CreateCacheParentKey(
                    Self->NamespaceName,
                    Self->UserId(),
                    "ClusterRankingScore"
                );
                const auto Key = Gs2::Ranking2::Domain::Model::FClusterRankingScoreDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetRankingName(),
                    ResultModel->GetItem()->GetClusterName(),
                    ResultModel->GetItem()->GetSeason().IsSet() ? FString::FromInt(*ResultModel->GetItem()->GetSeason()) : TOptional<FString>()
                );
                Self->Gs2->Cache->Put(
                    Gs2::Ranking2::Model::FClusterRankingScore::TypeName,
                    ParentKey,
                    Key,
                    ResultModel->GetItem(),
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );
            }
        }
        auto Domain = MakeShared<Gs2::Ranking2::Domain::Model::FClusterRankingScoreAccessTokenDomain>(
            Self->Gs2,
            Self->Service,
            Request->GetNamespaceName(),
            Self->AccessToken,
            ResultModel->GetItem()->GetRankingName(),
            ResultModel->GetItem()->GetClusterName(),
            ResultModel->GetItem()->GetSeason()
        );

        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FUserAccessTokenDomain::FPutClusterRankingScoreTask>> FUserAccessTokenDomain::PutClusterRankingScore(
        Request::FPutClusterRankingScoreRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FPutClusterRankingScoreTask>>(this->AsShared(), Request);
    }

    Gs2::Ranking2::Domain::Iterator::FDescribeGlobalRankingScoresIteratorPtr FUserAccessTokenDomain::GlobalRankingScores(
        const TOptional<FString> RankingName
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

    Gs2::Core::Domain::CallbackID FUserAccessTokenDomain::SubscribeGlobalRankingScores(
    TFunction<void()> Callback
    )
    {
        return Gs2->Cache->ListSubscribe(
            Gs2::Ranking2::Model::FGlobalRankingScore::TypeName,
            Gs2::Ranking2::Domain::Model::FUserDomain::CreateCacheParentKey(
                NamespaceName,
                UserId(),
                "GlobalRankingScore"
            ),
            Callback
        );
    }

    void FUserAccessTokenDomain::UnsubscribeGlobalRankingScores(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        Gs2->Cache->ListUnsubscribe(
            Gs2::Ranking2::Model::FGlobalRankingScore::TypeName,
            Gs2::Ranking2::Domain::Model::FUserDomain::CreateCacheParentKey(
                NamespaceName,
                UserId(),
                "GlobalRankingScore"
            ),
            CallbackID
        );
    }

    TSharedPtr<Gs2::Ranking2::Domain::Model::FGlobalRankingScoreAccessTokenDomain> FUserAccessTokenDomain::GlobalRankingScore(
        const FString RankingName,
        const TOptional<int64> Season
    )
    {
        return MakeShared<Gs2::Ranking2::Domain::Model::FGlobalRankingScoreAccessTokenDomain>(
            Gs2,
            Service,
            NamespaceName,
            AccessToken,
            RankingName == TEXT("") ? TOptional<FString>() : TOptional<FString>(RankingName),
            Season
        );
    }

    TSharedPtr<Gs2::Ranking2::Domain::Model::FSubscribeRankingSeasonAccessTokenDomain> FUserAccessTokenDomain::SubscribeRankingSeason(
        const FString RankingName,
        const TOptional<int64> Season
    )
    {
        return MakeShared<Gs2::Ranking2::Domain::Model::FSubscribeRankingSeasonAccessTokenDomain>(
            Gs2,
            Service,
            NamespaceName,
            AccessToken,
            RankingName == TEXT("") ? TOptional<FString>() : TOptional<FString>(RankingName),
            Season
        );
    }

    Gs2::Ranking2::Domain::Iterator::FDescribeSubscribesIteratorPtr FUserAccessTokenDomain::Subscribes(
        const TOptional<FString> RankingName
    ) const
    {
        return MakeShared<Gs2::Ranking2::Domain::Iterator::FDescribeSubscribesIterator>(
            Gs2,
            Client,
            NamespaceName,
            AccessToken,
            RankingName
        );
    }

    Gs2::Core::Domain::CallbackID FUserAccessTokenDomain::SubscribeSubscribes(
        const TOptional<FString> RankingName,
        TFunction<void()> Callback
    )
    {
        return Gs2->Cache->ListSubscribe(
            Gs2::Ranking2::Model::FSubscribeUser::TypeName,
            Gs2::Ranking2::Domain::Model::FSubscribeDomain::CreateCacheParentKey(
                NamespaceName,
                UserId(),
                RankingName,
                "SubscribeUser"
            ),
            Callback
        );
    }

    void FUserAccessTokenDomain::UnsubscribeSubscribes(
        const TOptional<FString> RankingName,
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        Gs2->Cache->ListUnsubscribe(
            Gs2::Ranking2::Model::FSubscribeUser::TypeName,
            Gs2::Ranking2::Domain::Model::FSubscribeDomain::CreateCacheParentKey(
                NamespaceName,
                UserId(),
                RankingName,
                "SubscribeUser"
            ),
            CallbackID
        );
    }

    TSharedPtr<Gs2::Ranking2::Domain::Model::FSubscribeAccessTokenDomain> FUserAccessTokenDomain::Subscribe(
        const FString RankingName
    )
    {
        return MakeShared<Gs2::Ranking2::Domain::Model::FSubscribeAccessTokenDomain>(
            Gs2,
            Service,
            NamespaceName,
            AccessToken,
            RankingName == TEXT("") ? TOptional<FString>() : TOptional<FString>(RankingName)
        );
    }

    Gs2::Ranking2::Domain::Iterator::FDescribeGlobalRankingReceivedRewardsIteratorPtr FUserAccessTokenDomain::GlobalRankingReceivedRewards(
        const TOptional<FString> RankingName,
        const TOptional<int64> Season
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

    Gs2::Core::Domain::CallbackID FUserAccessTokenDomain::SubscribeGlobalRankingReceivedRewards(
    TFunction<void()> Callback
    )
    {
        return Gs2->Cache->ListSubscribe(
            Gs2::Ranking2::Model::FGlobalRankingReceivedReward::TypeName,
            Gs2::Ranking2::Domain::Model::FUserDomain::CreateCacheParentKey(
                NamespaceName,
                UserId(),
                "GlobalRankingReceivedReward"
            ),
            Callback
        );
    }

    void FUserAccessTokenDomain::UnsubscribeGlobalRankingReceivedRewards(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        Gs2->Cache->ListUnsubscribe(
            Gs2::Ranking2::Model::FGlobalRankingReceivedReward::TypeName,
            Gs2::Ranking2::Domain::Model::FUserDomain::CreateCacheParentKey(
                NamespaceName,
                UserId(),
                "GlobalRankingReceivedReward"
            ),
            CallbackID
        );
    }

    TSharedPtr<Gs2::Ranking2::Domain::Model::FGlobalRankingReceivedRewardAccessTokenDomain> FUserAccessTokenDomain::GlobalRankingReceivedReward(
        const FString RankingName,
        const TOptional<int64> Season
    )
    {
        return MakeShared<Gs2::Ranking2::Domain::Model::FGlobalRankingReceivedRewardAccessTokenDomain>(
            Gs2,
            Service,
            NamespaceName,
            AccessToken,
            RankingName == TEXT("") ? TOptional<FString>() : TOptional<FString>(RankingName),
            Season
        );
    }

    Gs2::Ranking2::Domain::Iterator::FDescribeClusterRankingReceivedRewardsIteratorPtr FUserAccessTokenDomain::ClusterRankingReceivedRewards(
        const TOptional<FString> RankingName,
        const TOptional<FString> ClusterName,
        const TOptional<int64> Season
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

    Gs2::Core::Domain::CallbackID FUserAccessTokenDomain::SubscribeClusterRankingReceivedRewards(
    TFunction<void()> Callback
    )
    {
        return Gs2->Cache->ListSubscribe(
            Gs2::Ranking2::Model::FClusterRankingReceivedReward::TypeName,
            Gs2::Ranking2::Domain::Model::FUserDomain::CreateCacheParentKey(
                NamespaceName,
                UserId(),
                "ClusterRankingReceivedReward"
            ),
            Callback
        );
    }

    void FUserAccessTokenDomain::UnsubscribeClusterRankingReceivedRewards(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        Gs2->Cache->ListUnsubscribe(
            Gs2::Ranking2::Model::FClusterRankingReceivedReward::TypeName,
            Gs2::Ranking2::Domain::Model::FUserDomain::CreateCacheParentKey(
                NamespaceName,
                UserId(),
                "ClusterRankingReceivedReward"
            ),
            CallbackID
        );
    }

    TSharedPtr<Gs2::Ranking2::Domain::Model::FClusterRankingReceivedRewardAccessTokenDomain> FUserAccessTokenDomain::ClusterRankingReceivedReward(
        const FString RankingName,
        const FString ClusterName,
        const TOptional<int64> Season
    )
    {
        return MakeShared<Gs2::Ranking2::Domain::Model::FClusterRankingReceivedRewardAccessTokenDomain>(
            Gs2,
            Service,
            NamespaceName,
            AccessToken,
            RankingName == TEXT("") ? TOptional<FString>() : TOptional<FString>(RankingName),
            ClusterName == TEXT("") ? TOptional<FString>() : TOptional<FString>(ClusterName),
            Season
        );
    }

    Gs2::Ranking2::Domain::Iterator::FDescribeClusterRankingScoresIteratorPtr FUserAccessTokenDomain::ClusterRankingScores(
        const TOptional<FString> RankingName,
        const TOptional<FString> ClusterName,
        const TOptional<int64> Season
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

    Gs2::Core::Domain::CallbackID FUserAccessTokenDomain::SubscribeClusterRankingScores(
    TFunction<void()> Callback
    )
    {
        return Gs2->Cache->ListSubscribe(
            Gs2::Ranking2::Model::FClusterRankingScore::TypeName,
            Gs2::Ranking2::Domain::Model::FUserDomain::CreateCacheParentKey(
                NamespaceName,
                UserId(),
                "ClusterRankingScore"
            ),
            Callback
        );
    }

    void FUserAccessTokenDomain::UnsubscribeClusterRankingScores(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        Gs2->Cache->ListUnsubscribe(
            Gs2::Ranking2::Model::FClusterRankingScore::TypeName,
            Gs2::Ranking2::Domain::Model::FUserDomain::CreateCacheParentKey(
                NamespaceName,
                UserId(),
                "ClusterRankingScore"
            ),
            CallbackID
        );
    }

    TSharedPtr<Gs2::Ranking2::Domain::Model::FClusterRankingScoreAccessTokenDomain> FUserAccessTokenDomain::ClusterRankingScore(
        const FString RankingName,
        const FString ClusterName,
        const TOptional<int64> Season
    )
    {
        return MakeShared<Gs2::Ranking2::Domain::Model::FClusterRankingScoreAccessTokenDomain>(
            Gs2,
            Service,
            NamespaceName,
            AccessToken,
            RankingName == TEXT("") ? TOptional<FString>() : TOptional<FString>(RankingName),
            ClusterName == TEXT("") ? TOptional<FString>() : TOptional<FString>(ClusterName),
            Season
        );
    }

    FString FUserAccessTokenDomain::CreateCacheParentKey(
        TOptional<FString> NamespaceName,
        TOptional<FString> UserId,
        FString ChildType
    )
    {
        return FString("") +
            (NamespaceName.IsSet() ? *NamespaceName : "null") + ":" +
            (UserId.IsSet() ? *UserId : "null") + ":" +
            ChildType;
    }

    FString FUserAccessTokenDomain::CreateCacheKey(
        TOptional<FString> UserId
    )
    {
        return FString("") +
            (UserId.IsSet() ? *UserId : "null");
    }
}

#if defined(_MSC_VER)
#pragma warning (pop)
#elif defined(__clang__)
#pragma clang diagnostic pop
#endif

