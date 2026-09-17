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
#include "Grade/Model/Cache/Status.h"

namespace Gs2::Grade::Domain::SpeculativeExecutor
{
    class FStatusSpeculativeCommit final
    {
    public:
        using FTransform = TFunction<Gs2::Grade::Model::FStatusPtr(
            const Gs2::Grade::Model::FStatusPtr&
        )>;

        static Gs2::Core::Domain::SpeculativeExecutor::FPreparedSpeculativeCommit::FPreparedCommitPtr Create(
            const Gs2::Core::Domain::FCacheDatabasePtr& Cache,
            const TOptional<FString> NamespaceName,
            const TOptional<FString> UserId,
            const TOptional<FString> GradeName,
            const TOptional<FString> PropertyId,
            const TOptional<int32> TimeOffset,
            const FString& ExpectedStatusId,
            FTransform Transform
        )
        {
            if (!Cache.IsValid() || !UserId.IsSet() || !GradeName.IsSet() ||
                !PropertyId.IsSet() || !Transform)
            {
                return nullptr;
            }

            Gs2::Grade::Model::FStatusPtr Item;
            if (!Gs2::Grade::Model::Cache::FStatusCache::TryGet(
                    Cache, NamespaceName, UserId, GradeName, PropertyId,
                    TimeOffset, &Item) || !IsExpected(Item, ExpectedStatusId,
                    UserId, GradeName, PropertyId))
            {
                return nullptr;
            }

            const FString CompositionKey =
                Gs2::Grade::Model::Cache::FStatusCache::CreateCacheParentKey(
                    NamespaceName, UserId, TimeOffset
                ) + TEXT(":") +
                Gs2::Grade::Model::Cache::FStatusCache::CreateCacheKey(
                    GradeName, PropertyId
                );
            return Gs2::Core::Domain::SpeculativeExecutor::FPreparedSpeculativeCommit::CreateComposable(
                CompositionKey,
                [Cache, NamespaceName, UserId, GradeName, PropertyId, TimeOffset,
                    ExpectedStatusId, Transform](
                    const TSharedPtr<void>& Current,
                    const bool HasCurrent,
                    TSharedPtr<void>& Next
                )
                {
                    Gs2::Grade::Model::FStatusPtr Source;
                    if (HasCurrent)
                    {
                        if (!Current.IsValid())
                        {
                            Next = nullptr;
                            return false;
                        }
                        Source = StaticCastSharedPtr<Gs2::Grade::Model::FStatus>(Current);
                    }
                    else if (!Gs2::Grade::Model::Cache::FStatusCache::TryGet(
                        Cache, NamespaceName, UserId, GradeName, PropertyId,
                        TimeOffset, &Source))
                    {
                        Next = nullptr;
                        return false;
                    }

                    if (!IsExpected(Source, ExpectedStatusId, UserId, GradeName, PropertyId))
                    {
                        Next = nullptr;
                        return false;
                    }
                    const auto Changed = Transform(Source);
                    if (!IsExpected(Changed, ExpectedStatusId, UserId, GradeName, PropertyId))
                    {
                        Next = nullptr;
                        return false;
                    }
                    Next = Changed;
                    return true;
                },
                [Cache, NamespaceName, UserId, GradeName, PropertyId, TimeOffset,
                    ExpectedStatusId](const TSharedPtr<void>& State)
                {
                    if (!State.IsValid()) return;
                    const auto ItemToCommit =
                        StaticCastSharedPtr<Gs2::Grade::Model::FStatus>(State);
                    if (IsExpected(ItemToCommit, ExpectedStatusId, UserId, GradeName, PropertyId))
                    {
                        Gs2::Grade::Model::Cache::FStatusCache::Put(
                            Cache, NamespaceName, UserId, GradeName, PropertyId,
                            TimeOffset, ItemToCommit
                        );
                    }
                }
            );
        }

        static bool IsExpected(
            const Gs2::Grade::Model::FStatusPtr& Item,
            const FString& ExpectedStatusId,
            const TOptional<FString>& UserId,
            const TOptional<FString>& GradeName,
            const TOptional<FString>& PropertyId
        )
        {
            return Item.IsValid() &&
                Item->GetStatusId().Get(FString()) == ExpectedStatusId &&
                Item->GetUserId().Get(FString()) == UserId.Get(FString()) &&
                Item->GetGradeName().Get(FString()) == GradeName.Get(FString()) &&
                Item->GetPropertyId().Get(FString()) == PropertyId.Get(FString());
        }
    };
}
