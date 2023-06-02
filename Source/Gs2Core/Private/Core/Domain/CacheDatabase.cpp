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
    ListCached(From.ListCached)
{
}

void FCacheDatabase::Clear()
{
    Cache.Reset();
    ListCached.Reset();
}

void FCacheDatabase::SetListCache(
    FTypeName Kind,
    FParentCacheKey ParentKey
)
{
    Ensure(ListCached, Kind).Add(ParentKey);
}

void FCacheDatabase::ClearListCache(
    FTypeName Kind,
    FParentCacheKey ParentKey
)
{
    UE_LOG(Gs2Log, Log, TEXT("[%s][%s]: ClearListCache"), ToCStr(Kind), ToCStr(ParentKey));

    auto* Cache0 = Cache.Find(Kind);
    if (Cache0 != nullptr) Cache0->Remove(ParentKey);

    auto* ListCache0 = ListCached.Find(Kind);
    if (ListCache0 != nullptr) ListCache0->Remove(ParentKey);
}

void FCacheDatabase::Put(
    FTypeName Kind,
    FParentCacheKey ParentKey,
    FCacheKey Key,
    TSharedPtr<Gs2Object> Obj,
    FDateTime Ttl
)
{
    if (Ttl.ToUnixTimestamp() < 0)
    {
        UE_LOG(Gs2Log, Error, TEXT("invalid ttl"))
    }

    UE_LOG(Gs2Log, Log, TEXT("[%s][%s][%s]: Put %p"), ToCStr(Kind), ToCStr(ParentKey), ToCStr(Key), &Obj);
    Ensure(Ensure(Cache, Kind), ParentKey).Add(Key, TTuple<TSharedPtr<Gs2Object>, int64>(Obj, Ttl.ToUnixTimestamp()));
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
    UE_LOG(Gs2Log, Log, TEXT("[%s][%s][%s]: Remove"), ToCStr(Kind), ToCStr(ParentKey), ToCStr(Key));
    Cache1->Remove(Key);
}

TSharedPtr<void> FCacheDatabase::Get(
    FTypeName Kind,
    FParentCacheKey ParentKey,
    FCacheKey Key
)
{
    auto* Cache0 = Cache.Find(Kind);
    if (Cache0 == nullptr) return nullptr;
    auto* Cache1 = Cache0->Find(ParentKey);
    if (Cache1 == nullptr) return nullptr;
    auto* Data = Cache1->Find(Key);
    if (Data == nullptr) return nullptr;
    if (Data->Value < FDateTime::Now().ToUnixTimestamp())
    {
        Delete(Kind, ParentKey, Key);
        return nullptr;
    }
    UE_LOG(Gs2Log, Log, TEXT("[%s][%s][%s]: Get %p"), ToCStr(Kind), ToCStr(ParentKey), ToCStr(Key), &Data->Key);
    return Data->Key;
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