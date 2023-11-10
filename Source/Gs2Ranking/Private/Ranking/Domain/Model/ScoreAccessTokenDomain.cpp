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

#include "Ranking/Domain/Model/ScoreAccessToken.h"
#include "Ranking/Domain/Model/Score.h"
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

    FScoreAccessTokenDomain::FScoreAccessTokenDomain(
        const Core::Domain::FGs2Ptr& Gs2,
        const Ranking::Domain::FGs2RankingDomainPtr& Service,
        const TOptional<FString> NamespaceName,
        const Gs2::Auth::Model::FAccessTokenPtr& AccessToken,
        const TOptional<FString> CategoryName,
        const TOptional<FString> ScorerUserId,
        const TOptional<FString> UniqueId
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Gs2(Gs2),
        Service(Service),
        Client(MakeShared<Gs2::Ranking::FGs2RankingRestClient>(Gs2->RestSession)),
        NamespaceName(NamespaceName),
        AccessToken(AccessToken),
        CategoryName(CategoryName),
        ScorerUserId(ScorerUserId),
        UniqueId(UniqueId),
        ParentKey(Gs2::Ranking::Domain::Model::FUserDomain::CreateCacheParentKey(
            NamespaceName,
            UserId(),
            "Score"
        ))
    {
    }

    FScoreAccessTokenDomain::FScoreAccessTokenDomain(
        const FScoreAccessTokenDomain& From
    ):
        Gs2(From.Gs2),
        Service(From.Service),
        Client(From.Client),
        NamespaceName(From.NamespaceName),
        AccessToken(From.AccessToken),
        CategoryName(From.CategoryName),
        ScorerUserId(From.ScorerUserId),
        UniqueId(From.UniqueId),
        ParentKey(From.ParentKey)
    {

    }

    FScoreAccessTokenDomain::FGetTask::FGetTask(
        const TSharedPtr<FScoreAccessTokenDomain>& Self,
        const Request::FGetScoreRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FScoreAccessTokenDomain::FGetTask::FGetTask(
        const FGetTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FScoreAccessTokenDomain::FGetTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Ranking::Model::FScore>> Result
    )
    {
        Request
            ->WithNamespaceName(Self->NamespaceName)
            ->WithAccessToken(Self->AccessToken->GetToken())
            ->WithCategoryName(Self->CategoryName)
            ->WithScorerUserId(Self->ScorerUserId)
            ->WithUniqueId(Self->UniqueId);
        const auto Future = Self->Client->GetScore(
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
        *Result = ResultModel->GetItem();
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FScoreAccessTokenDomain::FGetTask>> FScoreAccessTokenDomain::Get(
        Request::FGetScoreRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FGetTask>>(this->AsShared(), Request);
    }

    FString FScoreAccessTokenDomain::CreateCacheParentKey(
        TOptional<FString> NamespaceName,
        TOptional<FString> UserId,
        TOptional<FString> CategoryName,
        TOptional<FString> ScorerUserId,
        TOptional<FString> UniqueId,
        FString ChildType
    )
    {
        return FString("") +
            (NamespaceName.IsSet() ? *NamespaceName : "null") + ":" +
            (UserId.IsSet() ? *UserId : "null") + ":" +
            (CategoryName.IsSet() ? *CategoryName : "null") + ":" +
            (ScorerUserId.IsSet() ? *ScorerUserId : "null") + ":" +
            (UniqueId.IsSet() ? *UniqueId : "null") + ":" +
            ChildType;
    }

    FString FScoreAccessTokenDomain::CreateCacheKey(
        TOptional<FString> CategoryName,
        TOptional<FString> ScorerUserId,
        TOptional<FString> UniqueId
    )
    {
        return FString("") +
            (CategoryName.IsSet() ? *CategoryName : "null") + ":" + 
            (ScorerUserId.IsSet() ? *ScorerUserId : "null") + ":" + 
            (UniqueId.IsSet() ? *UniqueId : "null");
    }

    FScoreAccessTokenDomain::FModelTask::FModelTask(
        const TSharedPtr<FScoreAccessTokenDomain> Self
    ): Self(Self)
    {

    }

    FScoreAccessTokenDomain::FModelTask::FModelTask(
        const FModelTask& From
    ): TGs2Future(From), Self(From.Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FScoreAccessTokenDomain::FModelTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Ranking::Model::FScore>> Result
    )
    {
        const auto ParentKey = FString("") +
            (Self->NamespaceName.IsSet() ? *Self->NamespaceName : "null") + ":" +
            (Self->UserId().IsSet() ? *Self->UserId() : "null") + ":" +
            (Self->CategoryName.IsSet() ? *Self->CategoryName : "null") + ":" +
            "Score";
        // ReSharper disable once CppLocalVariableMayBeConst
        TSharedPtr<Gs2::Ranking::Model::FScore> Value;
        auto bCacheHit = Self->Gs2->Cache->TryGet<Gs2::Ranking::Model::FScore>(
            ParentKey,
            Gs2::Ranking::Domain::Model::FScoreDomain::CreateCacheKey(
                Self->CategoryName,
                Self->ScorerUserId,
                Self->UniqueId ? *Self->UniqueId : "0"
            ),
            &Value
        );
        if (!bCacheHit) {
            const auto Future = Self->Get(
                MakeShared<Gs2::Ranking::Request::FGetScoreRequest>()
            );
            Future->StartSynchronousTask();
            if (Future->GetTask().IsError())
            {
                if (Future->GetTask().Error()->Type() != Gs2::Core::Model::FNotFoundError::TypeString)
                {
                    return Future->GetTask().Error();
                }

                const auto Key = Gs2::Ranking::Domain::Model::FScoreDomain::CreateCacheKey(
                    Self->CategoryName,
                    Self->ScorerUserId,
                    Self->UniqueId ? *Self->UniqueId : "0"
                );
                Self->Gs2->Cache->Put(
                    Gs2::Ranking::Model::FScore::TypeName,
                    ParentKey,
                    Key,
                    nullptr,
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );

                if (Future->GetTask().Error()->Detail(0)->GetComponent() != "score")
                {
                    return Future->GetTask().Error();
                }
            }
            Self->Gs2->Cache->TryGet<Gs2::Ranking::Model::FScore>(
                ParentKey,
                Gs2::Ranking::Domain::Model::FScoreDomain::CreateCacheKey(
                    Self->CategoryName,
                    Self->ScorerUserId,
                    Self->UniqueId ? *Self->UniqueId : "0"
                ),
                &Value
            );
            Future->EnsureCompletion();
        }
        *Result = Value;

        return nullptr;
    }

    TSharedPtr<FAsyncTask<FScoreAccessTokenDomain::FModelTask>> FScoreAccessTokenDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FScoreAccessTokenDomain::FModelTask>>(this->AsShared());
    }

    Gs2::Core::Domain::CallbackID FScoreAccessTokenDomain::Subscribe(
        TFunction<void(Gs2::Ranking::Model::FScorePtr)> Callback
    )
    {
        return Gs2->Cache->Subscribe(
            Gs2::Ranking::Model::FScore::TypeName,
            ParentKey,
            Gs2::Ranking::Domain::Model::FScoreDomain::CreateCacheKey(
                ScorerUserId,
                ScorerUserId,
                UniqueId ? *UniqueId : "0"
            ),
            [Callback](TSharedPtr<Gs2Object> obj)
            {
                Callback(StaticCastSharedPtr<Gs2::Ranking::Model::FScore>(obj));
            }
        );
    }

    void FScoreAccessTokenDomain::Unsubscribe(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        Gs2->Cache->Unsubscribe(
            Gs2::Ranking::Model::FScore::TypeName,
            ParentKey,
            Gs2::Ranking::Domain::Model::FScoreDomain::CreateCacheKey(
                ScorerUserId,
                ScorerUserId,
                UniqueId ? *UniqueId : "0"
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

