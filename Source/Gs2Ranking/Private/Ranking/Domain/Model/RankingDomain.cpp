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

#include "Ranking/Domain/Model/Ranking.h"
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
#include "Core/Domain/Transaction/ManualTransactionDomain.h"

namespace Gs2::Ranking::Domain::Model
{

    FRankingDomain::FRankingDomain(
        const Core::Domain::FGs2Ptr& Gs2,
        const Ranking::Domain::FGs2RankingDomainPtr& Service,
        const TOptional<FString> NamespaceName,
        const TOptional<FString> UserId,
        const TOptional<FString> CategoryName,
        const TOptional<FString> AdditionalScopeName,
        const TOptional<FString> ScorerUserId,
        const TOptional<int64> Index
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Gs2(Gs2),
        Service(Service),
        Client(MakeShared<Gs2::Ranking::FGs2RankingRestClient>(Gs2->RestSession)),
        NamespaceName(NamespaceName),
        UserId(UserId),
        CategoryName(CategoryName),
        AdditionalScopeName(AdditionalScopeName),
        ScorerUserId(ScorerUserId),
        Index(Index),
        ParentKey(Gs2::Ranking::Domain::Model::FRankingCategoryDomain::CreateCacheParentKey(
            NamespaceName,
            UserId,
            CategoryName,
            AdditionalScopeName,
            "Ranking"
        ))
    {
    }

    FRankingDomain::FRankingDomain(
        const FRankingDomain& From
    ):
        Gs2(From.Gs2),
        Service(From.Service),
        Client(From.Client),
        NamespaceName(From.NamespaceName),
        UserId(From.UserId),
        CategoryName(From.CategoryName),
        AdditionalScopeName(From.AdditionalScopeName),
        ScorerUserId(From.ScorerUserId),
        Index(From.Index),
        ParentKey(From.ParentKey)
    {

    }

    FRankingDomain::FGetTask::FGetTask(
        const TSharedPtr<FRankingDomain>& Self,
        const Request::FGetRankingByUserIdRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FRankingDomain::FGetTask::FGetTask(
        const FGetTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FRankingDomain::FGetTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Ranking::Model::FRanking>> Result
    )
    {
        Request
            ->WithNamespaceName(Self->NamespaceName)
            ->WithUserId(Self->UserId)
            ->WithCategoryName(Self->CategoryName)
            ->WithAdditionalScopeName(Self->AdditionalScopeName)
            ->WithScorerUserId(Self->ScorerUserId);
        const auto Future = Self->Client->GetRankingByUserId(
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
                    "Ranking";
                const auto Key = Gs2::Ranking::Domain::Model::FRankingDomain::CreateCacheKey(
                    RequestModel->GetScorerUserId(),
                    ResultModel->GetItem()->GetIndex().IsSet() ? FString::FromInt(*ResultModel->GetItem()->GetIndex()) : TOptional<FString>()
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

    TSharedPtr<FAsyncTask<FRankingDomain::FGetTask>> FRankingDomain::Get(
        Request::FGetRankingByUserIdRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FGetTask>>(this->AsShared(), Request);
    }

    FString FRankingDomain::CreateCacheParentKey(
        TOptional<FString> NamespaceName,
        TOptional<FString> UserId,
        TOptional<FString> CategoryName,
        TOptional<FString> AdditionalScopeName,
        TOptional<FString> ScorerUserId,
        TOptional<FString> Index,
        FString ChildType
    )
    {
        return FString("") +
            (NamespaceName.IsSet() ? *NamespaceName : "null") + ":" +
            (UserId.IsSet() ? *UserId : "null") + ":" +
            (CategoryName.IsSet() ? *CategoryName : "null") + ":" +
            (AdditionalScopeName.IsSet() ? *AdditionalScopeName : "null") + ":" +
            (ScorerUserId.IsSet() ? *ScorerUserId : "null") + ":" +
            (Index.IsSet() ? *Index : "null") + ":" +
            ChildType;
    }

    FString FRankingDomain::CreateCacheKey(
        TOptional<FString> ScorerUserId,
        TOptional<FString> Index
    )
    {
        return FString("") +
            (ScorerUserId.IsSet() ? *ScorerUserId : "null") + ":" + 
            (Index.IsSet() ? *Index : "null");
    }

    FRankingDomain::FModelTask::FModelTask(
        const TSharedPtr<FRankingDomain> Self
    ): Self(Self)
    {

    }

    FRankingDomain::FModelTask::FModelTask(
        const FModelTask& From
    ): TGs2Future(From), Self(From.Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FRankingDomain::FModelTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Ranking::Model::FRanking>> Result
    )
    {
        const auto ParentKey = FString("") +
            (Self->NamespaceName.IsSet() ? *Self->NamespaceName : "null") + ":" +
            (Self->UserId.IsSet() ? *Self->UserId : "null") + ":" +
            (Self->CategoryName.IsSet() ? *Self->CategoryName : "null") + ":" +
            "Ranking";
        // ReSharper disable once CppLocalVariableMayBeConst
        TSharedPtr<Gs2::Ranking::Model::FRanking> Value;
        auto bCacheHit = Self->Gs2->Cache->TryGet<Gs2::Ranking::Model::FRanking>(
            ParentKey,
            Gs2::Ranking::Domain::Model::FRankingDomain::CreateCacheKey(
                Self->ScorerUserId,
                Self->Index.IsSet() ? FString::FromInt(*Self->Index) : TOptional<FString>()
            ),
            &Value
        );
        if (!bCacheHit) {
            const auto Future = Self->Get(
                MakeShared<Gs2::Ranking::Request::FGetRankingByUserIdRequest>()
            );
            Future->StartSynchronousTask();
            if (Future->GetTask().IsError())
            {
                if (Future->GetTask().Error()->Type() != Gs2::Core::Model::FNotFoundError::TypeString)
                {
                    return Future->GetTask().Error();
                }

                const auto Key = Gs2::Ranking::Domain::Model::FRankingDomain::CreateCacheKey(
                    Self->ScorerUserId,
                    Self->Index.IsSet() ? FString::FromInt(*Self->Index) : TOptional<FString>()
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
                    Self->ScorerUserId,
                    Self->Index.IsSet() ? FString::FromInt(*Self->Index) : TOptional<FString>()
                ),
                &Value
            );
            Future->EnsureCompletion();
        }
        *Result = Value;

        return nullptr;
    }

    TSharedPtr<FAsyncTask<FRankingDomain::FModelTask>> FRankingDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FRankingDomain::FModelTask>>(this->AsShared());
    }

    Gs2::Core::Domain::CallbackID FRankingDomain::Subscribe(
        TFunction<void(Gs2::Ranking::Model::FRankingPtr)> Callback
    )
    {
        return Gs2->Cache->Subscribe(
            Gs2::Ranking::Model::FRanking::TypeName,
            ParentKey,
            Gs2::Ranking::Domain::Model::FRankingDomain::CreateCacheKey(
                ScorerUserId,
                Index.IsSet() ? FString::FromInt(*Index) : TOptional<FString>()
            ),
            [Callback](TSharedPtr<Gs2Object> obj)
            {
                Callback(StaticCastSharedPtr<Gs2::Ranking::Model::FRanking>(obj));
            }
        );
    }

    void FRankingDomain::Unsubscribe(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        Gs2->Cache->Unsubscribe(
            Gs2::Ranking::Model::FRanking::TypeName,
            ParentKey,
            Gs2::Ranking::Domain::Model::FRankingDomain::CreateCacheKey(
                ScorerUserId,
                Index.IsSet() ? FString::FromInt(*Index) : TOptional<FString>()
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

