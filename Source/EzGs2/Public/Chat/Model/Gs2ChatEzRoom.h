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
#include "Chat/Model/Room.h"

namespace Gs2::UE5::Chat::Model
{
	class EZGS2_API FEzRoom final : public TSharedFromThis<FEzRoom>
	{
        TOptional<FString> NameValue;
        TOptional<FString> MetadataValue;
        TSharedPtr<TArray<FString>> WhiteListUserIdsValue;

	public:
        TSharedPtr<FEzRoom> WithName(const TOptional<FString> Name);
        TSharedPtr<FEzRoom> WithMetadata(const TOptional<FString> Metadata);
        TSharedPtr<FEzRoom> WithWhiteListUserIds(const TSharedPtr<TArray<FString>> WhiteListUserIds);

        TOptional<FString> GetName() const;

        TOptional<FString> GetMetadata() const;

        TSharedPtr<TArray<FString>> GetWhiteListUserIds() const;

        Gs2::Chat::Model::FRoomPtr ToModel() const;
        static TSharedPtr<FEzRoom> FromModel(Gs2::Chat::Model::FRoomPtr Model);
    };
    typedef TSharedPtr<FEzRoom> FEzRoomPtr;
}