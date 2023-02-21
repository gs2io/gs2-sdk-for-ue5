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

#pragma once

#include "CoreMinimal.h"
#include "Core/Gs2Constant.h"

typedef FString FTypeName;
typedef FString FParentCacheKey;
typedef FString FCacheKey;

namespace Gs2::Core::Domain
{
    static int32 DefaultCacheMinutes = 5;
    
    class GS2CORE_API FCacheDatabase
    {
        TMap<FTypeName, TMap<FParentCacheKey, TMap<FCacheKey, TTuple<TSharedPtr<void>, int64>>>> Cache;
        TMap<FTypeName, TMap<FParentCacheKey, bool>> ListCached;

    public:
        FCacheDatabase()
        {
            
        }
        FCacheDatabase(
            const FCacheDatabase& From
        ):
            Cache(From.Cache),
            ListCached(From.ListCached)
        {
            
        }
        
        ~FCacheDatabase() = default;

        void Clear()
        {
            Cache.Reset();
            ListCached.Reset();
        }
        
        template<class TKind>
        bool IsListCached(
            FParentCacheKey ParentKey
        )
        {
            if (!ListCached.Contains(TKind::TypeName))
            {
                ListCached.Add(TKind::TypeName, TMap<FParentCacheKey, bool>());
            }
            return ListCached[TKind::TypeName].Contains(ParentKey);
        }
        
        template<class TKind>
        void SetListCache(
            FParentCacheKey ParentKey
        )
        {
            if (!ListCached.Contains(TKind::TypeName))
            {
                ListCached.Add(TKind::TypeName, TMap<FParentCacheKey, bool>());
            }
            UE_LOG(Gs2Log, Log, TEXT("[%s][%s]: SetListCache"), ToCStr(TKind::TypeName), ToCStr(ParentKey));
            ListCached[TKind::TypeName].Add(ParentKey, true);
        }
        
        template<class TKind>
        void ClearListCache(
            FParentCacheKey ParentKey
        )
        {
            if (!Cache.Contains(TKind::TypeName))
            {
                Cache.Add(TKind::TypeName, TMap<FParentCacheKey, TMap<FCacheKey, TTuple<TSharedPtr<void>, int64>>>());
            }
            if (!Cache[TKind::TypeName].Contains(ParentKey))
            {
                Cache[TKind::TypeName].Add(ParentKey, TMap<FCacheKey, TTuple<TSharedPtr<void>, int64>>());
            }
            Cache[TKind::TypeName][ParentKey].Reset();
            if (!ListCached.Contains(TKind::TypeName))
            {
                ListCached.Add(TKind::TypeName, TMap<FParentCacheKey, bool>());
            }
            UE_LOG(Gs2Log, Log, TEXT("[%s][%s]: ClearListCache"), ToCStr(TKind::TypeName), ToCStr(ParentKey));
            ListCached[TKind::TypeName].Remove(ParentKey);
        }

        template<class TKind>
        void Put(
            FParentCacheKey ParentKey,
            FCacheKey Key,
            TSharedPtr<TKind> Obj,
            FDateTime Ttl
        )
        {
            if (!Cache.Contains(TKind::TypeName))
            {
                Cache.Add(TKind::TypeName, TMap<FParentCacheKey, TMap<FCacheKey, TTuple<TSharedPtr<void>, int64>>>());
            }
            if (!Cache[TKind::TypeName].Contains(ParentKey))
            {
                Cache[TKind::TypeName].Add(ParentKey, TMap<FCacheKey, TTuple<TSharedPtr<void>, int64>>());
            }
            if (Ttl.ToUnixTimestamp() < 0)
            {
                UE_LOG(Gs2Log, Error, TEXT("invalid ttl"))
            }
            UE_LOG(Gs2Log, Log, TEXT("[%s][%s][%s]: Put %p"), ToCStr(TKind::TypeName), ToCStr(ParentKey), ToCStr(Key), &Obj);
            Cache[TKind::TypeName][ParentKey].Add(Key, TTuple<TSharedPtr<void>, int64>(Obj, Ttl.ToUnixTimestamp()));
        }

        template<class TKind>
        void Delete(
            FParentCacheKey ParentKey,
            FCacheKey Key
        )
        {
            if (!Cache.Contains(TKind::TypeName))
            {
                Cache.Add(TKind::TypeName, TMap<FParentCacheKey, TMap<FCacheKey, TTuple<TSharedPtr<void>, int64>>>());
            }
            if (!Cache[TKind::TypeName].Contains(ParentKey))
            {
                Cache[TKind::TypeName].Add(ParentKey, TMap<FCacheKey, TTuple<TSharedPtr<void>, int64>>());
            }
            UE_LOG(Gs2Log, Log, TEXT("[%s][%s][%s]: Remove"), ToCStr(TKind::TypeName), ToCStr(ParentKey), ToCStr(Key));
            Cache[TKind::TypeName][ParentKey].Remove(Key);
        }

        template<class TKind>
        TSharedPtr<TKind> Get(
            FParentCacheKey ParentKey,
            FCacheKey Key
        )
        {
            if (!Cache.Contains(TKind::TypeName))
            {
                Cache.Add(TKind::TypeName, TMap<FParentCacheKey, TMap<FCacheKey, TTuple<TSharedPtr<void>, int64>>>());
            }
            if (!Cache[TKind::TypeName].Contains(ParentKey))
            {
                Cache[TKind::TypeName].Add(ParentKey, TMap<FCacheKey, TTuple<TSharedPtr<void>, int64>>());
            }
            if (!Cache[TKind::TypeName][ParentKey].Contains(Key))
            {
                return nullptr;
            }
            auto Data = Cache[TKind::TypeName][ParentKey][Key];
            if (Data.Value < FDateTime::Now().ToUnixTimestamp())
            {
                Delete<TKind>(
                    ParentKey,
                    Key
                );
                return nullptr;
            }
            if (Data.Key == nullptr)
            {
                return nullptr;
            }
            UE_LOG(Gs2Log, Log, TEXT("[%s][%s][%s]: Get %p"), ToCStr(TKind::TypeName), ToCStr(ParentKey), ToCStr(Key), &Data.Key);
            return *static_cast<TSharedPtr<TKind>*>(static_cast<void*>(&Data.Key));
        }

        template<class TKind>
        TArray<TSharedPtr<TKind>> List(
            FParentCacheKey ParentKey
        )
        {
            if (!Cache.Contains(TKind::TypeName))
            {
                Cache.Add(TKind::TypeName, TMap<FParentCacheKey, TMap<FCacheKey, TTuple<TSharedPtr<void>, int64>>>());
            }
            if (!Cache[TKind::TypeName].Contains(ParentKey))
            {
                Cache[TKind::TypeName].Add(ParentKey, TMap<FCacheKey, TTuple<TSharedPtr<void>, int64>>());
            }
            TArray<TSharedPtr<TKind>> Result;
            for (auto Item : Cache[TKind::TypeName][ParentKey])
            {
                auto Key = Item.Key;
                auto Data = Item.Value;
                if (Data.Value < FDateTime::Now().ToUnixTimestamp())
                {
                    Delete<TKind>(
                        ParentKey,
                        Key
                    );
                    return TArray<TSharedPtr<TKind>>();
                }
                Result.Add(*static_cast<TSharedPtr<TKind>*>(static_cast<void*>(&Data.Key)));
            }
            return Result;
        }
    };
    typedef TSharedPtr<FCacheDatabase> FCacheDatabasePtr;
}