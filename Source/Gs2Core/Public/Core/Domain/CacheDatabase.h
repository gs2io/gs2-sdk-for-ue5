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
#include "Core/Gs2Object.h"
#include "Core/Gs2Constant.h"

typedef FString FTypeName;
typedef FString FParentCacheKey;
typedef FString FCacheKey;

namespace Gs2::Core::Domain
{
    static int32 DefaultCacheMinutes = 5;
    
    class GS2CORE_API FCacheDatabase
    {
        TMap<FTypeName, TMap<FParentCacheKey, TMap<FCacheKey, TTuple<TSharedPtr<Gs2Object>, int64>>>> Cache;
        TMap<FTypeName, TSet<FParentCacheKey>> ListCached;

    public:
        FCacheDatabase();
        FCacheDatabase(
            const FCacheDatabase& From
        );
        
        ~FCacheDatabase() = default;

        void Clear();
        
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
            TSharedPtr<Gs2Object> Obj,
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
        TSharedPtr<TArray<TSharedPtr<TKind>>> TryGetList(
            FParentCacheKey ParentKey
        )
        {
            auto* ListCache0 = ListCached.Find(TKind::TypeName);
            if (ListCache0 == nullptr || !ListCache0->Contains(ParentKey)) return nullptr;

            auto* Cache0 = Cache.Find(TKind::TypeName);
            if (Cache0 == nullptr) return nullptr;
            auto* Cache1 = Cache0->Find(ParentKey);
            if (Cache1 == nullptr) return nullptr;
            auto now = FDateTime::Now().ToUnixTimestamp();
            auto Result = MakeShared<TArray<TSharedPtr<TKind>>>();
            for (auto Item : *Cache1)
            {
                auto Key = Item.Key;
                auto Data = Item.Value;
                if (Data.Value < now)
                {
                    ClearListCache(TKind::TypeName, ParentKey);
                    return nullptr;
                }
                Result->Add(StaticCastSharedPtr<TKind>(Data.Key));
            }
            return Result;
        }
    };
    typedef TSharedPtr<FCacheDatabase> FCacheDatabasePtr;
}