/*
 * Copyright 2016 Game Server Services, Inc. or its affiliates. All Rights
 * Reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License").
 * You may obtain a copy of the License at
 *
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 * or in the "license" file accompanying this file.
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#pragma once

#include "Core/Domain/CacheDatabase.h"
#include "Core/Domain/SpeculativeExecutor/PreparedSpeculativeCommit.h"
#include "SkillTree/Model/Cache/Status.h"

namespace Gs2::SkillTree::Domain::SpeculativeExecutor::Private
{
    class FStatusSpeculativeCommit final
    {
    public:
        using FTransform = TFunction<Gs2::SkillTree::Model::FStatusPtr(
            const Gs2::SkillTree::Model::FStatusPtr&)>;

        static TSharedPtr<FStatusSpeculativeCommit> Create(
            const Gs2::Core::Domain::FCacheDatabasePtr& InCache,
            const TOptional<FString> InNamespaceName,
            const FString& InUserId,
            const FString& InPropertyId,
            const TOptional<int32> InTimeOffset,
            const FString& InExpectedStatusId,
            const bool InPreserveAuthoritativeReplacement,
            FTransform InTransform
        )
        {
            if (!InCache.IsValid() || InUserId.IsEmpty() ||
                InExpectedStatusId.IsEmpty() || !InTransform)
            {
                return nullptr;
            }
            Gs2::SkillTree::Model::FStatusPtr Item;
            if (!Gs2::SkillTree::Model::Cache::FStatusCache::TryGet(
                    InCache, InNamespaceName, InUserId, InPropertyId, InTimeOffset, &Item) ||
                !IsExpected(Item, InExpectedStatusId, InUserId, InPropertyId) ||
                !Item->GetReleasedNodeNames().IsValid())
            {
                return nullptr;
            }
            return MakeShared<FStatusSpeculativeCommit>(
                InCache, InNamespaceName, InUserId, InPropertyId, InTimeOffset,
                InExpectedStatusId, Item->GetRevision(),
                InPreserveAuthoritativeReplacement, MoveTemp(InTransform));
        }

        bool CanPrepare() const
        {
            Gs2::SkillTree::Model::FStatusPtr Item;
            if (!Gs2::SkillTree::Model::Cache::FStatusCache::TryGet(
                    Cache, NamespaceName, UserId, PropertyId, TimeOffset, &Item) ||
                !IsExpected(Item, ExpectedStatusId, UserId, PropertyId) ||
                !Item->GetReleasedNodeNames().IsValid())
            {
                return false;
            }
            return RevisionMatchesPrepared(Item);
        }

        FString CompositionKey() const
        {
            return Gs2::SkillTree::Model::Cache::FStatusCache::CreateCacheParentKey(
                       NamespaceName, UserId, TimeOffset) + TEXT(":") +
                Gs2::SkillTree::Model::Cache::FStatusCache::CreateCacheKey(PropertyId);
        }

        bool TryCompose(
            const TSharedPtr<void>& Current,
            const bool HasCurrent,
            TSharedPtr<void>& Next
        ) const
        {
            try
            {
                Gs2::SkillTree::Model::FStatusPtr Source;
                if (HasCurrent)
                {
                    if (!Current.IsValid())
                    {
                        Next = nullptr;
                        return false;
                    }
                    Source = StaticCastSharedPtr<Gs2::SkillTree::Model::FStatus>(Current);
                }
                else if (!Gs2::SkillTree::Model::Cache::FStatusCache::TryGet(
                    Cache, NamespaceName, UserId, PropertyId, TimeOffset, &Source) ||
                    !IsExpected(Source, ExpectedStatusId, UserId, PropertyId) ||
                    !Source->GetReleasedNodeNames().IsValid() ||
                    !RevisionMatchesPrepared(Source))
                {
                    Next = nullptr;
                    return false;
                }
                if (!IsExpected(Source, ExpectedStatusId, UserId, PropertyId) ||
                    !Source->GetReleasedNodeNames().IsValid())
                {
                    Next = nullptr;
                    return false;
                }

                const auto Changed = Transform(Clone(Source));
                if (!IsExpected(Changed, ExpectedStatusId, UserId, PropertyId) ||
                    !Changed->GetRevision().IsSet() || Changed->GetRevision().Get(0) != 0 ||
                    !Changed->GetReleasedNodeNames().IsValid())
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
            try
            {
                const auto Item = StaticCastSharedPtr<Gs2::SkillTree::Model::FStatus>(State);
                if (!IsExpected(Item, ExpectedStatusId, UserId, PropertyId) ||
                    !Item->GetReleasedNodeNames().IsValid() || !Item->GetRevision().IsSet() ||
                    Item->GetRevision().Get(0) != 0)
                {
                    return;
                }
                Gs2::SkillTree::Model::FStatusPtr Live;
                if (!Gs2::SkillTree::Model::Cache::FStatusCache::TryGet(
                        Cache, NamespaceName, UserId, PropertyId, TimeOffset, &Live) ||
                    !IsExpected(Live, ExpectedStatusId, UserId, PropertyId) ||
                    !Live->GetReleasedNodeNames().IsValid() || !RevisionMatchesPrepared(Live))
                {
                    return;
                }
                Gs2::SkillTree::Model::Cache::FStatusCache::Put(
                    Cache, NamespaceName, UserId, PropertyId, TimeOffset, Item);
            }
            catch (...)
            {
            }
        }

    public:
        FStatusSpeculativeCommit(
            const Gs2::Core::Domain::FCacheDatabasePtr& InCache,
            const TOptional<FString> InNamespaceName,
            const FString& InUserId,
            const FString& InPropertyId,
            const TOptional<int32> InTimeOffset,
            const FString& InExpectedStatusId,
            const TOptional<int64>& InPreparedRevision,
            const bool InPreserveAuthoritativeReplacement,
            FTransform InTransform
        ):
            Cache(InCache), NamespaceName(InNamespaceName), UserId(InUserId),
            PropertyId(InPropertyId), TimeOffset(InTimeOffset),
            ExpectedStatusId(InExpectedStatusId), PreparedRevision(InPreparedRevision),
            PreserveAuthoritativeReplacement(InPreserveAuthoritativeReplacement),
            Transform(MoveTemp(InTransform))
        {
        }

    private:
        static bool IsExpected(
            const Gs2::SkillTree::Model::FStatusPtr& Item,
            const FString& ExpectedStatusId,
            const FString& UserId,
            const FString& PropertyId
        )
        {
            return Item.IsValid() && Item->GetStatusId().IsSet() &&
                Item->GetStatusId().Get(FString()) == ExpectedStatusId &&
                Item->GetUserId().IsSet() && Item->GetUserId().Get(FString()) == UserId &&
                Item->GetPropertyId().IsSet() && Item->GetPropertyId().Get(FString()) == PropertyId;
        }

        static bool IsPositiveRevision(const Gs2::SkillTree::Model::FStatusPtr& Item)
        {
            return Item.IsValid() && Item->GetRevision().IsSet() && Item->GetRevision().Get(0) > 0;
        }

        bool RevisionMatchesPrepared(const Gs2::SkillTree::Model::FStatusPtr& Item) const
        {
            return !PreserveAuthoritativeReplacement || !IsPositiveRevision(Item) ||
                (PreparedRevision.IsSet() && Item->GetRevision().Get(0) == PreparedRevision.Get(0));
        }

        static Gs2::SkillTree::Model::FStatusPtr Clone(
            const Gs2::SkillTree::Model::FStatusPtr& Source
        )
        {
            if (!Source.IsValid()) return nullptr;
            const auto Changed = MakeShared<Gs2::SkillTree::Model::FStatus>(*Source);
            if (Source->GetReleasedNodeNames().IsValid())
            {
                Changed->WithReleasedNodeNames(
                    MakeShared<TArray<FString>>(*Source->GetReleasedNodeNames()));
            }
            return Changed;
        }

        const Gs2::Core::Domain::FCacheDatabasePtr Cache;
        const TOptional<FString> NamespaceName;
        const FString UserId;
        const FString PropertyId;
        const TOptional<int32> TimeOffset;
        const FString ExpectedStatusId;
        const TOptional<int64> PreparedRevision;
        const bool PreserveAuthoritativeReplacement;
        const FTransform Transform;
    };
}
