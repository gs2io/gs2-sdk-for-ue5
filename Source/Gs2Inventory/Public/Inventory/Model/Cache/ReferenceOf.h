#pragma once

#include "Core/Domain/CacheDatabase.h"
#include "Core/Model/Gs2Error.h"
#include "Inventory/Model/ReferenceOf.h"

namespace Gs2::Inventory::Model::Cache
{
    class GS2INVENTORY_API FReferenceOfCache final
    {
    public:
        static FString CreateCacheParentKey(
            TOptional<FString> CacheOwnerArgumentNamespaceName,
            TOptional<FString> CacheOwnerArgumentUserId,
            TOptional<FString> CacheOwnerArgumentInventoryName,
            TOptional<FString> CacheOwnerArgumentItemName,
            TOptional<FString> CacheOwnerArgumentItemSetName,
            TOptional<int32> CacheOwnerArgumentTimeOffset = TOptional<int32>()
        );

        static FString CreateCacheKey(
            TOptional<FString> CacheOwnerArgumentReferenceOf
        );

        static bool TryGet(
            const Gs2::Core::Domain::FCacheDatabasePtr& CacheOwnerArgumentCache,
            TOptional<FString> CacheOwnerArgumentNamespaceName,
            TOptional<FString> CacheOwnerArgumentUserId,
            TOptional<FString> CacheOwnerArgumentInventoryName,
            TOptional<FString> CacheOwnerArgumentItemName,
            TOptional<FString> CacheOwnerArgumentItemSetName,
            TOptional<FString> CacheOwnerArgumentReferenceOf,
            TOptional<int32> CacheOwnerArgumentTimeOffset,
            Gs2::Inventory::Model::FReferenceOfPtr* CacheOwnerArgumentOutItem
        );

        static void Put(
            const Gs2::Core::Domain::FCacheDatabasePtr& CacheOwnerArgumentCache,
            TOptional<FString> CacheOwnerArgumentNamespaceName,
            TOptional<FString> CacheOwnerArgumentUserId,
            TOptional<FString> CacheOwnerArgumentInventoryName,
            TOptional<FString> CacheOwnerArgumentItemName,
            TOptional<FString> CacheOwnerArgumentItemSetName,
            TOptional<FString> CacheOwnerArgumentReferenceOf,
            TOptional<int32> CacheOwnerArgumentTimeOffset,
            const Gs2::Inventory::Model::FReferenceOfPtr& CacheOwnerArgumentItem
        );

        static FString PutUserData(
            const Gs2::Core::Domain::FCacheDatabasePtr& Cache,
            TOptional<FString> NamespaceName,
            TOptional<FString> UserId,
            TOptional<int32> TimeOffset,
            const Gs2::Inventory::Model::FReferenceOfPtr& Item
        );

        static void Delete(
            const Gs2::Core::Domain::FCacheDatabasePtr& CacheOwnerArgumentCache,
            TOptional<FString> CacheOwnerArgumentNamespaceName,
            TOptional<FString> CacheOwnerArgumentUserId,
            TOptional<FString> CacheOwnerArgumentInventoryName,
            TOptional<FString> CacheOwnerArgumentItemName,
            TOptional<FString> CacheOwnerArgumentItemSetName,
            TOptional<FString> CacheOwnerArgumentReferenceOf,
            TOptional<int32> CacheOwnerArgumentTimeOffset
        );

        static Gs2::Core::Model::FGs2ErrorPtr Fetch(
            const Gs2::Core::Domain::FCacheDatabasePtr& CacheOwnerArgumentCache,
            TOptional<FString> CacheOwnerArgumentNamespaceName,
            TOptional<FString> CacheOwnerArgumentUserId,
            TOptional<FString> CacheOwnerArgumentInventoryName,
            TOptional<FString> CacheOwnerArgumentItemName,
            TOptional<FString> CacheOwnerArgumentItemSetName,
            TOptional<FString> CacheOwnerArgumentReferenceOf,
            TOptional<int32> CacheOwnerArgumentTimeOffset,
            const TFunction<Gs2::Core::Model::FGs2ErrorPtr(Gs2::Inventory::Model::FReferenceOfPtr*)>& CacheOwnerArgumentFetchImpl,
            Gs2::Inventory::Model::FReferenceOfPtr* CacheOwnerArgumentOutItem
        );

        static Gs2::Core::Domain::CallbackID ListSubscribe(
            const Gs2::Core::Domain::FCacheDatabasePtr& CacheOwnerArgumentCache,
            TOptional<FString> CacheOwnerArgumentNamespaceName,
            TOptional<FString> CacheOwnerArgumentUserId,
            TOptional<FString> CacheOwnerArgumentInventoryName,
            TOptional<FString> CacheOwnerArgumentItemName,
            TOptional<FString> CacheOwnerArgumentItemSetName,
            TOptional<int32> CacheOwnerArgumentTimeOffset,
            TFunction<void(TArray<Gs2::Inventory::Model::FReferenceOfPtr>)> CacheOwnerArgumentCallback
        );

        static void ListUnsubscribe(
            const Gs2::Core::Domain::FCacheDatabasePtr& CacheOwnerArgumentCache,
            TOptional<FString> CacheOwnerArgumentNamespaceName,
            TOptional<FString> CacheOwnerArgumentUserId,
            TOptional<FString> CacheOwnerArgumentInventoryName,
            TOptional<FString> CacheOwnerArgumentItemName,
            TOptional<FString> CacheOwnerArgumentItemSetName,
            TOptional<int32> CacheOwnerArgumentTimeOffset,
            Gs2::Core::Domain::CallbackID CacheOwnerArgumentCallbackID
        );
    };
}