#pragma once

// deny overwrite



#include "Core/Domain/CacheDatabase.h"
#include "Core/Model/Gs2Error.h"
#include "Guild/Model/SendMemberRequest.h"

namespace Gs2::Guild::Model::Cache
{
    class GS2GUILD_API FSendMemberRequestCache final
    {
    public:
        static FString CreateCacheParentKey(
            TOptional<FString> CacheOwnerArgumentNamespaceName,
            TOptional<FString> CacheOwnerArgumentGuildModelName,

            TOptional<FString> CacheOwnerArgumentUserId,
            TOptional<int32> CacheOwnerArgumentTimeOffset = TOptional<int32>()
        );

        static FString CreateCacheKey(
            TOptional<FString> CacheOwnerArgumentGuildName
        );

        static bool TryGet(
            const Gs2::Core::Domain::FCacheDatabasePtr& CacheOwnerArgumentCache,
            TOptional<FString> CacheOwnerArgumentNamespaceName,
            TOptional<FString> CacheOwnerArgumentUserId,
            TOptional<FString> CacheOwnerArgumentGuildModelName,
            TOptional<FString> CacheOwnerArgumentGuildName,
            TOptional<int32> CacheOwnerArgumentTimeOffset,
            Gs2::Guild::Model::FSendMemberRequestPtr* CacheOwnerArgumentOutItem
        );

        static void Put(
            const Gs2::Core::Domain::FCacheDatabasePtr& CacheOwnerArgumentCache,
            TOptional<FString> CacheOwnerArgumentNamespaceName,
            TOptional<FString> CacheOwnerArgumentUserId,
            TOptional<FString> CacheOwnerArgumentGuildModelName,
            TOptional<FString> CacheOwnerArgumentGuildName,
            TOptional<int32> CacheOwnerArgumentTimeOffset,
            const Gs2::Guild::Model::FSendMemberRequestPtr& CacheOwnerArgumentItem
        );

        static void Delete(
            const Gs2::Core::Domain::FCacheDatabasePtr& CacheOwnerArgumentCache,
            TOptional<FString> CacheOwnerArgumentNamespaceName,
            TOptional<FString> CacheOwnerArgumentUserId,
            TOptional<FString> CacheOwnerArgumentGuildModelName,
            TOptional<FString> CacheOwnerArgumentGuildName,
            TOptional<int32> CacheOwnerArgumentTimeOffset
        );

        static Gs2::Core::Model::FGs2ErrorPtr Fetch(
            const Gs2::Core::Domain::FCacheDatabasePtr& CacheOwnerArgumentCache,
            TOptional<FString> CacheOwnerArgumentNamespaceName,
            TOptional<FString> CacheOwnerArgumentUserId,
            TOptional<FString> CacheOwnerArgumentGuildModelName,
            TOptional<FString> CacheOwnerArgumentGuildName,
            TOptional<int32> CacheOwnerArgumentTimeOffset,
            const TFunction<Gs2::Core::Model::FGs2ErrorPtr(Gs2::Guild::Model::FSendMemberRequestPtr*)>& CacheOwnerArgumentFetchImpl,
            Gs2::Guild::Model::FSendMemberRequestPtr* CacheOwnerArgumentOutItem
        );

        static Gs2::Core::Domain::CallbackID ListSubscribe(
            const Gs2::Core::Domain::FCacheDatabasePtr& CacheOwnerArgumentCache,
            TOptional<FString> CacheOwnerArgumentNamespaceName,
            TOptional<FString> CacheOwnerArgumentGuildModelName,

            TOptional<FString> CacheOwnerArgumentUserId,
            TOptional<int32> CacheOwnerArgumentTimeOffset,
            TFunction<void(TArray<Gs2::Guild::Model::FSendMemberRequestPtr>)> CacheOwnerArgumentCallback
        );

        static void ListUnsubscribe(
            const Gs2::Core::Domain::FCacheDatabasePtr& CacheOwnerArgumentCache,
            TOptional<FString> CacheOwnerArgumentNamespaceName,
            TOptional<FString> CacheOwnerArgumentGuildModelName,

            TOptional<FString> CacheOwnerArgumentUserId,
            TOptional<int32> CacheOwnerArgumentTimeOffset,
            Gs2::Core::Domain::CallbackID CacheOwnerArgumentCallbackID
        );
    };
}
