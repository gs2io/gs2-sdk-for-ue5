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
#include "Gateway/Model/WebSocketSession.h"

namespace Gs2::UE5::Gateway::Model
{
	class EZGS2_API FEzWebSocketSession final : public TSharedFromThis<FEzWebSocketSession>
	{
        TOptional<FString> ConnectionIdValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> UserIdValue;

	public:
        TSharedPtr<FEzWebSocketSession> WithConnectionId(const TOptional<FString> ConnectionId);
        TSharedPtr<FEzWebSocketSession> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FEzWebSocketSession> WithUserId(const TOptional<FString> UserId);

        TOptional<FString> GetConnectionId() const;

        TOptional<FString> GetNamespaceName() const;

        TOptional<FString> GetUserId() const;

        Gs2::Gateway::Model::FWebSocketSessionPtr ToModel() const;
        static TSharedPtr<FEzWebSocketSession> FromModel(Gs2::Gateway::Model::FWebSocketSessionPtr Model);
    };
    typedef TSharedPtr<FEzWebSocketSession> FEzWebSocketSessionPtr;
}