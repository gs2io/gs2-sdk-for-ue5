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
#include "Core/Model/Gs2Error.h"
#include "Misc/ScopeLock.h"

typedef FString FTypeName;
typedef FString FParentCacheKey;
typedef FString FCacheKey;

class FGs2Object;
typedef TSharedPtr<FGs2Object> FGs2ObjectPtr;

namespace Gs2::Core::Domain
{
    using CallbackID = int32;

    // Configure this before starting SDK tasks; concurrent writes are unsupported.
    GS2CORE_API extern int32 DefaultCacheMinutes;
    
    class GS2CORE_API FCacheDatabase
    {
        struct FLockRegistry;

        struct FCacheSubscription
        {
            TFunction<void(FGs2ObjectPtr)> Update;
            TFunction<void()> Refetch;
        };

        struct FListSubscription
        {
            TFunction<void()> Update;
            TFunction<void()> Refetch;
            TFunction<void(const TArray<FGs2ObjectPtr>&)> TypedUpdate;
        };

        mutable FCriticalSection Mutex;
        TMap<FTypeName, TMap<FParentCacheKey, TMap<FCacheKey, TTuple<FGs2ObjectPtr, int64>>>> Cache;
        TMap<FTypeName, TMap<FParentCacheKey, TMap<FCacheKey, TMap<CallbackID, FCacheSubscription>>>> CacheUpdateCallback;
        TMap<FTypeName, TSet<FParentCacheKey>> ListCached;
        TMap<FTypeName, TMap<FParentCacheKey, TMap<CallbackID, FListSubscription>>> ListCacheUpdateCallback;
        TMap<FTypeName, TSet<FParentCacheKey>> ListCacheUpdateRequired;
        TMap<FTypeName, TMap<FParentCacheKey, FGs2ObjectPtr>> ListUpdateContexts;
        TSharedPtr<FLockRegistry> LockRegistry;

        void DispatchNotification(TFunction<void()> Notification);
        void DispatchNotifications(TArray<TFunction<void()>> Notifications);

        TArray<TFunction<void()>> GetListCallbacksLocked(
            FTypeName Kind,
            FParentCacheKey ParentKey
        );

        TArray<TFunction<void()>> GetListRefetchCallbacksLocked(FTypeName Kind, FParentCacheKey ParentKey) const;
        TArray<TFunction<void()>> GetItemRefetchCallbacksLocked(FTypeName Kind, FParentCacheKey ParentKey, FCacheKey Key) const;
        bool TryGetListSnapshot(FTypeName Kind, FParentCacheKey ParentKey, TArray<FGs2ObjectPtr>& Objects, FGs2ObjectPtr* OutUpdateContext, TArray<TFunction<void()>>& RefetchCallbacks);
        void ClearListCacheLocked(FTypeName Kind, FParentCacheKey ParentKey, TArray<TFunction<void()>>& RefetchCallbacks);

    public:
        FCacheDatabase();
        FCacheDatabase(
            const FCacheDatabase& From
        );

        FCacheDatabase& operator=(const FCacheDatabase& From);
        
        ~FCacheDatabase() = default;

        // Keep the returned handle alive for the complete FScopeLock lifetime.
        TSharedPtr<FCriticalSection> GetLockObject(
            FTypeName Kind,
            FParentCacheKey ParentKey,
            FCacheKey Key
        );

        template<class TKind>
        TSharedPtr<FCriticalSection> GetLockObject(
            FParentCacheKey ParentKey,
            FCacheKey Key
        )
        {
            return GetLockObject(TKind::TypeName, ParentKey, Key);
        }

        // Runs a synchronous action under its key lock, then dispatches notifications on this thread.
        // Same-cache nested actions merge notifications until the outer action unlocks.
        // Other-cache operations and work on other threads are not covered; avoid cyclic waits.
        // Keep this cache alive until this call returns and use a consistent nested key order.
        Gs2::Core::Model::FGs2ErrorPtr ExecuteWithKeyLock(
            FTypeName Kind,
            FParentCacheKey ParentKey,
            FCacheKey Key,
            const TFunction<Gs2::Core::Model::FGs2ErrorPtr()>& Action
        );

        void Clear();
        void ClearAndAllUnsubscribe();
        
        void SetListCached(
            FTypeName Kind,
            FParentCacheKey ParentKey,
            FGs2ObjectPtr UpdateContext = nullptr
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
            FGs2ObjectPtr Obj,
            FDateTime Ttl
        );

        CallbackID Subscribe(
            FTypeName Kind,
            FParentCacheKey ParentKey,
            FCacheKey Key,
            const TFunction<void(FGs2ObjectPtr)>& Callback,
            const TFunction<void()>& Refetch = TFunction<void()>()
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
            const TFunction<void()>& Callback,
            const TFunction<void()>& Refetch = TFunction<void()>()
        );

        // Typed list callbacks capture subscription membership at mutation time;
        // values are captured once at dispatch after item updates. Keep this cache
        // alive until the enclosing mutation or ExecuteWithKeyLock returns.
        CallbackID ListSubscribeTyped(
            FTypeName Kind,
            FParentCacheKey ParentKey,
            const TFunction<void(const TArray<FGs2ObjectPtr>&)>& Callback,
            const TFunction<void()>& Refetch = TFunction<void()>()
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
            FGs2ObjectPtr* OutObject
        );

        template<class TKind>
        bool TryGet(
            FParentCacheKey ParentKey,
            FCacheKey Key,
            TSharedPtr<TKind>* OutObject
        )
        {
            FGs2ObjectPtr Out;
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
            FGs2ObjectPtr* OutUpdateContext = nullptr
        )
        {
            TArray<FGs2ObjectPtr> Objects;
            TArray<TFunction<void()>> RefetchCallbacks;
            FGs2ObjectPtr Context;
            const bool Found = TryGetListSnapshot(TKind::TypeName, ParentKey, Objects, &Context, RefetchCallbacks);
            DispatchNotifications(MoveTemp(RefetchCallbacks));
            if (OutUpdateContext) *OutUpdateContext = Context;
            if (!Found) return nullptr;
            auto Result = MakeShared<TArray<TSharedPtr<TKind>>>();
            for (const auto& Object : Objects)
            {
                if (Object) Result->Add(StaticCastSharedPtr<TKind>(Object));
            }
            return Result;
        }
    };
    typedef TSharedPtr<FCacheDatabase> FCacheDatabasePtr;
}
