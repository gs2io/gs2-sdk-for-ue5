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

namespace Gs2::Experience::Request
{
    class FGetExperienceModelMasterRequest;

    class GS2EXPERIENCE_API FGetExperienceModelMasterRequest final : public TSharedFromThis<FGetExperienceModelMasterRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> ExperienceNameValue;
        
    public:
        
        FGetExperienceModelMasterRequest();
        FGetExperienceModelMasterRequest(
            const FGetExperienceModelMasterRequest& From
        );
        ~FGetExperienceModelMasterRequest() = default;

        TSharedPtr<FGetExperienceModelMasterRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FGetExperienceModelMasterRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FGetExperienceModelMasterRequest> WithExperienceName(const TOptional<FString> ExperienceName);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetExperienceName() const;

        static TSharedPtr<FGetExperienceModelMasterRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FGetExperienceModelMasterRequest, ESPMode::ThreadSafe> FGetExperienceModelMasterRequestPtr;
}