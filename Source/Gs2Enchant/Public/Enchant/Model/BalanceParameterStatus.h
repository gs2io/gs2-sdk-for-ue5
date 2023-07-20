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
#include "BalanceParameterValue.h"

namespace Gs2::Enchant::Model
{
    class GS2ENCHANT_API FBalanceParameterStatus final : public Gs2Object, public TSharedFromThis<FBalanceParameterStatus>
    {
        TOptional<FString> BalanceParameterStatusIdValue;
        TOptional<FString> UserIdValue;
        TOptional<FString> ParameterNameValue;
        TOptional<FString> PropertyIdValue;
        TSharedPtr<TArray<TSharedPtr<FBalanceParameterValue>>> ParameterValuesValue;
        TOptional<int64> CreatedAtValue;
        TOptional<int64> UpdatedAtValue;

    public:
        FBalanceParameterStatus();
        FBalanceParameterStatus(
            const FBalanceParameterStatus& From
        );
        virtual ~FBalanceParameterStatus() override = default;

        TSharedPtr<FBalanceParameterStatus> WithBalanceParameterStatusId(const TOptional<FString> BalanceParameterStatusId);
        TSharedPtr<FBalanceParameterStatus> WithUserId(const TOptional<FString> UserId);
        TSharedPtr<FBalanceParameterStatus> WithParameterName(const TOptional<FString> ParameterName);
        TSharedPtr<FBalanceParameterStatus> WithPropertyId(const TOptional<FString> PropertyId);
        TSharedPtr<FBalanceParameterStatus> WithParameterValues(const TSharedPtr<TArray<TSharedPtr<FBalanceParameterValue>>> ParameterValues);
        TSharedPtr<FBalanceParameterStatus> WithCreatedAt(const TOptional<int64> CreatedAt);
        TSharedPtr<FBalanceParameterStatus> WithUpdatedAt(const TOptional<int64> UpdatedAt);

        TOptional<FString> GetBalanceParameterStatusId() const;
        TOptional<FString> GetUserId() const;
        TOptional<FString> GetParameterName() const;
        TOptional<FString> GetPropertyId() const;
        TSharedPtr<TArray<TSharedPtr<FBalanceParameterValue>>> GetParameterValues() const;
        TOptional<int64> GetCreatedAt() const;
        FString GetCreatedAtString() const;
        TOptional<int64> GetUpdatedAt() const;
        FString GetUpdatedAtString() const;

        static TOptional<FString> GetRegionFromGrn(const FString Grn);
        static TOptional<FString> GetOwnerIdFromGrn(const FString Grn);
        static TOptional<FString> GetNamespaceNameFromGrn(const FString Grn);
        static TOptional<FString> GetUserIdFromGrn(const FString Grn);
        static TOptional<FString> GetParameterNameFromGrn(const FString Grn);
        static TOptional<FString> GetPropertyIdFromGrn(const FString Grn);

        static TSharedPtr<FBalanceParameterStatus> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;

        static FString TypeName;
    };
    typedef TSharedPtr<FBalanceParameterStatus, ESPMode::ThreadSafe> FBalanceParameterStatusPtr;
}