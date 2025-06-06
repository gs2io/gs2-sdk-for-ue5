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

namespace Gs2::Chat::Request
{
    class FDescribeMessagesByUserIdRequest;

    class GS2CHAT_API FDescribeMessagesByUserIdRequest final : public TSharedFromThis<FDescribeMessagesByUserIdRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> RoomNameValue;
        TOptional<FString> PasswordValue;
        TOptional<int32> CategoryValue;
        TOptional<FString> UserIdValue;
        TOptional<int64> StartAtValue;
        TOptional<int32> LimitValue;
        TOptional<FString> TimeOffsetTokenValue;
        
    public:
        
        FDescribeMessagesByUserIdRequest();
        FDescribeMessagesByUserIdRequest(
            const FDescribeMessagesByUserIdRequest& From
        );
        ~FDescribeMessagesByUserIdRequest() = default;

        TSharedPtr<FDescribeMessagesByUserIdRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FDescribeMessagesByUserIdRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FDescribeMessagesByUserIdRequest> WithRoomName(const TOptional<FString> RoomName);
        TSharedPtr<FDescribeMessagesByUserIdRequest> WithPassword(const TOptional<FString> Password);
        TSharedPtr<FDescribeMessagesByUserIdRequest> WithCategory(const TOptional<int32> Category);
        TSharedPtr<FDescribeMessagesByUserIdRequest> WithUserId(const TOptional<FString> UserId);
        TSharedPtr<FDescribeMessagesByUserIdRequest> WithStartAt(const TOptional<int64> StartAt);
        TSharedPtr<FDescribeMessagesByUserIdRequest> WithLimit(const TOptional<int32> Limit);
        TSharedPtr<FDescribeMessagesByUserIdRequest> WithTimeOffsetToken(const TOptional<FString> TimeOffsetToken);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetRoomName() const;
        TOptional<FString> GetPassword() const;
        TOptional<int32> GetCategory() const;
        FString GetCategoryString() const;
        TOptional<FString> GetUserId() const;
        TOptional<int64> GetStartAt() const;
        FString GetStartAtString() const;
        TOptional<int32> GetLimit() const;
        FString GetLimitString() const;
        TOptional<FString> GetTimeOffsetToken() const;

        static TSharedPtr<FDescribeMessagesByUserIdRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FDescribeMessagesByUserIdRequest> FDescribeMessagesByUserIdRequestPtr;
}