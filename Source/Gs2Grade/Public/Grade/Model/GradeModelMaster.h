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
#include "DefaultGradeModel.h"
#include "GradeEntryModel.h"
#include "AcquireActionRate.h"

namespace Gs2::Grade::Model
{
    class GS2GRADE_API FGradeModelMaster final : public FGs2Object, public TSharedFromThis<FGradeModelMaster>
    {
        TOptional<FString> GradeModelIdValue;
        TOptional<FString> NameValue;
        TOptional<FString> DescriptionValue;
        TOptional<FString> MetadataValue;
        TSharedPtr<TArray<TSharedPtr<FDefaultGradeModel>>> DefaultGradesValue;
        TOptional<FString> ExperienceModelIdValue;
        TSharedPtr<TArray<TSharedPtr<FGradeEntryModel>>> GradeEntriesValue;
        TSharedPtr<TArray<TSharedPtr<FAcquireActionRate>>> AcquireActionRatesValue;
        TOptional<int64> CreatedAtValue;
        TOptional<int64> UpdatedAtValue;
        TOptional<int64> RevisionValue;

    public:
        FGradeModelMaster();
        FGradeModelMaster(
            const FGradeModelMaster& From
        );
        virtual ~FGradeModelMaster() override = default;

        TSharedPtr<FGradeModelMaster> WithGradeModelId(const TOptional<FString> GradeModelId);
        TSharedPtr<FGradeModelMaster> WithName(const TOptional<FString> Name);
        TSharedPtr<FGradeModelMaster> WithDescription(const TOptional<FString> Description);
        TSharedPtr<FGradeModelMaster> WithMetadata(const TOptional<FString> Metadata);
        TSharedPtr<FGradeModelMaster> WithDefaultGrades(const TSharedPtr<TArray<TSharedPtr<FDefaultGradeModel>>> DefaultGrades);
        TSharedPtr<FGradeModelMaster> WithExperienceModelId(const TOptional<FString> ExperienceModelId);
        TSharedPtr<FGradeModelMaster> WithGradeEntries(const TSharedPtr<TArray<TSharedPtr<FGradeEntryModel>>> GradeEntries);
        TSharedPtr<FGradeModelMaster> WithAcquireActionRates(const TSharedPtr<TArray<TSharedPtr<FAcquireActionRate>>> AcquireActionRates);
        TSharedPtr<FGradeModelMaster> WithCreatedAt(const TOptional<int64> CreatedAt);
        TSharedPtr<FGradeModelMaster> WithUpdatedAt(const TOptional<int64> UpdatedAt);
        TSharedPtr<FGradeModelMaster> WithRevision(const TOptional<int64> Revision);

        TOptional<FString> GetGradeModelId() const;
        TOptional<FString> GetName() const;
        TOptional<FString> GetDescription() const;
        TOptional<FString> GetMetadata() const;
        TSharedPtr<TArray<TSharedPtr<FDefaultGradeModel>>> GetDefaultGrades() const;
        TOptional<FString> GetExperienceModelId() const;
        TSharedPtr<TArray<TSharedPtr<FGradeEntryModel>>> GetGradeEntries() const;
        TSharedPtr<TArray<TSharedPtr<FAcquireActionRate>>> GetAcquireActionRates() const;
        TOptional<int64> GetCreatedAt() const;
        FString GetCreatedAtString() const;
        TOptional<int64> GetUpdatedAt() const;
        FString GetUpdatedAtString() const;
        TOptional<int64> GetRevision() const;
        FString GetRevisionString() const;

        static TOptional<FString> GetRegionFromGrn(const FString Grn);
        static TOptional<FString> GetOwnerIdFromGrn(const FString Grn);
        static TOptional<FString> GetNamespaceNameFromGrn(const FString Grn);
        static TOptional<FString> GetGradeNameFromGrn(const FString Grn);

        static TSharedPtr<FGradeModelMaster> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;

        static FString TypeName;
    };
    typedef TSharedPtr<FGradeModelMaster, ESPMode::ThreadSafe> FGradeModelMasterPtr;
}