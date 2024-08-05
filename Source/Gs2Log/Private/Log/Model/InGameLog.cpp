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

#include "Log/Model/InGameLog.h"

namespace Gs2::Log::Model
{
    FInGameLog::FInGameLog():
        TimestampValue(TOptional<int64>()),
        RequestIdValue(TOptional<FString>()),
        UserIdValue(TOptional<FString>()),
        TagsValue(nullptr),
        PayloadValue(TOptional<FString>())
    {
    }

    FInGameLog::FInGameLog(
        const FInGameLog& From
    ):
        TimestampValue(From.TimestampValue),
        RequestIdValue(From.RequestIdValue),
        UserIdValue(From.UserIdValue),
        TagsValue(From.TagsValue),
        PayloadValue(From.PayloadValue)
    {
    }

    TSharedPtr<FInGameLog> FInGameLog::WithTimestamp(
        const TOptional<int64> Timestamp
    )
    {
        this->TimestampValue = Timestamp;
        return SharedThis(this);
    }

    TSharedPtr<FInGameLog> FInGameLog::WithRequestId(
        const TOptional<FString> RequestId
    )
    {
        this->RequestIdValue = RequestId;
        return SharedThis(this);
    }

    TSharedPtr<FInGameLog> FInGameLog::WithUserId(
        const TOptional<FString> UserId
    )
    {
        this->UserIdValue = UserId;
        return SharedThis(this);
    }

    TSharedPtr<FInGameLog> FInGameLog::WithTags(
        const TSharedPtr<TArray<TSharedPtr<Model::FInGameLogTag>>> Tags
    )
    {
        this->TagsValue = Tags;
        return SharedThis(this);
    }

    TSharedPtr<FInGameLog> FInGameLog::WithPayload(
        const TOptional<FString> Payload
    )
    {
        this->PayloadValue = Payload;
        return SharedThis(this);
    }
    TOptional<int64> FInGameLog::GetTimestamp() const
    {
        return TimestampValue;
    }

    FString FInGameLog::GetTimestampString() const
    {
        if (!TimestampValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), TimestampValue.GetValue());
    }
    TOptional<FString> FInGameLog::GetRequestId() const
    {
        return RequestIdValue;
    }
    TOptional<FString> FInGameLog::GetUserId() const
    {
        return UserIdValue;
    }
    TSharedPtr<TArray<TSharedPtr<Model::FInGameLogTag>>> FInGameLog::GetTags() const
    {
        return TagsValue;
    }
    TOptional<FString> FInGameLog::GetPayload() const
    {
        return PayloadValue;
    }

    TSharedPtr<FInGameLog> FInGameLog::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FInGameLog>()
            ->WithTimestamp(Data->HasField(ANSI_TO_TCHAR("timestamp")) ? [Data]() -> TOptional<int64>
                {
                    int64 v;
                    if (Data->TryGetNumberField(ANSI_TO_TCHAR("timestamp"), v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<int64>();
                }() : TOptional<int64>())
            ->WithRequestId(Data->HasField(ANSI_TO_TCHAR("requestId")) ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("requestId"), v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithUserId(Data->HasField(ANSI_TO_TCHAR("userId")) ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("userId"), v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithTags(Data->HasField(ANSI_TO_TCHAR("tags")) ? [Data]() -> TSharedPtr<TArray<Model::FInGameLogTagPtr>>
                {
                    auto v = MakeShared<TArray<Model::FInGameLogTagPtr>>();
                    if (!Data->HasTypedField<EJson::Null>(ANSI_TO_TCHAR("tags")) && Data->HasTypedField<EJson::Array>(ANSI_TO_TCHAR("tags")))
                    {
                        for (auto JsonObjectValue : Data->GetArrayField(ANSI_TO_TCHAR("tags")))
                        {
                            v->Add(Model::FInGameLogTag::FromJson(JsonObjectValue->AsObject()));
                        }
                    }
                    return v;
                 }() : MakeShared<TArray<Model::FInGameLogTagPtr>>())
            ->WithPayload(Data->HasField(ANSI_TO_TCHAR("payload")) ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("payload"), v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>());
    }

    TSharedPtr<FJsonObject> FInGameLog::ToJson() const
    {
        const TSharedPtr<FJsonObject> JsonRootObject = MakeShared<FJsonObject>();
        if (TimestampValue.IsSet())
        {
            JsonRootObject->SetStringField("timestamp", FString::Printf(TEXT("%lld"), TimestampValue.GetValue()));
        }
        if (RequestIdValue.IsSet())
        {
            JsonRootObject->SetStringField("requestId", RequestIdValue.GetValue());
        }
        if (UserIdValue.IsSet())
        {
            JsonRootObject->SetStringField("userId", UserIdValue.GetValue());
        }
        if (TagsValue != nullptr && TagsValue.IsValid())
        {
            TArray<TSharedPtr<FJsonValue>> v;
            for (auto JsonObjectValue : *TagsValue)
            {
                v.Add(MakeShared<FJsonValueObject>(JsonObjectValue->ToJson()));
            }
            JsonRootObject->SetArrayField("tags", v);
        }
        if (PayloadValue.IsSet())
        {
            JsonRootObject->SetStringField("payload", PayloadValue.GetValue());
        }
        return JsonRootObject;
    }

    FString FInGameLog::TypeName = "InGameLog";
}