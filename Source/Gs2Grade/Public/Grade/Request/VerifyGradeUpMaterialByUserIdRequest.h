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
    class FVerifyGradeUpMaterialByUserIdRequest;

    class GS2GRADE_API FVerifyGradeUpMaterialByUserIdRequest final : public TSharedFromThis<FVerifyGradeUpMaterialByUserIdRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> UserIdValue;
        TOptional<FString> GradeNameValue;
        TOptional<FString> VerifyTypeValue;
        TOptional<FString> PropertyIdValue;
        TOptional<FString> MaterialPropertyIdValue;
        TOptional<FString> TimeOffsetTokenValue;
        TOptional<FString> DuplicationAvoiderValue;
        
    public:
        
        FVerifyGradeUpMaterialByUserIdRequest();
        FVerifyGradeUpMaterialByUserIdRequest(
            const FVerifyGradeUpMaterialByUserIdRequest& From
        );
        ~FVerifyGradeUpMaterialByUserIdRequest() = default;

        TSharedPtr<FVerifyGradeUpMaterialByUserIdRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FVerifyGradeUpMaterialByUserIdRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FVerifyGradeUpMaterialByUserIdRequest> WithUserId(const TOptional<FString> UserId);
        TSharedPtr<FVerifyGradeUpMaterialByUserIdRequest> WithGradeName(const TOptional<FString> GradeName);
        TSharedPtr<FVerifyGradeUpMaterialByUserIdRequest> WithVerifyType(const TOptional<FString> VerifyType);
        TSharedPtr<FVerifyGradeUpMaterialByUserIdRequest> WithPropertyId(const TOptional<FString> PropertyId);
        TSharedPtr<FVerifyGradeUpMaterialByUserIdRequest> WithMaterialPropertyId(const TOptional<FString> MaterialPropertyId);
        TSharedPtr<FVerifyGradeUpMaterialByUserIdRequest> WithTimeOffsetToken(const TOptional<FString> TimeOffsetToken);
        TSharedPtr<FVerifyGradeUpMaterialByUserIdRequest> WithDuplicationAvoider(const TOptional<FString> DuplicationAvoider);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetUserId() const;
        TOptional<FString> GetGradeName() const;
        TOptional<FString> GetVerifyType() const;
        TOptional<FString> GetPropertyId() const;
        TOptional<FString> GetMaterialPropertyId() const;
        TOptional<FString> GetTimeOffsetToken() const;
        TOptional<FString> GetDuplicationAvoider() const;

        static TSharedPtr<FVerifyGradeUpMaterialByUserIdRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FVerifyGradeUpMaterialByUserIdRequest, ESPMode::ThreadSafe> FVerifyGradeUpMaterialByUserIdRequestPtr;
}