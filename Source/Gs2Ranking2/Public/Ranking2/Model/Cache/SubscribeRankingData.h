#pragma once

#include "Core/Domain/CacheDatabase.h"
#include "Core/Model/Gs2Error.h"
#include "Ranking2/Model/SubscribeRankingData.h"

namespace Gs2::Ranking2::Model::Cache
{
    class GS2RANKING2_API FSubscribeRankingDataCache final
    {
    public:
        static FString CreateCacheParentKey(
            TOptional<FString> CacheOwnerArgumentNamespaceName,
            TOptional<FString> CacheOwnerArgumentRankingName,
            TOptional<int64> CacheOwnerArgumentSeason,
            TOptional<int32> CacheOwnerArgumentTimeOffset = TOptional<int32>()
        );

        static FString CreateCacheKey(
            TOptional<FString> CacheOwnerArgumentRankingName,
            TOptional<FString> CacheOwnerArgumentScorerUserId
        );

        static bool TryGet(
            const Gs2::Core::Domain::FCacheDatabasePtr& CacheOwnerArgumentCache,
            TOptional<FString> CacheOwnerArgumentNamespaceName,
            TOptional<FString> CacheOwnerArgumentRankingName,
            TOptional<int64> CacheOwnerArgumentSeason,
            TOptional<FString> CacheOwnerArgumentScorerUserId,
            TOptional<int32> CacheOwnerArgumentTimeOffset,
            Gs2::Ranking2::Model::FSubscribeRankingDataPtr* CacheOwnerArgumentOutItem
        );

        static void Put(
            const Gs2::Core::Domain::FCacheDatabasePtr& CacheOwnerArgumentCache,
            TOptional<FString> CacheOwnerArgumentNamespaceName,
            TOptional<FString> CacheOwnerArgumentRankingName,
            TOptional<int64> CacheOwnerArgumentSeason,
            TOptional<FString> CacheOwnerArgumentScorerUserId,
            TOptional<int32> CacheOwnerArgumentTimeOffset,
            const Gs2::Ranking2::Model::FSubscribeRankingDataPtr& CacheOwnerArgumentItem
        );

        static FString PutUserData(
            const Gs2::Core::Domain::FCacheDatabasePtr& Cache,
            TOptional<FString> NamespaceName,
            TOptional<FString> UserId,
            TOptional<int32> TimeOffset,
            const Gs2::Ranking2::Model::FSubscribeRankingDataPtr& Item
        );

        static void Delete(
            const Gs2::Core::Domain::FCacheDatabasePtr& CacheOwnerArgumentCache,
            TOptional<FString> CacheOwnerArgumentNamespaceName,
            TOptional<FString> CacheOwnerArgumentRankingName,
            TOptional<int64> CacheOwnerArgumentSeason,
            TOptional<FString> CacheOwnerArgumentScorerUserId,
            TOptional<int32> CacheOwnerArgumentTimeOffset
        );

        static Gs2::Core::Model::FGs2ErrorPtr Fetch(
            const Gs2::Core::Domain::FCacheDatabasePtr& CacheOwnerArgumentCache,
            TOptional<FString> CacheOwnerArgumentNamespaceName,
            TOptional<FString> CacheOwnerArgumentRankingName,
            TOptional<int64> CacheOwnerArgumentSeason,
            TOptional<FString> CacheOwnerArgumentScorerUserId,
            TOptional<int32> CacheOwnerArgumentTimeOffset,
            const TFunction<Gs2::Core::Model::FGs2ErrorPtr(Gs2::Ranking2::Model::FSubscribeRankingDataPtr*)>& CacheOwnerArgumentFetchImpl,
            Gs2::Ranking2::Model::FSubscribeRankingDataPtr* CacheOwnerArgumentOutItem
        );

        static Gs2::Core::Domain::CallbackID ListSubscribe(
            const Gs2::Core::Domain::FCacheDatabasePtr& CacheOwnerArgumentCache,
            TOptional<FString> CacheOwnerArgumentNamespaceName,
            TOptional<FString> CacheOwnerArgumentRankingName,
            TOptional<int64> CacheOwnerArgumentSeason,
            TOptional<int32> CacheOwnerArgumentTimeOffset,
            TFunction<void(TArray<Gs2::Ranking2::Model::FSubscribeRankingDataPtr>)> CacheOwnerArgumentCallback
        );

        static void ListUnsubscribe(
            const Gs2::Core::Domain::FCacheDatabasePtr& CacheOwnerArgumentCache,
            TOptional<FString> CacheOwnerArgumentNamespaceName,
            TOptional<FString> CacheOwnerArgumentRankingName,
            TOptional<int64> CacheOwnerArgumentSeason,
            TOptional<int32> CacheOwnerArgumentTimeOffset,
            Gs2::Core::Domain::CallbackID CacheOwnerArgumentCallbackID
        );
    };
}