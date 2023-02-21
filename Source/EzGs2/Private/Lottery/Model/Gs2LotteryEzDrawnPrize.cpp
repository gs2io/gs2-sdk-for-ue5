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

#include "EzGs2/Public/Lottery/Model/Gs2LotteryEzDrawnPrize.h"

namespace Gs2::UE5::Lottery::Model
{

    TSharedPtr<FEzDrawnPrize> FEzDrawnPrize::WithPrizeId(
        const TOptional<FString> PrizeId
    )
    {
        this->PrizeIdValue = PrizeId;
        return SharedThis(this);
    }

    TSharedPtr<FEzDrawnPrize> FEzDrawnPrize::WithAcquireActions(
        const TSharedPtr<TArray<TSharedPtr<Gs2::UE5::Lottery::Model::FEzAcquireAction>>> AcquireActions
    )
    {
        this->AcquireActionsValue = AcquireActions;
        return SharedThis(this);
    }
    TOptional<FString> FEzDrawnPrize::GetPrizeId() const
    {
        return PrizeIdValue;
    }
    TSharedPtr<TArray<TSharedPtr<Gs2::UE5::Lottery::Model::FEzAcquireAction>>> FEzDrawnPrize::GetAcquireActions() const
    {
        return AcquireActionsValue;
    }

    Gs2::Lottery::Model::FDrawnPrizePtr FEzDrawnPrize::ToModel() const
    {
        return MakeShared<Gs2::Lottery::Model::FDrawnPrize>()
            ->WithPrizeId(PrizeIdValue)
            ->WithAcquireActions([&]
                {
                    auto v = MakeShared<TArray<TSharedPtr<Gs2::Lottery::Model::FAcquireAction>>>();
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

    TSharedPtr<FEzDrawnPrize> FEzDrawnPrize::FromModel(const Gs2::Lottery::Model::FDrawnPrizePtr Model)
    {
        if (Model == nullptr)
        {
            return nullptr;
        }
        return MakeShared<FEzDrawnPrize>()
            ->WithPrizeId(Model->GetPrizeId())
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