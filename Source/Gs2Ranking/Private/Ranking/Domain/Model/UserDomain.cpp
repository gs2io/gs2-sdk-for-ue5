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

#include "Ranking/Domain/Model/User.h"
#include "Ranking/Domain/Model/Namespace.h"
#include "Ranking/Domain/Model/CategoryModel.h"
#include "Ranking/Domain/Model/CategoryModelMaster.h"
#include "Ranking/Domain/Model/Subscribe.h"
#include "Ranking/Domain/Model/SubscribeAccessToken.h"
#include "Ranking/Domain/Model/Score.h"
#include "Ranking/Domain/Model/ScoreAccessToken.h"
#include "Ranking/Domain/Model/Ranking.h"
#include "Ranking/Domain/Model/RankingAccessToken.h"
#include "Ranking/Domain/Model/CurrentRankingMaster.h"
#include "Ranking/Domain/Model/SubscribeUser.h"
#include "Ranking/Domain/Model/SubscribeUserAccessToken.h"
#include "Ranking/Domain/Model/User.h"
#include "Ranking/Domain/Model/UserAccessToken.h"

#include "Core/Domain/Model/AutoStampSheetDomain.h"
#include "Core/Domain/Model/StampSheetDomain.h"

namespace Gs2::Ranking::Domain::Model
{

    FUserDomain::FUserDomain(
        const Core::Domain::FCacheDatabasePtr Cache,
        const Gs2::Core::Domain::Model::FJobQueueDomainPtr JobQueueDomain,
        const Gs2::Core::Domain::Model::FStampSheetConfigurationPtr StampSheetConfiguration,
        const Gs2::Core::Net::Rest::FGs2RestSessionPtr Session,
        const TOptional<FString> NamespaceName,
        const TOptional<FString> UserId
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Cache(Cache),
        JobQueueDomain(JobQueueDomain),
        StampSheetConfiguration(StampSheetConfiguration),
        Session(Session),
        Client(MakeShared<Gs2::Ranking::FGs2RankingRestClient>(Session)),
        NamespaceName(NamespaceName),
        UserId(UserId),
        ParentKey(Gs2::Ranking::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
            NamespaceName,
            "User"
        ))
    {
    }

    FUserDomain::FUserDomain(
        const FUserDomain& From
    ):
        Cache(From.Cache),
        JobQueueDomain(From.JobQueueDomain),
        StampSheetConfiguration(From.StampSheetConfiguration),
        Session(From.Session),
        Client(From.Client)
    {

    }

    FUserDomain::FSubscribeTask::FSubscribeTask(
        const TSharedPtr<FUserDomain> Self,
        const Request::FSubscribeByUserIdRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FUserDomain::FSubscribeTask::FSubscribeTask(
        const FSubscribeTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FUserDomain::FSubscribeTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Ranking::Domain::Model::FSubscribeUserDomain>> Result
    )
    {
        Request
            ->WithNamespaceName(Self->NamespaceName)
            ->WithUserId(Self->UserId);
        const auto Future = Self->Client->SubscribeByUserId(
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
                const auto ParentKey = Gs2::Ranking::Domain::Model::FUserDomain::CreateCacheParentKey(
                    Self->NamespaceName,
                    Self->UserId,
                    "SubscribeUser"
                );
                const auto Key = Gs2::Ranking::Domain::Model::FSubscribeUserDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetCategoryName(),
                    ResultModel->GetItem()->GetTargetUserId()
                );
                Self->Cache->Put<Gs2::Ranking::Model::FSubscribeUser>(
                    ParentKey,
                    Key,
                    ResultModel->GetItem(),
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );
            }
        }
        auto Domain = MakeShared<Gs2::Ranking::Domain::Model::FSubscribeUserDomain>(
            Self->Cache,
            Self->JobQueueDomain,
            Self->StampSheetConfiguration,
            Self->Session,
            Request->GetNamespaceName(),
            ResultModel->GetItem()->GetUserId(),
            ResultModel->GetItem()->GetCategoryName(),
            ResultModel->GetItem()->GetTargetUserId()
        );

        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FUserDomain::FSubscribeTask>> FUserDomain::Subscribe(
        Request::FSubscribeByUserIdRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FSubscribeTask>>(this->AsShared(), Request);
    }

    Gs2::Ranking::Domain::Iterator::FDescribeSubscribesByCategoryNameAndUserIdIteratorPtr FUserDomain::SubscribesByCategoryName(
        const FString CategoryName
    ) const
    {
        return MakeShared<Gs2::Ranking::Domain::Iterator::FDescribeSubscribesByCategoryNameAndUserIdIterator>(
            Cache,
            Client,
            NamespaceName,
            CategoryName,
            UserId
        );
    }

    TSharedPtr<Gs2::Ranking::Domain::Model::FSubscribeUserDomain> FUserDomain::SubscribeUser(
        const FString CategoryName,
        const FString TargetUserId
    ) const
    {
        return MakeShared<Gs2::Ranking::Domain::Model::FSubscribeUserDomain>(
            Cache,
            JobQueueDomain,
            StampSheetConfiguration,
            Session,
            NamespaceName,
            UserId,
            CategoryName,
            TargetUserId
        );
    }

    Gs2::Ranking::Domain::Iterator::FDescribeRankingsByUserIdIteratorPtr FUserDomain::Rankings(
        const FString CategoryName
    ) const
    {
        return MakeShared<Gs2::Ranking::Domain::Iterator::FDescribeRankingsByUserIdIterator>(
            Cache,
            Client,
            NamespaceName,
            CategoryName,
            UserId
        );
    }

    Gs2::Ranking::Domain::Iterator::FDescribeNearRankingsIteratorPtr FUserDomain::NearRankings(
        const FString CategoryName,
        const int64 Score
    ) const
    {
        return MakeShared<Gs2::Ranking::Domain::Iterator::FDescribeNearRankingsIterator>(
            Cache,
            Client,
            NamespaceName,
            CategoryName,
            Score
        );
    }

    TSharedPtr<Gs2::Ranking::Domain::Model::FRankingDomain> FUserDomain::Ranking(
        const FString CategoryName
    ) const
    {
        return MakeShared<Gs2::Ranking::Domain::Model::FRankingDomain>(
            Cache,
            JobQueueDomain,
            StampSheetConfiguration,
            Session,
            NamespaceName,
            UserId,
            CategoryName
        );
    }

    Gs2::Ranking::Domain::Iterator::FDescribeScoresByUserIdIteratorPtr FUserDomain::Scores(
        const FString CategoryName,
        const FString ScorerUserId
    ) const
    {
        return MakeShared<Gs2::Ranking::Domain::Iterator::FDescribeScoresByUserIdIterator>(
            Cache,
            Client,
            NamespaceName,
            CategoryName,
            UserId,
            ScorerUserId
        );
    }

    TSharedPtr<Gs2::Ranking::Domain::Model::FScoreDomain> FUserDomain::Score(
        const FString CategoryName,
        const FString ScorerUserId,
        const FString UniqueId
    ) const
    {
        return MakeShared<Gs2::Ranking::Domain::Model::FScoreDomain>(
            Cache,
            JobQueueDomain,
            StampSheetConfiguration,
            Session,
            NamespaceName,
            UserId,
            CategoryName,
            ScorerUserId,
            UniqueId
        );
    }

    FString FUserDomain::CreateCacheParentKey(
        TOptional<FString> NamespaceName,
        TOptional<FString> UserId,
        FString ChildType
    )
    {
        return FString() +
            (NamespaceName.IsSet() ? *NamespaceName : "null") + ":" +
            (UserId.IsSet() ? *UserId : "null") + ":" +
            ChildType;
    }

    FString FUserDomain::CreateCacheKey(
        TOptional<FString> UserId
    )
    {
        return FString() +
            (UserId.IsSet() ? *UserId : "null");
    }
}

#if defined(_MSC_VER)
#pragma warning (pop)
#elif defined(__clang__)
#pragma clang diagnostic pop
#endif

