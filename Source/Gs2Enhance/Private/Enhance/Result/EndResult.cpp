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

#include "Enhance/Result/EndResult.h"

namespace Gs2::Enhance::Result
{
    FEndResult::FEndResult():
        ItemValue(nullptr),
        TransactionIdValue(TOptional<FString>()),
        StampSheetValue(TOptional<FString>()),
        StampSheetEncryptionKeyIdValue(TOptional<FString>()),
        AutoRunStampSheetValue(TOptional<bool>()),
        AcquireExperienceValue(TOptional<int64>()),
        BonusRateValue(TOptional<float>())
    {
    }

    FEndResult::FEndResult(
        const FEndResult& From
    ):
        ItemValue(From.ItemValue),
        TransactionIdValue(From.TransactionIdValue),
        StampSheetValue(From.StampSheetValue),
        StampSheetEncryptionKeyIdValue(From.StampSheetEncryptionKeyIdValue),
        AutoRunStampSheetValue(From.AutoRunStampSheetValue),
        AcquireExperienceValue(From.AcquireExperienceValue),
        BonusRateValue(From.BonusRateValue)
    {
    }

    TSharedPtr<FEndResult> FEndResult::WithItem(
        const TSharedPtr<Model::FProgress> Item
    )
    {
        this->ItemValue = Item;
        return SharedThis(this);
    }

    TSharedPtr<FEndResult> FEndResult::WithTransactionId(
        const TOptional<FString> TransactionId
    )
    {
        this->TransactionIdValue = TransactionId;
        return SharedThis(this);
    }

    TSharedPtr<FEndResult> FEndResult::WithStampSheet(
        const TOptional<FString> StampSheet
    )
    {
        this->StampSheetValue = StampSheet;
        return SharedThis(this);
    }

    TSharedPtr<FEndResult> FEndResult::WithStampSheetEncryptionKeyId(
        const TOptional<FString> StampSheetEncryptionKeyId
    )
    {
        this->StampSheetEncryptionKeyIdValue = StampSheetEncryptionKeyId;
        return SharedThis(this);
    }

    TSharedPtr<FEndResult> FEndResult::WithAutoRunStampSheet(
        const TOptional<bool> AutoRunStampSheet
    )
    {
        this->AutoRunStampSheetValue = AutoRunStampSheet;
        return SharedThis(this);
    }

    TSharedPtr<FEndResult> FEndResult::WithAcquireExperience(
        const TOptional<int64> AcquireExperience
    )
    {
        this->AcquireExperienceValue = AcquireExperience;
        return SharedThis(this);
    }

    TSharedPtr<FEndResult> FEndResult::WithBonusRate(
        const TOptional<float> BonusRate
    )
    {
        this->BonusRateValue = BonusRate;
        return SharedThis(this);
    }

    TSharedPtr<Model::FProgress> FEndResult::GetItem() const
    {
        if (!ItemValue.IsValid())
        {
            return nullptr;
        }
        return ItemValue;
    }

    TOptional<FString> FEndResult::GetTransactionId() const
    {
        return TransactionIdValue;
    }

    TOptional<FString> FEndResult::GetStampSheet() const
    {
        return StampSheetValue;
    }

    TOptional<FString> FEndResult::GetStampSheetEncryptionKeyId() const
    {
        return StampSheetEncryptionKeyIdValue;
    }

    TOptional<bool> FEndResult::GetAutoRunStampSheet() const
    {
        return AutoRunStampSheetValue;
    }

    FString FEndResult::GetAutoRunStampSheetString() const
    {
        if (!AutoRunStampSheetValue.IsSet())
        {
            return FString("null");
        }
        return FString(AutoRunStampSheetValue.GetValue() ? "true" : "false");
    }

    TOptional<int64> FEndResult::GetAcquireExperience() const
    {
        return AcquireExperienceValue;
    }

    FString FEndResult::GetAcquireExperienceString() const
    {
        if (!AcquireExperienceValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), AcquireExperienceValue.GetValue());
    }

    TOptional<float> FEndResult::GetBonusRate() const
    {
        return BonusRateValue;
    }

    FString FEndResult::GetBonusRateString() const
    {
        if (!BonusRateValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%f"), BonusRateValue.GetValue());
    }

    TSharedPtr<FEndResult> FEndResult::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FEndResult>()
            ->WithItem(Data->HasField("item") ? [Data]() -> Model::FProgressPtr
                 {
                    if (Data->HasTypedField<EJson::Null>("item"))
                    {
                        return nullptr;
                    }
                    return Model::FProgress::FromJson(Data->GetObjectField("item"));
                 }() : nullptr)
            ->WithTransactionId(Data->HasField("transactionId") ? [Data]() -> TOptional<FString>
                {
                    FString v;
                    if (Data->TryGetStringField("transactionId", v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithStampSheet(Data->HasField("stampSheet") ? [Data]() -> TOptional<FString>
                {
                    FString v;
                    if (Data->TryGetStringField("stampSheet", v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithStampSheetEncryptionKeyId(Data->HasField("stampSheetEncryptionKeyId") ? [Data]() -> TOptional<FString>
                {
                    FString v;
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
                }() : TOptional<bool>())
            ->WithAcquireExperience(Data->HasField("acquireExperience") ? [Data]() -> TOptional<int64>
                {
                    int64 v;
                    if (Data->TryGetNumberField("acquireExperience", v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<int64>();
                }() : TOptional<int64>())
            ->WithBonusRate(Data->HasField("bonusRate") ? [Data]() -> TOptional<float>
                {
                    float v;
                    if (Data->TryGetNumberField("bonusRate", v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<float>();
                }() : TOptional<float>());
    }

    TSharedPtr<FJsonObject> FEndResult::ToJson() const
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
        if (AcquireExperienceValue.IsSet())
        {
            JsonRootObject->SetStringField("acquireExperience", FString::Printf(TEXT("%lld"), AcquireExperienceValue.GetValue()));
        }
        if (BonusRateValue.IsSet())
        {
            JsonRootObject->SetNumberField("bonusRate", BonusRateValue.GetValue());
        }
        return JsonRootObject;
    }
}