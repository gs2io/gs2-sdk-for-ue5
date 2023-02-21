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
#include "../Model/AcquireAction.h"
#include "../Model/TimeSpan.h"

namespace Gs2::Inbox::Request
{
    class FSendMessageByUserIdRequest;

    class GS2INBOX_API FSendMessageByUserIdRequest final : public TSharedFromThis<FSendMessageByUserIdRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> UserIdValue;
        TOptional<FString> MetadataValue;
        TSharedPtr<TArray<TSharedPtr<Model::FAcquireAction>>> ReadAcquireActionsValue;
        TOptional<int64> ExpiresAtValue;
        TSharedPtr<Model::FTimeSpan> ExpiresTimeSpanValue;
        TOptional<FString> DuplicationAvoiderValue;
        
    public:
        
        FSendMessageByUserIdRequest();
        FSendMessageByUserIdRequest(
            const FSendMessageByUserIdRequest& From
        );
        ~FSendMessageByUserIdRequest() = default;

        TSharedPtr<FSendMessageByUserIdRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FSendMessageByUserIdRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FSendMessageByUserIdRequest> WithUserId(const TOptional<FString> UserId);
        TSharedPtr<FSendMessageByUserIdRequest> WithMetadata(const TOptional<FString> Metadata);
        TSharedPtr<FSendMessageByUserIdRequest> WithReadAcquireActions(const TSharedPtr<TArray<TSharedPtr<Model::FAcquireAction>>> ReadAcquireActions);
        TSharedPtr<FSendMessageByUserIdRequest> WithExpiresAt(const TOptional<int64> ExpiresAt);
        TSharedPtr<FSendMessageByUserIdRequest> WithExpiresTimeSpan(const TSharedPtr<Model::FTimeSpan> ExpiresTimeSpan);
        TSharedPtr<FSendMessageByUserIdRequest> WithDuplicationAvoider(const TOptional<FString> DuplicationAvoider);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetUserId() const;
        TOptional<FString> GetMetadata() const;TSharedPtr<TArray<TSharedPtr<Model::FAcquireAction>>> GetReadAcquireActions() const;
        TOptional<int64> GetExpiresAt() const;
        FString GetExpiresAtString() const;
        TSharedPtr<Model::FTimeSpan> GetExpiresTimeSpan() const;
        TOptional<FString> GetDuplicationAvoider() const;

        static TSharedPtr<FSendMessageByUserIdRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FSendMessageByUserIdRequest, ESPMode::ThreadSafe> FSendMessageByUserIdRequestPtr;
}