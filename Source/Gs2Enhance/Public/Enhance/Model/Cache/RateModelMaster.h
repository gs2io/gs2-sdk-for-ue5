#pragma once

#include "Core/Domain/CacheDatabase.h"
#include "Core/Model/Gs2Error.h"
#include "Enhance/Model/RateModelMaster.h"

namespace Gs2::Enhance::Model::Cache
{
    class GS2ENHANCE_API FRateModelMasterCache final
    {
    public:
        static FString CreateCacheParentKey(
            TOptional<FString> CacheOwnerArgumentNamespaceName,
            TOptional<int32> CacheOwnerArgumentTimeOffset = TOptional<int32>()
        );

        static FString CreateCacheKey(
            TOptional<FString> CacheOwnerArgumentRateName
        );

        static bool TryGet(
            const Gs2::Core::Domain::FCacheDatabasePtr& CacheOwnerArgumentCache,
            TOptional<FString> CacheOwnerArgumentNamespaceName,
            TOptional<FString> CacheOwnerArgumentRateName,
            TOptional<int32> CacheOwnerArgumentTimeOffset,
            Gs2::Enhance::Model::FRateModelMasterPtr* CacheOwnerArgumentOutItem
        );

        static void Put(
            const Gs2::Core::Domain::FCacheDatabasePtr& CacheOwnerArgumentCache,
            TOptional<FString> CacheOwnerArgumentNamespaceName,
            TOptional<FString> CacheOwnerArgumentRateName,
            TOptional<int32> CacheOwnerArgumentTimeOffset,
            const Gs2::Enhance::Model::FRateModelMasterPtr& CacheOwnerArgumentItem
        );

        static void Delete(
            const Gs2::Core::Domain::FCacheDatabasePtr& CacheOwnerArgumentCache,
            TOptional<FString> CacheOwnerArgumentNamespaceName,
            TOptional<FString> CacheOwnerArgumentRateName,
            TOptional<int32> CacheOwnerArgumentTimeOffset
        );

        static Gs2::Core::Model::FGs2ErrorPtr Fetch(
            const Gs2::Core::Domain::FCacheDatabasePtr& CacheOwnerArgumentCache,
            TOptional<FString> CacheOwnerArgumentNamespaceName,
            TOptional<FString> CacheOwnerArgumentRateName,
            TOptional<int32> CacheOwnerArgumentTimeOffset,
            const TFunction<Gs2::Core::Model::FGs2ErrorPtr(Gs2::Enhance::Model::FRateModelMasterPtr*)>& CacheOwnerArgumentFetchImpl,
            Gs2::Enhance::Model::FRateModelMasterPtr* CacheOwnerArgumentOutItem
        );

        static Gs2::Core::Domain::CallbackID ListSubscribe(
            const Gs2::Core::Domain::FCacheDatabasePtr& CacheOwnerArgumentCache,
            TOptional<FString> CacheOwnerArgumentNamespaceName,
            TOptional<int32> CacheOwnerArgumentTimeOffset,
            TFunction<void(TArray<Gs2::Enhance::Model::FRateModelMasterPtr>)> CacheOwnerArgumentCallback
        );

        static void ListUnsubscribe(
            const Gs2::Core::Domain::FCacheDatabasePtr& CacheOwnerArgumentCache,
            TOptional<FString> CacheOwnerArgumentNamespaceName,
            TOptional<int32> CacheOwnerArgumentTimeOffset,
            Gs2::Core::Domain::CallbackID CacheOwnerArgumentCallbackID
        );
    };
}