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

#include "Money2/Model/WithdrawEvent.h"

namespace Gs2::Money2::Model
{
    FWithdrawEvent::FWithdrawEvent():
        SlotValue(TOptional<int32>()),
        WithdrawDetailsValue(nullptr),
        StatusValue(nullptr)
    {
    }

    FWithdrawEvent::FWithdrawEvent(
        const FWithdrawEvent& From
    ):
        SlotValue(From.SlotValue),
        WithdrawDetailsValue(From.WithdrawDetailsValue),
        StatusValue(From.StatusValue)
    {
    }

    TSharedPtr<FWithdrawEvent> FWithdrawEvent::WithSlot(
        const TOptional<int32> Slot
    )
    {
        this->SlotValue = Slot;
        return SharedThis(this);
    }

    TSharedPtr<FWithdrawEvent> FWithdrawEvent::WithWithdrawDetails(
        const TSharedPtr<TArray<TSharedPtr<Model::FDepositTransaction>>> WithdrawDetails
    )
    {
        this->WithdrawDetailsValue = WithdrawDetails;
        return SharedThis(this);
    }

    TSharedPtr<FWithdrawEvent> FWithdrawEvent::WithStatus(
        const TSharedPtr<FWalletSummary> Status
    )
    {
        this->StatusValue = Status;
        return SharedThis(this);
    }
    TOptional<int32> FWithdrawEvent::GetSlot() const
    {
        return SlotValue;
    }

    FString FWithdrawEvent::GetSlotString() const
    {
        if (!SlotValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%d"), SlotValue.GetValue());
    }
    TSharedPtr<TArray<TSharedPtr<Model::FDepositTransaction>>> FWithdrawEvent::GetWithdrawDetails() const
    {
        return WithdrawDetailsValue;
    }
    TSharedPtr<FWalletSummary> FWithdrawEvent::GetStatus() const
    {
        return StatusValue;
    }

    TSharedPtr<FWithdrawEvent> FWithdrawEvent::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FWithdrawEvent>()
            ->WithSlot(Data->HasField(ANSI_TO_TCHAR("slot")) ? [Data]() -> TOptional<int32>
                {
                    int32 v;
                    if (Data->TryGetNumberField(ANSI_TO_TCHAR("slot"), v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<int32>();
                }() : TOptional<int32>())
            ->WithWithdrawDetails(Data->HasField(ANSI_TO_TCHAR("withdrawDetails")) ? [Data]() -> TSharedPtr<TArray<Model::FDepositTransactionPtr>>
                {
                    auto v = MakeShared<TArray<Model::FDepositTransactionPtr>>();
                    if (!Data->HasTypedField<EJson::Null>(ANSI_TO_TCHAR("withdrawDetails")) && Data->HasTypedField<EJson::Array>(ANSI_TO_TCHAR("withdrawDetails")))
                    {
                        for (auto JsonObjectValue : Data->GetArrayField(ANSI_TO_TCHAR("withdrawDetails")))
                        {
                            v->Add(Model::FDepositTransaction::FromJson(JsonObjectValue->AsObject()));
                        }
                    }
                    return v;
                 }() : MakeShared<TArray<Model::FDepositTransactionPtr>>())
            ->WithStatus(Data->HasField(ANSI_TO_TCHAR("status")) ? [Data]() -> Model::FWalletSummaryPtr
                {
                    if (Data->HasTypedField<EJson::Null>(ANSI_TO_TCHAR("status")))
                    {
                        return nullptr;
                    }
                    return Model::FWalletSummary::FromJson(Data->GetObjectField(ANSI_TO_TCHAR("status")));
                 }() : nullptr);
    }

    TSharedPtr<FJsonObject> FWithdrawEvent::ToJson() const
    {
        const TSharedPtr<FJsonObject> JsonRootObject = MakeShared<FJsonObject>();
        if (SlotValue.IsSet())
        {
            JsonRootObject->SetNumberField("slot", SlotValue.GetValue());
        }
        if (WithdrawDetailsValue != nullptr && WithdrawDetailsValue.IsValid())
        {
            TArray<TSharedPtr<FJsonValue>> v;
            for (auto JsonObjectValue : *WithdrawDetailsValue)
            {
                v.Add(MakeShared<FJsonValueObject>(JsonObjectValue->ToJson()));
            }
            JsonRootObject->SetArrayField("withdrawDetails", v);
        }
        if (StatusValue != nullptr && StatusValue.IsValid())
        {
            JsonRootObject->SetObjectField("status", StatusValue->ToJson());
        }
        return JsonRootObject;
    }

    FString FWithdrawEvent::TypeName = "WithdrawEvent";
}