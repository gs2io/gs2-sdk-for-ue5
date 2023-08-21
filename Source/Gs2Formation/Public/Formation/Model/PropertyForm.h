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
#include "Slot.h"

namespace Gs2::Formation::Model
{
    class GS2FORMATION_API FPropertyForm final : public Gs2Object, public TSharedFromThis<FPropertyForm>
    {
        TOptional<FString> FormIdValue;
        TOptional<FString> UserIdValue;
        TOptional<FString> NameValue;
        TOptional<FString> PropertyIdValue;
        TSharedPtr<TArray<TSharedPtr<FSlot>>> SlotsValue;
        TOptional<int64> CreatedAtValue;
        TOptional<int64> UpdatedAtValue;
        TOptional<int64> RevisionValue;

    public:
        FPropertyForm();
        FPropertyForm(
            const FPropertyForm& From
        );
        virtual ~FPropertyForm() override = default;

        TSharedPtr<FPropertyForm> WithFormId(const TOptional<FString> FormId);
        TSharedPtr<FPropertyForm> WithUserId(const TOptional<FString> UserId);
        TSharedPtr<FPropertyForm> WithName(const TOptional<FString> Name);
        TSharedPtr<FPropertyForm> WithPropertyId(const TOptional<FString> PropertyId);
        TSharedPtr<FPropertyForm> WithSlots(const TSharedPtr<TArray<TSharedPtr<FSlot>>> Slots);
        TSharedPtr<FPropertyForm> WithCreatedAt(const TOptional<int64> CreatedAt);
        TSharedPtr<FPropertyForm> WithUpdatedAt(const TOptional<int64> UpdatedAt);
        TSharedPtr<FPropertyForm> WithRevision(const TOptional<int64> Revision);

        TOptional<FString> GetFormId() const;
        TOptional<FString> GetUserId() const;
        TOptional<FString> GetName() const;
        TOptional<FString> GetPropertyId() const;
        TSharedPtr<TArray<TSharedPtr<FSlot>>> GetSlots() const;
        TOptional<int64> GetCreatedAt() const;
        FString GetCreatedAtString() const;
        TOptional<int64> GetUpdatedAt() const;
        FString GetUpdatedAtString() const;
        TOptional<int64> GetRevision() const;
        FString GetRevisionString() const;

        static TOptional<FString> GetRegionFromGrn(const FString Grn);
        static TOptional<FString> GetOwnerIdFromGrn(const FString Grn);
        static TOptional<FString> GetNamespaceNameFromGrn(const FString Grn);
        static TOptional<FString> GetUserIdFromGrn(const FString Grn);
        static TOptional<FString> GetFormModelNameFromGrn(const FString Grn);
        static TOptional<FString> GetPropertyIdFromGrn(const FString Grn);

        static TSharedPtr<FPropertyForm> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;

        static FString TypeName;
    };
    typedef TSharedPtr<FPropertyForm, ESPMode::ThreadSafe> FPropertyFormPtr;
}