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

namespace Gs2::Realtime::Request
{
    class FWantRoomRequest;

    class GS2REALTIME_API FWantRoomRequest final : public TSharedFromThis<FWantRoomRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> NameValue;
        TSharedPtr<TArray<FString>> NotificationUserIdsValue;
        
    public:
        
        FWantRoomRequest();
        FWantRoomRequest(
            const FWantRoomRequest& From
        );
        ~FWantRoomRequest() = default;

        TSharedPtr<FWantRoomRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FWantRoomRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FWantRoomRequest> WithName(const TOptional<FString> Name);
        TSharedPtr<FWantRoomRequest> WithNotificationUserIds(
            const TSharedPtr<TArray<FString>> NotificationUserIds);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetName() const;
        TSharedPtr<TArray<FString>> GetNotificationUserIds() const;

        static TSharedPtr<FWantRoomRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FWantRoomRequest> FWantRoomRequestPtr;
}