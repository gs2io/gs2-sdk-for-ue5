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

namespace Gs2::AdReward::Request
{
    class FVerifyPointRequest;

    class GS2ADREWARD_API FVerifyPointRequest final : public TSharedFromThis<FVerifyPointRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> AccessTokenValue;
        TOptional<FString> VerifyTypeValue;
        TOptional<int64> PointValue;
        TOptional<bool> MultiplyValueSpecifyingQuantityValue;
        TOptional<FString> DuplicationAvoiderValue;
        
    public:
        
        FVerifyPointRequest();
        FVerifyPointRequest(
            const FVerifyPointRequest& From
        );
        ~FVerifyPointRequest() = default;

        TSharedPtr<FVerifyPointRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FVerifyPointRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FVerifyPointRequest> WithAccessToken(const TOptional<FString> AccessToken);
        TSharedPtr<FVerifyPointRequest> WithVerifyType(const TOptional<FString> VerifyType);
        TSharedPtr<FVerifyPointRequest> WithPoint(const TOptional<int64> Point);
        TSharedPtr<FVerifyPointRequest> WithMultiplyValueSpecifyingQuantity(const TOptional<bool> MultiplyValueSpecifyingQuantity);
        TSharedPtr<FVerifyPointRequest> WithDuplicationAvoider(const TOptional<FString> DuplicationAvoider);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetAccessToken() const;
        TOptional<FString> GetVerifyType() const;
        TOptional<int64> GetPoint() const;
        FString GetPointString() const;
        TOptional<bool> GetMultiplyValueSpecifyingQuantity() const;
        FString GetMultiplyValueSpecifyingQuantityString() const;
        TOptional<FString> GetDuplicationAvoider() const;

        static TSharedPtr<FVerifyPointRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FVerifyPointRequest> FVerifyPointRequestPtr;
}