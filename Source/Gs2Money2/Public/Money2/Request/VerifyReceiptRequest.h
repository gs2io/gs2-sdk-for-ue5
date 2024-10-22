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
#include "../Model/Receipt.h"

namespace Gs2::Money2::Request
{
    class FVerifyReceiptRequest;

    class GS2MONEY2_API FVerifyReceiptRequest final : public TSharedFromThis<FVerifyReceiptRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> AccessTokenValue;
        TOptional<FString> ContentNameValue;
        TSharedPtr<Model::FReceipt> ReceiptValue;
        TOptional<FString> DuplicationAvoiderValue;
        
    public:
        
        FVerifyReceiptRequest();
        FVerifyReceiptRequest(
            const FVerifyReceiptRequest& From
        );
        ~FVerifyReceiptRequest() = default;

        TSharedPtr<FVerifyReceiptRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FVerifyReceiptRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FVerifyReceiptRequest> WithAccessToken(const TOptional<FString> AccessToken);
        TSharedPtr<FVerifyReceiptRequest> WithContentName(const TOptional<FString> ContentName);
        TSharedPtr<FVerifyReceiptRequest> WithReceipt(const TSharedPtr<Model::FReceipt> Receipt);
        TSharedPtr<FVerifyReceiptRequest> WithDuplicationAvoider(const TOptional<FString> DuplicationAvoider);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetAccessToken() const;
        TOptional<FString> GetContentName() const;
        TSharedPtr<Model::FReceipt> GetReceipt() const;
        TOptional<FString> GetDuplicationAvoider() const;

        static TSharedPtr<FVerifyReceiptRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FVerifyReceiptRequest> FVerifyReceiptRequestPtr;
}