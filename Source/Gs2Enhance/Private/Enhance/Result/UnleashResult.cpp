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

#include "Enhance/Result/UnleashResult.h"

namespace Gs2::Enhance::Result
{
    FUnleashResult::FUnleashResult():
        ItemValue(nullptr),
        TransactionIdValue(TOptional<FString>()),
        StampSheetValue(TOptional<FString>()),
        StampSheetEncryptionKeyIdValue(TOptional<FString>()),
        AutoRunStampSheetValue(TOptional<bool>()),
        AtomicCommitValue(TOptional<bool>()),
        TransactionValue(TOptional<FString>()),
        TransactionResultValue(nullptr)
    {
    }

    FUnleashResult::FUnleashResult(
        const FUnleashResult& From
    ):
        ItemValue(From.ItemValue),
        TransactionIdValue(From.TransactionIdValue),
        StampSheetValue(From.StampSheetValue),
        StampSheetEncryptionKeyIdValue(From.StampSheetEncryptionKeyIdValue),
        AutoRunStampSheetValue(From.AutoRunStampSheetValue),
        AtomicCommitValue(From.AtomicCommitValue),
        TransactionValue(From.TransactionValue),
        TransactionResultValue(From.TransactionResultValue)
    {
    }

    TSharedPtr<FUnleashResult> FUnleashResult::WithItem(
        const TSharedPtr<Model::FUnleashRateModel> Item
    )
    {
        this->ItemValue = Item;
        return SharedThis(this);
    }

    TSharedPtr<FUnleashResult> FUnleashResult::WithTransactionId(
        const TOptional<FString> TransactionId
    )
    {
        this->TransactionIdValue = TransactionId;
        return SharedThis(this);
    }

    TSharedPtr<FUnleashResult> FUnleashResult::WithStampSheet(
        const TOptional<FString> StampSheet
    )
    {
        this->StampSheetValue = StampSheet;
        return SharedThis(this);
    }

    TSharedPtr<FUnleashResult> FUnleashResult::WithStampSheetEncryptionKeyId(
        const TOptional<FString> StampSheetEncryptionKeyId
    )
    {
        this->StampSheetEncryptionKeyIdValue = StampSheetEncryptionKeyId;
        return SharedThis(this);
    }

    TSharedPtr<FUnleashResult> FUnleashResult::WithAutoRunStampSheet(
        const TOptional<bool> AutoRunStampSheet
    )
    {
        this->AutoRunStampSheetValue = AutoRunStampSheet;
        return SharedThis(this);
    }

    TSharedPtr<FUnleashResult> FUnleashResult::WithAtomicCommit(
        const TOptional<bool> AtomicCommit
    )
    {
        this->AtomicCommitValue = AtomicCommit;
        return SharedThis(this);
    }

    TSharedPtr<FUnleashResult> FUnleashResult::WithTransaction(
        const TOptional<FString> Transaction
    )
    {
        this->TransactionValue = Transaction;
        return SharedThis(this);
    }

    TSharedPtr<FUnleashResult> FUnleashResult::WithTransactionResult(
        const TSharedPtr<Gs2::Core::Model::FTransactionResult> TransactionResult
    )
    {
        this->TransactionResultValue = TransactionResult;
        return SharedThis(this);
    }

    TSharedPtr<Model::FUnleashRateModel> FUnleashResult::GetItem() const
    {
        if (!ItemValue.IsValid())
        {
            return nullptr;
        }
        return ItemValue;
    }

    TOptional<FString> FUnleashResult::GetTransactionId() const
    {
        return TransactionIdValue;
    }

    TOptional<FString> FUnleashResult::GetStampSheet() const
    {
        return StampSheetValue;
    }

    TOptional<FString> FUnleashResult::GetStampSheetEncryptionKeyId() const
    {
        return StampSheetEncryptionKeyIdValue;
    }

    TOptional<bool> FUnleashResult::GetAutoRunStampSheet() const
    {
        return AutoRunStampSheetValue;
    }

    FString FUnleashResult::GetAutoRunStampSheetString() const
    {
        if (!AutoRunStampSheetValue.IsSet())
        {
            return FString("null");
        }
        return FString(AutoRunStampSheetValue.GetValue() ? "true" : "false");
    }

    TOptional<bool> FUnleashResult::GetAtomicCommit() const
    {
        return AtomicCommitValue;
    }

    FString FUnleashResult::GetAtomicCommitString() const
    {
        if (!AtomicCommitValue.IsSet())
        {
            return FString("null");
        }
        return FString(AtomicCommitValue.GetValue() ? "true" : "false");
    }

    TOptional<FString> FUnleashResult::GetTransaction() const
    {
        return TransactionValue;
    }

    TSharedPtr<Gs2::Core::Model::FTransactionResult> FUnleashResult::GetTransactionResult() const
    {
        if (!TransactionResultValue.IsValid())
        {
            return nullptr;
        }
        return TransactionResultValue;
    }

    TSharedPtr<FUnleashResult> FUnleashResult::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FUnleashResult>()
            ->WithItem(Data->HasField(ANSI_TO_TCHAR("item")) ? [Data]() -> Model::FUnleashRateModelPtr
                 {
                    if (Data->HasTypedField<EJson::Null>(ANSI_TO_TCHAR("item")))
                    {
                        return nullptr;
                    }
                    return Model::FUnleashRateModel::FromJson(Data->GetObjectField(ANSI_TO_TCHAR("item")));
                 }() : nullptr)
            ->WithTransactionId(Data->HasField(ANSI_TO_TCHAR("transactionId")) ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("transactionId"), v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithStampSheet(Data->HasField(ANSI_TO_TCHAR("stampSheet")) ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("stampSheet"), v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithStampSheetEncryptionKeyId(Data->HasField(ANSI_TO_TCHAR("stampSheetEncryptionKeyId")) ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("stampSheetEncryptionKeyId"), v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithAutoRunStampSheet(Data->HasField(ANSI_TO_TCHAR("autoRunStampSheet")) ? [Data]() -> TOptional<bool>
                {
                    bool v;
                    if (Data->TryGetBoolField(ANSI_TO_TCHAR("autoRunStampSheet"), v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<bool>();
                }() : TOptional<bool>())
            ->WithAtomicCommit(Data->HasField(ANSI_TO_TCHAR("atomicCommit")) ? [Data]() -> TOptional<bool>
                {
                    bool v;
                    if (Data->TryGetBoolField(ANSI_TO_TCHAR("atomicCommit"), v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<bool>();
                }() : TOptional<bool>())
            ->WithTransaction(Data->HasField(ANSI_TO_TCHAR("transaction")) ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("transaction"), v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithTransactionResult(Data->HasField(ANSI_TO_TCHAR("transactionResult")) ? [Data]() -> Gs2::Core::Model::FTransactionResultPtr
                 {
                    if (Data->HasTypedField<EJson::Null>(ANSI_TO_TCHAR("transactionResult")))
                    {
                        return nullptr;
                    }
                    return Gs2::Core::Model::FTransactionResult::FromJson(Data->GetObjectField(ANSI_TO_TCHAR("transactionResult")));
                 }() : nullptr);
    }

    TSharedPtr<FJsonObject> FUnleashResult::ToJson() const
    {
        const TSharedPtr<FJsonObject> JsonRootObject = MakeShared<FJsonObject>();
        if (ItemValue != nullptr && ItemValue.IsValid())
        {
            JsonRootObject->SetObjectField("item", ItemValue->ToJson());
        }
        if (TransactionIdValue.IsSet())
        {
            JsonRootObject->SetStringField("transactionId", TransactionIdValue.GetValue());
        }
        if (StampSheetValue.IsSet())
        {
            JsonRootObject->SetStringField("stampSheet", StampSheetValue.GetValue());
        }
        if (StampSheetEncryptionKeyIdValue.IsSet())
        {
            JsonRootObject->SetStringField("stampSheetEncryptionKeyId", StampSheetEncryptionKeyIdValue.GetValue());
        }
        if (AutoRunStampSheetValue.IsSet())
        {
            JsonRootObject->SetBoolField("autoRunStampSheet", AutoRunStampSheetValue.GetValue());
        }
        if (AtomicCommitValue.IsSet())
        {
            JsonRootObject->SetBoolField("atomicCommit", AtomicCommitValue.GetValue());
        }
        if (TransactionValue.IsSet())
        {
            JsonRootObject->SetStringField("transaction", TransactionValue.GetValue());
        }
        if (TransactionResultValue != nullptr && TransactionResultValue.IsValid())
        {
            JsonRootObject->SetObjectField("transactionResult", TransactionResultValue->ToJson());
        }
        return JsonRootObject;
    }
}