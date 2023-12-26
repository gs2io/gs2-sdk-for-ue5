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
    class GS2GRADE_API FGradeModel final : public Gs2Object, public TSharedFromThis<FGradeModel>
    {
        TOptional<FString> GradeModelIdValue;
        TOptional<FString> NameValue;
        TOptional<FString> MetadataValue;
        TSharedPtr<TArray<TSharedPtr<FDefaultGradeModel>>> DefaultGradesValue;
        TOptional<FString> ExperienceModelIdValue;
        TSharedPtr<TArray<TSharedPtr<FGradeEntryModel>>> GradeEntriesValue;
        TSharedPtr<TArray<TSharedPtr<FAcquireActionRate>>> AcquireActionRatesValue;

    public:
        FGradeModel();
        FGradeModel(
            const FGradeModel& From
        );
        virtual ~FGradeModel() override = default;

        TSharedPtr<FGradeModel> WithGradeModelId(const TOptional<FString> GradeModelId);
        TSharedPtr<FGradeModel> WithName(const TOptional<FString> Name);
        TSharedPtr<FGradeModel> WithMetadata(const TOptional<FString> Metadata);
        TSharedPtr<FGradeModel> WithDefaultGrades(const TSharedPtr<TArray<TSharedPtr<FDefaultGradeModel>>> DefaultGrades);
        TSharedPtr<FGradeModel> WithExperienceModelId(const TOptional<FString> ExperienceModelId);
        TSharedPtr<FGradeModel> WithGradeEntries(const TSharedPtr<TArray<TSharedPtr<FGradeEntryModel>>> GradeEntries);
        TSharedPtr<FGradeModel> WithAcquireActionRates(const TSharedPtr<TArray<TSharedPtr<FAcquireActionRate>>> AcquireActionRates);

        TOptional<FString> GetGradeModelId() const;
        TOptional<FString> GetName() const;
        TOptional<FString> GetMetadata() const;
        TSharedPtr<TArray<TSharedPtr<FDefaultGradeModel>>> GetDefaultGrades() const;
        TOptional<FString> GetExperienceModelId() const;
        TSharedPtr<TArray<TSharedPtr<FGradeEntryModel>>> GetGradeEntries() const;
        TSharedPtr<TArray<TSharedPtr<FAcquireActionRate>>> GetAcquireActionRates() const;

        static TOptional<FString> GetRegionFromGrn(const FString Grn);
        static TOptional<FString> GetOwnerIdFromGrn(const FString Grn);
        static TOptional<FString> GetNamespaceNameFromGrn(const FString Grn);
        static TOptional<FString> GetGradeNameFromGrn(const FString Grn);

        static TSharedPtr<FGradeModel> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;

        static FString TypeName;
    };
    typedef TSharedPtr<FGradeModel, ESPMode::ThreadSafe> FGradeModelPtr;
}