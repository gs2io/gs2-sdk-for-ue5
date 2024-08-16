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
    class FApplyRankCapByUserIdRequest;

    class GS2GRADE_API FApplyRankCapByUserIdRequest final : public TSharedFromThis<FApplyRankCapByUserIdRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> UserIdValue;
        TOptional<FString> GradeNameValue;
        TOptional<FString> PropertyIdValue;
        TOptional<FString> TimeOffsetTokenValue;
        TOptional<FString> DuplicationAvoiderValue;
        
    public:
        
        FApplyRankCapByUserIdRequest();
        FApplyRankCapByUserIdRequest(
            const FApplyRankCapByUserIdRequest& From
        );
        ~FApplyRankCapByUserIdRequest() = default;

        TSharedPtr<FApplyRankCapByUserIdRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FApplyRankCapByUserIdRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FApplyRankCapByUserIdRequest> WithUserId(const TOptional<FString> UserId);
        TSharedPtr<FApplyRankCapByUserIdRequest> WithGradeName(const TOptional<FString> GradeName);
        TSharedPtr<FApplyRankCapByUserIdRequest> WithPropertyId(const TOptional<FString> PropertyId);
        TSharedPtr<FApplyRankCapByUserIdRequest> WithTimeOffsetToken(const TOptional<FString> TimeOffsetToken);
        TSharedPtr<FApplyRankCapByUserIdRequest> WithDuplicationAvoider(const TOptional<FString> DuplicationAvoider);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetUserId() const;
        TOptional<FString> GetGradeName() const;
        TOptional<FString> GetPropertyId() const;
        TOptional<FString> GetTimeOffsetToken() const;
        TOptional<FString> GetDuplicationAvoider() const;

        static TSharedPtr<FApplyRankCapByUserIdRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FApplyRankCapByUserIdRequest> FApplyRankCapByUserIdRequestPtr;
}