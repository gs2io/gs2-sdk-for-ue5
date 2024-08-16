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
#include "Dom/JsonObject.h"

namespace Gs2::Grade::Request
{
    class FGetGradeModelRequest;

    class GS2GRADE_API FGetGradeModelRequest final : public TSharedFromThis<FGetGradeModelRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> GradeNameValue;
        
    public:
        
        FGetGradeModelRequest();
        FGetGradeModelRequest(
            const FGetGradeModelRequest& From
        );
        ~FGetGradeModelRequest() = default;

        TSharedPtr<FGetGradeModelRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FGetGradeModelRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FGetGradeModelRequest> WithGradeName(const TOptional<FString> GradeName);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetGradeName() const;

        static TSharedPtr<FGetGradeModelRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FGetGradeModelRequest> FGetGradeModelRequestPtr;
}