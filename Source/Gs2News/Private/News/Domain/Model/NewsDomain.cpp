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

#include "News/Domain/Model/News.h"
#include "News/Domain/Model/Namespace.h"
#include "News/Domain/Model/Progress.h"
#include "News/Domain/Model/Output.h"
#include "News/Domain/Model/CurrentNewsMaster.h"
#include "News/Domain/Model/SetCookieRequestEntry.h"
#include "News/Domain/Model/NewsAccessToken.h"
#include "News/Domain/Model/User.h"
#include "News/Domain/Model/UserAccessToken.h"
#include "News/Domain/Model/News.h"
#include "News/Domain/Model/SetCookieRequestEntry.h"
#include "News/Model/Cache/News.h"
#include "News/Model/Cache/SetCookieRequestEntry.h"

#include "Core/Domain/Gs2.h"
#include "Core/Domain/Transaction/JobQueueJobDomainFactory.h"
#include "Core/Domain/Transaction/InternalTransactionDomainFactory.h"
#include "Core/Domain/Transaction/ManualTransactionDomain.h"

namespace Gs2::News::Domain::Model
{

    FNewsDomain::FNewsDomain(
        const Core::Domain::FGs2Ptr& Gs2,
        const News::Domain::FGs2NewsDomainPtr& Service,
        const TOptional<FString> NamespaceName,
        const TOptional<FString> UserId
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Gs2(Gs2),
        Service(Service),
        Client(MakeShared<Gs2::News::FGs2NewsRestClient>(Gs2->RestSession)),
        NamespaceName(NamespaceName),
        UserId(UserId),
        ParentKey(Gs2::News::Domain::Model::FUserDomain::CreateCacheParentKey(
            NamespaceName,
            UserId,
            "News"
        ))
    {
    }

    FNewsDomain::FNewsDomain(
        const FNewsDomain& From
    ):
        Gs2(From.Gs2),
        Service(From.Service),
        Client(From.Client),
        NamespaceName(From.NamespaceName),
        UserId(From.UserId),
        ParentKey(From.ParentKey)
    {

    }

    FNewsDomain::FWantGrantTask::FWantGrantTask(
        const TSharedPtr<FNewsDomain>& Self,
        const Request::FWantGrantByUserIdRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FNewsDomain::FWantGrantTask::FWantGrantTask(
        const FWantGrantTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FNewsDomain::FWantGrantTask::Action(
        TSharedPtr<TSharedPtr<TArray<TSharedPtr<Gs2::News::Domain::Model::FSetCookieRequestEntryDomain>>>> Result
    )
    {
        Request
            ->WithContextStack((!Request->GetContextStack().IsSet() || Request->GetContextStack()->IsEmpty()) ? Self->Gs2->DefaultContextStack : Request->GetContextStack())
            ->WithNamespaceName(Self->NamespaceName)
            ->WithUserId(Self->UserId);
        const auto Future = Self->Client->WantGrantByUserId(
            Request
        );
        Future->StartSynchronousTask();
        if (Future->GetTask().IsError())
        {
            return Future->GetTask().Error();
        }
        const auto ResultModel = Future->GetTask().Result();
        Future->EnsureCompletion();
        if (ResultModel.IsValid() && ResultModel->GetItems().IsValid())
        {
            for (const auto& Item : *ResultModel->GetItems())
            {
                if (!Item.IsValid()) continue;
                Gs2::News::Model::Cache::FSetCookieRequestEntryCache::Put(
                    Self->Gs2->Cache,
                    Request->GetNamespaceName(), Request->GetUserId(), Item->GetKey(), Item->GetValue(),
                    TOptional<int32>(), Item
                );
            }
        }

        auto Domain = MakeShared<TArray<TSharedPtr<Gs2::News::Domain::Model::FSetCookieRequestEntryDomain>>>();
        if (ResultModel.IsValid() && ResultModel->GetItems().IsValid())
        {
        for (auto i=0; i<ResultModel->GetItems()->Num(); i++)
        {
            Domain->Add(
                MakeShared<Gs2::News::Domain::Model::FSetCookieRequestEntryDomain>(
                    Self->Gs2,
                    Self->Service,
                    Request->GetNamespaceName(),
                    Request->GetUserId(),
                    (*ResultModel->GetItems())[i]->GetKey(),
                    (*ResultModel->GetItems())[i]->GetValue()
                )
            );
        }
        }
        if (ResultModel != nullptr)
        {
            if (ResultModel->GetBrowserUrl().IsSet())
            {
                Self->BrowserUrl = ResultModel->GetBrowserUrl();
            }
            if (ResultModel->GetZipUrl().IsSet())
            {
                Self->ZipUrl = ResultModel->GetZipUrl();
            }
        }
        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FNewsDomain::FWantGrantTask>> FNewsDomain::WantGrant(
        Request::FWantGrantByUserIdRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FWantGrantTask>>(this->AsShared(), Request);
    }

    FString FNewsDomain::CreateCacheParentKey(
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

    FString FNewsDomain::CreateCacheKey(
    )
    {
        return "Singleton";
    }

    FNewsDomain::FModelTask::FModelTask(
        const TSharedPtr<FNewsDomain> Self
    ): Self(Self)
    {

    }

    FNewsDomain::FModelTask::FModelTask(
        const FModelTask& From
    ): TGs2Future(From), Self(From.Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FNewsDomain::FModelTask::Action(
        TSharedPtr<TSharedPtr<Gs2::News::Model::FNews>> Result
    )
    {
        const auto CacheParentKey = Gs2::News::Model::Cache::FNewsCache::CreateCacheParentKey(

            Self->NamespaceName,
            Self->UserId,
            TOptional<int32>()
        );
        const auto CacheKey = Gs2::News::Model::Cache::FNewsCache::CreateCacheKey(

        );
        return Self->Gs2->Cache->ExecuteWithKeyLock(
            Gs2::News::Model::FNews::TypeName,
            CacheParentKey,
            CacheKey,
            [Self = Self, Result]() -> Gs2::Core::Model::FGs2ErrorPtr
            {
                Gs2::News::Model::FNewsPtr Value;
                const auto CacheHit = Gs2::News::Model::Cache::FNewsCache::TryGet(
                    Self->Gs2->Cache,

                    Self->NamespaceName,
                    Self->UserId,
                    TOptional<int32>(),
                    &Value
                );
                if (CacheHit)
                {
                    *Result = Value;
                    return nullptr;
                }
                *Result = Value;
                return nullptr;
            }
        );
    }

    TSharedPtr<FAsyncTask<FNewsDomain::FModelTask>> FNewsDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FNewsDomain::FModelTask>>(this->AsShared());
    }

    void FNewsDomain::Invalidate()
    {
        Gs2::News::Model::Cache::FNewsCache::Delete(
            Gs2->Cache,

            NamespaceName,
            UserId,
            TOptional<int32>()
        );
    }

    FNewsDomain::FSubscribeWithInitialCallTask::FSubscribeWithInitialCallTask(
        const TSharedPtr<FNewsDomain>& Self,
        TFunction<void(Gs2::News::Model::FNewsPtr)> Callback
    ):
        Self(Self),
        Callback(Callback)
    {
    }

    FNewsDomain::FSubscribeWithInitialCallTask::FSubscribeWithInitialCallTask(
        const FSubscribeWithInitialCallTask& From
    ):
        TGs2Future(From),
        Self(From.Self),
        Callback(From.Callback)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FNewsDomain::FSubscribeWithInitialCallTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Core::Domain::CallbackID>> Result
    )
    {
        const auto Task = Self->Model();
        Task->StartSynchronousTask();
        Task->EnsureCompletion();
        if (Task->GetTask().IsError()) return Task->GetTask().Error();
        const auto Item = Task->GetTask().Result();
        const auto CallbackId = Self->Subscribe(Callback);
        Callback(Item);
        *Result = MakeShared<Gs2::Core::Domain::CallbackID>(CallbackId);
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FNewsDomain::FSubscribeWithInitialCallTask>> FNewsDomain::SubscribeWithInitialCall(
        TFunction<void(Gs2::News::Model::FNewsPtr)> Callback
    )
    {
        return Gs2::Core::Util::New<FAsyncTask<FSubscribeWithInitialCallTask>>(this->AsShared(), Callback);
    }

    Gs2::Core::Domain::CallbackID FNewsDomain::Subscribe(
        TFunction<void(Gs2::News::Model::FNewsPtr)> Callback
    )
    {
        const auto SubscriptionParentKey = Gs2::News::Model::Cache::FNewsCache::CreateCacheParentKey(

            NamespaceName,
            UserId,
            TOptional<int32>()
        );
        const auto SubscriptionCacheKey = Gs2::News::Model::Cache::FNewsCache::CreateCacheKey(

        );
        const TWeakPtr<Gs2::Core::Domain::FGs2> WeakGs2 = Gs2;
        const TWeakPtr<News::Domain::FGs2NewsDomain> WeakService = Service;
        const FString RegisteredParentKey = SubscriptionParentKey;
        const TOptional<FString> QueryNamespaceName = NamespaceName;
        const TOptional<FString> QueryUserId = UserId;
        return Gs2->Cache->Subscribe(
            Gs2::News::Model::FNews::TypeName,
            SubscriptionParentKey,
            SubscriptionCacheKey,
            [Callback](TSharedPtr<FGs2Object> obj)
            {
                Callback(StaticCastSharedPtr<Gs2::News::Model::FNews>(obj));
            },
            [WeakGs2, WeakService, RegisteredParentKey, QueryNamespaceName, QueryUserId]()
            {
                const auto Owner = WeakGs2.Pin();
                if (!Owner.IsValid())
                {
                    return;
                }
                const auto Domain = MakeShared<FNewsDomain>(
                    Owner,
                    WeakService.Pin(),
                    QueryNamespaceName,
                    QueryUserId
                );
                Domain->ParentKey = RegisteredParentKey;
                const auto Task = Domain->Model();
                Task->StartBackgroundTask();
            }
        );
    }

    void FNewsDomain::Unsubscribe(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        const auto SubscriptionParentKey = Gs2::News::Model::Cache::FNewsCache::CreateCacheParentKey(

            NamespaceName,
            UserId,
            TOptional<int32>()
        );
        const auto SubscriptionCacheKey = Gs2::News::Model::Cache::FNewsCache::CreateCacheKey(

        );
        Gs2->Cache->Unsubscribe(
            Gs2::News::Model::FNews::TypeName,
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
