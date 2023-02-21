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

#include "EzGs2/Public/Matchmaking/Model/Gs2MatchmakingEzGathering.h"

namespace Gs2::UE5::Matchmaking::Model
{

    TSharedPtr<FEzGathering> FEzGathering::WithGatheringId(
        const TOptional<FString> GatheringId
    )
    {
        this->GatheringIdValue = GatheringId;
        return SharedThis(this);
    }

    TSharedPtr<FEzGathering> FEzGathering::WithName(
        const TOptional<FString> Name
    )
    {
        this->NameValue = Name;
        return SharedThis(this);
    }

    TSharedPtr<FEzGathering> FEzGathering::WithAttributeRanges(
        const TSharedPtr<TArray<TSharedPtr<Gs2::UE5::Matchmaking::Model::FEzAttributeRange>>> AttributeRanges
    )
    {
        this->AttributeRangesValue = AttributeRanges;
        return SharedThis(this);
    }

    TSharedPtr<FEzGathering> FEzGathering::WithCapacityOfRoles(
        const TSharedPtr<TArray<TSharedPtr<Gs2::UE5::Matchmaking::Model::FEzCapacityOfRole>>> CapacityOfRoles
    )
    {
        this->CapacityOfRolesValue = CapacityOfRoles;
        return SharedThis(this);
    }

    TSharedPtr<FEzGathering> FEzGathering::WithAllowUserIds(
        const TSharedPtr<TArray<FString>> AllowUserIds
    )
    {
        this->AllowUserIdsValue = AllowUserIds;
        return SharedThis(this);
    }

    TSharedPtr<FEzGathering> FEzGathering::WithMetadata(
        const TOptional<FString> Metadata
    )
    {
        this->MetadataValue = Metadata;
        return SharedThis(this);
    }

    TSharedPtr<FEzGathering> FEzGathering::WithExpiresAt(
        const TOptional<int64> ExpiresAt
    )
    {
        this->ExpiresAtValue = ExpiresAt;
        return SharedThis(this);
    }

    TSharedPtr<FEzGathering> FEzGathering::WithCreatedAt(
        const TOptional<int64> CreatedAt
    )
    {
        this->CreatedAtValue = CreatedAt;
        return SharedThis(this);
    }

    TSharedPtr<FEzGathering> FEzGathering::WithUpdatedAt(
        const TOptional<int64> UpdatedAt
    )
    {
        this->UpdatedAtValue = UpdatedAt;
        return SharedThis(this);
    }
    TOptional<FString> FEzGathering::GetGatheringId() const
    {
        return GatheringIdValue;
    }
    TOptional<FString> FEzGathering::GetName() const
    {
        return NameValue;
    }
    TSharedPtr<TArray<TSharedPtr<Gs2::UE5::Matchmaking::Model::FEzAttributeRange>>> FEzGathering::GetAttributeRanges() const
    {
        return AttributeRangesValue;
    }
    TSharedPtr<TArray<TSharedPtr<Gs2::UE5::Matchmaking::Model::FEzCapacityOfRole>>> FEzGathering::GetCapacityOfRoles() const
    {
        return CapacityOfRolesValue;
    }
    TSharedPtr<TArray<FString>> FEzGathering::GetAllowUserIds() const
    {
        return AllowUserIdsValue;
    }
    TOptional<FString> FEzGathering::GetMetadata() const
    {
        return MetadataValue;
    }
    TOptional<int64> FEzGathering::GetExpiresAt() const
    {
        return ExpiresAtValue;
    }

    FString FEzGathering::GetExpiresAtString() const
    {
        if (!ExpiresAtValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), ExpiresAtValue.GetValue());
    }
    TOptional<int64> FEzGathering::GetCreatedAt() const
    {
        return CreatedAtValue;
    }

    FString FEzGathering::GetCreatedAtString() const
    {
        if (!CreatedAtValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), CreatedAtValue.GetValue());
    }
    TOptional<int64> FEzGathering::GetUpdatedAt() const
    {
        return UpdatedAtValue;
    }

    FString FEzGathering::GetUpdatedAtString() const
    {
        if (!UpdatedAtValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), UpdatedAtValue.GetValue());
    }

    Gs2::Matchmaking::Model::FGatheringPtr FEzGathering::ToModel() const
    {
        return MakeShared<Gs2::Matchmaking::Model::FGathering>()
            ->WithGatheringId(GatheringIdValue)
            ->WithName(NameValue)
            ->WithAttributeRanges([&]
                {
                    auto v = MakeShared<TArray<TSharedPtr<Gs2::Matchmaking::Model::FAttributeRange>>>();
                    if (AttributeRangesValue == nullptr)
                    {
                        return v;
                    }
                    for (auto v2 : *AttributeRangesValue)
                    {
                        v->Add(v2->ToModel());
                    }
                    return v;
                }()
            )
            ->WithCapacityOfRoles([&]
                {
                    auto v = MakeShared<TArray<TSharedPtr<Gs2::Matchmaking::Model::FCapacityOfRole>>>();
                    if (CapacityOfRolesValue == nullptr)
                    {
                        return v;
                    }
                    for (auto v2 : *CapacityOfRolesValue)
                    {
                        v->Add(v2->ToModel());
                    }
                    return v;
                }()
            )
            ->WithAllowUserIds(AllowUserIdsValue)
            ->WithMetadata(MetadataValue)
            ->WithExpiresAt(ExpiresAtValue)
            ->WithCreatedAt(CreatedAtValue)
            ->WithUpdatedAt(UpdatedAtValue);
    }

    TSharedPtr<FEzGathering> FEzGathering::FromModel(const Gs2::Matchmaking::Model::FGatheringPtr Model)
    {
        if (Model == nullptr)
        {
            return nullptr;
        }
        return MakeShared<FEzGathering>()
            ->WithGatheringId(Model->GetGatheringId())
            ->WithName(Model->GetName())
            ->WithAttributeRanges([&]
                {
                    auto v = MakeShared<TArray<TSharedPtr<FEzAttributeRange>>>();
                    if (Model->GetAttributeRanges() == nullptr)
                    {
                        return v;
                    }
                    for (auto v2 : *Model->GetAttributeRanges())
                    {
                        v->Add(FEzAttributeRange::FromModel(v2));
                    }
                    return v;
                }()
            )
            ->WithCapacityOfRoles([&]
                {
                    auto v = MakeShared<TArray<TSharedPtr<FEzCapacityOfRole>>>();
                    if (Model->GetCapacityOfRoles() == nullptr)
                    {
                        return v;
                    }
                    for (auto v2 : *Model->GetCapacityOfRoles())
                    {
                        v->Add(FEzCapacityOfRole::FromModel(v2));
                    }
                    return v;
                }()
            )
            ->WithAllowUserIds(Model->GetAllowUserIds())
            ->WithMetadata(Model->GetMetadata())
            ->WithExpiresAt(Model->GetExpiresAt())
            ->WithCreatedAt(Model->GetCreatedAt())
            ->WithUpdatedAt(Model->GetUpdatedAt());
    }
}