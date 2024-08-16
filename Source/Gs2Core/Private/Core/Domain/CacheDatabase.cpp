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

typedef FString FTypeName;
typedef FString FParentCacheKey;
typedef FString FCacheKey;

namespace Gs2::Core::Domain
{

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
{
}

FCacheDatabase::FCacheDatabase(
    const FCacheDatabase& From
):
    Cache(From.Cache),
    CacheUpdateCallback(From.CacheUpdateCallback),
    ListCached(From.ListCached),
    ListCacheUpdateCallback(From.ListCacheUpdateCallback),
    ListCacheUpdateRequired(From.ListCacheUpdateRequired),
    ListUpdateContexts(From.ListUpdateContexts)
{
}

void FCacheDatabase::Clear()
{
    Cache.Reset();
    CacheUpdateCallback.Reset();
    ListCached.Reset();
    ListCacheUpdateCallback.Reset();
    ListCacheUpdateRequired.Reset();
    ListUpdateContexts.Reset();
}

void FCacheDatabase::SetListCached(
    FTypeName Kind,
    FParentCacheKey ParentKey,
    Gs2ObjectPtr UpdateContext
)
{
    Ensure(ListCached, Kind).Add(ParentKey);

    if (UpdateContext)
    {
        auto* ListCacheUpdateRequired0 = ListCacheUpdateRequired.Find(Kind);
        if (ListCacheUpdateRequired0 != nullptr) ListCacheUpdateRequired0->Remove(ParentKey);

        Ensure(ListUpdateContexts, Kind).Add(ParentKey, UpdateContext);
    }
    auto Callbacks = Ensure(ListCacheUpdateCallback, Kind).Find(ParentKey);
    if (Callbacks != nullptr)
    {
        for (auto Callback : *Callbacks)
        {
            UE_LOG(Gs2Log, VeryVerbose, TEXT("[%s][%s]: List Update Callback %d"), ToCStr(Kind), ToCStr(ParentKey), Callback.Key);
            Callback.Value();
        }
    }
}

void FCacheDatabase::SetListCacheUpdateRequired(
    FTypeName Kind,
    FParentCacheKey ParentKey
)
{
    Ensure(ListCacheUpdateRequired, Kind).Add(ParentKey);
}

void FCacheDatabase::ClearListCache(
    FTypeName Kind,
    FParentCacheKey ParentKey
)
{
    UE_LOG(Gs2Log, VeryVerbose, TEXT("[%s][%s]: ClearListCache"), ToCStr(Kind), ToCStr(ParentKey));

    auto* Cache0 = Cache.Find(Kind);
    if (Cache0 != nullptr) Cache0->Remove(ParentKey);

    auto* ListCache0 = ListCached.Find(Kind);
    if (ListCache0 != nullptr) ListCache0->Remove(ParentKey);

    auto* ListCacheUpdateRequired0 = ListCacheUpdateRequired.Find(Kind);
    if (ListCacheUpdateRequired0 != nullptr) ListCacheUpdateRequired0->Remove(ParentKey);

    auto* ListUpdateContexts0 = ListUpdateContexts.Find(Kind);
    if (ListUpdateContexts0 != nullptr) ListUpdateContexts0->Remove(ParentKey);
}

void FCacheDatabase::Put(
    FTypeName Kind,
    FParentCacheKey ParentKey,
    FCacheKey Key,
    Gs2ObjectPtr Obj,
    FDateTime Ttl
)
{
    if (Ttl.ToUnixTimestamp() < 0)
    {
        UE_LOG(Gs2Log, Error, TEXT("invalid ttl"))
    }

    UE_LOG(Gs2Log, VeryVerbose, TEXT("[%s][%s][%s]: Put %p"), ToCStr(Kind), ToCStr(ParentKey), ToCStr(Key), &Obj);
    Ensure(Ensure(Cache, Kind), ParentKey).Add(Key, TTuple<Gs2ObjectPtr, int64>(Obj, Ttl.ToUnixTimestamp()));

    {
        auto Callbacks = Ensure(Ensure(CacheUpdateCallback, Kind), ParentKey).Find(Key);
        if (Callbacks != nullptr)
        {
            for (auto Callback : *Callbacks)
            {
                UE_LOG(Gs2Log, VeryVerbose, TEXT("[%s][%s][%s]: Update Callback %d"), ToCStr(Kind), ToCStr(ParentKey), ToCStr(Key), Callback.Key);
                Callback.Value(Obj);
            }
        }
    }
    {
        auto Callbacks = Ensure(ListCacheUpdateCallback, Kind).Find(ParentKey);
        if (Callbacks != nullptr)
        {
            for (auto Callback : *Callbacks)
            {
                UE_LOG(Gs2Log, VeryVerbose, TEXT("[%s][%s]: List Update Callback %d"), ToCStr(Kind), ToCStr(ParentKey), Callback.Key);
                Callback.Value();
            }
        }
    }
}

void FCacheDatabase::Delete(
    FTypeName Kind,
    FParentCacheKey ParentKey,
    FCacheKey Key
)
{
    auto* Cache0 = Cache.Find(Kind);
    if (Cache0 == nullptr) return;
    auto* Cache1 = Cache0->Find(ParentKey);
    if (Cache1 == nullptr) return;
    UE_LOG(Gs2Log, VeryVerbose, TEXT("[%s][%s][%s]: Remove"), ToCStr(Kind), ToCStr(ParentKey), ToCStr(Key));
    Cache1->Remove(Key);
    {
        auto Callbacks = Ensure(ListCacheUpdateCallback, Kind).Find(ParentKey);
        if (Callbacks != nullptr)
        {
            for (auto Callback : *Callbacks)
            {
                Callback.Value();
            }
        }
    }
}

static CallbackID GCallbackID = 1;

CallbackID FCacheDatabase::Subscribe(FTypeName Kind, FParentCacheKey ParentKey, FCacheKey Key, const TFunction<void(Gs2ObjectPtr)>& Callback)
{
    UE_LOG(Gs2Log, VeryVerbose, TEXT("[%s][%s][%s]: Subscribe(%d)"), ToCStr(Kind), ToCStr(ParentKey), ToCStr(Key), GCallbackID);
    Ensure(Ensure(Ensure(CacheUpdateCallback, Kind), ParentKey), Key).Add(GCallbackID, Callback);
    return GCallbackID++;
}

void FCacheDatabase::Unsubscribe(FTypeName Kind, FParentCacheKey ParentKey, FCacheKey Key, CallbackID CallbackID)
{
    UE_LOG(Gs2Log, VeryVerbose, TEXT("[%s][%s][%s]: Unsubscribe(%d)"), ToCStr(Kind), ToCStr(ParentKey), ToCStr(Key), CallbackID);
    Ensure(Ensure(Ensure(CacheUpdateCallback, Kind), ParentKey), Key).Remove(CallbackID);
}

CallbackID FCacheDatabase::ListSubscribe(FTypeName Kind, FParentCacheKey ParentKey, const TFunction<void()>& Callback)
{
    UE_LOG(Gs2Log, VeryVerbose, TEXT("[%s][%s]: ListSubscribe(%d)"), ToCStr(Kind), ToCStr(ParentKey), GCallbackID);
    Ensure(Ensure(ListCacheUpdateCallback, Kind), ParentKey).Add(GCallbackID, Callback);
    return GCallbackID++;
}

void FCacheDatabase::ListUnsubscribe(FTypeName Kind, FParentCacheKey ParentKey, CallbackID CallbackID)
{
    UE_LOG(Gs2Log, VeryVerbose, TEXT("[%s][%s]: ListUnsubscribe(%d)"), ToCStr(Kind), ToCStr(ParentKey), CallbackID);
    Ensure(Ensure(ListCacheUpdateCallback, Kind), ParentKey).Remove(CallbackID);
}

bool FCacheDatabase::TryGet(
    FTypeName Kind,
    FParentCacheKey ParentKey,
    FCacheKey Key,
    Gs2ObjectPtr* OutObject
)
{
    auto* Cache0 = Cache.Find(Kind);
    if (Cache0 == nullptr) return false;
    auto* Cache1 = Cache0->Find(ParentKey);
    if (Cache1 == nullptr) return false;
    auto* Data = Cache1->Find(Key);
    if (Data == nullptr) return false;
    if (Data->Value < FDateTime::Now().ToUnixTimestamp())
    {
        Delete(Kind, ParentKey, Key);
        return false;
    }
    UE_LOG(Gs2Log, VeryVerbose, TEXT("[%s][%s][%s]: Get %p"), ToCStr(Kind), ToCStr(ParentKey), ToCStr(Key), &Data->Key);
    *OutObject = Data->Key;
    return true;
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