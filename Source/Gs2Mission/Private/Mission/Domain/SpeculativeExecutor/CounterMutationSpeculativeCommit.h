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
#include "Mission/Model/Cache/Counter.h"
#include "Mission/Model/Counter.h"

namespace Gs2::Mission::Domain::SpeculativeExecutor::Private
{
    class FCounterMutationSpeculativeCommit final
    {
        struct FCompositionState final
        {
            Gs2::Mission::Model::FCounterPtr Item;
            bool Dirty;

            FCompositionState(
                const Gs2::Mission::Model::FCounterPtr& InItem,
                const bool InDirty
            ):
                Item(InItem), Dirty(InDirty)
            {
            }
        };

        const Gs2::Core::Domain::FCacheDatabasePtr Cache;
        const TOptional<FString> NamespaceName;
        const FString UserId;
        const FString CounterName;
        const TOptional<int32> TimeOffset;
        const FString ExpectedCounterId;
        const TOptional<int64> PreparedRevision;
        const TFunction<Gs2::Mission::Model::FCounterPtr(const Gs2::Mission::Model::FCounterPtr&)> Transform;

        bool IsExpected(const Gs2::Mission::Model::FCounterPtr& Item) const
        {
            return Item.IsValid() && Item->GetCounterId().IsSet() &&
                Item->GetCounterId().Get(FString()) == ExpectedCounterId &&
                Item->GetUserId().IsSet() && Item->GetUserId().Get(FString()) == UserId &&
                Item->GetName().IsSet() && Item->GetName().Get(FString()) == CounterName;
        }

        static Gs2::Mission::Model::FCounterPtr DeepCopy(
            const Gs2::Mission::Model::FCounterPtr& Item
        )
        {
            if (!Item.IsValid()) return nullptr;
            const auto Copy = MakeShared<Gs2::Mission::Model::FCounter>(*Item);
            const auto Values = MakeShared<TArray<Gs2::Mission::Model::FScopedValuePtr>>();
            if (Item->GetValues().IsValid())
            {
                for (const auto& Value : *Item->GetValues())
                {
                    Gs2::Mission::Model::FScopedValuePtr CopyValue = nullptr;
                    if (Value.IsValid()) CopyValue = MakeShared<Gs2::Mission::Model::FScopedValue>(*Value);
                    Values->Add(CopyValue);
                }
            }
            Copy->WithValues(Values);
            return Copy;
        }

    public:
        FCounterMutationSpeculativeCommit(
            const Gs2::Core::Domain::FCacheDatabasePtr& InCache,
            const TOptional<FString>& InNamespaceName,
            const FString& InUserId,
            const FString& InCounterName,
            const TOptional<int32>& InTimeOffset,
            const FString& InExpectedCounterId,
            const TOptional<int64>& InPreparedRevision,
            const TFunction<Gs2::Mission::Model::FCounterPtr(const Gs2::Mission::Model::FCounterPtr&)>& InTransform
        ):
            Cache(InCache), NamespaceName(InNamespaceName), UserId(InUserId), CounterName(InCounterName),
            TimeOffset(InTimeOffset), ExpectedCounterId(InExpectedCounterId), PreparedRevision(InPreparedRevision),
            Transform(InTransform)
        {
        }

        FString CompositionKey() const
        {
            return Gs2::Mission::Model::Cache::FCounterCache::CreateCacheParentKey(
                NamespaceName, UserId, TimeOffset
            ) + TEXT(":") + Gs2::Mission::Model::Cache::FCounterCache::CreateCacheKey(CounterName);
        }

        bool TryCompose(
            const TSharedPtr<void>& Current,
            const bool HasCurrent,
            TSharedPtr<void>& Next
        ) const
        {
            try
            {
                Gs2::Mission::Model::FCounterPtr Source;
                bool Dirty = false;
                if (HasCurrent)
                {
                    const auto State = StaticCastSharedPtr<FCompositionState>(Current);
                    if (!State.IsValid() || !IsExpected(State->Item))
                    {
                        Next = nullptr;
                        return false;
                    }
                    Source = State->Item;
                    Dirty = State->Dirty;
                }
                else
                {
                    if (!Gs2::Mission::Model::Cache::FCounterCache::TryGet(
                        Cache, NamespaceName, UserId, CounterName, TimeOffset, &Source
                    ) || !Source.IsValid())
                    {
                        Next = nullptr;
                        return false;
                    }
                    if (Source->GetRevision().IsSet() && Source->GetRevision().Get(0) > 0 &&
                        (!PreparedRevision.IsSet() || Source->GetRevision().Get(0) != PreparedRevision.Get(0)))
                    {
                        Next = nullptr;
                        return false;
                    }
                }
                if (!IsExpected(Source))
                {
                    Next = nullptr;
                    return false;
                }
                const auto Changed = Transform(Source);
                if (!Changed.IsValid())
                {
                    Next = nullptr;
                    return false;
                }
                if (Changed == Source)
                {
                    Next = MakeShared<FCompositionState>(Source, Dirty);
                    return true;
                }
                if (!IsExpected(Changed))
                {
                    Next = nullptr;
                    return false;
                }
                Changed->WithRevision(0);
                Next = MakeShared<FCompositionState>(Changed, true);
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
                const auto Composition = StaticCastSharedPtr<FCompositionState>(State);
                if (!Composition.IsValid() || !Composition->Dirty || !IsExpected(Composition->Item) ||
                    !Composition->Item->GetRevision().IsSet() || Composition->Item->GetRevision().Get(0) != 0)
                    return;
                Gs2::Mission::Model::Cache::FCounterCache::Put(
                    Cache, NamespaceName, UserId, CounterName, TimeOffset, Composition->Item
                );
            }
            catch (...)
            {
            }
        }

        static Gs2::Mission::Model::FCounterPtr Clone(
            const Gs2::Mission::Model::FCounterPtr& Item
        )
        {
            return DeepCopy(Item);
        }
    };
}
