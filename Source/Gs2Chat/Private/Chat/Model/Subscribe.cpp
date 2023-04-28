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

#include "Chat/Model/Subscribe.h"

namespace Gs2::Chat::Model
{
    FSubscribe::FSubscribe():
        SubscribeIdValue(TOptional<FString>()),
        UserIdValue(TOptional<FString>()),
        RoomNameValue(TOptional<FString>()),
        NotificationTypesValue(nullptr),
        CreatedAtValue(TOptional<int64>())
    {
    }

    FSubscribe::FSubscribe(
        const FSubscribe& From
    ):
        SubscribeIdValue(From.SubscribeIdValue),
        UserIdValue(From.UserIdValue),
        RoomNameValue(From.RoomNameValue),
        NotificationTypesValue(From.NotificationTypesValue),
        CreatedAtValue(From.CreatedAtValue)
    {
    }

    TSharedPtr<FSubscribe> FSubscribe::WithSubscribeId(
        const TOptional<FString> SubscribeId
    )
    {
        this->SubscribeIdValue = SubscribeId;
        return SharedThis(this);
    }

    TSharedPtr<FSubscribe> FSubscribe::WithUserId(
        const TOptional<FString> UserId
    )
    {
        this->UserIdValue = UserId;
        return SharedThis(this);
    }

    TSharedPtr<FSubscribe> FSubscribe::WithRoomName(
        const TOptional<FString> RoomName
    )
    {
        this->RoomNameValue = RoomName;
        return SharedThis(this);
    }

    TSharedPtr<FSubscribe> FSubscribe::WithNotificationTypes(
        const TSharedPtr<TArray<TSharedPtr<Model::FNotificationType>>> NotificationTypes
    )
    {
        this->NotificationTypesValue = NotificationTypes;
        return SharedThis(this);
    }

    TSharedPtr<FSubscribe> FSubscribe::WithCreatedAt(
        const TOptional<int64> CreatedAt
    )
    {
        this->CreatedAtValue = CreatedAt;
        return SharedThis(this);
    }
    TOptional<FString> FSubscribe::GetSubscribeId() const
    {
        return SubscribeIdValue;
    }
    TOptional<FString> FSubscribe::GetUserId() const
    {
        return UserIdValue;
    }
    TOptional<FString> FSubscribe::GetRoomName() const
    {
        return RoomNameValue;
    }
    TSharedPtr<TArray<TSharedPtr<Model::FNotificationType>>> FSubscribe::GetNotificationTypes() const
    {
        return NotificationTypesValue;
    }
    TOptional<int64> FSubscribe::GetCreatedAt() const
    {
        return CreatedAtValue;
    }

    FString FSubscribe::GetCreatedAtString() const
    {
        if (!CreatedAtValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), CreatedAtValue.GetValue());
    }

    TOptional<FString> FSubscribe::GetRegionFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):chat:(?<namespaceName>.+):user:(?<userId>.+):subscribe:(?<roomName>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(1);
        }
        return TOptional<FString>();
    }

    TOptional<FString> FSubscribe::GetOwnerIdFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):chat:(?<namespaceName>.+):user:(?<userId>.+):subscribe:(?<roomName>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(2);
        }
        return TOptional<FString>();
    }

    TOptional<FString> FSubscribe::GetNamespaceNameFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):chat:(?<namespaceName>.+):user:(?<userId>.+):subscribe:(?<roomName>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(3);
        }
        return TOptional<FString>();
    }

    TOptional<FString> FSubscribe::GetUserIdFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):chat:(?<namespaceName>.+):user:(?<userId>.+):subscribe:(?<roomName>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(4);
        }
        return TOptional<FString>();
    }

    TOptional<FString> FSubscribe::GetRoomNameFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):chat:(?<namespaceName>.+):user:(?<userId>.+):subscribe:(?<roomName>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(5);
        }
        return TOptional<FString>();
    }

    TSharedPtr<FSubscribe> FSubscribe::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FSubscribe>()
            ->WithSubscribeId(Data->HasField("subscribeId") ? [Data]() -> TOptional<FString>
                {
                    FString v;
                    if (Data->TryGetStringField("subscribeId", v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithUserId(Data->HasField("userId") ? [Data]() -> TOptional<FString>
                {
                    FString v;
                    if (Data->TryGetStringField("userId", v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithRoomName(Data->HasField("roomName") ? [Data]() -> TOptional<FString>
                {
                    FString v;
                    if (Data->TryGetStringField("roomName", v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithNotificationTypes(Data->HasField("notificationTypes") ? [Data]() -> TSharedPtr<TArray<Model::FNotificationTypePtr>>
                {
                    auto v = MakeShared<TArray<Model::FNotificationTypePtr>>();
                    if (!Data->HasTypedField<EJson::Null>("notificationTypes") && Data->HasTypedField<EJson::Array>("notificationTypes"))
                    {
                        for (auto JsonObjectValue : Data->GetArrayField("notificationTypes"))
                        {
                            v->Add(Model::FNotificationType::FromJson(JsonObjectValue->AsObject()));
                        }
                    }
                    return v;
                 }() : MakeShared<TArray<Model::FNotificationTypePtr>>())
            ->WithCreatedAt(Data->HasField("createdAt") ? [Data]() -> TOptional<int64>
                {
                    int64 v;
                    if (Data->TryGetNumberField("createdAt", v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<int64>();
                }() : TOptional<int64>());
    }

    TSharedPtr<FJsonObject> FSubscribe::ToJson() const
    {
        const TSharedPtr<FJsonObject> JsonRootObject = MakeShared<FJsonObject>();
        if (SubscribeIdValue.IsSet())
        {
            JsonRootObject->SetStringField("subscribeId", SubscribeIdValue.GetValue());
        }
        if (UserIdValue.IsSet())
        {
            JsonRootObject->SetStringField("userId", UserIdValue.GetValue());
        }
        if (RoomNameValue.IsSet())
        {
            JsonRootObject->SetStringField("roomName", RoomNameValue.GetValue());
        }
        if (NotificationTypesValue != nullptr && NotificationTypesValue.IsValid())
        {
            TArray<TSharedPtr<FJsonValue>> v;
            for (auto JsonObjectValue : *NotificationTypesValue)
            {
                v.Add(MakeShared<FJsonValueObject>(JsonObjectValue->ToJson()));
            }
            JsonRootObject->SetArrayField("notificationTypes", v);
        }
        if (CreatedAtValue.IsSet())
        {
            JsonRootObject->SetStringField("createdAt", FString::Printf(TEXT("%lld"), CreatedAtValue.GetValue()));
        }
        return JsonRootObject;
    }

    FString FSubscribe::TypeName = "Subscribe";
}