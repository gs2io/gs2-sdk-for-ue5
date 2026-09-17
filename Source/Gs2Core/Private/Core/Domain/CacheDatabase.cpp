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


#include "Core/Domain/CacheDatabase.h"

#include "Gs2Constant.h"

#include <atomic>

typedef FString FTypeName;
typedef FString FParentCacheKey;
typedef FString FCacheKey;

namespace Gs2::Core::Domain
{

int32 DefaultCacheMinutes = 15;

struct FCacheDatabase::FLockRegistry
{
    struct FLockEntry
    {
        FCriticalSection* Identity = nullptr;
        TWeakPtr<FCriticalSection> Lock;
    };

    FCriticalSection Mutex;
    TMap<FTypeName, TMap<FParentCacheKey, TMap<FCacheKey, FLockEntry>>> Locks;
};

namespace
{
    struct FNotificationBatch;
    thread_local FNotificationBatch* GNotificationBatch = nullptr;

    struct FNotificationBatch
    {
        FCacheDatabase* Cache;
        FNotificationBatch* Parent;
        TArray<TFunction<void()>> Notifications;

        explicit FNotificationBatch(FCacheDatabase* InCache)
            : Cache(InCache), Parent(GNotificationBatch)
        {
            GNotificationBatch = this;
        }

        ~FNotificationBatch()
        {
            GNotificationBatch = Parent;
            for (auto* Batch = Parent; Batch; Batch = Batch->Parent)
            {
                if (Batch->Cache == Cache)
                {
                    Batch->Notifications.Append(MoveTemp(Notifications));
                    return;
                }
            }
            for (auto& Notification : Notifications) Notification();
        }

        FNotificationBatch(const FNotificationBatch&) = delete;
        FNotificationBatch& operator=(const FNotificationBatch&) = delete;
        FNotificationBatch(FNotificationBatch&&) = delete;
        FNotificationBatch& operator=(FNotificationBatch&&) = delete;
    };
}

namespace 
{
    template<class TKey, class TValue>
    TValue& Ensure(TMap<TKey, TValue>&Map, TKey& Key)
    {
        auto* Value = Map.Find(Key);
        if (Value != nullptr) return *Value;
        return Map.Add(Key, TValue());
    }
}

FCacheDatabase::FCacheDatabase()
    : LockRegistry(MakeShared<FLockRegistry>())
{
}

FCacheDatabase::FCacheDatabase(
    const FCacheDatabase& From
)
    : LockRegistry(MakeShared<FLockRegistry>())
{
    FScopeLock Lock(&From.Mutex);
    Cache = From.Cache;
    CacheUpdateCallback = From.CacheUpdateCallback;
    ListCached = From.ListCached;
    ListCacheUpdateCallback = From.ListCacheUpdateCallback;
    ListCacheUpdateRequired = From.ListCacheUpdateRequired;
    ListUpdateContexts = From.ListUpdateContexts;
}

TSharedPtr<FCriticalSection> FCacheDatabase::GetLockObject(
    FTypeName Kind,
    FParentCacheKey ParentKey,
    FCacheKey Key
)
{
    const TSharedPtr<FLockRegistry> State = LockRegistry;
    FScopeLock Lock(&State->Mutex);

    auto& Entry = State->Locks.FindOrAdd(Kind).FindOrAdd(ParentKey).FindOrAdd(Key);
    if (auto Existing = Entry.Lock.Pin()) return Existing;

    TSharedPtr<FCriticalSection> Result = MakeShareable(
        new FCriticalSection(),
        [State, Kind, ParentKey, Key](FCriticalSection* LockObject)
        {
            {
                FScopeLock StateLock(&State->Mutex);
                auto* KindEntries = State->Locks.Find(Kind);
                if (KindEntries)
                {
                    auto* ParentEntries = KindEntries->Find(ParentKey);
                    if (ParentEntries)
                    {
                        auto* LockEntry = ParentEntries->Find(Key);
                        if (LockEntry && LockEntry->Identity == LockObject)
                        {
                            ParentEntries->Remove(Key);
                            if (ParentEntries->Num() == 0)
                            {
                                KindEntries->Remove(ParentKey);
                                if (KindEntries->Num() == 0) State->Locks.Remove(Kind);
                            }
                        }
                    }
                }
            }
            delete LockObject;
        }
    );
    Entry.Identity = Result.Get();
    Entry.Lock = Result;
    return Result;
}

FCacheDatabase& FCacheDatabase::operator=(const FCacheDatabase& From)
{
    if (this == &From) return *this;

    decltype(Cache) NewCache;
    decltype(CacheUpdateCallback) NewCacheUpdateCallback;
    decltype(ListCached) NewListCached;
    decltype(ListCacheUpdateCallback) NewListCacheUpdateCallback;
    decltype(ListCacheUpdateRequired) NewListCacheUpdateRequired;
    decltype(ListUpdateContexts) NewListUpdateContexts;
    {
        FScopeLock Lock(&From.Mutex);
        NewCache = From.Cache;
        NewCacheUpdateCallback = From.CacheUpdateCallback;
        NewListCached = From.ListCached;
        NewListCacheUpdateCallback = From.ListCacheUpdateCallback;
        NewListCacheUpdateRequired = From.ListCacheUpdateRequired;
        NewListUpdateContexts = From.ListUpdateContexts;
    }
    {
        FScopeLock Lock(&Mutex);
        Cache = MoveTemp(NewCache);
        CacheUpdateCallback = MoveTemp(NewCacheUpdateCallback);
        ListCached = MoveTemp(NewListCached);
        ListCacheUpdateCallback = MoveTemp(NewListCacheUpdateCallback);
        ListCacheUpdateRequired = MoveTemp(NewListCacheUpdateRequired);
        ListUpdateContexts = MoveTemp(NewListUpdateContexts);
    }
    return *this;
}

void FCacheDatabase::DispatchNotification(TFunction<void()> Notification)
{
    for (auto* Batch = GNotificationBatch; Batch; Batch = Batch->Parent)
    {
        if (Batch->Cache == this)
        {
            Batch->Notifications.Add(MoveTemp(Notification));
            return;
        }
    }
    Notification();
}

void FCacheDatabase::DispatchNotifications(TArray<TFunction<void()>> Notifications)
{
    for (auto& Notification : Notifications)
    {
        DispatchNotification(MoveTemp(Notification));
    }
}

Gs2::Core::Model::FGs2ErrorPtr FCacheDatabase::ExecuteWithKeyLock(
    FTypeName Kind,
    FParentCacheKey ParentKey,
    FCacheKey Key,
    const TFunction<Gs2::Core::Model::FGs2ErrorPtr()>& Action
)
{
    FNotificationBatch Batch(this);
    Gs2::Core::Model::FGs2ErrorPtr Error;
    {
        TSharedPtr<FCriticalSection> LockObject = GetLockObject(Kind, ParentKey, Key);
        FScopeLock Lock(LockObject.Get());
        Error = Action();
    }
    return Error;
}

void FCacheDatabase::Clear()
{
    TArray<TFunction<void()>> Refetch;
    {
        FScopeLock Lock(&Mutex);
        for (const auto& Kind : CacheUpdateCallback)
            for (const auto& Parent : Kind.Value)
                for (const auto& Key : Parent.Value)
                    for (const auto& Entry : Key.Value)
                        if (Entry.Value.Refetch) Refetch.Add(Entry.Value.Refetch);
        for (const auto& Kind : ListCacheUpdateCallback)
            for (const auto& Parent : Kind.Value)
                for (const auto& Entry : Parent.Value)
                    if (Entry.Value.Refetch) Refetch.Add(Entry.Value.Refetch);
        Cache.Reset(); ListCached.Reset(); ListCacheUpdateRequired.Reset(); ListUpdateContexts.Reset();
    }
    DispatchNotifications(MoveTemp(Refetch));
}

void FCacheDatabase::ClearAndAllUnsubscribe()
{
    FScopeLock Lock(&Mutex);
    Cache.Reset(); CacheUpdateCallback.Reset(); ListCached.Reset();
    ListCacheUpdateCallback.Reset(); ListCacheUpdateRequired.Reset(); ListUpdateContexts.Reset();
}

void FCacheDatabase::SetListCached(
    FTypeName Kind,
    FParentCacheKey ParentKey,
    FGs2ObjectPtr UpdateContext
)
{
    TArray<TFunction<void()>> Callbacks;
    {
        FScopeLock Lock(&Mutex);
        Ensure(ListCached, Kind).Add(ParentKey);
        if (auto* Required = ListCacheUpdateRequired.Find(Kind)) Required->Remove(ParentKey);

        if (UpdateContext)
        {
            Ensure(ListUpdateContexts, Kind).Add(ParentKey, UpdateContext);
        }
        Callbacks = GetListCallbacksLocked(Kind, ParentKey);
    }
    DispatchNotifications(MoveTemp(Callbacks));
}

void FCacheDatabase::SetListCacheUpdateRequired(
    FTypeName Kind,
    FParentCacheKey ParentKey
)
{
    TArray<TFunction<void()>> Refetch;
    {
        FScopeLock Lock(&Mutex);
        Ensure(ListCacheUpdateRequired, Kind).Add(ParentKey);
        auto* Contexts = ListUpdateContexts.Find(Kind);
        if (Contexts == nullptr || !Contexts->Contains(ParentKey))
        {
            ClearListCacheLocked(Kind, ParentKey, Refetch);
        }
        else Refetch = GetListRefetchCallbacksLocked(Kind, ParentKey);
    }
    DispatchNotifications(MoveTemp(Refetch));
}

void FCacheDatabase::ClearListCache(
    FTypeName Kind,
    FParentCacheKey ParentKey
)
{
    TArray<TFunction<void()>> Refetch;
    {
    FScopeLock Lock(&Mutex);
    UE_LOG(Gs2Log, VeryVerbose, TEXT("[%s][%s]: ClearListCache"), ToCStr(Kind), ToCStr(ParentKey));

    ClearListCacheLocked(Kind, ParentKey, Refetch);
    }
    DispatchNotifications(MoveTemp(Refetch));
}

void FCacheDatabase::Put(
    FTypeName Kind,
    FParentCacheKey ParentKey,
    FCacheKey Key,
    FGs2ObjectPtr Obj,
    FDateTime Ttl
)
{
    TArray<TFunction<void(FGs2ObjectPtr)>> ItemCallbacks;
    TArray<TFunction<void()>> ListCallbacks;
    {
        FScopeLock Lock(&Mutex);
        if (Ttl.ToUnixTimestamp() < 0)
        {
            UE_LOG(Gs2Log, Error, TEXT("invalid ttl"))
        }

        UE_LOG(Gs2Log, VeryVerbose, TEXT("[%s][%s][%s]: Put %p"), ToCStr(Kind), ToCStr(ParentKey), ToCStr(Key), &Obj);
        auto& Parent = Ensure(Ensure(Cache, Kind), ParentKey);
        const auto* Existing = Parent.Find(Key);
        const bool Changed = Existing == nullptr || !Existing->Key.IsValid() || Existing->Key != Obj;
        Parent.Add(Key, TTuple<FGs2ObjectPtr, int64>(Obj, Ttl.ToUnixTimestamp()));

        if (Changed)
        {
            if (auto* Callbacks = CacheUpdateCallback.Find(Kind))
                if (auto* Parents = Callbacks->Find(ParentKey))
                    if (auto* Entries = Parents->Find(Key))
                        for (const auto& Callback : *Entries)
                            if (Callback.Value.Update) ItemCallbacks.Add(Callback.Value.Update);
            ListCallbacks = GetListCallbacksLocked(Kind, ParentKey);
        }
    }
    for (auto& Callback : ItemCallbacks)
    {
        DispatchNotification([Callback, Obj] { Callback(Obj); });
    }
    DispatchNotifications(MoveTemp(ListCallbacks));
}

void FCacheDatabase::Delete(
    FTypeName Kind,
    FParentCacheKey ParentKey,
    FCacheKey Key
)
{
    TArray<TFunction<void()>> ListCallbacks;
    TArray<TFunction<void()>> ItemRefetchCallbacks;
    {
        FScopeLock Lock(&Mutex);
        if (auto* Cache0 = Cache.Find(Kind))
        {
            if (auto* Cache1 = Cache0->Find(ParentKey))
            {
                UE_LOG(Gs2Log, VeryVerbose, TEXT("[%s][%s][%s]: Remove"), ToCStr(Kind), ToCStr(ParentKey), ToCStr(Key));
                Cache1->Remove(Key);
                if (Cache1->Num() == 0) Cache0->Remove(ParentKey);
            }
            if (Cache0->Num() == 0) Cache.Remove(Kind);
        }
        ListCallbacks = GetListCallbacksLocked(Kind, ParentKey);
        ItemRefetchCallbacks = GetItemRefetchCallbacksLocked(Kind, ParentKey, Key);
    }
    DispatchNotifications(MoveTemp(ListCallbacks));
    DispatchNotifications(MoveTemp(ItemRefetchCallbacks));
}

static std::atomic<CallbackID> GCallbackID(1);

CallbackID FCacheDatabase::Subscribe(FTypeName Kind, FParentCacheKey ParentKey, FCacheKey Key, const TFunction<void(FGs2ObjectPtr)>& Callback, const TFunction<void()>& Refetch)
{
    const auto CallbackID = GCallbackID.fetch_add(1, std::memory_order_relaxed);
    FScopeLock Lock(&Mutex);
    Ensure(Ensure(Ensure(CacheUpdateCallback, Kind), ParentKey), Key).Add(CallbackID, FCacheSubscription{Callback, Refetch});
    return CallbackID;
}

void FCacheDatabase::Unsubscribe(FTypeName Kind, FParentCacheKey ParentKey, FCacheKey Key, CallbackID CallbackID)
{
    FScopeLock Lock(&Mutex);
    auto* K = CacheUpdateCallback.Find(Kind); if (!K) return;
    auto* P = K->Find(ParentKey); if (!P) return;
    auto* E = P->Find(Key); if (!E) return;
    E->Remove(CallbackID); if (E->Num() == 0) P->Remove(Key); if (P->Num() == 0) K->Remove(ParentKey); if (K->Num() == 0) CacheUpdateCallback.Remove(Kind);
}

CallbackID FCacheDatabase::ListSubscribe(FTypeName Kind, FParentCacheKey ParentKey, const TFunction<void()>& Callback, const TFunction<void()>& Refetch)
{
    const auto CallbackID = GCallbackID.fetch_add(1, std::memory_order_relaxed);
    FScopeLock Lock(&Mutex);
    Ensure(Ensure(ListCacheUpdateCallback, Kind), ParentKey).Add(CallbackID, FListSubscription{Callback, Refetch, TFunction<void(const TArray<FGs2ObjectPtr>&)>()});
    return CallbackID;
}

CallbackID FCacheDatabase::ListSubscribeTyped(
    FTypeName Kind,
    FParentCacheKey ParentKey,
    const TFunction<void(const TArray<FGs2ObjectPtr>&)>& Callback,
    const TFunction<void()>& Refetch
)
{
    const auto CallbackID = GCallbackID.fetch_add(1, std::memory_order_relaxed);
    FScopeLock Lock(&Mutex);
    Ensure(Ensure(ListCacheUpdateCallback, Kind), ParentKey).Add(CallbackID, FListSubscription{TFunction<void()>(), Refetch, Callback});
    return CallbackID;
}

void FCacheDatabase::ListUnsubscribe(FTypeName Kind, FParentCacheKey ParentKey, CallbackID CallbackID)
{
    FScopeLock Lock(&Mutex);
    auto* K = ListCacheUpdateCallback.Find(Kind); if (!K) return;
    auto* P = K->Find(ParentKey); if (!P) return;
    P->Remove(CallbackID); if (P->Num() == 0) K->Remove(ParentKey); if (K->Num() == 0) ListCacheUpdateCallback.Remove(Kind);
}

bool FCacheDatabase::TryGet(
    FTypeName Kind,
    FParentCacheKey ParentKey,
    FCacheKey Key,
    FGs2ObjectPtr* OutObject
)
{
    TArray<TFunction<void()>> ListRefetchCallbacks;
    bool Expired = false;
    {
        FScopeLock Lock(&Mutex);
        if (OutObject) *OutObject = nullptr;
        auto* Cache0 = Cache.Find(Kind);
        if (Cache0 == nullptr) return false;
        auto* Cache1 = Cache0->Find(ParentKey);
        if (Cache1 == nullptr) return false;
        auto* Data = Cache1->Find(Key);
        if (Data == nullptr) return false;
        if (Data->Value < FDateTime::Now().ToUnixTimestamp())
        {
            ClearListCacheLocked(Kind, ParentKey, ListRefetchCallbacks);
            Expired = true;
        }
        else
        {
            if (OutObject) *OutObject = Data->Key;
            return true;
        }
    }
    if (Expired)
    {
        DispatchNotification([this, Kind, ParentKey, Key,
            ListRefetchCallbacks = MoveTemp(ListRefetchCallbacks)]() mutable
        {
            for (auto& Callback : ListRefetchCallbacks) Callback();
            TArray<TFunction<void()>> ListCallbacks;
            TArray<TFunction<void()>> ItemRefetchCallbacks;
            {
                FScopeLock Lock(&Mutex);
                ListCallbacks = GetListCallbacksLocked(Kind, ParentKey);
                ItemRefetchCallbacks = GetItemRefetchCallbacksLocked(Kind, ParentKey, Key);
            }
            DispatchNotifications(MoveTemp(ListCallbacks));
            DispatchNotifications(MoveTemp(ItemRefetchCallbacks));
        });
    }
    return false;
}

TArray<TFunction<void()>> FCacheDatabase::GetListCallbacksLocked(
    FTypeName Kind,
    FParentCacheKey ParentKey
)
{
    TArray<TFunction<void()>> Result;
    const auto* Callbacks0 = ListCacheUpdateCallback.Find(Kind);
    if (Callbacks0 == nullptr) return Result;
    const auto* Callbacks = Callbacks0->Find(ParentKey);
    if (Callbacks == nullptr) return Result;
    bool HasTypedUpdate = false;
    TArray<FListSubscription> Subscriptions;
    for (const auto& Callback : *Callbacks)
    {
        if (Callback.Value.TypedUpdate) HasTypedUpdate = true;
        Subscriptions.Add(Callback.Value);
    }
    if (!HasTypedUpdate)
    {
        for (const auto& Subscription : Subscriptions)
            if (Subscription.Update) Result.Add(Subscription.Update);
        return Result;
    }
    Result.Add([this, Kind, ParentKey, Subscriptions = MoveTemp(Subscriptions)]() mutable
    {
        TArray<FGs2ObjectPtr> Values;
        TArray<TFunction<void()>> RefetchCallbacks;
        if (!TryGetListSnapshot(Kind, ParentKey, Values, nullptr, RefetchCallbacks)) Values.Reset();
        DispatchNotifications(MoveTemp(RefetchCallbacks));
        for (const auto& Subscription : Subscriptions)
        {
            if (Subscription.Update) Subscription.Update();
            if (Subscription.TypedUpdate) Subscription.TypedUpdate(Values);
        }
    });
    return Result;
}

TArray<TFunction<void()>> FCacheDatabase::GetListRefetchCallbacksLocked(FTypeName Kind, FParentCacheKey ParentKey) const
{
    TArray<TFunction<void()>> Result;
    const auto* K = ListCacheUpdateCallback.Find(Kind); if (!K) return Result;
    const auto* P = K->Find(ParentKey); if (!P) return Result;
    for (const auto& Entry : *P) if (Entry.Value.Refetch) Result.Add(Entry.Value.Refetch);
    return Result;
}

void FCacheDatabase::ClearListCacheLocked(FTypeName Kind, FParentCacheKey ParentKey, TArray<TFunction<void()>>& RefetchCallbacks)
{
    if (auto* Cache0 = Cache.Find(Kind))
    {
        Cache0->Remove(ParentKey);
        if (Cache0->Num() == 0) Cache.Remove(Kind);
    }
    if (auto* Cached = ListCached.Find(Kind))
    {
        Cached->Remove(ParentKey);
        if (Cached->Num() == 0) ListCached.Remove(Kind);
    }
    if (auto* Required = ListCacheUpdateRequired.Find(Kind))
    {
        Required->Remove(ParentKey);
        if (Required->Num() == 0) ListCacheUpdateRequired.Remove(Kind);
    }
    if (auto* Contexts = ListUpdateContexts.Find(Kind))
    {
        Contexts->Remove(ParentKey);
        if (Contexts->Num() == 0) ListUpdateContexts.Remove(Kind);
    }
    RefetchCallbacks = GetListRefetchCallbacksLocked(Kind, ParentKey);
}

bool FCacheDatabase::TryGetListSnapshot(
    FTypeName Kind,
    FParentCacheKey ParentKey,
    TArray<FGs2ObjectPtr>& Objects,
    FGs2ObjectPtr* OutUpdateContext,
    TArray<TFunction<void()>>& RefetchCallbacks
)
{
    FScopeLock Lock(&Mutex);
    Objects.Reset();
    RefetchCallbacks.Reset();
    if (OutUpdateContext) *OutUpdateContext = nullptr;
    auto* Cached = ListCached.Find(Kind);
    if (Cached == nullptr || !Cached->Contains(ParentKey)) return false;
    if (OutUpdateContext)
    {
        if (auto* Required = ListCacheUpdateRequired.Find(Kind); Required && Required->Contains(ParentKey))
            if (auto* Contexts = ListUpdateContexts.Find(Kind))
                if (auto* Context = Contexts->Find(ParentKey)) *OutUpdateContext = *Context;
    }
    auto* Parents = Cache.Find(Kind);
    if (Parents == nullptr) return true;
    auto* Entries = Parents->Find(ParentKey);
    if (Entries == nullptr) return true;
    const auto Now = FDateTime::Now().ToUnixTimestamp();
    for (const auto& Entry : *Entries)
    {
        if (Entry.Value.Value < Now)
        {
            if (OutUpdateContext) *OutUpdateContext = nullptr;
            ClearListCacheLocked(Kind, ParentKey, RefetchCallbacks);
            return false;
        }
        if (Entry.Value.Key) Objects.Add(Entry.Value.Key);
    }
    return true;
}

TArray<TFunction<void()>> FCacheDatabase::GetItemRefetchCallbacksLocked(FTypeName Kind, FParentCacheKey ParentKey, FCacheKey Key) const
{
    TArray<TFunction<void()>> Result;
    const auto* K = CacheUpdateCallback.Find(Kind); if (!K) return Result;
    const auto* P = K->Find(ParentKey); if (!P) return Result;
    const auto* E = P->Find(Key); if (!E) return Result;
    for (const auto& Entry : *E) if (Entry.Value.Refetch) Result.Add(Entry.Value.Refetch);
    return Result;
}

// template<class TKind>
// TArray<TSharedPtr<TKind>> List(
//     FTypeName Kind,
//     FParentCacheKey ParentKey
// )
// {
//     auto* Cache0 = Cache.Find(Kind);
//     if (Cache0 == nullptr) return TArray<TSharedPtr<TKind>>();
//     auto* Cache1 = Cache0->Find(ParentKey);
//     if (Cache1 == nullptr) return TArray<TSharedPtr<TKind>>();
//     TArray<TSharedPtr<TKind>> Result;
//     for (auto Item : *Cache1)
//     {
//         auto Key = Item.Key;
//         auto Data = Item.Value;
//         if (Data.Value < FDateTime::Now().ToUnixTimestamp())
//         {
//             ClearListCache(Kind, ParentKey);
//             return TArray<TSharedPtr<TKind>>();
//         }
//         Result.Add(*static_cast<TSharedPtr<TKind>*>(static_cast<Gs2Object*>(&Data.Key)));
//     }
//     return Result;
// }

}
