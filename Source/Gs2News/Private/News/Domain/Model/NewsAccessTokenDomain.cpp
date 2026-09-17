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

#include "News/Domain/Model/NewsAccessToken.h"
#include "News/Domain/Model/News.h"
#include "News/Domain/Model/Namespace.h"
#include "News/Domain/Model/Progress.h"
#include "News/Domain/Model/Output.h"
#include "News/Domain/Model/CurrentNewsMaster.h"
#include "News/Domain/Model/SetCookieRequestEntry.h"
#include "News/Domain/Model/NewsAccessToken.h"
#include "News/Domain/Model/User.h"
#include "News/Domain/Model/UserAccessToken.h"
#include "News/Domain/Model/SetCookieRequestEntryAccessToken.h"
#include "News/Model/Cache/News.h"
#include "News/Model/Cache/SetCookieRequestEntry.h"

#include "Core/Domain/Gs2.h"
#include "Core/Domain/Transaction/JobQueueJobDomainFactory.h"
#include "Core/Domain/Transaction/InternalTransactionDomainFactory.h"
#include "Core/Domain/Transaction/ManualTransactionAccessTokenDomain.h"

namespace Gs2::News::Domain::Model
{

    FNewsAccessTokenDomain::FNewsAccessTokenDomain(
        const Core::Domain::FGs2Ptr& Gs2,
        const News::Domain::FGs2NewsDomainPtr& Service,
        const TOptional<FString> NamespaceName,
        const Gs2::Auth::Model::FAccessTokenPtr& AccessToken
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Gs2(Gs2),
        Service(Service),
        Client(MakeShared<Gs2::News::FGs2NewsRestClient>(Gs2->RestSession)),
        NamespaceName(NamespaceName),
        AccessToken(AccessToken),
        ParentKey(Gs2::News::Model::Cache::FNewsCache::CreateCacheParentKey(
            NamespaceName,
            UserId(),
            AccessToken.IsValid() ? AccessToken->GetTimeOffset() : TOptional<int32>()
        ))
    {
    }

    FNewsAccessTokenDomain::FNewsAccessTokenDomain(
        const FNewsAccessTokenDomain& From
    ):
        Gs2(From.Gs2),
        Service(From.Service),
        Client(From.Client),
        NamespaceName(From.NamespaceName),
        AccessToken(From.AccessToken),
        ParentKey(From.ParentKey)
    {

    }

    FNewsAccessTokenDomain::FWantGrantTask::FWantGrantTask(
        const TSharedPtr<FNewsAccessTokenDomain>& Self,
        const Request::FWantGrantRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FNewsAccessTokenDomain::FWantGrantTask::FWantGrantTask(
        const FWantGrantTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FNewsAccessTokenDomain::FWantGrantTask::Action(
        TSharedPtr<TSharedPtr<TArray<TSharedPtr<Gs2::News::Domain::Model::FSetCookieRequestEntryAccessTokenDomain>>>> Result
    )
    {
        Request
            ->WithContextStack((!Request->GetContextStack().IsSet() || Request->GetContextStack()->IsEmpty()) ? Self->Gs2->DefaultContextStack : Request->GetContextStack())
            ->WithNamespaceName(Self->NamespaceName)
            ->WithAccessToken(Self->AccessToken->GetToken());
        const auto CacheOwnerSnapshotUserId = Self->AccessToken.IsValid() ? Self->UserId() : TOptional<FString>();
        const auto CacheOwnerSnapshotTimeOffset = Self->AccessToken.IsValid() ? Self->AccessToken->GetTimeOffset() : TOptional<int32>();
        const auto Future = Self->Client->WantGrant(
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
                    Request->GetNamespaceName(), CacheOwnerSnapshotUserId, Item->GetKey(), Item->GetValue(),
                    CacheOwnerSnapshotTimeOffset, Item
                );
            }
        }

        auto Domain = MakeShared<TArray<TSharedPtr<Gs2::News::Domain::Model::FSetCookieRequestEntryAccessTokenDomain>>>();
        if (ResultModel.IsValid() && ResultModel->GetItems().IsValid())
        {
        for (auto i=0; i<ResultModel->GetItems()->Num(); i++)
        {
            Domain->Add(
                MakeShared<Gs2::News::Domain::Model::FSetCookieRequestEntryAccessTokenDomain>(
                    Self->Gs2,
                    Self->Service,
                    Request->GetNamespaceName(),
                    Self->AccessToken,
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

    TSharedPtr<FAsyncTask<FNewsAccessTokenDomain::FWantGrantTask>> FNewsAccessTokenDomain::WantGrant(
        Request::FWantGrantRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FWantGrantTask>>(this->AsShared(), Request);
    }

    FString FNewsAccessTokenDomain::CreateCacheParentKey(
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

    FString FNewsAccessTokenDomain::CreateCacheKey(
    )
    {
        return "Singleton";
    }

    FNewsAccessTokenDomain::FModelTask::FModelTask(
        const TSharedPtr<FNewsAccessTokenDomain> Self
    ): Self(Self)
    {

    }

    FNewsAccessTokenDomain::FModelTask::FModelTask(
        const FModelTask& From
    ): TGs2Future(From), Self(From.Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FNewsAccessTokenDomain::FModelTask::Action(
        TSharedPtr<TSharedPtr<Gs2::News::Model::FNews>> Result
    )
    {
        const FString CacheKey = Gs2::News::Model::Cache::FNewsCache::CreateCacheKey(
        );
        return Self->Gs2->Cache->ExecuteWithKeyLock(
            Gs2::News::Model::FNews::TypeName,
            Self->ParentKey,
            CacheKey,
            [this, Result, CacheKey]() -> Gs2::Core::Model::FGs2ErrorPtr
            {
                // ReSharper disable once CppLocalVariableMayBeConst
                TSharedPtr<Gs2::News::Model::FNews> Value;
                auto bCacheHit = Self->Gs2->Cache->TryGet<Gs2::News::Model::FNews>(
                    Self->ParentKey,
                    CacheKey,
                    &Value
                );
                *Result = Value;

                return nullptr;
            }
        );
    }

    TSharedPtr<FAsyncTask<FNewsAccessTokenDomain::FModelTask>> FNewsAccessTokenDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FNewsAccessTokenDomain::FModelTask>>(this->AsShared());
    }


    FNewsAccessTokenDomain::FSubscribeWithInitialCallTask::FSubscribeWithInitialCallTask(
        const TSharedPtr<FNewsAccessTokenDomain> Self,
        const TFunction<void(Gs2::News::Model::FNewsPtr)>& Callback
    ): Self(Self), Callback(Callback)
    {
    }

    FNewsAccessTokenDomain::FSubscribeWithInitialCallTask::FSubscribeWithInitialCallTask(
        const FSubscribeWithInitialCallTask& From
    ): TGs2Future(From), Self(From.Self), Callback(From.Callback)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FNewsAccessTokenDomain::FSubscribeWithInitialCallTask::Action(
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

    TSharedPtr<FAsyncTask<FNewsAccessTokenDomain::FSubscribeWithInitialCallTask>> FNewsAccessTokenDomain::SubscribeWithInitialCall(
        TFunction<void(Gs2::News::Model::FNewsPtr)> Callback
    )
    {
        return Gs2::Core::Util::New<FAsyncTask<FNewsAccessTokenDomain::FSubscribeWithInitialCallTask>>(this->AsShared(), Callback);
    }

    void FNewsAccessTokenDomain::Invalidate()
    {
        Gs2::News::Model::Cache::FNewsCache::Delete(
            Gs2->Cache,
            NamespaceName,
            AccessToken.IsValid() ? UserId() : TOptional<FString>(),
            AccessToken.IsValid() ? AccessToken->GetTimeOffset() : TOptional<int32>()
        );
    }

    Gs2::Core::Domain::CallbackID FNewsAccessTokenDomain::Subscribe(
        TFunction<void(Gs2::News::Model::FNewsPtr)> Callback
    )
    {
        const TWeakPtr<Gs2::Core::Domain::FGs2> WeakGs2 = Gs2;
        const TWeakPtr<News::Domain::FGs2NewsDomain> WeakService = Service;
        const FString RegisteredParentKey = ParentKey;
        const TOptional<FString> QueryNamespaceName = NamespaceName;
        const auto SourceToken = AccessToken;
        const TOptional<FString> RegisteredUserId = SourceToken.IsValid()
            ? TOptional<FString>(SourceToken->GetUserId())
            : TOptional<FString>();
        const int32 RegisteredTimeOffset = SourceToken.IsValid() ? SourceToken->GetTimeOffset().Get(0) : 0;
        return Gs2->Cache->Subscribe(
            Gs2::News::Model::FNews::TypeName,
            ParentKey,
            Gs2::News::Model::Cache::FNewsCache::CreateCacheKey(
            ),
            [Callback](TSharedPtr<FGs2Object> obj)
            {
                Callback(StaticCastSharedPtr<Gs2::News::Model::FNews>(obj));
            },
            [WeakGs2, WeakService, RegisteredParentKey, QueryNamespaceName, SourceToken, RegisteredUserId, RegisteredTimeOffset]()
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
                const auto Domain = MakeShared<FNewsAccessTokenDomain>(
                    Owner,
                    WeakService.Pin(),
                    QueryNamespaceName,
                    TokenSnapshot
                );
                Domain->ParentKey = RegisteredParentKey;
                const auto Task = Domain->Model();
                Task->StartBackgroundTask();
            }
        );
    }

    void FNewsAccessTokenDomain::Unsubscribe(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        Gs2->Cache->Unsubscribe(
            Gs2::News::Model::FNews::TypeName,
            ParentKey,
            Gs2::News::Model::Cache::FNewsCache::CreateCacheKey(
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
