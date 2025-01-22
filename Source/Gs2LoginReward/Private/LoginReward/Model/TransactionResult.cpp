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

#include "LoginReward/Model/TransactionResult.h"

namespace Gs2::LoginReward::Model
{
    FTransactionResult::FTransactionResult():
        TransactionIdValue(TOptional<FString>()),
        VerifyResultsValue(nullptr),
        ConsumeResultsValue(nullptr),
        AcquireResultsValue(nullptr)
    {
    }

    FTransactionResult::FTransactionResult(
        const FTransactionResult& From
    ):
        TransactionIdValue(From.TransactionIdValue),
        VerifyResultsValue(From.VerifyResultsValue),
        ConsumeResultsValue(From.ConsumeResultsValue),
        AcquireResultsValue(From.AcquireResultsValue)
    {
    }

    TSharedPtr<FTransactionResult> FTransactionResult::WithTransactionId(
        const TOptional<FString> TransactionId
    )
    {
        this->TransactionIdValue = TransactionId;
        return SharedThis(this);
    }

    TSharedPtr<FTransactionResult> FTransactionResult::WithVerifyResults(
        const TSharedPtr<TArray<TSharedPtr<Model::FVerifyActionResult>>> VerifyResults
    )
    {
        this->VerifyResultsValue = VerifyResults;
        return SharedThis(this);
    }

    TSharedPtr<FTransactionResult> FTransactionResult::WithConsumeResults(
        const TSharedPtr<TArray<TSharedPtr<Model::FConsumeActionResult>>> ConsumeResults
    )
    {
        this->ConsumeResultsValue = ConsumeResults;
        return SharedThis(this);
    }

    TSharedPtr<FTransactionResult> FTransactionResult::WithAcquireResults(
        const TSharedPtr<TArray<TSharedPtr<Model::FAcquireActionResult>>> AcquireResults
    )
    {
        this->AcquireResultsValue = AcquireResults;
        return SharedThis(this);
    }
    TOptional<FString> FTransactionResult::GetTransactionId() const
    {
        return TransactionIdValue;
    }
    TSharedPtr<TArray<TSharedPtr<Model::FVerifyActionResult>>> FTransactionResult::GetVerifyResults() const
    {
        return VerifyResultsValue;
    }
    TSharedPtr<TArray<TSharedPtr<Model::FConsumeActionResult>>> FTransactionResult::GetConsumeResults() const
    {
        return ConsumeResultsValue;
    }
    TSharedPtr<TArray<TSharedPtr<Model::FAcquireActionResult>>> FTransactionResult::GetAcquireResults() const
    {
        return AcquireResultsValue;
    }

    TSharedPtr<FTransactionResult> FTransactionResult::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FTransactionResult>()
            ->WithTransactionId(Data->HasField(ANSI_TO_TCHAR("transactionId")) ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("transactionId"), v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithVerifyResults(Data->HasField(ANSI_TO_TCHAR("verifyResults")) ? [Data]() -> TSharedPtr<TArray<Model::FVerifyActionResultPtr>>
                {
                    auto v = MakeShared<TArray<Model::FVerifyActionResultPtr>>();
                    if (!Data->HasTypedField<EJson::Null>(ANSI_TO_TCHAR("verifyResults")) && Data->HasTypedField<EJson::Array>(ANSI_TO_TCHAR("verifyResults")))
                    {
                        for (auto JsonObjectValue : Data->GetArrayField(ANSI_TO_TCHAR("verifyResults")))
                        {
                            v->Add(Model::FVerifyActionResult::FromJson(JsonObjectValue->AsObject()));
                        }
                    }
                    return v;
                 }() : MakeShared<TArray<Model::FVerifyActionResultPtr>>())
            ->WithConsumeResults(Data->HasField(ANSI_TO_TCHAR("consumeResults")) ? [Data]() -> TSharedPtr<TArray<Model::FConsumeActionResultPtr>>
                {
                    auto v = MakeShared<TArray<Model::FConsumeActionResultPtr>>();
                    if (!Data->HasTypedField<EJson::Null>(ANSI_TO_TCHAR("consumeResults")) && Data->HasTypedField<EJson::Array>(ANSI_TO_TCHAR("consumeResults")))
                    {
                        for (auto JsonObjectValue : Data->GetArrayField(ANSI_TO_TCHAR("consumeResults")))
                        {
                            v->Add(Model::FConsumeActionResult::FromJson(JsonObjectValue->AsObject()));
                        }
                    }
                    return v;
                 }() : MakeShared<TArray<Model::FConsumeActionResultPtr>>())
            ->WithAcquireResults(Data->HasField(ANSI_TO_TCHAR("acquireResults")) ? [Data]() -> TSharedPtr<TArray<Model::FAcquireActionResultPtr>>
                {
                    auto v = MakeShared<TArray<Model::FAcquireActionResultPtr>>();
                    if (!Data->HasTypedField<EJson::Null>(ANSI_TO_TCHAR("acquireResults")) && Data->HasTypedField<EJson::Array>(ANSI_TO_TCHAR("acquireResults")))
                    {
                        for (auto JsonObjectValue : Data->GetArrayField(ANSI_TO_TCHAR("acquireResults")))
                        {
                            v->Add(Model::FAcquireActionResult::FromJson(JsonObjectValue->AsObject()));
                        }
                    }
                    return v;
                 }() : MakeShared<TArray<Model::FAcquireActionResultPtr>>());
    }

    TSharedPtr<FJsonObject> FTransactionResult::ToJson() const
    {
        const TSharedPtr<FJsonObject> JsonRootObject = MakeShared<FJsonObject>();
        if (TransactionIdValue.IsSet())
        {
            JsonRootObject->SetStringField("transactionId", TransactionIdValue.GetValue());
        }
        if (VerifyResultsValue != nullptr && VerifyResultsValue.IsValid())
        {
            TArray<TSharedPtr<FJsonValue>> v;
            for (auto JsonObjectValue : *VerifyResultsValue)
            {
                v.Add(MakeShared<FJsonValueObject>(JsonObjectValue->ToJson()));
            }
            JsonRootObject->SetArrayField("verifyResults", v);
        }
        if (ConsumeResultsValue != nullptr && ConsumeResultsValue.IsValid())
        {
            TArray<TSharedPtr<FJsonValue>> v;
            for (auto JsonObjectValue : *ConsumeResultsValue)
            {
                v.Add(MakeShared<FJsonValueObject>(JsonObjectValue->ToJson()));
            }
            JsonRootObject->SetArrayField("consumeResults", v);
        }
        if (AcquireResultsValue != nullptr && AcquireResultsValue.IsValid())
        {
            TArray<TSharedPtr<FJsonValue>> v;
            for (auto JsonObjectValue : *AcquireResultsValue)
            {
                v.Add(MakeShared<FJsonValueObject>(JsonObjectValue->ToJson()));
            }
            JsonRootObject->SetArrayField("acquireResults", v);
        }
        return JsonRootObject;
    }

    FString FTransactionResult::TypeName = "TransactionResult";
}