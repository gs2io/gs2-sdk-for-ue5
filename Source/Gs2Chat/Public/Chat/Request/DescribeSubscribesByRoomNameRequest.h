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
    class FDescribeSubscribesByRoomNameRequest;

    class GS2CHAT_API FDescribeSubscribesByRoomNameRequest final : public TSharedFromThis<FDescribeSubscribesByRoomNameRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> RoomNameValue;
        TOptional<FString> PageTokenValue;
        TOptional<int32> LimitValue;
        
    public:
        
        FDescribeSubscribesByRoomNameRequest();
        FDescribeSubscribesByRoomNameRequest(
            const FDescribeSubscribesByRoomNameRequest& From
        );
        ~FDescribeSubscribesByRoomNameRequest() = default;

        TSharedPtr<FDescribeSubscribesByRoomNameRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FDescribeSubscribesByRoomNameRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FDescribeSubscribesByRoomNameRequest> WithRoomName(const TOptional<FString> RoomName);
        TSharedPtr<FDescribeSubscribesByRoomNameRequest> WithPageToken(const TOptional<FString> PageToken);
        TSharedPtr<FDescribeSubscribesByRoomNameRequest> WithLimit(const TOptional<int32> Limit);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetRoomName() const;
        TOptional<FString> GetPageToken() const;
        TOptional<int32> GetLimit() const;
        FString GetLimitString() const;

        static TSharedPtr<FDescribeSubscribesByRoomNameRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FDescribeSubscribesByRoomNameRequest, ESPMode::ThreadSafe> FDescribeSubscribesByRoomNameRequestPtr;
}