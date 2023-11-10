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

#include "MegaField/Model/Scope.h"

namespace Gs2::MegaField::Model
{
    FScope::FScope():
        LayerNameValue(TOptional<FString>()),
        RValue(TOptional<float>()),
        LimitValue(TOptional<int32>())
    {
    }

    FScope::FScope(
        const FScope& From
    ):
        LayerNameValue(From.LayerNameValue),
        RValue(From.RValue),
        LimitValue(From.LimitValue)
    {
    }

    TSharedPtr<FScope> FScope::WithLayerName(
        const TOptional<FString> LayerName
    )
    {
        this->LayerNameValue = LayerName;
        return SharedThis(this);
    }

    TSharedPtr<FScope> FScope::WithR(
        const TOptional<float> R
    )
    {
        this->RValue = R;
        return SharedThis(this);
    }

    TSharedPtr<FScope> FScope::WithLimit(
        const TOptional<int32> Limit
    )
    {
        this->LimitValue = Limit;
        return SharedThis(this);
    }
    TOptional<FString> FScope::GetLayerName() const
    {
        return LayerNameValue;
    }
    TOptional<float> FScope::GetR() const
    {
        return RValue;
    }

    FString FScope::GetRString() const
    {
        if (!RValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%f"), RValue.GetValue());
    }
    TOptional<int32> FScope::GetLimit() const
    {
        return LimitValue;
    }

    FString FScope::GetLimitString() const
    {
        if (!LimitValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%d"), LimitValue.GetValue());
    }

    TSharedPtr<FScope> FScope::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FScope>()
            ->WithLayerName(Data->HasField("layerName") ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField("layerName", v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithR(Data->HasField("r") ? [Data]() -> TOptional<float>
                {
                    float v;
                    if (Data->TryGetNumberField("r", v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<float>();
                }() : TOptional<float>())
            ->WithLimit(Data->HasField("limit") ? [Data]() -> TOptional<int32>
                {
                    int32 v;
                    if (Data->TryGetNumberField("limit", v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<int32>();
                }() : TOptional<int32>());
    }

    TSharedPtr<FJsonObject> FScope::ToJson() const
    {
        const TSharedPtr<FJsonObject> JsonRootObject = MakeShared<FJsonObject>();
        if (LayerNameValue.IsSet())
        {
            JsonRootObject->SetStringField("layerName", LayerNameValue.GetValue());
        }
        if (RValue.IsSet())
        {
            JsonRootObject->SetNumberField("r", RValue.GetValue());
        }
        if (LimitValue.IsSet())
        {
            JsonRootObject->SetNumberField("limit", LimitValue.GetValue());
        }
        return JsonRootObject;
    }

    FString FScope::TypeName = "Scope";
}