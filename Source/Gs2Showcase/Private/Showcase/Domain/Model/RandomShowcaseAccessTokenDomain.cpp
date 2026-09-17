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

#include "Showcase/Domain/Model/RandomShowcaseAccessToken.h"
#include "Showcase/Domain/Model/RandomShowcase.h"
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
#include "Showcase/Model/Cache/RandomShowcase.h"
#include "Showcase/Model/Cache/RandomDisplayItem.h"

#include "Core/Domain/Gs2.h"
#include "Core/Domain/Transaction/JobQueueJobDomainFactory.h"
#include "Core/Domain/Transaction/InternalTransactionDomainFactory.h"
#include "Core/Domain/Transaction/ManualTransactionAccessTokenDomain.h"

namespace Gs2::Showcase::Domain::Model
{

    FRandomShowcaseAccessTokenDomain::FRandomShowcaseAccessTokenDomain(
        const Core::Domain::FGs2Ptr& Gs2,
        const Showcase::Domain::FGs2ShowcaseDomainPtr& Service,
        const TOptional<FString> NamespaceName,
        const Gs2::Auth::Model::FAccessTokenPtr& AccessToken,
        const TOptional<FString> ShowcaseName
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Gs2(Gs2),
        Service(Service),
        Client(MakeShared<Gs2::Showcase::FGs2ShowcaseRestClient>(Gs2->RestSession)),
        NamespaceName(NamespaceName),
        AccessToken(AccessToken),
        ShowcaseName(ShowcaseName),
        ParentKey(Gs2::Showcase::Model::Cache::FRandomShowcaseCache::CreateCacheParentKey(
            NamespaceName,
            UserId(),
            AccessToken.IsValid() ? AccessToken->GetTimeOffset() : TOptional<int32>()
        ))
    {
    }

    FRandomShowcaseAccessTokenDomain::FRandomShowcaseAccessTokenDomain(
        const FRandomShowcaseAccessTokenDomain& From
    ):
        Gs2(From.Gs2),
        Service(From.Service),
        Client(From.Client),
        NamespaceName(From.NamespaceName),
        AccessToken(From.AccessToken),
        ShowcaseName(From.ShowcaseName),
        ParentKey(From.ParentKey)
    {

    }

    Gs2::Showcase::Domain::Iterator::FDescribeRandomDisplayItemsIteratorPtr FRandomShowcaseAccessTokenDomain::RandomDisplayItems(
    ) const
    {
        return MakeShared<Gs2::Showcase::Domain::Iterator::FDescribeRandomDisplayItemsIterator>(
            Gs2,
            Client,
            NamespaceName,
            ShowcaseName,
            AccessToken
        );
    }

    Gs2::Core::Domain::CallbackID FRandomShowcaseAccessTokenDomain::SubscribeRandomDisplayItems(
    TFunction<void()> Callback

    )
    {
        return Gs2->Cache->ListSubscribe(
            Gs2::Showcase::Model::FRandomDisplayItem::TypeName,
            Gs2::Showcase::Model::Cache::FRandomDisplayItemCache::CreateCacheParentKey(
                NamespaceName,
                AccessToken.IsValid() ? AccessToken->GetUserId() : TOptional<FString>(),
                ShowcaseName,
                AccessToken.IsValid() ? AccessToken->GetTimeOffset() : TOptional<int32>()
            ),
            Callback,
            Callback
        );
    }
    void FRandomShowcaseAccessTokenDomain::UnsubscribeRandomDisplayItems(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        Gs2->Cache->ListUnsubscribe(
            Gs2::Showcase::Model::FRandomDisplayItem::TypeName,
            Gs2::Showcase::Model::Cache::FRandomDisplayItemCache::CreateCacheParentKey(
                NamespaceName,
                AccessToken.IsValid() ? AccessToken->GetUserId() : TOptional<FString>(),
                ShowcaseName,
                AccessToken.IsValid() ? AccessToken->GetTimeOffset() : TOptional<int32>()
            ),
            CallbackID
        );
    }
    class FRandomShowcaseAccessTokenDomain::FCollectRandomDisplayItemsTask : public Gs2::Core::Util::TGs2Future<TArray<Gs2::Showcase::Model::FRandomDisplayItemPtr>>, public TSharedFromThis<FCollectRandomDisplayItemsTask>
    {
        const TSharedPtr<FRandomShowcaseAccessTokenDomain> Self;
        const TFunction<void(TArray<Gs2::Showcase::Model::FRandomDisplayItemPtr>)> OnCollected;

    public:
        explicit FCollectRandomDisplayItemsTask(const TSharedPtr<FRandomShowcaseAccessTokenDomain>& Self, TFunction<void(TArray<Gs2::Showcase::Model::FRandomDisplayItemPtr>)> OnCollected) : Self(Self), OnCollected(OnCollected) {}
        FCollectRandomDisplayItemsTask(const FCollectRandomDisplayItemsTask& From) : TGs2Future(From), Self(From.Self), OnCollected(From.OnCollected) {}
        virtual Gs2::Core::Model::FGs2ErrorPtr Action(TSharedPtr<TSharedPtr<TArray<Gs2::Showcase::Model::FRandomDisplayItemPtr>>> Result) override
        {
            TArray<Gs2::Showcase::Model::FRandomDisplayItemPtr> Items;
            auto Iterator = Self->RandomDisplayItems()->begin();
            while (Iterator.HasNext())
            {
                if (Iterator.IsError()) return Iterator.Error();
                if (Iterator.IsCurrentValid()) Items.Add(Iterator.Current());
                ++Iterator;
            }
            if (Iterator.IsError()) return Iterator.Error();
            *Result = MakeShared<TArray<Gs2::Showcase::Model::FRandomDisplayItemPtr>>(Items);
            if (OnCollected) OnCollected(Items);
            return nullptr;
        }
    };

    Gs2::Core::Domain::CallbackID FRandomShowcaseAccessTokenDomain::SubscribeRandomDisplayItems(
        TFunction<void(TArray<Gs2::Showcase::Model::FRandomDisplayItemPtr>)> Callback
    )
    {
        const TWeakPtr<Gs2::Core::Domain::FGs2> WeakGs2 = this->Gs2;
        const TWeakPtr<Showcase::Domain::FGs2ShowcaseDomain> WeakService = this->Service;
        const auto SourceToken = this->AccessToken;
        const TOptional<FString> RegisteredUserId = SourceToken.IsValid() ? TOptional<FString>(SourceToken->GetUserId()) : TOptional<FString>();
        const int32 RegisteredTimeOffset = SourceToken.IsValid() ? SourceToken->GetTimeOffset().Get(0) : 0;
        const auto QueryNamespaceName = NamespaceName;
        const auto QueryShowcaseName = ShowcaseName;
        const auto Parent = Gs2::Showcase::Model::Cache::FRandomDisplayItemCache::CreateCacheParentKey(
        NamespaceName,
        AccessToken.IsValid() ? AccessToken->GetUserId() : TOptional<FString>(),
        ShowcaseName,
        AccessToken.IsValid() ? AccessToken->GetTimeOffset() : TOptional<int32>()
    );
        return Gs2->Cache->ListSubscribeTyped(
            Gs2::Showcase::Model::FRandomDisplayItem::TypeName,
            Parent,
            [Callback, WeakGs2](const TArray<FGs2ObjectPtr>& Values)
            {
                if (!WeakGs2.Pin().IsValid()) return;
                TArray<Gs2::Showcase::Model::FRandomDisplayItemPtr> TypedValues;
                for (const auto& Value : Values) if (Value.IsValid()) TypedValues.Add(StaticCastSharedPtr<Gs2::Showcase::Model::FRandomDisplayItem>(Value));
                Callback(TypedValues);
            },
            [WeakGs2, WeakService, Callback, QueryNamespaceName, QueryShowcaseName, SourceToken, RegisteredUserId, RegisteredTimeOffset]()
            {
                const auto Owner = WeakGs2.Pin();
                if (!Owner.IsValid() || !SourceToken.IsValid() || !RegisteredUserId.IsSet()) return;
                const auto TokenSnapshot = MakeShared<Gs2::Auth::Model::FAccessToken>(*SourceToken);
                if (TokenSnapshot->GetUserId() != RegisteredUserId || TokenSnapshot->GetTimeOffset().Get(0) != RegisteredTimeOffset) return;
                const auto Domain = MakeShared<FRandomShowcaseAccessTokenDomain>(Owner, WeakService.Pin(), QueryNamespaceName, TokenSnapshot, QueryShowcaseName);
                const auto Task = Gs2::Core::Util::New<FAsyncTask<FCollectRandomDisplayItemsTask>>(Domain, Callback);
                Task->StartBackgroundTask();
            }
        );
    }

    void FRandomShowcaseAccessTokenDomain::InvalidateRandomDisplayItems()
    {
        Gs2->Cache->ClearListCache(
            Gs2::Showcase::Model::FRandomDisplayItem::TypeName,
            Gs2::Showcase::Model::Cache::FRandomDisplayItemCache::CreateCacheParentKey(
        NamespaceName,
        AccessToken.IsValid() ? AccessToken->GetUserId() : TOptional<FString>(),
        ShowcaseName,
        AccessToken.IsValid() ? AccessToken->GetTimeOffset() : TOptional<int32>()
    )
        );
    }

    FRandomShowcaseAccessTokenDomain::FSubscribeRandomDisplayItemsWithInitialCallTask::FSubscribeRandomDisplayItemsWithInitialCallTask(const TSharedPtr<FRandomShowcaseAccessTokenDomain>& Self, TFunction<void(TArray<Gs2::Showcase::Model::FRandomDisplayItemPtr>)> Callback) : Self(Self), Callback(Callback) {}
    FRandomShowcaseAccessTokenDomain::FSubscribeRandomDisplayItemsWithInitialCallTask::FSubscribeRandomDisplayItemsWithInitialCallTask(const FSubscribeRandomDisplayItemsWithInitialCallTask& From) : TGs2Future(From), Self(From.Self), Callback(From.Callback) {}
    Gs2::Core::Model::FGs2ErrorPtr FRandomShowcaseAccessTokenDomain::FSubscribeRandomDisplayItemsWithInitialCallTask::Action(TSharedPtr<TSharedPtr<Gs2::Core::Domain::CallbackID>> Result)
    {
        const auto Task = Gs2::Core::Util::New<FAsyncTask<FCollectRandomDisplayItemsTask>>(Self, TFunction<void(TArray<Gs2::Showcase::Model::FRandomDisplayItemPtr>)>());
        Task->StartSynchronousTask(); Task->EnsureCompletion();
        if (Task->GetTask().IsError()) return Task->GetTask().Error();
        const auto Values = Task->GetTask().Result();
        const auto CallbackId = Self->SubscribeRandomDisplayItems(Callback);
        Callback(*Values); *Result = MakeShared<Gs2::Core::Domain::CallbackID>(CallbackId);
        return nullptr;
    }
    TSharedPtr<FAsyncTask<FRandomShowcaseAccessTokenDomain::FSubscribeRandomDisplayItemsWithInitialCallTask>> FRandomShowcaseAccessTokenDomain::SubscribeRandomDisplayItemsWithInitialCall(TFunction<void(TArray<Gs2::Showcase::Model::FRandomDisplayItemPtr>)> Callback)
    {
        return Gs2::Core::Util::New<FAsyncTask<FSubscribeRandomDisplayItemsWithInitialCallTask>>(this->AsShared(), Callback);
    }

    TSharedPtr<Gs2::Showcase::Domain::Model::FRandomDisplayItemAccessTokenDomain> FRandomShowcaseAccessTokenDomain::RandomDisplayItem(
        const FString DisplayItemName
    )
    {
        return MakeShared<Gs2::Showcase::Domain::Model::FRandomDisplayItemAccessTokenDomain>(
            Gs2,
            Service,
            NamespaceName,
            AccessToken,
            ShowcaseName,
            DisplayItemName == TEXT("") ? TOptional<FString>() : TOptional<FString>(DisplayItemName)
        );
    }

    FString FRandomShowcaseAccessTokenDomain::CreateCacheParentKey(
        TOptional<FString> NamespaceName,
        TOptional<FString> UserId,
        TOptional<FString> ShowcaseName,
        FString ChildType
    )
    {
        return FString("") +
            (NamespaceName.IsSet() ? *NamespaceName : "null") + ":" +
            (UserId.IsSet() ? *UserId : "null") + ":" +
            (ShowcaseName.IsSet() ? *ShowcaseName : "null") + ":" +
            ChildType;
    }

    FString FRandomShowcaseAccessTokenDomain::CreateCacheKey(
        TOptional<FString> ShowcaseName
    )
    {
        return FString("") +
            (ShowcaseName.IsSet() ? *ShowcaseName : "null");
    }

    FRandomShowcaseAccessTokenDomain::FModelTask::FModelTask(
        const TSharedPtr<FRandomShowcaseAccessTokenDomain> Self
    ): Self(Self)
    {

    }

    FRandomShowcaseAccessTokenDomain::FModelTask::FModelTask(
        const FModelTask& From
    ): TGs2Future(From), Self(From.Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FRandomShowcaseAccessTokenDomain::FModelTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Showcase::Model::FRandomShowcase>> Result
    )
    {
        const FString CacheKey = Gs2::Showcase::Model::Cache::FRandomShowcaseCache::CreateCacheKey(
            Self->ShowcaseName
        );
        return Self->Gs2->Cache->ExecuteWithKeyLock(
            Gs2::Showcase::Model::FRandomShowcase::TypeName,
            Self->ParentKey,
            CacheKey,
            [this, Result, CacheKey]() -> Gs2::Core::Model::FGs2ErrorPtr
            {
                // ReSharper disable once CppLocalVariableMayBeConst
                TSharedPtr<Gs2::Showcase::Model::FRandomShowcase> Value;
                auto bCacheHit = Self->Gs2->Cache->TryGet<Gs2::Showcase::Model::FRandomShowcase>(
                    Self->ParentKey,
                    CacheKey,
                    &Value
                );
                *Result = Value;

                return nullptr;
            }
        );
    }

    TSharedPtr<FAsyncTask<FRandomShowcaseAccessTokenDomain::FModelTask>> FRandomShowcaseAccessTokenDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FRandomShowcaseAccessTokenDomain::FModelTask>>(this->AsShared());
    }


    FRandomShowcaseAccessTokenDomain::FSubscribeWithInitialCallTask::FSubscribeWithInitialCallTask(
        const TSharedPtr<FRandomShowcaseAccessTokenDomain> Self,
        const TFunction<void(Gs2::Showcase::Model::FRandomShowcasePtr)> Callback
    ): Self(Self), Callback(Callback)
    {
    }

    FRandomShowcaseAccessTokenDomain::FSubscribeWithInitialCallTask::FSubscribeWithInitialCallTask(
        const FSubscribeWithInitialCallTask& From
    ): TGs2Future(From), Self(From.Self), Callback(From.Callback)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FRandomShowcaseAccessTokenDomain::FSubscribeWithInitialCallTask::Action(
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

    TSharedPtr<FAsyncTask<FRandomShowcaseAccessTokenDomain::FSubscribeWithInitialCallTask>> FRandomShowcaseAccessTokenDomain::SubscribeWithInitialCall(
        TFunction<void(Gs2::Showcase::Model::FRandomShowcasePtr)> Callback
    )
    {
        return Gs2::Core::Util::New<FAsyncTask<FRandomShowcaseAccessTokenDomain::FSubscribeWithInitialCallTask>>(this->AsShared(), Callback);
    }

    void FRandomShowcaseAccessTokenDomain::Invalidate()
    {
        Gs2::Showcase::Model::Cache::FRandomShowcaseCache::Delete(
            Gs2->Cache,
            NamespaceName,
            AccessToken.IsValid() ? UserId() : TOptional<FString>(),
            ShowcaseName,
            AccessToken.IsValid() ? AccessToken->GetTimeOffset() : TOptional<int32>()
        );
    }

    Gs2::Core::Domain::CallbackID FRandomShowcaseAccessTokenDomain::Subscribe(
        TFunction<void(Gs2::Showcase::Model::FRandomShowcasePtr)> Callback
    )
    {
        const TWeakPtr<Gs2::Core::Domain::FGs2> WeakGs2 = Gs2;
        const TWeakPtr<Showcase::Domain::FGs2ShowcaseDomain> WeakService = Service;
        const FString RegisteredParentKey = ParentKey;
        const TOptional<FString> QueryNamespaceName = NamespaceName;
        const TOptional<FString> QueryShowcaseName = ShowcaseName;
        const auto SourceToken = AccessToken;
        const TOptional<FString> RegisteredUserId = SourceToken.IsValid()
            ? TOptional<FString>(SourceToken->GetUserId())
            : TOptional<FString>();
        const int32 RegisteredTimeOffset = SourceToken.IsValid() ? SourceToken->GetTimeOffset().Get(0) : 0;
        return Gs2->Cache->Subscribe(
            Gs2::Showcase::Model::FRandomShowcase::TypeName,
            ParentKey,
            Gs2::Showcase::Model::Cache::FRandomShowcaseCache::CreateCacheKey(
                ShowcaseName
            ),
            [Callback](TSharedPtr<FGs2Object> obj)
            {
                Callback(StaticCastSharedPtr<Gs2::Showcase::Model::FRandomShowcase>(obj));
            },
            [WeakGs2, WeakService, RegisteredParentKey, QueryNamespaceName, QueryShowcaseName, SourceToken, RegisteredUserId, RegisteredTimeOffset]()
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
                const auto Domain = MakeShared<FRandomShowcaseAccessTokenDomain>(
                    Owner,
                    WeakService.Pin(),
                    QueryNamespaceName,
                    TokenSnapshot,
                    QueryShowcaseName
                );
                Domain->ParentKey = RegisteredParentKey;
                const auto Task = Domain->Model();
                Task->StartBackgroundTask();
            }
        );
    }

    void FRandomShowcaseAccessTokenDomain::Unsubscribe(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        Gs2->Cache->Unsubscribe(
            Gs2::Showcase::Model::FRandomShowcase::TypeName,
            ParentKey,
            Gs2::Showcase::Model::Cache::FRandomShowcaseCache::CreateCacheKey(
                ShowcaseName
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
