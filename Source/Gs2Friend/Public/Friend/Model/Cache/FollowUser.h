#pragma once

#include "Core/Domain/CacheDatabase.h"
#include "Core/Model/Gs2Error.h"
#include "Friend/Model/FollowUser.h"

namespace Gs2::Friend::Model::Cache
{
    class GS2FRIEND_API FFollowUserCache final
    {
    public:
        static FString CreateCacheParentKey(
            TOptional<FString> CacheOwnerArgumentNamespaceName,
            TOptional<FString> CacheOwnerArgumentUserId,
            TOptional<bool> CacheOwnerArgumentWithProfile,
            TOptional<int32> CacheOwnerArgumentTimeOffset = TOptional<int32>()
        );

        static FString CreateCacheKey(
            TOptional<FString> CacheOwnerArgumentTargetUserId
        );

        static bool TryGet(
            const Gs2::Core::Domain::FCacheDatabasePtr& CacheOwnerArgumentCache,
            TOptional<FString> CacheOwnerArgumentNamespaceName,
            TOptional<FString> CacheOwnerArgumentUserId,
            TOptional<bool> CacheOwnerArgumentWithProfile,
            TOptional<FString> CacheOwnerArgumentTargetUserId,
            TOptional<int32> CacheOwnerArgumentTimeOffset,
            Gs2::Friend::Model::FFollowUserPtr* CacheOwnerArgumentOutItem
        );

        static void Put(
            const Gs2::Core::Domain::FCacheDatabasePtr& CacheOwnerArgumentCache,
            TOptional<FString> CacheOwnerArgumentNamespaceName,
            TOptional<FString> CacheOwnerArgumentUserId,
            TOptional<bool> CacheOwnerArgumentWithProfile,
            TOptional<FString> CacheOwnerArgumentTargetUserId,
            TOptional<int32> CacheOwnerArgumentTimeOffset,
            const Gs2::Friend::Model::FFollowUserPtr& CacheOwnerArgumentItem
        );

        static FString PutUserData(
            const Gs2::Core::Domain::FCacheDatabasePtr& Cache,
            TOptional<FString> NamespaceName,
            TOptional<FString> UserId,
            TOptional<int32> TimeOffset,
            const Gs2::Friend::Model::FFollowUserPtr& Item
        );

        static void Delete(
            const Gs2::Core::Domain::FCacheDatabasePtr& CacheOwnerArgumentCache,
            TOptional<FString> CacheOwnerArgumentNamespaceName,
            TOptional<FString> CacheOwnerArgumentUserId,
            TOptional<bool> CacheOwnerArgumentWithProfile,
            TOptional<FString> CacheOwnerArgumentTargetUserId,
            TOptional<int32> CacheOwnerArgumentTimeOffset
        );

        static Gs2::Core::Model::FGs2ErrorPtr Fetch(
            const Gs2::Core::Domain::FCacheDatabasePtr& CacheOwnerArgumentCache,
            TOptional<FString> CacheOwnerArgumentNamespaceName,
            TOptional<FString> CacheOwnerArgumentUserId,
            TOptional<bool> CacheOwnerArgumentWithProfile,
            TOptional<FString> CacheOwnerArgumentTargetUserId,
            TOptional<int32> CacheOwnerArgumentTimeOffset,
            const TFunction<Gs2::Core::Model::FGs2ErrorPtr(Gs2::Friend::Model::FFollowUserPtr*)>& CacheOwnerArgumentFetchImpl,
            Gs2::Friend::Model::FFollowUserPtr* CacheOwnerArgumentOutItem
        );

        static Gs2::Core::Domain::CallbackID ListSubscribe(
            const Gs2::Core::Domain::FCacheDatabasePtr& CacheOwnerArgumentCache,
            TOptional<FString> CacheOwnerArgumentNamespaceName,
            TOptional<FString> CacheOwnerArgumentUserId,
            TOptional<bool> CacheOwnerArgumentWithProfile,
            TOptional<int32> CacheOwnerArgumentTimeOffset,
            TFunction<void(TArray<Gs2::Friend::Model::FFollowUserPtr>)> CacheOwnerArgumentCallback
        );

        static void ListUnsubscribe(
            const Gs2::Core::Domain::FCacheDatabasePtr& CacheOwnerArgumentCache,
            TOptional<FString> CacheOwnerArgumentNamespaceName,
            TOptional<FString> CacheOwnerArgumentUserId,
            TOptional<bool> CacheOwnerArgumentWithProfile,
            TOptional<int32> CacheOwnerArgumentTimeOffset,
            Gs2::Core::Domain::CallbackID CacheOwnerArgumentCallbackID
        );
    };
}