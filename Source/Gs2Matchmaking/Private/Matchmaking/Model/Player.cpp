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
        DenyUserIdsValue(nullptr)
    {
    }

    FPlayer::FPlayer(
        const FPlayer& From
    ):
        UserIdValue(From.UserIdValue),
        AttributesValue(From.AttributesValue),
        RoleNameValue(From.RoleNameValue),
        DenyUserIdsValue(From.DenyUserIdsValue)
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

    TSharedPtr<FPlayer> FPlayer::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FPlayer>()
            ->WithUserId(Data->HasField("userId") ? [Data]() -> TOptional<FString>
                {
                    FString v;
                    if (Data->TryGetStringField("userId", v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithAttributes(Data->HasField("attributes") ? [Data]() -> TSharedPtr<TArray<Model::FAttributePtr>>
                {
                    auto v = MakeShared<TArray<Model::FAttributePtr>>();
                    if (!Data->HasTypedField<EJson::Null>("attributes") && Data->HasTypedField<EJson::Array>("attributes"))
                    {
                        for (auto JsonObjectValue : Data->GetArrayField("attributes"))
                        {
                            v->Add(Model::FAttribute::FromJson(JsonObjectValue->AsObject()));
                        }
                    }
                    return v;
                 }() : nullptr)
            ->WithRoleName(Data->HasField("roleName") ? [Data]() -> TOptional<FString>
                {
                    FString v;
                    if (Data->TryGetStringField("roleName", v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithDenyUserIds(Data->HasField("denyUserIds") ? [Data]() -> TSharedPtr<TArray<FString>>
                {
                    auto v = MakeShared<TArray<FString>>();
                    if (!Data->HasTypedField<EJson::Null>("denyUserIds") && Data->HasTypedField<EJson::Array>("denyUserIds"))
                    {
                        for (auto JsonObjectValue : Data->GetArrayField("denyUserIds"))
                        {
                            v->Add(JsonObjectValue->AsString());
                        }
                    }
                    return v;
                 }() : nullptr);
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
        return JsonRootObject;
    }

    FString FPlayer::TypeName = "Player";
}