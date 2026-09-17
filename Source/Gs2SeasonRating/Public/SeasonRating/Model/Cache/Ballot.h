#pragma once

#include "Core/Domain/CacheDatabase.h"
#include "Core/Model/Gs2Error.h"
#include "SeasonRating/Model/Ballot.h"

namespace Gs2::SeasonRating::Model::Cache
{
    class GS2SEASONRATING_API FBallotCache final
    {
    public:
        static FString CreateCacheParentKey(
            TOptional<FString> CacheOwnerArgumentNamespaceName,
            TOptional<FString> CacheOwnerArgumentUserId,
            TOptional<int32> CacheOwnerArgumentTimeOffset = TOptional<int32>()
        );

        static FString CreateCacheKey(
            TOptional<FString> CacheOwnerArgumentSeasonName,
            TOptional<FString> CacheOwnerArgumentSessionName,
            TOptional<int32> CacheOwnerArgumentNumberOfPlayer,
            TOptional<FString> CacheOwnerArgumentKeyId
        );

        static bool TryGet(
            const Gs2::Core::Domain::FCacheDatabasePtr& CacheOwnerArgumentCache,
            TOptional<FString> CacheOwnerArgumentNamespaceName,
            TOptional<FString> CacheOwnerArgumentUserId,
            TOptional<FString> CacheOwnerArgumentSeasonName,
            TOptional<FString> CacheOwnerArgumentSessionName,
            TOptional<int32> CacheOwnerArgumentNumberOfPlayer,
            TOptional<FString> CacheOwnerArgumentKeyId,
            TOptional<int32> CacheOwnerArgumentTimeOffset,
            Gs2::SeasonRating::Model::FBallotPtr* CacheOwnerArgumentOutItem
        );

        static void Put(
            const Gs2::Core::Domain::FCacheDatabasePtr& CacheOwnerArgumentCache,
            TOptional<FString> CacheOwnerArgumentNamespaceName,
            TOptional<FString> CacheOwnerArgumentUserId,
            TOptional<FString> CacheOwnerArgumentSeasonName,
            TOptional<FString> CacheOwnerArgumentSessionName,
            TOptional<int32> CacheOwnerArgumentNumberOfPlayer,
            TOptional<FString> CacheOwnerArgumentKeyId,
            TOptional<int32> CacheOwnerArgumentTimeOffset,
            const Gs2::SeasonRating::Model::FBallotPtr& CacheOwnerArgumentItem
        );

        static void Delete(
            const Gs2::Core::Domain::FCacheDatabasePtr& CacheOwnerArgumentCache,
            TOptional<FString> CacheOwnerArgumentNamespaceName,
            TOptional<FString> CacheOwnerArgumentUserId,
            TOptional<FString> CacheOwnerArgumentSeasonName,
            TOptional<FString> CacheOwnerArgumentSessionName,
            TOptional<int32> CacheOwnerArgumentNumberOfPlayer,
            TOptional<FString> CacheOwnerArgumentKeyId,
            TOptional<int32> CacheOwnerArgumentTimeOffset
        );

        static Gs2::Core::Model::FGs2ErrorPtr Fetch(
            const Gs2::Core::Domain::FCacheDatabasePtr& CacheOwnerArgumentCache,
            TOptional<FString> CacheOwnerArgumentNamespaceName,
            TOptional<FString> CacheOwnerArgumentUserId,
            TOptional<FString> CacheOwnerArgumentSeasonName,
            TOptional<FString> CacheOwnerArgumentSessionName,
            TOptional<int32> CacheOwnerArgumentNumberOfPlayer,
            TOptional<FString> CacheOwnerArgumentKeyId,
            TOptional<int32> CacheOwnerArgumentTimeOffset,
            const TFunction<Gs2::Core::Model::FGs2ErrorPtr(Gs2::SeasonRating::Model::FBallotPtr*)>& CacheOwnerArgumentFetchImpl,
            Gs2::SeasonRating::Model::FBallotPtr* CacheOwnerArgumentOutItem
        );

        static Gs2::Core::Domain::CallbackID ListSubscribe(
            const Gs2::Core::Domain::FCacheDatabasePtr& CacheOwnerArgumentCache,
            TOptional<FString> CacheOwnerArgumentNamespaceName,
            TOptional<FString> CacheOwnerArgumentUserId,
            TOptional<int32> CacheOwnerArgumentTimeOffset,
            TFunction<void(TArray<Gs2::SeasonRating::Model::FBallotPtr>)> CacheOwnerArgumentCallback
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