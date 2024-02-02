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

    TSharedPtr<Gs2::Ranking::Domain::Model::FRankingCategoryAccessTokenDomain> FUserAccessTokenDomain::RankingCategory(
        const FString CategoryName,
        const TOptional<FString> AdditionalScopeName
    )
    {
        return MakeShared<Gs2::Ranking::Domain::Model::FRankingCategoryAccessTokenDomain>(
            Gs2,
            Service,
            NamespaceName,
            AccessToken,
            CategoryName == TEXT("") ? TOptional<FString>() : TOptional<FString>(CategoryName),
            AdditionalScopeName
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

