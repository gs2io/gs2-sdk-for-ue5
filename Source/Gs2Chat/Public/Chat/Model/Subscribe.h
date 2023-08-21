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
#include "Core/Gs2Object.h"
#include "NotificationType.h"

namespace Gs2::Chat::Model
{
    class GS2CHAT_API FSubscribe final : public Gs2Object, public TSharedFromThis<FSubscribe>
    {
        TOptional<FString> SubscribeIdValue;
        TOptional<FString> UserIdValue;
        TOptional<FString> RoomNameValue;
        TSharedPtr<TArray<TSharedPtr<FNotificationType>>> NotificationTypesValue;
        TOptional<int64> CreatedAtValue;
        TOptional<int64> RevisionValue;

    public:
        FSubscribe();
        FSubscribe(
            const FSubscribe& From
        );
        virtual ~FSubscribe() override = default;

        TSharedPtr<FSubscribe> WithSubscribeId(const TOptional<FString> SubscribeId);
        TSharedPtr<FSubscribe> WithUserId(const TOptional<FString> UserId);
        TSharedPtr<FSubscribe> WithRoomName(const TOptional<FString> RoomName);
        TSharedPtr<FSubscribe> WithNotificationTypes(const TSharedPtr<TArray<TSharedPtr<FNotificationType>>> NotificationTypes);
        TSharedPtr<FSubscribe> WithCreatedAt(const TOptional<int64> CreatedAt);
        TSharedPtr<FSubscribe> WithRevision(const TOptional<int64> Revision);

        TOptional<FString> GetSubscribeId() const;
        TOptional<FString> GetUserId() const;
        TOptional<FString> GetRoomName() const;
        TSharedPtr<TArray<TSharedPtr<FNotificationType>>> GetNotificationTypes() const;
        TOptional<int64> GetCreatedAt() const;
        FString GetCreatedAtString() const;
        TOptional<int64> GetRevision() const;
        FString GetRevisionString() const;

        static TOptional<FString> GetRegionFromGrn(const FString Grn);
        static TOptional<FString> GetOwnerIdFromGrn(const FString Grn);
        static TOptional<FString> GetNamespaceNameFromGrn(const FString Grn);
        static TOptional<FString> GetUserIdFromGrn(const FString Grn);
        static TOptional<FString> GetRoomNameFromGrn(const FString Grn);

        static TSharedPtr<FSubscribe> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;

        static FString TypeName;
    };
    typedef TSharedPtr<FSubscribe, ESPMode::ThreadSafe> FSubscribePtr;
}