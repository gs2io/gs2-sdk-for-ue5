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
#include "Showcase/Model/Cache/RandomDisplayItem.h"

#include "Core/Domain/Gs2.h"
#include "Core/Domain/Transaction/JobQueueJobDomainFactory.h"
#include "Core/Domain/Transaction/InternalTransactionDomainFactory.h"
#include "Core/Domain/Transaction/ManualTransactionDomain.h"

namespace Gs2::Showcase::Domain::Model
{

    FRandomDisplayItemDomain::FRandomDisplayItemDomain(
        const Core::Domain::FGs2Ptr& Gs2,
        const Showcase::Domain::FGs2ShowcaseDomainPtr& Service,
        const TOptional<FString> NamespaceName,
        const TOptional<FString> UserId,
        const TOptional<FString> ShowcaseName,
        const TOptional<FString> DisplayItemName
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Gs2(Gs2),
        Service(Service),
        Client(MakeShared<Gs2::Showcase::FGs2ShowcaseRestClient>(Gs2->RestSession)),
        NamespaceName(NamespaceName),
        UserId(UserId),
        ShowcaseName(ShowcaseName),
        DisplayItemName(DisplayItemName),
        ParentKey(Gs2::Showcase::Domain::Model::FRandomShowcaseDomain::CreateCacheParentKey(
            NamespaceName,
            UserId,
            ShowcaseName,
            "RandomDisplayItem"
        ))
    {
    }

    FRandomDisplayItemDomain::FRandomDisplayItemDomain(
        const FRandomDisplayItemDomain& From
    ):
        Gs2(From.Gs2),
        Service(From.Service),
        Client(From.Client),
        NamespaceName(From.NamespaceName),
        UserId(From.UserId),
        ShowcaseName(From.ShowcaseName),
        DisplayItemName(From.DisplayItemName),
        ParentKey(From.ParentKey)
    {

    }

    FRandomDisplayItemDomain::FGetTask::FGetTask(
        const TSharedPtr<FRandomDisplayItemDomain>& Self,
        const Request::FGetRandomDisplayItemByUserIdRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FRandomDisplayItemDomain::FGetTask::FGetTask(
        const FGetTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FRandomDisplayItemDomain::FGetTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Showcase::Model::FRandomDisplayItem>> Result
    )
    {
        Request
            ->WithContextStack((!Request->GetContextStack().IsSet() || Request->GetContextStack()->IsEmpty()) ? Self->Gs2->DefaultContextStack : Request->GetContextStack())
            ->WithNamespaceName(Self->NamespaceName)
            ->WithShowcaseName(Self->ShowcaseName)
            ->WithDisplayItemName(Self->DisplayItemName)
            ->WithUserId(Self->UserId);
        const auto Future = Self->Client->GetRandomDisplayItemByUserId(
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

    TSharedPtr<FAsyncTask<FRandomDisplayItemDomain::FGetTask>> FRandomDisplayItemDomain::Get(
        Request::FGetRandomDisplayItemByUserIdRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FGetTask>>(this->AsShared(), Request);
    }

    FRandomDisplayItemDomain::FRandomShowcaseBuyTask::FRandomShowcaseBuyTask(
        const TSharedPtr<FRandomDisplayItemDomain>& Self,
        const Request::FRandomShowcaseBuyByUserIdRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FRandomDisplayItemDomain::FRandomShowcaseBuyTask::FRandomShowcaseBuyTask(
        const FRandomShowcaseBuyTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FRandomDisplayItemDomain::FRandomShowcaseBuyTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Core::Domain::FTransactionDomain>> Result
    )
    {
        Request
            ->WithContextStack((!Request->GetContextStack().IsSet() || Request->GetContextStack()->IsEmpty()) ? Self->Gs2->DefaultContextStack : Request->GetContextStack())
            ->WithNamespaceName(Self->NamespaceName)
            ->WithShowcaseName(Self->ShowcaseName)
            ->WithDisplayItemName(Self->DisplayItemName)
            ->WithUserId(Self->UserId);
        const auto Future = Self->Client->RandomShowcaseBuyByUserId(
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
                Self->UserId,
                Self->ShowcaseName,
                TOptional<int32>()
            )
        );

        const auto Transaction = Gs2::Core::Domain::Internal::FTransactionDomainFactory::ToTransaction(
            Self->Gs2,
            *Self->UserId,
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

    TSharedPtr<FAsyncTask<FRandomDisplayItemDomain::FRandomShowcaseBuyTask>> FRandomDisplayItemDomain::RandomShowcaseBuy(
        Request::FRandomShowcaseBuyByUserIdRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FRandomShowcaseBuyTask>>(this->AsShared(), Request);
    }

    FString FRandomDisplayItemDomain::CreateCacheParentKey(
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

    FString FRandomDisplayItemDomain::CreateCacheKey(
        TOptional<FString> DisplayItemName
    )
    {
        return FString("") +
            (DisplayItemName.IsSet() ? *DisplayItemName : "null");
    }

    FRandomDisplayItemDomain::FModelTask::FModelTask(
        const TSharedPtr<FRandomDisplayItemDomain> Self
    ): Self(Self)
    {

    }

    FRandomDisplayItemDomain::FModelTask::FModelTask(
        const FModelTask& From
    ): TGs2Future(From), Self(From.Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FRandomDisplayItemDomain::FModelTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Showcase::Model::FRandomDisplayItem>> Result
    )
    {
        const auto CacheParentKey = Gs2::Showcase::Model::Cache::FRandomDisplayItemCache::CreateCacheParentKey(

            Self->NamespaceName,
            Self->UserId,
            Self->ShowcaseName,
            TOptional<int32>()
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
                    Self->UserId,
                    Self->ShowcaseName,
                    Self->DisplayItemName,
                    TOptional<int32>(),
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
                    Self->UserId,
                    Self->ShowcaseName,
                    Self->DisplayItemName,
                    TOptional<int32>(),
                    [Self](Gs2::Showcase::Model::FRandomDisplayItemPtr* OutItem) -> Gs2::Core::Model::FGs2ErrorPtr
                    {
                        const auto Future = Self->Get(
                            MakeShared<Gs2::Showcase::Request::FGetRandomDisplayItemByUserIdRequest>()
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

    TSharedPtr<FAsyncTask<FRandomDisplayItemDomain::FModelTask>> FRandomDisplayItemDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FRandomDisplayItemDomain::FModelTask>>(this->AsShared());
    }

    void FRandomDisplayItemDomain::Invalidate()
    {
        Gs2::Showcase::Model::Cache::FRandomDisplayItemCache::Delete(
            Gs2->Cache,

            NamespaceName,
            UserId,
            ShowcaseName,
            DisplayItemName,
            TOptional<int32>()
        );
    }

    FRandomDisplayItemDomain::FSubscribeWithInitialCallTask::FSubscribeWithInitialCallTask(
        const TSharedPtr<FRandomDisplayItemDomain>& Self,
        TFunction<void(Gs2::Showcase::Model::FRandomDisplayItemPtr)> Callback
    ):
        Self(Self),
        Callback(Callback)
    {
    }

    FRandomDisplayItemDomain::FSubscribeWithInitialCallTask::FSubscribeWithInitialCallTask(
        const FSubscribeWithInitialCallTask& From
    ):
        TGs2Future(From),
        Self(From.Self),
        Callback(From.Callback)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FRandomDisplayItemDomain::FSubscribeWithInitialCallTask::Action(
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

    TSharedPtr<FAsyncTask<FRandomDisplayItemDomain::FSubscribeWithInitialCallTask>> FRandomDisplayItemDomain::SubscribeWithInitialCall(
        TFunction<void(Gs2::Showcase::Model::FRandomDisplayItemPtr)> Callback
    )
    {
        return Gs2::Core::Util::New<FAsyncTask<FSubscribeWithInitialCallTask>>(this->AsShared(), Callback);
    }

    Gs2::Core::Domain::CallbackID FRandomDisplayItemDomain::Subscribe(
        TFunction<void(Gs2::Showcase::Model::FRandomDisplayItemPtr)> Callback
    )
    {
        const auto SubscriptionParentKey = Gs2::Showcase::Model::Cache::FRandomDisplayItemCache::CreateCacheParentKey(

            NamespaceName,
            UserId,
            ShowcaseName,
            TOptional<int32>()
        );
        const auto SubscriptionCacheKey = Gs2::Showcase::Model::Cache::FRandomDisplayItemCache::CreateCacheKey(

            DisplayItemName
        );
        const TWeakPtr<Gs2::Core::Domain::FGs2> WeakGs2 = Gs2;
        const TWeakPtr<Showcase::Domain::FGs2ShowcaseDomain> WeakService = Service;
        const FString RegisteredParentKey = SubscriptionParentKey;
        const TOptional<FString> QueryNamespaceName = NamespaceName;
        const TOptional<FString> QueryUserId = UserId;
        const TOptional<FString> QueryShowcaseName = ShowcaseName;
        const TOptional<FString> QueryDisplayItemName = DisplayItemName;
        return Gs2->Cache->Subscribe(
            Gs2::Showcase::Model::FRandomDisplayItem::TypeName,
            SubscriptionParentKey,
            SubscriptionCacheKey,
            [Callback](TSharedPtr<FGs2Object> obj)
            {
                Callback(StaticCastSharedPtr<Gs2::Showcase::Model::FRandomDisplayItem>(obj));
            },
            [WeakGs2, WeakService, RegisteredParentKey, QueryNamespaceName, QueryUserId, QueryShowcaseName, QueryDisplayItemName]()
            {
                const auto Owner = WeakGs2.Pin();
                if (!Owner.IsValid())
                {
                    return;
                }
                const auto Domain = MakeShared<FRandomDisplayItemDomain>(
                    Owner,
                    WeakService.Pin(),
                    QueryNamespaceName,
                    QueryUserId,
                    QueryShowcaseName,
                    QueryDisplayItemName
                );
                Domain->ParentKey = RegisteredParentKey;
                const auto Task = Domain->Model();
                Task->StartBackgroundTask();
            }
        );
    }

    void FRandomDisplayItemDomain::Unsubscribe(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        const auto SubscriptionParentKey = Gs2::Showcase::Model::Cache::FRandomDisplayItemCache::CreateCacheParentKey(

            NamespaceName,
            UserId,
            ShowcaseName,
            TOptional<int32>()
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
