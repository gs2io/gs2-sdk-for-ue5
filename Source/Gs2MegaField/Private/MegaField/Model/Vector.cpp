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

#include "MegaField/Model/Vector.h"

namespace Gs2::MegaField::Model
{
    FVector::FVector():
        XValue(TOptional<float>()),
        YValue(TOptional<float>()),
        ZValue(TOptional<float>())
    {
    }

    FVector::FVector(
        const FVector& From
    ):
        XValue(From.XValue),
        YValue(From.YValue),
        ZValue(From.ZValue)
    {
    }

    TSharedPtr<FVector> FVector::WithX(
        const TOptional<float> X
    )
    {
        this->XValue = X;
        return SharedThis(this);
    }

    TSharedPtr<FVector> FVector::WithY(
        const TOptional<float> Y
    )
    {
        this->YValue = Y;
        return SharedThis(this);
    }

    TSharedPtr<FVector> FVector::WithZ(
        const TOptional<float> Z
    )
    {
        this->ZValue = Z;
        return SharedThis(this);
    }
    TOptional<float> FVector::GetX() const
    {
        return XValue;
    }

    FString FVector::GetXString() const
    {
        if (!XValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%f"), XValue.GetValue());
    }
    TOptional<float> FVector::GetY() const
    {
        return YValue;
    }

    FString FVector::GetYString() const
    {
        if (!YValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%f"), YValue.GetValue());
    }
    TOptional<float> FVector::GetZ() const
    {
        return ZValue;
    }

    FString FVector::GetZString() const
    {
        if (!ZValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%f"), ZValue.GetValue());
    }

    TSharedPtr<FVector> FVector::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FVector>()
            ->WithX(Data->HasField("x") ? [Data]() -> TOptional<float>
                {
                    float v;
                    if (Data->TryGetNumberField("x", v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<float>();
                }() : TOptional<float>())
            ->WithY(Data->HasField("y") ? [Data]() -> TOptional<float>
                {
                    float v;
                    if (Data->TryGetNumberField("y", v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<float>();
                }() : TOptional<float>())
            ->WithZ(Data->HasField("z") ? [Data]() -> TOptional<float>
                {
                    float v;
                    if (Data->TryGetNumberField("z", v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<float>();
                }() : TOptional<float>());
    }

    TSharedPtr<FJsonObject> FVector::ToJson() const
    {
        const TSharedPtr<FJsonObject> JsonRootObject = MakeShared<FJsonObject>();
        if (XValue.IsSet())
        {
            JsonRootObject->SetNumberField("x", XValue.GetValue());
        }
        if (YValue.IsSet())
        {
            JsonRootObject->SetNumberField("y", YValue.GetValue());
        }
        if (ZValue.IsSet())
        {
            JsonRootObject->SetNumberField("z", ZValue.GetValue());
        }
        return JsonRootObject;
    }

    FString FVector::TypeName = "Vector";
}