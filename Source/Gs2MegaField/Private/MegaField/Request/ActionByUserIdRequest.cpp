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

#include "MegaField/Request/ActionByUserIdRequest.h"

namespace Gs2::MegaField::Request
{
    FActionByUserIdRequest::FActionByUserIdRequest():
        NamespaceNameValue(TOptional<FString>()),
        UserIdValue(TOptional<FString>()),
        AreaModelNameValue(TOptional<FString>()),
        LayerModelNameValue(TOptional<FString>()),
        PositionValue(nullptr),
        ScopesValue(nullptr)
    {
    }

    FActionByUserIdRequest::FActionByUserIdRequest(
        const FActionByUserIdRequest& From
    ):
        NamespaceNameValue(From.NamespaceNameValue),
        UserIdValue(From.UserIdValue),
        AreaModelNameValue(From.AreaModelNameValue),
        LayerModelNameValue(From.LayerModelNameValue),
        PositionValue(From.PositionValue),
        ScopesValue(From.ScopesValue)
    {
    }

    TSharedPtr<FActionByUserIdRequest> FActionByUserIdRequest::WithContextStack(
        const TOptional<FString> ContextStack
    )
    {
        this->ContextStackValue = ContextStack;
        return SharedThis(this);
    }

    TSharedPtr<FActionByUserIdRequest> FActionByUserIdRequest::WithNamespaceName(
        const TOptional<FString> NamespaceName
    )
    {
        this->NamespaceNameValue = NamespaceName;
        return SharedThis(this);
    }

    TSharedPtr<FActionByUserIdRequest> FActionByUserIdRequest::WithUserId(
        const TOptional<FString> UserId
    )
    {
        this->UserIdValue = UserId;
        return SharedThis(this);
    }

    TSharedPtr<FActionByUserIdRequest> FActionByUserIdRequest::WithAreaModelName(
        const TOptional<FString> AreaModelName
    )
    {
        this->AreaModelNameValue = AreaModelName;
        return SharedThis(this);
    }

    TSharedPtr<FActionByUserIdRequest> FActionByUserIdRequest::WithLayerModelName(
        const TOptional<FString> LayerModelName
    )
    {
        this->LayerModelNameValue = LayerModelName;
        return SharedThis(this);
    }

    TSharedPtr<FActionByUserIdRequest> FActionByUserIdRequest::WithPosition(
        const TSharedPtr<Model::FMyPosition> Position
    )
    {
        this->PositionValue = Position;
        return SharedThis(this);
    }

    TSharedPtr<FActionByUserIdRequest> FActionByUserIdRequest::WithScopes(
        const TSharedPtr<TArray<TSharedPtr<Model::FScope>>> Scopes
    )
    {
        this->ScopesValue = Scopes;
        return SharedThis(this);
    }

    TSharedPtr<FActionByUserIdRequest> FActionByUserIdRequest::WithDuplicationAvoider(
        const TOptional<FString> DuplicationAvoider
    )
    {
        this->DuplicationAvoiderValue = DuplicationAvoider;
        return SharedThis(this);
    }

    TOptional<FString> FActionByUserIdRequest::GetContextStack() const
    {
        return ContextStackValue;
    }

    TOptional<FString> FActionByUserIdRequest::GetNamespaceName() const
    {
        return NamespaceNameValue;
    }

    TOptional<FString> FActionByUserIdRequest::GetUserId() const
    {
        return UserIdValue;
    }

    TOptional<FString> FActionByUserIdRequest::GetAreaModelName() const
    {
        return AreaModelNameValue;
    }

    TOptional<FString> FActionByUserIdRequest::GetLayerModelName() const
    {
        return LayerModelNameValue;
    }

    TSharedPtr<Model::FMyPosition> FActionByUserIdRequest::GetPosition() const
    {
        if (!PositionValue.IsValid())
        {
            return nullptr;
        }
        return PositionValue;
    }

    TSharedPtr<TArray<TSharedPtr<Model::FScope>>> FActionByUserIdRequest::GetScopes() const
    {
        if (!ScopesValue.IsValid())
        {
            return nullptr;
        }
        return ScopesValue;
    }

    TOptional<FString> FActionByUserIdRequest::GetDuplicationAvoider() const
    {
        return DuplicationAvoiderValue;
    }

    TSharedPtr<FActionByUserIdRequest> FActionByUserIdRequest::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FActionByUserIdRequest>()
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
            ->WithUserId(Data->HasField("userId") ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField("userId", v))
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

    TSharedPtr<FJsonObject> FActionByUserIdRequest::ToJson() const
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
        if (UserIdValue.IsSet())
        {
            JsonRootObject->SetStringField("userId", UserIdValue.GetValue());
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