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

#include "Money2/Model/Gs2Money2EzWalletSummary.h"

namespace Gs2::UE5::Money2::Model
{

    TSharedPtr<FEzWalletSummary> FEzWalletSummary::WithPaid(
        const TOptional<int32> Paid
    )
    {
        this->PaidValue = Paid;
        return SharedThis(this);
    }

    TSharedPtr<FEzWalletSummary> FEzWalletSummary::WithFree(
        const TOptional<int32> Free
    )
    {
        this->FreeValue = Free;
        return SharedThis(this);
    }

    TSharedPtr<FEzWalletSummary> FEzWalletSummary::WithTotal(
        const TOptional<int32> Total
    )
    {
        this->TotalValue = Total;
        return SharedThis(this);
    }
    TOptional<int32> FEzWalletSummary::GetPaid() const
    {
        return PaidValue;
    }

    FString FEzWalletSummary::GetPaidString() const
    {
        if (!PaidValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%d"), PaidValue.GetValue());
    }
    TOptional<int32> FEzWalletSummary::GetFree() const
    {
        return FreeValue;
    }

    FString FEzWalletSummary::GetFreeString() const
    {
        if (!FreeValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%d"), FreeValue.GetValue());
    }
    TOptional<int32> FEzWalletSummary::GetTotal() const
    {
        return TotalValue;
    }

    FString FEzWalletSummary::GetTotalString() const
    {
        if (!TotalValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%d"), TotalValue.GetValue());
    }

    Gs2::Money2::Model::FWalletSummaryPtr FEzWalletSummary::ToModel() const
    {
        return MakeShared<Gs2::Money2::Model::FWalletSummary>()
            ->WithPaid(PaidValue)
            ->WithFree(FreeValue)
            ->WithTotal(TotalValue);
    }

    TSharedPtr<FEzWalletSummary> FEzWalletSummary::FromModel(const Gs2::Money2::Model::FWalletSummaryPtr Model)
    {
        if (Model == nullptr)
        {
            return nullptr;
        }
        return MakeShared<FEzWalletSummary>()
            ->WithPaid(Model->GetPaid())
            ->WithFree(Model->GetFree())
            ->WithTotal(Model->GetTotal());
    }
}