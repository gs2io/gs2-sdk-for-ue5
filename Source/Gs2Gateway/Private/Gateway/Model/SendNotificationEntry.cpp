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

#include "Gateway/Model/SendNotificationEntry.h"

namespace Gs2::Gateway::Model
{
    FSendNotificationEntry::FSendNotificationEntry():
        UserIdValue(TOptional<FString>()),
        IssuerValue(TOptional<FString>()),
        SubjectValue(TOptional<FString>()),
        PayloadValue(TOptional<FString>()),
        EnableTransferMobileNotificationValue(TOptional<bool>()),
        SoundValue(TOptional<FString>())
    {
    }

    FSendNotificationEntry::FSendNotificationEntry(
        const FSendNotificationEntry& From
    ):
        UserIdValue(From.UserIdValue),
        IssuerValue(From.IssuerValue),
        SubjectValue(From.SubjectValue),
        PayloadValue(From.PayloadValue),
        EnableTransferMobileNotificationValue(From.EnableTransferMobileNotificationValue),
        SoundValue(From.SoundValue)
    {
    }

    TSharedPtr<FSendNotificationEntry> FSendNotificationEntry::WithUserId(
        const TOptional<FString> UserId
    )
    {
        this->UserIdValue = UserId;
        return SharedThis(this);
    }

    TSharedPtr<FSendNotificationEntry> FSendNotificationEntry::WithIssuer(
        const TOptional<FString> Issuer
    )
    {
        this->IssuerValue = Issuer;
        return SharedThis(this);
    }

    TSharedPtr<FSendNotificationEntry> FSendNotificationEntry::WithSubject(
        const TOptional<FString> Subject
    )
    {
        this->SubjectValue = Subject;
        return SharedThis(this);
    }

    TSharedPtr<FSendNotificationEntry> FSendNotificationEntry::WithPayload(
        const TOptional<FString> Payload
    )
    {
        this->PayloadValue = Payload;
        return SharedThis(this);
    }

    TSharedPtr<FSendNotificationEntry> FSendNotificationEntry::WithEnableTransferMobileNotification(
        const TOptional<bool> EnableTransferMobileNotification
    )
    {
        this->EnableTransferMobileNotificationValue = EnableTransferMobileNotification;
        return SharedThis(this);
    }

    TSharedPtr<FSendNotificationEntry> FSendNotificationEntry::WithSound(
        const TOptional<FString> Sound
    )
    {
        this->SoundValue = Sound;
        return SharedThis(this);
    }
    TOptional<FString> FSendNotificationEntry::GetUserId() const
    {
        return UserIdValue;
    }
    TOptional<FString> FSendNotificationEntry::GetIssuer() const
    {
        return IssuerValue;
    }
    TOptional<FString> FSendNotificationEntry::GetSubject() const
    {
        return SubjectValue;
    }
    TOptional<FString> FSendNotificationEntry::GetPayload() const
    {
        return PayloadValue;
    }
    TOptional<bool> FSendNotificationEntry::GetEnableTransferMobileNotification() const
    {
        return EnableTransferMobileNotificationValue;
    }

    FString FSendNotificationEntry::GetEnableTransferMobileNotificationString() const
    {
        if (!EnableTransferMobileNotificationValue.IsSet())
        {
            return FString("null");
        }
        return FString(EnableTransferMobileNotificationValue.GetValue() ? "true" : "false");
    }
    TOptional<FString> FSendNotificationEntry::GetSound() const
    {
        return SoundValue;
    }

    TSharedPtr<FSendNotificationEntry> FSendNotificationEntry::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FSendNotificationEntry>()
            ->WithUserId(Data->HasField(ANSI_TO_TCHAR("userId")) ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("userId"), v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithIssuer(Data->HasField(ANSI_TO_TCHAR("issuer")) ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("issuer"), v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithSubject(Data->HasField(ANSI_TO_TCHAR("subject")) ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("subject"), v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithPayload(Data->HasField(ANSI_TO_TCHAR("payload")) ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("payload"), v))
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

    TSharedPtr<FJsonObject> FSendNotificationEntry::ToJson() const
    {
        const TSharedPtr<FJsonObject> JsonRootObject = MakeShared<FJsonObject>();
        if (UserIdValue.IsSet())
        {
            JsonRootObject->SetStringField("userId", UserIdValue.GetValue());
        }
        if (IssuerValue.IsSet())
        {
            JsonRootObject->SetStringField("issuer", IssuerValue.GetValue());
        }
        if (SubjectValue.IsSet())
        {
            JsonRootObject->SetStringField("subject", SubjectValue.GetValue());
        }
        if (PayloadValue.IsSet())
        {
            JsonRootObject->SetStringField("payload", PayloadValue.GetValue());
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

    FString FSendNotificationEntry::TypeName = "SendNotificationEntry";
}