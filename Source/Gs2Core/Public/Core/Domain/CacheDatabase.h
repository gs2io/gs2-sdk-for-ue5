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
    using CallbackID = int32;

    static int32 DefaultCacheMinutes = 5;
    
    class GS2CORE_API FCacheDatabase
    {
        TMap<FTypeName, TMap<FParentCacheKey, TMap<FCacheKey, TTuple<TSharedPtr<Gs2Object>, int64>>>> Cache;
        TMap<FTypeName, TMap<FParentCacheKey, TMap<FCacheKey, TMap<CallbackID, TFunction<void(TSharedPtr<Gs2Object>)>>>>> CacheUpdateCallback;
        TMap<FTypeName, TSet<FParentCacheKey>> ListCached;
        TMap<FTypeName, TMap<FParentCacheKey, TMap<CallbackID, TFunction<void()>>>> ListCacheUpdateCallback;
        TMap<FTypeName, TSet<FParentCacheKey>> ListCacheUpdateRequired;
        TMap<FTypeName, TMap<FParentCacheKey, TSharedPtr<Gs2Object>>> ListUpdateContexts;

    public:
        FCacheDatabase();
        FCacheDatabase(
            const FCacheDatabase& From
        );
        
        ~FCacheDatabase() = default;

        void Clear();
        
        void SetListCached(
            FTypeName Kind,
            FParentCacheKey ParentKey,
            TSharedPtr<Gs2Object> UpdateContext = nullptr
        );
        
        void SetListCacheUpdateRequired(
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

        CallbackID Subscribe(
            FTypeName Kind,
            FParentCacheKey ParentKey,
            FCacheKey Key,
            const TFunction<void(TSharedPtr<Gs2Object>)>& Callback
        );

        void Unsubscribe(
            FTypeName Kind,
            FParentCacheKey ParentKey,
            FCacheKey Key,
            CallbackID CallbackID
        );

        CallbackID ListSubscribe(
            FTypeName Kind,
            FParentCacheKey ParentKey,
            const TFunction<void()>& Callback
        );

        void ListUnsubscribe(
            FTypeName Kind,
            FParentCacheKey ParentKey,
            CallbackID CallbackID
        );

        void Delete(
            FTypeName Kind,
            FParentCacheKey ParentKey,
            FCacheKey Key
        );

        bool TryGet(
            FTypeName Kind,
            FParentCacheKey ParentKey,
            FCacheKey Key,
            TSharedPtr<Gs2Object>* OutObject
        );

        template<class TKind>
        bool TryGet(
            FParentCacheKey ParentKey,
            FCacheKey Key,
            TSharedPtr<TKind>* OutObject
        )
        {
            TSharedPtr<Gs2Object> Out;
            auto Result = TryGet(TKind::TypeName, ParentKey, Key, &Out);
            *OutObject = StaticCastSharedPtr<TKind>(Out);
            return Result;
        }

        template<class TKind>
        TSharedPtr<TKind> Get(
            FParentCacheKey ParentKey,
            FCacheKey Key
        )
        {
            TSharedPtr<TKind> Out;
            TryGet<TKind>(ParentKey, Key, &Out);
            return Out;
        }

        template<class TKind>
        TSharedPtr<TArray<TSharedPtr<TKind>>> TryGetList(
            FParentCacheKey ParentKey,
            TSharedPtr<Gs2Object>* OutUpdateContext = nullptr
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
                if (Data.Key)
                {
                    Result->Add(StaticCastSharedPtr<TKind>(Data.Key));
                }
            }

            if (OutUpdateContext)
            {
                *OutUpdateContext = nullptr;

                auto* ListCacheUpdateRequired0 = ListCacheUpdateRequired.Find(TKind::TypeName);
                if (ListCacheUpdateRequired0 && ListCacheUpdateRequired0->Contains(ParentKey))
                {
                    if (auto* ListUpdateContexts0 = ListUpdateContexts.Find(TKind::TypeName))
                    {
                        if (auto* UpdateContext = ListUpdateContexts0->Find(ParentKey))
                        {
                            *OutUpdateContext = *UpdateContext;
                        }
                    }
                }
            }

            return Result;
        }
    };
    typedef TSharedPtr<FCacheDatabase> FCacheDatabasePtr;
}