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
    class GS2DATASTORE_API FDataObjectHistory final : public TSharedFromThis<FDataObjectHistory>
    {
        TOptional<FString> DataObjectHistoryIdValue;
        TOptional<FString> DataObjectNameValue;
        TOptional<FString> GenerationValue;
        TOptional<int64> ContentLengthValue;
        TOptional<int64> CreatedAtValue;

    public:
        FDataObjectHistory();
        FDataObjectHistory(
            const FDataObjectHistory& From
        );
        ~FDataObjectHistory() = default;

        TSharedPtr<FDataObjectHistory> WithDataObjectHistoryId(const TOptional<FString> DataObjectHistoryId);
        TSharedPtr<FDataObjectHistory> WithDataObjectName(const TOptional<FString> DataObjectName);
        TSharedPtr<FDataObjectHistory> WithGeneration(const TOptional<FString> Generation);
        TSharedPtr<FDataObjectHistory> WithContentLength(const TOptional<int64> ContentLength);
        TSharedPtr<FDataObjectHistory> WithCreatedAt(const TOptional<int64> CreatedAt);

        TOptional<FString> GetDataObjectHistoryId() const;
        TOptional<FString> GetDataObjectName() const;
        TOptional<FString> GetGeneration() const;
        TOptional<int64> GetContentLength() const;
        FString GetContentLengthString() const;
        TOptional<int64> GetCreatedAt() const;
        FString GetCreatedAtString() const;

        static TOptional<FString> GetRegionFromGrn(const FString Grn);
        static TOptional<FString> GetOwnerIdFromGrn(const FString Grn);
        static TOptional<FString> GetNamespaceNameFromGrn(const FString Grn);
        static TOptional<FString> GetUserIdFromGrn(const FString Grn);
        static TOptional<FString> GetDataObjectNameFromGrn(const FString Grn);
        static TOptional<FString> GetGenerationFromGrn(const FString Grn);

        static TSharedPtr<FDataObjectHistory> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;

        static FString TypeName;
    };
    typedef TSharedPtr<FDataObjectHistory, ESPMode::ThreadSafe> FDataObjectHistoryPtr;
}