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

#include "Dictionary/Domain/Model/UserAccessToken.h"
#include "Dictionary/Domain/Model/User.h"
#include "Dictionary/Domain/Model/Namespace.h"
#include "Dictionary/Domain/Model/EntryModel.h"
#include "Dictionary/Domain/Model/EntryModelMaster.h"
#include "Dictionary/Domain/Model/Entry.h"
#include "Dictionary/Domain/Model/EntryAccessToken.h"
#include "Dictionary/Domain/Model/Like.h"
#include "Dictionary/Domain/Model/LikeAccessToken.h"
#include "Dictionary/Domain/Model/CurrentEntryMaster.h"
#include "Dictionary/Domain/Model/User.h"
#include "Dictionary/Domain/Model/UserAccessToken.h"
#include "Dictionary/Model/Cache/Entry.h"
#include "Dictionary/Model/Cache/Like.h"

#include "Core/Domain/Gs2.h"
#include "Core/Domain/Transaction/JobQueueJobDomainFactory.h"
#include "Core/Domain/Transaction/InternalTransactionDomainFactory.h"
#include "Core/Domain/Transaction/ManualTransactionAccessTokenDomain.h"

namespace Gs2::Dictionary::Domain::Model
{

    FUserAccessTokenDomain::FUserAccessTokenDomain(
        const Core::Domain::FGs2Ptr& Gs2,
        const Dictionary::Domain::FGs2DictionaryDomainPtr& Service,
        const TOptional<FString> NamespaceName,
        const Gs2::Auth::Model::FAccessTokenPtr& AccessToken
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Gs2(Gs2),
        Service(Service),
        Client(MakeShared<Gs2::Dictionary::FGs2DictionaryRestClient>(Gs2->RestSession)),
        NamespaceName(NamespaceName),
        AccessToken(AccessToken),
        ParentKey(Gs2::Dictionary::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
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

    FUserAccessTokenDomain::FDeleteEntriesTask::FDeleteEntriesTask(
        const TSharedPtr<FUserAccessTokenDomain>& Self,
        const Request::FDeleteEntriesRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FUserAccessTokenDomain::FDeleteEntriesTask::FDeleteEntriesTask(
        const FDeleteEntriesTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FUserAccessTokenDomain::FDeleteEntriesTask::Action(
        TSharedPtr<TSharedPtr<TArray<TSharedPtr<Gs2::Dictionary::Domain::Model::FEntryAccessTokenDomain>>>> Result
    )
    {
        Request
            ->WithContextStack((!Request->GetContextStack().IsSet() || Request->GetContextStack()->IsEmpty()) ? Self->Gs2->DefaultContextStack : Request->GetContextStack())
            ->WithNamespaceName(Self->NamespaceName)
            ->WithAccessToken(Self->AccessToken->GetToken());
        const auto CacheOwnerSnapshotUserId = Self->AccessToken.IsValid() ? Self->UserId() : TOptional<FString>();
        const auto CacheOwnerSnapshotTimeOffset = Self->AccessToken.IsValid() ? Self->AccessToken->GetTimeOffset() : TOptional<int32>();
        const auto Future = Self->Client->DeleteEntries(
            Request
        );
        Future->StartSynchronousTask();
        if (Future->GetTask().IsError())
        {
            const auto Error = Future->GetTask().Error();
            if (Error.IsValid() && Error->IsChildOf(Gs2::Core::Model::FNotFoundError::Class))
            {
                *Result = MakeShared<TArray<TSharedPtr<Gs2::Dictionary::Domain::Model::FEntryAccessTokenDomain>>>();
                return nullptr;
            }
            return Error;
        }
        const auto ResultModel = Future->GetTask().Result();
        Future->EnsureCompletion();
        if (ResultModel.IsValid() && ResultModel->GetItems().IsValid())
        {
            for (const auto& Item : *ResultModel->GetItems())
            {
                if (!Item.IsValid()) continue;
                Gs2::Dictionary::Model::Cache::FEntryCache::Delete(
                    Self->Gs2->Cache,
                    Request->GetNamespaceName(), CacheOwnerSnapshotUserId, Item->GetName(),
                    CacheOwnerSnapshotTimeOffset
                );
            }
        }

        auto Domain = MakeShared<TArray<TSharedPtr<Gs2::Dictionary::Domain::Model::FEntryAccessTokenDomain>>>();
        if (ResultModel.IsValid() && ResultModel->GetItems().IsValid())
        {
        for (auto i=0; i<ResultModel->GetItems()->Num(); i++)
        {
            Domain->Add(
                MakeShared<Gs2::Dictionary::Domain::Model::FEntryAccessTokenDomain>(
                    Self->Gs2,
                    Self->Service,
                    Request->GetNamespaceName(),
                    Self->AccessToken,
                    (*ResultModel->GetItems())[i]->GetName()
                )
            );
        }
        }
        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FUserAccessTokenDomain::FDeleteEntriesTask>> FUserAccessTokenDomain::DeleteEntries(
        Request::FDeleteEntriesRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FDeleteEntriesTask>>(this->AsShared(), Request);
    }

    FUserAccessTokenDomain::FAddLikesTask::FAddLikesTask(
        const TSharedPtr<FUserAccessTokenDomain>& Self,
        const Request::FAddLikesRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FUserAccessTokenDomain::FAddLikesTask::FAddLikesTask(
        const FAddLikesTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FUserAccessTokenDomain::FAddLikesTask::Action(
        TSharedPtr<TSharedPtr<TArray<TSharedPtr<Gs2::Dictionary::Domain::Model::FLikeAccessTokenDomain>>>> Result
    )
    {
        Request
            ->WithContextStack((!Request->GetContextStack().IsSet() || Request->GetContextStack()->IsEmpty()) ? Self->Gs2->DefaultContextStack : Request->GetContextStack())
            ->WithNamespaceName(Self->NamespaceName)
            ->WithAccessToken(Self->AccessToken->GetToken());
        const auto CacheOwnerSnapshotUserId = Self->AccessToken.IsValid() ? Self->UserId() : TOptional<FString>();
        const auto CacheOwnerSnapshotTimeOffset = Self->AccessToken.IsValid() ? Self->AccessToken->GetTimeOffset() : TOptional<int32>();
        const auto Future = Self->Client->AddLikes(
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
                Gs2::Dictionary::Model::Cache::FLikeCache::Put(
                    Self->Gs2->Cache,
                    Request->GetNamespaceName(), CacheOwnerSnapshotUserId, Item->GetName(),
                    CacheOwnerSnapshotTimeOffset, Item
                );
            }
        }

        auto Domain = MakeShared<TArray<TSharedPtr<Gs2::Dictionary::Domain::Model::FLikeAccessTokenDomain>>>();
        if (ResultModel.IsValid() && ResultModel->GetItems().IsValid())
        {
        for (auto i=0; i<ResultModel->GetItems()->Num(); i++)
        {
            Domain->Add(
                MakeShared<Gs2::Dictionary::Domain::Model::FLikeAccessTokenDomain>(
                    Self->Gs2,
                    Self->Service,
                    Request->GetNamespaceName(),
                    Self->AccessToken,
                    (*ResultModel->GetItems())[i]->GetName()
                )
            );
        }
        }
        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FUserAccessTokenDomain::FAddLikesTask>> FUserAccessTokenDomain::AddLikes(
        Request::FAddLikesRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FAddLikesTask>>(this->AsShared(), Request);
    }

    FUserAccessTokenDomain::FResetLikesTask::FResetLikesTask(
        const TSharedPtr<FUserAccessTokenDomain>& Self,
        const Request::FResetLikesRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FUserAccessTokenDomain::FResetLikesTask::FResetLikesTask(
        const FResetLikesTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FUserAccessTokenDomain::FResetLikesTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Dictionary::Domain::Model::FUserAccessTokenDomain>> Result
    )
    {
        Request
            ->WithContextStack((!Request->GetContextStack().IsSet() || Request->GetContextStack()->IsEmpty()) ? Self->Gs2->DefaultContextStack : Request->GetContextStack())
            ->WithNamespaceName(Self->NamespaceName)
            ->WithAccessToken(Self->AccessToken->GetToken());
        const auto Future = Self->Client->ResetLikes(
            Request
        );
        Future->StartSynchronousTask();
        if (Future->GetTask().IsError())
        {
            return Future->GetTask().Error();
        }
        const auto ResultModel = Future->GetTask().Result();
        Future->EnsureCompletion();

        const auto Domain = Self;
        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FUserAccessTokenDomain::FResetLikesTask>> FUserAccessTokenDomain::ResetLikes(
        Request::FResetLikesRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FResetLikesTask>>(this->AsShared(), Request);
    }

    FUserAccessTokenDomain::FDeleteLikesTask::FDeleteLikesTask(
        const TSharedPtr<FUserAccessTokenDomain>& Self,
        const Request::FDeleteLikesRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FUserAccessTokenDomain::FDeleteLikesTask::FDeleteLikesTask(
        const FDeleteLikesTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FUserAccessTokenDomain::FDeleteLikesTask::Action(
        TSharedPtr<TSharedPtr<TArray<TSharedPtr<Gs2::Dictionary::Domain::Model::FLikeAccessTokenDomain>>>> Result
    )
    {
        Request
            ->WithContextStack((!Request->GetContextStack().IsSet() || Request->GetContextStack()->IsEmpty()) ? Self->Gs2->DefaultContextStack : Request->GetContextStack())
            ->WithNamespaceName(Self->NamespaceName)
            ->WithAccessToken(Self->AccessToken->GetToken());
        const auto CacheOwnerSnapshotUserId = Self->AccessToken.IsValid() ? Self->UserId() : TOptional<FString>();
        const auto CacheOwnerSnapshotTimeOffset = Self->AccessToken.IsValid() ? Self->AccessToken->GetTimeOffset() : TOptional<int32>();
        const auto Future = Self->Client->DeleteLikes(
            Request
        );
        Future->StartSynchronousTask();
        if (Future->GetTask().IsError())
        {
            const auto Error = Future->GetTask().Error();
            if (Error.IsValid() && Error->IsChildOf(Gs2::Core::Model::FNotFoundError::Class))
            {
                *Result = MakeShared<TArray<TSharedPtr<Gs2::Dictionary::Domain::Model::FLikeAccessTokenDomain>>>();
                return nullptr;
            }
            return Error;
        }
        const auto ResultModel = Future->GetTask().Result();
        Future->EnsureCompletion();
        if (ResultModel.IsValid() && ResultModel->GetItems().IsValid())
        {
            for (const auto& Item : *ResultModel->GetItems())
            {
                if (!Item.IsValid()) continue;
                Gs2::Dictionary::Model::Cache::FLikeCache::Delete(
                    Self->Gs2->Cache,
                    Request->GetNamespaceName(), CacheOwnerSnapshotUserId, Item->GetName(),
                    CacheOwnerSnapshotTimeOffset
                );
            }
        }

        auto Domain = MakeShared<TArray<TSharedPtr<Gs2::Dictionary::Domain::Model::FLikeAccessTokenDomain>>>();
        if (ResultModel.IsValid() && ResultModel->GetItems().IsValid())
        {
        for (auto i=0; i<ResultModel->GetItems()->Num(); i++)
        {
            Domain->Add(
                MakeShared<Gs2::Dictionary::Domain::Model::FLikeAccessTokenDomain>(
                    Self->Gs2,
                    Self->Service,
                    Request->GetNamespaceName(),
                    Self->AccessToken,
                    (*ResultModel->GetItems())[i]->GetName()
                )
            );
        }
        }
        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FUserAccessTokenDomain::FDeleteLikesTask>> FUserAccessTokenDomain::DeleteLikes(
        Request::FDeleteLikesRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FDeleteLikesTask>>(this->AsShared(), Request);
    }

    Gs2::Dictionary::Domain::Iterator::FDescribeEntriesIteratorPtr FUserAccessTokenDomain::Entries(
    ) const
    {
        return MakeShared<Gs2::Dictionary::Domain::Iterator::FDescribeEntriesIterator>(
            Gs2,
            Client,
            NamespaceName,
            AccessToken
        );
    }

    Gs2::Core::Domain::CallbackID FUserAccessTokenDomain::SubscribeEntries(
    TFunction<void()> Callback

    )
    {
        return Gs2->Cache->ListSubscribe(
            Gs2::Dictionary::Model::FEntry::TypeName,
            Gs2::Dictionary::Model::Cache::FEntryCache::CreateCacheParentKey(
                NamespaceName,
                AccessToken.IsValid() ? AccessToken->GetUserId() : TOptional<FString>(),
                AccessToken.IsValid() ? AccessToken->GetTimeOffset() : TOptional<int32>()
            ),
            Callback,
            Callback
        );
    }
    void FUserAccessTokenDomain::UnsubscribeEntries(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        Gs2->Cache->ListUnsubscribe(
            Gs2::Dictionary::Model::FEntry::TypeName,
            Gs2::Dictionary::Model::Cache::FEntryCache::CreateCacheParentKey(
                NamespaceName,
                AccessToken.IsValid() ? AccessToken->GetUserId() : TOptional<FString>(),
                AccessToken.IsValid() ? AccessToken->GetTimeOffset() : TOptional<int32>()
            ),
            CallbackID
        );
    }
    class FUserAccessTokenDomain::FCollectEntriesTask : public Gs2::Core::Util::TGs2Future<TArray<Gs2::Dictionary::Model::FEntryPtr>>, public TSharedFromThis<FCollectEntriesTask>
    {
        const TSharedPtr<FUserAccessTokenDomain> Self;
        const TFunction<void(TArray<Gs2::Dictionary::Model::FEntryPtr>)> OnCollected;

    public:
        explicit FCollectEntriesTask(const TSharedPtr<FUserAccessTokenDomain>& Self, TFunction<void(TArray<Gs2::Dictionary::Model::FEntryPtr>)> OnCollected) : Self(Self), OnCollected(OnCollected) {}
        FCollectEntriesTask(const FCollectEntriesTask& From) : TGs2Future(From), Self(From.Self), OnCollected(From.OnCollected) {}
        virtual Gs2::Core::Model::FGs2ErrorPtr Action(TSharedPtr<TSharedPtr<TArray<Gs2::Dictionary::Model::FEntryPtr>>> Result) override
        {
            TArray<Gs2::Dictionary::Model::FEntryPtr> Items;
            auto Iterator = Self->Entries()->begin();
            while (Iterator.HasNext())
            {
                if (Iterator.IsError()) return Iterator.Error();
                if (Iterator.IsCurrentValid()) Items.Add(Iterator.Current());
                ++Iterator;
            }
            if (Iterator.IsError()) return Iterator.Error();
            *Result = MakeShared<TArray<Gs2::Dictionary::Model::FEntryPtr>>(Items);
            if (OnCollected) OnCollected(Items);
            return nullptr;
        }
    };

    Gs2::Core::Domain::CallbackID FUserAccessTokenDomain::SubscribeEntries(
        TFunction<void(TArray<Gs2::Dictionary::Model::FEntryPtr>)> Callback
    )
    {
        const TWeakPtr<Gs2::Core::Domain::FGs2> WeakGs2 = this->Gs2;
        const TWeakPtr<Dictionary::Domain::FGs2DictionaryDomain> WeakService = this->Service;
        const auto SourceToken = this->AccessToken;
        const TOptional<FString> RegisteredUserId = SourceToken.IsValid() ? TOptional<FString>(SourceToken->GetUserId()) : TOptional<FString>();
        const int32 RegisteredTimeOffset = SourceToken.IsValid() ? SourceToken->GetTimeOffset().Get(0) : 0;
        const auto QueryNamespaceName = NamespaceName;
        const auto Parent = Gs2::Dictionary::Model::Cache::FEntryCache::CreateCacheParentKey(
        NamespaceName,
        AccessToken.IsValid() ? AccessToken->GetUserId() : TOptional<FString>(),
        AccessToken.IsValid() ? AccessToken->GetTimeOffset() : TOptional<int32>()
    );
        return Gs2->Cache->ListSubscribeTyped(
            Gs2::Dictionary::Model::FEntry::TypeName,
            Parent,
            [Callback, WeakGs2](const TArray<FGs2ObjectPtr>& Values)
            {
                if (!WeakGs2.Pin().IsValid()) return;
                TArray<Gs2::Dictionary::Model::FEntryPtr> TypedValues;
                for (const auto& Value : Values) if (Value.IsValid()) TypedValues.Add(StaticCastSharedPtr<Gs2::Dictionary::Model::FEntry>(Value));
                Callback(TypedValues);
            },
            [WeakGs2, WeakService, Callback, QueryNamespaceName, SourceToken, RegisteredUserId, RegisteredTimeOffset]()
            {
                const auto Owner = WeakGs2.Pin();
                if (!Owner.IsValid() || !SourceToken.IsValid() || !RegisteredUserId.IsSet()) return;
                const auto TokenSnapshot = MakeShared<Gs2::Auth::Model::FAccessToken>(*SourceToken);
                if (TokenSnapshot->GetUserId() != RegisteredUserId || TokenSnapshot->GetTimeOffset().Get(0) != RegisteredTimeOffset) return;
                const auto Domain = MakeShared<FUserAccessTokenDomain>(Owner, WeakService.Pin(), QueryNamespaceName, TokenSnapshot);
                const auto Task = Gs2::Core::Util::New<FAsyncTask<FCollectEntriesTask>>(Domain, Callback);
                Task->StartBackgroundTask();
            }
        );
    }

    void FUserAccessTokenDomain::InvalidateEntries()
    {
        Gs2->Cache->ClearListCache(
            Gs2::Dictionary::Model::FEntry::TypeName,
            Gs2::Dictionary::Model::Cache::FEntryCache::CreateCacheParentKey(
        NamespaceName,
        AccessToken.IsValid() ? AccessToken->GetUserId() : TOptional<FString>(),
        AccessToken.IsValid() ? AccessToken->GetTimeOffset() : TOptional<int32>()
    )
        );
    }

    FUserAccessTokenDomain::FSubscribeEntriesWithInitialCallTask::FSubscribeEntriesWithInitialCallTask(const TSharedPtr<FUserAccessTokenDomain>& Self, TFunction<void(TArray<Gs2::Dictionary::Model::FEntryPtr>)> Callback) : Self(Self), Callback(Callback) {}
    FUserAccessTokenDomain::FSubscribeEntriesWithInitialCallTask::FSubscribeEntriesWithInitialCallTask(const FSubscribeEntriesWithInitialCallTask& From) : TGs2Future(From), Self(From.Self), Callback(From.Callback) {}
    Gs2::Core::Model::FGs2ErrorPtr FUserAccessTokenDomain::FSubscribeEntriesWithInitialCallTask::Action(TSharedPtr<TSharedPtr<Gs2::Core::Domain::CallbackID>> Result)
    {
        const auto Task = Gs2::Core::Util::New<FAsyncTask<FCollectEntriesTask>>(Self, TFunction<void(TArray<Gs2::Dictionary::Model::FEntryPtr>)>());
        Task->StartSynchronousTask(); Task->EnsureCompletion();
        if (Task->GetTask().IsError()) return Task->GetTask().Error();
        const auto Values = Task->GetTask().Result();
        const auto CallbackId = Self->SubscribeEntries(Callback);
        Callback(*Values); *Result = MakeShared<Gs2::Core::Domain::CallbackID>(CallbackId);
        return nullptr;
    }
    TSharedPtr<FAsyncTask<FUserAccessTokenDomain::FSubscribeEntriesWithInitialCallTask>> FUserAccessTokenDomain::SubscribeEntriesWithInitialCall(TFunction<void(TArray<Gs2::Dictionary::Model::FEntryPtr>)> Callback)
    {
        return Gs2::Core::Util::New<FAsyncTask<FSubscribeEntriesWithInitialCallTask>>(this->AsShared(), Callback);
    }

    TSharedPtr<Gs2::Dictionary::Domain::Model::FEntryAccessTokenDomain> FUserAccessTokenDomain::Entry(
        const FString EntryModelName
    )
    {
        return MakeShared<Gs2::Dictionary::Domain::Model::FEntryAccessTokenDomain>(
            Gs2,
            Service,
            NamespaceName,
            AccessToken,
            EntryModelName == TEXT("") ? TOptional<FString>() : TOptional<FString>(EntryModelName)
        );
    }

    Gs2::Dictionary::Domain::Iterator::FDescribeLikesIteratorPtr FUserAccessTokenDomain::Likes(
    ) const
    {
        return MakeShared<Gs2::Dictionary::Domain::Iterator::FDescribeLikesIterator>(
            Gs2,
            Client,
            NamespaceName,
            AccessToken
        );
    }

    Gs2::Core::Domain::CallbackID FUserAccessTokenDomain::SubscribeLikes(
    TFunction<void()> Callback

    )
    {
        return Gs2->Cache->ListSubscribe(
            Gs2::Dictionary::Model::FLike::TypeName,
            Gs2::Dictionary::Model::Cache::FLikeCache::CreateCacheParentKey(
                NamespaceName,
                AccessToken.IsValid() ? AccessToken->GetUserId() : TOptional<FString>(),
                AccessToken.IsValid() ? AccessToken->GetTimeOffset() : TOptional<int32>()
            ),
            Callback,
            Callback
        );
    }
    void FUserAccessTokenDomain::UnsubscribeLikes(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        Gs2->Cache->ListUnsubscribe(
            Gs2::Dictionary::Model::FLike::TypeName,
            Gs2::Dictionary::Model::Cache::FLikeCache::CreateCacheParentKey(
                NamespaceName,
                AccessToken.IsValid() ? AccessToken->GetUserId() : TOptional<FString>(),
                AccessToken.IsValid() ? AccessToken->GetTimeOffset() : TOptional<int32>()
            ),
            CallbackID
        );
    }
    class FUserAccessTokenDomain::FCollectLikesTask : public Gs2::Core::Util::TGs2Future<TArray<Gs2::Dictionary::Model::FLikePtr>>, public TSharedFromThis<FCollectLikesTask>
    {
        const TSharedPtr<FUserAccessTokenDomain> Self;
        const TFunction<void(TArray<Gs2::Dictionary::Model::FLikePtr>)> OnCollected;

    public:
        explicit FCollectLikesTask(const TSharedPtr<FUserAccessTokenDomain>& Self, TFunction<void(TArray<Gs2::Dictionary::Model::FLikePtr>)> OnCollected) : Self(Self), OnCollected(OnCollected) {}
        FCollectLikesTask(const FCollectLikesTask& From) : TGs2Future(From), Self(From.Self), OnCollected(From.OnCollected) {}
        virtual Gs2::Core::Model::FGs2ErrorPtr Action(TSharedPtr<TSharedPtr<TArray<Gs2::Dictionary::Model::FLikePtr>>> Result) override
        {
            TArray<Gs2::Dictionary::Model::FLikePtr> Items;
            auto Iterator = Self->Likes()->begin();
            while (Iterator.HasNext())
            {
                if (Iterator.IsError()) return Iterator.Error();
                if (Iterator.IsCurrentValid()) Items.Add(Iterator.Current());
                ++Iterator;
            }
            if (Iterator.IsError()) return Iterator.Error();
            *Result = MakeShared<TArray<Gs2::Dictionary::Model::FLikePtr>>(Items);
            if (OnCollected) OnCollected(Items);
            return nullptr;
        }
    };

    Gs2::Core::Domain::CallbackID FUserAccessTokenDomain::SubscribeLikes(
        TFunction<void(TArray<Gs2::Dictionary::Model::FLikePtr>)> Callback
    )
    {
        const TWeakPtr<Gs2::Core::Domain::FGs2> WeakGs2 = this->Gs2;
        const TWeakPtr<Dictionary::Domain::FGs2DictionaryDomain> WeakService = this->Service;
        const auto SourceToken = this->AccessToken;
        const TOptional<FString> RegisteredUserId = SourceToken.IsValid() ? TOptional<FString>(SourceToken->GetUserId()) : TOptional<FString>();
        const int32 RegisteredTimeOffset = SourceToken.IsValid() ? SourceToken->GetTimeOffset().Get(0) : 0;
        const auto QueryNamespaceName = NamespaceName;
        const auto Parent = Gs2::Dictionary::Model::Cache::FLikeCache::CreateCacheParentKey(
        NamespaceName,
        AccessToken.IsValid() ? AccessToken->GetUserId() : TOptional<FString>(),
        AccessToken.IsValid() ? AccessToken->GetTimeOffset() : TOptional<int32>()
    );
        return Gs2->Cache->ListSubscribeTyped(
            Gs2::Dictionary::Model::FLike::TypeName,
            Parent,
            [Callback, WeakGs2](const TArray<FGs2ObjectPtr>& Values)
            {
                if (!WeakGs2.Pin().IsValid()) return;
                TArray<Gs2::Dictionary::Model::FLikePtr> TypedValues;
                for (const auto& Value : Values) if (Value.IsValid()) TypedValues.Add(StaticCastSharedPtr<Gs2::Dictionary::Model::FLike>(Value));
                Callback(TypedValues);
            },
            [WeakGs2, WeakService, Callback, QueryNamespaceName, SourceToken, RegisteredUserId, RegisteredTimeOffset]()
            {
                const auto Owner = WeakGs2.Pin();
                if (!Owner.IsValid() || !SourceToken.IsValid() || !RegisteredUserId.IsSet()) return;
                const auto TokenSnapshot = MakeShared<Gs2::Auth::Model::FAccessToken>(*SourceToken);
                if (TokenSnapshot->GetUserId() != RegisteredUserId || TokenSnapshot->GetTimeOffset().Get(0) != RegisteredTimeOffset) return;
                const auto Domain = MakeShared<FUserAccessTokenDomain>(Owner, WeakService.Pin(), QueryNamespaceName, TokenSnapshot);
                const auto Task = Gs2::Core::Util::New<FAsyncTask<FCollectLikesTask>>(Domain, Callback);
                Task->StartBackgroundTask();
            }
        );
    }

    void FUserAccessTokenDomain::InvalidateLikes()
    {
        Gs2->Cache->ClearListCache(
            Gs2::Dictionary::Model::FLike::TypeName,
            Gs2::Dictionary::Model::Cache::FLikeCache::CreateCacheParentKey(
        NamespaceName,
        AccessToken.IsValid() ? AccessToken->GetUserId() : TOptional<FString>(),
        AccessToken.IsValid() ? AccessToken->GetTimeOffset() : TOptional<int32>()
    )
        );
    }

    FUserAccessTokenDomain::FSubscribeLikesWithInitialCallTask::FSubscribeLikesWithInitialCallTask(const TSharedPtr<FUserAccessTokenDomain>& Self, TFunction<void(TArray<Gs2::Dictionary::Model::FLikePtr>)> Callback) : Self(Self), Callback(Callback) {}
    FUserAccessTokenDomain::FSubscribeLikesWithInitialCallTask::FSubscribeLikesWithInitialCallTask(const FSubscribeLikesWithInitialCallTask& From) : TGs2Future(From), Self(From.Self), Callback(From.Callback) {}
    Gs2::Core::Model::FGs2ErrorPtr FUserAccessTokenDomain::FSubscribeLikesWithInitialCallTask::Action(TSharedPtr<TSharedPtr<Gs2::Core::Domain::CallbackID>> Result)
    {
        const auto Task = Gs2::Core::Util::New<FAsyncTask<FCollectLikesTask>>(Self, TFunction<void(TArray<Gs2::Dictionary::Model::FLikePtr>)>());
        Task->StartSynchronousTask(); Task->EnsureCompletion();
        if (Task->GetTask().IsError()) return Task->GetTask().Error();
        const auto Values = Task->GetTask().Result();
        const auto CallbackId = Self->SubscribeLikes(Callback);
        Callback(*Values); *Result = MakeShared<Gs2::Core::Domain::CallbackID>(CallbackId);
        return nullptr;
    }
    TSharedPtr<FAsyncTask<FUserAccessTokenDomain::FSubscribeLikesWithInitialCallTask>> FUserAccessTokenDomain::SubscribeLikesWithInitialCall(TFunction<void(TArray<Gs2::Dictionary::Model::FLikePtr>)> Callback)
    {
        return Gs2::Core::Util::New<FAsyncTask<FSubscribeLikesWithInitialCallTask>>(this->AsShared(), Callback);
    }

    TSharedPtr<Gs2::Dictionary::Domain::Model::FLikeAccessTokenDomain> FUserAccessTokenDomain::Like(
        const FString EntryModelName
    )
    {
        return MakeShared<Gs2::Dictionary::Domain::Model::FLikeAccessTokenDomain>(
            Gs2,
            Service,
            NamespaceName,
            AccessToken,
            EntryModelName == TEXT("") ? TOptional<FString>() : TOptional<FString>(EntryModelName)
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
