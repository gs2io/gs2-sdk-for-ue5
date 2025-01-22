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

namespace Gs2::SerialKey::Request
{
    class FVerifyCodeRequest;

    class GS2SERIALKEY_API FVerifyCodeRequest final : public TSharedFromThis<FVerifyCodeRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> AccessTokenValue;
        TOptional<FString> CodeValue;
        TOptional<FString> CampaignModelNameValue;
        TOptional<FString> VerifyTypeValue;
        TOptional<FString> DuplicationAvoiderValue;
        
    public:
        
        FVerifyCodeRequest();
        FVerifyCodeRequest(
            const FVerifyCodeRequest& From
        );
        ~FVerifyCodeRequest() = default;

        TSharedPtr<FVerifyCodeRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FVerifyCodeRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FVerifyCodeRequest> WithAccessToken(const TOptional<FString> AccessToken);
        TSharedPtr<FVerifyCodeRequest> WithCode(const TOptional<FString> Code);
        TSharedPtr<FVerifyCodeRequest> WithCampaignModelName(const TOptional<FString> CampaignModelName);
        TSharedPtr<FVerifyCodeRequest> WithVerifyType(const TOptional<FString> VerifyType);
        TSharedPtr<FVerifyCodeRequest> WithDuplicationAvoider(const TOptional<FString> DuplicationAvoider);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetAccessToken() const;
        TOptional<FString> GetCode() const;
        TOptional<FString> GetCampaignModelName() const;
        TOptional<FString> GetVerifyType() const;
        TOptional<FString> GetDuplicationAvoider() const;

        static TSharedPtr<FVerifyCodeRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FVerifyCodeRequest> FVerifyCodeRequestPtr;
}