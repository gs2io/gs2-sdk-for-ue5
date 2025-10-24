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

#include "Ranking2/Domain/Model/User.h"
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

    FUserDomain::FUserDomain(
        const Core::Domain::FGs2Ptr& Gs2,
        const Ranking2::Domain::FGs2Ranking2DomainPtr& Service,
        const TOptional<FString> NamespaceName,
        const TOptional<FString> UserId
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Gs2(Gs2),
        Service(Service),
        Client(MakeShared<Gs2::Ranking2::FGs2Ranking2RestClient>(Gs2->RestSession)),
        NamespaceName(NamespaceName),
        UserId(UserId),
        ParentKey(Gs2::Ranking2::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
            NamespaceName,
            "User"
        ))
    {
    }

    FUserDomain::FUserDomain(
        const FUserDomain& From
    ):
        Gs2(From.Gs2),
        Service(From.Service),
        Client(From.Client),
        NamespaceName(From.NamespaceName),
        UserId(From.UserId),
        ParentKey(From.ParentKey)
    {

    }

    FUserDomain::FPutGlobalRankingScoreTask::FPutGlobalRankingScoreTask(
        const TSharedPtr<FUserDomain>& Self,
        const Request::FPutGlobalRankingScoreByUserIdRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FUserDomain::FPutGlobalRankingScoreTask::FPutGlobalRankingScoreTask(
        const FPutGlobalRankingScoreTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FUserDomain::FPutGlobalRankingScoreTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Ranking2::Domain::Model::FGlobalRankingScoreDomain>> Result
    )
    {
        Request
            ->WithContextStack(Self->Gs2->DefaultContextStack)
            ->WithNamespaceName(Self->NamespaceName)
            ->WithUserId(Self->UserId);
        const auto Future = Self->Client->PutGlobalRankingScoreByUserId(
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
                    Self->UserId,
                    "GlobalRankingScore"
                );
                const auto Key = Gs2::Ranking2::Domain::Model::FGlobalRankingScoreDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetSeason(),
                    Self->UserId
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
        auto Domain = MakeShared<Gs2::Ranking2::Domain::Model::FGlobalRankingScoreDomain>(
            Self->Gs2,
            Self->Service,
            Request->GetNamespaceName(),
            ResultModel->GetItem()->GetRankingName(),
            ResultModel->GetItem()->GetSeason(),
            ResultModel->GetItem()->GetUserId()
        );

        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FUserDomain::FPutGlobalRankingScoreTask>> FUserDomain::PutGlobalRankingScore(
        Request::FPutGlobalRankingScoreByUserIdRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FPutGlobalRankingScoreTask>>(this->AsShared(), Request);
    }

    FUserDomain::FPutClusterRankingScoreTask::FPutClusterRankingScoreTask(
        const TSharedPtr<FUserDomain>& Self,
        const Request::FPutClusterRankingScoreByUserIdRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FUserDomain::FPutClusterRankingScoreTask::FPutClusterRankingScoreTask(
        const FPutClusterRankingScoreTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FUserDomain::FPutClusterRankingScoreTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Ranking2::Domain::Model::FClusterRankingScoreDomain>> Result
    )
    {
        Request
            ->WithContextStack(Self->Gs2->DefaultContextStack)
            ->WithNamespaceName(Self->NamespaceName)
            ->WithUserId(Self->UserId);
        const auto Future = Self->Client->PutClusterRankingScoreByUserId(
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
                    Self->UserId,
                    "ClusterRankingScore"
                );
                const auto Key = Gs2::Ranking2::Domain::Model::FClusterRankingScoreDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetRankingName(),
                    ResultModel->GetItem()->GetSeason(),
                    Self->UserId
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
        auto Domain = MakeShared<Gs2::Ranking2::Domain::Model::FClusterRankingScoreDomain>(
            Self->Gs2,
            Self->Service,
            Request->GetNamespaceName(),
            ResultModel->GetItem()->GetRankingName(),
            ResultModel->GetItem()->GetClusterName(),
            ResultModel->GetItem()->GetSeason(),
            ResultModel->GetItem()->GetUserId()
        );

        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FUserDomain::FPutClusterRankingScoreTask>> FUserDomain::PutClusterRankingScore(
        Request::FPutClusterRankingScoreByUserIdRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FPutClusterRankingScoreTask>>(this->AsShared(), Request);
    }

    Gs2::Ranking2::Domain::Iterator::FDescribeGlobalRankingScoresByUserIdIteratorPtr FUserDomain::GlobalRankingScores(
        const TOptional<FString> RankingName,
        const TOptional<FString> TimeOffsetToken
    ) const
    {
        return MakeShared<Gs2::Ranking2::Domain::Iterator::FDescribeGlobalRankingScoresByUserIdIterator>(
            Gs2,
            Client,
            NamespaceName,
            UserId,
            RankingName,
            TimeOffsetToken
        );
    }

    Gs2::Core::Domain::CallbackID FUserDomain::SubscribeGlobalRankingScores(
    TFunction<void()> Callback
    )
    {
        return Gs2->Cache->ListSubscribe(
            Gs2::Ranking2::Model::FGlobalRankingScore::TypeName,
            Gs2::Ranking2::Domain::Model::FUserDomain::CreateCacheParentKey(
                NamespaceName,
                UserId,
                "GlobalRankingScore"
            ),
            Callback
        );
    }

    void FUserDomain::UnsubscribeGlobalRankingScores(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        Gs2->Cache->ListUnsubscribe(
            Gs2::Ranking2::Model::FGlobalRankingScore::TypeName,
            Gs2::Ranking2::Domain::Model::FUserDomain::CreateCacheParentKey(
                NamespaceName,
                UserId,
                "GlobalRankingScore"
            ),
            CallbackID
        );
    }

    TSharedPtr<Gs2::Ranking2::Domain::Model::FGlobalRankingScoreDomain> FUserDomain::GlobalRankingScore(
        const FString RankingName,
        const TOptional<int64> Season
    )
    {
        return MakeShared<Gs2::Ranking2::Domain::Model::FGlobalRankingScoreDomain>(
            Gs2,
            Service,
            NamespaceName,
            RankingName == TEXT("") ? TOptional<FString>() : TOptional<FString>(RankingName),
            Season,
            UserId
        );
    }

    TSharedPtr<Gs2::Ranking2::Domain::Model::FSubscribeRankingSeasonDomain> FUserDomain::SubscribeRankingSeason(
        const FString RankingName,
        const TOptional<int64> Season
    )
    {
        return MakeShared<Gs2::Ranking2::Domain::Model::FSubscribeRankingSeasonDomain>(
            Gs2,
            Service,
            NamespaceName,
            RankingName == TEXT("") ? TOptional<FString>() : TOptional<FString>(RankingName),
            Season,
            UserId
        );
    }

    Gs2::Ranking2::Domain::Iterator::FDescribeSubscribesByUserIdIteratorPtr FUserDomain::Subscribes(
        const FString RankingName,
        const TOptional<FString> TimeOffsetToken
    ) const
    {
        return MakeShared<Gs2::Ranking2::Domain::Iterator::FDescribeSubscribesByUserIdIterator>(
            Gs2,
            Client,
            NamespaceName,
            UserId,
            RankingName,
            TimeOffsetToken
        );
    }

    Gs2::Core::Domain::CallbackID FUserDomain::SubscribeSubscribes(
        const FString RankingName,
        TFunction<void()> Callback
    )
    {
        return Gs2->Cache->ListSubscribe(
            Gs2::Ranking2::Model::FSubscribeUser::TypeName,
            Gs2::Ranking2::Domain::Model::FSubscribeDomain::CreateCacheParentKey(
                NamespaceName,
                UserId,
                RankingName,
                "SubscribeUser"
            ),
            Callback
        );
    }

    void FUserDomain::UnsubscribeSubscribes(
        const FString RankingName,
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        Gs2->Cache->ListUnsubscribe(
            Gs2::Ranking2::Model::FSubscribeUser::TypeName,
            Gs2::Ranking2::Domain::Model::FSubscribeDomain::CreateCacheParentKey(
                NamespaceName,
                UserId,
                RankingName,
                "SubscribeUser"
            ),
            CallbackID
        );
    }

    TSharedPtr<Gs2::Ranking2::Domain::Model::FSubscribeDomain> FUserDomain::Subscribe(
        const FString RankingName
    )
    {
        return MakeShared<Gs2::Ranking2::Domain::Model::FSubscribeDomain>(
            Gs2,
            Service,
            NamespaceName,
            UserId,
            RankingName == TEXT("") ? TOptional<FString>() : TOptional<FString>(RankingName)
        );
    }

    Gs2::Ranking2::Domain::Iterator::FDescribeGlobalRankingReceivedRewardsByUserIdIteratorPtr FUserDomain::GlobalRankingReceivedRewards(
        const TOptional<FString> RankingName,
        const TOptional<int64> Season,
        const TOptional<FString> TimeOffsetToken
    ) const
    {
        return MakeShared<Gs2::Ranking2::Domain::Iterator::FDescribeGlobalRankingReceivedRewardsByUserIdIterator>(
            Gs2,
            Client,
            NamespaceName,
            UserId,
            RankingName,
            Season,
            TimeOffsetToken
        );
    }

    Gs2::Core::Domain::CallbackID FUserDomain::SubscribeGlobalRankingReceivedRewards(
    TFunction<void()> Callback
    )
    {
        return Gs2->Cache->ListSubscribe(
            Gs2::Ranking2::Model::FGlobalRankingReceivedReward::TypeName,
            Gs2::Ranking2::Domain::Model::FUserDomain::CreateCacheParentKey(
                NamespaceName,
                UserId,
                "GlobalRankingReceivedReward"
            ),
            Callback
        );
    }

    void FUserDomain::UnsubscribeGlobalRankingReceivedRewards(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        Gs2->Cache->ListUnsubscribe(
            Gs2::Ranking2::Model::FGlobalRankingReceivedReward::TypeName,
            Gs2::Ranking2::Domain::Model::FUserDomain::CreateCacheParentKey(
                NamespaceName,
                UserId,
                "GlobalRankingReceivedReward"
            ),
            CallbackID
        );
    }

    TSharedPtr<Gs2::Ranking2::Domain::Model::FGlobalRankingReceivedRewardDomain> FUserDomain::GlobalRankingReceivedReward(
        const FString RankingName,
        const int64 Season
    )
    {
        return MakeShared<Gs2::Ranking2::Domain::Model::FGlobalRankingReceivedRewardDomain>(
            Gs2,
            Service,
            NamespaceName,
            RankingName == TEXT("") ? TOptional<FString>() : TOptional<FString>(RankingName),
            Season,
            UserId
        );
    }

    Gs2::Ranking2::Domain::Iterator::FDescribeClusterRankingReceivedRewardsByUserIdIteratorPtr FUserDomain::ClusterRankingReceivedRewards(
        const TOptional<FString> RankingName,
        const TOptional<FString> ClusterName,
        const TOptional<int64> Season,
        const TOptional<FString> TimeOffsetToken
    ) const
    {
        return MakeShared<Gs2::Ranking2::Domain::Iterator::FDescribeClusterRankingReceivedRewardsByUserIdIterator>(
            Gs2,
            Client,
            NamespaceName,
            UserId,
            RankingName,
            ClusterName,
            Season,
            TimeOffsetToken
        );
    }

    Gs2::Core::Domain::CallbackID FUserDomain::SubscribeClusterRankingReceivedRewards(
    TFunction<void()> Callback
    )
    {
        return Gs2->Cache->ListSubscribe(
            Gs2::Ranking2::Model::FClusterRankingReceivedReward::TypeName,
            Gs2::Ranking2::Domain::Model::FUserDomain::CreateCacheParentKey(
                NamespaceName,
                UserId,
                "ClusterRankingReceivedReward"
            ),
            Callback
        );
    }

    void FUserDomain::UnsubscribeClusterRankingReceivedRewards(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        Gs2->Cache->ListUnsubscribe(
            Gs2::Ranking2::Model::FClusterRankingReceivedReward::TypeName,
            Gs2::Ranking2::Domain::Model::FUserDomain::CreateCacheParentKey(
                NamespaceName,
                UserId,
                "ClusterRankingReceivedReward"
            ),
            CallbackID
        );
    }

    TSharedPtr<Gs2::Ranking2::Domain::Model::FClusterRankingReceivedRewardDomain> FUserDomain::ClusterRankingReceivedReward(
        const FString RankingName,
        const FString ClusterName,
        const int64 Season
    )
    {
        return MakeShared<Gs2::Ranking2::Domain::Model::FClusterRankingReceivedRewardDomain>(
            Gs2,
            Service,
            NamespaceName,
            RankingName == TEXT("") ? TOptional<FString>() : TOptional<FString>(RankingName),
            ClusterName == TEXT("") ? TOptional<FString>() : TOptional<FString>(ClusterName),
            Season,
            UserId
        );
    }

    Gs2::Ranking2::Domain::Iterator::FDescribeClusterRankingScoresByUserIdIteratorPtr FUserDomain::ClusterRankingScores(
        const TOptional<FString> RankingName,
        const TOptional<FString> ClusterName,
        const TOptional<int64> Season,
        const TOptional<FString> TimeOffsetToken
    ) const
    {
        return MakeShared<Gs2::Ranking2::Domain::Iterator::FDescribeClusterRankingScoresByUserIdIterator>(
            Gs2,
            Client,
            NamespaceName,
            UserId,
            RankingName,
            ClusterName,
            Season,
            TimeOffsetToken
        );
    }

    Gs2::Core::Domain::CallbackID FUserDomain::SubscribeClusterRankingScores(
    TFunction<void()> Callback
    )
    {
        return Gs2->Cache->ListSubscribe(
            Gs2::Ranking2::Model::FClusterRankingScore::TypeName,
            Gs2::Ranking2::Domain::Model::FUserDomain::CreateCacheParentKey(
                NamespaceName,
                UserId,
                "ClusterRankingScore"
            ),
            Callback
        );
    }

    void FUserDomain::UnsubscribeClusterRankingScores(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        Gs2->Cache->ListUnsubscribe(
            Gs2::Ranking2::Model::FClusterRankingScore::TypeName,
            Gs2::Ranking2::Domain::Model::FUserDomain::CreateCacheParentKey(
                NamespaceName,
                UserId,
                "ClusterRankingScore"
            ),
            CallbackID
        );
    }

    TSharedPtr<Gs2::Ranking2::Domain::Model::FClusterRankingScoreDomain> FUserDomain::ClusterRankingScore(
        const FString RankingName,
        const FString ClusterName,
        const int64 Season
    )
    {
        return MakeShared<Gs2::Ranking2::Domain::Model::FClusterRankingScoreDomain>(
            Gs2,
            Service,
            NamespaceName,
            RankingName == TEXT("") ? TOptional<FString>() : TOptional<FString>(RankingName),
            ClusterName == TEXT("") ? TOptional<FString>() : TOptional<FString>(ClusterName),
            Season,
            UserId
        );
    }

    FString FUserDomain::CreateCacheParentKey(
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

    FString FUserDomain::CreateCacheKey(
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

