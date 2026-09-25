#pragma once

#include "Core/Domain/CacheDatabase.h"
#include "Core/Model/Gs2Error.h"
#include "Identifier/Model/SecurityPolicy.h"

namespace Gs2::Identifier::Model::Cache
{
    class GS2IDENTIFIER_API FSecurityPolicyCache final
    {
    public:
        static FString CreateCacheParentKey(
            TOptional<int32> CacheOwnerArgumentTimeOffset = TOptional<int32>()
        );

        static FString CreateCacheKey(
            TOptional<FString> CacheOwnerArgumentSecurityPolicyName
        );

        static bool TryGet(
            const Gs2::Core::Domain::FCacheDatabasePtr& CacheOwnerArgumentCache,
            TOptional<FString> CacheOwnerArgumentSecurityPolicyName,
            TOptional<int32> CacheOwnerArgumentTimeOffset,
            Gs2::Identifier::Model::FSecurityPolicyPtr* CacheOwnerArgumentOutItem
        );

        static void Put(
            const Gs2::Core::Domain::FCacheDatabasePtr& CacheOwnerArgumentCache,
            TOptional<FString> CacheOwnerArgumentSecurityPolicyName,
            TOptional<int32> CacheOwnerArgumentTimeOffset,
            const Gs2::Identifier::Model::FSecurityPolicyPtr& CacheOwnerArgumentItem
        );

        static FString PutUserData(
            const Gs2::Core::Domain::FCacheDatabasePtr& Cache,
            TOptional<FString> NamespaceName,
            TOptional<FString> UserId,
            TOptional<int32> TimeOffset,
            const Gs2::Identifier::Model::FSecurityPolicyPtr& Item
        );

        static void Delete(
            const Gs2::Core::Domain::FCacheDatabasePtr& CacheOwnerArgumentCache,
            TOptional<FString> CacheOwnerArgumentSecurityPolicyName,
            TOptional<int32> CacheOwnerArgumentTimeOffset
        );

        static Gs2::Core::Model::FGs2ErrorPtr Fetch(
            const Gs2::Core::Domain::FCacheDatabasePtr& CacheOwnerArgumentCache,
            TOptional<FString> CacheOwnerArgumentSecurityPolicyName,
            TOptional<int32> CacheOwnerArgumentTimeOffset,
            const TFunction<Gs2::Core::Model::FGs2ErrorPtr(Gs2::Identifier::Model::FSecurityPolicyPtr*)>& CacheOwnerArgumentFetchImpl,
            Gs2::Identifier::Model::FSecurityPolicyPtr* CacheOwnerArgumentOutItem
        );

        static Gs2::Core::Domain::CallbackID ListSubscribe(
            const Gs2::Core::Domain::FCacheDatabasePtr& CacheOwnerArgumentCache,
            TOptional<int32> CacheOwnerArgumentTimeOffset,
            TFunction<void(TArray<Gs2::Identifier::Model::FSecurityPolicyPtr>)> CacheOwnerArgumentCallback
        );

        static void ListUnsubscribe(
            const Gs2::Core::Domain::FCacheDatabasePtr& CacheOwnerArgumentCache,
            TOptional<int32> CacheOwnerArgumentTimeOffset,
            Gs2::Core::Domain::CallbackID CacheOwnerArgumentCallbackID
        );
    };
}