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

#include "Matchmaking/Model/CapacityOfRole.h"

namespace Gs2::Matchmaking::Model
{
    FCapacityOfRole::FCapacityOfRole():
        RoleNameValue(TOptional<FString>()),
        RoleAliasesValue(nullptr),
        CapacityValue(TOptional<int32>()),
        ParticipantsValue(nullptr)
    {
    }

    FCapacityOfRole::FCapacityOfRole(
        const FCapacityOfRole& From
    ):
        RoleNameValue(From.RoleNameValue),
        RoleAliasesValue(From.RoleAliasesValue),
        CapacityValue(From.CapacityValue),
        ParticipantsValue(From.ParticipantsValue)
    {
    }

    TSharedPtr<FCapacityOfRole> FCapacityOfRole::WithRoleName(
        const TOptional<FString> RoleName
    )
    {
        this->RoleNameValue = RoleName;
        return SharedThis(this);
    }

    TSharedPtr<FCapacityOfRole> FCapacityOfRole::WithRoleAliases(
        const TSharedPtr<TArray<FString>> RoleAliases
    )
    {
        this->RoleAliasesValue = RoleAliases;
        return SharedThis(this);
    }

    TSharedPtr<FCapacityOfRole> FCapacityOfRole::WithCapacity(
        const TOptional<int32> Capacity
    )
    {
        this->CapacityValue = Capacity;
        return SharedThis(this);
    }

    TSharedPtr<FCapacityOfRole> FCapacityOfRole::WithParticipants(
        const TSharedPtr<TArray<TSharedPtr<Model::FPlayer>>> Participants
    )
    {
        this->ParticipantsValue = Participants;
        return SharedThis(this);
    }
    TOptional<FString> FCapacityOfRole::GetRoleName() const
    {
        return RoleNameValue;
    }
    TSharedPtr<TArray<FString>> FCapacityOfRole::GetRoleAliases() const
    {
        return RoleAliasesValue;
    }
    TOptional<int32> FCapacityOfRole::GetCapacity() const
    {
        return CapacityValue;
    }

    FString FCapacityOfRole::GetCapacityString() const
    {
        if (!CapacityValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%d"), CapacityValue.GetValue());
    }
    TSharedPtr<TArray<TSharedPtr<Model::FPlayer>>> FCapacityOfRole::GetParticipants() const
    {
        return ParticipantsValue;
    }

    TSharedPtr<FCapacityOfRole> FCapacityOfRole::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FCapacityOfRole>()
            ->WithRoleName(Data->HasField("roleName") ? [Data]() -> TOptional<FString>
                {
                    FString v;
                    if (Data->TryGetStringField("roleName", v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithRoleAliases(Data->HasField("roleAliases") ? [Data]() -> TSharedPtr<TArray<FString>>
                {
                    auto v = MakeShared<TArray<FString>>();
                    if (!Data->HasTypedField<EJson::Null>("roleAliases") && Data->HasTypedField<EJson::Array>("roleAliases"))
                    {
                        for (auto JsonObjectValue : Data->GetArrayField("roleAliases"))
                        {
                            v->Add(JsonObjectValue->AsString());
                        }
                    }
                    return v;
                 }() : MakeShared<TArray<FString>>())
            ->WithCapacity(Data->HasField("capacity") ? [Data]() -> TOptional<int32>
                {
                    int32 v;
                    if (Data->TryGetNumberField("capacity", v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<int32>();
                }() : TOptional<int32>())
            ->WithParticipants(Data->HasField("participants") ? [Data]() -> TSharedPtr<TArray<Model::FPlayerPtr>>
                {
                    auto v = MakeShared<TArray<Model::FPlayerPtr>>();
                    if (!Data->HasTypedField<EJson::Null>("participants") && Data->HasTypedField<EJson::Array>("participants"))
                    {
                        for (auto JsonObjectValue : Data->GetArrayField("participants"))
                        {
                            v->Add(Model::FPlayer::FromJson(JsonObjectValue->AsObject()));
                        }
                    }
                    return v;
                 }() : MakeShared<TArray<Model::FPlayerPtr>>());
    }

    TSharedPtr<FJsonObject> FCapacityOfRole::ToJson() const
    {
        const TSharedPtr<FJsonObject> JsonRootObject = MakeShared<FJsonObject>();
        if (RoleNameValue.IsSet())
        {
            JsonRootObject->SetStringField("roleName", RoleNameValue.GetValue());
        }
        if (RoleAliasesValue != nullptr && RoleAliasesValue.IsValid())
        {
            TArray<TSharedPtr<FJsonValue>> v;
            for (auto JsonObjectValue : *RoleAliasesValue)
            {
                v.Add(MakeShared<FJsonValueString>(JsonObjectValue));
            }
            JsonRootObject->SetArrayField("roleAliases", v);
        }
        if (CapacityValue.IsSet())
        {
            JsonRootObject->SetNumberField("capacity", CapacityValue.GetValue());
        }
        if (ParticipantsValue != nullptr && ParticipantsValue.IsValid())
        {
            TArray<TSharedPtr<FJsonValue>> v;
            for (auto JsonObjectValue : *ParticipantsValue)
            {
                v.Add(MakeShared<FJsonValueObject>(JsonObjectValue->ToJson()));
            }
            JsonRootObject->SetArrayField("participants", v);
        }
        return JsonRootObject;
    }

    FString FCapacityOfRole::TypeName = "CapacityOfRole";
}