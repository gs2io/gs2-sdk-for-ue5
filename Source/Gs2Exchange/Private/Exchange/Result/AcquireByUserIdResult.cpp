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

#include "Exchange/Result/AcquireByUserIdResult.h"

namespace Gs2::Exchange::Result
{
    FAcquireByUserIdResult::FAcquireByUserIdResult():
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

    FAcquireByUserIdResult::FAcquireByUserIdResult(
        const FAcquireByUserIdResult& From
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

    TSharedPtr<FAcquireByUserIdResult> FAcquireByUserIdResult::WithItem(
        const TSharedPtr<Model::FAwait> Item
    )
    {
        this->ItemValue = Item;
        return SharedThis(this);
    }

    TSharedPtr<FAcquireByUserIdResult> FAcquireByUserIdResult::WithTransactionId(
        const TOptional<FString> TransactionId
    )
    {
        this->TransactionIdValue = TransactionId;
        return SharedThis(this);
    }

    TSharedPtr<FAcquireByUserIdResult> FAcquireByUserIdResult::WithStampSheet(
        const TOptional<FString> StampSheet
    )
    {
        this->StampSheetValue = StampSheet;
        return SharedThis(this);
    }

    TSharedPtr<FAcquireByUserIdResult> FAcquireByUserIdResult::WithStampSheetEncryptionKeyId(
        const TOptional<FString> StampSheetEncryptionKeyId
    )
    {
        this->StampSheetEncryptionKeyIdValue = StampSheetEncryptionKeyId;
        return SharedThis(this);
    }

    TSharedPtr<FAcquireByUserIdResult> FAcquireByUserIdResult::WithAutoRunStampSheet(
        const TOptional<bool> AutoRunStampSheet
    )
    {
        this->AutoRunStampSheetValue = AutoRunStampSheet;
        return SharedThis(this);
    }

    TSharedPtr<FAcquireByUserIdResult> FAcquireByUserIdResult::WithAtomicCommit(
        const TOptional<bool> AtomicCommit
    )
    {
        this->AtomicCommitValue = AtomicCommit;
        return SharedThis(this);
    }

    TSharedPtr<FAcquireByUserIdResult> FAcquireByUserIdResult::WithTransaction(
        const TOptional<FString> Transaction
    )
    {
        this->TransactionValue = Transaction;
        return SharedThis(this);
    }

    TSharedPtr<FAcquireByUserIdResult> FAcquireByUserIdResult::WithTransactionResult(
        const TSharedPtr<Gs2::Core::Model::FTransactionResult> TransactionResult
    )
    {
        this->TransactionResultValue = TransactionResult;
        return SharedThis(this);
    }

    TSharedPtr<Model::FAwait> FAcquireByUserIdResult::GetItem() const
    {
        if (!ItemValue.IsValid())
        {
            return nullptr;
        }
        return ItemValue;
    }

    TOptional<FString> FAcquireByUserIdResult::GetTransactionId() const
    {
        return TransactionIdValue;
    }

    TOptional<FString> FAcquireByUserIdResult::GetStampSheet() const
    {
        return StampSheetValue;
    }

    TOptional<FString> FAcquireByUserIdResult::GetStampSheetEncryptionKeyId() const
    {
        return StampSheetEncryptionKeyIdValue;
    }

    TOptional<bool> FAcquireByUserIdResult::GetAutoRunStampSheet() const
    {
        return AutoRunStampSheetValue;
    }

    FString FAcquireByUserIdResult::GetAutoRunStampSheetString() const
    {
        if (!AutoRunStampSheetValue.IsSet())
        {
            return FString("null");
        }
        return FString(AutoRunStampSheetValue.GetValue() ? "true" : "false");
    }

    TOptional<bool> FAcquireByUserIdResult::GetAtomicCommit() const
    {
        return AtomicCommitValue;
    }

    FString FAcquireByUserIdResult::GetAtomicCommitString() const
    {
        if (!AtomicCommitValue.IsSet())
        {
            return FString("null");
        }
        return FString(AtomicCommitValue.GetValue() ? "true" : "false");
    }

    TOptional<FString> FAcquireByUserIdResult::GetTransaction() const
    {
        return TransactionValue;
    }

    TSharedPtr<Gs2::Core::Model::FTransactionResult> FAcquireByUserIdResult::GetTransactionResult() const
    {
        if (!TransactionResultValue.IsValid())
        {
            return nullptr;
        }
        return TransactionResultValue;
    }

    TSharedPtr<FAcquireByUserIdResult> FAcquireByUserIdResult::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FAcquireByUserIdResult>()
            ->WithItem(Data->HasField(ANSI_TO_TCHAR("item")) ? [Data]() -> Model::FAwaitPtr
                 {
                    if (Data->HasTypedField<EJson::Null>(ANSI_TO_TCHAR("item")))
                    {
                        return nullptr;
                    }
                    return Model::FAwait::FromJson(Data->GetObjectField(ANSI_TO_TCHAR("item")));
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

    TSharedPtr<FJsonObject> FAcquireByUserIdResult::ToJson() const
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