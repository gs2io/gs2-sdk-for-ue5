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

#include "EzGs2/Public/Chat/Model/Gs2ChatEzMessage.h"

namespace Gs2::UE5::Chat::Model
{

    TSharedPtr<FEzMessage> FEzMessage::WithName(
        const TOptional<FString> Name
    )
    {
        this->NameValue = Name;
        return SharedThis(this);
    }

    TSharedPtr<FEzMessage> FEzMessage::WithRoomName(
        const TOptional<FString> RoomName
    )
    {
        this->RoomNameValue = RoomName;
        return SharedThis(this);
    }

    TSharedPtr<FEzMessage> FEzMessage::WithUserId(
        const TOptional<FString> UserId
    )
    {
        this->UserIdValue = UserId;
        return SharedThis(this);
    }

    TSharedPtr<FEzMessage> FEzMessage::WithCategory(
        const TOptional<int32> Category
    )
    {
        this->CategoryValue = Category;
        return SharedThis(this);
    }

    TSharedPtr<FEzMessage> FEzMessage::WithMetadata(
        const TOptional<FString> Metadata
    )
    {
        this->MetadataValue = Metadata;
        return SharedThis(this);
    }

    TSharedPtr<FEzMessage> FEzMessage::WithCreatedAt(
        const TOptional<int64> CreatedAt
    )
    {
        this->CreatedAtValue = CreatedAt;
        return SharedThis(this);
    }
    TOptional<FString> FEzMessage::GetName() const
    {
        return NameValue;
    }
    TOptional<FString> FEzMessage::GetRoomName() const
    {
        return RoomNameValue;
    }
    TOptional<FString> FEzMessage::GetUserId() const
    {
        return UserIdValue;
    }
    TOptional<int32> FEzMessage::GetCategory() const
    {
        return CategoryValue;
    }

    FString FEzMessage::GetCategoryString() const
    {
        if (!CategoryValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%ld"), CategoryValue.GetValue());
    }
    TOptional<FString> FEzMessage::GetMetadata() const
    {
        return MetadataValue;
    }
    TOptional<int64> FEzMessage::GetCreatedAt() const
    {
        return CreatedAtValue;
    }

    FString FEzMessage::GetCreatedAtString() const
    {
        if (!CreatedAtValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), CreatedAtValue.GetValue());
    }

    Gs2::Chat::Model::FMessagePtr FEzMessage::ToModel() const
    {
        return MakeShared<Gs2::Chat::Model::FMessage>()
            ->WithName(NameValue)
            ->WithRoomName(RoomNameValue)
            ->WithUserId(UserIdValue)
            ->WithCategory(CategoryValue)
            ->WithMetadata(MetadataValue)
            ->WithCreatedAt(CreatedAtValue);
    }

    TSharedPtr<FEzMessage> FEzMessage::FromModel(const Gs2::Chat::Model::FMessagePtr Model)
    {
        if (Model == nullptr)
        {
            return nullptr;
        }
        return MakeShared<FEzMessage>()
            ->WithName(Model->GetName())
            ->WithRoomName(Model->GetRoomName())
            ->WithUserId(Model->GetUserId())
            ->WithCategory(Model->GetCategory())
            ->WithMetadata(Model->GetMetadata())
            ->WithCreatedAt(Model->GetCreatedAt());
    }
}