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

#include "AdReward/Model/AdMob.h"

namespace Gs2::AdReward::Model
{
    FAdMob::FAdMob():
        AllowAdUnitIdsValue(nullptr)
    {
    }

    FAdMob::FAdMob(
        const FAdMob& From
    ):
        AllowAdUnitIdsValue(From.AllowAdUnitIdsValue)
    {
    }

    TSharedPtr<FAdMob> FAdMob::WithAllowAdUnitIds(
        const TSharedPtr<TArray<FString>> AllowAdUnitIds
    )
    {
        this->AllowAdUnitIdsValue = AllowAdUnitIds;
        return SharedThis(this);
    }
    TSharedPtr<TArray<FString>> FAdMob::GetAllowAdUnitIds() const
    {
        return AllowAdUnitIdsValue;
    }

    TSharedPtr<FAdMob> FAdMob::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FAdMob>()
            ->WithAllowAdUnitIds(Data->HasField("allowAdUnitIds") ? [Data]() -> TSharedPtr<TArray<FString>>
                {
                    auto v = MakeShared<TArray<FString>>();
                    if (!Data->HasTypedField<EJson::Null>("allowAdUnitIds") && Data->HasTypedField<EJson::Array>("allowAdUnitIds"))
                    {
                        for (auto JsonObjectValue : Data->GetArrayField("allowAdUnitIds"))
                        {
                            v->Add(JsonObjectValue->AsString());
                        }
                    }
                    return v;
                 }() : MakeShared<TArray<FString>>());
    }

    TSharedPtr<FJsonObject> FAdMob::ToJson() const
    {
        const TSharedPtr<FJsonObject> JsonRootObject = MakeShared<FJsonObject>();
        if (AllowAdUnitIdsValue != nullptr && AllowAdUnitIdsValue.IsValid())
        {
            TArray<TSharedPtr<FJsonValue>> v;
            for (auto JsonObjectValue : *AllowAdUnitIdsValue)
            {
                v.Add(MakeShared<FJsonValueString>(JsonObjectValue));
            }
            JsonRootObject->SetArrayField("allowAdUnitIds", v);
        }
        return JsonRootObject;
    }

    FString FAdMob::TypeName = "AdMob";
}