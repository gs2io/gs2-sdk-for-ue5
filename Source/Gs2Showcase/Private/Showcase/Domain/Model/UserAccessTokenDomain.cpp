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

#include "Showcase/Domain/Model/UserAccessToken.h"
#include "Showcase/Domain/Model/User.h"
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
#include "Showcase/Model/Cache/Showcase.h"
#include "Showcase/Model/Cache/DisplayItem.h"

#include "Core/Domain/Gs2.h"
#include "Core/Domain/Transaction/JobQueueJobDomainFactory.h"
#include "Core/Domain/Transaction/InternalTransactionDomainFactory.h"
#include "Core/Domain/Transaction/ManualTransactionAccessTokenDomain.h"

namespace Gs2::Showcase::Domain::Model
{

    FUserAccessTokenDomain::FUserAccessTokenDomain(
        const Core::Domain::FGs2Ptr& Gs2,
        const Showcase::Domain::FGs2ShowcaseDomainPtr& Service,
        const TOptional<FString> NamespaceName,
        const Gs2::Auth::Model::FAccessTokenPtr& AccessToken
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Gs2(Gs2),
        Service(Service),
        Client(MakeShared<Gs2::Showcase::FGs2ShowcaseRestClient>(Gs2->RestSession)),
        NamespaceName(NamespaceName),
        AccessToken(AccessToken),
        ParentKey(Gs2::Showcase::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
            NamespaceName,
            "User"
        ))
    {
    }

    FUserAccessTokenDomain::FUserAccessTokenDomain(
        const FUserAccessTokenDomain& From
    ):
        Gs2(From.Gs2),
        Service(From.Service),
        Client(From.Client),
        NamespaceName(From.NamespaceName),
        AccessToken(From.AccessToken),
        ParentKey(From.ParentKey)
    {

    }

    Gs2::Showcase::Domain::Iterator::FDescribeShowcasesIteratorPtr FUserAccessTokenDomain::Showcases(
    ) const
    {
        return MakeShared<Gs2::Showcase::Domain::Iterator::FDescribeShowcasesIterator>(
            Gs2,
            Client,
            NamespaceName,
            AccessToken
        );
    }

    Gs2::Core::Domain::CallbackID FUserAccessTokenDomain::SubscribeShowcases(
    TFunction<void()> Callback

    )
    {
        return Gs2->Cache->ListSubscribe(
            Gs2::Showcase::Model::FShowcase::TypeName,
            Gs2::Showcase::Model::Cache::FShowcaseCache::CreateCacheParentKey(
                NamespaceName,
                AccessToken.IsValid() ? AccessToken->GetUserId() : TOptional<FString>(),
                AccessToken.IsValid() ? AccessToken->GetTimeOffset() : TOptional<int32>()
            ),
            Callback,
            Callback
        );
    }
    void FUserAccessTokenDomain::UnsubscribeShowcases(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        Gs2->Cache->ListUnsubscribe(
            Gs2::Showcase::Model::FShowcase::TypeName,
            Gs2::Showcase::Model::Cache::FShowcaseCache::CreateCacheParentKey(
                NamespaceName,
                AccessToken.IsValid() ? AccessToken->GetUserId() : TOptional<FString>(),
                AccessToken.IsValid() ? AccessToken->GetTimeOffset() : TOptional<int32>()
            ),
            CallbackID
        );
    }
    class FUserAccessTokenDomain::FCollectShowcasesTask : public Gs2::Core::Util::TGs2Future<TArray<Gs2::Showcase::Model::FShowcasePtr>>, public TSharedFromThis<FCollectShowcasesTask>
    {
        const TSharedPtr<FUserAccessTokenDomain> Self;
        const TFunction<void(TArray<Gs2::Showcase::Model::FShowcasePtr>)> OnCollected;

    public:
        explicit FCollectShowcasesTask(const TSharedPtr<FUserAccessTokenDomain>& Self, TFunction<void(TArray<Gs2::Showcase::Model::FShowcasePtr>)> OnCollected) : Self(Self), OnCollected(OnCollected) {}
        FCollectShowcasesTask(const FCollectShowcasesTask& From) : TGs2Future(From), Self(From.Self), OnCollected(From.OnCollected) {}
        virtual Gs2::Core::Model::FGs2ErrorPtr Action(TSharedPtr<TSharedPtr<TArray<Gs2::Showcase::Model::FShowcasePtr>>> Result) override
        {
            TArray<Gs2::Showcase::Model::FShowcasePtr> Items;
            auto Iterator = Self->Showcases()->begin();
            while (Iterator.HasNext())
            {
                if (Iterator.IsError()) return Iterator.Error();
                if (Iterator.IsCurrentValid()) Items.Add(Iterator.Current());
                ++Iterator;
            }
            if (Iterator.IsError()) return Iterator.Error();
            *Result = MakeShared<TArray<Gs2::Showcase::Model::FShowcasePtr>>(Items);
            if (OnCollected) OnCollected(Items);
            return nullptr;
        }
    };

    Gs2::Core::Domain::CallbackID FUserAccessTokenDomain::SubscribeShowcases(
        TFunction<void(TArray<Gs2::Showcase::Model::FShowcasePtr>)> Callback
    )
    {
        const TWeakPtr<Gs2::Core::Domain::FGs2> WeakGs2 = this->Gs2;
        const TWeakPtr<Showcase::Domain::FGs2ShowcaseDomain> WeakService = this->Service;
        const auto SourceToken = this->AccessToken;
        const TOptional<FString> RegisteredUserId = SourceToken.IsValid() ? TOptional<FString>(SourceToken->GetUserId()) : TOptional<FString>();
        const int32 RegisteredTimeOffset = SourceToken.IsValid() ? SourceToken->GetTimeOffset().Get(0) : 0;
        const auto QueryNamespaceName = NamespaceName;
        const auto Parent = Gs2::Showcase::Model::Cache::FShowcaseCache::CreateCacheParentKey(
        NamespaceName,
        AccessToken.IsValid() ? AccessToken->GetUserId() : TOptional<FString>(),
        AccessToken.IsValid() ? AccessToken->GetTimeOffset() : TOptional<int32>()
    );
        return Gs2->Cache->ListSubscribeTyped(
            Gs2::Showcase::Model::FShowcase::TypeName,
            Parent,
            [Callback, WeakGs2](const TArray<FGs2ObjectPtr>& Values)
            {
                if (!WeakGs2.Pin().IsValid()) return;
                TArray<Gs2::Showcase::Model::FShowcasePtr> TypedValues;
                for (const auto& Value : Values) if (Value.IsValid()) TypedValues.Add(StaticCastSharedPtr<Gs2::Showcase::Model::FShowcase>(Value));
                Callback(TypedValues);
            },
            [WeakGs2, WeakService, Callback, QueryNamespaceName, SourceToken, RegisteredUserId, RegisteredTimeOffset]()
            {
                const auto Owner = WeakGs2.Pin();
                if (!Owner.IsValid() || !SourceToken.IsValid() || !RegisteredUserId.IsSet()) return;
                const auto TokenSnapshot = MakeShared<Gs2::Auth::Model::FAccessToken>(*SourceToken);
                if (TokenSnapshot->GetUserId() != RegisteredUserId || TokenSnapshot->GetTimeOffset().Get(0) != RegisteredTimeOffset) return;
                const auto Domain = MakeShared<FUserAccessTokenDomain>(Owner, WeakService.Pin(), QueryNamespaceName, TokenSnapshot);
                const auto Task = Gs2::Core::Util::New<FAsyncTask<FCollectShowcasesTask>>(Domain, Callback);
                Task->StartBackgroundTask();
            }
        );
    }

    void FUserAccessTokenDomain::InvalidateShowcases()
    {
        Gs2->Cache->ClearListCache(
            Gs2::Showcase::Model::FShowcase::TypeName,
            Gs2::Showcase::Model::Cache::FShowcaseCache::CreateCacheParentKey(
        NamespaceName,
        AccessToken.IsValid() ? AccessToken->GetUserId() : TOptional<FString>(),
        AccessToken.IsValid() ? AccessToken->GetTimeOffset() : TOptional<int32>()
    )
        );
    }

    FUserAccessTokenDomain::FSubscribeShowcasesWithInitialCallTask::FSubscribeShowcasesWithInitialCallTask(const TSharedPtr<FUserAccessTokenDomain>& Self, TFunction<void(TArray<Gs2::Showcase::Model::FShowcasePtr>)> Callback) : Self(Self), Callback(Callback) {}
    FUserAccessTokenDomain::FSubscribeShowcasesWithInitialCallTask::FSubscribeShowcasesWithInitialCallTask(const FSubscribeShowcasesWithInitialCallTask& From) : TGs2Future(From), Self(From.Self), Callback(From.Callback) {}
    Gs2::Core::Model::FGs2ErrorPtr FUserAccessTokenDomain::FSubscribeShowcasesWithInitialCallTask::Action(TSharedPtr<TSharedPtr<Gs2::Core::Domain::CallbackID>> Result)
    {
        const auto Task = Gs2::Core::Util::New<FAsyncTask<FCollectShowcasesTask>>(Self, TFunction<void(TArray<Gs2::Showcase::Model::FShowcasePtr>)>());
        Task->StartSynchronousTask(); Task->EnsureCompletion();
        if (Task->GetTask().IsError()) return Task->GetTask().Error();
        const auto Values = Task->GetTask().Result();
        const auto CallbackId = Self->SubscribeShowcases(Callback);
        Callback(*Values); *Result = MakeShared<Gs2::Core::Domain::CallbackID>(CallbackId);
        return nullptr;
    }
    TSharedPtr<FAsyncTask<FUserAccessTokenDomain::FSubscribeShowcasesWithInitialCallTask>> FUserAccessTokenDomain::SubscribeShowcasesWithInitialCall(TFunction<void(TArray<Gs2::Showcase::Model::FShowcasePtr>)> Callback)
    {
        return Gs2::Core::Util::New<FAsyncTask<FSubscribeShowcasesWithInitialCallTask>>(this->AsShared(), Callback);
    }

    TSharedPtr<Gs2::Showcase::Domain::Model::FShowcaseAccessTokenDomain> FUserAccessTokenDomain::Showcase(
        const FString ShowcaseName
    )
    {
        return MakeShared<Gs2::Showcase::Domain::Model::FShowcaseAccessTokenDomain>(
            Gs2,
            Service,
            NamespaceName,
            AccessToken,
            ShowcaseName == TEXT("") ? TOptional<FString>() : TOptional<FString>(ShowcaseName)
        );
    }

    TSharedPtr<Gs2::Showcase::Domain::Model::FRandomShowcaseAccessTokenDomain> FUserAccessTokenDomain::RandomShowcase(
        const FString ShowcaseName
    )
    {
        return MakeShared<Gs2::Showcase::Domain::Model::FRandomShowcaseAccessTokenDomain>(
            Gs2,
            Service,
            NamespaceName,
            AccessToken,
            ShowcaseName == TEXT("") ? TOptional<FString>() : TOptional<FString>(ShowcaseName)
        );
    }

    TSharedPtr<Gs2::Showcase::Domain::Model::FRandomShowcaseStatusAccessTokenDomain> FUserAccessTokenDomain::RandomShowcaseStatus(
        const FString ShowcaseName
    )
    {
        return MakeShared<Gs2::Showcase::Domain::Model::FRandomShowcaseStatusAccessTokenDomain>(
            Gs2,
            Service,
            NamespaceName,
            AccessToken,
            ShowcaseName == TEXT("") ? TOptional<FString>() : TOptional<FString>(ShowcaseName)
        );
    }

    FString FUserAccessTokenDomain::CreateCacheParentKey(
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

    FString FUserAccessTokenDomain::CreateCacheKey(
        TOptional<FString> UserId
    )
    {
        return FString("") +
            (UserId.IsSet() ? *UserId : "null");
    }
}

#if defined(_MSC_VER)
#pragma warning (pop)
#elif defined(__clang__)
#pragma clang diagnostic pop
#endif
