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
    class FDescribeLatestMessagesRequest;

    class GS2CHAT_API FDescribeLatestMessagesRequest final : public TSharedFromThis<FDescribeLatestMessagesRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> RoomNameValue;
        TOptional<FString> PasswordValue;
        TOptional<int32> CategoryValue;
        TOptional<FString> AccessTokenValue;
        TOptional<int32> LimitValue;
        
    public:
        
        FDescribeLatestMessagesRequest();
        FDescribeLatestMessagesRequest(
            const FDescribeLatestMessagesRequest& From
        );
        ~FDescribeLatestMessagesRequest() = default;

        TSharedPtr<FDescribeLatestMessagesRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FDescribeLatestMessagesRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FDescribeLatestMessagesRequest> WithRoomName(const TOptional<FString> RoomName);
        TSharedPtr<FDescribeLatestMessagesRequest> WithPassword(const TOptional<FString> Password);
        TSharedPtr<FDescribeLatestMessagesRequest> WithCategory(const TOptional<int32> Category);
        TSharedPtr<FDescribeLatestMessagesRequest> WithAccessToken(const TOptional<FString> AccessToken);
        TSharedPtr<FDescribeLatestMessagesRequest> WithLimit(const TOptional<int32> Limit);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetRoomName() const;
        TOptional<FString> GetPassword() const;
        TOptional<int32> GetCategory() const;
        FString GetCategoryString() const;
        TOptional<FString> GetAccessToken() const;
        TOptional<int32> GetLimit() const;
        FString GetLimitString() const;

        static TSharedPtr<FDescribeLatestMessagesRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FDescribeLatestMessagesRequest> FDescribeLatestMessagesRequestPtr;
}