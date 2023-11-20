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

#include "Gateway/Model/Gs2GatewayEzWebSocketSession.h"

namespace Gs2::UE5::Gateway::Model
{

    TSharedPtr<FEzWebSocketSession> FEzWebSocketSession::WithConnectionId(
        const TOptional<FString> ConnectionId
    )
    {
        this->ConnectionIdValue = ConnectionId;
        return SharedThis(this);
    }

    TSharedPtr<FEzWebSocketSession> FEzWebSocketSession::WithNamespaceName(
        const TOptional<FString> NamespaceName
    )
    {
        this->NamespaceNameValue = NamespaceName;
        return SharedThis(this);
    }

    TSharedPtr<FEzWebSocketSession> FEzWebSocketSession::WithUserId(
        const TOptional<FString> UserId
    )
    {
        this->UserIdValue = UserId;
        return SharedThis(this);
    }
    TOptional<FString> FEzWebSocketSession::GetConnectionId() const
    {
        return ConnectionIdValue;
    }
    TOptional<FString> FEzWebSocketSession::GetNamespaceName() const
    {
        return NamespaceNameValue;
    }
    TOptional<FString> FEzWebSocketSession::GetUserId() const
    {
        return UserIdValue;
    }

    Gs2::Gateway::Model::FWebSocketSessionPtr FEzWebSocketSession::ToModel() const
    {
        return MakeShared<Gs2::Gateway::Model::FWebSocketSession>()
            ->WithConnectionId(ConnectionIdValue)
            ->WithNamespaceName(NamespaceNameValue)
            ->WithUserId(UserIdValue);
    }

    TSharedPtr<FEzWebSocketSession> FEzWebSocketSession::FromModel(const Gs2::Gateway::Model::FWebSocketSessionPtr Model)
    {
        if (Model == nullptr)
        {
            return nullptr;
        }
        return MakeShared<FEzWebSocketSession>()
            ->WithConnectionId(Model->GetConnectionId())
            ->WithNamespaceName(Model->GetNamespaceName())
            ->WithUserId(Model->GetUserId());
    }
}