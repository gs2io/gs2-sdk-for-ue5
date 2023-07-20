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

#include "Enchant/Model/RarityParameterValueModel.h"

namespace Gs2::Enchant::Model
{
    FRarityParameterValueModel::FRarityParameterValueModel():
        NameValue(TOptional<FString>()),
        MetadataValue(TOptional<FString>()),
        ResourceNameValue(TOptional<FString>()),
        ResourceValueValue(TOptional<int64>()),
        WeightValue(TOptional<int32>())
    {
    }

    FRarityParameterValueModel::FRarityParameterValueModel(
        const FRarityParameterValueModel& From
    ):
        NameValue(From.NameValue),
        MetadataValue(From.MetadataValue),
        ResourceNameValue(From.ResourceNameValue),
        ResourceValueValue(From.ResourceValueValue),
        WeightValue(From.WeightValue)
    {
    }

    TSharedPtr<FRarityParameterValueModel> FRarityParameterValueModel::WithName(
        const TOptional<FString> Name
    )
    {
        this->NameValue = Name;
        return SharedThis(this);
    }

    TSharedPtr<FRarityParameterValueModel> FRarityParameterValueModel::WithMetadata(
        const TOptional<FString> Metadata
    )
    {
        this->MetadataValue = Metadata;
        return SharedThis(this);
    }

    TSharedPtr<FRarityParameterValueModel> FRarityParameterValueModel::WithResourceName(
        const TOptional<FString> ResourceName
    )
    {
        this->ResourceNameValue = ResourceName;
        return SharedThis(this);
    }

    TSharedPtr<FRarityParameterValueModel> FRarityParameterValueModel::WithResourceValue(
        const TOptional<int64> ResourceValue
    )
    {
        this->ResourceValueValue = ResourceValue;
        return SharedThis(this);
    }

    TSharedPtr<FRarityParameterValueModel> FRarityParameterValueModel::WithWeight(
        const TOptional<int32> Weight
    )
    {
        this->WeightValue = Weight;
        return SharedThis(this);
    }
    TOptional<FString> FRarityParameterValueModel::GetName() const
    {
        return NameValue;
    }
    TOptional<FString> FRarityParameterValueModel::GetMetadata() const
    {
        return MetadataValue;
    }
    TOptional<FString> FRarityParameterValueModel::GetResourceName() const
    {
        return ResourceNameValue;
    }
    TOptional<int64> FRarityParameterValueModel::GetResourceValue() const
    {
        return ResourceValueValue;
    }

    FString FRarityParameterValueModel::GetResourceValueString() const
    {
        if (!ResourceValueValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), ResourceValueValue.GetValue());
    }
    TOptional<int32> FRarityParameterValueModel::GetWeight() const
    {
        return WeightValue;
    }

    FString FRarityParameterValueModel::GetWeightString() const
    {
        if (!WeightValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%d"), WeightValue.GetValue());
    }

    TSharedPtr<FRarityParameterValueModel> FRarityParameterValueModel::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FRarityParameterValueModel>()
            ->WithName(Data->HasField("name") ? [Data]() -> TOptional<FString>
                {
                    FString v;
                    if (Data->TryGetStringField("name", v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithMetadata(Data->HasField("metadata") ? [Data]() -> TOptional<FString>
                {
                    FString v;
                    if (Data->TryGetStringField("metadata", v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithResourceName(Data->HasField("resourceName") ? [Data]() -> TOptional<FString>
                {
                    FString v;
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
                }() : TOptional<int64>())
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

    TSharedPtr<FJsonObject> FRarityParameterValueModel::ToJson() const
    {
        const TSharedPtr<FJsonObject> JsonRootObject = MakeShared<FJsonObject>();
        if (NameValue.IsSet())
        {
            JsonRootObject->SetStringField("name", NameValue.GetValue());
        }
        if (MetadataValue.IsSet())
        {
            JsonRootObject->SetStringField("metadata", MetadataValue.GetValue());
        }
        if (ResourceNameValue.IsSet())
        {
            JsonRootObject->SetStringField("resourceName", ResourceNameValue.GetValue());
        }
        if (ResourceValueValue.IsSet())
        {
            JsonRootObject->SetStringField("resourceValue", FString::Printf(TEXT("%lld"), ResourceValueValue.GetValue()));
        }
        if (WeightValue.IsSet())
        {
            JsonRootObject->SetNumberField("weight", WeightValue.GetValue());
        }
        return JsonRootObject;
    }

    FString FRarityParameterValueModel::TypeName = "RarityParameterValueModel";
}