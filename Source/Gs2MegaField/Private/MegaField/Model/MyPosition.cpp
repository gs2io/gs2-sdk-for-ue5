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

#include "MegaField/Model/MyPosition.h"

namespace Gs2::MegaField::Model
{
    FMyPosition::FMyPosition():
        PositionValue(nullptr),
        VectorValue(nullptr),
        RValue(TOptional<float>())
    {
    }

    FMyPosition::FMyPosition(
        const FMyPosition& From
    ):
        PositionValue(From.PositionValue),
        VectorValue(From.VectorValue),
        RValue(From.RValue)
    {
    }

    TSharedPtr<FMyPosition> FMyPosition::WithPosition(
        const TSharedPtr<FPosition> Position
    )
    {
        this->PositionValue = Position;
        return SharedThis(this);
    }

    TSharedPtr<FMyPosition> FMyPosition::WithVector(
        const TSharedPtr<FVector> Vector
    )
    {
        this->VectorValue = Vector;
        return SharedThis(this);
    }

    TSharedPtr<FMyPosition> FMyPosition::WithR(
        const TOptional<float> R
    )
    {
        this->RValue = R;
        return SharedThis(this);
    }
    TSharedPtr<FPosition> FMyPosition::GetPosition() const
    {
        return PositionValue;
    }
    TSharedPtr<FVector> FMyPosition::GetVector() const
    {
        return VectorValue;
    }
    TOptional<float> FMyPosition::GetR() const
    {
        return RValue;
    }

    FString FMyPosition::GetRString() const
    {
        if (!RValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%f"), RValue.GetValue());
    }

    TSharedPtr<FMyPosition> FMyPosition::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FMyPosition>()
            ->WithPosition(Data->HasField("position") ? [Data]() -> Model::FPositionPtr
                {
                    if (Data->HasTypedField<EJson::Null>("position"))
                    {
                        return nullptr;
                    }
                    return Model::FPosition::FromJson(Data->GetObjectField("position"));
                 }() : nullptr)
            ->WithVector(Data->HasField("vector") ? [Data]() -> Model::FVectorPtr
                {
                    if (Data->HasTypedField<EJson::Null>("vector"))
                    {
                        return nullptr;
                    }
                    return Model::FVector::FromJson(Data->GetObjectField("vector"));
                 }() : nullptr)
            ->WithR(Data->HasField("r") ? [Data]() -> TOptional<float>
                {
                    float v;
                    if (Data->TryGetNumberField("r", v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<float>();
                }() : TOptional<float>());
    }

    TSharedPtr<FJsonObject> FMyPosition::ToJson() const
    {
        const TSharedPtr<FJsonObject> JsonRootObject = MakeShared<FJsonObject>();
        if (PositionValue != nullptr && PositionValue.IsValid())
        {
            JsonRootObject->SetObjectField("position", PositionValue->ToJson());
        }
        if (VectorValue != nullptr && VectorValue.IsValid())
        {
            JsonRootObject->SetObjectField("vector", VectorValue->ToJson());
        }
        if (RValue.IsSet())
        {
            JsonRootObject->SetNumberField("r", RValue.GetValue());
        }
        return JsonRootObject;
    }

    FString FMyPosition::TypeName = "MyPosition";
}