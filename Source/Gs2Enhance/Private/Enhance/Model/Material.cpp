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

#include "Enhance/Model/Material.h"

namespace Gs2::Enhance::Model
{
    FMaterial::FMaterial():
        MaterialItemSetIdValue(TOptional<FString>()),
        CountValue(TOptional<int32>())
    {
    }

    FMaterial::FMaterial(
        const FMaterial& From
    ):
        MaterialItemSetIdValue(From.MaterialItemSetIdValue),
        CountValue(From.CountValue)
    {
    }

    TSharedPtr<FMaterial> FMaterial::WithMaterialItemSetId(
        const TOptional<FString> MaterialItemSetId
    )
    {
        this->MaterialItemSetIdValue = MaterialItemSetId;
        return SharedThis(this);
    }

    TSharedPtr<FMaterial> FMaterial::WithCount(
        const TOptional<int32> Count
    )
    {
        this->CountValue = Count;
        return SharedThis(this);
    }
    TOptional<FString> FMaterial::GetMaterialItemSetId() const
    {
        return MaterialItemSetIdValue;
    }
    TOptional<int32> FMaterial::GetCount() const
    {
        return CountValue;
    }

    FString FMaterial::GetCountString() const
    {
        if (!CountValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%d"), CountValue.GetValue());
    }

    TSharedPtr<FMaterial> FMaterial::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FMaterial>()
            ->WithMaterialItemSetId(Data->HasField("materialItemSetId") ? [Data]() -> TOptional<FString>
                {
                    FString v;
                    if (Data->TryGetStringField("materialItemSetId", v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithCount(Data->HasField("count") ? [Data]() -> TOptional<int32>
                {
                    int32 v;
                    if (Data->TryGetNumberField("count", v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<int32>();
                }() : TOptional<int32>());
    }

    TSharedPtr<FJsonObject> FMaterial::ToJson() const
    {
        const TSharedPtr<FJsonObject> JsonRootObject = MakeShared<FJsonObject>();
        if (MaterialItemSetIdValue.IsSet())
        {
            JsonRootObject->SetStringField("materialItemSetId", MaterialItemSetIdValue.GetValue());
        }
        if (CountValue.IsSet())
        {
            JsonRootObject->SetNumberField("count", CountValue.GetValue());
        }
        return JsonRootObject;
    }

    FString FMaterial::TypeName = "Material";
}