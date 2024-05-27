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

#include "Ranking/Domain/Model/Subscribe.h"
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

    FSubscribeDomain::FSubscribeDomain(
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
        ParentKey(Gs2::Ranking::Domain::Model::FRankingCategoryDomain::CreateCacheParentKey(
            NamespaceName,
            UserId,
            CategoryName,
            AdditionalScopeName,
            "Subscribe"
        ))
    {
    }

    FSubscribeDomain::FSubscribeDomain(
        const FSubscribeDomain& From
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

    FString FSubscribeDomain::CreateCacheParentKey(
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

    FString FSubscribeDomain::CreateCacheKey(
    )
    {
        return "Singleton";
    }

    FSubscribeDomain::FModelTask::FModelTask(
        const TSharedPtr<FSubscribeDomain> Self
    ): Self(Self)
    {

    }

    FSubscribeDomain::FModelTask::FModelTask(
        const FModelTask& From
    ): TGs2Future(From), Self(From.Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FSubscribeDomain::FModelTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Ranking::Model::FSubscribe>> Result
    )
    {
        // ReSharper disable once CppLocalVariableMayBeConst
        TSharedPtr<Gs2::Ranking::Model::FSubscribe> Value;
        auto bCacheHit = Self->Gs2->Cache->TryGet<Gs2::Ranking::Model::FSubscribe>(
            Self->ParentKey,
            Gs2::Ranking::Domain::Model::FSubscribeDomain::CreateCacheKey(
            ),
            &Value
        );
        *Result = Value;

        return nullptr;
    }

    TSharedPtr<FAsyncTask<FSubscribeDomain::FModelTask>> FSubscribeDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FSubscribeDomain::FModelTask>>(this->AsShared());
    }

    Gs2::Core::Domain::CallbackID FSubscribeDomain::Subscribe(
        TFunction<void(Gs2::Ranking::Model::FSubscribePtr)> Callback
    )
    {
        return Gs2->Cache->Subscribe(
            Gs2::Ranking::Model::FSubscribe::TypeName,
            ParentKey,
            Gs2::Ranking::Domain::Model::FSubscribeDomain::CreateCacheKey(
            ),
            [Callback](TSharedPtr<Gs2Object> obj)
            {
                Callback(StaticCastSharedPtr<Gs2::Ranking::Model::FSubscribe>(obj));
            }
        );
    }

    void FSubscribeDomain::Unsubscribe(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        Gs2->Cache->Unsubscribe(
            Gs2::Ranking::Model::FSubscribe::TypeName,
            ParentKey,
            Gs2::Ranking::Domain::Model::FSubscribeDomain::CreateCacheKey(
            ),
            CallbackID
        );
    }
}

#if defined(_MSC_VER)
#pragma warning (pop)
#elif defined(__clang__)
#pragma clang diagnostic pop
#endif

