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

namespace Gs2::Enchant::Request
{
    class FVerifyRarityParameterStatusRequest;

    class GS2ENCHANT_API FVerifyRarityParameterStatusRequest final : public TSharedFromThis<FVerifyRarityParameterStatusRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> ParameterNameValue;
        TOptional<FString> AccessTokenValue;
        TOptional<FString> PropertyIdValue;
        TOptional<FString> VerifyTypeValue;
        TOptional<FString> ParameterValueNameValue;
        TOptional<int32> ParameterCountValue;
        TOptional<FString> DuplicationAvoiderValue;
        
    public:
        
        FVerifyRarityParameterStatusRequest();
        FVerifyRarityParameterStatusRequest(
            const FVerifyRarityParameterStatusRequest& From
        );
        ~FVerifyRarityParameterStatusRequest() = default;

        TSharedPtr<FVerifyRarityParameterStatusRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FVerifyRarityParameterStatusRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FVerifyRarityParameterStatusRequest> WithParameterName(const TOptional<FString> ParameterName);
        TSharedPtr<FVerifyRarityParameterStatusRequest> WithAccessToken(const TOptional<FString> AccessToken);
        TSharedPtr<FVerifyRarityParameterStatusRequest> WithPropertyId(const TOptional<FString> PropertyId);
        TSharedPtr<FVerifyRarityParameterStatusRequest> WithVerifyType(const TOptional<FString> VerifyType);
        TSharedPtr<FVerifyRarityParameterStatusRequest> WithParameterValueName(const TOptional<FString> ParameterValueName);
        TSharedPtr<FVerifyRarityParameterStatusRequest> WithParameterCount(const TOptional<int32> ParameterCount);
        TSharedPtr<FVerifyRarityParameterStatusRequest> WithDuplicationAvoider(const TOptional<FString> DuplicationAvoider);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetParameterName() const;
        TOptional<FString> GetAccessToken() const;
        TOptional<FString> GetPropertyId() const;
        TOptional<FString> GetVerifyType() const;
        TOptional<FString> GetParameterValueName() const;
        TOptional<int32> GetParameterCount() const;
        FString GetParameterCountString() const;
        TOptional<FString> GetDuplicationAvoider() const;

        static TSharedPtr<FVerifyRarityParameterStatusRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FVerifyRarityParameterStatusRequest, ESPMode::ThreadSafe> FVerifyRarityParameterStatusRequestPtr;
}