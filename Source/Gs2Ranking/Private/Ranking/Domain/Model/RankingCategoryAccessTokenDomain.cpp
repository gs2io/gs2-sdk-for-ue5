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

#include "Ranking/Domain/Model/RankingCategoryAccessToken.h"
#include "Ranking/Domain/Model/RankingCategory.h"
#include "Ranking/Domain/Model/Namespace.h"
#include "Ranking/Domain/Model/CategoryModel.h"
#include "Ranking/Domain/Model/CategoryModelMaster.h"
#include "Ranking/Domain/Model/Subscribe.h"
#include "Ranking/Domain/Model/SubscribeAccessToken.h"
#include "Ranking/Domain/Model/Score.h"
#include "Ranking/Domain/Model/ScoreAccessToken.h"
#include "Ranking/Domain/Model/RankingCategory.h"
#include "Ranking/Domain/Model/RankingCategoryAccessToken.h"
#include "Ranking/Domain/Model/Ranking.h"
#include "Ranking/Domain/Model/RankingAccessToken.h"
#include "Ranking/Domain/Model/CurrentRankingMaster.h"
#include "Ranking/Domain/Model/SubscribeUser.h"
#include "Ranking/Domain/Model/SubscribeUserAccessToken.h"
#include "Ranking/Domain/Model/User.h"
#include "Ranking/Domain/Model/UserAccessToken.h"

#include "Core/Domain/Gs2.h"
#include "Core/Domain/Transaction/JobQueueJobDomainFactory.h"
#include "Core/Domain/Transaction/InternalTransactionDomainFactory.h"
#include "Core/Domain/Transaction/ManualTransactionAccessTokenDomain.h"

namespace Gs2::Ranking::Domain::Model
{

    FRankingCategoryAccessTokenDomain::FRankingCategoryAccessTokenDomain(
        const Core::Domain::FGs2Ptr& Gs2,
        const Ranking::Domain::FGs2RankingDomainPtr& Service,
        const TOptional<FString> NamespaceName,
        const Gs2::Auth::Model::FAccessTokenPtr& AccessToken,
        const TOptional<FString> CategoryName,
        const TOptional<FString> AdditionalScopeName
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Gs2(Gs2),
        Service(Service),
        Client(MakeShared<Gs2::Ranking::FGs2RankingRestClient>(Gs2->RestSession)),
        NamespaceName(NamespaceName),
        AccessToken(AccessToken),
        CategoryName(CategoryName),
        AdditionalScopeName(AdditionalScopeName),
        ParentKey(Gs2::Ranking::Domain::Model::FUserDomain::CreateCacheParentKey(
            NamespaceName,
            UserId(),
            "RankingCategory"
        ))
    {
    }

    FRankingCategoryAccessTokenDomain::FRankingCategoryAccessTokenDomain(
        const FRankingCategoryAccessTokenDomain& From
    ):
        Gs2(From.Gs2),
        Service(From.Service),
        Client(From.Client),
        NamespaceName(From.NamespaceName),
        AccessToken(From.AccessToken),
        CategoryName(From.CategoryName),
        AdditionalScopeName(From.AdditionalScopeName),
        ParentKey(From.ParentKey)
    {

    }

    FRankingCategoryAccessTokenDomain::FSubscribeTask::FSubscribeTask(
        const TSharedPtr<FRankingCategoryAccessTokenDomain>& Self,
        const Request::FSubscribeRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FRankingCategoryAccessTokenDomain::FSubscribeTask::FSubscribeTask(
        const FSubscribeTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FRankingCategoryAccessTokenDomain::FSubscribeTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Ranking::Domain::Model::FSubscribeUserAccessTokenDomain>> Result
    )
    {
        Request
            ->WithNamespaceName(Self->NamespaceName)
            ->WithAccessToken(Self->AccessToken->GetToken())
            ->WithCategoryName(Self->CategoryName);
        const auto Future = Self->Client->Subscribe(
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
                    Self->UserId(),
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
        auto Domain = MakeShared<Gs2::Ranking::Domain::Model::FSubscribeUserAccessTokenDomain>(
            Self->Gs2,
            Self->Service,
            Request->GetNamespaceName(),
            Self->AccessToken,
            ResultModel->GetItem()->GetCategoryName(),
            Self->AdditionalScopeName,
            ResultModel->GetItem()->GetTargetUserId()
        );

        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FRankingCategoryAccessTokenDomain::FSubscribeTask>> FRankingCategoryAccessTokenDomain::Subscribe(
        Request::FSubscribeRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FSubscribeTask>>(this->AsShared(), Request);
    }

    FRankingCategoryAccessTokenDomain::FPutScoreTask::FPutScoreTask(
        const TSharedPtr<FRankingCategoryAccessTokenDomain>& Self,
        const Request::FPutScoreRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FRankingCategoryAccessTokenDomain::FPutScoreTask::FPutScoreTask(
        const FPutScoreTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FRankingCategoryAccessTokenDomain::FPutScoreTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Ranking::Domain::Model::FScoreAccessTokenDomain>> Result
    )
    {
        Request
            ->WithNamespaceName(Self->NamespaceName)
            ->WithAccessToken(Self->AccessToken->GetToken())
            ->WithCategoryName(Self->CategoryName);
        const auto Future = Self->Client->PutScore(
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
                    (Self->UserId().IsSet() ? *Self->UserId() : "null") + ":" +
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
        auto Domain = MakeShared<Gs2::Ranking::Domain::Model::FScoreAccessTokenDomain>(
            Self->Gs2,
            Self->Service,
            Request->GetNamespaceName(),
            Self->AccessToken,
            ResultModel->GetItem()->GetCategoryName(),
            ResultModel->GetItem()->GetScorerUserId(),
            ResultModel->GetItem()->GetUniqueId()
        );

        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FRankingCategoryAccessTokenDomain::FPutScoreTask>> FRankingCategoryAccessTokenDomain::PutScore(
        Request::FPutScoreRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FPutScoreTask>>(this->AsShared(), Request);
    }

    Gs2::Ranking::Domain::Iterator::FDescribeSubscribesByCategoryNameIteratorPtr FRankingCategoryAccessTokenDomain::SubscribeUsers(
    ) const
    {
        return MakeShared<Gs2::Ranking::Domain::Iterator::FDescribeSubscribesByCategoryNameIterator>(
            Gs2->Cache,
            Client,
            NamespaceName,
            CategoryName,
            AccessToken
        );
    }

    Gs2::Core::Domain::CallbackID FRankingCategoryAccessTokenDomain::SubscribeSubscribeUsers(
    TFunction<void()> Callback
    )
    {
        return Gs2->Cache->ListSubscribe(
            Gs2::Ranking::Model::FSubscribeUser::TypeName,
            Gs2::Ranking::Domain::Model::FRankingCategoryDomain::CreateCacheParentKey(
                NamespaceName,
                UserId(),
                CategoryName,
                AdditionalScopeName,
                "SubscribeUser"
            ),
            Callback
        );
    }

    void FRankingCategoryAccessTokenDomain::UnsubscribeSubscribeUsers(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        Gs2->Cache->ListUnsubscribe(
            Gs2::Ranking::Model::FSubscribeUser::TypeName,
            Gs2::Ranking::Domain::Model::FRankingCategoryDomain::CreateCacheParentKey(
                NamespaceName,
                UserId(),
                CategoryName,
                AdditionalScopeName,
                "SubscribeUser"
            ),
            CallbackID
        );
    }

    TSharedPtr<Gs2::Ranking::Domain::Model::FSubscribeUserAccessTokenDomain> FRankingCategoryAccessTokenDomain::SubscribeUser(
        const FString TargetUserId
    )
    {
        return MakeShared<Gs2::Ranking::Domain::Model::FSubscribeUserAccessTokenDomain>(
            Gs2,
            Service,
            NamespaceName,
            AccessToken,
            CategoryName,
            AdditionalScopeName,
            TargetUserId == TEXT("") ? TOptional<FString>() : TOptional<FString>(TargetUserId)
        );
    }

    Gs2::Ranking::Domain::Iterator::FDescribeRankingsIteratorPtr FRankingCategoryAccessTokenDomain::Rankings(
    ) const
    {
        return MakeShared<Gs2::Ranking::Domain::Iterator::FDescribeRankingsIterator>(
            Gs2->Cache,
            Client,
            NamespaceName,
            CategoryName,
            AccessToken,
            AdditionalScopeName
        );
    }

    Gs2::Core::Domain::CallbackID FRankingCategoryAccessTokenDomain::SubscribeRankings(
    TFunction<void()> Callback
    )
    {
        return Gs2->Cache->ListSubscribe(
            Gs2::Ranking::Model::FRanking::TypeName,
            Gs2::Ranking::Domain::Model::FRankingCategoryDomain::CreateCacheParentKey(
                NamespaceName,
                UserId(),
                CategoryName,
                AdditionalScopeName,
                "Ranking"
            ),
            Callback
        );
    }

    void FRankingCategoryAccessTokenDomain::UnsubscribeRankings(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        Gs2->Cache->ListUnsubscribe(
            Gs2::Ranking::Model::FRanking::TypeName,
            Gs2::Ranking::Domain::Model::FRankingCategoryDomain::CreateCacheParentKey(
                NamespaceName,
                UserId(),
                CategoryName,
                AdditionalScopeName,
                "Ranking"
            ),
            CallbackID
        );
    }

    TSharedPtr<Gs2::Ranking::Domain::Model::FRankingAccessTokenDomain> FRankingCategoryAccessTokenDomain::Ranking(
        const TOptional<FString> ScorerUserId,
        const TOptional<int64> Index
    )
    {
        return MakeShared<Gs2::Ranking::Domain::Model::FRankingAccessTokenDomain>(
            Gs2,
            Service,
            NamespaceName,
            AccessToken,
            CategoryName,
            AdditionalScopeName,
            ScorerUserId,
            Index
        );
    }

    FString FRankingCategoryAccessTokenDomain::CreateCacheParentKey(
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

    FString FRankingCategoryAccessTokenDomain::CreateCacheKey(
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

