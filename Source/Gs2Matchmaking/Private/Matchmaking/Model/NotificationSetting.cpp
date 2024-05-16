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

#include "Matchmaking/Model/NotificationSetting.h"

namespace Gs2::Matchmaking::Model
{
    FNotificationSetting::FNotificationSetting():
        GatewayNamespaceIdValue(TOptional<FString>()),
        EnableTransferMobileNotificationValue(TOptional<bool>()),
        SoundValue(TOptional<FString>())
    {
    }

    FNotificationSetting::FNotificationSetting(
        const FNotificationSetting& From
    ):
        GatewayNamespaceIdValue(From.GatewayNamespaceIdValue),
        EnableTransferMobileNotificationValue(From.EnableTransferMobileNotificationValue),
        SoundValue(From.SoundValue)
    {
    }

    TSharedPtr<FNotificationSetting> FNotificationSetting::WithGatewayNamespaceId(
        const TOptional<FString> GatewayNamespaceId
    )
    {
        this->GatewayNamespaceIdValue = GatewayNamespaceId;
        return SharedThis(this);
    }

    TSharedPtr<FNotificationSetting> FNotificationSetting::WithEnableTransferMobileNotification(
        const TOptional<bool> EnableTransferMobileNotification
    )
    {
        this->EnableTransferMobileNotificationValue = EnableTransferMobileNotification;
        return SharedThis(this);
    }

    TSharedPtr<FNotificationSetting> FNotificationSetting::WithSound(
        const TOptional<FString> Sound
    )
    {
        this->SoundValue = Sound;
        return SharedThis(this);
    }
    TOptional<FString> FNotificationSetting::GetGatewayNamespaceId() const
    {
        return GatewayNamespaceIdValue;
    }
    TOptional<bool> FNotificationSetting::GetEnableTransferMobileNotification() const
    {
        return EnableTransferMobileNotificationValue;
    }

    FString FNotificationSetting::GetEnableTransferMobileNotificationString() const
    {
        if (!EnableTransferMobileNotificationValue.IsSet())
        {
            return FString("null");
        }
        return FString(EnableTransferMobileNotificationValue.GetValue() ? "true" : "false");
    }
    TOptional<FString> FNotificationSetting::GetSound() const
    {
        return SoundValue;
    }

    TSharedPtr<FNotificationSetting> FNotificationSetting::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FNotificationSetting>()
            ->WithGatewayNamespaceId(Data->HasField(ANSI_TO_TCHAR("gatewayNamespaceId")) ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("gatewayNamespaceId"), v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithEnableTransferMobileNotification(Data->HasField(ANSI_TO_TCHAR("enableTransferMobileNotification")) ? [Data]() -> TOptional<bool>
                {
                    bool v;
                    if (Data->TryGetBoolField(ANSI_TO_TCHAR("enableTransferMobileNotification"), v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<bool>();
                }() : TOptional<bool>())
            ->WithSound(Data->HasField(ANSI_TO_TCHAR("sound")) ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("sound"), v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>());
    }

    TSharedPtr<FJsonObject> FNotificationSetting::ToJson() const
    {
        const TSharedPtr<FJsonObject> JsonRootObject = MakeShared<FJsonObject>();
        if (GatewayNamespaceIdValue.IsSet())
        {
            JsonRootObject->SetStringField("gatewayNamespaceId", GatewayNamespaceIdValue.GetValue());
        }
        if (EnableTransferMobileNotificationValue.IsSet())
        {
            JsonRootObject->SetBoolField("enableTransferMobileNotification", EnableTransferMobileNotificationValue.GetValue());
        }
        if (SoundValue.IsSet())
        {
            JsonRootObject->SetStringField("sound", SoundValue.GetValue());
        }
        return JsonRootObject;
    }

    FString FNotificationSetting::TypeName = "NotificationSetting";
}