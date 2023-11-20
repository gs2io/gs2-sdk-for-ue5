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

#include "Chat/Model/Gs2ChatEzRoom.h"

namespace Gs2::UE5::Chat::Model
{

    TSharedPtr<FEzRoom> FEzRoom::WithName(
        const TOptional<FString> Name
    )
    {
        this->NameValue = Name;
        return SharedThis(this);
    }

    TSharedPtr<FEzRoom> FEzRoom::WithMetadata(
        const TOptional<FString> Metadata
    )
    {
        this->MetadataValue = Metadata;
        return SharedThis(this);
    }
    TOptional<FString> FEzRoom::GetName() const
    {
        return NameValue;
    }
    TOptional<FString> FEzRoom::GetMetadata() const
    {
        return MetadataValue;
    }

    Gs2::Chat::Model::FRoomPtr FEzRoom::ToModel() const
    {
        return MakeShared<Gs2::Chat::Model::FRoom>()
            ->WithName(NameValue)
            ->WithMetadata(MetadataValue);
    }

    TSharedPtr<FEzRoom> FEzRoom::FromModel(const Gs2::Chat::Model::FRoomPtr Model)
    {
        if (Model == nullptr)
        {
            return nullptr;
        }
        return MakeShared<FEzRoom>()
            ->WithName(Model->GetName())
            ->WithMetadata(Model->GetMetadata());
    }
}