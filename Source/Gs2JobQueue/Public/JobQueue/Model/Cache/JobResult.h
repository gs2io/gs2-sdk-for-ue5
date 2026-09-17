#pragma once

#include "Core/Domain/CacheDatabase.h"
#include "Core/Model/Gs2Error.h"
#include "JobQueue/Model/JobResult.h"

namespace Gs2::JobQueue::Model::Cache
{
    class GS2JOBQUEUE_API FJobResultCache final
    {
    public:
        static FString CreateCacheParentKey(
            TOptional<FString> CacheOwnerArgumentNamespaceName,
            TOptional<FString> CacheOwnerArgumentUserId,
            TOptional<FString> CacheOwnerArgumentJobName,
            TOptional<int32> CacheOwnerArgumentTimeOffset = TOptional<int32>()
        );

        static FString CreateCacheKey(
            TOptional<int32> CacheOwnerArgumentTryNumber
        );

        static bool TryGet(
            const Gs2::Core::Domain::FCacheDatabasePtr& CacheOwnerArgumentCache,
            TOptional<FString> CacheOwnerArgumentNamespaceName,
            TOptional<FString> CacheOwnerArgumentUserId,
            TOptional<FString> CacheOwnerArgumentJobName,
            TOptional<int32> CacheOwnerArgumentTryNumber,
            TOptional<int32> CacheOwnerArgumentTimeOffset,
            Gs2::JobQueue::Model::FJobResultPtr* CacheOwnerArgumentOutItem
        );

        static void Put(
            const Gs2::Core::Domain::FCacheDatabasePtr& CacheOwnerArgumentCache,
            TOptional<FString> CacheOwnerArgumentNamespaceName,
            TOptional<FString> CacheOwnerArgumentUserId,
            TOptional<FString> CacheOwnerArgumentJobName,
            TOptional<int32> CacheOwnerArgumentTryNumber,
            TOptional<int32> CacheOwnerArgumentTimeOffset,
            const Gs2::JobQueue::Model::FJobResultPtr& CacheOwnerArgumentItem
        );

        static void Delete(
            const Gs2::Core::Domain::FCacheDatabasePtr& CacheOwnerArgumentCache,
            TOptional<FString> CacheOwnerArgumentNamespaceName,
            TOptional<FString> CacheOwnerArgumentUserId,
            TOptional<FString> CacheOwnerArgumentJobName,
            TOptional<int32> CacheOwnerArgumentTryNumber,
            TOptional<int32> CacheOwnerArgumentTimeOffset
        );

        static Gs2::Core::Model::FGs2ErrorPtr Fetch(
            const Gs2::Core::Domain::FCacheDatabasePtr& CacheOwnerArgumentCache,
            TOptional<FString> CacheOwnerArgumentNamespaceName,
            TOptional<FString> CacheOwnerArgumentUserId,
            TOptional<FString> CacheOwnerArgumentJobName,
            TOptional<int32> CacheOwnerArgumentTryNumber,
            TOptional<int32> CacheOwnerArgumentTimeOffset,
            const TFunction<Gs2::Core::Model::FGs2ErrorPtr(Gs2::JobQueue::Model::FJobResultPtr*)>& CacheOwnerArgumentFetchImpl,
            Gs2::JobQueue::Model::FJobResultPtr* CacheOwnerArgumentOutItem
        );

        static Gs2::Core::Domain::CallbackID ListSubscribe(
            const Gs2::Core::Domain::FCacheDatabasePtr& CacheOwnerArgumentCache,
            TOptional<FString> CacheOwnerArgumentNamespaceName,
            TOptional<FString> CacheOwnerArgumentUserId,
            TOptional<FString> CacheOwnerArgumentJobName,
            TOptional<int32> CacheOwnerArgumentTimeOffset,
            TFunction<void(TArray<Gs2::JobQueue::Model::FJobResultPtr>)> CacheOwnerArgumentCallback
        );

        static void ListUnsubscribe(
            const Gs2::Core::Domain::FCacheDatabasePtr& CacheOwnerArgumentCache,
            TOptional<FString> CacheOwnerArgumentNamespaceName,
            TOptional<FString> CacheOwnerArgumentUserId,
            TOptional<FString> CacheOwnerArgumentJobName,
            TOptional<int32> CacheOwnerArgumentTimeOffset,
            Gs2::Core::Domain::CallbackID CacheOwnerArgumentCallbackID
        );
    };
}