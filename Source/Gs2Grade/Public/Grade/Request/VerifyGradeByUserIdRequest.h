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
    class FVerifyGradeByUserIdRequest;

    class GS2GRADE_API FVerifyGradeByUserIdRequest final : public TSharedFromThis<FVerifyGradeByUserIdRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> UserIdValue;
        TOptional<FString> GradeNameValue;
        TOptional<FString> VerifyTypeValue;
        TOptional<FString> PropertyIdValue;
        TOptional<int64> GradeValueValue;
        TOptional<bool> MultiplyValueSpecifyingQuantityValue;
        TOptional<FString> TimeOffsetTokenValue;
        TOptional<FString> DuplicationAvoiderValue;
        
    public:
        
        FVerifyGradeByUserIdRequest();
        FVerifyGradeByUserIdRequest(
            const FVerifyGradeByUserIdRequest& From
        );
        ~FVerifyGradeByUserIdRequest() = default;

        TSharedPtr<FVerifyGradeByUserIdRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FVerifyGradeByUserIdRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FVerifyGradeByUserIdRequest> WithUserId(const TOptional<FString> UserId);
        TSharedPtr<FVerifyGradeByUserIdRequest> WithGradeName(const TOptional<FString> GradeName);
        TSharedPtr<FVerifyGradeByUserIdRequest> WithVerifyType(const TOptional<FString> VerifyType);
        TSharedPtr<FVerifyGradeByUserIdRequest> WithPropertyId(const TOptional<FString> PropertyId);
        TSharedPtr<FVerifyGradeByUserIdRequest> WithGradeValue(const TOptional<int64> GradeValue);
        TSharedPtr<FVerifyGradeByUserIdRequest> WithMultiplyValueSpecifyingQuantity(const TOptional<bool> MultiplyValueSpecifyingQuantity);
        TSharedPtr<FVerifyGradeByUserIdRequest> WithTimeOffsetToken(const TOptional<FString> TimeOffsetToken);
        TSharedPtr<FVerifyGradeByUserIdRequest> WithDuplicationAvoider(const TOptional<FString> DuplicationAvoider);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetUserId() const;
        TOptional<FString> GetGradeName() const;
        TOptional<FString> GetVerifyType() const;
        TOptional<FString> GetPropertyId() const;
        TOptional<int64> GetGradeValue() const;
        FString GetGradeValueString() const;
        TOptional<bool> GetMultiplyValueSpecifyingQuantity() const;
        FString GetMultiplyValueSpecifyingQuantityString() const;
        TOptional<FString> GetTimeOffsetToken() const;
        TOptional<FString> GetDuplicationAvoider() const;

        static TSharedPtr<FVerifyGradeByUserIdRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FVerifyGradeByUserIdRequest> FVerifyGradeByUserIdRequestPtr;
}