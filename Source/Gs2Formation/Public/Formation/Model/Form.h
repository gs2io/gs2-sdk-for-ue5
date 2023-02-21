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
#include "Slot.h"

namespace Gs2::Formation::Model
{
    class GS2FORMATION_API FForm final : public TSharedFromThis<FForm>
    {
        TOptional<FString> FormIdValue;
        TOptional<FString> NameValue;
        TOptional<int32> IndexValue;
        TSharedPtr<TArray<TSharedPtr<FSlot>>> SlotsValue;
        TOptional<int64> CreatedAtValue;
        TOptional<int64> UpdatedAtValue;

    public:
        FForm();
        FForm(
            const FForm& From
        );
        ~FForm() = default;

        TSharedPtr<FForm> WithFormId(const TOptional<FString> FormId);
        TSharedPtr<FForm> WithName(const TOptional<FString> Name);
        TSharedPtr<FForm> WithIndex(const TOptional<int32> Index);
        TSharedPtr<FForm> WithSlots(const TSharedPtr<TArray<TSharedPtr<FSlot>>> Slots);
        TSharedPtr<FForm> WithCreatedAt(const TOptional<int64> CreatedAt);
        TSharedPtr<FForm> WithUpdatedAt(const TOptional<int64> UpdatedAt);

        TOptional<FString> GetFormId() const;
        TOptional<FString> GetName() const;
        TOptional<int32> GetIndex() const;
        FString GetIndexString() const;
        TSharedPtr<TArray<TSharedPtr<FSlot>>> GetSlots() const;
        TOptional<int64> GetCreatedAt() const;
        FString GetCreatedAtString() const;
        TOptional<int64> GetUpdatedAt() const;
        FString GetUpdatedAtString() const;

        static TOptional<FString> GetRegionFromGrn(const FString Grn);
        static TOptional<FString> GetOwnerIdFromGrn(const FString Grn);
        static TOptional<FString> GetNamespaceNameFromGrn(const FString Grn);
        static TOptional<FString> GetUserIdFromGrn(const FString Grn);
        static TOptional<FString> GetMoldNameFromGrn(const FString Grn);
        static TOptional<FString> GetIndexFromGrn(const FString Grn);

        static TSharedPtr<FForm> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;

        static FString TypeName;
    };
    typedef TSharedPtr<FForm, ESPMode::ThreadSafe> FFormPtr;
}