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

#include "MegaField/Request/ActionRequest.h"

namespace Gs2::MegaField::Request
{
    FActionRequest::FActionRequest():
        NamespaceNameValue(TOptional<FString>()),
        AccessTokenValue(TOptional<FString>()),
        AreaModelNameValue(TOptional<FString>()),
        LayerModelNameValue(TOptional<FString>()),
        PositionValue(nullptr),
        ScopesValue(nullptr)
    {
    }

    FActionRequest::FActionRequest(
        const FActionRequest& From
    ):
        NamespaceNameValue(From.NamespaceNameValue),
        AccessTokenValue(From.AccessTokenValue),
        AreaModelNameValue(From.AreaModelNameValue),
        LayerModelNameValue(From.LayerModelNameValue),
        PositionValue(From.PositionValue),
        ScopesValue(From.ScopesValue)
    {
    }

    TSharedPtr<FActionRequest> FActionRequest::WithContextStack(
        const TOptional<FString> ContextStack
    )
    {
        this->ContextStackValue = ContextStack;
        return SharedThis(this);
    }

    TSharedPtr<FActionRequest> FActionRequest::WithNamespaceName(
        const TOptional<FString> NamespaceName
    )
    {
        this->NamespaceNameValue = NamespaceName;
        return SharedThis(this);
    }

    TSharedPtr<FActionRequest> FActionRequest::WithAccessToken(
        const TOptional<FString> AccessToken
    )
    {
        this->AccessTokenValue = AccessToken;
        return SharedThis(this);
    }

    TSharedPtr<FActionRequest> FActionRequest::WithAreaModelName(
        const TOptional<FString> AreaModelName
    )
    {
        this->AreaModelNameValue = AreaModelName;
        return SharedThis(this);
    }

    TSharedPtr<FActionRequest> FActionRequest::WithLayerModelName(
        const TOptional<FString> LayerModelName
    )
    {
        this->LayerModelNameValue = LayerModelName;
        return SharedThis(this);
    }

    TSharedPtr<FActionRequest> FActionRequest::WithPosition(
        const TSharedPtr<Model::FMyPosition> Position
    )
    {
        this->PositionValue = Position;
        return SharedThis(this);
    }

    TSharedPtr<FActionRequest> FActionRequest::WithScopes(
        const TSharedPtr<TArray<TSharedPtr<Model::FScope>>> Scopes
    )
    {
        this->ScopesValue = Scopes;
        return SharedThis(this);
    }

    TSharedPtr<FActionRequest> FActionRequest::WithDuplicationAvoider(
        const TOptional<FString> DuplicationAvoider
    )
    {
        this->DuplicationAvoiderValue = DuplicationAvoider;
        return SharedThis(this);
    }

    TOptional<FString> FActionRequest::GetContextStack() const
    {
        return ContextStackValue;
    }

    TOptional<FString> FActionRequest::GetNamespaceName() const
    {
        return NamespaceNameValue;
    }

    TOptional<FString> FActionRequest::GetAccessToken() const
    {
        return AccessTokenValue;
    }

    TOptional<FString> FActionRequest::GetAreaModelName() const
    {
        return AreaModelNameValue;
    }

    TOptional<FString> FActionRequest::GetLayerModelName() const
    {
        return LayerModelNameValue;
    }

    TSharedPtr<Model::FMyPosition> FActionRequest::GetPosition() const
    {
        if (!PositionValue.IsValid())
        {
            return nullptr;
        }
        return PositionValue;
    }

    TSharedPtr<TArray<TSharedPtr<Model::FScope>>> FActionRequest::GetScopes() const
    {
        if (!ScopesValue.IsValid())
        {
            return nullptr;
        }
        return ScopesValue;
    }

    TOptional<FString> FActionRequest::GetDuplicationAvoider() const
    {
        return DuplicationAvoiderValue;
    }

    TSharedPtr<FActionRequest> FActionRequest::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FActionRequest>()
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
            ->WithAccessToken(Data->HasField("xGs2AccessToken") ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField("xGs2AccessToken", v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
            ->WithAreaModelName(Data->HasField("areaModelName") ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField("areaModelName", v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
            ->WithLayerModelName(Data->HasField("layerModelName") ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField("layerModelName", v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
          ->WithPosition(Data->HasField("position") ? [Data]() -> Model::FMyPositionPtr
              {
                  if (Data->HasTypedField<EJson::Null>("position"))
                  {
                      return nullptr;
                  }
                  return Model::FMyPosition::FromJson(Data->GetObjectField("position"));
             }() : nullptr)
          ->WithScopes(Data->HasField("scopes") ? [Data]() -> TSharedPtr<TArray<Model::FScopePtr>>
              {
                  auto v = MakeShared<TArray<Model::FScopePtr>>();
                  if (!Data->HasTypedField<EJson::Null>("scopes") && Data->HasTypedField<EJson::Array>("scopes"))
                  {
                      for (auto JsonObjectValue : Data->GetArrayField("scopes"))
                      {
                          v->Add(Model::FScope::FromJson(JsonObjectValue->AsObject()));
                      }
                  }
                  return v;
             }() : nullptr)
          ->WithDuplicationAvoider(Data->HasField("duplicationAvoider") ? TOptional<FString>(Data->GetStringField("duplicationAvoider")) : TOptional<FString>());
    }

    TSharedPtr<FJsonObject> FActionRequest::ToJson() const
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
        if (AccessTokenValue.IsSet())
        {
            JsonRootObject->SetStringField("xGs2AccessToken", AccessTokenValue.GetValue());
        }
        if (AreaModelNameValue.IsSet())
        {
            JsonRootObject->SetStringField("areaModelName", AreaModelNameValue.GetValue());
        }
        if (LayerModelNameValue.IsSet())
        {
            JsonRootObject->SetStringField("layerModelName", LayerModelNameValue.GetValue());
        }
        if (PositionValue != nullptr && PositionValue.IsValid())
        {
            JsonRootObject->SetObjectField("position", PositionValue->ToJson());
        }
        if (ScopesValue != nullptr && ScopesValue.IsValid())
        {
            TArray<TSharedPtr<FJsonValue>> v;
            for (auto JsonObjectValue : *ScopesValue)
            {
                v.Add(MakeShared<FJsonValueObject>(JsonObjectValue->ToJson()));
            }
            JsonRootObject->SetArrayField("scopes", v);
        }
        if (DuplicationAvoiderValue.IsSet())
        {
            JsonRootObject->SetStringField("duplicationAvoider", DuplicationAvoiderValue.GetValue());
        }
        return JsonRootObject;
    }
}