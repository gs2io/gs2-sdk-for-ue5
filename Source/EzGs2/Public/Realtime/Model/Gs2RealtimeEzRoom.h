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
#include "Realtime/Model/Room.h"

namespace Gs2::UE5::Realtime::Model
{
	class EZGS2_API FEzRoom final : public TSharedFromThis<FEzRoom>
	{
        TOptional<FString> NameValue;
        TOptional<FString> IpAddressValue;
        TOptional<int32> PortValue;
        TOptional<FString> EncryptionKeyValue;

	public:
        TSharedPtr<FEzRoom> WithName(const TOptional<FString> Name);
        TSharedPtr<FEzRoom> WithIpAddress(const TOptional<FString> IpAddress);
        TSharedPtr<FEzRoom> WithPort(const TOptional<int32> Port);
        TSharedPtr<FEzRoom> WithEncryptionKey(const TOptional<FString> EncryptionKey);

        TOptional<FString> GetName() const;

        TOptional<FString> GetIpAddress() const;

        TOptional<int32> GetPort() const;
        FString GetPortString() const;

        TOptional<FString> GetEncryptionKey() const;

        Gs2::Realtime::Model::FRoomPtr ToModel() const;
        static TSharedPtr<FEzRoom> FromModel(Gs2::Realtime::Model::FRoomPtr Model);
    };
    typedef TSharedPtr<FEzRoom> FEzRoomPtr;
}