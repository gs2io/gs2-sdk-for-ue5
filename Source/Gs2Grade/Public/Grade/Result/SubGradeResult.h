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
    class GS2GRADE_API FSubGradeResult final : public TSharedFromThis<FSubGradeResult>
    {
        TSharedPtr<Model::FStatus> ItemValue;
        TOptional<FString> ExperienceNamespaceNameValue;
        TSharedPtr<Gs2::Experience::Model::FStatus> ExperienceStatusValue;
        
    public:
        
        FSubGradeResult();
        FSubGradeResult(
            const FSubGradeResult& From
        );
        ~FSubGradeResult() = default;

        TSharedPtr<FSubGradeResult> WithItem(const TSharedPtr<Model::FStatus> Item);
        TSharedPtr<FSubGradeResult> WithExperienceNamespaceName(const TOptional<FString> ExperienceNamespaceName);
        TSharedPtr<FSubGradeResult> WithExperienceStatus(const TSharedPtr<Gs2::Experience::Model::FStatus> ExperienceStatus);

        TSharedPtr<Model::FStatus> GetItem() const;
        TOptional<FString> GetExperienceNamespaceName() const;
        TSharedPtr<Gs2::Experience::Model::FStatus> GetExperienceStatus() const;

        static TSharedPtr<FSubGradeResult> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FSubGradeResult, ESPMode::ThreadSafe> FSubGradeResultPtr;
}