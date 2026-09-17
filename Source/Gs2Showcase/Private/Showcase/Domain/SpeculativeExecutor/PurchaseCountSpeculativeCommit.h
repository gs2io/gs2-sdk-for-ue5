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
#include "Showcase/Model/Cache/RandomDisplayItem.h"

namespace Gs2::Showcase::Domain::SpeculativeExecutor::Private
{
    class FPurchaseCountSpeculativeCommit final
    {
    public:
        static Gs2::Showcase::Model::FRandomDisplayItemPtr Transform(
            const Gs2::Showcase::Model::FRandomDisplayItemPtr& Source,
            const int32 Count
        )
        {
            if (!Source.IsValid() || !Source->GetCurrentPurchaseCount().IsSet() ||
                !Source->GetMaximumPurchaseCount().IsSet())
            {
                return nullptr;
            }

            const int64 ChangedCount =
                static_cast<int64>(Source->GetCurrentPurchaseCount().GetValue()) +
                static_cast<int64>(Count);
            if (ChangedCount < TNumericLimits<int32>::Min() ||
                ChangedCount > TNumericLimits<int32>::Max() ||
                ChangedCount > static_cast<int64>(Source->GetMaximumPurchaseCount().GetValue()))
            {
                return nullptr;
            }

            const auto Changed = Gs2::Showcase::Model::FRandomDisplayItem::FromJson(
                Source->ToJson()
            );
            if (!Changed.IsValid())
            {
                return nullptr;
            }
            Changed->WithCurrentPurchaseCount(static_cast<int32>(ChangedCount));
            return Changed;
        }

        static Gs2::Core::Domain::SpeculativeExecutor::FPreparedSpeculativeCommit::FPreparedCommitPtr Create(
            const Gs2::Core::Domain::FCacheDatabasePtr& Cache,
            const TOptional<FString>& NamespaceName,
            const TOptional<FString>& UserId,
            const TOptional<FString>& ShowcaseName,
            const TOptional<FString>& DisplayItemName,
            const TOptional<int32>& TimeOffset,
            const Gs2::Showcase::Model::FRandomDisplayItemPtr& PreparedItem,
            const int32 Count
        )
        {
            if (!Cache.IsValid() || !UserId.IsSet() || !PreparedItem.IsValid() ||
                !IsExpected(PreparedItem, ShowcaseName, DisplayItemName) ||
                !Transform(PreparedItem, Count).IsValid())
            {
                return nullptr;
            }

            const FString CompositionKey =
                Gs2::Showcase::Model::Cache::FRandomDisplayItemCache::CreateCacheParentKey(
                    NamespaceName, UserId, ShowcaseName, TimeOffset
                ) + TEXT(":") +
                Gs2::Showcase::Model::Cache::FRandomDisplayItemCache::CreateCacheKey(
                    DisplayItemName
                );

            return Gs2::Core::Domain::SpeculativeExecutor::FPreparedSpeculativeCommit::CreateComposable(
                CompositionKey,
                [Cache, NamespaceName, UserId, ShowcaseName, DisplayItemName,
                    TimeOffset, PreparedItem, Count](
                    const TSharedPtr<void>& Current,
                    const bool HasCurrent,
                    TSharedPtr<void>& Next
                )
                {
                    try
                    {
                        Gs2::Showcase::Model::FRandomDisplayItemPtr Source;
                        if (HasCurrent)
                        {
                            if (!Current.IsValid())
                            {
                                Next = nullptr;
                                return false;
                            }
                            Source = StaticCastSharedPtr<Gs2::Showcase::Model::FRandomDisplayItem>(Current);
                        }
                        else if (!Gs2::Showcase::Model::Cache::FRandomDisplayItemCache::TryGet(
                            Cache, NamespaceName, UserId, ShowcaseName, DisplayItemName,
                            TimeOffset, &Source
                        ) || Source != PreparedItem)
                        {
                            Next = nullptr;
                            return false;
                        }

                        if (!IsExpected(Source, ShowcaseName, DisplayItemName))
                        {
                            Next = nullptr;
                            return false;
                        }
                        const auto Changed = Transform(Source, Count);
                        if (!Changed.IsValid() || !IsExpected(Changed, ShowcaseName, DisplayItemName))
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
                },
                [Cache, NamespaceName, UserId, ShowcaseName, DisplayItemName,
                    TimeOffset, PreparedItem](const TSharedPtr<void>& State)
                {
                    if (!State.IsValid())
                    {
                        return;
                    }
                    const auto Changed = StaticCastSharedPtr<Gs2::Showcase::Model::FRandomDisplayItem>(State);
                    Gs2::Showcase::Model::FRandomDisplayItemPtr Live;
                    if (!Gs2::Showcase::Model::Cache::FRandomDisplayItemCache::TryGet(
                        Cache, NamespaceName, UserId, ShowcaseName, DisplayItemName,
                        TimeOffset, &Live
                    ) || Live != PreparedItem ||
                        !IsExpected(Live, ShowcaseName, DisplayItemName) ||
                        !IsExpected(Changed, ShowcaseName, DisplayItemName))
                    {
                        return;
                    }
                    Gs2::Showcase::Model::Cache::FRandomDisplayItemCache::Put(
                        Cache, NamespaceName, UserId, ShowcaseName, DisplayItemName,
                        TimeOffset, Changed
                    );
                }
            );
        }

    private:
        static bool IsExpected(
            const Gs2::Showcase::Model::FRandomDisplayItemPtr& Item,
            const TOptional<FString>& ShowcaseName,
            const TOptional<FString>& DisplayItemName
        )
        {
            return Item.IsValid() && Item->GetShowcaseName() == ShowcaseName &&
                Item->GetName() == DisplayItemName;
        }
    };
}
