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

#include "Ranking/Domain/Model/UserAccessToken.h"
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
#include "Core/Domain/Model/AutoStampSheetDomain.h"
#include "Core/Domain/Model/StampSheetDomain.h"

namespace Gs2::Ranking::Domain::Model
{

    FUserAccessTokenDomain::FUserAccessTokenDomain(
        const Core::Domain::FGs2Ptr& Gs2,
        const Ranking::Domain::FGs2RankingDomainPtr& Service,
        const TOptional<FString> NamespaceName,
        const Gs2::Auth::Model::FAccessTokenPtr& AccessToken
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Gs2(Gs2),
        Service(Service),
        Client(MakeShared<Gs2::Ranking::FGs2RankingRestClient>(Gs2->RestSession)),
        NamespaceName(NamespaceName),
        AccessToken(AccessToken),
        ParentKey(Gs2::Ranking::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
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

    FUserAccessTokenDomain::FSubscribeTask::FSubscribeTask(
        const TSharedPtr<FUserAccessTokenDomain>& Self,
        const Request::FSubscribeRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FUserAccessTokenDomain::FSubscribeTask::FSubscribeTask(
        const FSubscribeTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FUserAccessTokenDomain::FSubscribeTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Ranking::Domain::Model::FSubscribeUserAccessTokenDomain>> Result
    )
    {
        Request
            ->WithNamespaceName(Self->NamespaceName)
            ->WithAccessToken(Self->AccessToken->GetToken());
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
                const auto ParentKey = Gs2::Ranking::Domain::Model::FUserDomain::CreateCacheParentKey(
                    Self->NamespaceName,
                    Self->UserId(),
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
        auto Domain = MakeShared<Gs2::Ranking::Domain::Model::FSubscribeUserAccessTokenDomain>(
            Self->Gs2,
            Self->Service,
            Request->GetNamespaceName(),
            Self->AccessToken,
            ResultModel->GetItem()->GetCategoryName(),
            ResultModel->GetItem()->GetTargetUserId()
        );

        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FUserAccessTokenDomain::FSubscribeTask>> FUserAccessTokenDomain::Subscribe(
        Request::FSubscribeRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FSubscribeTask>>(this->AsShared(), Request);
    }

    Gs2::Ranking::Domain::Iterator::FDescribeSubscribesByCategoryNameIteratorPtr FUserAccessTokenDomain::SubscribeUsers(
        const FString CategoryName
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

    Gs2::Core::Domain::CallbackID FUserAccessTokenDomain::SubscribeSubscribeUsers(
    TFunction<void()> Callback
    )
    {
        return Gs2->Cache->ListSubscribe(
            Gs2::Ranking::Model::FSubscribeUser::TypeName,
            Gs2::Ranking::Domain::Model::FUserDomain::CreateCacheParentKey(
                NamespaceName,
                UserId(),
                "SubscribeUser"
            ),
            Callback
        );
    }

    void FUserAccessTokenDomain::UnsubscribeSubscribeUsers(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        Gs2->Cache->ListUnsubscribe(
            Gs2::Ranking::Model::FSubscribeUser::TypeName,
            Gs2::Ranking::Domain::Model::FUserDomain::CreateCacheParentKey(
                NamespaceName,
                UserId(),
                "SubscribeUser"
            ),
            CallbackID
        );
    }

    TSharedPtr<Gs2::Ranking::Domain::Model::FSubscribeUserAccessTokenDomain> FUserAccessTokenDomain::SubscribeUser(
        const FString CategoryName,
        const FString TargetUserId
    )
    {
        return MakeShared<Gs2::Ranking::Domain::Model::FSubscribeUserAccessTokenDomain>(
            Gs2,
            Service,
            NamespaceName,
            AccessToken,
            CategoryName == TEXT("") ? TOptional<FString>() : TOptional<FString>(CategoryName),
            TargetUserId == TEXT("") ? TOptional<FString>() : TOptional<FString>(TargetUserId)
        );
    }

    Gs2::Ranking::Domain::Iterator::FDescribeRankingsIteratorPtr FUserAccessTokenDomain::Rankings(
        const FString CategoryName,
        const TOptional<FString> AdditionalScopeName
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

    Gs2::Core::Domain::CallbackID FUserAccessTokenDomain::SubscribeRankings(
    TFunction<void()> Callback
    )
    {
        return Gs2->Cache->ListSubscribe(
            Gs2::Ranking::Model::FRanking::TypeName,
            Gs2::Ranking::Domain::Model::FUserDomain::CreateCacheParentKey(
                NamespaceName,
                UserId(),
                "Ranking"
            ),
            Callback
        );
    }

    void FUserAccessTokenDomain::UnsubscribeRankings(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        Gs2->Cache->ListUnsubscribe(
            Gs2::Ranking::Model::FRanking::TypeName,
            Gs2::Ranking::Domain::Model::FUserDomain::CreateCacheParentKey(
                NamespaceName,
                UserId(),
                "Ranking"
            ),
            CallbackID
        );
    }

    TSharedPtr<Gs2::Ranking::Domain::Model::FRankingAccessTokenDomain> FUserAccessTokenDomain::Ranking(
        const FString CategoryName
    )
    {
        return MakeShared<Gs2::Ranking::Domain::Model::FRankingAccessTokenDomain>(
            Gs2,
            Service,
            NamespaceName,
            AccessToken,
            CategoryName == TEXT("") ? TOptional<FString>() : TOptional<FString>(CategoryName)
        );
    }

    Gs2::Ranking::Domain::Iterator::FDescribeScoresIteratorPtr FUserAccessTokenDomain::Scores(
        const FString CategoryName,
        const FString ScorerUserId
    ) const
    {
        return MakeShared<Gs2::Ranking::Domain::Iterator::FDescribeScoresIterator>(
            Gs2->Cache,
            Client,
            NamespaceName,
            CategoryName,
            AccessToken,
            ScorerUserId
        );
    }

    Gs2::Core::Domain::CallbackID FUserAccessTokenDomain::SubscribeScores(
    TFunction<void()> Callback
    )
    {
        return Gs2->Cache->ListSubscribe(
            Gs2::Ranking::Model::FScore::TypeName,
            Gs2::Ranking::Domain::Model::FUserDomain::CreateCacheParentKey(
                NamespaceName,
                UserId(),
                "Score"
            ),
            Callback
        );
    }

    void FUserAccessTokenDomain::UnsubscribeScores(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        Gs2->Cache->ListUnsubscribe(
            Gs2::Ranking::Model::FScore::TypeName,
            Gs2::Ranking::Domain::Model::FUserDomain::CreateCacheParentKey(
                NamespaceName,
                UserId(),
                "Score"
            ),
            CallbackID
        );
    }

    TSharedPtr<Gs2::Ranking::Domain::Model::FScoreAccessTokenDomain> FUserAccessTokenDomain::Score(
        const FString CategoryName,
        const FString ScorerUserId,
        const FString UniqueId
    )
    {
        return MakeShared<Gs2::Ranking::Domain::Model::FScoreAccessTokenDomain>(
            Gs2,
            Service,
            NamespaceName,
            AccessToken,
            CategoryName == TEXT("") ? TOptional<FString>() : TOptional<FString>(CategoryName),
            ScorerUserId == TEXT("") ? TOptional<FString>() : TOptional<FString>(ScorerUserId),
            UniqueId == TEXT("") ? TOptional<FString>() : TOptional<FString>(UniqueId)
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

