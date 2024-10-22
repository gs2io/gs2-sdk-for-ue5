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

namespace Gs2::Inbox::Request
{
    class FUpdateReceivedByUserIdRequest;

    class GS2INBOX_API FUpdateReceivedByUserIdRequest final : public TSharedFromThis<FUpdateReceivedByUserIdRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> UserIdValue;
        TSharedPtr<TArray<FString>> ReceivedGlobalMessageNamesValue;
        TOptional<FString> TimeOffsetTokenValue;
        TOptional<FString> DuplicationAvoiderValue;
        
    public:
        
        FUpdateReceivedByUserIdRequest();
        FUpdateReceivedByUserIdRequest(
            const FUpdateReceivedByUserIdRequest& From
        );
        ~FUpdateReceivedByUserIdRequest() = default;

        TSharedPtr<FUpdateReceivedByUserIdRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FUpdateReceivedByUserIdRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FUpdateReceivedByUserIdRequest> WithUserId(const TOptional<FString> UserId);
        TSharedPtr<FUpdateReceivedByUserIdRequest> WithReceivedGlobalMessageNames(
            const TSharedPtr<TArray<FString>> ReceivedGlobalMessageNames);
        TSharedPtr<FUpdateReceivedByUserIdRequest> WithTimeOffsetToken(const TOptional<FString> TimeOffsetToken);
        TSharedPtr<FUpdateReceivedByUserIdRequest> WithDuplicationAvoider(const TOptional<FString> DuplicationAvoider);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetUserId() const;
        TSharedPtr<TArray<FString>> GetReceivedGlobalMessageNames() const;
        TOptional<FString> GetTimeOffsetToken() const;
        TOptional<FString> GetDuplicationAvoider() const;

        static TSharedPtr<FUpdateReceivedByUserIdRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FUpdateReceivedByUserIdRequest> FUpdateReceivedByUserIdRequestPtr;
}