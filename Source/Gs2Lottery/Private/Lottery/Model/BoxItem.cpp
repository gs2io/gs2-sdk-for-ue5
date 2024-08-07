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

#include "Lottery/Model/BoxItem.h"

namespace Gs2::Lottery::Model
{
    FBoxItem::FBoxItem():
        PrizeIdValue(TOptional<FString>()),
        AcquireActionsValue(nullptr),
        RemainingValue(TOptional<int32>()),
        InitialValue(TOptional<int32>())
    {
    }

    FBoxItem::FBoxItem(
        const FBoxItem& From
    ):
        PrizeIdValue(From.PrizeIdValue),
        AcquireActionsValue(From.AcquireActionsValue),
        RemainingValue(From.RemainingValue),
        InitialValue(From.InitialValue)
    {
    }

    TSharedPtr<FBoxItem> FBoxItem::WithPrizeId(
        const TOptional<FString> PrizeId
    )
    {
        this->PrizeIdValue = PrizeId;
        return SharedThis(this);
    }

    TSharedPtr<FBoxItem> FBoxItem::WithAcquireActions(
        const TSharedPtr<TArray<TSharedPtr<Model::FAcquireAction>>> AcquireActions
    )
    {
        this->AcquireActionsValue = AcquireActions;
        return SharedThis(this);
    }

    TSharedPtr<FBoxItem> FBoxItem::WithRemaining(
        const TOptional<int32> Remaining
    )
    {
        this->RemainingValue = Remaining;
        return SharedThis(this);
    }

    TSharedPtr<FBoxItem> FBoxItem::WithInitial(
        const TOptional<int32> Initial
    )
    {
        this->InitialValue = Initial;
        return SharedThis(this);
    }
    TOptional<FString> FBoxItem::GetPrizeId() const
    {
        return PrizeIdValue;
    }
    TSharedPtr<TArray<TSharedPtr<Model::FAcquireAction>>> FBoxItem::GetAcquireActions() const
    {
        return AcquireActionsValue;
    }
    TOptional<int32> FBoxItem::GetRemaining() const
    {
        return RemainingValue;
    }

    FString FBoxItem::GetRemainingString() const
    {
        if (!RemainingValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%d"), RemainingValue.GetValue());
    }
    TOptional<int32> FBoxItem::GetInitial() const
    {
        return InitialValue;
    }

    FString FBoxItem::GetInitialString() const
    {
        if (!InitialValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%d"), InitialValue.GetValue());
    }

    TSharedPtr<FBoxItem> FBoxItem::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FBoxItem>()
            ->WithPrizeId(Data->HasField(ANSI_TO_TCHAR("prizeId")) ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("prizeId"), v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
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
            ->WithRemaining(Data->HasField(ANSI_TO_TCHAR("remaining")) ? [Data]() -> TOptional<int32>
                {
                    int32 v;
                    if (Data->TryGetNumberField(ANSI_TO_TCHAR("remaining"), v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<int32>();
                }() : TOptional<int32>())
            ->WithInitial(Data->HasField(ANSI_TO_TCHAR("initial")) ? [Data]() -> TOptional<int32>
                {
                    int32 v;
                    if (Data->TryGetNumberField(ANSI_TO_TCHAR("initial"), v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<int32>();
                }() : TOptional<int32>());
    }

    TSharedPtr<FJsonObject> FBoxItem::ToJson() const
    {
        const TSharedPtr<FJsonObject> JsonRootObject = MakeShared<FJsonObject>();
        if (PrizeIdValue.IsSet())
        {
            JsonRootObject->SetStringField("prizeId", PrizeIdValue.GetValue());
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
        if (RemainingValue.IsSet())
        {
            JsonRootObject->SetNumberField("remaining", RemainingValue.GetValue());
        }
        if (InitialValue.IsSet())
        {
            JsonRootObject->SetNumberField("initial", InitialValue.GetValue());
        }
        return JsonRootObject;
    }

    FString FBoxItem::TypeName = "BoxItem";
}