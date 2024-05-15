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

#include "Guild/Model/Gs2GuildEzGuildModel.h"

namespace Gs2::UE5::Guild::Model
{

    TSharedPtr<FEzGuildModel> FEzGuildModel::WithName(
        const TOptional<FString> Name
    )
    {
        this->NameValue = Name;
        return SharedThis(this);
    }

    TSharedPtr<FEzGuildModel> FEzGuildModel::WithMetadata(
        const TOptional<FString> Metadata
    )
    {
        this->MetadataValue = Metadata;
        return SharedThis(this);
    }

    TSharedPtr<FEzGuildModel> FEzGuildModel::WithDefaultMaximumMemberCount(
        const TOptional<int32> DefaultMaximumMemberCount
    )
    {
        this->DefaultMaximumMemberCountValue = DefaultMaximumMemberCount;
        return SharedThis(this);
    }

    TSharedPtr<FEzGuildModel> FEzGuildModel::WithMaximumMemberCount(
        const TOptional<int32> MaximumMemberCount
    )
    {
        this->MaximumMemberCountValue = MaximumMemberCount;
        return SharedThis(this);
    }

    TSharedPtr<FEzGuildModel> FEzGuildModel::WithRoles(
        const TSharedPtr<TArray<TSharedPtr<Gs2::UE5::Guild::Model::FEzRoleModel>>> Roles
    )
    {
        this->RolesValue = Roles;
        return SharedThis(this);
    }

    TSharedPtr<FEzGuildModel> FEzGuildModel::WithRejoinCoolTimeMinutes(
        const TOptional<int32> RejoinCoolTimeMinutes
    )
    {
        this->RejoinCoolTimeMinutesValue = RejoinCoolTimeMinutes;
        return SharedThis(this);
    }
    TOptional<FString> FEzGuildModel::GetName() const
    {
        return NameValue;
    }
    TOptional<FString> FEzGuildModel::GetMetadata() const
    {
        return MetadataValue;
    }
    TOptional<int32> FEzGuildModel::GetDefaultMaximumMemberCount() const
    {
        return DefaultMaximumMemberCountValue;
    }

    FString FEzGuildModel::GetDefaultMaximumMemberCountString() const
    {
        if (!DefaultMaximumMemberCountValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%d"), DefaultMaximumMemberCountValue.GetValue());
    }
    TOptional<int32> FEzGuildModel::GetMaximumMemberCount() const
    {
        return MaximumMemberCountValue;
    }

    FString FEzGuildModel::GetMaximumMemberCountString() const
    {
        if (!MaximumMemberCountValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%d"), MaximumMemberCountValue.GetValue());
    }
    TSharedPtr<TArray<TSharedPtr<Gs2::UE5::Guild::Model::FEzRoleModel>>> FEzGuildModel::GetRoles() const
    {
        return RolesValue;
    }
    TOptional<int32> FEzGuildModel::GetRejoinCoolTimeMinutes() const
    {
        return RejoinCoolTimeMinutesValue;
    }

    FString FEzGuildModel::GetRejoinCoolTimeMinutesString() const
    {
        if (!RejoinCoolTimeMinutesValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%d"), RejoinCoolTimeMinutesValue.GetValue());
    }

    Gs2::Guild::Model::FGuildModelPtr FEzGuildModel::ToModel() const
    {
        return MakeShared<Gs2::Guild::Model::FGuildModel>()
            ->WithName(NameValue)
            ->WithMetadata(MetadataValue)
            ->WithDefaultMaximumMemberCount(DefaultMaximumMemberCountValue)
            ->WithMaximumMemberCount(MaximumMemberCountValue)
            ->WithRoles([&]
                {
                    auto v = MakeShared<TArray<TSharedPtr<Gs2::Guild::Model::FRoleModel>>>();
                    if (RolesValue == nullptr)
                    {
                        return v;
                    }
                    for (auto v2 : *RolesValue)
                    {
                        v->Add(v2->ToModel());
                    }
                    return v;
                }()
            )
            ->WithRejoinCoolTimeMinutes(RejoinCoolTimeMinutesValue);
    }

    TSharedPtr<FEzGuildModel> FEzGuildModel::FromModel(const Gs2::Guild::Model::FGuildModelPtr Model)
    {
        if (Model == nullptr)
        {
            return nullptr;
        }
        return MakeShared<FEzGuildModel>()
            ->WithName(Model->GetName())
            ->WithMetadata(Model->GetMetadata())
            ->WithDefaultMaximumMemberCount(Model->GetDefaultMaximumMemberCount())
            ->WithMaximumMemberCount(Model->GetMaximumMemberCount())
            ->WithRoles([&]
                {
                    auto v = MakeShared<TArray<TSharedPtr<FEzRoleModel>>>();
                    if (Model->GetRoles() == nullptr)
                    {
                        return v;
                    }
                    for (auto v2 : *Model->GetRoles())
                    {
                        v->Add(FEzRoleModel::FromModel(v2));
                    }
                    return v;
                }()
            )
            ->WithRejoinCoolTimeMinutes(Model->GetRejoinCoolTimeMinutes());
    }
}