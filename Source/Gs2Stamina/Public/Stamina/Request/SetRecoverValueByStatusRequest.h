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

namespace Gs2::Stamina::Request
{
    class FSetRecoverValueByStatusRequest;

    class GS2STAMINA_API FSetRecoverValueByStatusRequest final : public TSharedFromThis<FSetRecoverValueByStatusRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> StaminaNameValue;
        TOptional<FString> AccessTokenValue;
        TOptional<FString> KeyIdValue;
        TOptional<FString> SignedStatusBodyValue;
        TOptional<FString> SignedStatusSignatureValue;
        TOptional<FString> DuplicationAvoiderValue;
        
    public:
        
        FSetRecoverValueByStatusRequest();
        FSetRecoverValueByStatusRequest(
            const FSetRecoverValueByStatusRequest& From
        );
        ~FSetRecoverValueByStatusRequest() = default;

        TSharedPtr<FSetRecoverValueByStatusRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FSetRecoverValueByStatusRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FSetRecoverValueByStatusRequest> WithStaminaName(const TOptional<FString> StaminaName);
        TSharedPtr<FSetRecoverValueByStatusRequest> WithAccessToken(const TOptional<FString> AccessToken);
        TSharedPtr<FSetRecoverValueByStatusRequest> WithKeyId(const TOptional<FString> KeyId);
        TSharedPtr<FSetRecoverValueByStatusRequest> WithSignedStatusBody(const TOptional<FString> SignedStatusBody);
        TSharedPtr<FSetRecoverValueByStatusRequest> WithSignedStatusSignature(const TOptional<FString> SignedStatusSignature);
        TSharedPtr<FSetRecoverValueByStatusRequest> WithDuplicationAvoider(const TOptional<FString> DuplicationAvoider);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetStaminaName() const;
        TOptional<FString> GetAccessToken() const;
        TOptional<FString> GetKeyId() const;
        TOptional<FString> GetSignedStatusBody() const;
        TOptional<FString> GetSignedStatusSignature() const;
        TOptional<FString> GetDuplicationAvoider() const;

        static TSharedPtr<FSetRecoverValueByStatusRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FSetRecoverValueByStatusRequest> FSetRecoverValueByStatusRequestPtr;
}