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

#include "Matchmaking/Model/Player.h"

namespace Gs2::Matchmaking::Model
{
    FPlayer::FPlayer():
        UserIdValue(TOptional<FString>()),
        AttributesValue(nullptr),
        RoleNameValue(TOptional<FString>()),
        DenyUserIdsValue(nullptr),
        CreatedAtValue(TOptional<int64>())
    {
    }

    FPlayer::FPlayer(
        const FPlayer& From
    ):
        UserIdValue(From.UserIdValue),
        AttributesValue(From.AttributesValue),
        RoleNameValue(From.RoleNameValue),
        DenyUserIdsValue(From.DenyUserIdsValue),
        CreatedAtValue(From.CreatedAtValue)
    {
    }

    TSharedPtr<FPlayer> FPlayer::WithUserId(
        const TOptional<FString> UserId
    )
    {
        this->UserIdValue = UserId;
        return SharedThis(this);
    }

    TSharedPtr<FPlayer> FPlayer::WithAttributes(
        const TSharedPtr<TArray<TSharedPtr<Model::FAttribute>>> Attributes
    )
    {
        this->AttributesValue = Attributes;
        return SharedThis(this);
    }

    TSharedPtr<FPlayer> FPlayer::WithRoleName(
        const TOptional<FString> RoleName
    )
    {
        this->RoleNameValue = RoleName;
        return SharedThis(this);
    }

    TSharedPtr<FPlayer> FPlayer::WithDenyUserIds(
        const TSharedPtr<TArray<FString>> DenyUserIds
    )
    {
        this->DenyUserIdsValue = DenyUserIds;
        return SharedThis(this);
    }

    TSharedPtr<FPlayer> FPlayer::WithCreatedAt(
        const TOptional<int64> CreatedAt
    )
    {
        this->CreatedAtValue = CreatedAt;
        return SharedThis(this);
    }
    TOptional<FString> FPlayer::GetUserId() const
    {
        return UserIdValue;
    }
    TSharedPtr<TArray<TSharedPtr<Model::FAttribute>>> FPlayer::GetAttributes() const
    {
        return AttributesValue;
    }
    TOptional<FString> FPlayer::GetRoleName() const
    {
        return RoleNameValue;
    }
    TSharedPtr<TArray<FString>> FPlayer::GetDenyUserIds() const
    {
        return DenyUserIdsValue;
    }
    TOptional<int64> FPlayer::GetCreatedAt() const
    {
        return CreatedAtValue;
    }

    FString FPlayer::GetCreatedAtString() const
    {
        if (!CreatedAtValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), CreatedAtValue.GetValue());
    }

    TSharedPtr<FPlayer> FPlayer::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FPlayer>()
            ->WithUserId(Data->HasField(ANSI_TO_TCHAR("userId")) ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("userId"), v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithAttributes(Data->HasField(ANSI_TO_TCHAR("attributes")) ? [Data]() -> TSharedPtr<TArray<Model::FAttributePtr>>
                {
                    auto v = MakeShared<TArray<Model::FAttributePtr>>();
                    if (!Data->HasTypedField<EJson::Null>(ANSI_TO_TCHAR("attributes")) && Data->HasTypedField<EJson::Array>(ANSI_TO_TCHAR("attributes")))
                    {
                        for (auto JsonObjectValue : Data->GetArrayField(ANSI_TO_TCHAR("attributes")))
                        {
                            v->Add(Model::FAttribute::FromJson(JsonObjectValue->AsObject()));
                        }
                    }
                    return v;
                 }() : MakeShared<TArray<Model::FAttributePtr>>())
            ->WithRoleName(Data->HasField(ANSI_TO_TCHAR("roleName")) ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("roleName"), v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithDenyUserIds(Data->HasField(ANSI_TO_TCHAR("denyUserIds")) ? [Data]() -> TSharedPtr<TArray<FString>>
                {
                    auto v = MakeShared<TArray<FString>>();
                    if (!Data->HasTypedField<EJson::Null>(ANSI_TO_TCHAR("denyUserIds")) && Data->HasTypedField<EJson::Array>(ANSI_TO_TCHAR("denyUserIds")))
                    {
                        for (auto JsonObjectValue : Data->GetArrayField(ANSI_TO_TCHAR("denyUserIds")))
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
                }() : TOptional<int64>());
    }

    TSharedPtr<FJsonObject> FPlayer::ToJson() const
    {
        const TSharedPtr<FJsonObject> JsonRootObject = MakeShared<FJsonObject>();
        if (UserIdValue.IsSet())
        {
            JsonRootObject->SetStringField("userId", UserIdValue.GetValue());
        }
        if (AttributesValue != nullptr && AttributesValue.IsValid())
        {
            TArray<TSharedPtr<FJsonValue>> v;
            for (auto JsonObjectValue : *AttributesValue)
            {
                v.Add(MakeShared<FJsonValueObject>(JsonObjectValue->ToJson()));
            }
            JsonRootObject->SetArrayField("attributes", v);
        }
        if (RoleNameValue.IsSet())
        {
            JsonRootObject->SetStringField("roleName", RoleNameValue.GetValue());
        }
        if (DenyUserIdsValue != nullptr && DenyUserIdsValue.IsValid())
        {
            TArray<TSharedPtr<FJsonValue>> v;
            for (auto JsonObjectValue : *DenyUserIdsValue)
            {
                v.Add(MakeShared<FJsonValueString>(JsonObjectValue));
            }
            JsonRootObject->SetArrayField("denyUserIds", v);
        }
        if (CreatedAtValue.IsSet())
        {
            JsonRootObject->SetStringField("createdAt", FString::Printf(TEXT("%lld"), CreatedAtValue.GetValue()));
        }
        return JsonRootObject;
    }

    FString FPlayer::TypeName = "Player";
}