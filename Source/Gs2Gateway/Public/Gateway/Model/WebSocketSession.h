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

namespace Gs2::Gateway::Model
{
    class GS2GATEWAY_API FWebSocketSession final : public TSharedFromThis<FWebSocketSession>
    {
        TOptional<FString> WebSocketSessionIdValue;
        TOptional<FString> ConnectionIdValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> UserIdValue;
        TOptional<int64> CreatedAtValue;
        TOptional<int64> UpdatedAtValue;

    public:
        FWebSocketSession();
        FWebSocketSession(
            const FWebSocketSession& From
        );
        ~FWebSocketSession() = default;

        TSharedPtr<FWebSocketSession> WithWebSocketSessionId(const TOptional<FString> WebSocketSessionId);
        TSharedPtr<FWebSocketSession> WithConnectionId(const TOptional<FString> ConnectionId);
        TSharedPtr<FWebSocketSession> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FWebSocketSession> WithUserId(const TOptional<FString> UserId);
        TSharedPtr<FWebSocketSession> WithCreatedAt(const TOptional<int64> CreatedAt);
        TSharedPtr<FWebSocketSession> WithUpdatedAt(const TOptional<int64> UpdatedAt);

        TOptional<FString> GetWebSocketSessionId() const;
        TOptional<FString> GetConnectionId() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetUserId() const;
        TOptional<int64> GetCreatedAt() const;
        FString GetCreatedAtString() const;
        TOptional<int64> GetUpdatedAt() const;
        FString GetUpdatedAtString() const;

        static TOptional<FString> GetRegionFromGrn(const FString Grn);
        static TOptional<FString> GetOwnerIdFromGrn(const FString Grn);
        static TOptional<FString> GetNamespaceNameFromGrn(const FString Grn);
        static TOptional<FString> GetUserIdFromGrn(const FString Grn);
        static TOptional<FString> GetConnectionIdFromGrn(const FString Grn);

        static TSharedPtr<FWebSocketSession> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;

        static FString TypeName;
    };
    typedef TSharedPtr<FWebSocketSession, ESPMode::ThreadSafe> FWebSocketSessionPtr;
}