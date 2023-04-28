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

#include "EzGs2/Public/Matchmaking/Model/Gs2MatchmakingEzRatingModel.h"

namespace Gs2::UE5::Matchmaking::Model
{

    TSharedPtr<FEzRatingModel> FEzRatingModel::WithName(
        const TOptional<FString> Name
    )
    {
        this->NameValue = Name;
        return SharedThis(this);
    }

    TSharedPtr<FEzRatingModel> FEzRatingModel::WithMetadata(
        const TOptional<FString> Metadata
    )
    {
        this->MetadataValue = Metadata;
        return SharedThis(this);
    }

    TSharedPtr<FEzRatingModel> FEzRatingModel::WithVolatility(
        const TOptional<int32> Volatility
    )
    {
        this->VolatilityValue = Volatility;
        return SharedThis(this);
    }
    TOptional<FString> FEzRatingModel::GetName() const
    {
        return NameValue;
    }
    TOptional<FString> FEzRatingModel::GetMetadata() const
    {
        return MetadataValue;
    }
    TOptional<int32> FEzRatingModel::GetVolatility() const
    {
        return VolatilityValue;
    }

    FString FEzRatingModel::GetVolatilityString() const
    {
        if (!VolatilityValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%d"), VolatilityValue.GetValue());
    }

    Gs2::Matchmaking::Model::FRatingModelPtr FEzRatingModel::ToModel() const
    {
        return MakeShared<Gs2::Matchmaking::Model::FRatingModel>()
            ->WithName(NameValue)
            ->WithMetadata(MetadataValue)
            ->WithVolatility(VolatilityValue);
    }

    TSharedPtr<FEzRatingModel> FEzRatingModel::FromModel(const Gs2::Matchmaking::Model::FRatingModelPtr Model)
    {
        if (Model == nullptr)
        {
            return nullptr;
        }
        return MakeShared<FEzRatingModel>()
            ->WithName(Model->GetName())
            ->WithMetadata(Model->GetMetadata())
            ->WithVolatility(Model->GetVolatility());
    }
}