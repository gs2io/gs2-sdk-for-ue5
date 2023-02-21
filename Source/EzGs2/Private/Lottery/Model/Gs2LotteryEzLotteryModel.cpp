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

#include "EzGs2/Public/Lottery/Model/Gs2LotteryEzLotteryModel.h"

namespace Gs2::UE5::Lottery::Model
{

    TSharedPtr<FEzLotteryModel> FEzLotteryModel::WithName(
        const TOptional<FString> Name
    )
    {
        this->NameValue = Name;
        return SharedThis(this);
    }

    TSharedPtr<FEzLotteryModel> FEzLotteryModel::WithMetadata(
        const TOptional<FString> Metadata
    )
    {
        this->MetadataValue = Metadata;
        return SharedThis(this);
    }

    TSharedPtr<FEzLotteryModel> FEzLotteryModel::WithMode(
        const TOptional<FString> Mode
    )
    {
        this->ModeValue = Mode;
        return SharedThis(this);
    }

    TSharedPtr<FEzLotteryModel> FEzLotteryModel::WithPrizeTableName(
        const TOptional<FString> PrizeTableName
    )
    {
        this->PrizeTableNameValue = PrizeTableName;
        return SharedThis(this);
    }
    TOptional<FString> FEzLotteryModel::GetName() const
    {
        return NameValue;
    }
    TOptional<FString> FEzLotteryModel::GetMetadata() const
    {
        return MetadataValue;
    }
    TOptional<FString> FEzLotteryModel::GetMode() const
    {
        return ModeValue;
    }
    TOptional<FString> FEzLotteryModel::GetPrizeTableName() const
    {
        return PrizeTableNameValue;
    }

    Gs2::Lottery::Model::FLotteryModelPtr FEzLotteryModel::ToModel() const
    {
        return MakeShared<Gs2::Lottery::Model::FLotteryModel>()
            ->WithName(NameValue)
            ->WithMetadata(MetadataValue)
            ->WithMode(ModeValue)
            ->WithPrizeTableName(PrizeTableNameValue);
    }

    TSharedPtr<FEzLotteryModel> FEzLotteryModel::FromModel(const Gs2::Lottery::Model::FLotteryModelPtr Model)
    {
        if (Model == nullptr)
        {
            return nullptr;
        }
        return MakeShared<FEzLotteryModel>()
            ->WithName(Model->GetName())
            ->WithMetadata(Model->GetMetadata())
            ->WithMode(Model->GetMode())
            ->WithPrizeTableName(Model->GetPrizeTableName());
    }
}