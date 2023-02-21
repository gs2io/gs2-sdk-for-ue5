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

#include "Enhance/Request/DirectEnhanceRequest.h"

namespace Gs2::Enhance::Request
{
    FDirectEnhanceRequest::FDirectEnhanceRequest():
        NamespaceNameValue(TOptional<FString>()),
        RateNameValue(TOptional<FString>()),
        AccessTokenValue(TOptional<FString>()),
        TargetItemSetIdValue(TOptional<FString>()),
        MaterialsValue(nullptr),
        ConfigValue(nullptr)
    {
    }

    FDirectEnhanceRequest::FDirectEnhanceRequest(
        const FDirectEnhanceRequest& From
    ):
        NamespaceNameValue(From.NamespaceNameValue),
        RateNameValue(From.RateNameValue),
        AccessTokenValue(From.AccessTokenValue),
        TargetItemSetIdValue(From.TargetItemSetIdValue),
        MaterialsValue(From.MaterialsValue),
        ConfigValue(From.ConfigValue)
    {
    }

    TSharedPtr<FDirectEnhanceRequest> FDirectEnhanceRequest::WithContextStack(
        const TOptional<FString> ContextStack
    )
    {
        this->ContextStackValue = ContextStack;
        return SharedThis(this);
    }

    TSharedPtr<FDirectEnhanceRequest> FDirectEnhanceRequest::WithNamespaceName(
        const TOptional<FString> NamespaceName
    )
    {
        this->NamespaceNameValue = NamespaceName;
        return SharedThis(this);
    }

    TSharedPtr<FDirectEnhanceRequest> FDirectEnhanceRequest::WithRateName(
        const TOptional<FString> RateName
    )
    {
        this->RateNameValue = RateName;
        return SharedThis(this);
    }

    TSharedPtr<FDirectEnhanceRequest> FDirectEnhanceRequest::WithAccessToken(
        const TOptional<FString> AccessToken
    )
    {
        this->AccessTokenValue = AccessToken;
        return SharedThis(this);
    }

    TSharedPtr<FDirectEnhanceRequest> FDirectEnhanceRequest::WithTargetItemSetId(
        const TOptional<FString> TargetItemSetId
    )
    {
        this->TargetItemSetIdValue = TargetItemSetId;
        return SharedThis(this);
    }

    TSharedPtr<FDirectEnhanceRequest> FDirectEnhanceRequest::WithMaterials(
        const TSharedPtr<TArray<TSharedPtr<Model::FMaterial>>> Materials
    )
    {
        this->MaterialsValue = Materials;
        return SharedThis(this);
    }

    TSharedPtr<FDirectEnhanceRequest> FDirectEnhanceRequest::WithConfig(
        const TSharedPtr<TArray<TSharedPtr<Model::FConfig>>> Config
    )
    {
        this->ConfigValue = Config;
        return SharedThis(this);
    }

    TSharedPtr<FDirectEnhanceRequest> FDirectEnhanceRequest::WithDuplicationAvoider(
        const TOptional<FString> DuplicationAvoider
    )
    {
        this->DuplicationAvoiderValue = DuplicationAvoider;
        return SharedThis(this);
    }

    TOptional<FString> FDirectEnhanceRequest::GetContextStack() const
    {
        return ContextStackValue;
    }

    TOptional<FString> FDirectEnhanceRequest::GetNamespaceName() const
    {
        return NamespaceNameValue;
    }

    TOptional<FString> FDirectEnhanceRequest::GetRateName() const
    {
        return RateNameValue;
    }

    TOptional<FString> FDirectEnhanceRequest::GetAccessToken() const
    {
        return AccessTokenValue;
    }

    TOptional<FString> FDirectEnhanceRequest::GetTargetItemSetId() const
    {
        return TargetItemSetIdValue;
    }

    TSharedPtr<TArray<TSharedPtr<Model::FMaterial>>> FDirectEnhanceRequest::GetMaterials() const
    {
        if (!MaterialsValue.IsValid())
        {
            return nullptr;
        }
        return MaterialsValue;
    }

    TSharedPtr<TArray<TSharedPtr<Model::FConfig>>> FDirectEnhanceRequest::GetConfig() const
    {
        if (!ConfigValue.IsValid())
        {
            return nullptr;
        }
        return ConfigValue;
    }

    TOptional<FString> FDirectEnhanceRequest::GetDuplicationAvoider() const
    {
        return DuplicationAvoiderValue;
    }

    TSharedPtr<FDirectEnhanceRequest> FDirectEnhanceRequest::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FDirectEnhanceRequest>()
            ->WithContextStack(Data->HasField("contextStack") ? TOptional<FString>(Data->GetStringField("contextStack")) : TOptional<FString>())
            ->WithNamespaceName(Data->HasField("namespaceName") ? [Data]() -> TOptional<FString>
              {
                  FString v;
                    if (Data->TryGetStringField("namespaceName", v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
            ->WithRateName(Data->HasField("rateName") ? [Data]() -> TOptional<FString>
              {
                  FString v;
                    if (Data->TryGetStringField("rateName", v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
            ->WithAccessToken(Data->HasField("xGs2AccessToken") ? [Data]() -> TOptional<FString>
              {
                  FString v;
                    if (Data->TryGetStringField("xGs2AccessToken", v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
            ->WithTargetItemSetId(Data->HasField("targetItemSetId") ? [Data]() -> TOptional<FString>
              {
                  FString v;
                    if (Data->TryGetStringField("targetItemSetId", v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
          ->WithMaterials(Data->HasField("materials") ? [Data]() -> TSharedPtr<TArray<Model::FMaterialPtr>>
              {
                  auto v = MakeShared<TArray<Model::FMaterialPtr>>();
                  if (!Data->HasTypedField<EJson::Null>("materials") && Data->HasTypedField<EJson::Array>("materials"))
                  {
                      for (auto JsonObjectValue : Data->GetArrayField("materials"))
                      {
                          v->Add(Model::FMaterial::FromJson(JsonObjectValue->AsObject()));
                      }
                  }
                  return v;
             }() : nullptr)
          ->WithConfig(Data->HasField("config") ? [Data]() -> TSharedPtr<TArray<Model::FConfigPtr>>
              {
                  auto v = MakeShared<TArray<Model::FConfigPtr>>();
                  if (!Data->HasTypedField<EJson::Null>("config") && Data->HasTypedField<EJson::Array>("config"))
                  {
                      for (auto JsonObjectValue : Data->GetArrayField("config"))
                      {
                          v->Add(Model::FConfig::FromJson(JsonObjectValue->AsObject()));
                      }
                  }
                  return v;
             }() : nullptr)
          ->WithDuplicationAvoider(Data->HasField("duplicationAvoider") ? TOptional<FString>(Data->GetStringField("duplicationAvoider")) : TOptional<FString>());
    }

    TSharedPtr<FJsonObject> FDirectEnhanceRequest::ToJson() const
    {
        const TSharedPtr<FJsonObject> JsonRootObject = MakeShared<FJsonObject>();
        if (ContextStackValue.IsSet())
        {
            JsonRootObject->SetStringField("contextStack", ContextStackValue.GetValue());
        }
        if (NamespaceNameValue.IsSet())
        {
            JsonRootObject->SetStringField("namespaceName", NamespaceNameValue.GetValue());
        }
        if (RateNameValue.IsSet())
        {
            JsonRootObject->SetStringField("rateName", RateNameValue.GetValue());
        }
        if (AccessTokenValue.IsSet())
        {
            JsonRootObject->SetStringField("xGs2AccessToken", AccessTokenValue.GetValue());
        }
        if (TargetItemSetIdValue.IsSet())
        {
            JsonRootObject->SetStringField("targetItemSetId", TargetItemSetIdValue.GetValue());
        }
        if (MaterialsValue != nullptr && MaterialsValue.IsValid())
        {
            TArray<TSharedPtr<FJsonValue>> v;
            for (auto JsonObjectValue : *MaterialsValue)
            {
                v.Add(MakeShared<FJsonValueObject>(JsonObjectValue->ToJson()));
            }
            JsonRootObject->SetArrayField("materials", v);
        }
        if (ConfigValue != nullptr && ConfigValue.IsValid())
        {
            TArray<TSharedPtr<FJsonValue>> v;
            for (auto JsonObjectValue : *ConfigValue)
            {
                v.Add(MakeShared<FJsonValueObject>(JsonObjectValue->ToJson()));
            }
            JsonRootObject->SetArrayField("config", v);
        }
        if (DuplicationAvoiderValue.IsSet())
        {
            JsonRootObject->SetStringField("duplicationAvoider", DuplicationAvoiderValue.GetValue());
        }
        return JsonRootObject;
    }
}