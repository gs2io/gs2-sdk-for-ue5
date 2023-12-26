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
    class FAddGradeByUserIdRequest;

    class GS2GRADE_API FAddGradeByUserIdRequest final : public TSharedFromThis<FAddGradeByUserIdRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> UserIdValue;
        TOptional<FString> GradeNameValue;
        TOptional<FString> PropertyIdValue;
        TOptional<int64> GradeValueValue;
        TOptional<FString> DuplicationAvoiderValue;
        
    public:
        
        FAddGradeByUserIdRequest();
        FAddGradeByUserIdRequest(
            const FAddGradeByUserIdRequest& From
        );
        ~FAddGradeByUserIdRequest() = default;

        TSharedPtr<FAddGradeByUserIdRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FAddGradeByUserIdRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FAddGradeByUserIdRequest> WithUserId(const TOptional<FString> UserId);
        TSharedPtr<FAddGradeByUserIdRequest> WithGradeName(const TOptional<FString> GradeName);
        TSharedPtr<FAddGradeByUserIdRequest> WithPropertyId(const TOptional<FString> PropertyId);
        TSharedPtr<FAddGradeByUserIdRequest> WithGradeValue(const TOptional<int64> GradeValue);
        TSharedPtr<FAddGradeByUserIdRequest> WithDuplicationAvoider(const TOptional<FString> DuplicationAvoider);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetUserId() const;
        TOptional<FString> GetGradeName() const;
        TOptional<FString> GetPropertyId() const;
        TOptional<int64> GetGradeValue() const;
        FString GetGradeValueString() const;
        TOptional<FString> GetDuplicationAvoider() const;

        static TSharedPtr<FAddGradeByUserIdRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FAddGradeByUserIdRequest, ESPMode::ThreadSafe> FAddGradeByUserIdRequestPtr;
}