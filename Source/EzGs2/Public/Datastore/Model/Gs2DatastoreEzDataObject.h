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
#include "Datastore/Model/DataObject.h"

namespace Gs2::UE5::Datastore::Model
{
	class EZGS2_API FEzDataObject final : public TSharedFromThis<FEzDataObject>
	{
        TOptional<FString> DataObjectIdValue;
        TOptional<FString> NameValue;
        TOptional<FString> UserIdValue;
        TOptional<FString> ScopeValue;
        TSharedPtr<TArray<FString>> AllowUserIdsValue;
        TOptional<FString> StatusValue;
        TOptional<FString> GenerationValue;
        TOptional<int64> CreatedAtValue;
        TOptional<int64> UpdatedAtValue;

	public:
        TSharedPtr<FEzDataObject> WithDataObjectId(const TOptional<FString> DataObjectId);
        TSharedPtr<FEzDataObject> WithName(const TOptional<FString> Name);
        TSharedPtr<FEzDataObject> WithUserId(const TOptional<FString> UserId);
        TSharedPtr<FEzDataObject> WithScope(const TOptional<FString> Scope);
        TSharedPtr<FEzDataObject> WithAllowUserIds(const TSharedPtr<TArray<FString>> AllowUserIds);
        TSharedPtr<FEzDataObject> WithStatus(const TOptional<FString> Status);
        TSharedPtr<FEzDataObject> WithGeneration(const TOptional<FString> Generation);
        TSharedPtr<FEzDataObject> WithCreatedAt(const TOptional<int64> CreatedAt);
        TSharedPtr<FEzDataObject> WithUpdatedAt(const TOptional<int64> UpdatedAt);

        TOptional<FString> GetDataObjectId() const;

        TOptional<FString> GetName() const;

        TOptional<FString> GetUserId() const;

        TOptional<FString> GetScope() const;

        TSharedPtr<TArray<FString>> GetAllowUserIds() const;

        TOptional<FString> GetStatus() const;

        TOptional<FString> GetGeneration() const;

        TOptional<int64> GetCreatedAt() const;
        FString GetCreatedAtString() const;

        TOptional<int64> GetUpdatedAt() const;
        FString GetUpdatedAtString() const;

        Gs2::Datastore::Model::FDataObjectPtr ToModel() const;
        static TSharedPtr<FEzDataObject> FromModel(Gs2::Datastore::Model::FDataObjectPtr Model);
    };
    typedef TSharedPtr<FEzDataObject> FEzDataObjectPtr;
}