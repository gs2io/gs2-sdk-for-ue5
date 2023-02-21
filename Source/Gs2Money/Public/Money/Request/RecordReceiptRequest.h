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

namespace Gs2::Money::Request
{
    class FRecordReceiptRequest;

    class GS2MONEY_API FRecordReceiptRequest final : public TSharedFromThis<FRecordReceiptRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> UserIdValue;
        TOptional<FString> ContentsIdValue;
        TOptional<FString> ReceiptValue;
        TOptional<FString> DuplicationAvoiderValue;
        
    public:
        
        FRecordReceiptRequest();
        FRecordReceiptRequest(
            const FRecordReceiptRequest& From
        );
        ~FRecordReceiptRequest() = default;

        TSharedPtr<FRecordReceiptRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FRecordReceiptRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FRecordReceiptRequest> WithUserId(const TOptional<FString> UserId);
        TSharedPtr<FRecordReceiptRequest> WithContentsId(const TOptional<FString> ContentsId);
        TSharedPtr<FRecordReceiptRequest> WithReceipt(const TOptional<FString> Receipt);
        TSharedPtr<FRecordReceiptRequest> WithDuplicationAvoider(const TOptional<FString> DuplicationAvoider);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetUserId() const;
        TOptional<FString> GetContentsId() const;
        TOptional<FString> GetReceipt() const;
        TOptional<FString> GetDuplicationAvoider() const;

        static TSharedPtr<FRecordReceiptRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FRecordReceiptRequest, ESPMode::ThreadSafe> FRecordReceiptRequestPtr;
}