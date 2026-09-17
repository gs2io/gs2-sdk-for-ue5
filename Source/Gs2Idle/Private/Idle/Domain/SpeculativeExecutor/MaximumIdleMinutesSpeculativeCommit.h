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
#include "Idle/Model/Cache/Status.h"
#include "Idle/Model/Status.h"

namespace Gs2::Idle::Domain::SpeculativeExecutor::Private
{
    class FMaximumIdleMinutesSpeculativeCommit final
    {
        const Gs2::Core::Domain::FCacheDatabasePtr Cache;
        const TOptional<FString> NamespaceName;
        const FString UserId;
        const FString CategoryName;
        const TOptional<int32> TimeOffset;
        const FString ExpectedStatusId;
        const TFunction<Gs2::Idle::Model::FStatusPtr(const Gs2::Idle::Model::FStatusPtr&)> Transform;

        bool IsExpected(const Gs2::Idle::Model::FStatusPtr& Item) const
        {
            return Item.IsValid() && Item->GetStatusId().IsSet() && Item->GetStatusId().Get(FString()) == ExpectedStatusId &&
                Item->GetUserId().IsSet() && Item->GetUserId().Get(FString()) == UserId &&
                Item->GetCategoryName().IsSet() && Item->GetCategoryName().Get(FString()) == CategoryName;
        }

    public:
        FMaximumIdleMinutesSpeculativeCommit(
            const Gs2::Core::Domain::FCacheDatabasePtr& InCache,
            const TOptional<FString>& InNamespaceName,
            const FString& InUserId,
            const FString& InCategoryName,
            const TOptional<int32>& InTimeOffset,
            const FString& InExpectedStatusId,
            const TFunction<Gs2::Idle::Model::FStatusPtr(const Gs2::Idle::Model::FStatusPtr&)>& InTransform
        ):
            Cache(InCache), NamespaceName(InNamespaceName), UserId(InUserId), CategoryName(InCategoryName),
            TimeOffset(InTimeOffset), ExpectedStatusId(InExpectedStatusId), Transform(InTransform)
        {
        }

        FString CompositionKey() const
        {
            return Gs2::Idle::Model::Cache::FStatusCache::CreateCacheParentKey(
                NamespaceName, UserId, TimeOffset
            ) + TEXT(":") + Gs2::Idle::Model::Cache::FStatusCache::CreateCacheKey(CategoryName);
        }

        bool TryCompose(const TSharedPtr<void>& Current, const bool HasCurrent, TSharedPtr<void>& Next) const
        {
            try
            {
                Gs2::Idle::Model::FStatusPtr Status;
                if (HasCurrent) Status = StaticCastSharedPtr<Gs2::Idle::Model::FStatus>(Current);
                else if (!Gs2::Idle::Model::Cache::FStatusCache::TryGet(
                    Cache, NamespaceName, UserId, CategoryName, TimeOffset, &Status
                ) || !IsExpected(Status)) { Next = nullptr; return false; }
                if (!IsExpected(Status)) { Next = nullptr; return false; }
                auto Changed = Transform(Status);
                if (!IsExpected(Changed) || !Changed->GetRevision().IsSet() || Changed->GetRevision().Get(0) != 0)
                { Next = nullptr; return false; }
                Next = Changed;
                return true;
            }
            catch (...) { Next = nullptr; return false; }
        }

        void Commit(const TSharedPtr<void>& State) const
        {
            try
            {
                const auto Item = StaticCastSharedPtr<Gs2::Idle::Model::FStatus>(State);
                if (!IsExpected(Item) || !Item->GetRevision().IsSet() || Item->GetRevision().Get(0) != 0) return;
                Cache->Put(
                    Gs2::Idle::Model::FStatus::TypeName,
                    Gs2::Idle::Model::Cache::FStatusCache::CreateCacheParentKey(NamespaceName, UserId, TimeOffset),
                    Gs2::Idle::Model::Cache::FStatusCache::CreateCacheKey(CategoryName), Item,
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );
            }
            catch (...) { }
        }
    };
}
