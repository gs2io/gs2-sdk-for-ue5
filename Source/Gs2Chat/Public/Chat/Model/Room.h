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

namespace Gs2::Chat::Model
{
    class GS2CHAT_API FRoom final : public FGs2Object, public TSharedFromThis<FRoom>
    {
        TOptional<FString> RoomIdValue;
        TOptional<FString> NameValue;
        TOptional<FString> UserIdValue;
        TOptional<FString> MetadataValue;
        TOptional<FString> PasswordValue;
        TSharedPtr<TArray<FString>> WhiteListUserIdsValue;
        TOptional<int64> CreatedAtValue;
        TOptional<int64> UpdatedAtValue;
        TOptional<int64> RevisionValue;

    public:
        FRoom();
        FRoom(
            const FRoom& From
        );
        virtual ~FRoom() override = default;

        TSharedPtr<FRoom> WithRoomId(const TOptional<FString> RoomId);
        TSharedPtr<FRoom> WithName(const TOptional<FString> Name);
        TSharedPtr<FRoom> WithUserId(const TOptional<FString> UserId);
        TSharedPtr<FRoom> WithMetadata(const TOptional<FString> Metadata);
        TSharedPtr<FRoom> WithPassword(const TOptional<FString> Password);
        TSharedPtr<FRoom> WithWhiteListUserIds(const TSharedPtr<TArray<FString>> WhiteListUserIds);
        TSharedPtr<FRoom> WithCreatedAt(const TOptional<int64> CreatedAt);
        TSharedPtr<FRoom> WithUpdatedAt(const TOptional<int64> UpdatedAt);
        TSharedPtr<FRoom> WithRevision(const TOptional<int64> Revision);

        TOptional<FString> GetRoomId() const;
        TOptional<FString> GetName() const;
        TOptional<FString> GetUserId() const;
        TOptional<FString> GetMetadata() const;
        TOptional<FString> GetPassword() const;
        TSharedPtr<TArray<FString>> GetWhiteListUserIds() const;
        TOptional<int64> GetCreatedAt() const;
        FString GetCreatedAtString() const;
        TOptional<int64> GetUpdatedAt() const;
        FString GetUpdatedAtString() const;
        TOptional<int64> GetRevision() const;
        FString GetRevisionString() const;

        static TOptional<FString> GetRegionFromGrn(const FString Grn);
        static TOptional<FString> GetOwnerIdFromGrn(const FString Grn);
        static TOptional<FString> GetNamespaceNameFromGrn(const FString Grn);
        static TOptional<FString> GetRoomNameFromGrn(const FString Grn);

        static TSharedPtr<FRoom> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;

        static FString TypeName;
    };
    typedef TSharedPtr<FRoom, ESPMode::ThreadSafe> FRoomPtr;
}