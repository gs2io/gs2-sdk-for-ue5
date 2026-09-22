#pragma once

#include "Core/Domain/CacheDatabase.h"
#include "Core/Model/Gs2Error.h"
#include "Guild/Model/ReceiveMemberRequest.h"

namespace Gs2::Guild::Model::Cache
{
    class GS2GUILD_API FReceiveMemberRequestCache final
    {
    public:
        static FString CreateCacheParentKey(
            TOptional<FString> CacheOwnerArgumentNamespaceName,
            TOptional<FString> CacheOwnerArgumentGuildModelName,
            TOptional<FString> CacheOwnerArgumentGuildName,
            TOptional<int32> CacheOwnerArgumentTimeOffset = TOptional<int32>()
        );

        static FString CreateCacheKey(
            TOptional<FString> CacheOwnerArgumentFromUserId
        );

        static bool TryGet(
            const Gs2::Core::Domain::FCacheDatabasePtr& CacheOwnerArgumentCache,
            TOptional<FString> CacheOwnerArgumentNamespaceName,
            TOptional<FString> CacheOwnerArgumentGuildModelName,
            TOptional<FString> CacheOwnerArgumentGuildName,
            TOptional<FString> CacheOwnerArgumentFromUserId,
            TOptional<int32> CacheOwnerArgumentTimeOffset,
            Gs2::Guild::Model::FReceiveMemberRequestPtr* CacheOwnerArgumentOutItem
        );

        static void Put(
            const Gs2::Core::Domain::FCacheDatabasePtr& CacheOwnerArgumentCache,
            TOptional<FString> CacheOwnerArgumentNamespaceName,
            TOptional<FString> CacheOwnerArgumentGuildModelName,
            TOptional<FString> CacheOwnerArgumentGuildName,
            TOptional<FString> CacheOwnerArgumentFromUserId,
            TOptional<int32> CacheOwnerArgumentTimeOffset,
            const Gs2::Guild::Model::FReceiveMemberRequestPtr& CacheOwnerArgumentItem
        );

        // Gs2Distributor:DescribeUserData（ユーザーの全データの一括取得）の 1 エントリ（この kind）をキャッシュへ入れる。
        // 鍵はエントリの namespaceName / 読み込むユーザーの userId / モデル自身のプロパティ / 主キー GRN から取る
        // （sdk-gen の BaseModel.user_data_cache_keys）。戻り値は親キーで、呼び手が全ページを読み終えてから
        // FGs2GuildDomain::SetListCached(TimeOffset, Kind, ParentKey) で「リストが揃った印」を立てる。
        static FString PutUserData(
            const Gs2::Core::Domain::FCacheDatabasePtr& Cache,
            TOptional<FString> NamespaceName,
            TOptional<FString> UserId,
            TOptional<int32> TimeOffset,
            const Gs2::Guild::Model::FReceiveMemberRequestPtr& Item
        );

        static void Delete(
            const Gs2::Core::Domain::FCacheDatabasePtr& CacheOwnerArgumentCache,
            TOptional<FString> CacheOwnerArgumentNamespaceName,
            TOptional<FString> CacheOwnerArgumentGuildModelName,
            TOptional<FString> CacheOwnerArgumentGuildName,
            TOptional<FString> CacheOwnerArgumentFromUserId,
            TOptional<int32> CacheOwnerArgumentTimeOffset
        );

        static Gs2::Core::Model::FGs2ErrorPtr Fetch(
            const Gs2::Core::Domain::FCacheDatabasePtr& CacheOwnerArgumentCache,
            TOptional<FString> CacheOwnerArgumentNamespaceName,
            TOptional<FString> CacheOwnerArgumentGuildModelName,
            TOptional<FString> CacheOwnerArgumentGuildName,
            TOptional<FString> CacheOwnerArgumentFromUserId,
            TOptional<int32> CacheOwnerArgumentTimeOffset,
            const TFunction<Gs2::Core::Model::FGs2ErrorPtr(Gs2::Guild::Model::FReceiveMemberRequestPtr*)>& CacheOwnerArgumentFetchImpl,
            Gs2::Guild::Model::FReceiveMemberRequestPtr* CacheOwnerArgumentOutItem
        );

        static Gs2::Core::Domain::CallbackID ListSubscribe(
            const Gs2::Core::Domain::FCacheDatabasePtr& CacheOwnerArgumentCache,
            TOptional<FString> CacheOwnerArgumentNamespaceName,
            TOptional<FString> CacheOwnerArgumentGuildModelName,
            TOptional<FString> CacheOwnerArgumentGuildName,
            TOptional<int32> CacheOwnerArgumentTimeOffset,
            TFunction<void(TArray<Gs2::Guild::Model::FReceiveMemberRequestPtr>)> CacheOwnerArgumentCallback
        );

        static void ListUnsubscribe(
            const Gs2::Core::Domain::FCacheDatabasePtr& CacheOwnerArgumentCache,
            TOptional<FString> CacheOwnerArgumentNamespaceName,
            TOptional<FString> CacheOwnerArgumentGuildModelName,
            TOptional<FString> CacheOwnerArgumentGuildName,
            TOptional<int32> CacheOwnerArgumentTimeOffset,
            Gs2::Core::Domain::CallbackID CacheOwnerArgumentCallbackID
        );
    };
}