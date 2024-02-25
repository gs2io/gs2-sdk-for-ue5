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

#include "SeasonRating/Model/TierModel.h"

namespace Gs2::SeasonRating::Model
{
    FTierModel::FTierModel():
        MetadataValue(TOptional<FString>()),
        RaiseRankBonusValue(TOptional<int32>()),
        EntryFeeValue(TOptional<int32>()),
        MinimumChangePointValue(TOptional<int32>()),
        MaximumChangePointValue(TOptional<int32>())
    {
    }

    FTierModel::FTierModel(
        const FTierModel& From
    ):
        MetadataValue(From.MetadataValue),
        RaiseRankBonusValue(From.RaiseRankBonusValue),
        EntryFeeValue(From.EntryFeeValue),
        MinimumChangePointValue(From.MinimumChangePointValue),
        MaximumChangePointValue(From.MaximumChangePointValue)
    {
    }

    TSharedPtr<FTierModel> FTierModel::WithMetadata(
        const TOptional<FString> Metadata
    )
    {
        this->MetadataValue = Metadata;
        return SharedThis(this);
    }

    TSharedPtr<FTierModel> FTierModel::WithRaiseRankBonus(
        const TOptional<int32> RaiseRankBonus
    )
    {
        this->RaiseRankBonusValue = RaiseRankBonus;
        return SharedThis(this);
    }

    TSharedPtr<FTierModel> FTierModel::WithEntryFee(
        const TOptional<int32> EntryFee
    )
    {
        this->EntryFeeValue = EntryFee;
        return SharedThis(this);
    }

    TSharedPtr<FTierModel> FTierModel::WithMinimumChangePoint(
        const TOptional<int32> MinimumChangePoint
    )
    {
        this->MinimumChangePointValue = MinimumChangePoint;
        return SharedThis(this);
    }

    TSharedPtr<FTierModel> FTierModel::WithMaximumChangePoint(
        const TOptional<int32> MaximumChangePoint
    )
    {
        this->MaximumChangePointValue = MaximumChangePoint;
        return SharedThis(this);
    }
    TOptional<FString> FTierModel::GetMetadata() const
    {
        return MetadataValue;
    }
    TOptional<int32> FTierModel::GetRaiseRankBonus() const
    {
        return RaiseRankBonusValue;
    }

    FString FTierModel::GetRaiseRankBonusString() const
    {
        if (!RaiseRankBonusValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%d"), RaiseRankBonusValue.GetValue());
    }
    TOptional<int32> FTierModel::GetEntryFee() const
    {
        return EntryFeeValue;
    }

    FString FTierModel::GetEntryFeeString() const
    {
        if (!EntryFeeValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%d"), EntryFeeValue.GetValue());
    }
    TOptional<int32> FTierModel::GetMinimumChangePoint() const
    {
        return MinimumChangePointValue;
    }

    FString FTierModel::GetMinimumChangePointString() const
    {
        if (!MinimumChangePointValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%d"), MinimumChangePointValue.GetValue());
    }
    TOptional<int32> FTierModel::GetMaximumChangePoint() const
    {
        return MaximumChangePointValue;
    }

    FString FTierModel::GetMaximumChangePointString() const
    {
        if (!MaximumChangePointValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%d"), MaximumChangePointValue.GetValue());
    }

    TSharedPtr<FTierModel> FTierModel::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FTierModel>()
            ->WithMetadata(Data->HasField("metadata") ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField("metadata", v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithRaiseRankBonus(Data->HasField("raiseRankBonus") ? [Data]() -> TOptional<int32>
                {
                    int32 v;
                    if (Data->TryGetNumberField("raiseRankBonus", v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<int32>();
                }() : TOptional<int32>())
            ->WithEntryFee(Data->HasField("entryFee") ? [Data]() -> TOptional<int32>
                {
                    int32 v;
                    if (Data->TryGetNumberField("entryFee", v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<int32>();
                }() : TOptional<int32>())
            ->WithMinimumChangePoint(Data->HasField("minimumChangePoint") ? [Data]() -> TOptional<int32>
                {
                    int32 v;
                    if (Data->TryGetNumberField("minimumChangePoint", v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<int32>();
                }() : TOptional<int32>())
            ->WithMaximumChangePoint(Data->HasField("maximumChangePoint") ? [Data]() -> TOptional<int32>
                {
                    int32 v;
                    if (Data->TryGetNumberField("maximumChangePoint", v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<int32>();
                }() : TOptional<int32>());
    }

    TSharedPtr<FJsonObject> FTierModel::ToJson() const
    {
        const TSharedPtr<FJsonObject> JsonRootObject = MakeShared<FJsonObject>();
        if (MetadataValue.IsSet())
        {
            JsonRootObject->SetStringField("metadata", MetadataValue.GetValue());
        }
        if (RaiseRankBonusValue.IsSet())
        {
            JsonRootObject->SetNumberField("raiseRankBonus", RaiseRankBonusValue.GetValue());
        }
        if (EntryFeeValue.IsSet())
        {
            JsonRootObject->SetNumberField("entryFee", EntryFeeValue.GetValue());
        }
        if (MinimumChangePointValue.IsSet())
        {
            JsonRootObject->SetNumberField("minimumChangePoint", MinimumChangePointValue.GetValue());
        }
        if (MaximumChangePointValue.IsSet())
        {
            JsonRootObject->SetNumberField("maximumChangePoint", MaximumChangePointValue.GetValue());
        }
        return JsonRootObject;
    }

    FString FTierModel::TypeName = "TierModel";
}