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

#include "MegaField/Model/Position.h"

namespace Gs2::MegaField::Model
{
    FPosition::FPosition():
        XValue(TOptional<float>()),
        YValue(TOptional<float>()),
        ZValue(TOptional<float>())
    {
    }

    FPosition::FPosition(
        const FPosition& From
    ):
        XValue(From.XValue),
        YValue(From.YValue),
        ZValue(From.ZValue)
    {
    }

    TSharedPtr<FPosition> FPosition::WithX(
        const TOptional<float> X
    )
    {
        this->XValue = X;
        return SharedThis(this);
    }

    TSharedPtr<FPosition> FPosition::WithY(
        const TOptional<float> Y
    )
    {
        this->YValue = Y;
        return SharedThis(this);
    }

    TSharedPtr<FPosition> FPosition::WithZ(
        const TOptional<float> Z
    )
    {
        this->ZValue = Z;
        return SharedThis(this);
    }
    TOptional<float> FPosition::GetX() const
    {
        return XValue;
    }

    FString FPosition::GetXString() const
    {
        if (!XValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%f"), XValue.GetValue());
    }
    TOptional<float> FPosition::GetY() const
    {
        return YValue;
    }

    FString FPosition::GetYString() const
    {
        if (!YValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%f"), YValue.GetValue());
    }
    TOptional<float> FPosition::GetZ() const
    {
        return ZValue;
    }

    FString FPosition::GetZString() const
    {
        if (!ZValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%f"), ZValue.GetValue());
    }

    TSharedPtr<FPosition> FPosition::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FPosition>()
            ->WithX(Data->HasField(ANSI_TO_TCHAR("x")) ? [Data]() -> TOptional<float>
                {
                    float v;
                    if (Data->TryGetNumberField(ANSI_TO_TCHAR("x"), v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<float>();
                }() : TOptional<float>())
            ->WithY(Data->HasField(ANSI_TO_TCHAR("y")) ? [Data]() -> TOptional<float>
                {
                    float v;
                    if (Data->TryGetNumberField(ANSI_TO_TCHAR("y"), v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<float>();
                }() : TOptional<float>())
            ->WithZ(Data->HasField(ANSI_TO_TCHAR("z")) ? [Data]() -> TOptional<float>
                {
                    float v;
                    if (Data->TryGetNumberField(ANSI_TO_TCHAR("z"), v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<float>();
                }() : TOptional<float>());
    }

    TSharedPtr<FJsonObject> FPosition::ToJson() const
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

    FString FPosition::TypeName = "Position";
}