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

#include "Matchmaking/Model/Gs2MatchmakingEzAttributeRange.h"

namespace Gs2::UE5::Matchmaking::Model
{

    TSharedPtr<FEzAttributeRange> FEzAttributeRange::WithName(
        const TOptional<FString> Name
    )
    {
        this->NameValue = Name;
        return SharedThis(this);
    }

    TSharedPtr<FEzAttributeRange> FEzAttributeRange::WithMin(
        const TOptional<int32> Min
    )
    {
        this->MinValue = Min;
        return SharedThis(this);
    }

    TSharedPtr<FEzAttributeRange> FEzAttributeRange::WithMax(
        const TOptional<int32> Max
    )
    {
        this->MaxValue = Max;
        return SharedThis(this);
    }
    TOptional<FString> FEzAttributeRange::GetName() const
    {
        return NameValue;
    }
    TOptional<int32> FEzAttributeRange::GetMin() const
    {
        return MinValue;
    }

    FString FEzAttributeRange::GetMinString() const
    {
        if (!MinValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%d"), MinValue.GetValue());
    }
    TOptional<int32> FEzAttributeRange::GetMax() const
    {
        return MaxValue;
    }

    FString FEzAttributeRange::GetMaxString() const
    {
        if (!MaxValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%d"), MaxValue.GetValue());
    }

    Gs2::Matchmaking::Model::FAttributeRangePtr FEzAttributeRange::ToModel() const
    {
        return MakeShared<Gs2::Matchmaking::Model::FAttributeRange>()
            ->WithName(NameValue)
            ->WithMin(MinValue)
            ->WithMax(MaxValue);
    }

    TSharedPtr<FEzAttributeRange> FEzAttributeRange::FromModel(const Gs2::Matchmaking::Model::FAttributeRangePtr Model)
    {
        if (Model == nullptr)
        {
            return nullptr;
        }
        return MakeShared<FEzAttributeRange>()
            ->WithName(Model->GetName())
            ->WithMin(Model->GetMin())
            ->WithMax(Model->GetMax());
    }
}