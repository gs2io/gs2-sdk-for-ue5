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

#include "Chat/Model/MobileNotificationMessage.h"

namespace Gs2::Chat::Model
{
    FMobileNotificationMessage::FMobileNotificationMessage():
        LocaleValue(TOptional<FString>()),
        TitleValue(TOptional<FString>()),
        MessageValue(TOptional<FString>())
    {
    }

    FMobileNotificationMessage::FMobileNotificationMessage(
        const FMobileNotificationMessage& From
    ):
        LocaleValue(From.LocaleValue),
        TitleValue(From.TitleValue),
        MessageValue(From.MessageValue)
    {
    }

    TSharedPtr<FMobileNotificationMessage> FMobileNotificationMessage::WithLocale(
        const TOptional<FString> Locale
    )
    {
        this->LocaleValue = Locale;
        return SharedThis(this);
    }

    TSharedPtr<FMobileNotificationMessage> FMobileNotificationMessage::WithTitle(
        const TOptional<FString> Title
    )
    {
        this->TitleValue = Title;
        return SharedThis(this);
    }

    TSharedPtr<FMobileNotificationMessage> FMobileNotificationMessage::WithMessage(
        const TOptional<FString> Message
    )
    {
        this->MessageValue = Message;
        return SharedThis(this);
    }
    TOptional<FString> FMobileNotificationMessage::GetLocale() const
    {
        return LocaleValue;
    }
    TOptional<FString> FMobileNotificationMessage::GetTitle() const
    {
        return TitleValue;
    }
    TOptional<FString> FMobileNotificationMessage::GetMessage() const
    {
        return MessageValue;
    }

    TSharedPtr<FMobileNotificationMessage> FMobileNotificationMessage::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FMobileNotificationMessage>()
            ->WithLocale(Data->HasField(ANSI_TO_TCHAR("locale")) ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("locale"), v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithTitle(Data->HasField(ANSI_TO_TCHAR("title")) ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("title"), v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithMessage(Data->HasField(ANSI_TO_TCHAR("message")) ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("message"), v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>());
    }

    TSharedPtr<FJsonObject> FMobileNotificationMessage::ToJson() const
    {
        const TSharedPtr<FJsonObject> JsonRootObject = MakeShared<FJsonObject>();
        if (LocaleValue.IsSet())
        {
            JsonRootObject->SetStringField(TEXT("locale"), LocaleValue.GetValue());
        }
        if (TitleValue.IsSet())
        {
            JsonRootObject->SetStringField(TEXT("title"), TitleValue.GetValue());
        }
        if (MessageValue.IsSet())
        {
            JsonRootObject->SetStringField(TEXT("message"), MessageValue.GetValue());
        }
        return JsonRootObject;
    }

    FString FMobileNotificationMessage::TypeName = "MobileNotificationMessage";
}