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

#include "Ranking2/Result/ReceiveGlobalRankingReceivedRewardResult.h"

namespace Gs2::Ranking2::Result
{
    FReceiveGlobalRankingReceivedRewardResult::FReceiveGlobalRankingReceivedRewardResult():
        ItemValue(nullptr),
        AcquireActionsValue(nullptr),
        TransactionIdValue(TOptional<FString>()),
        StampSheetValue(TOptional<FString>()),
        StampSheetEncryptionKeyIdValue(TOptional<FString>()),
        AutoRunStampSheetValue(TOptional<bool>())
    {
    }

    FReceiveGlobalRankingReceivedRewardResult::FReceiveGlobalRankingReceivedRewardResult(
        const FReceiveGlobalRankingReceivedRewardResult& From
    ):
        ItemValue(From.ItemValue),
        AcquireActionsValue(From.AcquireActionsValue),
        TransactionIdValue(From.TransactionIdValue),
        StampSheetValue(From.StampSheetValue),
        StampSheetEncryptionKeyIdValue(From.StampSheetEncryptionKeyIdValue),
        AutoRunStampSheetValue(From.AutoRunStampSheetValue)
    {
    }

    TSharedPtr<FReceiveGlobalRankingReceivedRewardResult> FReceiveGlobalRankingReceivedRewardResult::WithItem(
        const TSharedPtr<Model::FGlobalRankingModel> Item
    )
    {
        this->ItemValue = Item;
        return SharedThis(this);
    }

    TSharedPtr<FReceiveGlobalRankingReceivedRewardResult> FReceiveGlobalRankingReceivedRewardResult::WithAcquireActions(
        const TSharedPtr<TArray<TSharedPtr<Model::FAcquireAction>>> AcquireActions
    )
    {
        this->AcquireActionsValue = AcquireActions;
        return SharedThis(this);
    }

    TSharedPtr<FReceiveGlobalRankingReceivedRewardResult> FReceiveGlobalRankingReceivedRewardResult::WithTransactionId(
        const TOptional<FString> TransactionId
    )
    {
        this->TransactionIdValue = TransactionId;
        return SharedThis(this);
    }

    TSharedPtr<FReceiveGlobalRankingReceivedRewardResult> FReceiveGlobalRankingReceivedRewardResult::WithStampSheet(
        const TOptional<FString> StampSheet
    )
    {
        this->StampSheetValue = StampSheet;
        return SharedThis(this);
    }

    TSharedPtr<FReceiveGlobalRankingReceivedRewardResult> FReceiveGlobalRankingReceivedRewardResult::WithStampSheetEncryptionKeyId(
        const TOptional<FString> StampSheetEncryptionKeyId
    )
    {
        this->StampSheetEncryptionKeyIdValue = StampSheetEncryptionKeyId;
        return SharedThis(this);
    }

    TSharedPtr<FReceiveGlobalRankingReceivedRewardResult> FReceiveGlobalRankingReceivedRewardResult::WithAutoRunStampSheet(
        const TOptional<bool> AutoRunStampSheet
    )
    {
        this->AutoRunStampSheetValue = AutoRunStampSheet;
        return SharedThis(this);
    }

    TSharedPtr<Model::FGlobalRankingModel> FReceiveGlobalRankingReceivedRewardResult::GetItem() const
    {
        if (!ItemValue.IsValid())
        {
            return nullptr;
        }
        return ItemValue;
    }

    TSharedPtr<TArray<TSharedPtr<Model::FAcquireAction>>> FReceiveGlobalRankingReceivedRewardResult::GetAcquireActions() const
    {
        if (!AcquireActionsValue.IsValid())
        {
            return nullptr;
        }
        return AcquireActionsValue;
    }

    TOptional<FString> FReceiveGlobalRankingReceivedRewardResult::GetTransactionId() const
    {
        return TransactionIdValue;
    }

    TOptional<FString> FReceiveGlobalRankingReceivedRewardResult::GetStampSheet() const
    {
        return StampSheetValue;
    }

    TOptional<FString> FReceiveGlobalRankingReceivedRewardResult::GetStampSheetEncryptionKeyId() const
    {
        return StampSheetEncryptionKeyIdValue;
    }

    TOptional<bool> FReceiveGlobalRankingReceivedRewardResult::GetAutoRunStampSheet() const
    {
        return AutoRunStampSheetValue;
    }

    FString FReceiveGlobalRankingReceivedRewardResult::GetAutoRunStampSheetString() const
    {
        if (!AutoRunStampSheetValue.IsSet())
        {
            return FString("null");
        }
        return FString(AutoRunStampSheetValue.GetValue() ? "true" : "false");
    }

    TSharedPtr<FReceiveGlobalRankingReceivedRewardResult> FReceiveGlobalRankingReceivedRewardResult::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FReceiveGlobalRankingReceivedRewardResult>()
            ->WithItem(Data->HasField(ANSI_TO_TCHAR("item")) ? [Data]() -> Model::FGlobalRankingModelPtr
                 {
                    if (Data->HasTypedField<EJson::Null>(ANSI_TO_TCHAR("item")))
                    {
                        return nullptr;
                    }
                    return Model::FGlobalRankingModel::FromJson(Data->GetObjectField(ANSI_TO_TCHAR("item")));
                 }() : nullptr)
            ->WithAcquireActions(Data->HasField(ANSI_TO_TCHAR("acquireActions")) ? [Data]() -> TSharedPtr<TArray<Model::FAcquireActionPtr>>
                 {
                    auto v = MakeShared<TArray<Model::FAcquireActionPtr>>();
                    if (!Data->HasTypedField<EJson::Null>(ANSI_TO_TCHAR("acquireActions")) && Data->HasTypedField<EJson::Array>(ANSI_TO_TCHAR("acquireActions")))
                    {
                        for (auto JsonObjectValue : Data->GetArrayField(ANSI_TO_TCHAR("acquireActions")))
                        {
                            v->Add(Model::FAcquireAction::FromJson(JsonObjectValue->AsObject()));
                        }
                    }
                    return v;
                 }() : MakeShared<TArray<Model::FAcquireActionPtr>>())
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
                }() : TOptional<bool>());
    }

    TSharedPtr<FJsonObject> FReceiveGlobalRankingReceivedRewardResult::ToJson() const
    {
        const TSharedPtr<FJsonObject> JsonRootObject = MakeShared<FJsonObject>();
        if (ItemValue != nullptr && ItemValue.IsValid())
        {
            JsonRootObject->SetObjectField("item", ItemValue->ToJson());
        }
        if (AcquireActionsValue != nullptr && AcquireActionsValue.IsValid())
        {
            TArray<TSharedPtr<FJsonValue>> v;
            for (auto JsonObjectValue : *AcquireActionsValue)
            {
                v.Add(MakeShared<FJsonValueObject>(JsonObjectValue->ToJson()));
            }
            JsonRootObject->SetArrayField("acquireActions", v);
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