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
    class FApplyRankCapRequest;

    class GS2GRADE_API FApplyRankCapRequest final : public TSharedFromThis<FApplyRankCapRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> AccessTokenValue;
        TOptional<FString> GradeNameValue;
        TOptional<FString> PropertyIdValue;
        TOptional<FString> DuplicationAvoiderValue;
        
    public:
        
        FApplyRankCapRequest();
        FApplyRankCapRequest(
            const FApplyRankCapRequest& From
        );
        ~FApplyRankCapRequest() = default;

        TSharedPtr<FApplyRankCapRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FApplyRankCapRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FApplyRankCapRequest> WithAccessToken(const TOptional<FString> AccessToken);
        TSharedPtr<FApplyRankCapRequest> WithGradeName(const TOptional<FString> GradeName);
        TSharedPtr<FApplyRankCapRequest> WithPropertyId(const TOptional<FString> PropertyId);
        TSharedPtr<FApplyRankCapRequest> WithDuplicationAvoider(const TOptional<FString> DuplicationAvoider);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetAccessToken() const;
        TOptional<FString> GetGradeName() const;
        TOptional<FString> GetPropertyId() const;
        TOptional<FString> GetDuplicationAvoider() const;

        static TSharedPtr<FApplyRankCapRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FApplyRankCapRequest> FApplyRankCapRequestPtr;
}