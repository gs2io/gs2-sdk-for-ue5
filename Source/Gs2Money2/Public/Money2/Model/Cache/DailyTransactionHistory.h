#pragma once

#include "Core/Domain/CacheDatabase.h"
#include "Core/Model/Gs2Error.h"
#include "Money2/Model/DailyTransactionHistory.h"

namespace Gs2::Money2::Model::Cache
{
    class GS2MONEY2_API FDailyTransactionHistoryCache final
    {
    public:
        static FString CreateCacheParentKey(
            TOptional<FString> CacheOwnerArgumentNamespaceName,
            TOptional<int32> CacheOwnerArgumentTimeOffset = TOptional<int32>()
        );

        static FString CreateCacheKey(
            TOptional<int32> CacheOwnerArgumentYear,
            TOptional<int32> CacheOwnerArgumentMonth,
            TOptional<int32> CacheOwnerArgumentDay,
            TOptional<FString> CacheOwnerArgumentCurrency
        );

        static bool TryGet(
            const Gs2::Core::Domain::FCacheDatabasePtr& CacheOwnerArgumentCache,
            TOptional<FString> CacheOwnerArgumentNamespaceName,
            TOptional<int32> CacheOwnerArgumentYear,
            TOptional<int32> CacheOwnerArgumentMonth,
            TOptional<int32> CacheOwnerArgumentDay,
            TOptional<FString> CacheOwnerArgumentCurrency,
            TOptional<int32> CacheOwnerArgumentTimeOffset,
            Gs2::Money2::Model::FDailyTransactionHistoryPtr* CacheOwnerArgumentOutItem
        );

        static void Put(
            const Gs2::Core::Domain::FCacheDatabasePtr& CacheOwnerArgumentCache,
            TOptional<FString> CacheOwnerArgumentNamespaceName,
            TOptional<int32> CacheOwnerArgumentYear,
            TOptional<int32> CacheOwnerArgumentMonth,
            TOptional<int32> CacheOwnerArgumentDay,
            TOptional<FString> CacheOwnerArgumentCurrency,
            TOptional<int32> CacheOwnerArgumentTimeOffset,
            const Gs2::Money2::Model::FDailyTransactionHistoryPtr& CacheOwnerArgumentItem
        );

        // Gs2Distributor:DescribeUserData（ユーザーの全データの一括取得）の 1 エントリ（この kind）をキャッシュへ入れる。
        // 鍵はエントリの namespaceName / 読み込むユーザーの userId / モデル自身のプロパティ / 主キー GRN から取る
        // （sdk-gen の BaseModel.user_data_cache_keys）。戻り値は親キーで、呼び手が全ページを読み終えてから
        // FGs2Money2Domain::SetListCached(TimeOffset, Kind, ParentKey) で「リストが揃った印」を立てる。
        static FString PutUserData(
            const Gs2::Core::Domain::FCacheDatabasePtr& Cache,
            TOptional<FString> NamespaceName,
            TOptional<FString> UserId,
            TOptional<int32> TimeOffset,
            const Gs2::Money2::Model::FDailyTransactionHistoryPtr& Item
        );

        static void Delete(
            const Gs2::Core::Domain::FCacheDatabasePtr& CacheOwnerArgumentCache,
            TOptional<FString> CacheOwnerArgumentNamespaceName,
            TOptional<int32> CacheOwnerArgumentYear,
            TOptional<int32> CacheOwnerArgumentMonth,
            TOptional<int32> CacheOwnerArgumentDay,
            TOptional<FString> CacheOwnerArgumentCurrency,
            TOptional<int32> CacheOwnerArgumentTimeOffset
        );

        static Gs2::Core::Model::FGs2ErrorPtr Fetch(
            const Gs2::Core::Domain::FCacheDatabasePtr& CacheOwnerArgumentCache,
            TOptional<FString> CacheOwnerArgumentNamespaceName,
            TOptional<int32> CacheOwnerArgumentYear,
            TOptional<int32> CacheOwnerArgumentMonth,
            TOptional<int32> CacheOwnerArgumentDay,
            TOptional<FString> CacheOwnerArgumentCurrency,
            TOptional<int32> CacheOwnerArgumentTimeOffset,
            const TFunction<Gs2::Core::Model::FGs2ErrorPtr(Gs2::Money2::Model::FDailyTransactionHistoryPtr*)>& CacheOwnerArgumentFetchImpl,
            Gs2::Money2::Model::FDailyTransactionHistoryPtr* CacheOwnerArgumentOutItem
        );

        static Gs2::Core::Domain::CallbackID ListSubscribe(
            const Gs2::Core::Domain::FCacheDatabasePtr& CacheOwnerArgumentCache,
            TOptional<FString> CacheOwnerArgumentNamespaceName,
            TOptional<int32> CacheOwnerArgumentTimeOffset,
            TFunction<void(TArray<Gs2::Money2::Model::FDailyTransactionHistoryPtr>)> CacheOwnerArgumentCallback
        );

        static void ListUnsubscribe(
            const Gs2::Core::Domain::FCacheDatabasePtr& CacheOwnerArgumentCache,
            TOptional<FString> CacheOwnerArgumentNamespaceName,
            TOptional<int32> CacheOwnerArgumentTimeOffset,
            Gs2::Core::Domain::CallbackID CacheOwnerArgumentCallbackID
        );
    };
}