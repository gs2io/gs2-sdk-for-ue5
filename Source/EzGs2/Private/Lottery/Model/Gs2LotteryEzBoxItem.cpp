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

#include "EzGs2/Public/Lottery/Model/Gs2LotteryEzBoxItem.h"

namespace Gs2::UE5::Lottery::Model
{

    TSharedPtr<FEzBoxItem> FEzBoxItem::WithAcquireActions(
        const TSharedPtr<TArray<TSharedPtr<Gs2::UE5::Lottery::Model::FEzAcquireAction>>> AcquireActions
    )
    {
        this->AcquireActionsValue = AcquireActions;
        return SharedThis(this);
    }

    TSharedPtr<FEzBoxItem> FEzBoxItem::WithRemaining(
        const TOptional<int32> Remaining
    )
    {
        this->RemainingValue = Remaining;
        return SharedThis(this);
    }

    TSharedPtr<FEzBoxItem> FEzBoxItem::WithInitial(
        const TOptional<int32> Initial
    )
    {
        this->InitialValue = Initial;
        return SharedThis(this);
    }
    TSharedPtr<TArray<TSharedPtr<Gs2::UE5::Lottery::Model::FEzAcquireAction>>> FEzBoxItem::GetAcquireActions() const
    {
        return AcquireActionsValue;
    }
    TOptional<int32> FEzBoxItem::GetRemaining() const
    {
        return RemainingValue;
    }

    FString FEzBoxItem::GetRemainingString() const
    {
        if (!RemainingValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%d"), RemainingValue.GetValue());
    }
    TOptional<int32> FEzBoxItem::GetInitial() const
    {
        return InitialValue;
    }

    FString FEzBoxItem::GetInitialString() const
    {
        if (!InitialValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%d"), InitialValue.GetValue());
    }

    Gs2::Lottery::Model::FBoxItemPtr FEzBoxItem::ToModel() const
    {
        return MakeShared<Gs2::Lottery::Model::FBoxItem>()
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
            )
            ->WithRemaining(RemainingValue)
            ->WithInitial(InitialValue);
    }

    TSharedPtr<FEzBoxItem> FEzBoxItem::FromModel(const Gs2::Lottery::Model::FBoxItemPtr Model)
    {
        if (Model == nullptr)
        {
            return nullptr;
        }
        return MakeShared<FEzBoxItem>()
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
            )
            ->WithRemaining(Model->GetRemaining())
            ->WithInitial(Model->GetInitial());
    }
}