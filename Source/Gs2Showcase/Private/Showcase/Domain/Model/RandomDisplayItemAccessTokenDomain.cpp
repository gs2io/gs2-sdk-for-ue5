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

#include "Showcase/Domain/Model/RandomDisplayItemAccessToken.h"
#include "Showcase/Domain/Model/RandomDisplayItem.h"
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
#include "Showcase/Domain/SpeculativeExecutor/Transaction/RandomShowcaseBuyByUserIdSpeculativeExecutor.h"
#include "Showcase/Model/Cache/RandomDisplayItem.h"

#include "Core/Domain/Gs2.h"
#include "Core/Domain/Transaction/JobQueueJobDomainFactory.h"
#include "Core/Domain/Transaction/InternalTransactionDomainFactory.h"
#include "Core/Domain/Transaction/ManualTransactionAccessTokenDomain.h"

namespace Gs2::Showcase::Domain::Model
{

    FRandomDisplayItemAccessTokenDomain::FRandomDisplayItemAccessTokenDomain(
        const Core::Domain::FGs2Ptr& Gs2,
        const Showcase::Domain::FGs2ShowcaseDomainPtr& Service,
        const TOptional<FString> NamespaceName,
        const Gs2::Auth::Model::FAccessTokenPtr& AccessToken,
        const TOptional<FString> ShowcaseName,
        const TOptional<FString> DisplayItemName
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Gs2(Gs2),
        Service(Service),
        Client(MakeShared<Gs2::Showcase::FGs2ShowcaseRestClient>(Gs2->RestSession)),
        NamespaceName(NamespaceName),
        AccessToken(AccessToken),
        ShowcaseName(ShowcaseName),
        DisplayItemName(DisplayItemName),
        ParentKey(Gs2::Showcase::Domain::Model::FRandomShowcaseDomain::CreateCacheParentKey(
            NamespaceName,
            UserId(),
            ShowcaseName,
            "RandomDisplayItem"
        ))
    {
    }

    FRandomDisplayItemAccessTokenDomain::FRandomDisplayItemAccessTokenDomain(
        const FRandomDisplayItemAccessTokenDomain& From
    ):
        Gs2(From.Gs2),
        Service(From.Service),
        Client(From.Client),
        NamespaceName(From.NamespaceName),
        AccessToken(From.AccessToken),
        ShowcaseName(From.ShowcaseName),
        DisplayItemName(From.DisplayItemName),
        ParentKey(From.ParentKey)
    {

    }

    FRandomDisplayItemAccessTokenDomain::FGetTask::FGetTask(
        const TSharedPtr<FRandomDisplayItemAccessTokenDomain>& Self,
        const Request::FGetRandomDisplayItemRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FRandomDisplayItemAccessTokenDomain::FGetTask::FGetTask(
        const FGetTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FRandomDisplayItemAccessTokenDomain::FGetTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Showcase::Model::FRandomDisplayItem>> Result
    )
    {
        Request
            ->WithContextStack((!Request->GetContextStack().IsSet() || Request->GetContextStack()->IsEmpty()) ? Self->Gs2->DefaultContextStack : Request->GetContextStack())
            ->WithNamespaceName(Self->NamespaceName)
            ->WithShowcaseName(Self->ShowcaseName)
            ->WithDisplayItemName(Self->DisplayItemName)
            ->WithAccessToken(Self->AccessToken->GetToken());
        const auto Future = Self->Client->GetRandomDisplayItem(
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

    TSharedPtr<FAsyncTask<FRandomDisplayItemAccessTokenDomain::FGetTask>> FRandomDisplayItemAccessTokenDomain::Get(
        Request::FGetRandomDisplayItemRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FGetTask>>(this->AsShared(), Request);
    }

    FRandomDisplayItemAccessTokenDomain::FRandomShowcaseBuyTask::FRandomShowcaseBuyTask(
        const TSharedPtr<FRandomDisplayItemAccessTokenDomain>& Self,
        const Request::FRandomShowcaseBuyRequestPtr Request,
        bool SpeculativeExecute
    ): Self(Self), Request(Request), SpeculativeExecute(SpeculativeExecute)
    {

    }

    FRandomDisplayItemAccessTokenDomain::FRandomShowcaseBuyTask::FRandomShowcaseBuyTask(
        const FRandomShowcaseBuyTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request), SpeculativeExecute(From.SpeculativeExecute)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FRandomDisplayItemAccessTokenDomain::FRandomShowcaseBuyTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Core::Domain::FTransactionAccessTokenDomain>> Result
    )
    {
        Request
            ->WithContextStack((!Request->GetContextStack().IsSet() || Request->GetContextStack()->IsEmpty()) ? Self->Gs2->DefaultContextStack : Request->GetContextStack())
            ->WithNamespaceName(Self->NamespaceName)
            ->WithShowcaseName(Self->ShowcaseName)
            ->WithDisplayItemName(Self->DisplayItemName)
            ->WithAccessToken(Self->AccessToken->GetToken());
        const auto Future = Self->Client->RandomShowcaseBuy(
            Request
        );
        Future->StartSynchronousTask();
        if (Future->GetTask().IsError())
        {
            return Future->GetTask().Error();
        }
        const auto ResultModel = Future->GetTask().Result();
        Future->EnsureCompletion();

        Self->Gs2->Cache->ClearListCache(
            Gs2::Showcase::Model::FRandomDisplayItem::TypeName,
            Gs2::Showcase::Model::Cache::FRandomDisplayItemCache::CreateCacheParentKey(
                Self->NamespaceName,
                Self->UserId(),
                Self->ShowcaseName,
                Self->AccessToken.IsValid() ? Self->AccessToken->GetTimeOffset() : TOptional<int32>()
            )
        );

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

    TSharedPtr<FAsyncTask<FRandomDisplayItemAccessTokenDomain::FRandomShowcaseBuyTask>> FRandomDisplayItemAccessTokenDomain::RandomShowcaseBuy(
        Request::FRandomShowcaseBuyRequestPtr Request,
        bool SpeculativeExecute
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FRandomShowcaseBuyTask>>(this->AsShared(), Request, SpeculativeExecute);
    }

    FString FRandomDisplayItemAccessTokenDomain::CreateCacheParentKey(
        TOptional<FString> NamespaceName,
        TOptional<FString> UserId,
        TOptional<FString> ShowcaseName,
        TOptional<FString> DisplayItemName,
        FString ChildType
    )
    {
        return FString("") +
            (NamespaceName.IsSet() ? *NamespaceName : "null") + ":" +
            (UserId.IsSet() ? *UserId : "null") + ":" +
            (ShowcaseName.IsSet() ? *ShowcaseName : "null") + ":" +
            (DisplayItemName.IsSet() ? *DisplayItemName : "null") + ":" +
            ChildType;
    }

    FString FRandomDisplayItemAccessTokenDomain::CreateCacheKey(
        TOptional<FString> DisplayItemName
    )
    {
        return FString("") +
            (DisplayItemName.IsSet() ? *DisplayItemName : "null");
    }

    FRandomDisplayItemAccessTokenDomain::FModelTask::FModelTask(
        const TSharedPtr<FRandomDisplayItemAccessTokenDomain> Self
    ): Self(Self)
    {

    }

    FRandomDisplayItemAccessTokenDomain::FModelTask::FModelTask(
        const FModelTask& From
    ): TGs2Future(From), Self(From.Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FRandomDisplayItemAccessTokenDomain::FModelTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Showcase::Model::FRandomDisplayItem>> Result
    )
    {
        const auto CacheParentKey = Gs2::Showcase::Model::Cache::FRandomDisplayItemCache::CreateCacheParentKey(

            Self->NamespaceName,
            Self->AccessToken.IsValid() ? Self->UserId() : TOptional<FString>(),
            Self->ShowcaseName,
            Self->AccessToken.IsValid() ? Self->AccessToken->GetTimeOffset() : TOptional<int32>()
        );
        const auto CacheKey = Gs2::Showcase::Model::Cache::FRandomDisplayItemCache::CreateCacheKey(

            Self->DisplayItemName
        );
        return Self->Gs2->Cache->ExecuteWithKeyLock(
            Gs2::Showcase::Model::FRandomDisplayItem::TypeName,
            CacheParentKey,
            CacheKey,
            [Self = Self, Result]() -> Gs2::Core::Model::FGs2ErrorPtr
            {
                Gs2::Showcase::Model::FRandomDisplayItemPtr Value;
                const auto CacheHit = Gs2::Showcase::Model::Cache::FRandomDisplayItemCache::TryGet(
                    Self->Gs2->Cache,

                    Self->NamespaceName,
                    Self->AccessToken.IsValid() ? Self->UserId() : TOptional<FString>(),
                    Self->ShowcaseName,
                    Self->DisplayItemName,
                    Self->AccessToken.IsValid() ? Self->AccessToken->GetTimeOffset() : TOptional<int32>(),
                    &Value
                );
                if (CacheHit)
                {
                    *Result = Value;
                    return nullptr;
                }
                const auto Error = Gs2::Showcase::Model::Cache::FRandomDisplayItemCache::Fetch(
                    Self->Gs2->Cache,

                    Self->NamespaceName,
                    Self->AccessToken.IsValid() ? Self->UserId() : TOptional<FString>(),
                    Self->ShowcaseName,
                    Self->DisplayItemName,
                    Self->AccessToken.IsValid() ? Self->AccessToken->GetTimeOffset() : TOptional<int32>(),
                    [Self](Gs2::Showcase::Model::FRandomDisplayItemPtr* OutItem) -> Gs2::Core::Model::FGs2ErrorPtr
                    {
                        const auto Future = Self->Get(
                            MakeShared<Gs2::Showcase::Request::FGetRandomDisplayItemRequest>()
                        );
                        Future->StartSynchronousTask();
                        if (Future->GetTask().IsError()) return Future->GetTask().Error();
                        *OutItem = Future->GetTask().Result();
                        Future->EnsureCompletion();
                        return nullptr;
                    },
                    &Value
                );
                if (Error.IsValid()) return Error;
                *Result = Value;
                return nullptr;
            }
        );
    }

    TSharedPtr<FAsyncTask<FRandomDisplayItemAccessTokenDomain::FModelTask>> FRandomDisplayItemAccessTokenDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FRandomDisplayItemAccessTokenDomain::FModelTask>>(this->AsShared());
    }

    void FRandomDisplayItemAccessTokenDomain::Invalidate()
    {
        Gs2::Showcase::Model::Cache::FRandomDisplayItemCache::Delete(
            Gs2->Cache,

            NamespaceName,
            AccessToken.IsValid() ? UserId() : TOptional<FString>(),
            ShowcaseName,
            DisplayItemName,
            AccessToken.IsValid() ? AccessToken->GetTimeOffset() : TOptional<int32>()
        );
    }

    FRandomDisplayItemAccessTokenDomain::FSubscribeWithInitialCallTask::FSubscribeWithInitialCallTask(
        const TSharedPtr<FRandomDisplayItemAccessTokenDomain>& Self,
        TFunction<void(Gs2::Showcase::Model::FRandomDisplayItemPtr)> Callback
    ):
        Self(Self),
        Callback(Callback)
    {
    }

    FRandomDisplayItemAccessTokenDomain::FSubscribeWithInitialCallTask::FSubscribeWithInitialCallTask(
        const FSubscribeWithInitialCallTask& From
    ):
        TGs2Future(From),
        Self(From.Self),
        Callback(From.Callback)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FRandomDisplayItemAccessTokenDomain::FSubscribeWithInitialCallTask::Action(
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

    TSharedPtr<FAsyncTask<FRandomDisplayItemAccessTokenDomain::FSubscribeWithInitialCallTask>> FRandomDisplayItemAccessTokenDomain::SubscribeWithInitialCall(
        TFunction<void(Gs2::Showcase::Model::FRandomDisplayItemPtr)> Callback
    )
    {
        return Gs2::Core::Util::New<FAsyncTask<FSubscribeWithInitialCallTask>>(this->AsShared(), Callback);
    }

    Gs2::Core::Domain::CallbackID FRandomDisplayItemAccessTokenDomain::Subscribe(
        TFunction<void(Gs2::Showcase::Model::FRandomDisplayItemPtr)> Callback
    )
    {
        const auto SubscriptionParentKey = Gs2::Showcase::Model::Cache::FRandomDisplayItemCache::CreateCacheParentKey(

            NamespaceName,
            AccessToken.IsValid() ? UserId() : TOptional<FString>(),
            ShowcaseName,
            AccessToken.IsValid() ? AccessToken->GetTimeOffset() : TOptional<int32>()
        );
        const auto SubscriptionCacheKey = Gs2::Showcase::Model::Cache::FRandomDisplayItemCache::CreateCacheKey(

            DisplayItemName
        );
        const TWeakPtr<Gs2::Core::Domain::FGs2> WeakGs2 = Gs2;
        const TWeakPtr<Showcase::Domain::FGs2ShowcaseDomain> WeakService = Service;
        const FString RegisteredParentKey = SubscriptionParentKey;
        const TOptional<FString> QueryNamespaceName = NamespaceName;
        const TOptional<FString> QueryShowcaseName = ShowcaseName;
        const TOptional<FString> QueryDisplayItemName = DisplayItemName;
        const auto SourceToken = AccessToken;
        const TOptional<FString> RegisteredUserId = SourceToken.IsValid()
            ? TOptional<FString>(SourceToken->GetUserId())
            : TOptional<FString>();
        const int32 RegisteredTimeOffset = SourceToken.IsValid() ? SourceToken->GetTimeOffset().Get(0) : 0;
        return Gs2->Cache->Subscribe(
            Gs2::Showcase::Model::FRandomDisplayItem::TypeName,
            SubscriptionParentKey,
            SubscriptionCacheKey,
            [Callback](TSharedPtr<FGs2Object> obj)
            {
                Callback(StaticCastSharedPtr<Gs2::Showcase::Model::FRandomDisplayItem>(obj));
            },
            [WeakGs2, WeakService, RegisteredParentKey, QueryNamespaceName, QueryShowcaseName, QueryDisplayItemName, SourceToken, RegisteredUserId, RegisteredTimeOffset]()
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
                const auto Domain = MakeShared<FRandomDisplayItemAccessTokenDomain>(
                    Owner,
                    WeakService.Pin(),
                    QueryNamespaceName,
                    TokenSnapshot,
                    QueryShowcaseName,
                    QueryDisplayItemName
                );
                Domain->ParentKey = RegisteredParentKey;
                const auto Task = Domain->Model();
                Task->StartBackgroundTask();
            }
        );
    }

    void FRandomDisplayItemAccessTokenDomain::Unsubscribe(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        const auto SubscriptionParentKey = Gs2::Showcase::Model::Cache::FRandomDisplayItemCache::CreateCacheParentKey(

            NamespaceName,
            AccessToken.IsValid() ? UserId() : TOptional<FString>(),
            ShowcaseName,
            AccessToken.IsValid() ? AccessToken->GetTimeOffset() : TOptional<int32>()
        );
        const auto SubscriptionCacheKey = Gs2::Showcase::Model::Cache::FRandomDisplayItemCache::CreateCacheKey(

            DisplayItemName
        );
        Gs2->Cache->Unsubscribe(
            Gs2::Showcase::Model::FRandomDisplayItem::TypeName,
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
