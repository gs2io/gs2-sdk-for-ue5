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
        AcquireActionsValue(nullptr),
        RemainingValue(TOptional<int32>()),
        InitialValue(TOptional<int32>())
    {
    }

    FBoxItem::FBoxItem(
        const FBoxItem& From
    ):
        AcquireActionsValue(From.AcquireActionsValue),
        RemainingValue(From.RemainingValue),
        InitialValue(From.InitialValue)
    {
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
        return FString::Printf(TEXT("%ld"), RemainingValue.GetValue());
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
        return FString::Printf(TEXT("%ld"), InitialValue.GetValue());
    }

    TSharedPtr<FBoxItem> FBoxItem::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FBoxItem>()
            ->WithAcquireActions(Data->HasField("acquireActions") ? [Data]() -> TSharedPtr<TArray<Model::FAcquireActionPtr>>
                {
                    auto v = MakeShared<TArray<Model::FAcquireActionPtr>>();
                    if (!Data->HasTypedField<EJson::Null>("acquireActions") && Data->HasTypedField<EJson::Array>("acquireActions"))
                    {
                        for (auto JsonObjectValue : Data->GetArrayField("acquireActions"))
                        {
                            v->Add(Model::FAcquireAction::FromJson(JsonObjectValue->AsObject()));
                        }
                    }
                    return v;
                 }() : nullptr)
            ->WithRemaining(Data->HasField("remaining") ? [Data]() -> TOptional<int32>
                {
                    int32 v;
                    if (Data->TryGetNumberField("remaining", v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<int32>();
                }() : TOptional<int32>())
            ->WithInitial(Data->HasField("initial") ? [Data]() -> TOptional<int32>
                {
                    int32 v;
                    if (Data->TryGetNumberField("initial", v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<int32>();
                }() : TOptional<int32>());
    }

    TSharedPtr<FJsonObject> FBoxItem::ToJson() const
    {
        const TSharedPtr<FJsonObject> JsonRootObject = MakeShared<FJsonObject>();
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