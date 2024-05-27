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

#include "Ranking/Domain/Model/RankingCategory.h"
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
#include "Ranking/Domain/Model/RankingCategory.h"
#include "Ranking/Domain/Model/RankingCategoryAccessToken.h"
#include "Ranking/Domain/Model/SubscribeUser.h"
#include "Ranking/Domain/Model/SubscribeUserAccessToken.h"
#include "Ranking/Domain/Model/User.h"
#include "Ranking/Domain/Model/UserAccessToken.h"

#include "Core/Domain/Gs2.h"
#include "Core/Domain/Transaction/JobQueueJobDomainFactory.h"
#include "Core/Domain/Transaction/InternalTransactionDomainFactory.h"
#include "Core/Domain/Transaction/ManualTransactionDomain.h"

namespace Gs2::Ranking::Domain::Model
{

    FRankingCategoryDomain::FRankingCategoryDomain(
        const Core::Domain::FGs2Ptr& Gs2,
        const Ranking::Domain::FGs2RankingDomainPtr& Service,
        const TOptional<FString> NamespaceName,
        const TOptional<FString> UserId,
        const TOptional<FString> CategoryName,
        const TOptional<FString> AdditionalScopeName
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Gs2(Gs2),
        Service(Service),
        Client(MakeShared<Gs2::Ranking::FGs2RankingRestClient>(Gs2->RestSession)),
        NamespaceName(NamespaceName),
        UserId(UserId),
        CategoryName(CategoryName),
        AdditionalScopeName(AdditionalScopeName),
        ParentKey(Gs2::Ranking::Domain::Model::FUserDomain::CreateCacheParentKey(
            NamespaceName,
            UserId,
            "RankingCategory"
        ))
    {
    }

    FRankingCategoryDomain::FRankingCategoryDomain(
        const FRankingCategoryDomain& From
    ):
        Gs2(From.Gs2),
        Service(From.Service),
        Client(From.Client),
        NamespaceName(From.NamespaceName),
        UserId(From.UserId),
        CategoryName(From.CategoryName),
        AdditionalScopeName(From.AdditionalScopeName),
        ParentKey(From.ParentKey)
    {

    }

    FRankingCategoryDomain::FSubscribeTask::FSubscribeTask(
        const TSharedPtr<FRankingCategoryDomain>& Self,
        const Request::FSubscribeByUserIdRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FRankingCategoryDomain::FSubscribeTask::FSubscribeTask(
        const FSubscribeTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FRankingCategoryDomain::FSubscribeTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Ranking::Domain::Model::FSubscribeUserDomain>> Result
    )
    {
        Request
            ->WithContextStack(Self->Gs2->DefaultContextStack)
            ->WithNamespaceName(Self->NamespaceName)
            ->WithUserId(Self->UserId)
            ->WithCategoryName(Self->CategoryName);
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
                const auto ParentKey = Gs2::Ranking::Domain::Model::FRankingCategoryDomain::CreateCacheParentKey(
                    Self->NamespaceName,
                    Self->UserId,
                    Self->CategoryName,
                    Self->AdditionalScopeName,
                    "SubscribeUser"
                );
                const auto Key = Gs2::Ranking::Domain::Model::FSubscribeUserDomain::CreateCacheKey(
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
            Self->AdditionalScopeName,
            ResultModel->GetItem()->GetTargetUserId()
        );

        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FRankingCategoryDomain::FSubscribeTask>> FRankingCategoryDomain::Subscribe(
        Request::FSubscribeByUserIdRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FSubscribeTask>>(this->AsShared(), Request);
    }

    FRankingCategoryDomain::FPutScoreTask::FPutScoreTask(
        const TSharedPtr<FRankingCategoryDomain>& Self,
        const Request::FPutScoreByUserIdRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FRankingCategoryDomain::FPutScoreTask::FPutScoreTask(
        const FPutScoreTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FRankingCategoryDomain::FPutScoreTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Ranking::Domain::Model::FScoreDomain>> Result
    )
    {
        Request
            ->WithContextStack(Self->Gs2->DefaultContextStack)
            ->WithNamespaceName(Self->NamespaceName)
            ->WithUserId(Self->UserId)
            ->WithCategoryName(Self->CategoryName);
        const auto Future = Self->Client->PutScoreByUserId(
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
                const auto ParentKey = FString("") +
                    (Self->NamespaceName.IsSet() ? *Self->NamespaceName : "null") + ":" +
                    (Self->UserId.IsSet() ? *Self->UserId : "null") + ":" +
                    (Self->CategoryName.IsSet() ? *Self->CategoryName : "null") + ":" +
                    "Score";
                const auto Key = Gs2::Ranking::Domain::Model::FScoreDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetCategoryName(),
                    ResultModel->GetItem()->GetScorerUserId(),
                    ResultModel->GetItem()->GetUniqueId()
                );
                Self->Gs2->Cache->Put(
                    Gs2::Ranking::Model::FScore::TypeName,
                    ParentKey,
                    Key,
                    ResultModel->GetItem(),
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );
            }
        }
        auto Domain = MakeShared<Gs2::Ranking::Domain::Model::FScoreDomain>(
            Self->Gs2,
            Self->Service,
            Request->GetNamespaceName(),
            ResultModel->GetItem()->GetUserId(),
            ResultModel->GetItem()->GetCategoryName(),
            ResultModel->GetItem()->GetScorerUserId(),
            ResultModel->GetItem()->GetUniqueId()
        );

        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FRankingCategoryDomain::FPutScoreTask>> FRankingCategoryDomain::PutScore(
        Request::FPutScoreByUserIdRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FPutScoreTask>>(this->AsShared(), Request);
    }

    Gs2::Ranking::Domain::Iterator::FDescribeSubscribesByCategoryNameAndUserIdIteratorPtr FRankingCategoryDomain::SubscribesByCategoryName(
        const TOptional<FString> TimeOffsetToken
    ) const
    {
        return MakeShared<Gs2::Ranking::Domain::Iterator::FDescribeSubscribesByCategoryNameAndUserIdIterator>(
            Gs2,
            Client,
            NamespaceName,
            CategoryName,
            UserId,
            TimeOffsetToken
        );
    }

    Gs2::Core::Domain::CallbackID FRankingCategoryDomain::SubscribeSubscribesByCategoryName(
    TFunction<void()> Callback
    )
    {
        return Gs2->Cache->ListSubscribe(
            Gs2::Ranking::Model::FSubscribeUser::TypeName,
            Gs2::Ranking::Domain::Model::FRankingCategoryDomain::CreateCacheParentKey(
                NamespaceName,
                UserId,
                CategoryName,
                AdditionalScopeName,
                "SubscribeUser"
            ),
            Callback
        );
    }

    void FRankingCategoryDomain::UnsubscribeSubscribesByCategoryName(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        Gs2->Cache->ListUnsubscribe(
            Gs2::Ranking::Model::FSubscribeUser::TypeName,
            Gs2::Ranking::Domain::Model::FRankingCategoryDomain::CreateCacheParentKey(
                NamespaceName,
                UserId,
                CategoryName,
                AdditionalScopeName,
                "SubscribeUser"
            ),
            CallbackID
        );
    }

    TSharedPtr<Gs2::Ranking::Domain::Model::FSubscribeUserDomain> FRankingCategoryDomain::SubscribeUser(
        const FString TargetUserId
    )
    {
        return MakeShared<Gs2::Ranking::Domain::Model::FSubscribeUserDomain>(
            Gs2,
            Service,
            NamespaceName,
            UserId,
            CategoryName,
            AdditionalScopeName,
            TargetUserId == TEXT("") ? TOptional<FString>() : TOptional<FString>(TargetUserId)
        );
    }

    Gs2::Ranking::Domain::Iterator::FDescribeRankingsByUserIdIteratorPtr FRankingCategoryDomain::Rankings(
        const TOptional<FString> TimeOffsetToken
    ) const
    {
        return MakeShared<Gs2::Ranking::Domain::Iterator::FDescribeRankingsByUserIdIterator>(
            Gs2,
            Client,
            NamespaceName,
            CategoryName,
            UserId,
            AdditionalScopeName,
            TimeOffsetToken
        );
    }

    Gs2::Core::Domain::CallbackID FRankingCategoryDomain::SubscribeRankings(
    TFunction<void()> Callback
    )
    {
        return Gs2->Cache->ListSubscribe(
            Gs2::Ranking::Model::FRanking::TypeName,
            Gs2::Ranking::Domain::Model::FRankingCategoryDomain::CreateCacheParentKey(
                NamespaceName,
                UserId,
                CategoryName,
                AdditionalScopeName,
                "Ranking"
            ),
            Callback
        );
    }

    void FRankingCategoryDomain::UnsubscribeRankings(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        Gs2->Cache->ListUnsubscribe(
            Gs2::Ranking::Model::FRanking::TypeName,
            Gs2::Ranking::Domain::Model::FRankingCategoryDomain::CreateCacheParentKey(
                NamespaceName,
                UserId,
                CategoryName,
                AdditionalScopeName,
                "Ranking"
            ),
            CallbackID
        );
    }

    Gs2::Ranking::Domain::Iterator::FDescribeNearRankingsIteratorPtr FRankingCategoryDomain::NearRankings(
        const int64 Score
    ) const
    {
        return MakeShared<Gs2::Ranking::Domain::Iterator::FDescribeNearRankingsIterator>(
            Gs2,
            Client,
            NamespaceName,
            CategoryName,
            Score,
            AdditionalScopeName
        );
    }

    Gs2::Core::Domain::CallbackID FRankingCategoryDomain::SubscribeNearRankings(
    TFunction<void()> Callback
    )
    {
        return Gs2->Cache->ListSubscribe(
            Gs2::Ranking::Model::FRanking::TypeName,
            Gs2::Ranking::Domain::Model::FRankingCategoryDomain::CreateCacheParentKey(
                NamespaceName,
                TOptional<FString>("Singleton"),
                CategoryName,
                AdditionalScopeName,
                "NearRanking"
            ),
            Callback
        );
    }

    void FRankingCategoryDomain::UnsubscribeNearRankings(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        Gs2->Cache->ListUnsubscribe(
            Gs2::Ranking::Model::FRanking::TypeName,
            Gs2::Ranking::Domain::Model::FRankingCategoryDomain::CreateCacheParentKey(
                NamespaceName,
                TOptional<FString>("Singleton"),
                CategoryName,
                AdditionalScopeName,
                "NearRanking"
            ),
            CallbackID
        );
    }

    TSharedPtr<Gs2::Ranking::Domain::Model::FRankingDomain> FRankingCategoryDomain::Ranking(
        const TOptional<FString> ScorerUserId,
        const TOptional<int64> Index
    )
    {
        return MakeShared<Gs2::Ranking::Domain::Model::FRankingDomain>(
            Gs2,
            Service,
            NamespaceName,
            UserId,
            CategoryName,
            AdditionalScopeName,
            ScorerUserId,
            Index
        );
    }

    FString FRankingCategoryDomain::CreateCacheParentKey(
        TOptional<FString> NamespaceName,
        TOptional<FString> UserId,
        TOptional<FString> CategoryName,
        TOptional<FString> AdditionalScopeName,
        FString ChildType
    )
    {
        return FString("") +
            (NamespaceName.IsSet() ? *NamespaceName : "null") + ":" +
            (UserId.IsSet() ? *UserId : "null") + ":" +
            (CategoryName.IsSet() ? *CategoryName : "null") + ":" +
            (AdditionalScopeName.IsSet() ? *AdditionalScopeName : "null") + ":" +
            ChildType;
    }

    FString FRankingCategoryDomain::CreateCacheKey(
        TOptional<FString> CategoryName,
        TOptional<FString> AdditionalScopeName
    )
    {
        return FString("") +
            (CategoryName.IsSet() ? *CategoryName : "null") + ":" + 
            (AdditionalScopeName.IsSet() ? *AdditionalScopeName : "null");
    }
}

#if defined(_MSC_VER)
#pragma warning (pop)
#elif defined(__clang__)
#pragma clang diagnostic pop
#endif

