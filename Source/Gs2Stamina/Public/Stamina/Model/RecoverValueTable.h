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

namespace Gs2::Stamina::Model
{
    class GS2STAMINA_API FRecoverValueTable final : public TSharedFromThis<FRecoverValueTable>
    {
        TOptional<FString> RecoverValueTableIdValue;
        TOptional<FString> NameValue;
        TOptional<FString> MetadataValue;
        TOptional<FString> ExperienceModelIdValue;
        TSharedPtr<TArray<int32>> ValuesValue;

    public:
        FRecoverValueTable();
        FRecoverValueTable(
            const FRecoverValueTable& From
        );
        ~FRecoverValueTable() = default;

        TSharedPtr<FRecoverValueTable> WithRecoverValueTableId(const TOptional<FString> RecoverValueTableId);
        TSharedPtr<FRecoverValueTable> WithName(const TOptional<FString> Name);
        TSharedPtr<FRecoverValueTable> WithMetadata(const TOptional<FString> Metadata);
        TSharedPtr<FRecoverValueTable> WithExperienceModelId(const TOptional<FString> ExperienceModelId);
        TSharedPtr<FRecoverValueTable> WithValues(const TSharedPtr<TArray<int32>> Values);

        TOptional<FString> GetRecoverValueTableId() const;
        TOptional<FString> GetName() const;
        TOptional<FString> GetMetadata() const;
        TOptional<FString> GetExperienceModelId() const;
        TSharedPtr<TArray<int32>> GetValues() const;

        static TOptional<FString> GetRegionFromGrn(const FString Grn);
        static TOptional<FString> GetOwnerIdFromGrn(const FString Grn);
        static TOptional<FString> GetNamespaceNameFromGrn(const FString Grn);
        static TOptional<FString> GetRecoverValueTableNameFromGrn(const FString Grn);

        static TSharedPtr<FRecoverValueTable> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;

        static FString TypeName;
    };
    typedef TSharedPtr<FRecoverValueTable, ESPMode::ThreadSafe> FRecoverValueTablePtr;
}