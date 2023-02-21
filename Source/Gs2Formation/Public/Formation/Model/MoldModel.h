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
#include "FormModel.h"

namespace Gs2::Formation::Model
{
    class GS2FORMATION_API FMoldModel final : public TSharedFromThis<FMoldModel>
    {
        TOptional<FString> MoldModelIdValue;
        TOptional<FString> NameValue;
        TOptional<FString> MetadataValue;
        TOptional<int32> InitialMaxCapacityValue;
        TOptional<int32> MaxCapacityValue;
        TSharedPtr<FFormModel> FormModelValue;

    public:
        FMoldModel();
        FMoldModel(
            const FMoldModel& From
        );
        ~FMoldModel() = default;

        TSharedPtr<FMoldModel> WithMoldModelId(const TOptional<FString> MoldModelId);
        TSharedPtr<FMoldModel> WithName(const TOptional<FString> Name);
        TSharedPtr<FMoldModel> WithMetadata(const TOptional<FString> Metadata);
        TSharedPtr<FMoldModel> WithInitialMaxCapacity(const TOptional<int32> InitialMaxCapacity);
        TSharedPtr<FMoldModel> WithMaxCapacity(const TOptional<int32> MaxCapacity);
        TSharedPtr<FMoldModel> WithFormModel(const TSharedPtr<FFormModel> FormModel);

        TOptional<FString> GetMoldModelId() const;
        TOptional<FString> GetName() const;
        TOptional<FString> GetMetadata() const;
        TOptional<int32> GetInitialMaxCapacity() const;
        FString GetInitialMaxCapacityString() const;
        TOptional<int32> GetMaxCapacity() const;
        FString GetMaxCapacityString() const;
        TSharedPtr<FFormModel> GetFormModel() const;

        static TOptional<FString> GetRegionFromGrn(const FString Grn);
        static TOptional<FString> GetOwnerIdFromGrn(const FString Grn);
        static TOptional<FString> GetNamespaceNameFromGrn(const FString Grn);
        static TOptional<FString> GetMoldNameFromGrn(const FString Grn);

        static TSharedPtr<FMoldModel> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;

        static FString TypeName;
    };
    typedef TSharedPtr<FMoldModel, ESPMode::ThreadSafe> FMoldModelPtr;
}