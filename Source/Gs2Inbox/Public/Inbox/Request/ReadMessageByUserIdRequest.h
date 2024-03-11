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
#include "../Model/Config.h"

namespace Gs2::Inbox::Request
{
    class FReadMessageByUserIdRequest;

    class GS2INBOX_API FReadMessageByUserIdRequest final : public TSharedFromThis<FReadMessageByUserIdRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> UserIdValue;
        TOptional<FString> MessageNameValue;
        TSharedPtr<TArray<TSharedPtr<Model::FConfig>>> ConfigValue;
        TOptional<FString> TimeOffsetTokenValue;
        TOptional<FString> DuplicationAvoiderValue;
        
    public:
        
        FReadMessageByUserIdRequest();
        FReadMessageByUserIdRequest(
            const FReadMessageByUserIdRequest& From
        );
        ~FReadMessageByUserIdRequest() = default;

        TSharedPtr<FReadMessageByUserIdRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FReadMessageByUserIdRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FReadMessageByUserIdRequest> WithUserId(const TOptional<FString> UserId);
        TSharedPtr<FReadMessageByUserIdRequest> WithMessageName(const TOptional<FString> MessageName);
        TSharedPtr<FReadMessageByUserIdRequest> WithConfig(const TSharedPtr<TArray<TSharedPtr<Model::FConfig>>> Config);
        TSharedPtr<FReadMessageByUserIdRequest> WithTimeOffsetToken(const TOptional<FString> TimeOffsetToken);
        TSharedPtr<FReadMessageByUserIdRequest> WithDuplicationAvoider(const TOptional<FString> DuplicationAvoider);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetUserId() const;
        TOptional<FString> GetMessageName() const;TSharedPtr<TArray<TSharedPtr<Model::FConfig>>> GetConfig() const;
        TOptional<FString> GetTimeOffsetToken() const;
        TOptional<FString> GetDuplicationAvoider() const;

        static TSharedPtr<FReadMessageByUserIdRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FReadMessageByUserIdRequest, ESPMode::ThreadSafe> FReadMessageByUserIdRequestPtr;
}