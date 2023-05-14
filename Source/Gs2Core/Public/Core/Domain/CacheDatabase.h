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
        TMap<FTypeName, TSet<FParentCacheKey>> ListCached;

    public:
        FCacheDatabase();
        FCacheDatabase(
            const FCacheDatabase& From
        );
        
        ~FCacheDatabase() = default;

        void Clear();
        
        bool IsListCached(
            FTypeName Kind,
            FParentCacheKey ParentKey
        );
        
        void SetListCache(
            FTypeName Kind,
            FParentCacheKey ParentKey
        );
        
        void ClearListCache(
            FTypeName Kind,
            FParentCacheKey ParentKey
        );

        void Put(
            FTypeName Kind,
            FParentCacheKey ParentKey,
            FCacheKey Key,
            TSharedPtr<void> Obj,
            FDateTime Ttl
        );

        void Delete(
            FTypeName Kind,
            FParentCacheKey ParentKey,
            FCacheKey Key
        );

        TSharedPtr<void> Get(
            FTypeName Kind,
            FParentCacheKey ParentKey,
            FCacheKey Key
        );

        template<class TKind>
        TSharedPtr<TKind> Get(
            FParentCacheKey ParentKey,
            FCacheKey Key
        )
        {
            return StaticCastSharedPtr<TKind>(Get(TKind::TypeName, ParentKey, Key));
        }

        template<class TKind>
        TArray<TSharedPtr<TKind>> List(
            FParentCacheKey ParentKey
        )
        {
            auto* Cache0 = Cache.Find(TKind::TypeName);
            if (Cache0 == nullptr) return TArray<TSharedPtr<TKind>>();
            auto* Cache1 = Cache0->Find(ParentKey);
            if (Cache1 == nullptr) return TArray<TSharedPtr<TKind>>();
            TArray<TSharedPtr<TKind>> Result;
            for (auto Item : *Cache1)
            {
                auto Key = Item.Key;
                auto Data = Item.Value;
                if (Data.Value < FDateTime::Now().ToUnixTimestamp())
                {
                    ClearListCache(TKind::TypeName, ParentKey);
                    return TArray<TSharedPtr<TKind>>();
                }
                Result.Add(*static_cast<TSharedPtr<TKind>*>(static_cast<void*>(&Data.Key)));
            }
            return Result;
        }
    };
    typedef TSharedPtr<FCacheDatabase> FCacheDatabasePtr;
}