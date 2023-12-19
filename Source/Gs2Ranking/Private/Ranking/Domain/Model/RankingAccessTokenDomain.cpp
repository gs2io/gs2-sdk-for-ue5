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

#include "Ranking/Domain/Model/RankingAccessToken.h"
#include "Ranking/Domain/Model/Ranking.h"
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

    FRankingAccessTokenDomain::FRankingAccessTokenDomain(
        const Core::Domain::FGs2Ptr& Gs2,
        const Ranking::Domain::FGs2RankingDomainPtr& Service,
        const TOptional<FString> NamespaceName,
        const Gs2::Auth::Model::FAccessTokenPtr& AccessToken,
        const TOptional<FString> CategoryName
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Gs2(Gs2),
        Service(Service),
        Client(MakeShared<Gs2::Ranking::FGs2RankingRestClient>(Gs2->RestSession)),
        NamespaceName(NamespaceName),
        AccessToken(AccessToken),
        CategoryName(CategoryName),
        ParentKey(Gs2::Ranking::Domain::Model::FUserDomain::CreateCacheParentKey(
            NamespaceName,
            UserId(),
            "Ranking"
        ))
    {
    }

    FRankingAccessTokenDomain::FRankingAccessTokenDomain(
        const FRankingAccessTokenDomain& From
    ):
        Gs2(From.Gs2),
        Service(From.Service),
        Client(From.Client),
        NamespaceName(From.NamespaceName),
        AccessToken(From.AccessToken),
        CategoryName(From.CategoryName),
        ParentKey(From.ParentKey)
    {

    }

    FRankingAccessTokenDomain::FGetTask::FGetTask(
        const TSharedPtr<FRankingAccessTokenDomain>& Self,
        const Request::FGetRankingRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FRankingAccessTokenDomain::FGetTask::FGetTask(
        const FGetTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FRankingAccessTokenDomain::FGetTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Ranking::Model::FRanking>> Result
    )
    {
        Request
            ->WithNamespaceName(Self->NamespaceName)
            ->WithAccessToken(Self->AccessToken->GetToken())
            ->WithCategoryName(Self->CategoryName);
        const auto Future = Self->Client->GetRanking(
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
                    "Ranking";
                const auto Key = Gs2::Ranking::Domain::Model::FRankingDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetUserId()
                );
                Self->Gs2->Cache->Put(
                    Gs2::Ranking::Model::FRanking::TypeName,
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

    TSharedPtr<FAsyncTask<FRankingAccessTokenDomain::FGetTask>> FRankingAccessTokenDomain::Get(
        Request::FGetRankingRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FGetTask>>(this->AsShared(), Request);
    }

    FRankingAccessTokenDomain::FPutScoreTask::FPutScoreTask(
        const TSharedPtr<FRankingAccessTokenDomain>& Self,
        const Request::FPutScoreRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FRankingAccessTokenDomain::FPutScoreTask::FPutScoreTask(
        const FPutScoreTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FRankingAccessTokenDomain::FPutScoreTask::Action(
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

    TSharedPtr<FAsyncTask<FRankingAccessTokenDomain::FPutScoreTask>> FRankingAccessTokenDomain::PutScore(
        Request::FPutScoreRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FPutScoreTask>>(this->AsShared(), Request);
    }

    FString FRankingAccessTokenDomain::CreateCacheParentKey(
        TOptional<FString> NamespaceName,
        TOptional<FString> UserId,
        TOptional<FString> CategoryName,
        FString ChildType
    )
    {
        return FString("") +
            (NamespaceName.IsSet() ? *NamespaceName : "null") + ":" +
            (UserId.IsSet() ? *UserId : "null") + ":" +
            (CategoryName.IsSet() ? *CategoryName : "null") + ":" +
            ChildType;
    }

    FString FRankingAccessTokenDomain::CreateCacheKey(
        TOptional<FString> CategoryName
    )
    {
        return FString("") +
            (CategoryName.IsSet() ? *CategoryName : "null");
    }

    FRankingAccessTokenDomain::FModelTask::FModelTask(
        const TSharedPtr<FRankingAccessTokenDomain> Self,
        const TOptional<FString> ScorerUserId
    ): Self(Self), ScorerUserId(ScorerUserId)
    {

    }

    FRankingAccessTokenDomain::FModelTask::FModelTask(
        const FModelTask& From
    ): TGs2Future(From), Self(From.Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FRankingAccessTokenDomain::FModelTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Ranking::Model::FRanking>> Result
    )
    {
        const auto ParentKey = FString("") +
            (Self->NamespaceName.IsSet() ? *Self->NamespaceName : "null") + ":" +
            (Self->UserId().IsSet() ? *Self->UserId() : "null") + ":" +
            (Self->CategoryName.IsSet() ? *Self->CategoryName : "null") + ":" +
            "Ranking";
        // ReSharper disable once CppLocalVariableMayBeConst
        TSharedPtr<Gs2::Ranking::Model::FRanking> Value;
        auto bCacheHit = Self->Gs2->Cache->TryGet<Gs2::Ranking::Model::FRanking>(
            ParentKey,
            Gs2::Ranking::Domain::Model::FRankingDomain::CreateCacheKey(
                ScorerUserId
            ),
            &Value
        );
        if (!bCacheHit) {
            const auto Future = Self->Get(
                MakeShared<Gs2::Ranking::Request::FGetRankingRequest>()
                    ->WithScorerUserId(ScorerUserId)
            );
            Future->StartSynchronousTask();
            if (Future->GetTask().IsError())
            {
                if (Future->GetTask().Error()->Type() != Gs2::Core::Model::FNotFoundError::TypeString)
                {
                    return Future->GetTask().Error();
                }

                const auto Key = Gs2::Ranking::Domain::Model::FRankingDomain::CreateCacheKey(
                    ScorerUserId
                );
                Self->Gs2->Cache->Put(
                    Gs2::Ranking::Model::FRanking::TypeName,
                    ParentKey,
                    Key,
                    nullptr,
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );

                if (Future->GetTask().Error()->Detail(0)->GetComponent() != "ranking")
                {
                    return Future->GetTask().Error();
                }
            }
            Self->Gs2->Cache->TryGet<Gs2::Ranking::Model::FRanking>(
                ParentKey,
                Gs2::Ranking::Domain::Model::FRankingDomain::CreateCacheKey(
                    ScorerUserId
                ),
                &Value
            );
            Future->EnsureCompletion();
        }
        *Result = Value;

        return nullptr;
    }

    TSharedPtr<FAsyncTask<FRankingAccessTokenDomain::FModelTask>> FRankingAccessTokenDomain::Model(
        const TOptional<FString> ScorerUserId
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FRankingAccessTokenDomain::FModelTask>>(this->AsShared(), ScorerUserId);
    }

    Gs2::Core::Domain::CallbackID FRankingAccessTokenDomain::Subscribe(
        TFunction<void(Gs2::Ranking::Model::FRankingPtr)> Callback
    )
    {
        return Gs2->Cache->Subscribe(
            Gs2::Ranking::Model::FRanking::TypeName,
            ParentKey,
            Gs2::Ranking::Domain::Model::FRankingDomain::CreateCacheKey(
                CategoryName
            ),
            [Callback](TSharedPtr<Gs2Object> obj)
            {
                Callback(StaticCastSharedPtr<Gs2::Ranking::Model::FRanking>(obj));
            }
        );
    }

    void FRankingAccessTokenDomain::Unsubscribe(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        Gs2->Cache->Unsubscribe(
            Gs2::Ranking::Model::FRanking::TypeName,
            ParentKey,
            Gs2::Ranking::Domain::Model::FRankingDomain::CreateCacheKey(
                CategoryName
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

