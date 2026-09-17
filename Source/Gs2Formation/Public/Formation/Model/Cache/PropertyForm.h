#pragma once

#include "Core/Domain/CacheDatabase.h"
#include "Core/Model/Gs2Error.h"
#include "Formation/Model/PropertyForm.h"

namespace Gs2::Formation::Model::Cache
{
    class GS2FORMATION_API FPropertyFormCache final
    {
    public:
        static FString CreateCacheParentKey(
            TOptional<FString> CacheOwnerArgumentNamespaceName,
            TOptional<FString> CacheOwnerArgumentUserId,
            TOptional<int32> CacheOwnerArgumentTimeOffset = TOptional<int32>()
        );

        static FString CreateCacheKey(
            TOptional<FString> CacheOwnerArgumentPropertyFormModelName,
            TOptional<FString> CacheOwnerArgumentPropertyId
        );

        static bool TryGet(
            const Gs2::Core::Domain::FCacheDatabasePtr& CacheOwnerArgumentCache,
            TOptional<FString> CacheOwnerArgumentNamespaceName,
            TOptional<FString> CacheOwnerArgumentUserId,
            TOptional<FString> CacheOwnerArgumentPropertyFormModelName,
            TOptional<FString> CacheOwnerArgumentPropertyId,
            TOptional<int32> CacheOwnerArgumentTimeOffset,
            Gs2::Formation::Model::FPropertyFormPtr* CacheOwnerArgumentOutItem
        );

        static void Put(
            const Gs2::Core::Domain::FCacheDatabasePtr& CacheOwnerArgumentCache,
            TOptional<FString> CacheOwnerArgumentNamespaceName,
            TOptional<FString> CacheOwnerArgumentUserId,
            TOptional<FString> CacheOwnerArgumentPropertyFormModelName,
            TOptional<FString> CacheOwnerArgumentPropertyId,
            TOptional<int32> CacheOwnerArgumentTimeOffset,
            const Gs2::Formation::Model::FPropertyFormPtr& CacheOwnerArgumentItem
        );

        static void Delete(
            const Gs2::Core::Domain::FCacheDatabasePtr& CacheOwnerArgumentCache,
            TOptional<FString> CacheOwnerArgumentNamespaceName,
            TOptional<FString> CacheOwnerArgumentUserId,
            TOptional<FString> CacheOwnerArgumentPropertyFormModelName,
            TOptional<FString> CacheOwnerArgumentPropertyId,
            TOptional<int32> CacheOwnerArgumentTimeOffset
        );

        static Gs2::Core::Model::FGs2ErrorPtr Fetch(
            const Gs2::Core::Domain::FCacheDatabasePtr& CacheOwnerArgumentCache,
            TOptional<FString> CacheOwnerArgumentNamespaceName,
            TOptional<FString> CacheOwnerArgumentUserId,
            TOptional<FString> CacheOwnerArgumentPropertyFormModelName,
            TOptional<FString> CacheOwnerArgumentPropertyId,
            TOptional<int32> CacheOwnerArgumentTimeOffset,
            const TFunction<Gs2::Core::Model::FGs2ErrorPtr(Gs2::Formation::Model::FPropertyFormPtr*)>& CacheOwnerArgumentFetchImpl,
            Gs2::Formation::Model::FPropertyFormPtr* CacheOwnerArgumentOutItem
        );

        static Gs2::Core::Domain::CallbackID ListSubscribe(
            const Gs2::Core::Domain::FCacheDatabasePtr& CacheOwnerArgumentCache,
            TOptional<FString> CacheOwnerArgumentNamespaceName,
            TOptional<FString> CacheOwnerArgumentUserId,
            TOptional<int32> CacheOwnerArgumentTimeOffset,
            TFunction<void(TArray<Gs2::Formation::Model::FPropertyFormPtr>)> CacheOwnerArgumentCallback
        );

        static void ListUnsubscribe(
            const Gs2::Core::Domain::FCacheDatabasePtr& CacheOwnerArgumentCache,
            TOptional<FString> CacheOwnerArgumentNamespaceName,
            TOptional<FString> CacheOwnerArgumentUserId,
            TOptional<int32> CacheOwnerArgumentTimeOffset,
            Gs2::Core::Domain::CallbackID CacheOwnerArgumentCallbackID
        );
    };
}