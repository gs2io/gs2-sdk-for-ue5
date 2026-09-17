#pragma once

#include "Core/Domain/CacheDatabase.h"
#include "Core/Model/Gs2Error.h"
#include "Ranking/Model/Ranking.h"

namespace Gs2::Ranking::Model::Cache
{
    class GS2RANKING_API FRankingCache final
    {
    public:
        static FString CreateCacheParentKey(
            TOptional<FString> CacheOwnerArgumentNamespaceName,
            TOptional<FString> CacheOwnerArgumentUserId,
            TOptional<FString> CacheOwnerArgumentCategoryName,
            TOptional<FString> CacheOwnerArgumentAdditionalScopeName,
            TOptional<int32> CacheOwnerArgumentTimeOffset = TOptional<int32>()
        );

        static FString CreateCacheKey(
            TOptional<FString> CacheOwnerArgumentScorerUserId,
            TOptional<int64> CacheOwnerArgumentIndex
        );

        static bool TryGet(
            const Gs2::Core::Domain::FCacheDatabasePtr& CacheOwnerArgumentCache,
            TOptional<FString> CacheOwnerArgumentNamespaceName,
            TOptional<FString> CacheOwnerArgumentUserId,
            TOptional<FString> CacheOwnerArgumentCategoryName,
            TOptional<FString> CacheOwnerArgumentAdditionalScopeName,
            TOptional<FString> CacheOwnerArgumentScorerUserId,
            TOptional<int64> CacheOwnerArgumentIndex,
            TOptional<int32> CacheOwnerArgumentTimeOffset,
            Gs2::Ranking::Model::FRankingPtr* CacheOwnerArgumentOutItem
        );

        static void Put(
            const Gs2::Core::Domain::FCacheDatabasePtr& CacheOwnerArgumentCache,
            TOptional<FString> CacheOwnerArgumentNamespaceName,
            TOptional<FString> CacheOwnerArgumentUserId,
            TOptional<FString> CacheOwnerArgumentCategoryName,
            TOptional<FString> CacheOwnerArgumentAdditionalScopeName,
            TOptional<FString> CacheOwnerArgumentScorerUserId,
            TOptional<int64> CacheOwnerArgumentIndex,
            TOptional<int32> CacheOwnerArgumentTimeOffset,
            const Gs2::Ranking::Model::FRankingPtr& CacheOwnerArgumentItem
        );

        static void Delete(
            const Gs2::Core::Domain::FCacheDatabasePtr& CacheOwnerArgumentCache,
            TOptional<FString> CacheOwnerArgumentNamespaceName,
            TOptional<FString> CacheOwnerArgumentUserId,
            TOptional<FString> CacheOwnerArgumentCategoryName,
            TOptional<FString> CacheOwnerArgumentAdditionalScopeName,
            TOptional<FString> CacheOwnerArgumentScorerUserId,
            TOptional<int64> CacheOwnerArgumentIndex,
            TOptional<int32> CacheOwnerArgumentTimeOffset
        );

        static Gs2::Core::Model::FGs2ErrorPtr Fetch(
            const Gs2::Core::Domain::FCacheDatabasePtr& CacheOwnerArgumentCache,
            TOptional<FString> CacheOwnerArgumentNamespaceName,
            TOptional<FString> CacheOwnerArgumentUserId,
            TOptional<FString> CacheOwnerArgumentCategoryName,
            TOptional<FString> CacheOwnerArgumentAdditionalScopeName,
            TOptional<FString> CacheOwnerArgumentScorerUserId,
            TOptional<int64> CacheOwnerArgumentIndex,
            TOptional<int32> CacheOwnerArgumentTimeOffset,
            const TFunction<Gs2::Core::Model::FGs2ErrorPtr(Gs2::Ranking::Model::FRankingPtr*)>& CacheOwnerArgumentFetchImpl,
            Gs2::Ranking::Model::FRankingPtr* CacheOwnerArgumentOutItem
        );

        static Gs2::Core::Domain::CallbackID ListSubscribe(
            const Gs2::Core::Domain::FCacheDatabasePtr& CacheOwnerArgumentCache,
            TOptional<FString> CacheOwnerArgumentNamespaceName,
            TOptional<FString> CacheOwnerArgumentUserId,
            TOptional<FString> CacheOwnerArgumentCategoryName,
            TOptional<FString> CacheOwnerArgumentAdditionalScopeName,
            TOptional<int32> CacheOwnerArgumentTimeOffset,
            TFunction<void(TArray<Gs2::Ranking::Model::FRankingPtr>)> CacheOwnerArgumentCallback
        );

        static void ListUnsubscribe(
            const Gs2::Core::Domain::FCacheDatabasePtr& CacheOwnerArgumentCache,
            TOptional<FString> CacheOwnerArgumentNamespaceName,
            TOptional<FString> CacheOwnerArgumentUserId,
            TOptional<FString> CacheOwnerArgumentCategoryName,
            TOptional<FString> CacheOwnerArgumentAdditionalScopeName,
            TOptional<int32> CacheOwnerArgumentTimeOffset,
            Gs2::Core::Domain::CallbackID CacheOwnerArgumentCallbackID
        );
    };
}