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

#include "Ranking/Domain/Model/SubscribeUser.h"
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
#include "Ranking/Model/Cache/SubscribeUser.h"

#include "Core/Domain/Gs2.h"
#include "Core/Domain/Transaction/JobQueueJobDomainFactory.h"
#include "Core/Domain/Transaction/InternalTransactionDomainFactory.h"
#include "Core/Domain/Transaction/ManualTransactionDomain.h"

namespace Gs2::Ranking::Domain::Model
{

    FSubscribeUserDomain::FSubscribeUserDomain(
        const Core::Domain::FGs2Ptr& Gs2,
        const Ranking::Domain::FGs2RankingDomainPtr& Service,
        const TOptional<FString> NamespaceName,
        const TOptional<FString> UserId,
        const TOptional<FString> CategoryName,
        const TOptional<FString> AdditionalScopeName,
        const TOptional<FString> TargetUserId
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Gs2(Gs2),
        Service(Service),
        Client(MakeShared<Gs2::Ranking::FGs2RankingRestClient>(Gs2->RestSession)),
        NamespaceName(NamespaceName),
        UserId(UserId),
        CategoryName(CategoryName),
        AdditionalScopeName(AdditionalScopeName),
        TargetUserId(TargetUserId),
        ParentKey(Gs2::Ranking::Model::Cache::FSubscribeUserCache::CreateCacheParentKey(
            NamespaceName,
            UserId,
            CategoryName,
            AdditionalScopeName,
            TOptional<int32>()
        ))
    {
    }

    FSubscribeUserDomain::FSubscribeUserDomain(
        const FSubscribeUserDomain& From
    ):
        Gs2(From.Gs2),
        Service(From.Service),
        Client(From.Client),
        NamespaceName(From.NamespaceName),
        UserId(From.UserId),
        CategoryName(From.CategoryName),
        AdditionalScopeName(From.AdditionalScopeName),
        TargetUserId(From.TargetUserId),
        ParentKey(From.ParentKey)
    {

    }

    FSubscribeUserDomain::FGetTask::FGetTask(
        const TSharedPtr<FSubscribeUserDomain>& Self,
        const Request::FGetSubscribeByUserIdRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FSubscribeUserDomain::FGetTask::FGetTask(
        const FGetTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FSubscribeUserDomain::FGetTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Ranking::Model::FSubscribeUser>> Result
    )
    {
        Request
            ->WithContextStack((!Request->GetContextStack().IsSet() || Request->GetContextStack()->IsEmpty()) ? Self->Gs2->DefaultContextStack : Request->GetContextStack())
            ->WithNamespaceName(Self->NamespaceName)
            ->WithCategoryName(Self->CategoryName)
            ->WithUserId(Self->UserId)
            ->WithTargetUserId(Self->TargetUserId);
        const auto Future = Self->Client->GetSubscribeByUserId(
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

    TSharedPtr<FAsyncTask<FSubscribeUserDomain::FGetTask>> FSubscribeUserDomain::Get(
        Request::FGetSubscribeByUserIdRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FGetTask>>(this->AsShared(), Request);
    }

    FSubscribeUserDomain::FUnsubscribeTask::FUnsubscribeTask(
        const TSharedPtr<FSubscribeUserDomain>& Self,
        const Request::FUnsubscribeByUserIdRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FSubscribeUserDomain::FUnsubscribeTask::FUnsubscribeTask(
        const FUnsubscribeTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FSubscribeUserDomain::FUnsubscribeTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Ranking::Domain::Model::FSubscribeUserDomain>> Result
    )
    {
        Request
            ->WithContextStack((!Request->GetContextStack().IsSet() || Request->GetContextStack()->IsEmpty()) ? Self->Gs2->DefaultContextStack : Request->GetContextStack())
            ->WithNamespaceName(Self->NamespaceName)
            ->WithCategoryName(Self->CategoryName)
            ->WithUserId(Self->UserId)
            ->WithTargetUserId(Self->TargetUserId);
        const auto Future = Self->Client->UnsubscribeByUserId(
            Request
        );
        Future->StartSynchronousTask();
        if (Future->GetTask().IsError())
        {
            return Future->GetTask().Error();
        }
        const auto ResultModel = Future->GetTask().Result();
        Future->EnsureCompletion();
        if (ResultModel->GetItem() != nullptr)
        {
            const auto Key = Gs2::Ranking::Domain::Model::FSubscribeUserDomain::CreateCacheKey(
                ResultModel->GetItem()->GetTargetUserId()
            );
            Self->Gs2->Cache->Delete(
                Gs2::Ranking::Model::FSubscribeUser::TypeName,
                Self->ParentKey,
                Key
            );
        }
        auto Domain = Self;

        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FSubscribeUserDomain::FUnsubscribeTask>> FSubscribeUserDomain::Unsubscribe(
        Request::FUnsubscribeByUserIdRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FUnsubscribeTask>>(this->AsShared(), Request);
    }

    FString FSubscribeUserDomain::CreateCacheParentKey(
        TOptional<FString> NamespaceName,
        TOptional<FString> UserId,
        TOptional<FString> CategoryName,
        TOptional<FString> AdditionalScopeName,
        TOptional<FString> TargetUserId,
        FString ChildType
    )
    {
        return FString("") +
            (NamespaceName.IsSet() ? *NamespaceName : "null") + ":" +
            (UserId.IsSet() ? *UserId : "null") + ":" +
            (CategoryName.IsSet() ? *CategoryName : "null") + ":" +
            (AdditionalScopeName.IsSet() ? *AdditionalScopeName : "null") + ":" +
            (TargetUserId.IsSet() ? *TargetUserId : "null") + ":" +
            ChildType;
    }

    FString FSubscribeUserDomain::CreateCacheKey(
        TOptional<FString> TargetUserId
    )
    {
        return FString("") +
            (TargetUserId.IsSet() ? *TargetUserId : "null");
    }

    FSubscribeUserDomain::FModelTask::FModelTask(
        const TSharedPtr<FSubscribeUserDomain> Self
    ): Self(Self)
    {

    }

    FSubscribeUserDomain::FModelTask::FModelTask(
        const FModelTask& From
    ): TGs2Future(From), Self(From.Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FSubscribeUserDomain::FModelTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Ranking::Model::FSubscribeUser>> Result
    )
    {
        const FString CacheKey = Gs2::Ranking::Domain::Model::FSubscribeUserDomain::CreateCacheKey(
            Self->TargetUserId
        );
        return Self->Gs2->Cache->ExecuteWithKeyLock(
            Gs2::Ranking::Model::FSubscribeUser::TypeName,
            Self->ParentKey,
            CacheKey,
            [this, Result, CacheKey]() -> Gs2::Core::Model::FGs2ErrorPtr
            {
                // ReSharper disable once CppLocalVariableMayBeConst
                TSharedPtr<Gs2::Ranking::Model::FSubscribeUser> Value;
                auto bCacheHit = Self->Gs2->Cache->TryGet<Gs2::Ranking::Model::FSubscribeUser>(
                    Self->ParentKey,
                    CacheKey,
                    &Value
                );
                if (!bCacheHit) {
                    const auto Future = Self->Get(
                        MakeShared<Gs2::Ranking::Request::FGetSubscribeByUserIdRequest>()
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
                            Gs2::Ranking::Model::FSubscribeUser::TypeName,
                            Self->ParentKey,
                            CacheKey,
                            nullptr,
                            FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                        );

                        if (!Error->GetErrors().IsValid() || Error->Count() == 0 || !Error->Detail(0).IsValid() || Error->Detail(0)->GetComponent() != "subscribeUser")
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
                        Gs2::Ranking::Model::FSubscribeUser::TypeName,
                        Self->ParentKey,
                        CacheKey,
                        &ExistingObject
                    );
                    if (!Existing || ExistingObject != Value)
                    {
                        Self->Gs2->Cache->Put(
                            Gs2::Ranking::Model::FSubscribeUser::TypeName,
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

    TSharedPtr<FAsyncTask<FSubscribeUserDomain::FModelTask>> FSubscribeUserDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FSubscribeUserDomain::FModelTask>>(this->AsShared());
    }

    FSubscribeUserDomain::FSubscribeWithInitialCallTask::FSubscribeWithInitialCallTask(
        const TSharedPtr<FSubscribeUserDomain> Self,
        const TFunction<void(Gs2::Ranking::Model::FSubscribeUserPtr)>& Callback
    ): Self(Self), Callback(Callback)
    {
    }

    FSubscribeUserDomain::FSubscribeWithInitialCallTask::FSubscribeWithInitialCallTask(
        const FSubscribeWithInitialCallTask& From
    ): TGs2Future(From), Self(From.Self), Callback(From.Callback)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FSubscribeUserDomain::FSubscribeWithInitialCallTask::Action(
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

    TSharedPtr<FAsyncTask<FSubscribeUserDomain::FSubscribeWithInitialCallTask>> FSubscribeUserDomain::SubscribeWithInitialCall(
        TFunction<void(Gs2::Ranking::Model::FSubscribeUserPtr)> Callback
    )
    {
        return Gs2::Core::Util::New<FAsyncTask<FSubscribeWithInitialCallTask>>(this->AsShared(), Callback);
    }

    void FSubscribeUserDomain::Invalidate()
    {
        Gs2::Ranking::Model::Cache::FSubscribeUserCache::Delete(
            Gs2->Cache,
            NamespaceName,
            UserId,
            CategoryName,
            AdditionalScopeName,
            TargetUserId,
            TOptional<int32>()
        );
    }

    Gs2::Core::Domain::CallbackID FSubscribeUserDomain::Subscribe(
        TFunction<void(Gs2::Ranking::Model::FSubscribeUserPtr)> Callback
    )
    {
        const auto SubscriptionParentKey = Gs2::Ranking::Model::Cache::FSubscribeUserCache::CreateCacheParentKey(

            NamespaceName,
            UserId,
            CategoryName,
            AdditionalScopeName,
            TOptional<int32>()
        );
        const auto SubscriptionCacheKey = Gs2::Ranking::Model::Cache::FSubscribeUserCache::CreateCacheKey(

            TargetUserId
        );
        const TWeakPtr<Gs2::Core::Domain::FGs2> WeakGs2 = Gs2;
        const TWeakPtr<Ranking::Domain::FGs2RankingDomain> WeakService = Service;
        const FString RegisteredParentKey = SubscriptionParentKey;
        const TOptional<FString> QueryNamespaceName = NamespaceName;
        const TOptional<FString> QueryUserId = UserId;
        const TOptional<FString> QueryCategoryName = CategoryName;
        const TOptional<FString> QueryAdditionalScopeName = AdditionalScopeName;
        const TOptional<FString> QueryTargetUserId = TargetUserId;
        return Gs2->Cache->Subscribe(
            Gs2::Ranking::Model::FSubscribeUser::TypeName,
            SubscriptionParentKey,
            SubscriptionCacheKey,
            [Callback](TSharedPtr<FGs2Object> obj)
            {
                Callback(StaticCastSharedPtr<Gs2::Ranking::Model::FSubscribeUser>(obj));
            },
            [WeakGs2, WeakService, RegisteredParentKey, QueryNamespaceName, QueryUserId, QueryCategoryName, QueryAdditionalScopeName, QueryTargetUserId]()
            {
                const auto Owner = WeakGs2.Pin();
                if (!Owner.IsValid())
                {
                    return;
                }
                const auto Domain = MakeShared<FSubscribeUserDomain>(
                    Owner,
                    WeakService.Pin(),
                    QueryNamespaceName,
                    QueryUserId,
                    QueryCategoryName,
                    QueryAdditionalScopeName,
                    QueryTargetUserId
                );
                Domain->ParentKey = RegisteredParentKey;
                const auto Task = Domain->Model();
                Task->StartBackgroundTask();
            }
        );
    }

    void FSubscribeUserDomain::Unsubscribe(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        const auto SubscriptionParentKey = Gs2::Ranking::Model::Cache::FSubscribeUserCache::CreateCacheParentKey(

            NamespaceName,
            UserId,
            CategoryName,
            AdditionalScopeName,
            TOptional<int32>()
        );
        const auto SubscriptionCacheKey = Gs2::Ranking::Model::Cache::FSubscribeUserCache::CreateCacheKey(

            TargetUserId
        );
        Gs2->Cache->Unsubscribe(
            Gs2::Ranking::Model::FSubscribeUser::TypeName,
            SubscriptionParentKey,
            SubscriptionCacheKey,
            CallbackID
        );
    }
}

#if defined(_MSC_VER)
#pragma warning (pop)
#elif defined(__clang__)
#pragma clang diagnostic pop
#endif
