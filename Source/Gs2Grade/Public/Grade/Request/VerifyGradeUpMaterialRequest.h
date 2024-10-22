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
    class FVerifyGradeUpMaterialRequest;

    class GS2GRADE_API FVerifyGradeUpMaterialRequest final : public TSharedFromThis<FVerifyGradeUpMaterialRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> AccessTokenValue;
        TOptional<FString> GradeNameValue;
        TOptional<FString> VerifyTypeValue;
        TOptional<FString> PropertyIdValue;
        TOptional<FString> MaterialPropertyIdValue;
        TOptional<FString> DuplicationAvoiderValue;
        
    public:
        
        FVerifyGradeUpMaterialRequest();
        FVerifyGradeUpMaterialRequest(
            const FVerifyGradeUpMaterialRequest& From
        );
        ~FVerifyGradeUpMaterialRequest() = default;

        TSharedPtr<FVerifyGradeUpMaterialRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FVerifyGradeUpMaterialRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FVerifyGradeUpMaterialRequest> WithAccessToken(const TOptional<FString> AccessToken);
        TSharedPtr<FVerifyGradeUpMaterialRequest> WithGradeName(const TOptional<FString> GradeName);
        TSharedPtr<FVerifyGradeUpMaterialRequest> WithVerifyType(const TOptional<FString> VerifyType);
        TSharedPtr<FVerifyGradeUpMaterialRequest> WithPropertyId(const TOptional<FString> PropertyId);
        TSharedPtr<FVerifyGradeUpMaterialRequest> WithMaterialPropertyId(const TOptional<FString> MaterialPropertyId);
        TSharedPtr<FVerifyGradeUpMaterialRequest> WithDuplicationAvoider(const TOptional<FString> DuplicationAvoider);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetAccessToken() const;
        TOptional<FString> GetGradeName() const;
        TOptional<FString> GetVerifyType() const;
        TOptional<FString> GetPropertyId() const;
        TOptional<FString> GetMaterialPropertyId() const;
        TOptional<FString> GetDuplicationAvoider() const;

        static TSharedPtr<FVerifyGradeUpMaterialRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FVerifyGradeUpMaterialRequest> FVerifyGradeUpMaterialRequestPtr;
}