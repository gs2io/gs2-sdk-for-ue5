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

#include "Core/Domain/Gs2.h"

namespace Gs2::Ranking::Domain::Model
{

    FUserDomain::FUserDomain(
        const Core::Domain::FGs2Ptr& Gs2,
        const Ranking::Domain::FGs2RankingDomainPtr& Service,
        const TOptional<FString> NamespaceName,
        const TOptional<FString> UserId
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Gs2(Gs2),
        Service(Service),
        Client(MakeShared<Gs2::Ranking::FGs2RankingRestClient>(Gs2->RestSession)),
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
        Gs2(From.Gs2),
        Service(From.Service),
        Client(From.Client),
        NamespaceName(From.NamespaceName),
        UserId(From.UserId),
        ParentKey(From.ParentKey)
    {

    }

    FUserDomain::FSubscribeTask::FSubscribeTask(
        const TSharedPtr<FUserDomain>& Self,
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
                Self->Gs2->Cache->Put(
                    Gs2::Ranking::Model::FSubscribeUser::TypeName,
                    ParentKey,
                    Key,
                    ResultModel->GetItem(),
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );
            }
        }
        auto Domain = MakeShared<Gs2::Ranking::Domain::Model::FSubscribeUserDomain>(
            Self->Gs2,
            Self->Service,
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
            Gs2->Cache,
            Client,
            NamespaceName,
            CategoryName,
            UserId
        );
    }

    TSharedPtr<Gs2::Ranking::Domain::Model::FSubscribeUserDomain> FUserDomain::SubscribeUser(
        const FString CategoryName,
        const FString TargetUserId
    )
    {
        return MakeShared<Gs2::Ranking::Domain::Model::FSubscribeUserDomain>(
            Gs2,
            Service,
            NamespaceName,
            UserId,
            CategoryName == TEXT("") ? TOptional<FString>() : TOptional<FString>(CategoryName),
            TargetUserId == TEXT("") ? TOptional<FString>() : TOptional<FString>(TargetUserId)
        );
    }

    Gs2::Ranking::Domain::Iterator::FDescribeRankingsByUserIdIteratorPtr FUserDomain::Rankings(
        const FString CategoryName,
        const TOptional<FString> AdditionalScopeName
    ) const
    {
        return MakeShared<Gs2::Ranking::Domain::Iterator::FDescribeRankingsByUserIdIterator>(
            Gs2->Cache,
            Client,
            NamespaceName,
            CategoryName,
            UserId,
            AdditionalScopeName
        );
    }

    Gs2::Core::Domain::CallbackID FUserDomain::SubscribeRankings(
    TFunction<void()> Callback
    )
    {
        return Gs2->Cache->ListSubscribe(
            Gs2::Ranking::Model::FRanking::TypeName,
            Gs2::Ranking::Domain::Model::FUserDomain::CreateCacheParentKey(
                NamespaceName,
                UserId,
                "Ranking"
            ),
            Callback
        );
    }

    void FUserDomain::UnsubscribeRankings(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        Gs2->Cache->ListUnsubscribe(
            Gs2::Ranking::Model::FRanking::TypeName,
            Gs2::Ranking::Domain::Model::FUserDomain::CreateCacheParentKey(
                NamespaceName,
                UserId,
                "Ranking"
            ),
            CallbackID
        );
    }

    Gs2::Ranking::Domain::Iterator::FDescribeNearRankingsIteratorPtr FUserDomain::NearRankings(
        const FString CategoryName,
        const int64 Score,
        const TOptional<FString> AdditionalScopeName
    ) const
    {
        return MakeShared<Gs2::Ranking::Domain::Iterator::FDescribeNearRankingsIterator>(
            Gs2->Cache,
            Client,
            NamespaceName,
            CategoryName,
            AdditionalScopeName,
            Score
        );
    }

    Gs2::Core::Domain::CallbackID FUserDomain::SubscribeNearRankings(
    TFunction<void()> Callback
    )
    {
        return Gs2->Cache->ListSubscribe(
            Gs2::Ranking::Model::FRanking::TypeName,
            Gs2::Ranking::Domain::Model::FUserDomain::CreateCacheParentKey(
                NamespaceName,
                TOptional<FString>("Singleton"),
                "NearRanking"
            ),
            Callback
        );
    }

    void FUserDomain::UnsubscribeNearRankings(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        Gs2->Cache->ListUnsubscribe(
            Gs2::Ranking::Model::FRanking::TypeName,
            Gs2::Ranking::Domain::Model::FUserDomain::CreateCacheParentKey(
                NamespaceName,
                TOptional<FString>("Singleton"),
                "NearRanking"
            ),
            CallbackID
        );
    }

    TSharedPtr<Gs2::Ranking::Domain::Model::FRankingDomain> FUserDomain::Ranking(
        const FString CategoryName
    )
    {
        return MakeShared<Gs2::Ranking::Domain::Model::FRankingDomain>(
            Gs2,
            Service,
            NamespaceName,
            UserId,
            CategoryName == TEXT("") ? TOptional<FString>() : TOptional<FString>(CategoryName)
        );
    }

    Gs2::Ranking::Domain::Iterator::FDescribeScoresByUserIdIteratorPtr FUserDomain::Scores(
        const FString CategoryName,
        const FString ScorerUserId
    ) const
    {
        return MakeShared<Gs2::Ranking::Domain::Iterator::FDescribeScoresByUserIdIterator>(
            Gs2->Cache,
            Client,
            NamespaceName,
            CategoryName,
            UserId,
            ScorerUserId
        );
    }

    Gs2::Core::Domain::CallbackID FUserDomain::SubscribeScores(
    TFunction<void()> Callback
    )
    {
        return Gs2->Cache->ListSubscribe(
            Gs2::Ranking::Model::FScore::TypeName,
            Gs2::Ranking::Domain::Model::FUserDomain::CreateCacheParentKey(
                NamespaceName,
                UserId,
                "Score"
            ),
            Callback
        );
    }

    void FUserDomain::UnsubscribeScores(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        Gs2->Cache->ListUnsubscribe(
            Gs2::Ranking::Model::FScore::TypeName,
            Gs2::Ranking::Domain::Model::FUserDomain::CreateCacheParentKey(
                NamespaceName,
                UserId,
                "Score"
            ),
            CallbackID
        );
    }

    TSharedPtr<Gs2::Ranking::Domain::Model::FScoreDomain> FUserDomain::Score(
        const FString CategoryName,
        const FString ScorerUserId,
        const FString UniqueId
    )
    {
        return MakeShared<Gs2::Ranking::Domain::Model::FScoreDomain>(
            Gs2,
            Service,
            NamespaceName,
            UserId,
            CategoryName == TEXT("") ? TOptional<FString>() : TOptional<FString>(CategoryName),
            ScorerUserId == TEXT("") ? TOptional<FString>() : TOptional<FString>(ScorerUserId),
            UniqueId == TEXT("") ? TOptional<FString>() : TOptional<FString>(UniqueId)
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

