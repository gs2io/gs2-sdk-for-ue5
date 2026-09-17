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

#include "Showcase/Domain/Model/DisplayItemAccessToken.h"
#include "Showcase/Domain/Model/DisplayItem.h"
#include "Showcase/Domain/Model/Namespace.h"
#include "Showcase/Domain/Model/SalesItemMaster.h"
#include "Showcase/Domain/Model/SalesItemGroupMaster.h"
#include "Showcase/Domain/Model/ShowcaseMaster.h"
#include "Showcase/Domain/Model/CurrentShowcaseMaster.h"
#include "Showcase/Domain/Model/Showcase.h"
#include "Showcase/Domain/Model/ShowcaseAccessToken.h"
#include "Showcase/Domain/Model/DisplayItem.h"
#include "Showcase/Domain/Model/DisplayItemAccessToken.h"
#include "Showcase/Domain/Model/RandomShowcaseMaster.h"
#include "Showcase/Domain/Model/RandomShowcase.h"
#include "Showcase/Domain/Model/RandomShowcaseAccessToken.h"
#include "Showcase/Domain/Model/User.h"
#include "Showcase/Domain/Model/UserAccessToken.h"
#include "Showcase/Domain/Model/RandomShowcaseStatus.h"
#include "Showcase/Domain/Model/RandomShowcaseStatusAccessToken.h"
#include "Showcase/Domain/Model/RandomDisplayItem.h"
#include "Showcase/Domain/Model/RandomDisplayItemAccessToken.h"
#include "Showcase/Domain/SpeculativeExecutor/Transaction/BuyByUserIdSpeculativeExecutor.h"
#include "Showcase/Model/Cache/DisplayItem.h"

#include "Core/Domain/Gs2.h"
#include "Core/Domain/Transaction/JobQueueJobDomainFactory.h"
#include "Core/Domain/Transaction/InternalTransactionDomainFactory.h"
#include "Core/Domain/Transaction/ManualTransactionAccessTokenDomain.h"

namespace Gs2::Showcase::Domain::Model
{

    FDisplayItemAccessTokenDomain::FDisplayItemAccessTokenDomain(
        const Core::Domain::FGs2Ptr& Gs2,
        const Showcase::Domain::FGs2ShowcaseDomainPtr& Service,
        const TOptional<FString> NamespaceName,
        const Gs2::Auth::Model::FAccessTokenPtr& AccessToken,
        const TOptional<FString> ShowcaseName,
        const TOptional<FString> DisplayItemId
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Gs2(Gs2),
        Service(Service),
        Client(MakeShared<Gs2::Showcase::FGs2ShowcaseRestClient>(Gs2->RestSession)),
        NamespaceName(NamespaceName),
        AccessToken(AccessToken),
        ShowcaseName(ShowcaseName),
        DisplayItemId(DisplayItemId),
        ParentKey(Gs2::Showcase::Domain::Model::FShowcaseDomain::CreateCacheParentKey(
            NamespaceName,
            UserId(),
            ShowcaseName,
            "DisplayItem"
        ))
    {
    }

    FDisplayItemAccessTokenDomain::FDisplayItemAccessTokenDomain(
        const FDisplayItemAccessTokenDomain& From
    ):
        Gs2(From.Gs2),
        Service(From.Service),
        Client(From.Client),
        NamespaceName(From.NamespaceName),
        AccessToken(From.AccessToken),
        ShowcaseName(From.ShowcaseName),
        DisplayItemId(From.DisplayItemId),
        ParentKey(From.ParentKey)
    {

    }

    FDisplayItemAccessTokenDomain::FBuyTask::FBuyTask(
        const TSharedPtr<FDisplayItemAccessTokenDomain>& Self,
        const Request::FBuyRequestPtr Request,
        bool SpeculativeExecute
    ): Self(Self), Request(Request), SpeculativeExecute(SpeculativeExecute)
    {

    }

    FDisplayItemAccessTokenDomain::FBuyTask::FBuyTask(
        const FBuyTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request), SpeculativeExecute(From.SpeculativeExecute)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FDisplayItemAccessTokenDomain::FBuyTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Core::Domain::FTransactionAccessTokenDomain>> Result
    )
    {
        Request
            ->WithContextStack((!Request->GetContextStack().IsSet() || Request->GetContextStack()->IsEmpty()) ? Self->Gs2->DefaultContextStack : Request->GetContextStack())
            ->WithNamespaceName(Self->NamespaceName)
            ->WithShowcaseName(Self->ShowcaseName)
            ->WithDisplayItemId(Self->DisplayItemId)
            ->WithAccessToken(Self->AccessToken->GetToken());
        const auto Future = Self->Client->Buy(
            Request
        );
        Future->StartSynchronousTask();
        if (Future->GetTask().IsError())
        {
            return Future->GetTask().Error();
        }
        const auto ResultModel = Future->GetTask().Result();
        Future->EnsureCompletion();

        const auto Transaction = Gs2::Core::Domain::Internal::FTransactionDomainFactory::ToTransaction(
            Self->Gs2,
            Self->AccessToken,
            ResultModel->GetAutoRunStampSheet().IsSet() ? *ResultModel->GetAutoRunStampSheet() : false,
            ResultModel->GetTransactionId().IsSet() ? *ResultModel->GetTransactionId() : FString(),
            ResultModel->GetStampSheet().IsSet() ? *ResultModel->GetStampSheet() : FString(),
            ResultModel->GetStampSheetEncryptionKeyId().IsSet() ? *ResultModel->GetStampSheetEncryptionKeyId() : FString(),
            ResultModel->GetAtomicCommit().IsSet() ? *ResultModel->GetAtomicCommit() : false,
            ResultModel->GetTransactionResult()
        );
        const auto Future3 = Transaction->Wait(true);
        Future3->StartSynchronousTask();
        if (Future3->GetTask().IsError())
        {
            return Future3->GetTask().Error();
        }
        *Result = Transaction;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FDisplayItemAccessTokenDomain::FBuyTask>> FDisplayItemAccessTokenDomain::Buy(
        Request::FBuyRequestPtr Request,
        bool SpeculativeExecute
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FBuyTask>>(this->AsShared(), Request, SpeculativeExecute);
    }

    FString FDisplayItemAccessTokenDomain::CreateCacheParentKey(
        TOptional<FString> NamespaceName,
        TOptional<FString> UserId,
        TOptional<FString> ShowcaseName,
        TOptional<FString> DisplayItemId,
        FString ChildType
    )
    {
        return FString("") +
            (NamespaceName.IsSet() ? *NamespaceName : "null") + ":" +
            (UserId.IsSet() ? *UserId : "null") + ":" +
            (ShowcaseName.IsSet() ? *ShowcaseName : "null") + ":" +
            (DisplayItemId.IsSet() ? *DisplayItemId : "null") + ":" +
            ChildType;
    }

    FString FDisplayItemAccessTokenDomain::CreateCacheKey(
        TOptional<FString> DisplayItemId
    )
    {
        return FString("") +
            (DisplayItemId.IsSet() ? *DisplayItemId : "null");
    }

    FDisplayItemAccessTokenDomain::FModelTask::FModelTask(
        const TSharedPtr<FDisplayItemAccessTokenDomain> Self
    ): Self(Self)
    {

    }

    FDisplayItemAccessTokenDomain::FModelTask::FModelTask(
        const FModelTask& From
    ): TGs2Future(From), Self(From.Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FDisplayItemAccessTokenDomain::FModelTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Showcase::Model::FDisplayItem>> Result
    )
    {
        const auto CacheParentKey = Gs2::Showcase::Model::Cache::FDisplayItemCache::CreateCacheParentKey(

            Self->NamespaceName,
            Self->AccessToken.IsValid() ? Self->UserId() : TOptional<FString>(),
            Self->ShowcaseName,
            Self->AccessToken.IsValid() ? Self->AccessToken->GetTimeOffset() : TOptional<int32>()
        );
        const auto CacheKey = Gs2::Showcase::Model::Cache::FDisplayItemCache::CreateCacheKey(

            Self->DisplayItemId
        );
        return Self->Gs2->Cache->ExecuteWithKeyLock(
            Gs2::Showcase::Model::FDisplayItem::TypeName,
            CacheParentKey,
            CacheKey,
            [Self = Self, Result]() -> Gs2::Core::Model::FGs2ErrorPtr
            {
                Gs2::Showcase::Model::FDisplayItemPtr Value;
                const auto CacheHit = Gs2::Showcase::Model::Cache::FDisplayItemCache::TryGet(
                    Self->Gs2->Cache,

                    Self->NamespaceName,
                    Self->AccessToken.IsValid() ? Self->UserId() : TOptional<FString>(),
                    Self->ShowcaseName,
                    Self->DisplayItemId,
                    Self->AccessToken.IsValid() ? Self->AccessToken->GetTimeOffset() : TOptional<int32>(),
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

    TSharedPtr<FAsyncTask<FDisplayItemAccessTokenDomain::FModelTask>> FDisplayItemAccessTokenDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FDisplayItemAccessTokenDomain::FModelTask>>(this->AsShared());
    }

    void FDisplayItemAccessTokenDomain::Invalidate()
    {
        Gs2::Showcase::Model::Cache::FDisplayItemCache::Delete(
            Gs2->Cache,

            NamespaceName,
            AccessToken.IsValid() ? UserId() : TOptional<FString>(),
            ShowcaseName,
            DisplayItemId,
            AccessToken.IsValid() ? AccessToken->GetTimeOffset() : TOptional<int32>()
        );
    }

    FDisplayItemAccessTokenDomain::FSubscribeWithInitialCallTask::FSubscribeWithInitialCallTask(
        const TSharedPtr<FDisplayItemAccessTokenDomain>& Self,
        TFunction<void(Gs2::Showcase::Model::FDisplayItemPtr)> Callback
    ):
        Self(Self),
        Callback(Callback)
    {
    }

    FDisplayItemAccessTokenDomain::FSubscribeWithInitialCallTask::FSubscribeWithInitialCallTask(
        const FSubscribeWithInitialCallTask& From
    ):
        TGs2Future(From),
        Self(From.Self),
        Callback(From.Callback)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FDisplayItemAccessTokenDomain::FSubscribeWithInitialCallTask::Action(
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

    TSharedPtr<FAsyncTask<FDisplayItemAccessTokenDomain::FSubscribeWithInitialCallTask>> FDisplayItemAccessTokenDomain::SubscribeWithInitialCall(
        TFunction<void(Gs2::Showcase::Model::FDisplayItemPtr)> Callback
    )
    {
        return Gs2::Core::Util::New<FAsyncTask<FSubscribeWithInitialCallTask>>(this->AsShared(), Callback);
    }

    Gs2::Core::Domain::CallbackID FDisplayItemAccessTokenDomain::Subscribe(
        TFunction<void(Gs2::Showcase::Model::FDisplayItemPtr)> Callback
    )
    {
        const auto SubscriptionParentKey = Gs2::Showcase::Model::Cache::FDisplayItemCache::CreateCacheParentKey(

            NamespaceName,
            AccessToken.IsValid() ? UserId() : TOptional<FString>(),
            ShowcaseName,
            AccessToken.IsValid() ? AccessToken->GetTimeOffset() : TOptional<int32>()
        );
        const auto SubscriptionCacheKey = Gs2::Showcase::Model::Cache::FDisplayItemCache::CreateCacheKey(

            DisplayItemId
        );
        const TWeakPtr<Gs2::Core::Domain::FGs2> WeakGs2 = Gs2;
        const TWeakPtr<Showcase::Domain::FGs2ShowcaseDomain> WeakService = Service;
        const FString RegisteredParentKey = SubscriptionParentKey;
        const TOptional<FString> QueryNamespaceName = NamespaceName;
        const TOptional<FString> QueryShowcaseName = ShowcaseName;
        const TOptional<FString> QueryDisplayItemId = DisplayItemId;
        const auto SourceToken = AccessToken;
        const TOptional<FString> RegisteredUserId = SourceToken.IsValid()
            ? TOptional<FString>(SourceToken->GetUserId())
            : TOptional<FString>();
        const int32 RegisteredTimeOffset = SourceToken.IsValid() ? SourceToken->GetTimeOffset().Get(0) : 0;
        return Gs2->Cache->Subscribe(
            Gs2::Showcase::Model::FDisplayItem::TypeName,
            SubscriptionParentKey,
            SubscriptionCacheKey,
            [Callback](TSharedPtr<FGs2Object> obj)
            {
                Callback(StaticCastSharedPtr<Gs2::Showcase::Model::FDisplayItem>(obj));
            },
            [WeakGs2, WeakService, RegisteredParentKey, QueryNamespaceName, QueryShowcaseName, QueryDisplayItemId, SourceToken, RegisteredUserId, RegisteredTimeOffset]()
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
                const auto Domain = MakeShared<FDisplayItemAccessTokenDomain>(
                    Owner,
                    WeakService.Pin(),
                    QueryNamespaceName,
                    TokenSnapshot,
                    QueryShowcaseName,
                    QueryDisplayItemId
                );
                Domain->ParentKey = RegisteredParentKey;
                const auto Task = Domain->Model();
                Task->StartBackgroundTask();
            }
        );
    }

    void FDisplayItemAccessTokenDomain::Unsubscribe(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        const auto SubscriptionParentKey = Gs2::Showcase::Model::Cache::FDisplayItemCache::CreateCacheParentKey(

            NamespaceName,
            AccessToken.IsValid() ? UserId() : TOptional<FString>(),
            ShowcaseName,
            AccessToken.IsValid() ? AccessToken->GetTimeOffset() : TOptional<int32>()
        );
        const auto SubscriptionCacheKey = Gs2::Showcase::Model::Cache::FDisplayItemCache::CreateCacheKey(

            DisplayItemId
        );
        Gs2->Cache->Unsubscribe(
            Gs2::Showcase::Model::FDisplayItem::TypeName,
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
