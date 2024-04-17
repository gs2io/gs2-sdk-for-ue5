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

#include "Buff/Model/Gs2BuffEzBuffTargetModel.h"

namespace Gs2::UE5::Buff::Model
{

    TSharedPtr<FEzBuffTargetModel> FEzBuffTargetModel::WithTargetModelName(
        const TOptional<FString> TargetModelName
    )
    {
        this->TargetModelNameValue = TargetModelName;
        return SharedThis(this);
    }

    TSharedPtr<FEzBuffTargetModel> FEzBuffTargetModel::WithTargetFieldName(
        const TOptional<FString> TargetFieldName
    )
    {
        this->TargetFieldNameValue = TargetFieldName;
        return SharedThis(this);
    }

    TSharedPtr<FEzBuffTargetModel> FEzBuffTargetModel::WithConditionGrns(
        const TSharedPtr<TArray<TSharedPtr<Gs2::UE5::Buff::Model::FEzBuffTargetGrn>>> ConditionGrns
    )
    {
        this->ConditionGrnsValue = ConditionGrns;
        return SharedThis(this);
    }

    TSharedPtr<FEzBuffTargetModel> FEzBuffTargetModel::WithRate(
        const TOptional<float> Rate
    )
    {
        this->RateValue = Rate;
        return SharedThis(this);
    }
    TOptional<FString> FEzBuffTargetModel::GetTargetModelName() const
    {
        return TargetModelNameValue;
    }
    TOptional<FString> FEzBuffTargetModel::GetTargetFieldName() const
    {
        return TargetFieldNameValue;
    }
    TSharedPtr<TArray<TSharedPtr<Gs2::UE5::Buff::Model::FEzBuffTargetGrn>>> FEzBuffTargetModel::GetConditionGrns() const
    {
        return ConditionGrnsValue;
    }
    TOptional<float> FEzBuffTargetModel::GetRate() const
    {
        return RateValue;
    }

    FString FEzBuffTargetModel::GetRateString() const
    {
        if (!RateValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%f"), RateValue.GetValue());
    }

    Gs2::Buff::Model::FBuffTargetModelPtr FEzBuffTargetModel::ToModel() const
    {
        return MakeShared<Gs2::Buff::Model::FBuffTargetModel>()
            ->WithTargetModelName(TargetModelNameValue)
            ->WithTargetFieldName(TargetFieldNameValue)
            ->WithConditionGrns([&]
                {
                    auto v = MakeShared<TArray<TSharedPtr<Gs2::Buff::Model::FBuffTargetGrn>>>();
                    if (ConditionGrnsValue == nullptr)
                    {
                        return v;
                    }
                    for (auto v2 : *ConditionGrnsValue)
                    {
                        v->Add(v2->ToModel());
                    }
                    return v;
                }()
            )
            ->WithRate(RateValue);
    }

    TSharedPtr<FEzBuffTargetModel> FEzBuffTargetModel::FromModel(const Gs2::Buff::Model::FBuffTargetModelPtr Model)
    {
        if (Model == nullptr)
        {
            return nullptr;
        }
        return MakeShared<FEzBuffTargetModel>()
            ->WithTargetModelName(Model->GetTargetModelName())
            ->WithTargetFieldName(Model->GetTargetFieldName())
            ->WithConditionGrns([&]
                {
                    auto v = MakeShared<TArray<TSharedPtr<FEzBuffTargetGrn>>>();
                    if (Model->GetConditionGrns() == nullptr)
                    {
                        return v;
                    }
                    for (auto v2 : *Model->GetConditionGrns())
                    {
                        v->Add(FEzBuffTargetGrn::FromModel(v2));
                    }
                    return v;
                }()
            )
            ->WithRate(Model->GetRate());
    }
}