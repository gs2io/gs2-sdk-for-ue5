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
#include "Formation/Model/Cache/Mold.h"
#include "Formation/Model/Cache/MoldModel.h"
#include "Formation/Model/Mold.h"
#include "Formation/Model/MoldModel.h"

namespace Gs2::Formation::Domain::SpeculativeExecutor::Private
{
    class FMoldCapacityMutationSpeculativeCommit final
    {
        const Gs2::Core::Domain::FCacheDatabasePtr Cache;
        const TOptional<FString> NamespaceName;
        const FString UserId;
        const FString MoldModelName;
        const TOptional<int32> TimeOffset;
        const FString ExpectedMoldId;
        const FString ExpectedModelId;
        const TOptional<int64> PreparedRevision;
        const int32 PreparedMaxCapacity;
        const TFunction<Gs2::Formation::Model::FMoldPtr(const Gs2::Formation::Model::FMoldPtr&)> Transform;

        bool IsExpectedMold(const Gs2::Formation::Model::FMoldPtr& Item) const
        {
            return Item.IsValid() && Item->GetMoldId().IsSet() && Item->GetMoldId().Get(FString()) == ExpectedMoldId &&
                Item->GetName().IsSet() && Item->GetName().Get(FString()) == MoldModelName &&
                Item->GetUserId().IsSet() && Item->GetUserId().Get(FString()) == UserId;
        }

        bool IsExpectedModel(const Gs2::Formation::Model::FMoldModelPtr& Item) const
        {
            return Item.IsValid() && Item->GetMoldModelId().IsSet() && Item->GetMoldModelId().Get(FString()) == ExpectedModelId &&
                Item->GetName().IsSet() && Item->GetName().Get(FString()) == MoldModelName &&
                Item->GetMaxCapacity().IsSet() && Item->GetMaxCapacity().Get(0) == PreparedMaxCapacity;
        }

    public:
        FMoldCapacityMutationSpeculativeCommit(
            const Gs2::Core::Domain::FCacheDatabasePtr& InCache,
            const TOptional<FString>& InNamespaceName,
            const FString& InUserId,
            const FString& InMoldModelName,
            const TOptional<int32>& InTimeOffset,
            const FString& InExpectedMoldId,
            const FString& InExpectedModelId,
            const TOptional<int64>& InPreparedRevision,
            const int32 InPreparedMaxCapacity,
            const TFunction<Gs2::Formation::Model::FMoldPtr(const Gs2::Formation::Model::FMoldPtr&)>& InTransform
        ):
            Cache(InCache), NamespaceName(InNamespaceName), UserId(InUserId), MoldModelName(InMoldModelName),
            TimeOffset(InTimeOffset), ExpectedMoldId(InExpectedMoldId), ExpectedModelId(InExpectedModelId),
            PreparedRevision(InPreparedRevision), PreparedMaxCapacity(InPreparedMaxCapacity), Transform(InTransform)
        {
        }

        FString CompositionKey() const
        {
            return Gs2::Formation::Model::Cache::FMoldCache::CreateCacheParentKey(
                NamespaceName, UserId, TimeOffset
            ) + TEXT(":") + Gs2::Formation::Model::Cache::FMoldCache::CreateCacheKey(MoldModelName);
        }

        bool TryCompose(const TSharedPtr<void>& Current, const bool HasCurrent, TSharedPtr<void>& Next) const
        {
            try
            {
                Gs2::Formation::Model::FMoldModelPtr Model;
                if (!Gs2::Formation::Model::Cache::FMoldModelCache::TryGet(
                    Cache, NamespaceName, MoldModelName, TOptional<int32>(), &Model
                ) || !IsExpectedModel(Model))
                {
                    Next = nullptr;
                    return false;
                }
                Gs2::Formation::Model::FMoldPtr Mold;
                if (HasCurrent)
                {
                    Mold = StaticCastSharedPtr<Gs2::Formation::Model::FMold>(Current);
                }
                else if (!Gs2::Formation::Model::Cache::FMoldCache::TryGet(
                    Cache, NamespaceName, UserId, MoldModelName, TimeOffset, &Mold
                ) || !IsExpectedMold(Mold))
                {
                    Next = nullptr;
                    return false;
                }
                if (!HasCurrent && Mold->GetRevision().IsSet() && Mold->GetRevision().Get(0) > 0 &&
                    (!PreparedRevision.IsSet() || Mold->GetRevision().Get(0) != PreparedRevision.Get(0)))
                {
                    Next = nullptr;
                    return false;
                }
                if (!IsExpectedMold(Mold))
                {
                    Next = nullptr;
                    return false;
                }
                auto Changed = Transform(Mold);
                if (!IsExpectedMold(Changed) || !Changed->GetCapacity().IsSet() ||
                    Changed->GetCapacity().Get(0) < 0 || Changed->GetCapacity().Get(0) > Model->GetMaxCapacity().Get(0))
                {
                    Next = nullptr;
                    return false;
                }
                Changed->WithRevision(0);
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
                const auto Item = StaticCastSharedPtr<Gs2::Formation::Model::FMold>(State);
                if (!IsExpectedMold(Item) || !Item->GetCapacity().IsSet() || Item->GetCapacity().Get(0) < 0 ||
                    !Item->GetRevision().IsSet() || Item->GetRevision().Get(0) != 0) return;
                Cache->Put(
                    Gs2::Formation::Model::FMold::TypeName,
                    Gs2::Formation::Model::Cache::FMoldCache::CreateCacheParentKey(NamespaceName, UserId, TimeOffset),
                    Gs2::Formation::Model::Cache::FMoldCache::CreateCacheKey(MoldModelName), Item,
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );
            }
            catch (...) { }
        }
    };
}
