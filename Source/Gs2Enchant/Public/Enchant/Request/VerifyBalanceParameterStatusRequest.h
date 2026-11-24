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

namespace Gs2::Enchant::Request
{
    class FVerifyBalanceParameterStatusRequest;

    class GS2ENCHANT_API FVerifyBalanceParameterStatusRequest final : public TSharedFromThis<FVerifyBalanceParameterStatusRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> AccessTokenValue;
        TOptional<FString> ParameterNameValue;
        TOptional<FString> PropertyIdValue;
        TOptional<FString> ParameterValueNameValue;
        TOptional<FString> VerifyTypeValue;
        TOptional<int64> ParameterValueValue;
        TOptional<FString> DuplicationAvoiderValue;
        
    public:
        
        FVerifyBalanceParameterStatusRequest();
        FVerifyBalanceParameterStatusRequest(
            const FVerifyBalanceParameterStatusRequest& From
        );
        ~FVerifyBalanceParameterStatusRequest() = default;

        TSharedPtr<FVerifyBalanceParameterStatusRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FVerifyBalanceParameterStatusRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FVerifyBalanceParameterStatusRequest> WithAccessToken(const TOptional<FString> AccessToken);
        TSharedPtr<FVerifyBalanceParameterStatusRequest> WithParameterName(const TOptional<FString> ParameterName);
        TSharedPtr<FVerifyBalanceParameterStatusRequest> WithPropertyId(const TOptional<FString> PropertyId);
        TSharedPtr<FVerifyBalanceParameterStatusRequest> WithParameterValueName(const TOptional<FString> ParameterValueName);
        TSharedPtr<FVerifyBalanceParameterStatusRequest> WithVerifyType(const TOptional<FString> VerifyType);
        TSharedPtr<FVerifyBalanceParameterStatusRequest> WithParameterValue(const TOptional<int64> ParameterValue);
        TSharedPtr<FVerifyBalanceParameterStatusRequest> WithDuplicationAvoider(const TOptional<FString> DuplicationAvoider);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetAccessToken() const;
        TOptional<FString> GetParameterName() const;
        TOptional<FString> GetPropertyId() const;
        TOptional<FString> GetParameterValueName() const;
        TOptional<FString> GetVerifyType() const;
        TOptional<int64> GetParameterValue() const;
        FString GetParameterValueString() const;
        TOptional<FString> GetDuplicationAvoider() const;

        static TSharedPtr<FVerifyBalanceParameterStatusRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FVerifyBalanceParameterStatusRequest> FVerifyBalanceParameterStatusRequestPtr;
}