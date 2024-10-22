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

namespace Gs2::Dictionary::Model
{
    class GS2DICTIONARY_API FEntryModel final : public Gs2Object, public TSharedFromThis<FEntryModel>
    {
        TOptional<FString> EntryModelIdValue;
        TOptional<FString> NameValue;
        TOptional<FString> MetadataValue;

    public:
        FEntryModel();
        FEntryModel(
            const FEntryModel& From
        );
        virtual ~FEntryModel() override = default;

        TSharedPtr<FEntryModel> WithEntryModelId(const TOptional<FString> EntryModelId);
        TSharedPtr<FEntryModel> WithName(const TOptional<FString> Name);
        TSharedPtr<FEntryModel> WithMetadata(const TOptional<FString> Metadata);

        TOptional<FString> GetEntryModelId() const;
        TOptional<FString> GetName() const;
        TOptional<FString> GetMetadata() const;

        static TOptional<FString> GetRegionFromGrn(const FString Grn);
        static TOptional<FString> GetOwnerIdFromGrn(const FString Grn);
        static TOptional<FString> GetNamespaceNameFromGrn(const FString Grn);
        static TOptional<FString> GetEntryModelNameFromGrn(const FString Grn);

        static TSharedPtr<FEntryModel> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;

        static FString TypeName;
    };
    typedef TSharedPtr<FEntryModel, ESPMode::ThreadSafe> FEntryModelPtr;
}