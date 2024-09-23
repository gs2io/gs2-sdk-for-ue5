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
    class FVerifyGradeRequest;

    class GS2GRADE_API FVerifyGradeRequest final : public TSharedFromThis<FVerifyGradeRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> AccessTokenValue;
        TOptional<FString> GradeNameValue;
        TOptional<FString> VerifyTypeValue;
        TOptional<FString> PropertyIdValue;
        TOptional<int64> GradeValueValue;
        TOptional<bool> MultiplyValueSpecifyingQuantityValue;
        TOptional<FString> DuplicationAvoiderValue;
        
    public:
        
        FVerifyGradeRequest();
        FVerifyGradeRequest(
            const FVerifyGradeRequest& From
        );
        ~FVerifyGradeRequest() = default;

        TSharedPtr<FVerifyGradeRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FVerifyGradeRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FVerifyGradeRequest> WithAccessToken(const TOptional<FString> AccessToken);
        TSharedPtr<FVerifyGradeRequest> WithGradeName(const TOptional<FString> GradeName);
        TSharedPtr<FVerifyGradeRequest> WithVerifyType(const TOptional<FString> VerifyType);
        TSharedPtr<FVerifyGradeRequest> WithPropertyId(const TOptional<FString> PropertyId);
        TSharedPtr<FVerifyGradeRequest> WithGradeValue(const TOptional<int64> GradeValue);
        TSharedPtr<FVerifyGradeRequest> WithMultiplyValueSpecifyingQuantity(const TOptional<bool> MultiplyValueSpecifyingQuantity);
        TSharedPtr<FVerifyGradeRequest> WithDuplicationAvoider(const TOptional<FString> DuplicationAvoider);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetAccessToken() const;
        TOptional<FString> GetGradeName() const;
        TOptional<FString> GetVerifyType() const;
        TOptional<FString> GetPropertyId() const;
        TOptional<int64> GetGradeValue() const;
        FString GetGradeValueString() const;
        TOptional<bool> GetMultiplyValueSpecifyingQuantity() const;
        FString GetMultiplyValueSpecifyingQuantityString() const;
        TOptional<FString> GetDuplicationAvoider() const;

        static TSharedPtr<FVerifyGradeRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FVerifyGradeRequest, ESPMode::ThreadSafe> FVerifyGradeRequestPtr;
}