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
#include "../Model/Status.h"
#include "Gs2Experience/Public/Experience/Model/Status.h"

namespace Gs2::Grade::Result
{
    class GS2GRADE_API FSubGradeByStampTaskResult final : public TSharedFromThis<FSubGradeByStampTaskResult>
    {
        TSharedPtr<Model::FStatus> ItemValue;
        TOptional<FString> NewContextStackValue;
        TOptional<FString> ExperienceNamespaceNameValue;
        TSharedPtr<Gs2::Experience::Model::FStatus> ExperienceStatusValue;
        
    public:
        
        FSubGradeByStampTaskResult();
        FSubGradeByStampTaskResult(
            const FSubGradeByStampTaskResult& From
        );
        ~FSubGradeByStampTaskResult() = default;

        TSharedPtr<FSubGradeByStampTaskResult> WithItem(const TSharedPtr<Model::FStatus> Item);
        TSharedPtr<FSubGradeByStampTaskResult> WithNewContextStack(const TOptional<FString> NewContextStack);
        TSharedPtr<FSubGradeByStampTaskResult> WithExperienceNamespaceName(const TOptional<FString> ExperienceNamespaceName);
        TSharedPtr<FSubGradeByStampTaskResult> WithExperienceStatus(const TSharedPtr<Gs2::Experience::Model::FStatus> ExperienceStatus);

        TSharedPtr<Model::FStatus> GetItem() const;
        TOptional<FString> GetNewContextStack() const;
        TOptional<FString> GetExperienceNamespaceName() const;
        TSharedPtr<Gs2::Experience::Model::FStatus> GetExperienceStatus() const;

        static TSharedPtr<FSubGradeByStampTaskResult> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FSubGradeByStampTaskResult, ESPMode::ThreadSafe> FSubGradeByStampTaskResultPtr;
}