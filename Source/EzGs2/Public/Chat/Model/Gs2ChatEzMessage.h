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
#include "Chat/Model/Message.h"

namespace Gs2::UE5::Chat::Model
{
	class EZGS2_API FEzMessage final : public TSharedFromThis<FEzMessage>
	{
        TOptional<FString> NameValue;
        TOptional<FString> RoomNameValue;
        TOptional<FString> UserIdValue;
        TOptional<int32> CategoryValue;
        TOptional<FString> MetadataValue;
        TOptional<int64> CreatedAtValue;

	public:
        TSharedPtr<FEzMessage> WithName(const TOptional<FString> Name);
        TSharedPtr<FEzMessage> WithRoomName(const TOptional<FString> RoomName);
        TSharedPtr<FEzMessage> WithUserId(const TOptional<FString> UserId);
        TSharedPtr<FEzMessage> WithCategory(const TOptional<int32> Category);
        TSharedPtr<FEzMessage> WithMetadata(const TOptional<FString> Metadata);
        TSharedPtr<FEzMessage> WithCreatedAt(const TOptional<int64> CreatedAt);

        TOptional<FString> GetName() const;

        TOptional<FString> GetRoomName() const;

        TOptional<FString> GetUserId() const;

        TOptional<int32> GetCategory() const;
        FString GetCategoryString() const;

        TOptional<FString> GetMetadata() const;

        TOptional<int64> GetCreatedAt() const;
        FString GetCreatedAtString() const;

        Gs2::Chat::Model::FMessagePtr ToModel() const;
        static TSharedPtr<FEzMessage> FromModel(Gs2::Chat::Model::FMessagePtr Model);
    };
    typedef TSharedPtr<FEzMessage> FEzMessagePtr;
}