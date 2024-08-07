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

#include "Realtime/Model/Room.h"

namespace Gs2::Realtime::Model
{
    FRoom::FRoom():
        RoomIdValue(TOptional<FString>()),
        NameValue(TOptional<FString>()),
        IpAddressValue(TOptional<FString>()),
        PortValue(TOptional<int32>()),
        EncryptionKeyValue(TOptional<FString>()),
        NotificationUserIdsValue(nullptr),
        CreatedAtValue(TOptional<int64>()),
        UpdatedAtValue(TOptional<int64>()),
        RevisionValue(TOptional<int64>())
    {
    }

    FRoom::FRoom(
        const FRoom& From
    ):
        RoomIdValue(From.RoomIdValue),
        NameValue(From.NameValue),
        IpAddressValue(From.IpAddressValue),
        PortValue(From.PortValue),
        EncryptionKeyValue(From.EncryptionKeyValue),
        NotificationUserIdsValue(From.NotificationUserIdsValue),
        CreatedAtValue(From.CreatedAtValue),
        UpdatedAtValue(From.UpdatedAtValue),
        RevisionValue(From.RevisionValue)
    {
    }

    TSharedPtr<FRoom> FRoom::WithRoomId(
        const TOptional<FString> RoomId
    )
    {
        this->RoomIdValue = RoomId;
        return SharedThis(this);
    }

    TSharedPtr<FRoom> FRoom::WithName(
        const TOptional<FString> Name
    )
    {
        this->NameValue = Name;
        return SharedThis(this);
    }

    TSharedPtr<FRoom> FRoom::WithIpAddress(
        const TOptional<FString> IpAddress
    )
    {
        this->IpAddressValue = IpAddress;
        return SharedThis(this);
    }

    TSharedPtr<FRoom> FRoom::WithPort(
        const TOptional<int32> Port
    )
    {
        this->PortValue = Port;
        return SharedThis(this);
    }

    TSharedPtr<FRoom> FRoom::WithEncryptionKey(
        const TOptional<FString> EncryptionKey
    )
    {
        this->EncryptionKeyValue = EncryptionKey;
        return SharedThis(this);
    }

    TSharedPtr<FRoom> FRoom::WithNotificationUserIds(
        const TSharedPtr<TArray<FString>> NotificationUserIds
    )
    {
        this->NotificationUserIdsValue = NotificationUserIds;
        return SharedThis(this);
    }

    TSharedPtr<FRoom> FRoom::WithCreatedAt(
        const TOptional<int64> CreatedAt
    )
    {
        this->CreatedAtValue = CreatedAt;
        return SharedThis(this);
    }

    TSharedPtr<FRoom> FRoom::WithUpdatedAt(
        const TOptional<int64> UpdatedAt
    )
    {
        this->UpdatedAtValue = UpdatedAt;
        return SharedThis(this);
    }

    TSharedPtr<FRoom> FRoom::WithRevision(
        const TOptional<int64> Revision
    )
    {
        this->RevisionValue = Revision;
        return SharedThis(this);
    }
    TOptional<FString> FRoom::GetRoomId() const
    {
        return RoomIdValue;
    }
    TOptional<FString> FRoom::GetName() const
    {
        return NameValue;
    }
    TOptional<FString> FRoom::GetIpAddress() const
    {
        return IpAddressValue;
    }
    TOptional<int32> FRoom::GetPort() const
    {
        return PortValue;
    }

    FString FRoom::GetPortString() const
    {
        if (!PortValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%d"), PortValue.GetValue());
    }
    TOptional<FString> FRoom::GetEncryptionKey() const
    {
        return EncryptionKeyValue;
    }
    TSharedPtr<TArray<FString>> FRoom::GetNotificationUserIds() const
    {
        return NotificationUserIdsValue;
    }
    TOptional<int64> FRoom::GetCreatedAt() const
    {
        return CreatedAtValue;
    }

    FString FRoom::GetCreatedAtString() const
    {
        if (!CreatedAtValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), CreatedAtValue.GetValue());
    }
    TOptional<int64> FRoom::GetUpdatedAt() const
    {
        return UpdatedAtValue;
    }

    FString FRoom::GetUpdatedAtString() const
    {
        if (!UpdatedAtValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), UpdatedAtValue.GetValue());
    }
    TOptional<int64> FRoom::GetRevision() const
    {
        return RevisionValue;
    }

    FString FRoom::GetRevisionString() const
    {
        if (!RevisionValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), RevisionValue.GetValue());
    }

    TOptional<FString> FRoom::GetRegionFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):realtime:(?<namespaceName>.+):room:(?<roomName>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(1);
        }
        return TOptional<FString>();
    }

    TOptional<FString> FRoom::GetOwnerIdFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):realtime:(?<namespaceName>.+):room:(?<roomName>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(2);
        }
        return TOptional<FString>();
    }

    TOptional<FString> FRoom::GetNamespaceNameFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):realtime:(?<namespaceName>.+):room:(?<roomName>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(3);
        }
        return TOptional<FString>();
    }

    TOptional<FString> FRoom::GetRoomNameFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):realtime:(?<namespaceName>.+):room:(?<roomName>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(4);
        }
        return TOptional<FString>();
    }

    TSharedPtr<FRoom> FRoom::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FRoom>()
            ->WithRoomId(Data->HasField(ANSI_TO_TCHAR("roomId")) ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("roomId"), v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithName(Data->HasField(ANSI_TO_TCHAR("name")) ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("name"), v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithIpAddress(Data->HasField(ANSI_TO_TCHAR("ipAddress")) ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("ipAddress"), v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithPort(Data->HasField(ANSI_TO_TCHAR("port")) ? [Data]() -> TOptional<int32>
                {
                    int32 v;
                    if (Data->TryGetNumberField(ANSI_TO_TCHAR("port"), v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<int32>();
                }() : TOptional<int32>())
            ->WithEncryptionKey(Data->HasField(ANSI_TO_TCHAR("encryptionKey")) ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("encryptionKey"), v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithNotificationUserIds(Data->HasField(ANSI_TO_TCHAR("notificationUserIds")) ? [Data]() -> TSharedPtr<TArray<FString>>
                {
                    auto v = MakeShared<TArray<FString>>();
                    if (!Data->HasTypedField<EJson::Null>(ANSI_TO_TCHAR("notificationUserIds")) && Data->HasTypedField<EJson::Array>(ANSI_TO_TCHAR("notificationUserIds")))
                    {
                        for (auto JsonObjectValue : Data->GetArrayField(ANSI_TO_TCHAR("notificationUserIds")))
                        {
                            v->Add(JsonObjectValue->AsString());
                        }
                    }
                    return v;
                 }() : MakeShared<TArray<FString>>())
            ->WithCreatedAt(Data->HasField(ANSI_TO_TCHAR("createdAt")) ? [Data]() -> TOptional<int64>
                {
                    int64 v;
                    if (Data->TryGetNumberField(ANSI_TO_TCHAR("createdAt"), v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<int64>();
                }() : TOptional<int64>())
            ->WithUpdatedAt(Data->HasField(ANSI_TO_TCHAR("updatedAt")) ? [Data]() -> TOptional<int64>
                {
                    int64 v;
                    if (Data->TryGetNumberField(ANSI_TO_TCHAR("updatedAt"), v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<int64>();
                }() : TOptional<int64>())
            ->WithRevision(Data->HasField(ANSI_TO_TCHAR("revision")) ? [Data]() -> TOptional<int64>
                {
                    int64 v;
                    if (Data->TryGetNumberField(ANSI_TO_TCHAR("revision"), v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<int64>();
                }() : TOptional<int64>());
    }

    TSharedPtr<FJsonObject> FRoom::ToJson() const
    {
        const TSharedPtr<FJsonObject> JsonRootObject = MakeShared<FJsonObject>();
        if (RoomIdValue.IsSet())
        {
            JsonRootObject->SetStringField("roomId", RoomIdValue.GetValue());
        }
        if (NameValue.IsSet())
        {
            JsonRootObject->SetStringField("name", NameValue.GetValue());
        }
        if (IpAddressValue.IsSet())
        {
            JsonRootObject->SetStringField("ipAddress", IpAddressValue.GetValue());
        }
        if (PortValue.IsSet())
        {
            JsonRootObject->SetNumberField("port", PortValue.GetValue());
        }
        if (EncryptionKeyValue.IsSet())
        {
            JsonRootObject->SetStringField("encryptionKey", EncryptionKeyValue.GetValue());
        }
        if (NotificationUserIdsValue != nullptr && NotificationUserIdsValue.IsValid())
        {
            TArray<TSharedPtr<FJsonValue>> v;
            for (auto JsonObjectValue : *NotificationUserIdsValue)
            {
                v.Add(MakeShared<FJsonValueString>(JsonObjectValue));
            }
            JsonRootObject->SetArrayField("notificationUserIds", v);
        }
        if (CreatedAtValue.IsSet())
        {
            JsonRootObject->SetStringField("createdAt", FString::Printf(TEXT("%lld"), CreatedAtValue.GetValue()));
        }
        if (UpdatedAtValue.IsSet())
        {
            JsonRootObject->SetStringField("updatedAt", FString::Printf(TEXT("%lld"), UpdatedAtValue.GetValue()));
        }
        if (RevisionValue.IsSet())
        {
            JsonRootObject->SetStringField("revision", FString::Printf(TEXT("%lld"), RevisionValue.GetValue()));
        }
        return JsonRootObject;
    }

    FString FRoom::TypeName = "Room";
}