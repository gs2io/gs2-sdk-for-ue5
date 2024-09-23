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

namespace Gs2::Grade::Request
{
    class FSetGradeByUserIdRequest;

    class GS2GRADE_API FSetGradeByUserIdRequest final : public TSharedFromThis<FSetGradeByUserIdRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> UserIdValue;
        TOptional<FString> GradeNameValue;
        TOptional<FString> PropertyIdValue;
        TOptional<int64> GradeValueValue;
        TOptional<FString> TimeOffsetTokenValue;
        TOptional<FString> DuplicationAvoiderValue;
        
    public:
        
        FSetGradeByUserIdRequest();
        FSetGradeByUserIdRequest(
            const FSetGradeByUserIdRequest& From
        );
        ~FSetGradeByUserIdRequest() = default;

        TSharedPtr<FSetGradeByUserIdRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FSetGradeByUserIdRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FSetGradeByUserIdRequest> WithUserId(const TOptional<FString> UserId);
        TSharedPtr<FSetGradeByUserIdRequest> WithGradeName(const TOptional<FString> GradeName);
        TSharedPtr<FSetGradeByUserIdRequest> WithPropertyId(const TOptional<FString> PropertyId);
        TSharedPtr<FSetGradeByUserIdRequest> WithGradeValue(const TOptional<int64> GradeValue);
        TSharedPtr<FSetGradeByUserIdRequest> WithTimeOffsetToken(const TOptional<FString> TimeOffsetToken);
        TSharedPtr<FSetGradeByUserIdRequest> WithDuplicationAvoider(const TOptional<FString> DuplicationAvoider);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetUserId() const;
        TOptional<FString> GetGradeName() const;
        TOptional<FString> GetPropertyId() const;
        TOptional<int64> GetGradeValue() const;
        FString GetGradeValueString() const;
        TOptional<FString> GetTimeOffsetToken() const;
        TOptional<FString> GetDuplicationAvoider() const;

        static TSharedPtr<FSetGradeByUserIdRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FSetGradeByUserIdRequest, ESPMode::ThreadSafe> FSetGradeByUserIdRequestPtr;
}