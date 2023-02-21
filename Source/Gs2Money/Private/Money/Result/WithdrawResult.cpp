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

#include "Money/Result/WithdrawResult.h"

namespace Gs2::Money::Result
{
    FWithdrawResult::FWithdrawResult():
        ItemValue(nullptr),
        PriceValue(TOptional<float>())
    {
    }

    FWithdrawResult::FWithdrawResult(
        const FWithdrawResult& From
    ):
        ItemValue(From.ItemValue),
        PriceValue(From.PriceValue)
    {
    }

    TSharedPtr<FWithdrawResult> FWithdrawResult::WithItem(
        const TSharedPtr<Model::FWallet> Item
    )
    {
        this->ItemValue = Item;
        return SharedThis(this);
    }

    TSharedPtr<FWithdrawResult> FWithdrawResult::WithPrice(
        const TOptional<float> Price
    )
    {
        this->PriceValue = Price;
        return SharedThis(this);
    }

    TSharedPtr<Model::FWallet> FWithdrawResult::GetItem() const
    {
        if (!ItemValue.IsValid())
        {
            return nullptr;
        }
        return ItemValue;
    }

    TOptional<float> FWithdrawResult::GetPrice() const
    {
        return PriceValue;
    }

    FString FWithdrawResult::GetPriceString() const
    {
        if (!PriceValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%f"), PriceValue.GetValue());
    }

    TSharedPtr<FWithdrawResult> FWithdrawResult::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FWithdrawResult>()
            ->WithItem(Data->HasField("item") ? [Data]() -> Model::FWalletPtr
                 {
                    if (Data->HasTypedField<EJson::Null>("item"))
                    {
                        return nullptr;
                    }
                    return Model::FWallet::FromJson(Data->GetObjectField("item"));
                 }() : nullptr)
            ->WithPrice(Data->HasField("price") ? [Data]() -> TOptional<float>
                {
                    float v;
                    if (Data->TryGetNumberField("price", v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<float>();
                }() : TOptional<float>());
    }

    TSharedPtr<FJsonObject> FWithdrawResult::ToJson() const
    {
        const TSharedPtr<FJsonObject> JsonRootObject = MakeShared<FJsonObject>();
        if (ItemValue != nullptr && ItemValue.IsValid())
        {
            JsonRootObject->SetObjectField("item", ItemValue->ToJson());
        }
        if (PriceValue.IsSet())
        {
            JsonRootObject->SetNumberField("price", PriceValue.GetValue());
        }
        return JsonRootObject;
    }
}