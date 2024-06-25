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

#include "Money2/Model/WalletSummary.h"

namespace Gs2::Money2::Model
{
    FWalletSummary::FWalletSummary():
        PaidValue(TOptional<int32>()),
        FreeValue(TOptional<int32>()),
        TotalValue(TOptional<int32>())
    {
    }

    FWalletSummary::FWalletSummary(
        const FWalletSummary& From
    ):
        PaidValue(From.PaidValue),
        FreeValue(From.FreeValue),
        TotalValue(From.TotalValue)
    {
    }

    TSharedPtr<FWalletSummary> FWalletSummary::WithPaid(
        const TOptional<int32> Paid
    )
    {
        this->PaidValue = Paid;
        return SharedThis(this);
    }

    TSharedPtr<FWalletSummary> FWalletSummary::WithFree(
        const TOptional<int32> Free
    )
    {
        this->FreeValue = Free;
        return SharedThis(this);
    }

    TSharedPtr<FWalletSummary> FWalletSummary::WithTotal(
        const TOptional<int32> Total
    )
    {
        this->TotalValue = Total;
        return SharedThis(this);
    }
    TOptional<int32> FWalletSummary::GetPaid() const
    {
        return PaidValue;
    }

    FString FWalletSummary::GetPaidString() const
    {
        if (!PaidValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%d"), PaidValue.GetValue());
    }
    TOptional<int32> FWalletSummary::GetFree() const
    {
        return FreeValue;
    }

    FString FWalletSummary::GetFreeString() const
    {
        if (!FreeValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%d"), FreeValue.GetValue());
    }
    TOptional<int32> FWalletSummary::GetTotal() const
    {
        return TotalValue;
    }

    FString FWalletSummary::GetTotalString() const
    {
        if (!TotalValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%d"), TotalValue.GetValue());
    }

    TSharedPtr<FWalletSummary> FWalletSummary::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FWalletSummary>()
            ->WithPaid(Data->HasField(ANSI_TO_TCHAR("paid")) ? [Data]() -> TOptional<int32>
                {
                    int32 v;
                    if (Data->TryGetNumberField(ANSI_TO_TCHAR("paid"), v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<int32>();
                }() : TOptional<int32>())
            ->WithFree(Data->HasField(ANSI_TO_TCHAR("free")) ? [Data]() -> TOptional<int32>
                {
                    int32 v;
                    if (Data->TryGetNumberField(ANSI_TO_TCHAR("free"), v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<int32>();
                }() : TOptional<int32>())
            ->WithTotal(Data->HasField(ANSI_TO_TCHAR("total")) ? [Data]() -> TOptional<int32>
                {
                    int32 v;
                    if (Data->TryGetNumberField(ANSI_TO_TCHAR("total"), v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<int32>();
                }() : TOptional<int32>());
    }

    TSharedPtr<FJsonObject> FWalletSummary::ToJson() const
    {
        const TSharedPtr<FJsonObject> JsonRootObject = MakeShared<FJsonObject>();
        if (PaidValue.IsSet())
        {
            JsonRootObject->SetNumberField("paid", PaidValue.GetValue());
        }
        if (FreeValue.IsSet())
        {
            JsonRootObject->SetNumberField("free", FreeValue.GetValue());
        }
        if (TotalValue.IsSet())
        {
            JsonRootObject->SetNumberField("total", TotalValue.GetValue());
        }
        return JsonRootObject;
    }

    FString FWalletSummary::TypeName = "WalletSummary";
}