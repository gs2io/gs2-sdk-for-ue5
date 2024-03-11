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

namespace Gs2::Chat::Request
{
    class FPostByUserIdRequest;

    class GS2CHAT_API FPostByUserIdRequest final : public TSharedFromThis<FPostByUserIdRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> RoomNameValue;
        TOptional<FString> UserIdValue;
        TOptional<int32> CategoryValue;
        TOptional<FString> MetadataValue;
        TOptional<FString> PasswordValue;
        TOptional<FString> TimeOffsetTokenValue;
        TOptional<FString> DuplicationAvoiderValue;
        
    public:
        
        FPostByUserIdRequest();
        FPostByUserIdRequest(
            const FPostByUserIdRequest& From
        );
        ~FPostByUserIdRequest() = default;

        TSharedPtr<FPostByUserIdRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FPostByUserIdRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FPostByUserIdRequest> WithRoomName(const TOptional<FString> RoomName);
        TSharedPtr<FPostByUserIdRequest> WithUserId(const TOptional<FString> UserId);
        TSharedPtr<FPostByUserIdRequest> WithCategory(const TOptional<int32> Category);
        TSharedPtr<FPostByUserIdRequest> WithMetadata(const TOptional<FString> Metadata);
        TSharedPtr<FPostByUserIdRequest> WithPassword(const TOptional<FString> Password);
        TSharedPtr<FPostByUserIdRequest> WithTimeOffsetToken(const TOptional<FString> TimeOffsetToken);
        TSharedPtr<FPostByUserIdRequest> WithDuplicationAvoider(const TOptional<FString> DuplicationAvoider);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetRoomName() const;
        TOptional<FString> GetUserId() const;
        TOptional<int32> GetCategory() const;
        FString GetCategoryString() const;
        TOptional<FString> GetMetadata() const;
        TOptional<FString> GetPassword() const;
        TOptional<FString> GetTimeOffsetToken() const;
        TOptional<FString> GetDuplicationAvoider() const;

        static TSharedPtr<FPostByUserIdRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FPostByUserIdRequest, ESPMode::ThreadSafe> FPostByUserIdRequestPtr;
}