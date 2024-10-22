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
    class FVerifyReceiptByUserIdRequest;

    class GS2MONEY2_API FVerifyReceiptByUserIdRequest final : public TSharedFromThis<FVerifyReceiptByUserIdRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> UserIdValue;
        TOptional<FString> ContentNameValue;
        TSharedPtr<Model::FReceipt> ReceiptValue;
        TOptional<FString> TimeOffsetTokenValue;
        TOptional<FString> DuplicationAvoiderValue;
        
    public:
        
        FVerifyReceiptByUserIdRequest();
        FVerifyReceiptByUserIdRequest(
            const FVerifyReceiptByUserIdRequest& From
        );
        ~FVerifyReceiptByUserIdRequest() = default;

        TSharedPtr<FVerifyReceiptByUserIdRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FVerifyReceiptByUserIdRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FVerifyReceiptByUserIdRequest> WithUserId(const TOptional<FString> UserId);
        TSharedPtr<FVerifyReceiptByUserIdRequest> WithContentName(const TOptional<FString> ContentName);
        TSharedPtr<FVerifyReceiptByUserIdRequest> WithReceipt(const TSharedPtr<Model::FReceipt> Receipt);
        TSharedPtr<FVerifyReceiptByUserIdRequest> WithTimeOffsetToken(const TOptional<FString> TimeOffsetToken);
        TSharedPtr<FVerifyReceiptByUserIdRequest> WithDuplicationAvoider(const TOptional<FString> DuplicationAvoider);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetUserId() const;
        TOptional<FString> GetContentName() const;
        TSharedPtr<Model::FReceipt> GetReceipt() const;
        TOptional<FString> GetTimeOffsetToken() const;
        TOptional<FString> GetDuplicationAvoider() const;

        static TSharedPtr<FVerifyReceiptByUserIdRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FVerifyReceiptByUserIdRequest> FVerifyReceiptByUserIdRequestPtr;
}