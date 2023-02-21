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

namespace Gs2::Datastore::Model
{
    class GS2DATASTORE_API FDataObject final : public TSharedFromThis<FDataObject>
    {
        TOptional<FString> DataObjectIdValue;
        TOptional<FString> NameValue;
        TOptional<FString> UserIdValue;
        TOptional<FString> ScopeValue;
        TSharedPtr<TArray<FString>> AllowUserIdsValue;
        TOptional<FString> StatusValue;
        TOptional<FString> GenerationValue;
        TOptional<FString> PreviousGenerationValue;
        TOptional<int64> CreatedAtValue;
        TOptional<int64> UpdatedAtValue;

    public:
        FDataObject();
        FDataObject(
            const FDataObject& From
        );
        ~FDataObject() = default;

        TSharedPtr<FDataObject> WithDataObjectId(const TOptional<FString> DataObjectId);
        TSharedPtr<FDataObject> WithName(const TOptional<FString> Name);
        TSharedPtr<FDataObject> WithUserId(const TOptional<FString> UserId);
        TSharedPtr<FDataObject> WithScope(const TOptional<FString> Scope);
        TSharedPtr<FDataObject> WithAllowUserIds(const TSharedPtr<TArray<FString>> AllowUserIds);
        TSharedPtr<FDataObject> WithStatus(const TOptional<FString> Status);
        TSharedPtr<FDataObject> WithGeneration(const TOptional<FString> Generation);
        TSharedPtr<FDataObject> WithPreviousGeneration(const TOptional<FString> PreviousGeneration);
        TSharedPtr<FDataObject> WithCreatedAt(const TOptional<int64> CreatedAt);
        TSharedPtr<FDataObject> WithUpdatedAt(const TOptional<int64> UpdatedAt);

        TOptional<FString> GetDataObjectId() const;
        TOptional<FString> GetName() const;
        TOptional<FString> GetUserId() const;
        TOptional<FString> GetScope() const;
        TSharedPtr<TArray<FString>> GetAllowUserIds() const;
        TOptional<FString> GetStatus() const;
        TOptional<FString> GetGeneration() const;
        TOptional<FString> GetPreviousGeneration() const;
        TOptional<int64> GetCreatedAt() const;
        FString GetCreatedAtString() const;
        TOptional<int64> GetUpdatedAt() const;
        FString GetUpdatedAtString() const;

        static TOptional<FString> GetRegionFromGrn(const FString Grn);
        static TOptional<FString> GetOwnerIdFromGrn(const FString Grn);
        static TOptional<FString> GetNamespaceNameFromGrn(const FString Grn);
        static TOptional<FString> GetUserIdFromGrn(const FString Grn);
        static TOptional<FString> GetDataObjectNameFromGrn(const FString Grn);

        static TSharedPtr<FDataObject> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;

        static FString TypeName;
    };
    typedef TSharedPtr<FDataObject, ESPMode::ThreadSafe> FDataObjectPtr;
}