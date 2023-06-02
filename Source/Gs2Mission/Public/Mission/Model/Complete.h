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

#include "CoreMinimal.h"
#include "Core/Gs2Object.h"

namespace Gs2::Mission::Model
{
    class GS2MISSION_API FComplete final : public Gs2Object, public TSharedFromThis<FComplete>
    {
        TOptional<FString> CompleteIdValue;
        TOptional<FString> UserIdValue;
        TOptional<FString> MissionGroupNameValue;
        TSharedPtr<TArray<FString>> CompletedMissionTaskNamesValue;
        TSharedPtr<TArray<FString>> ReceivedMissionTaskNamesValue;
        TOptional<int64> NextResetAtValue;
        TOptional<int64> CreatedAtValue;
        TOptional<int64> UpdatedAtValue;

    public:
        FComplete();
        FComplete(
            const FComplete& From
        );
        virtual ~FComplete() override = default;

        TSharedPtr<FComplete> WithCompleteId(const TOptional<FString> CompleteId);
        TSharedPtr<FComplete> WithUserId(const TOptional<FString> UserId);
        TSharedPtr<FComplete> WithMissionGroupName(const TOptional<FString> MissionGroupName);
        TSharedPtr<FComplete> WithCompletedMissionTaskNames(const TSharedPtr<TArray<FString>> CompletedMissionTaskNames);
        TSharedPtr<FComplete> WithReceivedMissionTaskNames(const TSharedPtr<TArray<FString>> ReceivedMissionTaskNames);
        TSharedPtr<FComplete> WithNextResetAt(const TOptional<int64> NextResetAt);
        TSharedPtr<FComplete> WithCreatedAt(const TOptional<int64> CreatedAt);
        TSharedPtr<FComplete> WithUpdatedAt(const TOptional<int64> UpdatedAt);

        TOptional<FString> GetCompleteId() const;
        TOptional<FString> GetUserId() const;
        TOptional<FString> GetMissionGroupName() const;
        TSharedPtr<TArray<FString>> GetCompletedMissionTaskNames() const;
        TSharedPtr<TArray<FString>> GetReceivedMissionTaskNames() const;
        TOptional<int64> GetNextResetAt() const;
        FString GetNextResetAtString() const;
        TOptional<int64> GetCreatedAt() const;
        FString GetCreatedAtString() const;
        TOptional<int64> GetUpdatedAt() const;
        FString GetUpdatedAtString() const;

        static TOptional<FString> GetRegionFromGrn(const FString Grn);
        static TOptional<FString> GetOwnerIdFromGrn(const FString Grn);
        static TOptional<FString> GetNamespaceNameFromGrn(const FString Grn);
        static TOptional<FString> GetUserIdFromGrn(const FString Grn);
        static TOptional<FString> GetMissionGroupNameFromGrn(const FString Grn);

        static TSharedPtr<FComplete> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;

        static FString TypeName;
    };
    typedef TSharedPtr<FComplete, ESPMode::ThreadSafe> FCompletePtr;
}