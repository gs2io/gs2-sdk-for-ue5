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

#include "Enchant/Model/RarityParameterValue.h"

namespace Gs2::Enchant::Model
{
    FRarityParameterValue::FRarityParameterValue():
        NameValue(TOptional<FString>()),
        ResourceNameValue(TOptional<FString>()),
        ResourceValueValue(TOptional<int64>())
    {
    }

    FRarityParameterValue::FRarityParameterValue(
        const FRarityParameterValue& From
    ):
        NameValue(From.NameValue),
        ResourceNameValue(From.ResourceNameValue),
        ResourceValueValue(From.ResourceValueValue)
    {
    }

    TSharedPtr<FRarityParameterValue> FRarityParameterValue::WithName(
        const TOptional<FString> Name
    )
    {
        this->NameValue = Name;
        return SharedThis(this);
    }

    TSharedPtr<FRarityParameterValue> FRarityParameterValue::WithResourceName(
        const TOptional<FString> ResourceName
    )
    {
        this->ResourceNameValue = ResourceName;
        return SharedThis(this);
    }

    TSharedPtr<FRarityParameterValue> FRarityParameterValue::WithResourceValue(
        const TOptional<int64> ResourceValue
    )
    {
        this->ResourceValueValue = ResourceValue;
        return SharedThis(this);
    }
    TOptional<FString> FRarityParameterValue::GetName() const
    {
        return NameValue;
    }
    TOptional<FString> FRarityParameterValue::GetResourceName() const
    {
        return ResourceNameValue;
    }
    TOptional<int64> FRarityParameterValue::GetResourceValue() const
    {
        return ResourceValueValue;
    }

    FString FRarityParameterValue::GetResourceValueString() const
    {
        if (!ResourceValueValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), ResourceValueValue.GetValue());
    }

    TSharedPtr<FRarityParameterValue> FRarityParameterValue::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FRarityParameterValue>()
            ->WithName(Data->HasField("name") ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField("name", v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithResourceName(Data->HasField("resourceName") ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField("resourceName", v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithResourceValue(Data->HasField("resourceValue") ? [Data]() -> TOptional<int64>
                {
                    int64 v;
                    if (Data->TryGetNumberField("resourceValue", v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<int64>();
                }() : TOptional<int64>());
    }

    TSharedPtr<FJsonObject> FRarityParameterValue::ToJson() const
    {
        const TSharedPtr<FJsonObject> JsonRootObject = MakeShared<FJsonObject>();
        if (NameValue.IsSet())
        {
            JsonRootObject->SetStringField("name", NameValue.GetValue());
        }
        if (ResourceNameValue.IsSet())
        {
            JsonRootObject->SetStringField("resourceName", ResourceNameValue.GetValue());
        }
        if (ResourceValueValue.IsSet())
        {
            JsonRootObject->SetStringField("resourceValue", FString::Printf(TEXT("%lld"), ResourceValueValue.GetValue()));
        }
        return JsonRootObject;
    }

    FString FRarityParameterValue::TypeName = "RarityParameterValue";
}