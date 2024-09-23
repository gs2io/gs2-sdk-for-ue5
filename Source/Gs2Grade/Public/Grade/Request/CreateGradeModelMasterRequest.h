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
    class FCreateGradeModelMasterRequest;

    class GS2GRADE_API FCreateGradeModelMasterRequest final : public TSharedFromThis<FCreateGradeModelMasterRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> NameValue;
        TOptional<FString> DescriptionValue;
        TOptional<FString> MetadataValue;
        TSharedPtr<TArray<TSharedPtr<Model::FDefaultGradeModel>>> DefaultGradesValue;
        TOptional<FString> ExperienceModelIdValue;
        TSharedPtr<TArray<TSharedPtr<Model::FGradeEntryModel>>> GradeEntriesValue;
        TSharedPtr<TArray<TSharedPtr<Model::FAcquireActionRate>>> AcquireActionRatesValue;
        
    public:
        
        FCreateGradeModelMasterRequest();
        FCreateGradeModelMasterRequest(
            const FCreateGradeModelMasterRequest& From
        );
        ~FCreateGradeModelMasterRequest() = default;

        TSharedPtr<FCreateGradeModelMasterRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FCreateGradeModelMasterRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FCreateGradeModelMasterRequest> WithName(const TOptional<FString> Name);
        TSharedPtr<FCreateGradeModelMasterRequest> WithDescription(const TOptional<FString> Description);
        TSharedPtr<FCreateGradeModelMasterRequest> WithMetadata(const TOptional<FString> Metadata);
        TSharedPtr<FCreateGradeModelMasterRequest> WithDefaultGrades(const TSharedPtr<TArray<TSharedPtr<Model::FDefaultGradeModel>>> DefaultGrades);
        TSharedPtr<FCreateGradeModelMasterRequest> WithExperienceModelId(const TOptional<FString> ExperienceModelId);
        TSharedPtr<FCreateGradeModelMasterRequest> WithGradeEntries(const TSharedPtr<TArray<TSharedPtr<Model::FGradeEntryModel>>> GradeEntries);
        TSharedPtr<FCreateGradeModelMasterRequest> WithAcquireActionRates(const TSharedPtr<TArray<TSharedPtr<Model::FAcquireActionRate>>> AcquireActionRates);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetName() const;
        TOptional<FString> GetDescription() const;
        TOptional<FString> GetMetadata() const;TSharedPtr<TArray<TSharedPtr<Model::FDefaultGradeModel>>> GetDefaultGrades() const;
        TOptional<FString> GetExperienceModelId() const;TSharedPtr<TArray<TSharedPtr<Model::FGradeEntryModel>>> GetGradeEntries() const;TSharedPtr<TArray<TSharedPtr<Model::FAcquireActionRate>>> GetAcquireActionRates() const;

        static TSharedPtr<FCreateGradeModelMasterRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FCreateGradeModelMasterRequest, ESPMode::ThreadSafe> FCreateGradeModelMasterRequestPtr;
}