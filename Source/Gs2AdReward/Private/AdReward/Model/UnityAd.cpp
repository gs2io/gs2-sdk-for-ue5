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

#include "AdReward/Model/UnityAd.h"

namespace Gs2::AdReward::Model
{
    FUnityAd::FUnityAd():
        KeysValue(nullptr)
    {
    }

    FUnityAd::FUnityAd(
        const FUnityAd& From
    ):
        KeysValue(From.KeysValue)
    {
    }

    TSharedPtr<FUnityAd> FUnityAd::WithKeys(
        const TSharedPtr<TArray<FString>> Keys
    )
    {
        this->KeysValue = Keys;
        return SharedThis(this);
    }
    TSharedPtr<TArray<FString>> FUnityAd::GetKeys() const
    {
        return KeysValue;
    }

    TSharedPtr<FUnityAd> FUnityAd::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FUnityAd>()
            ->WithKeys(Data->HasField(ANSI_TO_TCHAR("keys")) ? [Data]() -> TSharedPtr<TArray<FString>>
                {
                    auto v = MakeShared<TArray<FString>>();
                    if (!Data->HasTypedField<EJson::Null>(ANSI_TO_TCHAR("keys")) && Data->HasTypedField<EJson::Array>(ANSI_TO_TCHAR("keys")))
                    {
                        for (auto JsonObjectValue : Data->GetArrayField(ANSI_TO_TCHAR("keys")))
                        {
                            v->Add(JsonObjectValue->AsString());
                        }
                    }
                    return v;
                 }() : MakeShared<TArray<FString>>());
    }

    TSharedPtr<FJsonObject> FUnityAd::ToJson() const
    {
        const TSharedPtr<FJsonObject> JsonRootObject = MakeShared<FJsonObject>();
        if (KeysValue != nullptr && KeysValue.IsValid())
        {
            TArray<TSharedPtr<FJsonValue>> v;
            for (auto JsonObjectValue : *KeysValue)
            {
                v.Add(MakeShared<FJsonValueString>(JsonObjectValue));
            }
            JsonRootObject->SetArrayField("keys", v);
        }
        return JsonRootObject;
    }

    FString FUnityAd::TypeName = "UnityAd";
}