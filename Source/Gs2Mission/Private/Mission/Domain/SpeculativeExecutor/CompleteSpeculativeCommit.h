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
#include "Mission/Model/Cache/Complete.h"
#include "Mission/Model/Complete.h"

namespace Gs2::Mission::Domain::SpeculativeExecutor::Private
{
    class FCompleteSpeculativeCommit final
    {
        struct FCompositionState final
        {
            Gs2::Mission::Model::FCompletePtr Item;
            TArray<FString> ReceiveMissionTaskNames;
            bool HasRevertMissionTaskName = false;
            FString RevertMissionTaskName;
            bool Dirty = true;
        };

        const Gs2::Core::Domain::FCacheDatabasePtr Cache;
        const TOptional<FString> NamespaceName;
        const FString UserId;
        const FString MissionGroupName;
        const TOptional<int32> TimeOffset;
        const FString ExpectedCompleteId;
        const TFunction<Gs2::Mission::Model::FCompletePtr(const Gs2::Mission::Model::FCompletePtr&)> Transform;
        const TFunction<Gs2::Mission::Model::FCompletePtr(const Gs2::Mission::Model::FCompletePtr&, const TArray<FString>&)> ComposeTransform;
        const TArray<FString> ReceiveMissionTaskNames;
        const bool HasRevertMissionTaskName;
        const FString RevertMissionTaskName;

        bool IsExpected(const Gs2::Mission::Model::FCompletePtr& Item) const
        {
            return Item.IsValid() && Item->GetCompleteId().IsSet() && Item->GetCompleteId().Get(FString()) == ExpectedCompleteId &&
                Item->GetUserId().IsSet() && Item->GetUserId().Get(FString()) == UserId &&
                Item->GetMissionGroupName().IsSet() && Item->GetMissionGroupName().Get(FString()) == MissionGroupName;
        }

        static bool Contains(const TArray<FString>& Values, const FString& Value)
        {
            return Values.Contains(Value);
        }

        static bool TryMerge(
            const FCompositionState& Current,
            const TArray<FString>& IncomingReceive,
            const bool IncomingHasRevert,
            const FString& IncomingRevert,
            TArray<FString>& Receive,
            bool& HasRevert,
            FString& Revert,
            bool& DuplicateRevert
        )
        {
            Receive = Current.ReceiveMissionTaskNames;
            for (const auto& Name : IncomingReceive)
            {
                if (!Receive.Contains(Name)) Receive.Add(Name);
            }
            HasRevert = Current.HasRevertMissionTaskName;
            Revert = Current.RevertMissionTaskName;
            DuplicateRevert = false;
            if (!IncomingHasRevert) return true;
            if (!HasRevert)
            {
                HasRevert = true;
                Revert = IncomingRevert;
                return true;
            }
            if (Revert == IncomingRevert)
            {
                DuplicateRevert = true;
                return true;
            }
            return false;
        }

    public:
        FCompleteSpeculativeCommit(
            const Gs2::Core::Domain::FCacheDatabasePtr& InCache,
            const TOptional<FString>& InNamespaceName,
            const FString& InUserId,
            const FString& InMissionGroupName,
            const TOptional<int32>& InTimeOffset,
            const FString& InExpectedCompleteId,
            const TFunction<Gs2::Mission::Model::FCompletePtr(const Gs2::Mission::Model::FCompletePtr&)>& InTransform,
            const TFunction<Gs2::Mission::Model::FCompletePtr(const Gs2::Mission::Model::FCompletePtr&, const TArray<FString>&)>& InComposeTransform,
            const TArray<FString>& InReceiveMissionTaskNames,
            const bool InHasRevertMissionTaskName,
            const FString& InRevertMissionTaskName
        ):
            Cache(InCache), NamespaceName(InNamespaceName), UserId(InUserId), MissionGroupName(InMissionGroupName),
            TimeOffset(InTimeOffset), ExpectedCompleteId(InExpectedCompleteId), Transform(InTransform),
            ComposeTransform(InComposeTransform), ReceiveMissionTaskNames(InReceiveMissionTaskNames),
            HasRevertMissionTaskName(InHasRevertMissionTaskName), RevertMissionTaskName(InRevertMissionTaskName)
        {
        }

        FString CompositionKey() const
        {
            return Gs2::Mission::Model::Cache::FCompleteCache::CreateCacheParentKey(
                NamespaceName, UserId, TimeOffset
            ) + TEXT(":") + Gs2::Mission::Model::Cache::FCompleteCache::CreateCacheKey(MissionGroupName);
        }

        bool TryCompose(const TSharedPtr<void>& Current, const bool HasCurrent, TSharedPtr<void>& Next) const
        {
            try
            {
                if (HasCurrent)
                {
                    const auto State = StaticCastSharedPtr<FCompositionState>(Current);
                    if (!State.IsValid() || !IsExpected(State->Item))
                    {
                        Next = nullptr;
                        return false;
                    }
                    TArray<FString> Receive;
                    bool HasRevert = false;
                    FString Revert;
                    bool DuplicateRevert = false;
                    if (!TryMerge(*State, ReceiveMissionTaskNames, HasRevertMissionTaskName, RevertMissionTaskName,
                        Receive, HasRevert, Revert, DuplicateRevert))
                    {
                        Next = nullptr;
                        return false;
                    }
                    const auto Composed = DuplicateRevert ? State->Item : ComposeTransform(State->Item, State->ReceiveMissionTaskNames);
                    if (!IsExpected(Composed))
                    {
                        Next = nullptr;
                        return false;
                    }
                    auto NextState = MakeShared<FCompositionState>();
                    NextState->Item = Composed;
                    NextState->ReceiveMissionTaskNames = MoveTemp(Receive);
                    NextState->HasRevertMissionTaskName = HasRevert;
                    NextState->RevertMissionTaskName = Revert;
                    NextState->Dirty = State->Dirty || (!DuplicateRevert && Composed != State->Item);
                    Next = NextState;
                    return true;
                }

                Gs2::Mission::Model::FCompletePtr Cached;
                if (!Gs2::Mission::Model::Cache::FCompleteCache::TryGet(
                    Cache, NamespaceName, UserId, MissionGroupName, TimeOffset, &Cached
                ) || !IsExpected(Cached))
                {
                    Next = nullptr;
                    return false;
                }
                const auto Changed = Transform(Cached);
                if (!IsExpected(Changed))
                {
                    Next = nullptr;
                    return false;
                }
                auto InitialState = MakeShared<FCompositionState>();
                InitialState->Item = Changed;
                InitialState->ReceiveMissionTaskNames = ReceiveMissionTaskNames;
                InitialState->HasRevertMissionTaskName = HasRevertMissionTaskName;
                InitialState->RevertMissionTaskName = RevertMissionTaskName;
                InitialState->Dirty = Changed != Cached;
                Next = InitialState;
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
                if (!Composition.IsValid() || !Composition->Dirty || !IsExpected(Composition->Item)) return;
                Gs2::Mission::Model::Cache::FCompleteCache::Put(
                    Cache, NamespaceName, UserId, MissionGroupName, TimeOffset, Composition->Item
                );
            }
            catch (...)
            {
            }
        }

        static Gs2::Mission::Model::FCompletePtr Clone(const Gs2::Mission::Model::FCompletePtr& Source)
        {
            if (!Source.IsValid()) return nullptr;
            auto Result = MakeShared<Gs2::Mission::Model::FComplete>(*Source);
            if (Source->GetCompletedMissionTaskNames().IsValid())
            {
                Result->WithCompletedMissionTaskNames(MakeShared<TArray<FString>>(*Source->GetCompletedMissionTaskNames()));
            }
            if (Source->GetReceivedMissionTaskNames().IsValid())
            {
                Result->WithReceivedMissionTaskNames(MakeShared<TArray<FString>>(*Source->GetReceivedMissionTaskNames()));
            }
            return Result;
        }
    };
}
