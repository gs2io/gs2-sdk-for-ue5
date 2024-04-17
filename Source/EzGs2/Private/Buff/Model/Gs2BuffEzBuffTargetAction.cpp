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

#include "Buff/Model/Gs2BuffEzBuffTargetAction.h"

namespace Gs2::UE5::Buff::Model
{

    TSharedPtr<FEzBuffTargetAction> FEzBuffTargetAction::WithTargetActionName(
        const TOptional<FString> TargetActionName
    )
    {
        this->TargetActionNameValue = TargetActionName;
        return SharedThis(this);
    }

    TSharedPtr<FEzBuffTargetAction> FEzBuffTargetAction::WithTargetFieldName(
        const TOptional<FString> TargetFieldName
    )
    {
        this->TargetFieldNameValue = TargetFieldName;
        return SharedThis(this);
    }

    TSharedPtr<FEzBuffTargetAction> FEzBuffTargetAction::WithConditionGrns(
        const TSharedPtr<TArray<TSharedPtr<Gs2::UE5::Buff::Model::FEzBuffTargetGrn>>> ConditionGrns
    )
    {
        this->ConditionGrnsValue = ConditionGrns;
        return SharedThis(this);
    }

    TSharedPtr<FEzBuffTargetAction> FEzBuffTargetAction::WithRate(
        const TOptional<float> Rate
    )
    {
        this->RateValue = Rate;
        return SharedThis(this);
    }
    TOptional<FString> FEzBuffTargetAction::GetTargetActionName() const
    {
        return TargetActionNameValue;
    }
    TOptional<FString> FEzBuffTargetAction::GetTargetFieldName() const
    {
        return TargetFieldNameValue;
    }
    TSharedPtr<TArray<TSharedPtr<Gs2::UE5::Buff::Model::FEzBuffTargetGrn>>> FEzBuffTargetAction::GetConditionGrns() const
    {
        return ConditionGrnsValue;
    }
    TOptional<float> FEzBuffTargetAction::GetRate() const
    {
        return RateValue;
    }

    FString FEzBuffTargetAction::GetRateString() const
    {
        if (!RateValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%f"), RateValue.GetValue());
    }

    Gs2::Buff::Model::FBuffTargetActionPtr FEzBuffTargetAction::ToModel() const
    {
        return MakeShared<Gs2::Buff::Model::FBuffTargetAction>()
            ->WithTargetActionName(TargetActionNameValue)
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

    TSharedPtr<FEzBuffTargetAction> FEzBuffTargetAction::FromModel(const Gs2::Buff::Model::FBuffTargetActionPtr Model)
    {
        if (Model == nullptr)
        {
            return nullptr;
        }
        return MakeShared<FEzBuffTargetAction>()
            ->WithTargetActionName(Model->GetTargetActionName())
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