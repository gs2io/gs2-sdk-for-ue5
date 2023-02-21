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

#include "EzGs2/Public/Realtime/Model/Gs2RealtimeEzRoom.h"

namespace Gs2::UE5::Realtime::Model
{

    TSharedPtr<FEzRoom> FEzRoom::WithName(
        const TOptional<FString> Name
    )
    {
        this->NameValue = Name;
        return SharedThis(this);
    }

    TSharedPtr<FEzRoom> FEzRoom::WithIpAddress(
        const TOptional<FString> IpAddress
    )
    {
        this->IpAddressValue = IpAddress;
        return SharedThis(this);
    }

    TSharedPtr<FEzRoom> FEzRoom::WithPort(
        const TOptional<int32> Port
    )
    {
        this->PortValue = Port;
        return SharedThis(this);
    }

    TSharedPtr<FEzRoom> FEzRoom::WithEncryptionKey(
        const TOptional<FString> EncryptionKey
    )
    {
        this->EncryptionKeyValue = EncryptionKey;
        return SharedThis(this);
    }
    TOptional<FString> FEzRoom::GetName() const
    {
        return NameValue;
    }
    TOptional<FString> FEzRoom::GetIpAddress() const
    {
        return IpAddressValue;
    }
    TOptional<int32> FEzRoom::GetPort() const
    {
        return PortValue;
    }

    FString FEzRoom::GetPortString() const
    {
        if (!PortValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%ld"), PortValue.GetValue());
    }
    TOptional<FString> FEzRoom::GetEncryptionKey() const
    {
        return EncryptionKeyValue;
    }

    Gs2::Realtime::Model::FRoomPtr FEzRoom::ToModel() const
    {
        return MakeShared<Gs2::Realtime::Model::FRoom>()
            ->WithName(NameValue)
            ->WithIpAddress(IpAddressValue)
            ->WithPort(PortValue)
            ->WithEncryptionKey(EncryptionKeyValue);
    }

    TSharedPtr<FEzRoom> FEzRoom::FromModel(const Gs2::Realtime::Model::FRoomPtr Model)
    {
        if (Model == nullptr)
        {
            return nullptr;
        }
        return MakeShared<FEzRoom>()
            ->WithName(Model->GetName())
            ->WithIpAddress(Model->GetIpAddress())
            ->WithPort(Model->GetPort())
            ->WithEncryptionKey(Model->GetEncryptionKey());
    }
}