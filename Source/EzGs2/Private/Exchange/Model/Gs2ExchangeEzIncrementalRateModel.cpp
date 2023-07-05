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

#include "EzGs2/Public/Exchange/Model/Gs2ExchangeEzIncrementalRateModel.h"

namespace Gs2::UE5::Exchange::Model
{

    TSharedPtr<FEzIncrementalRateModel> FEzIncrementalRateModel::WithName(
        const TOptional<FString> Name
    )
    {
        this->NameValue = Name;
        return SharedThis(this);
    }

    TSharedPtr<FEzIncrementalRateModel> FEzIncrementalRateModel::WithMetadata(
        const TOptional<FString> Metadata
    )
    {
        this->MetadataValue = Metadata;
        return SharedThis(this);
    }

    TSharedPtr<FEzIncrementalRateModel> FEzIncrementalRateModel::WithCalculateType(
        const TOptional<FString> CalculateType
    )
    {
        this->CalculateTypeValue = CalculateType;
        return SharedThis(this);
    }

    TSharedPtr<FEzIncrementalRateModel> FEzIncrementalRateModel::WithConsumeAction(
        const TSharedPtr<Gs2::UE5::Exchange::Model::FEzConsumeAction> ConsumeAction
    )
    {
        this->ConsumeActionValue = ConsumeAction;
        return SharedThis(this);
    }

    TSharedPtr<FEzIncrementalRateModel> FEzIncrementalRateModel::WithBaseValue(
        const TOptional<int64> BaseValue
    )
    {
        this->BaseValueValue = BaseValue;
        return SharedThis(this);
    }

    TSharedPtr<FEzIncrementalRateModel> FEzIncrementalRateModel::WithCoefficientValue(
        const TOptional<int64> CoefficientValue
    )
    {
        this->CoefficientValueValue = CoefficientValue;
        return SharedThis(this);
    }

    TSharedPtr<FEzIncrementalRateModel> FEzIncrementalRateModel::WithExchangeCountId(
        const TOptional<FString> ExchangeCountId
    )
    {
        this->ExchangeCountIdValue = ExchangeCountId;
        return SharedThis(this);
    }

    TSharedPtr<FEzIncrementalRateModel> FEzIncrementalRateModel::WithAcquireActions(
        const TSharedPtr<TArray<TSharedPtr<Gs2::UE5::Exchange::Model::FEzAcquireAction>>> AcquireActions
    )
    {
        this->AcquireActionsValue = AcquireActions;
        return SharedThis(this);
    }
    TOptional<FString> FEzIncrementalRateModel::GetName() const
    {
        return NameValue;
    }
    TOptional<FString> FEzIncrementalRateModel::GetMetadata() const
    {
        return MetadataValue;
    }
    TOptional<FString> FEzIncrementalRateModel::GetCalculateType() const
    {
        return CalculateTypeValue;
    }
    TSharedPtr<Gs2::UE5::Exchange::Model::FEzConsumeAction> FEzIncrementalRateModel::GetConsumeAction() const
    {
        return ConsumeActionValue;
    }
    TOptional<int64> FEzIncrementalRateModel::GetBaseValue() const
    {
        return BaseValueValue;
    }

    FString FEzIncrementalRateModel::GetBaseValueString() const
    {
        if (!BaseValueValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), BaseValueValue.GetValue());
    }
    TOptional<int64> FEzIncrementalRateModel::GetCoefficientValue() const
    {
        return CoefficientValueValue;
    }

    FString FEzIncrementalRateModel::GetCoefficientValueString() const
    {
        if (!CoefficientValueValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), CoefficientValueValue.GetValue());
    }
    TOptional<FString> FEzIncrementalRateModel::GetExchangeCountId() const
    {
        return ExchangeCountIdValue;
    }
    TSharedPtr<TArray<TSharedPtr<Gs2::UE5::Exchange::Model::FEzAcquireAction>>> FEzIncrementalRateModel::GetAcquireActions() const
    {
        return AcquireActionsValue;
    }

    Gs2::Exchange::Model::FIncrementalRateModelPtr FEzIncrementalRateModel::ToModel() const
    {
        return MakeShared<Gs2::Exchange::Model::FIncrementalRateModel>()
            ->WithName(NameValue)
            ->WithMetadata(MetadataValue)
            ->WithCalculateType(CalculateTypeValue)
            ->WithConsumeAction(ConsumeActionValue == nullptr ? nullptr : ConsumeActionValue->ToModel())
            ->WithBaseValue(BaseValueValue)
            ->WithCoefficientValue(CoefficientValueValue)
            ->WithExchangeCountId(ExchangeCountIdValue)
            ->WithAcquireActions([&]
                {
                    auto v = MakeShared<TArray<TSharedPtr<Gs2::Exchange::Model::FAcquireAction>>>();
                    if (AcquireActionsValue == nullptr)
                    {
                        return v;
                    }
                    for (auto v2 : *AcquireActionsValue)
                    {
                        v->Add(v2->ToModel());
                    }
                    return v;
                }()
            );
    }

    TSharedPtr<FEzIncrementalRateModel> FEzIncrementalRateModel::FromModel(const Gs2::Exchange::Model::FIncrementalRateModelPtr Model)
    {
        if (Model == nullptr)
        {
            return nullptr;
        }
        return MakeShared<FEzIncrementalRateModel>()
            ->WithName(Model->GetName())
            ->WithMetadata(Model->GetMetadata())
            ->WithCalculateType(Model->GetCalculateType())
            ->WithConsumeAction(Model->GetConsumeAction() != nullptr ? Gs2::UE5::Exchange::Model::FEzConsumeAction::FromModel(Model->GetConsumeAction()) : nullptr)
            ->WithBaseValue(Model->GetBaseValue())
            ->WithCoefficientValue(Model->GetCoefficientValue())
            ->WithExchangeCountId(Model->GetExchangeCountId())
            ->WithAcquireActions([&]
                {
                    auto v = MakeShared<TArray<TSharedPtr<FEzAcquireAction>>>();
                    if (Model->GetAcquireActions() == nullptr)
                    {
                        return v;
                    }
                    for (auto v2 : *Model->GetAcquireActions())
                    {
                        v->Add(FEzAcquireAction::FromModel(v2));
                    }
                    return v;
                }()
            );
    }
}