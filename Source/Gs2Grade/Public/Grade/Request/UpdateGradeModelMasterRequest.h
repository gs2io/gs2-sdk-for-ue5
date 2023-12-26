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
#include "../Model/DefaultGradeModel.h"
#include "../Model/GradeEntryModel.h"
#include "../Model/AcquireActionRate.h"

namespace Gs2::Grade::Request
{
    class FUpdateGradeModelMasterRequest;

    class GS2GRADE_API FUpdateGradeModelMasterRequest final : public TSharedFromThis<FUpdateGradeModelMasterRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> GradeNameValue;
        TOptional<FString> DescriptionValue;
        TOptional<FString> MetadataValue;
        TSharedPtr<TArray<TSharedPtr<Model::FDefaultGradeModel>>> DefaultGradesValue;
        TOptional<FString> ExperienceModelIdValue;
        TSharedPtr<TArray<TSharedPtr<Model::FGradeEntryModel>>> GradeEntriesValue;
        TSharedPtr<TArray<TSharedPtr<Model::FAcquireActionRate>>> AcquireActionRatesValue;
        
    public:
        
        FUpdateGradeModelMasterRequest();
        FUpdateGradeModelMasterRequest(
            const FUpdateGradeModelMasterRequest& From
        );
        ~FUpdateGradeModelMasterRequest() = default;

        TSharedPtr<FUpdateGradeModelMasterRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FUpdateGradeModelMasterRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FUpdateGradeModelMasterRequest> WithGradeName(const TOptional<FString> GradeName);
        TSharedPtr<FUpdateGradeModelMasterRequest> WithDescription(const TOptional<FString> Description);
        TSharedPtr<FUpdateGradeModelMasterRequest> WithMetadata(const TOptional<FString> Metadata);
        TSharedPtr<FUpdateGradeModelMasterRequest> WithDefaultGrades(const TSharedPtr<TArray<TSharedPtr<Model::FDefaultGradeModel>>> DefaultGrades);
        TSharedPtr<FUpdateGradeModelMasterRequest> WithExperienceModelId(const TOptional<FString> ExperienceModelId);
        TSharedPtr<FUpdateGradeModelMasterRequest> WithGradeEntries(const TSharedPtr<TArray<TSharedPtr<Model::FGradeEntryModel>>> GradeEntries);
        TSharedPtr<FUpdateGradeModelMasterRequest> WithAcquireActionRates(const TSharedPtr<TArray<TSharedPtr<Model::FAcquireActionRate>>> AcquireActionRates);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetGradeName() const;
        TOptional<FString> GetDescription() const;
        TOptional<FString> GetMetadata() const;TSharedPtr<TArray<TSharedPtr<Model::FDefaultGradeModel>>> GetDefaultGrades() const;
        TOptional<FString> GetExperienceModelId() const;TSharedPtr<TArray<TSharedPtr<Model::FGradeEntryModel>>> GetGradeEntries() const;TSharedPtr<TArray<TSharedPtr<Model::FAcquireActionRate>>> GetAcquireActionRates() const;

        static TSharedPtr<FUpdateGradeModelMasterRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FUpdateGradeModelMasterRequest, ESPMode::ThreadSafe> FUpdateGradeModelMasterRequestPtr;
}