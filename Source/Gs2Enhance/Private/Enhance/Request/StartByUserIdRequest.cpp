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

#include "Enhance/Request/StartByUserIdRequest.h"

namespace Gs2::Enhance::Request
{
    FStartByUserIdRequest::FStartByUserIdRequest():
        NamespaceNameValue(TOptional<FString>()),
        RateNameValue(TOptional<FString>()),
        TargetItemSetIdValue(TOptional<FString>()),
        MaterialsValue(nullptr),
        UserIdValue(TOptional<FString>()),
        ForceValue(TOptional<bool>()),
        ConfigValue(nullptr)
    {
    }

    FStartByUserIdRequest::FStartByUserIdRequest(
        const FStartByUserIdRequest& From
    ):
        NamespaceNameValue(From.NamespaceNameValue),
        RateNameValue(From.RateNameValue),
        TargetItemSetIdValue(From.TargetItemSetIdValue),
        MaterialsValue(From.MaterialsValue),
        UserIdValue(From.UserIdValue),
        ForceValue(From.ForceValue),
        ConfigValue(From.ConfigValue)
    {
    }

    TSharedPtr<FStartByUserIdRequest> FStartByUserIdRequest::WithContextStack(
        const TOptional<FString> ContextStack
    )
    {
        this->ContextStackValue = ContextStack;
        return SharedThis(this);
    }

    TSharedPtr<FStartByUserIdRequest> FStartByUserIdRequest::WithNamespaceName(
        const TOptional<FString> NamespaceName
    )
    {
        this->NamespaceNameValue = NamespaceName;
        return SharedThis(this);
    }

    TSharedPtr<FStartByUserIdRequest> FStartByUserIdRequest::WithRateName(
        const TOptional<FString> RateName
    )
    {
        this->RateNameValue = RateName;
        return SharedThis(this);
    }

    TSharedPtr<FStartByUserIdRequest> FStartByUserIdRequest::WithTargetItemSetId(
        const TOptional<FString> TargetItemSetId
    )
    {
        this->TargetItemSetIdValue = TargetItemSetId;
        return SharedThis(this);
    }

    TSharedPtr<FStartByUserIdRequest> FStartByUserIdRequest::WithMaterials(
        const TSharedPtr<TArray<TSharedPtr<Model::FMaterial>>> Materials
    )
    {
        this->MaterialsValue = Materials;
        return SharedThis(this);
    }

    TSharedPtr<FStartByUserIdRequest> FStartByUserIdRequest::WithUserId(
        const TOptional<FString> UserId
    )
    {
        this->UserIdValue = UserId;
        return SharedThis(this);
    }

    TSharedPtr<FStartByUserIdRequest> FStartByUserIdRequest::WithForce(
        const TOptional<bool> Force
    )
    {
        this->ForceValue = Force;
        return SharedThis(this);
    }

    TSharedPtr<FStartByUserIdRequest> FStartByUserIdRequest::WithConfig(
        const TSharedPtr<TArray<TSharedPtr<Model::FConfig>>> Config
    )
    {
        this->ConfigValue = Config;
        return SharedThis(this);
    }

    TSharedPtr<FStartByUserIdRequest> FStartByUserIdRequest::WithDuplicationAvoider(
        const TOptional<FString> DuplicationAvoider
    )
    {
        this->DuplicationAvoiderValue = DuplicationAvoider;
        return SharedThis(this);
    }

    TOptional<FString> FStartByUserIdRequest::GetContextStack() const
    {
        return ContextStackValue;
    }

    TOptional<FString> FStartByUserIdRequest::GetNamespaceName() const
    {
        return NamespaceNameValue;
    }

    TOptional<FString> FStartByUserIdRequest::GetRateName() const
    {
        return RateNameValue;
    }

    TOptional<FString> FStartByUserIdRequest::GetTargetItemSetId() const
    {
        return TargetItemSetIdValue;
    }

    TSharedPtr<TArray<TSharedPtr<Model::FMaterial>>> FStartByUserIdRequest::GetMaterials() const
    {
        if (!MaterialsValue.IsValid())
        {
            return nullptr;
        }
        return MaterialsValue;
    }

    TOptional<FString> FStartByUserIdRequest::GetUserId() const
    {
        return UserIdValue;
    }

    TOptional<bool> FStartByUserIdRequest::GetForce() const
    {
        return ForceValue;
    }

    FString FStartByUserIdRequest::GetForceString() const
    {
        if (!ForceValue.IsSet())
        {
            return FString("null");
        }
        return FString(ForceValue.GetValue() ? "true" : "false");
    }

    TSharedPtr<TArray<TSharedPtr<Model::FConfig>>> FStartByUserIdRequest::GetConfig() const
    {
        if (!ConfigValue.IsValid())
        {
            return nullptr;
        }
        return ConfigValue;
    }

    TOptional<FString> FStartByUserIdRequest::GetDuplicationAvoider() const
    {
        return DuplicationAvoiderValue;
    }

    TSharedPtr<FStartByUserIdRequest> FStartByUserIdRequest::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FStartByUserIdRequest>()
            ->WithContextStack(Data->HasField("contextStack") ? TOptional<FString>(Data->GetStringField("contextStack")) : TOptional<FString>())
            ->WithNamespaceName(Data->HasField("namespaceName") ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField("namespaceName", v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
            ->WithRateName(Data->HasField("rateName") ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField("rateName", v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
            ->WithTargetItemSetId(Data->HasField("targetItemSetId") ? [Data]() -> TOptional<FString>
              {
                  FString v("");
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
            ->WithUserId(Data->HasField("userId") ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField("userId", v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
            ->WithForce(Data->HasField("force") ? [Data]() -> TOptional<bool>
              {
                  bool v;
                    if (Data->TryGetBoolField("force", v))
                  {
                        return TOptional(v);
                  }
                  return TOptional<bool>();
              }() : TOptional<bool>())
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

    TSharedPtr<FJsonObject> FStartByUserIdRequest::ToJson() const
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
        if (UserIdValue.IsSet())
        {
            JsonRootObject->SetStringField("userId", UserIdValue.GetValue());
        }
        if (ForceValue.IsSet())
        {
            JsonRootObject->SetBoolField("force", ForceValue.GetValue());
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