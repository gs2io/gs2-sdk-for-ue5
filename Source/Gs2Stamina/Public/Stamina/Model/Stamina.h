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

namespace Gs2::Stamina::Model
{
    class GS2STAMINA_API FStamina final : public Gs2Object, public TSharedFromThis<FStamina>
    {
        TOptional<FString> StaminaIdValue;
        TOptional<FString> StaminaNameValue;
        TOptional<FString> UserIdValue;
        TOptional<int32> ValueValue;
        TOptional<int32> MaxValueValue;
        TOptional<int32> RecoverIntervalMinutesValue;
        TOptional<int32> RecoverValueValue;
        TOptional<int32> OverflowValueValue;
        TOptional<int64> NextRecoverAtValue;
        TOptional<int64> LastRecoveredAtValue;
        TOptional<int64> CreatedAtValue;
        TOptional<int64> UpdatedAtValue;
        TOptional<int64> RevisionValue;

    public:
        FStamina();
        FStamina(
            const FStamina& From
        );
        virtual ~FStamina() override = default;

        TSharedPtr<FStamina> WithStaminaId(const TOptional<FString> StaminaId);
        TSharedPtr<FStamina> WithStaminaName(const TOptional<FString> StaminaName);
        TSharedPtr<FStamina> WithUserId(const TOptional<FString> UserId);
        TSharedPtr<FStamina> WithValue(const TOptional<int32> Value);
        TSharedPtr<FStamina> WithMaxValue(const TOptional<int32> MaxValue);
        TSharedPtr<FStamina> WithRecoverIntervalMinutes(const TOptional<int32> RecoverIntervalMinutes);
        TSharedPtr<FStamina> WithRecoverValue(const TOptional<int32> RecoverValue);
        TSharedPtr<FStamina> WithOverflowValue(const TOptional<int32> OverflowValue);
        TSharedPtr<FStamina> WithNextRecoverAt(const TOptional<int64> NextRecoverAt);
        TSharedPtr<FStamina> WithLastRecoveredAt(const TOptional<int64> LastRecoveredAt);
        TSharedPtr<FStamina> WithCreatedAt(const TOptional<int64> CreatedAt);
        TSharedPtr<FStamina> WithUpdatedAt(const TOptional<int64> UpdatedAt);
        TSharedPtr<FStamina> WithRevision(const TOptional<int64> Revision);

        TOptional<FString> GetStaminaId() const;
        TOptional<FString> GetStaminaName() const;
        TOptional<FString> GetUserId() const;
        TOptional<int32> GetValue() const;
        FString GetValueString() const;
        TOptional<int32> GetMaxValue() const;
        FString GetMaxValueString() const;
        TOptional<int32> GetRecoverIntervalMinutes() const;
        FString GetRecoverIntervalMinutesString() const;
        TOptional<int32> GetRecoverValue() const;
        FString GetRecoverValueString() const;
        TOptional<int32> GetOverflowValue() const;
        FString GetOverflowValueString() const;
        TOptional<int64> GetNextRecoverAt() const;
        FString GetNextRecoverAtString() const;
        TOptional<int64> GetLastRecoveredAt() const;
        FString GetLastRecoveredAtString() const;
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
        static TOptional<FString> GetStaminaNameFromGrn(const FString Grn);

        static TSharedPtr<FStamina> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;

        static FString TypeName;
    };
    typedef TSharedPtr<FStamina, ESPMode::ThreadSafe> FStaminaPtr;
}