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

#include "Guild/Model/Gs2GuildEzGuild.h"

namespace Gs2::UE5::Guild::Model
{

    TSharedPtr<FEzGuild> FEzGuild::WithGuildModelName(
        const TOptional<FString> GuildModelName
    )
    {
        this->GuildModelNameValue = GuildModelName;
        return SharedThis(this);
    }

    TSharedPtr<FEzGuild> FEzGuild::WithName(
        const TOptional<FString> Name
    )
    {
        this->NameValue = Name;
        return SharedThis(this);
    }

    TSharedPtr<FEzGuild> FEzGuild::WithDisplayName(
        const TOptional<FString> DisplayName
    )
    {
        this->DisplayNameValue = DisplayName;
        return SharedThis(this);
    }

    TSharedPtr<FEzGuild> FEzGuild::WithAttribute1(
        const TOptional<int32> Attribute1
    )
    {
        this->Attribute1Value = Attribute1;
        return SharedThis(this);
    }

    TSharedPtr<FEzGuild> FEzGuild::WithAttribute2(
        const TOptional<int32> Attribute2
    )
    {
        this->Attribute2Value = Attribute2;
        return SharedThis(this);
    }

    TSharedPtr<FEzGuild> FEzGuild::WithAttribute3(
        const TOptional<int32> Attribute3
    )
    {
        this->Attribute3Value = Attribute3;
        return SharedThis(this);
    }

    TSharedPtr<FEzGuild> FEzGuild::WithAttribute4(
        const TOptional<int32> Attribute4
    )
    {
        this->Attribute4Value = Attribute4;
        return SharedThis(this);
    }

    TSharedPtr<FEzGuild> FEzGuild::WithAttribute5(
        const TOptional<int32> Attribute5
    )
    {
        this->Attribute5Value = Attribute5;
        return SharedThis(this);
    }

    TSharedPtr<FEzGuild> FEzGuild::WithMetadata(
        const TOptional<FString> Metadata
    )
    {
        this->MetadataValue = Metadata;
        return SharedThis(this);
    }

    TSharedPtr<FEzGuild> FEzGuild::WithJoinPolicy(
        const TOptional<FString> JoinPolicy
    )
    {
        this->JoinPolicyValue = JoinPolicy;
        return SharedThis(this);
    }

    TSharedPtr<FEzGuild> FEzGuild::WithCustomRoles(
        const TSharedPtr<TArray<TSharedPtr<Gs2::UE5::Guild::Model::FEzRoleModel>>> CustomRoles
    )
    {
        this->CustomRolesValue = CustomRoles;
        return SharedThis(this);
    }

    TSharedPtr<FEzGuild> FEzGuild::WithMembers(
        const TSharedPtr<TArray<TSharedPtr<Gs2::UE5::Guild::Model::FEzMember>>> Members
    )
    {
        this->MembersValue = Members;
        return SharedThis(this);
    }
    TOptional<FString> FEzGuild::GetGuildModelName() const
    {
        return GuildModelNameValue;
    }
    TOptional<FString> FEzGuild::GetName() const
    {
        return NameValue;
    }
    TOptional<FString> FEzGuild::GetDisplayName() const
    {
        return DisplayNameValue;
    }
    TOptional<int32> FEzGuild::GetAttribute1() const
    {
        return Attribute1Value;
    }

    FString FEzGuild::GetAttribute1String() const
    {
        if (!Attribute1Value.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%d"), Attribute1Value.GetValue());
    }
    TOptional<int32> FEzGuild::GetAttribute2() const
    {
        return Attribute2Value;
    }

    FString FEzGuild::GetAttribute2String() const
    {
        if (!Attribute2Value.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%d"), Attribute2Value.GetValue());
    }
    TOptional<int32> FEzGuild::GetAttribute3() const
    {
        return Attribute3Value;
    }

    FString FEzGuild::GetAttribute3String() const
    {
        if (!Attribute3Value.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%d"), Attribute3Value.GetValue());
    }
    TOptional<int32> FEzGuild::GetAttribute4() const
    {
        return Attribute4Value;
    }

    FString FEzGuild::GetAttribute4String() const
    {
        if (!Attribute4Value.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%d"), Attribute4Value.GetValue());
    }
    TOptional<int32> FEzGuild::GetAttribute5() const
    {
        return Attribute5Value;
    }

    FString FEzGuild::GetAttribute5String() const
    {
        if (!Attribute5Value.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%d"), Attribute5Value.GetValue());
    }
    TOptional<FString> FEzGuild::GetMetadata() const
    {
        return MetadataValue;
    }
    TOptional<FString> FEzGuild::GetJoinPolicy() const
    {
        return JoinPolicyValue;
    }
    TSharedPtr<TArray<TSharedPtr<Gs2::UE5::Guild::Model::FEzRoleModel>>> FEzGuild::GetCustomRoles() const
    {
        return CustomRolesValue;
    }
    TSharedPtr<TArray<TSharedPtr<Gs2::UE5::Guild::Model::FEzMember>>> FEzGuild::GetMembers() const
    {
        return MembersValue;
    }

    Gs2::Guild::Model::FGuildPtr FEzGuild::ToModel() const
    {
        return MakeShared<Gs2::Guild::Model::FGuild>()
            ->WithGuildModelName(GuildModelNameValue)
            ->WithName(NameValue)
            ->WithDisplayName(DisplayNameValue)
            ->WithAttribute1(Attribute1Value)
            ->WithAttribute2(Attribute2Value)
            ->WithAttribute3(Attribute3Value)
            ->WithAttribute4(Attribute4Value)
            ->WithAttribute5(Attribute5Value)
            ->WithMetadata(MetadataValue)
            ->WithJoinPolicy(JoinPolicyValue)
            ->WithCustomRoles([&]
                {
                    auto v = MakeShared<TArray<TSharedPtr<Gs2::Guild::Model::FRoleModel>>>();
                    if (CustomRolesValue == nullptr)
                    {
                        return v;
                    }
                    for (auto v2 : *CustomRolesValue)
                    {
                        v->Add(v2->ToModel());
                    }
                    return v;
                }()
            )
            ->WithMembers([&]
                {
                    auto v = MakeShared<TArray<TSharedPtr<Gs2::Guild::Model::FMember>>>();
                    if (MembersValue == nullptr)
                    {
                        return v;
                    }
                    for (auto v2 : *MembersValue)
                    {
                        v->Add(v2->ToModel());
                    }
                    return v;
                }()
            );
    }

    TSharedPtr<FEzGuild> FEzGuild::FromModel(const Gs2::Guild::Model::FGuildPtr Model)
    {
        if (Model == nullptr)
        {
            return nullptr;
        }
        return MakeShared<FEzGuild>()
            ->WithGuildModelName(Model->GetGuildModelName())
            ->WithName(Model->GetName())
            ->WithDisplayName(Model->GetDisplayName())
            ->WithAttribute1(Model->GetAttribute1())
            ->WithAttribute2(Model->GetAttribute2())
            ->WithAttribute3(Model->GetAttribute3())
            ->WithAttribute4(Model->GetAttribute4())
            ->WithAttribute5(Model->GetAttribute5())
            ->WithMetadata(Model->GetMetadata())
            ->WithJoinPolicy(Model->GetJoinPolicy())
            ->WithCustomRoles([&]
                {
                    auto v = MakeShared<TArray<TSharedPtr<FEzRoleModel>>>();
                    if (Model->GetCustomRoles() == nullptr)
                    {
                        return v;
                    }
                    for (auto v2 : *Model->GetCustomRoles())
                    {
                        v->Add(FEzRoleModel::FromModel(v2));
                    }
                    return v;
                }()
            )
            ->WithMembers([&]
                {
                    auto v = MakeShared<TArray<TSharedPtr<FEzMember>>>();
                    if (Model->GetMembers() == nullptr)
                    {
                        return v;
                    }
                    for (auto v2 : *Model->GetMembers())
                    {
                        v->Add(FEzMember::FromModel(v2));
                    }
                    return v;
                }()
            );
    }
}