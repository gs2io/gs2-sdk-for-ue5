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
    class FGetRoomRequest;

    class GS2CHAT_API FGetRoomRequest final : public TSharedFromThis<FGetRoomRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> RoomNameValue;
        
    public:
        
        FGetRoomRequest();
        FGetRoomRequest(
            const FGetRoomRequest& From
        );
        ~FGetRoomRequest() = default;

        TSharedPtr<FGetRoomRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FGetRoomRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FGetRoomRequest> WithRoomName(const TOptional<FString> RoomName);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetRoomName() const;

        static TSharedPtr<FGetRoomRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FGetRoomRequest> FGetRoomRequestPtr;
}