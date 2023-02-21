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

namespace Gs2::Chat::Model
{
    class GS2CHAT_API FMessage final : public TSharedFromThis<FMessage>
    {
        TOptional<FString> MessageIdValue;
        TOptional<FString> RoomNameValue;
        TOptional<FString> NameValue;
        TOptional<FString> UserIdValue;
        TOptional<int32> CategoryValue;
        TOptional<FString> MetadataValue;
        TOptional<int64> CreatedAtValue;

    public:
        FMessage();
        FMessage(
            const FMessage& From
        );
        ~FMessage() = default;

        TSharedPtr<FMessage> WithMessageId(const TOptional<FString> MessageId);
        TSharedPtr<FMessage> WithRoomName(const TOptional<FString> RoomName);
        TSharedPtr<FMessage> WithName(const TOptional<FString> Name);
        TSharedPtr<FMessage> WithUserId(const TOptional<FString> UserId);
        TSharedPtr<FMessage> WithCategory(const TOptional<int32> Category);
        TSharedPtr<FMessage> WithMetadata(const TOptional<FString> Metadata);
        TSharedPtr<FMessage> WithCreatedAt(const TOptional<int64> CreatedAt);

        TOptional<FString> GetMessageId() const;
        TOptional<FString> GetRoomName() const;
        TOptional<FString> GetName() const;
        TOptional<FString> GetUserId() const;
        TOptional<int32> GetCategory() const;
        FString GetCategoryString() const;
        TOptional<FString> GetMetadata() const;
        TOptional<int64> GetCreatedAt() const;
        FString GetCreatedAtString() const;

        static TOptional<FString> GetRegionFromGrn(const FString Grn);
        static TOptional<FString> GetOwnerIdFromGrn(const FString Grn);
        static TOptional<FString> GetNamespaceNameFromGrn(const FString Grn);
        static TOptional<FString> GetRoomNameFromGrn(const FString Grn);
        static TOptional<FString> GetMessageNameFromGrn(const FString Grn);

        static TSharedPtr<FMessage> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;

        static FString TypeName;
    };
    typedef TSharedPtr<FMessage, ESPMode::ThreadSafe> FMessagePtr;
}