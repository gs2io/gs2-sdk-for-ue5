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

namespace Gs2::Grade::Model
{
    class GS2GRADE_API FStatus final : public FGs2Object, public TSharedFromThis<FStatus>
    {
        TOptional<FString> StatusIdValue;
        TOptional<FString> GradeNameValue;
        TOptional<FString> UserIdValue;
        TOptional<FString> PropertyIdValue;
        TOptional<int64> GradeValueValue;
        TOptional<int64> CreatedAtValue;
        TOptional<int64> UpdatedAtValue;
        TOptional<int64> RevisionValue;

    public:
        FStatus();
        FStatus(
            const FStatus& From
        );
        virtual ~FStatus() override = default;

        TSharedPtr<FStatus> WithStatusId(const TOptional<FString> StatusId);
        TSharedPtr<FStatus> WithGradeName(const TOptional<FString> GradeName);
        TSharedPtr<FStatus> WithUserId(const TOptional<FString> UserId);
        TSharedPtr<FStatus> WithPropertyId(const TOptional<FString> PropertyId);
        TSharedPtr<FStatus> WithGradeValue(const TOptional<int64> GradeValue);
        TSharedPtr<FStatus> WithCreatedAt(const TOptional<int64> CreatedAt);
        TSharedPtr<FStatus> WithUpdatedAt(const TOptional<int64> UpdatedAt);
        TSharedPtr<FStatus> WithRevision(const TOptional<int64> Revision);

        TOptional<FString> GetStatusId() const;
        TOptional<FString> GetGradeName() const;
        TOptional<FString> GetUserId() const;
        TOptional<FString> GetPropertyId() const;
        TOptional<int64> GetGradeValue() const;
        FString GetGradeValueString() const;
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
        static TOptional<FString> GetGradeNameFromGrn(const FString Grn);
        static TOptional<FString> GetPropertyIdFromGrn(const FString Grn);

        static TSharedPtr<FStatus> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;

        static FString TypeName;
    };
    typedef TSharedPtr<FStatus, ESPMode::ThreadSafe> FStatusPtr;
}