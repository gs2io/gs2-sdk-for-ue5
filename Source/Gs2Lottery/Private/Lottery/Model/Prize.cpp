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

#include "Lottery/Model/Prize.h"

namespace Gs2::Lottery::Model
{
    FPrize::FPrize():
        PrizeIdValue(TOptional<FString>()),
        TypeValue(TOptional<FString>()),
        AcquireActionsValue(nullptr),
        DrawnLimitValue(TOptional<int32>()),
        LimitFailOverPrizeIdValue(TOptional<FString>()),
        PrizeTableNameValue(TOptional<FString>()),
        WeightValue(TOptional<int32>())
    {
    }

    FPrize::FPrize(
        const FPrize& From
    ):
        PrizeIdValue(From.PrizeIdValue),
        TypeValue(From.TypeValue),
        AcquireActionsValue(From.AcquireActionsValue),
        DrawnLimitValue(From.DrawnLimitValue),
        LimitFailOverPrizeIdValue(From.LimitFailOverPrizeIdValue),
        PrizeTableNameValue(From.PrizeTableNameValue),
        WeightValue(From.WeightValue)
    {
    }

    TSharedPtr<FPrize> FPrize::WithPrizeId(
        const TOptional<FString> PrizeId
    )
    {
        this->PrizeIdValue = PrizeId;
        return SharedThis(this);
    }

    TSharedPtr<FPrize> FPrize::WithType(
        const TOptional<FString> Type
    )
    {
        this->TypeValue = Type;
        return SharedThis(this);
    }

    TSharedPtr<FPrize> FPrize::WithAcquireActions(
        const TSharedPtr<TArray<TSharedPtr<Model::FAcquireAction>>> AcquireActions
    )
    {
        this->AcquireActionsValue = AcquireActions;
        return SharedThis(this);
    }

    TSharedPtr<FPrize> FPrize::WithDrawnLimit(
        const TOptional<int32> DrawnLimit
    )
    {
        this->DrawnLimitValue = DrawnLimit;
        return SharedThis(this);
    }

    TSharedPtr<FPrize> FPrize::WithLimitFailOverPrizeId(
        const TOptional<FString> LimitFailOverPrizeId
    )
    {
        this->LimitFailOverPrizeIdValue = LimitFailOverPrizeId;
        return SharedThis(this);
    }

    TSharedPtr<FPrize> FPrize::WithPrizeTableName(
        const TOptional<FString> PrizeTableName
    )
    {
        this->PrizeTableNameValue = PrizeTableName;
        return SharedThis(this);
    }

    TSharedPtr<FPrize> FPrize::WithWeight(
        const TOptional<int32> Weight
    )
    {
        this->WeightValue = Weight;
        return SharedThis(this);
    }
    TOptional<FString> FPrize::GetPrizeId() const
    {
        return PrizeIdValue;
    }
    TOptional<FString> FPrize::GetType() const
    {
        return TypeValue;
    }
    TSharedPtr<TArray<TSharedPtr<Model::FAcquireAction>>> FPrize::GetAcquireActions() const
    {
        return AcquireActionsValue;
    }
    TOptional<int32> FPrize::GetDrawnLimit() const
    {
        return DrawnLimitValue;
    }

    FString FPrize::GetDrawnLimitString() const
    {
        if (!DrawnLimitValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%ld"), DrawnLimitValue.GetValue());
    }
    TOptional<FString> FPrize::GetLimitFailOverPrizeId() const
    {
        return LimitFailOverPrizeIdValue;
    }
    TOptional<FString> FPrize::GetPrizeTableName() const
    {
        return PrizeTableNameValue;
    }
    TOptional<int32> FPrize::GetWeight() const
    {
        return WeightValue;
    }

    FString FPrize::GetWeightString() const
    {
        if (!WeightValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%ld"), WeightValue.GetValue());
    }

    TSharedPtr<FPrize> FPrize::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FPrize>()
            ->WithPrizeId(Data->HasField("prizeId") ? [Data]() -> TOptional<FString>
                {
                    FString v;
                    if (Data->TryGetStringField("prizeId", v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithType(Data->HasField("type") ? [Data]() -> TOptional<FString>
                {
                    FString v;
                    if (Data->TryGetStringField("type", v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
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
            ->WithDrawnLimit(Data->HasField("drawnLimit") ? [Data]() -> TOptional<int32>
                {
                    int32 v;
                    if (Data->TryGetNumberField("drawnLimit", v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<int32>();
                }() : TOptional<int32>())
            ->WithLimitFailOverPrizeId(Data->HasField("limitFailOverPrizeId") ? [Data]() -> TOptional<FString>
                {
                    FString v;
                    if (Data->TryGetStringField("limitFailOverPrizeId", v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithPrizeTableName(Data->HasField("prizeTableName") ? [Data]() -> TOptional<FString>
                {
                    FString v;
                    if (Data->TryGetStringField("prizeTableName", v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithWeight(Data->HasField("weight") ? [Data]() -> TOptional<int32>
                {
                    int32 v;
                    if (Data->TryGetNumberField("weight", v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<int32>();
                }() : TOptional<int32>());
    }

    TSharedPtr<FJsonObject> FPrize::ToJson() const
    {
        const TSharedPtr<FJsonObject> JsonRootObject = MakeShared<FJsonObject>();
        if (PrizeIdValue.IsSet())
        {
            JsonRootObject->SetStringField("prizeId", PrizeIdValue.GetValue());
        }
        if (TypeValue.IsSet())
        {
            JsonRootObject->SetStringField("type", TypeValue.GetValue());
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
        if (DrawnLimitValue.IsSet())
        {
            JsonRootObject->SetNumberField("drawnLimit", DrawnLimitValue.GetValue());
        }
        if (LimitFailOverPrizeIdValue.IsSet())
        {
            JsonRootObject->SetStringField("limitFailOverPrizeId", LimitFailOverPrizeIdValue.GetValue());
        }
        if (PrizeTableNameValue.IsSet())
        {
            JsonRootObject->SetStringField("prizeTableName", PrizeTableNameValue.GetValue());
        }
        if (WeightValue.IsSet())
        {
            JsonRootObject->SetNumberField("weight", WeightValue.GetValue());
        }
        return JsonRootObject;
    }

    FString FPrize::TypeName = "Prize";
}