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

#include "Enhance/Model/UnleashQuantityMaterialSetting.h"

namespace Gs2::Enhance::Model
{
    FUnleashQuantityMaterialSetting::FUnleashQuantityMaterialSetting():
        MatchTypeValue(TOptional<FString>()),
        MaterialInventoryModelIdValue(TOptional<FString>()),
        ItemModelIdValue(TOptional<FString>()),
        CountValue(TOptional<int32>())
    {
    }

    FUnleashQuantityMaterialSetting::FUnleashQuantityMaterialSetting(
        const FUnleashQuantityMaterialSetting& From
    ):
        MatchTypeValue(From.MatchTypeValue),
        MaterialInventoryModelIdValue(From.MaterialInventoryModelIdValue),
        ItemModelIdValue(From.ItemModelIdValue),
        CountValue(From.CountValue)
    {
    }

    TSharedPtr<FUnleashQuantityMaterialSetting> FUnleashQuantityMaterialSetting::WithMatchType(
        const TOptional<FString> MatchType
    )
    {
        this->MatchTypeValue = MatchType;
        return SharedThis(this);
    }

    TSharedPtr<FUnleashQuantityMaterialSetting> FUnleashQuantityMaterialSetting::WithMaterialInventoryModelId(
        const TOptional<FString> MaterialInventoryModelId
    )
    {
        this->MaterialInventoryModelIdValue = MaterialInventoryModelId;
        return SharedThis(this);
    }

    TSharedPtr<FUnleashQuantityMaterialSetting> FUnleashQuantityMaterialSetting::WithItemModelId(
        const TOptional<FString> ItemModelId
    )
    {
        this->ItemModelIdValue = ItemModelId;
        return SharedThis(this);
    }

    TSharedPtr<FUnleashQuantityMaterialSetting> FUnleashQuantityMaterialSetting::WithCount(
        const TOptional<int32> Count
    )
    {
        this->CountValue = Count;
        return SharedThis(this);
    }
    TOptional<FString> FUnleashQuantityMaterialSetting::GetMatchType() const
    {
        return MatchTypeValue;
    }
    TOptional<FString> FUnleashQuantityMaterialSetting::GetMaterialInventoryModelId() const
    {
        return MaterialInventoryModelIdValue;
    }
    TOptional<FString> FUnleashQuantityMaterialSetting::GetItemModelId() const
    {
        return ItemModelIdValue;
    }
    TOptional<int32> FUnleashQuantityMaterialSetting::GetCount() const
    {
        return CountValue;
    }

    FString FUnleashQuantityMaterialSetting::GetCountString() const
    {
        if (!CountValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%d"), CountValue.GetValue());
    }

    TSharedPtr<FUnleashQuantityMaterialSetting> FUnleashQuantityMaterialSetting::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FUnleashQuantityMaterialSetting>()
            ->WithMatchType(Data->HasField(ANSI_TO_TCHAR("matchType")) ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("matchType"), v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithMaterialInventoryModelId(Data->HasField(ANSI_TO_TCHAR("materialInventoryModelId")) ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("materialInventoryModelId"), v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithItemModelId(Data->HasField(ANSI_TO_TCHAR("itemModelId")) ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("itemModelId"), v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithCount(Data->HasField(ANSI_TO_TCHAR("count")) ? [Data]() -> TOptional<int32>
                {
                    int32 v;
                    if (Data->TryGetNumberField(ANSI_TO_TCHAR("count"), v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<int32>();
                }() : TOptional<int32>());
    }

    TSharedPtr<FJsonObject> FUnleashQuantityMaterialSetting::ToJson() const
    {
        const TSharedPtr<FJsonObject> JsonRootObject = MakeShared<FJsonObject>();
        if (MatchTypeValue.IsSet())
        {
            JsonRootObject->SetStringField(TEXT("matchType"), MatchTypeValue.GetValue());
        }
        if (MaterialInventoryModelIdValue.IsSet())
        {
            JsonRootObject->SetStringField(TEXT("materialInventoryModelId"), MaterialInventoryModelIdValue.GetValue());
        }
        if (ItemModelIdValue.IsSet())
        {
            JsonRootObject->SetStringField(TEXT("itemModelId"), ItemModelIdValue.GetValue());
        }
        if (CountValue.IsSet())
        {
            JsonRootObject->SetNumberField(TEXT("count"), CountValue.GetValue());
        }
        return JsonRootObject;
    }

    FString FUnleashQuantityMaterialSetting::TypeName = "UnleashQuantityMaterialSetting";
}