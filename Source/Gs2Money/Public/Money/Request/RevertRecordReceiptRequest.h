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
    class FRevertRecordReceiptRequest;

    class GS2MONEY_API FRevertRecordReceiptRequest final : public TSharedFromThis<FRevertRecordReceiptRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> UserIdValue;
        TOptional<FString> ReceiptValue;
        TOptional<FString> DuplicationAvoiderValue;
        
    public:
        
        FRevertRecordReceiptRequest();
        FRevertRecordReceiptRequest(
            const FRevertRecordReceiptRequest& From
        );
        ~FRevertRecordReceiptRequest() = default;

        TSharedPtr<FRevertRecordReceiptRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FRevertRecordReceiptRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FRevertRecordReceiptRequest> WithUserId(const TOptional<FString> UserId);
        TSharedPtr<FRevertRecordReceiptRequest> WithReceipt(const TOptional<FString> Receipt);
        TSharedPtr<FRevertRecordReceiptRequest> WithDuplicationAvoider(const TOptional<FString> DuplicationAvoider);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetUserId() const;
        TOptional<FString> GetReceipt() const;
        TOptional<FString> GetDuplicationAvoider() const;

        static TSharedPtr<FRevertRecordReceiptRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FRevertRecordReceiptRequest, ESPMode::ThreadSafe> FRevertRecordReceiptRequestPtr;
}