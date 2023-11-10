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

#include "Formation/Result/AcquireActionsToFormPropertiesResult.h"

namespace Gs2::Formation::Result
{
    FAcquireActionsToFormPropertiesResult::FAcquireActionsToFormPropertiesResult():
        ItemValue(nullptr),
        MoldValue(nullptr),
        TransactionIdValue(TOptional<FString>()),
        StampSheetValue(TOptional<FString>()),
        StampSheetEncryptionKeyIdValue(TOptional<FString>()),
        AutoRunStampSheetValue(TOptional<bool>())
    {
    }

    FAcquireActionsToFormPropertiesResult::FAcquireActionsToFormPropertiesResult(
        const FAcquireActionsToFormPropertiesResult& From
    ):
        ItemValue(From.ItemValue),
        MoldValue(From.MoldValue),
        TransactionIdValue(From.TransactionIdValue),
        StampSheetValue(From.StampSheetValue),
        StampSheetEncryptionKeyIdValue(From.StampSheetEncryptionKeyIdValue),
        AutoRunStampSheetValue(From.AutoRunStampSheetValue)
    {
    }

    TSharedPtr<FAcquireActionsToFormPropertiesResult> FAcquireActionsToFormPropertiesResult::WithItem(
        const TSharedPtr<Model::FForm> Item
    )
    {
        this->ItemValue = Item;
        return SharedThis(this);
    }

    TSharedPtr<FAcquireActionsToFormPropertiesResult> FAcquireActionsToFormPropertiesResult::WithMold(
        const TSharedPtr<Model::FMold> Mold
    )
    {
        this->MoldValue = Mold;
        return SharedThis(this);
    }

    TSharedPtr<FAcquireActionsToFormPropertiesResult> FAcquireActionsToFormPropertiesResult::WithTransactionId(
        const TOptional<FString> TransactionId
    )
    {
        this->TransactionIdValue = TransactionId;
        return SharedThis(this);
    }

    TSharedPtr<FAcquireActionsToFormPropertiesResult> FAcquireActionsToFormPropertiesResult::WithStampSheet(
        const TOptional<FString> StampSheet
    )
    {
        this->StampSheetValue = StampSheet;
        return SharedThis(this);
    }

    TSharedPtr<FAcquireActionsToFormPropertiesResult> FAcquireActionsToFormPropertiesResult::WithStampSheetEncryptionKeyId(
        const TOptional<FString> StampSheetEncryptionKeyId
    )
    {
        this->StampSheetEncryptionKeyIdValue = StampSheetEncryptionKeyId;
        return SharedThis(this);
    }

    TSharedPtr<FAcquireActionsToFormPropertiesResult> FAcquireActionsToFormPropertiesResult::WithAutoRunStampSheet(
        const TOptional<bool> AutoRunStampSheet
    )
    {
        this->AutoRunStampSheetValue = AutoRunStampSheet;
        return SharedThis(this);
    }

    TSharedPtr<Model::FForm> FAcquireActionsToFormPropertiesResult::GetItem() const
    {
        if (!ItemValue.IsValid())
        {
            return nullptr;
        }
        return ItemValue;
    }

    TSharedPtr<Model::FMold> FAcquireActionsToFormPropertiesResult::GetMold() const
    {
        if (!MoldValue.IsValid())
        {
            return nullptr;
        }
        return MoldValue;
    }

    TOptional<FString> FAcquireActionsToFormPropertiesResult::GetTransactionId() const
    {
        return TransactionIdValue;
    }

    TOptional<FString> FAcquireActionsToFormPropertiesResult::GetStampSheet() const
    {
        return StampSheetValue;
    }

    TOptional<FString> FAcquireActionsToFormPropertiesResult::GetStampSheetEncryptionKeyId() const
    {
        return StampSheetEncryptionKeyIdValue;
    }

    TOptional<bool> FAcquireActionsToFormPropertiesResult::GetAutoRunStampSheet() const
    {
        return AutoRunStampSheetValue;
    }

    FString FAcquireActionsToFormPropertiesResult::GetAutoRunStampSheetString() const
    {
        if (!AutoRunStampSheetValue.IsSet())
        {
            return FString("null");
        }
        return FString(AutoRunStampSheetValue.GetValue() ? "true" : "false");
    }

    TSharedPtr<FAcquireActionsToFormPropertiesResult> FAcquireActionsToFormPropertiesResult::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FAcquireActionsToFormPropertiesResult>()
            ->WithItem(Data->HasField("item") ? [Data]() -> Model::FFormPtr
                 {
                    if (Data->HasTypedField<EJson::Null>("item"))
                    {
                        return nullptr;
                    }
                    return Model::FForm::FromJson(Data->GetObjectField("item"));
                 }() : nullptr)
            ->WithMold(Data->HasField("mold") ? [Data]() -> Model::FMoldPtr
                 {
                    if (Data->HasTypedField<EJson::Null>("mold"))
                    {
                        return nullptr;
                    }
                    return Model::FMold::FromJson(Data->GetObjectField("mold"));
                 }() : nullptr)
            ->WithTransactionId(Data->HasField("transactionId") ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField("transactionId", v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithStampSheet(Data->HasField("stampSheet") ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField("stampSheet", v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithStampSheetEncryptionKeyId(Data->HasField("stampSheetEncryptionKeyId") ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField("stampSheetEncryptionKeyId", v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithAutoRunStampSheet(Data->HasField("autoRunStampSheet") ? [Data]() -> TOptional<bool>
                {
                    bool v;
                    if (Data->TryGetBoolField("autoRunStampSheet", v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<bool>();
                }() : TOptional<bool>());
    }

    TSharedPtr<FJsonObject> FAcquireActionsToFormPropertiesResult::ToJson() const
    {
        const TSharedPtr<FJsonObject> JsonRootObject = MakeShared<FJsonObject>();
        if (ItemValue != nullptr && ItemValue.IsValid())
        {
            JsonRootObject->SetObjectField("item", ItemValue->ToJson());
        }
        if (MoldValue != nullptr && MoldValue.IsValid())
        {
            JsonRootObject->SetObjectField("mold", MoldValue->ToJson());
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
        return JsonRootObject;
    }
}