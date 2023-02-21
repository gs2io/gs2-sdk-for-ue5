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
#include "Datastore/Model/DataObjectHistory.h"

namespace Gs2::UE5::Datastore::Model
{
	class EZGS2_API FEzDataObjectHistory final : public TSharedFromThis<FEzDataObjectHistory>
	{
        TOptional<FString> DataObjectHistoryIdValue;
        TOptional<FString> GenerationValue;
        TOptional<int64> ContentLengthValue;
        TOptional<int64> CreatedAtValue;

	public:
        TSharedPtr<FEzDataObjectHistory> WithDataObjectHistoryId(const TOptional<FString> DataObjectHistoryId);
        TSharedPtr<FEzDataObjectHistory> WithGeneration(const TOptional<FString> Generation);
        TSharedPtr<FEzDataObjectHistory> WithContentLength(const TOptional<int64> ContentLength);
        TSharedPtr<FEzDataObjectHistory> WithCreatedAt(const TOptional<int64> CreatedAt);

        TOptional<FString> GetDataObjectHistoryId() const;

        TOptional<FString> GetGeneration() const;

        TOptional<int64> GetContentLength() const;
        FString GetContentLengthString() const;

        TOptional<int64> GetCreatedAt() const;
        FString GetCreatedAtString() const;

        Gs2::Datastore::Model::FDataObjectHistoryPtr ToModel() const;
        static TSharedPtr<FEzDataObjectHistory> FromModel(Gs2::Datastore::Model::FDataObjectHistoryPtr Model);
    };
    typedef TSharedPtr<FEzDataObjectHistory> FEzDataObjectHistoryPtr;
}