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

#include "News/Domain/Model/SetCookieRequestEntry.h"
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
#include "News/Model/Cache/SetCookieRequestEntry.h"

#include "Core/Domain/Gs2.h"
#include "Core/Domain/Transaction/JobQueueJobDomainFactory.h"
#include "Core/Domain/Transaction/InternalTransactionDomainFactory.h"
#include "Core/Domain/Transaction/ManualTransactionDomain.h"

namespace Gs2::News::Domain::Model
{

    FSetCookieRequestEntryDomain::FSetCookieRequestEntryDomain(
        const Core::Domain::FGs2Ptr& Gs2,
        const News::Domain::FGs2NewsDomainPtr& Service,
        const TOptional<FString> NamespaceName,
        const TOptional<FString> UserId,
        const TOptional<FString> Key,
        const TOptional<FString> Value
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Gs2(Gs2),
        Service(Service),
        Client(MakeShared<Gs2::News::FGs2NewsRestClient>(Gs2->RestSession)),
        NamespaceName(NamespaceName),
        UserId(UserId),
        Key(Key),
        Value(Value),
        ParentKey(Gs2::News::Domain::Model::FUserDomain::CreateCacheParentKey(
            NamespaceName,
            UserId,
            "SetCookieRequestEntry"
        ))
    {
    }

    FSetCookieRequestEntryDomain::FSetCookieRequestEntryDomain(
        const FSetCookieRequestEntryDomain& From
    ):
        Gs2(From.Gs2),
        Service(From.Service),
        Client(From.Client),
        NamespaceName(From.NamespaceName),
        UserId(From.UserId),
        Key(From.Key),
        Value(From.Value),
        ParentKey(From.ParentKey)
    {

    }

    FString FSetCookieRequestEntryDomain::CreateCacheParentKey(
        TOptional<FString> NamespaceName,
        TOptional<FString> UserId,
        TOptional<FString> Key,
        TOptional<FString> Value,
        FString ChildType
    )
    {
        return FString("") +
            (NamespaceName.IsSet() ? *NamespaceName : "null") + ":" +
            (UserId.IsSet() ? *UserId : "null") + ":" +
            (Key.IsSet() ? *Key : "null") + ":" +
            (Value.IsSet() ? *Value : "null") + ":" +
            ChildType;
    }

    FString FSetCookieRequestEntryDomain::CreateCacheKey(
        TOptional<FString> Key,
        TOptional<FString> Value
    )
    {
        return FString("") +
            (Key.IsSet() ? *Key : "null") + ":" +
            (Value.IsSet() ? *Value : "null");
    }

    FSetCookieRequestEntryDomain::FModelTask::FModelTask(
        const TSharedPtr<FSetCookieRequestEntryDomain> Self
    ): Self(Self)
    {

    }

    FSetCookieRequestEntryDomain::FModelTask::FModelTask(
        const FModelTask& From
    ): TGs2Future(From), Self(From.Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FSetCookieRequestEntryDomain::FModelTask::Action(
        TSharedPtr<TSharedPtr<Gs2::News::Model::FSetCookieRequestEntry>> Result
    )
    {
        const auto CacheParentKey = Gs2::News::Model::Cache::FSetCookieRequestEntryCache::CreateCacheParentKey(

            Self->NamespaceName,
            Self->UserId,
            TOptional<int32>()
        );
        const auto CacheKey = Gs2::News::Model::Cache::FSetCookieRequestEntryCache::CreateCacheKey(

            Self->Key,
            Self->Value
        );
        return Self->Gs2->Cache->ExecuteWithKeyLock(
            Gs2::News::Model::FSetCookieRequestEntry::TypeName,
            CacheParentKey,
            CacheKey,
            [Self = Self, Result]() -> Gs2::Core::Model::FGs2ErrorPtr
            {
                Gs2::News::Model::FSetCookieRequestEntryPtr Value;
                const auto CacheHit = Gs2::News::Model::Cache::FSetCookieRequestEntryCache::TryGet(
                    Self->Gs2->Cache,

                    Self->NamespaceName,
                    Self->UserId,
                    Self->Key,
                    Self->Value,
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

    TSharedPtr<FAsyncTask<FSetCookieRequestEntryDomain::FModelTask>> FSetCookieRequestEntryDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FSetCookieRequestEntryDomain::FModelTask>>(this->AsShared());
    }

    void FSetCookieRequestEntryDomain::Invalidate()
    {
        Gs2::News::Model::Cache::FSetCookieRequestEntryCache::Delete(
            Gs2->Cache,

            NamespaceName,
            UserId,
            Key,
            Value,
            TOptional<int32>()
        );
    }

    FSetCookieRequestEntryDomain::FSubscribeWithInitialCallTask::FSubscribeWithInitialCallTask(
        const TSharedPtr<FSetCookieRequestEntryDomain>& Self,
        TFunction<void(Gs2::News::Model::FSetCookieRequestEntryPtr)> Callback
    ):
        Self(Self),
        Callback(Callback)
    {
    }

    FSetCookieRequestEntryDomain::FSubscribeWithInitialCallTask::FSubscribeWithInitialCallTask(
        const FSubscribeWithInitialCallTask& From
    ):
        TGs2Future(From),
        Self(From.Self),
        Callback(From.Callback)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FSetCookieRequestEntryDomain::FSubscribeWithInitialCallTask::Action(
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

    TSharedPtr<FAsyncTask<FSetCookieRequestEntryDomain::FSubscribeWithInitialCallTask>> FSetCookieRequestEntryDomain::SubscribeWithInitialCall(
        TFunction<void(Gs2::News::Model::FSetCookieRequestEntryPtr)> Callback
    )
    {
        return Gs2::Core::Util::New<FAsyncTask<FSubscribeWithInitialCallTask>>(this->AsShared(), Callback);
    }

    Gs2::Core::Domain::CallbackID FSetCookieRequestEntryDomain::Subscribe(
        TFunction<void(Gs2::News::Model::FSetCookieRequestEntryPtr)> Callback
    )
    {
        const auto SubscriptionParentKey = Gs2::News::Model::Cache::FSetCookieRequestEntryCache::CreateCacheParentKey(

            NamespaceName,
            UserId,
            TOptional<int32>()
        );
        const auto SubscriptionCacheKey = Gs2::News::Model::Cache::FSetCookieRequestEntryCache::CreateCacheKey(

            Key,
            Value
        );
        const TWeakPtr<Gs2::Core::Domain::FGs2> WeakGs2 = Gs2;
        const TWeakPtr<News::Domain::FGs2NewsDomain> WeakService = Service;
        const FString RegisteredParentKey = SubscriptionParentKey;
        const TOptional<FString> QueryNamespaceName = NamespaceName;
        const TOptional<FString> QueryUserId = UserId;
        const TOptional<FString> QueryKey = Key;
        const TOptional<FString> QueryValue = Value;
        return Gs2->Cache->Subscribe(
            Gs2::News::Model::FSetCookieRequestEntry::TypeName,
            SubscriptionParentKey,
            SubscriptionCacheKey,
            [Callback](TSharedPtr<FGs2Object> obj)
            {
                Callback(StaticCastSharedPtr<Gs2::News::Model::FSetCookieRequestEntry>(obj));
            },
            [WeakGs2, WeakService, RegisteredParentKey, QueryNamespaceName, QueryUserId, QueryKey, QueryValue]()
            {
                const auto Owner = WeakGs2.Pin();
                if (!Owner.IsValid())
                {
                    return;
                }
                const auto Domain = MakeShared<FSetCookieRequestEntryDomain>(
                    Owner,
                    WeakService.Pin(),
                    QueryNamespaceName,
                    QueryUserId,
                    QueryKey,
                    QueryValue
                );
                Domain->ParentKey = RegisteredParentKey;
                const auto Task = Domain->Model();
                Task->StartBackgroundTask();
            }
        );
    }

    void FSetCookieRequestEntryDomain::Unsubscribe(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        const auto SubscriptionParentKey = Gs2::News::Model::Cache::FSetCookieRequestEntryCache::CreateCacheParentKey(

            NamespaceName,
            UserId,
            TOptional<int32>()
        );
        const auto SubscriptionCacheKey = Gs2::News::Model::Cache::FSetCookieRequestEntryCache::CreateCacheKey(

            Key,
            Value
        );
        Gs2->Cache->Unsubscribe(
            Gs2::News::Model::FSetCookieRequestEntry::TypeName,
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
