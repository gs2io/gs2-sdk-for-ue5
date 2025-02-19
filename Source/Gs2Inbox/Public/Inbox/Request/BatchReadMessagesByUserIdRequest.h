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
#include "../Model/Config.h"

namespace Gs2::Inbox::Request
{
    class FBatchReadMessagesByUserIdRequest;

    class GS2INBOX_API FBatchReadMessagesByUserIdRequest final : public TSharedFromThis<FBatchReadMessagesByUserIdRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> UserIdValue;
        TSharedPtr<TArray<FString>> MessageNamesValue;
        TSharedPtr<TArray<TSharedPtr<Model::FConfig>>> ConfigValue;
        TOptional<FString> TimeOffsetTokenValue;
        TOptional<FString> DuplicationAvoiderValue;
        
    public:
        
        FBatchReadMessagesByUserIdRequest();
        FBatchReadMessagesByUserIdRequest(
            const FBatchReadMessagesByUserIdRequest& From
        );
        ~FBatchReadMessagesByUserIdRequest() = default;

        TSharedPtr<FBatchReadMessagesByUserIdRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FBatchReadMessagesByUserIdRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FBatchReadMessagesByUserIdRequest> WithUserId(const TOptional<FString> UserId);
        TSharedPtr<FBatchReadMessagesByUserIdRequest> WithMessageNames(
            const TSharedPtr<TArray<FString>> MessageNames);
        TSharedPtr<FBatchReadMessagesByUserIdRequest> WithConfig(const TSharedPtr<TArray<TSharedPtr<Model::FConfig>>> Config);
        TSharedPtr<FBatchReadMessagesByUserIdRequest> WithTimeOffsetToken(const TOptional<FString> TimeOffsetToken);
        TSharedPtr<FBatchReadMessagesByUserIdRequest> WithDuplicationAvoider(const TOptional<FString> DuplicationAvoider);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetUserId() const;
        TSharedPtr<TArray<FString>> GetMessageNames() const;TSharedPtr<TArray<TSharedPtr<Model::FConfig>>> GetConfig() const;
        TOptional<FString> GetTimeOffsetToken() const;
        TOptional<FString> GetDuplicationAvoider() const;

        static TSharedPtr<FBatchReadMessagesByUserIdRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FBatchReadMessagesByUserIdRequest> FBatchReadMessagesByUserIdRequestPtr;
}