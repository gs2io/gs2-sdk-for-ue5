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

#include "Money2/Result/WithdrawByUserIdResult.h"

namespace Gs2::Money2::Result
{
    FWithdrawByUserIdResult::FWithdrawByUserIdResult():
        ItemValue(nullptr),
        WithdrawTransactionsValue(nullptr)
    {
    }

    FWithdrawByUserIdResult::FWithdrawByUserIdResult(
        const FWithdrawByUserIdResult& From
    ):
        ItemValue(From.ItemValue),
        WithdrawTransactionsValue(From.WithdrawTransactionsValue)
    {
    }

    TSharedPtr<FWithdrawByUserIdResult> FWithdrawByUserIdResult::WithItem(
        const TSharedPtr<Model::FWallet> Item
    )
    {
        this->ItemValue = Item;
        return SharedThis(this);
    }

    TSharedPtr<FWithdrawByUserIdResult> FWithdrawByUserIdResult::WithWithdrawTransactions(
        const TSharedPtr<TArray<TSharedPtr<Model::FDepositTransaction>>> WithdrawTransactions
    )
    {
        this->WithdrawTransactionsValue = WithdrawTransactions;
        return SharedThis(this);
    }

    TSharedPtr<Model::FWallet> FWithdrawByUserIdResult::GetItem() const
    {
        if (!ItemValue.IsValid())
        {
            return nullptr;
        }
        return ItemValue;
    }

    TSharedPtr<TArray<TSharedPtr<Model::FDepositTransaction>>> FWithdrawByUserIdResult::GetWithdrawTransactions() const
    {
        if (!WithdrawTransactionsValue.IsValid())
        {
            return nullptr;
        }
        return WithdrawTransactionsValue;
    }

    TSharedPtr<FWithdrawByUserIdResult> FWithdrawByUserIdResult::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FWithdrawByUserIdResult>()
            ->WithItem(Data->HasField(ANSI_TO_TCHAR("item")) ? [Data]() -> Model::FWalletPtr
                 {
                    if (Data->HasTypedField<EJson::Null>(ANSI_TO_TCHAR("item")))
                    {
                        return nullptr;
                    }
                    return Model::FWallet::FromJson(Data->GetObjectField(ANSI_TO_TCHAR("item")));
                 }() : nullptr)
            ->WithWithdrawTransactions(Data->HasField(ANSI_TO_TCHAR("withdrawTransactions")) ? [Data]() -> TSharedPtr<TArray<Model::FDepositTransactionPtr>>
                 {
                    auto v = MakeShared<TArray<Model::FDepositTransactionPtr>>();
                    if (!Data->HasTypedField<EJson::Null>(ANSI_TO_TCHAR("withdrawTransactions")) && Data->HasTypedField<EJson::Array>(ANSI_TO_TCHAR("withdrawTransactions")))
                    {
                        for (auto JsonObjectValue : Data->GetArrayField(ANSI_TO_TCHAR("withdrawTransactions")))
                        {
                            v->Add(Model::FDepositTransaction::FromJson(JsonObjectValue->AsObject()));
                        }
                    }
                    return v;
                 }() : MakeShared<TArray<Model::FDepositTransactionPtr>>());
    }

    TSharedPtr<FJsonObject> FWithdrawByUserIdResult::ToJson() const
    {
        const TSharedPtr<FJsonObject> JsonRootObject = MakeShared<FJsonObject>();
        if (ItemValue != nullptr && ItemValue.IsValid())
        {
            JsonRootObject->SetObjectField("item", ItemValue->ToJson());
        }
        if (WithdrawTransactionsValue != nullptr && WithdrawTransactionsValue.IsValid())
        {
            TArray<TSharedPtr<FJsonValue>> v;
            for (auto JsonObjectValue : *WithdrawTransactionsValue)
            {
                v.Add(MakeShared<FJsonValueObject>(JsonObjectValue->ToJson()));
            }
            JsonRootObject->SetArrayField("withdrawTransactions", v);
        }
        return JsonRootObject;
    }
}