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
#include "Ranking/Domain/Model/RankingCategory.h"
#include "Ranking/Domain/Model/RankingCategoryAccessToken.h"
#include "Ranking/Domain/Model/SubscribeUser.h"
#include "Ranking/Domain/Model/SubscribeUserAccessToken.h"
#include "Ranking/Domain/Model/User.h"
#include "Ranking/Domain/Model/UserAccessToken.h"
#include "Ranking/Model/Cache/Ranking.h"

#include "Core/Domain/Gs2.h"
#include "Core/Domain/Transaction/JobQueueJobDomainFactory.h"
#include "Core/Domain/Transaction/InternalTransactionDomainFactory.h"
#include "Core/Domain/Transaction/ManualTransactionAccessTokenDomain.h"

namespace Gs2::Ranking::Domain::Model
{

    FRankingAccessTokenDomain::FRankingAccessTokenDomain(
        const Core::Domain::FGs2Ptr& Gs2,
        const Ranking::Domain::FGs2RankingDomainPtr& Service,
        const TOptional<FString> NamespaceName,
        const Gs2::Auth::Model::FAccessTokenPtr& AccessToken,
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
        AccessToken(AccessToken),
        CategoryName(CategoryName),
        AdditionalScopeName(AdditionalScopeName),
        ScorerUserId(ScorerUserId),
        Index(Index),
        ParentKey(Gs2::Ranking::Model::Cache::FRankingCache::CreateCacheParentKey(
            NamespaceName,
            UserId(),
            CategoryName,
            AdditionalScopeName,
            AccessToken.IsValid() ? AccessToken->GetTimeOffset() : TOptional<int32>()
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
        AdditionalScopeName(From.AdditionalScopeName),
        ScorerUserId(From.ScorerUserId),
        Index(From.Index),
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
            ->WithContextStack((!Request->GetContextStack().IsSet() || Request->GetContextStack()->IsEmpty()) ? Self->Gs2->DefaultContextStack : Request->GetContextStack())
            ->WithNamespaceName(Self->NamespaceName)
            ->WithCategoryName(Self->CategoryName)
            ->WithAccessToken(Self->AccessToken->GetToken())
            ->WithScorerUserId(Self->ScorerUserId)
            ->WithAdditionalScopeName(Self->AdditionalScopeName);
        const auto Future = Self->Client->GetRanking(
            Request
        );
        Future->StartSynchronousTask();
        if (Future->GetTask().IsError())
        {
            return Future->GetTask().Error();
        }
        const auto ResultModel = Future->GetTask().Result();
        Future->EnsureCompletion();

        *Result = ResultModel->GetItem();
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FRankingAccessTokenDomain::FGetTask>> FRankingAccessTokenDomain::Get(
        Request::FGetRankingRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FGetTask>>(this->AsShared(), Request);
    }

    FString FRankingAccessTokenDomain::CreateCacheParentKey(
        TOptional<FString> NamespaceName,
        TOptional<FString> UserId,
        TOptional<FString> CategoryName,
        TOptional<FString> AdditionalScopeName,
        TOptional<FString> ScorerUserId,
        TOptional<int64> Index,
        FString ChildType
    )
    {
        return FString("") +
            (NamespaceName.IsSet() ? *NamespaceName : "null") + ":" +
            (UserId.IsSet() ? *UserId : "null") + ":" +
            (CategoryName.IsSet() ? *CategoryName : "null") + ":" +
            (AdditionalScopeName.IsSet() ? *AdditionalScopeName : "null") + ":" +
            (ScorerUserId.IsSet() ? *ScorerUserId : "null") + ":" +
            (Index.IsSet() ? FString::FromInt(*Index) : "null") + ":" +
            ChildType;
    }

    FString FRankingAccessTokenDomain::CreateCacheKey(
        TOptional<FString> ScorerUserId,
        TOptional<int64> Index
    )
    {
        return FString("") +
            (ScorerUserId.IsSet() ? *ScorerUserId : "null") + ":" +
            (Index.IsSet() ? FString::FromInt(*Index) : "null");
    }

    FRankingAccessTokenDomain::FModelTask::FModelTask(
        const TSharedPtr<FRankingAccessTokenDomain> Self
    ): Self(Self)
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
        const FString CacheKey = Gs2::Ranking::Model::Cache::FRankingCache::CreateCacheKey(
            Self->ScorerUserId,
            Self->Index
        );
        return Self->Gs2->Cache->ExecuteWithKeyLock(
            Gs2::Ranking::Model::FRanking::TypeName,
            Self->ParentKey,
            CacheKey,
            [this, Result, CacheKey]() -> Gs2::Core::Model::FGs2ErrorPtr
            {
                // ReSharper disable once CppLocalVariableMayBeConst
                TSharedPtr<Gs2::Ranking::Model::FRanking> Value;
                auto bCacheHit = Self->Gs2->Cache->TryGet<Gs2::Ranking::Model::FRanking>(
                    Self->ParentKey,
                    CacheKey,
                    &Value
                );
                if (!bCacheHit) {
                    const auto Future = Self->Get(
                        MakeShared<Gs2::Ranking::Request::FGetRankingRequest>()
                    );
                    Future->StartSynchronousTask();
                    if (Future->GetTask().IsError())
                    {
                        const auto Error = Future->GetTask().Error();
                        if (!Error.IsValid() || Error->Type() != Gs2::Core::Model::FNotFoundError::TypeString)
                        {
                            return Error;
                        }

                        Self->Gs2->Cache->Put(
                            Gs2::Ranking::Model::FRanking::TypeName,
                            Self->ParentKey,
                            CacheKey,
                            nullptr,
                            FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                        );

                        if (!Error->GetErrors().IsValid() || Error->Count() == 0 || !Error->Detail(0).IsValid() || Error->Detail(0)->GetComponent() != "ranking")
                        {
                            return Error;
                        }
                    }
                    else
                    {
                        Value = Future->GetTask().Result();
                    }
                    Future->EnsureCompletion();
                }

                if (!bCacheHit)
                {
                    FGs2ObjectPtr ExistingObject;
                    const bool Existing = Self->Gs2->Cache->TryGet(
                        Gs2::Ranking::Model::FRanking::TypeName,
                        Self->ParentKey,
                        CacheKey,
                        &ExistingObject
                    );
                    if (!Existing || ExistingObject != Value)
                    {
                        Self->Gs2->Cache->Put(
                            Gs2::Ranking::Model::FRanking::TypeName,
                            Self->ParentKey,
                            CacheKey,
                            Value,
                            FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                        );
                    }
                }
                *Result = Value;

                return nullptr;
            }
        );
    }

    TSharedPtr<FAsyncTask<FRankingAccessTokenDomain::FModelTask>> FRankingAccessTokenDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FRankingAccessTokenDomain::FModelTask>>(this->AsShared());
    }


    FRankingAccessTokenDomain::FSubscribeWithInitialCallTask::FSubscribeWithInitialCallTask(
        const TSharedPtr<FRankingAccessTokenDomain> Self,
        const TFunction<void(Gs2::Ranking::Model::FRankingPtr)>& Callback
    ): Self(Self), Callback(Callback)
    {
    }

    FRankingAccessTokenDomain::FSubscribeWithInitialCallTask::FSubscribeWithInitialCallTask(
        const FSubscribeWithInitialCallTask& From
    ): TGs2Future(From), Self(From.Self), Callback(From.Callback)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FRankingAccessTokenDomain::FSubscribeWithInitialCallTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Core::Domain::CallbackID>> Result
    )
    {
        const auto Future = Self->Model();
        Future->StartSynchronousTask();
        Future->EnsureCompletion();
        if (Future->GetTask().IsError())
        {
            return Future->GetTask().Error();
        }
        const auto Item = Future->GetTask().Result();
        const auto ID = Self->Subscribe(Callback);
        Callback(Item);
        *Result = MakeShared<Gs2::Core::Domain::CallbackID>(ID);
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FRankingAccessTokenDomain::FSubscribeWithInitialCallTask>> FRankingAccessTokenDomain::SubscribeWithInitialCall(
        TFunction<void(Gs2::Ranking::Model::FRankingPtr)> Callback
    )
    {
        return Gs2::Core::Util::New<FAsyncTask<FRankingAccessTokenDomain::FSubscribeWithInitialCallTask>>(this->AsShared(), Callback);
    }

    void FRankingAccessTokenDomain::Invalidate()
    {
        Gs2::Ranking::Model::Cache::FRankingCache::Delete(
            Gs2->Cache,
            NamespaceName,
            AccessToken.IsValid() ? UserId() : TOptional<FString>(),
            CategoryName,
            AdditionalScopeName,
            ScorerUserId,
            Index,
            AccessToken.IsValid() ? AccessToken->GetTimeOffset() : TOptional<int32>()
        );
    }

    Gs2::Core::Domain::CallbackID FRankingAccessTokenDomain::Subscribe(
        TFunction<void(Gs2::Ranking::Model::FRankingPtr)> Callback
    )
    {
        const TWeakPtr<Gs2::Core::Domain::FGs2> WeakGs2 = Gs2;
        const TWeakPtr<Ranking::Domain::FGs2RankingDomain> WeakService = Service;
        const FString RegisteredParentKey = ParentKey;
        const TOptional<FString> QueryNamespaceName = NamespaceName;
        const TOptional<FString> QueryCategoryName = CategoryName;
        const TOptional<FString> QueryAdditionalScopeName = AdditionalScopeName;
        const TOptional<FString> QueryScorerUserId = ScorerUserId;
        const TOptional<int64> QueryIndex = Index;
        const auto SourceToken = AccessToken;
        const TOptional<FString> RegisteredUserId = SourceToken.IsValid()
            ? TOptional<FString>(SourceToken->GetUserId())
            : TOptional<FString>();
        const int32 RegisteredTimeOffset = SourceToken.IsValid() ? SourceToken->GetTimeOffset().Get(0) : 0;
        return Gs2->Cache->Subscribe(
            Gs2::Ranking::Model::FRanking::TypeName,
            ParentKey,
            Gs2::Ranking::Model::Cache::FRankingCache::CreateCacheKey(
                ScorerUserId,
                Index
            ),
            [Callback](TSharedPtr<FGs2Object> obj)
            {
                Callback(StaticCastSharedPtr<Gs2::Ranking::Model::FRanking>(obj));
            },
            [WeakGs2, WeakService, RegisteredParentKey, QueryNamespaceName, QueryCategoryName, QueryAdditionalScopeName, QueryScorerUserId, QueryIndex, SourceToken, RegisteredUserId, RegisteredTimeOffset]()
            {
                const auto Owner = WeakGs2.Pin();
                if (!Owner.IsValid() || !SourceToken.IsValid() || !RegisteredUserId.IsSet())
                {
                    return;
                }
                const auto TokenSnapshot = MakeShared<Gs2::Auth::Model::FAccessToken>(*SourceToken);
                if (TokenSnapshot->GetUserId() != RegisteredUserId || TokenSnapshot->GetTimeOffset().Get(0) != RegisteredTimeOffset)
                {
                    return;
                }
                const auto Domain = MakeShared<FRankingAccessTokenDomain>(
                    Owner,
                    WeakService.Pin(),
                    QueryNamespaceName,
                    TokenSnapshot,
                    QueryCategoryName,
                    QueryAdditionalScopeName,
                    QueryScorerUserId,
                    QueryIndex
                );
                Domain->ParentKey = RegisteredParentKey;
                const auto Task = Domain->Model();
                Task->StartBackgroundTask();
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
            Gs2::Ranking::Model::Cache::FRankingCache::CreateCacheKey(
                ScorerUserId,
                Index
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
