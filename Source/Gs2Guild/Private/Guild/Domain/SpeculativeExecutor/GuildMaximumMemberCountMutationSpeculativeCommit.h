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
#include "Guild/Model/Cache/Guild.h"
#include "Guild/Model/Cache/GuildModel.h"
#include "Guild/Model/Guild.h"
#include "Guild/Model/GuildModel.h"

namespace Gs2::Guild::Domain::SpeculativeExecutor::Private
{
    class FGuildMaximumMemberCountMutationSpeculativeCommit final
    {
        const Gs2::Core::Domain::FCacheDatabasePtr Cache;
        const TOptional<FString> NamespaceName;
        const TOptional<FString> GuildModelName;
        const TOptional<FString> GuildName;
        const TOptional<int32> TimeOffset;
        const FString ExpectedGuildId;
        const FString ExpectedModelId;
        const TOptional<int64> PreparedRevision;
        const bool UsesModel;
        const TFunction<Gs2::Guild::Model::FGuildPtr(const Gs2::Guild::Model::FGuildPtr&, int32)> Transform;

        bool IsExpected(const Gs2::Guild::Model::FGuildPtr& Item) const
        {
            return Item.IsValid() && Item->GetGuildId().IsSet() && Item->GetGuildId().Get(FString()) == ExpectedGuildId &&
                Item->GetGuildModelName() == GuildModelName && Item->GetName() == GuildName;
        }

    public:
        FGuildMaximumMemberCountMutationSpeculativeCommit(
            const Gs2::Core::Domain::FCacheDatabasePtr& InCache,
            const TOptional<FString>& InNamespaceName,
            const TOptional<FString>& InGuildModelName,
            const TOptional<FString>& InGuildName,
            const TOptional<int32>& InTimeOffset,
            const FString& InExpectedGuildId,
            const FString& InExpectedModelId,
            const TOptional<int64>& InPreparedRevision,
            const bool InUsesModel,
            const TFunction<Gs2::Guild::Model::FGuildPtr(const Gs2::Guild::Model::FGuildPtr&, int32)>& InTransform
        ):
            Cache(InCache), NamespaceName(InNamespaceName), GuildModelName(InGuildModelName), GuildName(InGuildName),
            TimeOffset(InTimeOffset), ExpectedGuildId(InExpectedGuildId), ExpectedModelId(InExpectedModelId),
            PreparedRevision(InPreparedRevision), UsesModel(InUsesModel),
            Transform(InTransform)
        {
        }

        FString CompositionKey() const
        {
            return Gs2::Guild::Model::Cache::FGuildCache::CreateCacheParentKey(NamespaceName, TimeOffset) + TEXT(":") +
                Gs2::Guild::Model::Cache::FGuildCache::CreateCacheKey(GuildModelName, GuildName);
        }

        bool TryCompose(const TSharedPtr<void>& Current, const bool HasCurrent, TSharedPtr<void>& Next) const
        {
            try
            {
                int32 Maximum = INT32_MAX;
                if (UsesModel)
                {
                    Gs2::Guild::Model::FGuildModelPtr Model;
                    if (!Gs2::Guild::Model::Cache::FGuildModelCache::TryGet(
                        Cache, NamespaceName, GuildModelName, TOptional<int32>(), &Model
                    ) || !Model.IsValid() || !Model->GetGuildModelId().IsSet() ||
                        Model->GetGuildModelId().Get(FString()) != ExpectedModelId || Model->GetName() != GuildModelName) { Next = nullptr; return false; }
                    if (Model->GetMaximumMemberCount().IsSet()) Maximum = Model->GetMaximumMemberCount().Get(0);
                }
                Gs2::Guild::Model::FGuildPtr Guild;
                if (HasCurrent) Guild = StaticCastSharedPtr<Gs2::Guild::Model::FGuild>(Current);
                else if (!Gs2::Guild::Model::Cache::FGuildCache::TryGet(
                    Cache, NamespaceName, GuildModelName, GuildName, TimeOffset, &Guild
                ) || !IsExpected(Guild)) { Next = nullptr; return false; }
                if (!HasCurrent && Guild->GetRevision().IsSet() && Guild->GetRevision().Get(0) > 0 &&
                    (!PreparedRevision.IsSet() || Guild->GetRevision().Get(0) != PreparedRevision.Get(0)))
                { Next = nullptr; return false; }
                if (!IsExpected(Guild)) { Next = nullptr; return false; }
                auto Changed = Transform(Guild, Maximum);
                if (!IsExpected(Changed)) { Next = nullptr; return false; }
                Changed->WithRevision(0);
                Next = Changed;
                return true;
            }
            catch (...) { Next = nullptr; return false; }
        }

        void Commit(const TSharedPtr<void>& State) const
        {
            try
            {
                const auto Item = StaticCastSharedPtr<Gs2::Guild::Model::FGuild>(State);
                if (!IsExpected(Item) || !Item->GetRevision().IsSet() || Item->GetRevision().Get(0) != 0) return;
                Cache->Put(
                    Gs2::Guild::Model::FGuild::TypeName,
                    Gs2::Guild::Model::Cache::FGuildCache::CreateCacheParentKey(NamespaceName, TimeOffset),
                    Gs2::Guild::Model::Cache::FGuildCache::CreateCacheKey(GuildModelName, GuildName), Item,
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );
            }
            catch (...) { }
        }
    };
}
