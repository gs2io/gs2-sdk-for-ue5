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

#include "Matchmaking/Model/AttributeRange.h"

namespace Gs2::Matchmaking::Model
{
    FAttributeRange::FAttributeRange():
        NameValue(TOptional<FString>()),
        MinValue(TOptional<int32>()),
        MaxValue(TOptional<int32>())
    {
    }

    FAttributeRange::FAttributeRange(
        const FAttributeRange& From
    ):
        NameValue(From.NameValue),
        MinValue(From.MinValue),
        MaxValue(From.MaxValue)
    {
    }

    TSharedPtr<FAttributeRange> FAttributeRange::WithName(
        const TOptional<FString> Name
    )
    {
        this->NameValue = Name;
        return SharedThis(this);
    }

    TSharedPtr<FAttributeRange> FAttributeRange::WithMin(
        const TOptional<int32> Min
    )
    {
        this->MinValue = Min;
        return SharedThis(this);
    }

    TSharedPtr<FAttributeRange> FAttributeRange::WithMax(
        const TOptional<int32> Max
    )
    {
        this->MaxValue = Max;
        return SharedThis(this);
    }
    TOptional<FString> FAttributeRange::GetName() const
    {
        return NameValue;
    }
    TOptional<int32> FAttributeRange::GetMin() const
    {
        return MinValue;
    }

    FString FAttributeRange::GetMinString() const
    {
        if (!MinValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%ld"), MinValue.GetValue());
    }
    TOptional<int32> FAttributeRange::GetMax() const
    {
        return MaxValue;
    }

    FString FAttributeRange::GetMaxString() const
    {
        if (!MaxValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%ld"), MaxValue.GetValue());
    }

    TSharedPtr<FAttributeRange> FAttributeRange::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FAttributeRange>()
            ->WithName(Data->HasField("name") ? [Data]() -> TOptional<FString>
                {
                    FString v;
                    if (Data->TryGetStringField("name", v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithMin(Data->HasField("min") ? [Data]() -> TOptional<int32>
                {
                    int32 v;
                    if (Data->TryGetNumberField("min", v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<int32>();
                }() : TOptional<int32>())
            ->WithMax(Data->HasField("max") ? [Data]() -> TOptional<int32>
                {
                    int32 v;
                    if (Data->TryGetNumberField("max", v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<int32>();
                }() : TOptional<int32>());
    }

    TSharedPtr<FJsonObject> FAttributeRange::ToJson() const
    {
        const TSharedPtr<FJsonObject> JsonRootObject = MakeShared<FJsonObject>();
        if (NameValue.IsSet())
        {
            JsonRootObject->SetStringField("name", NameValue.GetValue());
        }
        if (MinValue.IsSet())
        {
            JsonRootObject->SetNumberField("min", MinValue.GetValue());
        }
        if (MaxValue.IsSet())
        {
            JsonRootObject->SetNumberField("max", MaxValue.GetValue());
        }
        return JsonRootObject;
    }

    FString FAttributeRange::TypeName = "AttributeRange";
}