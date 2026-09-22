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
#include "Core/Domain/Transaction/ManualTransactionDomain.h"

namespace Gs2::Showcase::Domain::Model
{

    FRandomShowcaseDomain::FRandomShowcaseDomain(
        const Core::Domain::FGs2Ptr& Gs2,
        const Showcase::Domain::FGs2ShowcaseDomainPtr& Service,
        const TOptional<FString> NamespaceName,
        const TOptional<FString> UserId,
        const TOptional<FString> ShowcaseName
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Gs2(Gs2),
        Service(Service),
        Client(MakeShared<Gs2::Showcase::FGs2ShowcaseRestClient>(Gs2->RestSession)),
        NamespaceName(NamespaceName),
        UserId(UserId),
        ShowcaseName(ShowcaseName),
        ParentKey(Gs2::Showcase::Domain::Model::FUserDomain::CreateCacheParentKey(
            NamespaceName,
            UserId,
            "RandomShowcase"
        ))
    {
    }

    FRandomShowcaseDomain::FRandomShowcaseDomain(
        const FRandomShowcaseDomain& From
    ):
        Gs2(From.Gs2),
        Service(From.Service),
        Client(From.Client),
        NamespaceName(From.NamespaceName),
        UserId(From.UserId),
        ShowcaseName(From.ShowcaseName),
        ParentKey(From.ParentKey)
    {

    }

    Gs2::Showcase::Domain::Iterator::FDescribeRandomDisplayItemsByUserIdIteratorPtr FRandomShowcaseDomain::RandomDisplayItems(
        const TOptional<FString> TimeOffsetToken
    ) const
    {
        return MakeShared<Gs2::Showcase::Domain::Iterator::FDescribeRandomDisplayItemsByUserIdIterator>(
            Gs2,
            Client,
            NamespaceName,
            ShowcaseName,
            UserId,
            TimeOffsetToken
        );
    }

    Gs2::Core::Domain::CallbackID FRandomShowcaseDomain::SubscribeRandomDisplayItems(
    TFunction<void()> Callback
    )
    {
        return Gs2->Cache->ListSubscribe(
            Gs2::Showcase::Model::FRandomDisplayItem::TypeName,
            Gs2::Showcase::Model::Cache::FRandomDisplayItemCache::CreateCacheParentKey(
                NamespaceName,
                UserId,
                ShowcaseName,
                TOptional<int32>()
            ),
            Callback,
            Callback
        );
    }
    void FRandomShowcaseDomain::UnsubscribeRandomDisplayItems(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        Gs2->Cache->ListUnsubscribe(
            Gs2::Showcase::Model::FRandomDisplayItem::TypeName,
            Gs2::Showcase::Model::Cache::FRandomDisplayItemCache::CreateCacheParentKey(
                NamespaceName,
                UserId,
                ShowcaseName,
                TOptional<int32>()
            ),
            CallbackID
        );
    }
    class FRandomShowcaseDomain::FCollectRandomDisplayItemsTask : public Gs2::Core::Util::TGs2Future<TArray<Gs2::Showcase::Model::FRandomDisplayItemPtr>>, public TSharedFromThis<FCollectRandomDisplayItemsTask>
    {
        const TSharedPtr<FRandomShowcaseDomain> Self;
        const TFunction<void(TArray<Gs2::Showcase::Model::FRandomDisplayItemPtr>)> OnCollected;
    const TOptional<FString> QueryTimeOffsetToken;
    public:
        explicit FCollectRandomDisplayItemsTask(const TSharedPtr<FRandomShowcaseDomain>& Self, TFunction<void(TArray<Gs2::Showcase::Model::FRandomDisplayItemPtr>)> OnCollected,const TOptional<FString> TimeOffsetToken) : Self(Self), OnCollected(OnCollected), QueryTimeOffsetToken(TimeOffsetToken) {}
        FCollectRandomDisplayItemsTask(const FCollectRandomDisplayItemsTask& From) : TGs2Future(From), Self(From.Self), OnCollected(From.OnCollected), QueryTimeOffsetToken(From.QueryTimeOffsetToken) {}
        virtual Gs2::Core::Model::FGs2ErrorPtr Action(TSharedPtr<TSharedPtr<TArray<Gs2::Showcase::Model::FRandomDisplayItemPtr>>> Result) override
        {
            TArray<Gs2::Showcase::Model::FRandomDisplayItemPtr> Items;
            auto Iterator = Self->RandomDisplayItems(QueryTimeOffsetToken)->begin();
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

    Gs2::Core::Domain::CallbackID FRandomShowcaseDomain::SubscribeRandomDisplayItems(
        TFunction<void(TArray<Gs2::Showcase::Model::FRandomDisplayItemPtr>)> Callback,const TOptional<FString> TimeOffsetToken
    )
    {
        const TWeakPtr<Gs2::Core::Domain::FGs2> WeakGs2 = this->Gs2;
        const TWeakPtr<Showcase::Domain::FGs2ShowcaseDomain> WeakService = this->Service;
        const auto QueryNamespaceName = NamespaceName;
        const auto QueryUserId = UserId;
        const auto QueryShowcaseName = ShowcaseName;
        const auto QueryTimeOffsetToken = TimeOffsetToken;
        const auto Parent = Gs2::Showcase::Model::Cache::FRandomDisplayItemCache::CreateCacheParentKey(
        NamespaceName,
        UserId,
        ShowcaseName,
        TOptional<int32>()
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
            [WeakGs2, WeakService, Callback, QueryNamespaceName, QueryUserId, QueryShowcaseName, QueryTimeOffsetToken]()
            {
                const auto Owner = WeakGs2.Pin();
                if (!Owner.IsValid()) return;
                const auto Domain = MakeShared<FRandomShowcaseDomain>(Owner, WeakService.Pin(), QueryNamespaceName, QueryUserId, QueryShowcaseName);
                const auto Task = Gs2::Core::Util::New<FAsyncTask<FCollectRandomDisplayItemsTask>>(Domain, Callback, QueryTimeOffsetToken);
                Task->StartBackgroundTask();
            }
        );
    }

    void FRandomShowcaseDomain::InvalidateRandomDisplayItems(const TOptional<FString> TimeOffsetToken)
    {
        Gs2->Cache->ClearListCache(
            Gs2::Showcase::Model::FRandomDisplayItem::TypeName,
            Gs2::Showcase::Model::Cache::FRandomDisplayItemCache::CreateCacheParentKey(
        NamespaceName,
        UserId,
        ShowcaseName,
        TOptional<int32>()
    )
        );
    }

    FRandomShowcaseDomain::FSubscribeRandomDisplayItemsWithInitialCallTask::FSubscribeRandomDisplayItemsWithInitialCallTask(const TSharedPtr<FRandomShowcaseDomain>& Self, TFunction<void(TArray<Gs2::Showcase::Model::FRandomDisplayItemPtr>)> Callback,const TOptional<FString> TimeOffsetToken) : Self(Self), Callback(Callback), QueryTimeOffsetToken(TimeOffsetToken) {}
    FRandomShowcaseDomain::FSubscribeRandomDisplayItemsWithInitialCallTask::FSubscribeRandomDisplayItemsWithInitialCallTask(const FSubscribeRandomDisplayItemsWithInitialCallTask& From) : TGs2Future(From), Self(From.Self), Callback(From.Callback), QueryTimeOffsetToken(From.QueryTimeOffsetToken) {}
    Gs2::Core::Model::FGs2ErrorPtr FRandomShowcaseDomain::FSubscribeRandomDisplayItemsWithInitialCallTask::Action(TSharedPtr<TSharedPtr<Gs2::Core::Domain::CallbackID>> Result)
    {
        const auto Task = Gs2::Core::Util::New<FAsyncTask<FCollectRandomDisplayItemsTask>>(Self, TFunction<void(TArray<Gs2::Showcase::Model::FRandomDisplayItemPtr>)>(), QueryTimeOffsetToken);
        Task->StartSynchronousTask(); Task->EnsureCompletion();
        if (Task->GetTask().IsError()) return Task->GetTask().Error();
        const auto Values = Task->GetTask().Result();
        const auto CallbackId = Self->SubscribeRandomDisplayItems(Callback, QueryTimeOffsetToken);
        Callback(*Values); *Result = MakeShared<Gs2::Core::Domain::CallbackID>(CallbackId);
        return nullptr;
    }
    TSharedPtr<FAsyncTask<FRandomShowcaseDomain::FSubscribeRandomDisplayItemsWithInitialCallTask>> FRandomShowcaseDomain::SubscribeRandomDisplayItemsWithInitialCall(TFunction<void(TArray<Gs2::Showcase::Model::FRandomDisplayItemPtr>)> Callback,const TOptional<FString> TimeOffsetToken)
    {
        return Gs2::Core::Util::New<FAsyncTask<FSubscribeRandomDisplayItemsWithInitialCallTask>>(this->AsShared(), Callback, TimeOffsetToken);
    }

    TSharedPtr<Gs2::Showcase::Domain::Model::FRandomDisplayItemDomain> FRandomShowcaseDomain::RandomDisplayItem(
        const FString DisplayItemName
    )
    {
        return MakeShared<Gs2::Showcase::Domain::Model::FRandomDisplayItemDomain>(
            Gs2,
            Service,
            NamespaceName,
            UserId,
            ShowcaseName,
            DisplayItemName == TEXT("") ? TOptional<FString>() : TOptional<FString>(DisplayItemName)
        );
    }

    FString FRandomShowcaseDomain::CreateCacheParentKey(
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

    FString FRandomShowcaseDomain::CreateCacheKey(
        TOptional<FString> ShowcaseName
    )
    {
        return FString("") +
            (ShowcaseName.IsSet() ? *ShowcaseName : "null");
    }

    FRandomShowcaseDomain::FModelTask::FModelTask(
        const TSharedPtr<FRandomShowcaseDomain> Self
    ): Self(Self)
    {

    }

    FRandomShowcaseDomain::FModelTask::FModelTask(
        const FModelTask& From
    ): TGs2Future(From), Self(From.Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FRandomShowcaseDomain::FModelTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Showcase::Model::FRandomShowcase>> Result
    )
    {
        const auto CacheParentKey = Gs2::Showcase::Model::Cache::FRandomShowcaseCache::CreateCacheParentKey(

            Self->NamespaceName,
            Self->UserId,
            TOptional<int32>()
        );
        const auto CacheKey = Gs2::Showcase::Model::Cache::FRandomShowcaseCache::CreateCacheKey(

            Self->ShowcaseName
        );
        return Self->Gs2->Cache->ExecuteWithKeyLock(
            Gs2::Showcase::Model::FRandomShowcase::TypeName,
            CacheParentKey,
            CacheKey,
            [Self = Self, Result]() -> Gs2::Core::Model::FGs2ErrorPtr
            {
                Gs2::Showcase::Model::FRandomShowcasePtr Value;
                const auto CacheHit = Gs2::Showcase::Model::Cache::FRandomShowcaseCache::TryGet(
                    Self->Gs2->Cache,

                    Self->NamespaceName,
                    Self->UserId,
                    Self->ShowcaseName,
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

    TSharedPtr<FAsyncTask<FRandomShowcaseDomain::FModelTask>> FRandomShowcaseDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FRandomShowcaseDomain::FModelTask>>(this->AsShared());
    }

    void FRandomShowcaseDomain::Invalidate()
    {
        Gs2::Showcase::Model::Cache::FRandomShowcaseCache::Delete(
            Gs2->Cache,

            NamespaceName,
            UserId,
            ShowcaseName,
            TOptional<int32>()
        );
    }

    FRandomShowcaseDomain::FSubscribeWithInitialCallTask::FSubscribeWithInitialCallTask(
        const TSharedPtr<FRandomShowcaseDomain>& Self,
        TFunction<void(Gs2::Showcase::Model::FRandomShowcasePtr)> Callback
    ):
        Self(Self),
        Callback(Callback)
    {
    }

    FRandomShowcaseDomain::FSubscribeWithInitialCallTask::FSubscribeWithInitialCallTask(
        const FSubscribeWithInitialCallTask& From
    ):
        TGs2Future(From),
        Self(From.Self),
        Callback(From.Callback)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FRandomShowcaseDomain::FSubscribeWithInitialCallTask::Action(
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

    TSharedPtr<FAsyncTask<FRandomShowcaseDomain::FSubscribeWithInitialCallTask>> FRandomShowcaseDomain::SubscribeWithInitialCall(
        TFunction<void(Gs2::Showcase::Model::FRandomShowcasePtr)> Callback
    )
    {
        return Gs2::Core::Util::New<FAsyncTask<FSubscribeWithInitialCallTask>>(this->AsShared(), Callback);
    }

    Gs2::Core::Domain::CallbackID FRandomShowcaseDomain::Subscribe(
        TFunction<void(Gs2::Showcase::Model::FRandomShowcasePtr)> Callback
    )
    {
        const auto SubscriptionParentKey = Gs2::Showcase::Model::Cache::FRandomShowcaseCache::CreateCacheParentKey(

            NamespaceName,
            UserId,
            TOptional<int32>()
        );
        const auto SubscriptionCacheKey = Gs2::Showcase::Model::Cache::FRandomShowcaseCache::CreateCacheKey(

            ShowcaseName
        );
        const TWeakPtr<Gs2::Core::Domain::FGs2> WeakGs2 = Gs2;
        const TWeakPtr<Showcase::Domain::FGs2ShowcaseDomain> WeakService = Service;
        const FString RegisteredParentKey = SubscriptionParentKey;
        const TOptional<FString> QueryNamespaceName = NamespaceName;
        const TOptional<FString> QueryUserId = UserId;
        const TOptional<FString> QueryShowcaseName = ShowcaseName;
        return Gs2->Cache->Subscribe(
            Gs2::Showcase::Model::FRandomShowcase::TypeName,
            SubscriptionParentKey,
            SubscriptionCacheKey,
            [Callback](TSharedPtr<FGs2Object> obj)
            {
                Callback(StaticCastSharedPtr<Gs2::Showcase::Model::FRandomShowcase>(obj));
            },
            [WeakGs2, WeakService, RegisteredParentKey, QueryNamespaceName, QueryUserId, QueryShowcaseName]()
            {
                const auto Owner = WeakGs2.Pin();
                if (!Owner.IsValid())
                {
                    return;
                }
                const auto Domain = MakeShared<FRandomShowcaseDomain>(
                    Owner,
                    WeakService.Pin(),
                    QueryNamespaceName,
                    QueryUserId,
                    QueryShowcaseName
                );
                Domain->ParentKey = RegisteredParentKey;
                const auto Task = Domain->Model();
                Task->StartBackgroundTask();
            }
        );
    }

    void FRandomShowcaseDomain::Unsubscribe(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        const auto SubscriptionParentKey = Gs2::Showcase::Model::Cache::FRandomShowcaseCache::CreateCacheParentKey(

            NamespaceName,
            UserId,
            TOptional<int32>()
        );
        const auto SubscriptionCacheKey = Gs2::Showcase::Model::Cache::FRandomShowcaseCache::CreateCacheKey(

            ShowcaseName
        );
        Gs2->Cache->Unsubscribe(
            Gs2::Showcase::Model::FRandomShowcase::TypeName,
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
