#pragma once

#include "Core/Domain/CacheDatabase.h"
#include "Core/Model/Gs2Error.h"
#include "MegaField/Model/LayerModel.h"

namespace Gs2::MegaField::Model::Cache
{
    class GS2MEGAFIELD_API FLayerModelCache final
    {
    public:
        static FString CreateCacheParentKey(
            TOptional<FString> CacheOwnerArgumentNamespaceName,
            TOptional<FString> CacheOwnerArgumentAreaModelName,
            TOptional<int32> CacheOwnerArgumentTimeOffset = TOptional<int32>()
        );

        static FString CreateCacheKey(
            TOptional<FString> CacheOwnerArgumentLayerModelName
        );

        static bool TryGet(
            const Gs2::Core::Domain::FCacheDatabasePtr& CacheOwnerArgumentCache,
            TOptional<FString> CacheOwnerArgumentNamespaceName,
            TOptional<FString> CacheOwnerArgumentAreaModelName,
            TOptional<FString> CacheOwnerArgumentLayerModelName,
            TOptional<int32> CacheOwnerArgumentTimeOffset,
            Gs2::MegaField::Model::FLayerModelPtr* CacheOwnerArgumentOutItem
        );

        static void Put(
            const Gs2::Core::Domain::FCacheDatabasePtr& CacheOwnerArgumentCache,
            TOptional<FString> CacheOwnerArgumentNamespaceName,
            TOptional<FString> CacheOwnerArgumentAreaModelName,
            TOptional<FString> CacheOwnerArgumentLayerModelName,
            TOptional<int32> CacheOwnerArgumentTimeOffset,
            const Gs2::MegaField::Model::FLayerModelPtr& CacheOwnerArgumentItem
        );

        static void Delete(
            const Gs2::Core::Domain::FCacheDatabasePtr& CacheOwnerArgumentCache,
            TOptional<FString> CacheOwnerArgumentNamespaceName,
            TOptional<FString> CacheOwnerArgumentAreaModelName,
            TOptional<FString> CacheOwnerArgumentLayerModelName,
            TOptional<int32> CacheOwnerArgumentTimeOffset
        );

        static Gs2::Core::Model::FGs2ErrorPtr Fetch(
            const Gs2::Core::Domain::FCacheDatabasePtr& CacheOwnerArgumentCache,
            TOptional<FString> CacheOwnerArgumentNamespaceName,
            TOptional<FString> CacheOwnerArgumentAreaModelName,
            TOptional<FString> CacheOwnerArgumentLayerModelName,
            TOptional<int32> CacheOwnerArgumentTimeOffset,
            const TFunction<Gs2::Core::Model::FGs2ErrorPtr(Gs2::MegaField::Model::FLayerModelPtr*)>& CacheOwnerArgumentFetchImpl,
            Gs2::MegaField::Model::FLayerModelPtr* CacheOwnerArgumentOutItem
        );

        static Gs2::Core::Domain::CallbackID ListSubscribe(
            const Gs2::Core::Domain::FCacheDatabasePtr& CacheOwnerArgumentCache,
            TOptional<FString> CacheOwnerArgumentNamespaceName,
            TOptional<FString> CacheOwnerArgumentAreaModelName,
            TOptional<int32> CacheOwnerArgumentTimeOffset,
            TFunction<void(TArray<Gs2::MegaField::Model::FLayerModelPtr>)> CacheOwnerArgumentCallback
        );

        static void ListUnsubscribe(
            const Gs2::Core::Domain::FCacheDatabasePtr& CacheOwnerArgumentCache,
            TOptional<FString> CacheOwnerArgumentNamespaceName,
            TOptional<FString> CacheOwnerArgumentAreaModelName,
            TOptional<int32> CacheOwnerArgumentTimeOffset,
            Gs2::Core::Domain::CallbackID CacheOwnerArgumentCallbackID
        );
    };
}