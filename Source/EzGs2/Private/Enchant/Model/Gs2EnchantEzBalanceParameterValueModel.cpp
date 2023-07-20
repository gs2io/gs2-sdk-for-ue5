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

#include "EzGs2/Public/Enchant/Model/Gs2EnchantEzBalanceParameterValueModel.h"

namespace Gs2::UE5::Enchant::Model
{

    TSharedPtr<FEzBalanceParameterValueModel> FEzBalanceParameterValueModel::WithName(
        const TOptional<FString> Name
    )
    {
        this->NameValue = Name;
        return SharedThis(this);
    }

    TSharedPtr<FEzBalanceParameterValueModel> FEzBalanceParameterValueModel::WithMetadata(
        const TOptional<FString> Metadata
    )
    {
        this->MetadataValue = Metadata;
        return SharedThis(this);
    }
    TOptional<FString> FEzBalanceParameterValueModel::GetName() const
    {
        return NameValue;
    }
    TOptional<FString> FEzBalanceParameterValueModel::GetMetadata() const
    {
        return MetadataValue;
    }

    Gs2::Enchant::Model::FBalanceParameterValueModelPtr FEzBalanceParameterValueModel::ToModel() const
    {
        return MakeShared<Gs2::Enchant::Model::FBalanceParameterValueModel>()
            ->WithName(NameValue)
            ->WithMetadata(MetadataValue);
    }

    TSharedPtr<FEzBalanceParameterValueModel> FEzBalanceParameterValueModel::FromModel(const Gs2::Enchant::Model::FBalanceParameterValueModelPtr Model)
    {
        if (Model == nullptr)
        {
            return nullptr;
        }
        return MakeShared<FEzBalanceParameterValueModel>()
            ->WithName(Model->GetName())
            ->WithMetadata(Model->GetMetadata());
    }
}