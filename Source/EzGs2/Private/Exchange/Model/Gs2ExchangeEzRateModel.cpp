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

#include "EzGs2/Public/Exchange/Model/Gs2ExchangeEzRateModel.h"

namespace Gs2::UE5::Exchange::Model
{

    TSharedPtr<FEzRateModel> FEzRateModel::WithName(
        const TOptional<FString> Name
    )
    {
        this->NameValue = Name;
        return SharedThis(this);
    }

    TSharedPtr<FEzRateModel> FEzRateModel::WithMetadata(
        const TOptional<FString> Metadata
    )
    {
        this->MetadataValue = Metadata;
        return SharedThis(this);
    }

    TSharedPtr<FEzRateModel> FEzRateModel::WithTimingType(
        const TOptional<FString> TimingType
    )
    {
        this->TimingTypeValue = TimingType;
        return SharedThis(this);
    }

    TSharedPtr<FEzRateModel> FEzRateModel::WithLockTime(
        const TOptional<int32> LockTime
    )
    {
        this->LockTimeValue = LockTime;
        return SharedThis(this);
    }

    TSharedPtr<FEzRateModel> FEzRateModel::WithConsumeActions(
        const TSharedPtr<TArray<TSharedPtr<Gs2::UE5::Exchange::Model::FEzConsumeAction>>> ConsumeActions
    )
    {
        this->ConsumeActionsValue = ConsumeActions;
        return SharedThis(this);
    }

    TSharedPtr<FEzRateModel> FEzRateModel::WithAcquireActions(
        const TSharedPtr<TArray<TSharedPtr<Gs2::UE5::Exchange::Model::FEzAcquireAction>>> AcquireActions
    )
    {
        this->AcquireActionsValue = AcquireActions;
        return SharedThis(this);
    }
    TOptional<FString> FEzRateModel::GetName() const
    {
        return NameValue;
    }
    TOptional<FString> FEzRateModel::GetMetadata() const
    {
        return MetadataValue;
    }
    TOptional<FString> FEzRateModel::GetTimingType() const
    {
        return TimingTypeValue;
    }
    TOptional<int32> FEzRateModel::GetLockTime() const
    {
        return LockTimeValue;
    }

    FString FEzRateModel::GetLockTimeString() const
    {
        if (!LockTimeValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%d"), LockTimeValue.GetValue());
    }
    TSharedPtr<TArray<TSharedPtr<Gs2::UE5::Exchange::Model::FEzConsumeAction>>> FEzRateModel::GetConsumeActions() const
    {
        return ConsumeActionsValue;
    }
    TSharedPtr<TArray<TSharedPtr<Gs2::UE5::Exchange::Model::FEzAcquireAction>>> FEzRateModel::GetAcquireActions() const
    {
        return AcquireActionsValue;
    }

    Gs2::Exchange::Model::FRateModelPtr FEzRateModel::ToModel() const
    {
        return MakeShared<Gs2::Exchange::Model::FRateModel>()
            ->WithName(NameValue)
            ->WithMetadata(MetadataValue)
            ->WithTimingType(TimingTypeValue)
            ->WithLockTime(LockTimeValue)
            ->WithConsumeActions([&]
                {
                    auto v = MakeShared<TArray<TSharedPtr<Gs2::Exchange::Model::FConsumeAction>>>();
                    if (ConsumeActionsValue == nullptr)
                    {
                        return v;
                    }
                    for (auto v2 : *ConsumeActionsValue)
                    {
                        v->Add(v2->ToModel());
                    }
                    return v;
                }()
            )
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

    TSharedPtr<FEzRateModel> FEzRateModel::FromModel(const Gs2::Exchange::Model::FRateModelPtr Model)
    {
        if (Model == nullptr)
        {
            return nullptr;
        }
        return MakeShared<FEzRateModel>()
            ->WithName(Model->GetName())
            ->WithMetadata(Model->GetMetadata())
            ->WithTimingType(Model->GetTimingType())
            ->WithLockTime(Model->GetLockTime())
            ->WithConsumeActions([&]
                {
                    auto v = MakeShared<TArray<TSharedPtr<FEzConsumeAction>>>();
                    if (Model->GetConsumeActions() == nullptr)
                    {
                        return v;
                    }
                    for (auto v2 : *Model->GetConsumeActions())
                    {
                        v->Add(FEzConsumeAction::FromModel(v2));
                    }
                    return v;
                }()
            )
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