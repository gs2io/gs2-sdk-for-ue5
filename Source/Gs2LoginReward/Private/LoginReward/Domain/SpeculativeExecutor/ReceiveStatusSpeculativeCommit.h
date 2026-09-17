/*
 * Copyright 2016 Game Server Services, Inc. or its affiliates. All Rights
 * Reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License").
 * You may not use this file except in compliance with the License.
 * A copy of the License is located at
 *
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 * or in the "license" file accompanying this file. This file is distributed
 * on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either
 * express or implied. See the License for the specific language governing
 * permissions and limitations under the License.
 */

#pragma once

#include "Core/Domain/CacheDatabase.h"
#include "Core/Domain/SpeculativeExecutor/PreparedSpeculativeCommit.h"
#include "LoginReward/Model/Cache/ReceiveStatus.h"

#include "Serialization/JsonSerializer.h"
#include "Serialization/JsonWriter.h"

namespace Gs2::LoginReward::Domain::SpeculativeExecutor
{
    class FReceiveStatusSpeculativeCommit final
    {
    public:
        using FTransform = TFunction<Gs2::LoginReward::Model::FReceiveStatusPtr(
            const Gs2::LoginReward::Model::FReceiveStatusPtr&)>;

        FReceiveStatusSpeculativeCommit(
            const Gs2::Core::Domain::FCacheDatabasePtr& Cache,
            const TOptional<FString>& NamespaceName,
            const FString& UserId,
            const TOptional<FString>& BonusModelName,
            const TOptional<int32>& TimeOffset,
            const FString& ExpectedId,
            FTransform Transform
        ):
            Cache(Cache),
            NamespaceName(NamespaceName),
            UserId(UserId),
            BonusModelName(BonusModelName),
            TimeOffset(TimeOffset),
            ExpectedId(ExpectedId),
            Transform(MoveTemp(Transform))
        {
        }

        FString CompositionKey() const
        {
            return Gs2::LoginReward::Model::Cache::FReceiveStatusCache::CreateCacheParentKey(
                NamespaceName, UserId, TimeOffset
            ) + TEXT(":") + Gs2::LoginReward::Model::Cache::FReceiveStatusCache::CreateCacheKey(
                BonusModelName
            );
        }

        bool CanPrepare() const
        {
            Gs2::LoginReward::Model::FReceiveStatusPtr Item;
            return Gs2::LoginReward::Model::Cache::FReceiveStatusCache::TryGet(
                Cache, NamespaceName, UserId, BonusModelName, TimeOffset, &Item
            ) && IsExpected(Item);
        }

        bool TryCompose(
            const TSharedPtr<void>& Current,
            const bool HasCurrent,
            TSharedPtr<void>& Next
        ) const
        {
            try
            {
                Gs2::LoginReward::Model::FReceiveStatusPtr Source;
                if (HasCurrent)
                {
                    if (!Current.IsValid())
                    {
                        Next = nullptr;
                        return false;
                    }
                    Source = StaticCastSharedPtr<Gs2::LoginReward::Model::FReceiveStatus>(Current);
                }
                else if (!Gs2::LoginReward::Model::Cache::FReceiveStatusCache::TryGet(
                    Cache, NamespaceName, UserId, BonusModelName, TimeOffset, &Source
                ))
                {
                    Next = nullptr;
                    return false;
                }
                if (!IsExpected(Source) || !Transform)
                {
                    Next = nullptr;
                    return false;
                }
                const auto Changed = Transform(Source);
                if (!IsExpected(Changed))
                {
                    Next = nullptr;
                    return false;
                }
                Next = Changed;
                return true;
            }
            catch (...)
            {
                Next = nullptr;
                return false;
            }
        }

        void Commit(const TSharedPtr<void>& State) const
        {
            if (!State.IsValid()) return;
            const auto Item = StaticCastSharedPtr<Gs2::LoginReward::Model::FReceiveStatus>(State);
            if (!IsExpected(Item)) return;

            Gs2::LoginReward::Model::FReceiveStatusPtr Current;
            if (!Gs2::LoginReward::Model::Cache::FReceiveStatusCache::TryGet(
                Cache, NamespaceName, UserId, BonusModelName, TimeOffset, &Current
            ) || !IsExpected(Current)) return;

            if (Current->GetRevision().IsSet() && Item->GetRevision().IsSet() &&
                Current->GetRevision().Get(0) == 0 && Item->GetRevision().Get(0) == 0 &&
                Snapshot(Current) != Snapshot(Item))
            {
                Cache->Put(
                    Gs2::LoginReward::Model::FReceiveStatus::TypeName,
                    Gs2::LoginReward::Model::Cache::FReceiveStatusCache::CreateCacheParentKey(
                        NamespaceName, UserId, TimeOffset
                    ),
                    Gs2::LoginReward::Model::Cache::FReceiveStatusCache::CreateCacheKey(
                        BonusModelName
                    ),
                    Item,
                    FDateTime::Now() + FTimespan::FromMinutes(
                        Gs2::Core::Domain::DefaultCacheMinutes
                    )
                );
                return;
            }

            Gs2::LoginReward::Model::Cache::FReceiveStatusCache::Put(
                Cache, NamespaceName, UserId, BonusModelName, TimeOffset, Item
            );
        }

    private:
        bool IsExpected(const Gs2::LoginReward::Model::FReceiveStatusPtr& Item) const
        {
            return Item.IsValid() &&
                Item->GetReceiveStatusId().IsSet() &&
                Item->GetReceiveStatusId().Get(FString()) == ExpectedId &&
                Item->GetUserId().IsSet() &&
                Item->GetUserId().Get(FString()) == UserId &&
                IsSame(Item->GetBonusModelName(), BonusModelName);
        }

        static bool IsSame(
            const TOptional<FString>& Actual,
            const TOptional<FString>& Expected
        )
        {
            return Actual.IsSet() == Expected.IsSet() &&
                (!Actual.IsSet() || Actual.Get(FString()) == Expected.Get(FString()));
        }

        static FString Snapshot(const Gs2::LoginReward::Model::FReceiveStatusPtr& Item)
        {
            FString Value;
            const auto Writer = TJsonWriterFactory<TCHAR, TCondensedJsonPrintPolicy<TCHAR>>::Create(&Value);
            FJsonSerializer::Serialize(Item->ToJson().ToSharedRef(), Writer);
            return Value;
        }

        const Gs2::Core::Domain::FCacheDatabasePtr Cache;
        const TOptional<FString> NamespaceName;
        const FString UserId;
        const TOptional<FString> BonusModelName;
        const TOptional<int32> TimeOffset;
        const FString ExpectedId;
        const FTransform Transform;
    };
}
