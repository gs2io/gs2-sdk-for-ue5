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

#include "Money2/Model/GooglePlayRealtimeNotificationMessage.h"

namespace Gs2::Money2::Model
{
    FGooglePlayRealtimeNotificationMessage::FGooglePlayRealtimeNotificationMessage():
        DataValue(TOptional<FString>()),
        MessageIdValue(TOptional<FString>()),
        PublishTimeValue(TOptional<FString>())
    {
    }

    FGooglePlayRealtimeNotificationMessage::FGooglePlayRealtimeNotificationMessage(
        const FGooglePlayRealtimeNotificationMessage& From
    ):
        DataValue(From.DataValue),
        MessageIdValue(From.MessageIdValue),
        PublishTimeValue(From.PublishTimeValue)
    {
    }

    TSharedPtr<FGooglePlayRealtimeNotificationMessage> FGooglePlayRealtimeNotificationMessage::WithData(
        const TOptional<FString> Data
    )
    {
        this->DataValue = Data;
        return SharedThis(this);
    }

    TSharedPtr<FGooglePlayRealtimeNotificationMessage> FGooglePlayRealtimeNotificationMessage::WithMessageId(
        const TOptional<FString> MessageId
    )
    {
        this->MessageIdValue = MessageId;
        return SharedThis(this);
    }

    TSharedPtr<FGooglePlayRealtimeNotificationMessage> FGooglePlayRealtimeNotificationMessage::WithPublishTime(
        const TOptional<FString> PublishTime
    )
    {
        this->PublishTimeValue = PublishTime;
        return SharedThis(this);
    }
    TOptional<FString> FGooglePlayRealtimeNotificationMessage::GetData() const
    {
        return DataValue;
    }
    TOptional<FString> FGooglePlayRealtimeNotificationMessage::GetMessageId() const
    {
        return MessageIdValue;
    }
    TOptional<FString> FGooglePlayRealtimeNotificationMessage::GetPublishTime() const
    {
        return PublishTimeValue;
    }

    TSharedPtr<FGooglePlayRealtimeNotificationMessage> FGooglePlayRealtimeNotificationMessage::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FGooglePlayRealtimeNotificationMessage>()
            ->WithData(Data->HasField(ANSI_TO_TCHAR("data")) ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("data"), v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithMessageId(Data->HasField(ANSI_TO_TCHAR("messageId")) ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("messageId"), v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithPublishTime(Data->HasField(ANSI_TO_TCHAR("publishTime")) ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("publishTime"), v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>());
    }

    TSharedPtr<FJsonObject> FGooglePlayRealtimeNotificationMessage::ToJson() const
    {
        const TSharedPtr<FJsonObject> JsonRootObject = MakeShared<FJsonObject>();
        if (DataValue.IsSet())
        {
            JsonRootObject->SetStringField("data", DataValue.GetValue());
        }
        if (MessageIdValue.IsSet())
        {
            JsonRootObject->SetStringField("messageId", MessageIdValue.GetValue());
        }
        if (PublishTimeValue.IsSet())
        {
            JsonRootObject->SetStringField("publishTime", PublishTimeValue.GetValue());
        }
        return JsonRootObject;
    }

    FString FGooglePlayRealtimeNotificationMessage::TypeName = "GooglePlayRealtimeNotificationMessage";
}