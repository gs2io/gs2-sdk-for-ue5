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

#include "MegaField/Request/FetchPositionRequest.h"

namespace Gs2::MegaField::Request
{
    FFetchPositionRequest::FFetchPositionRequest():
        NamespaceNameValue(TOptional<FString>()),
        AccessTokenValue(TOptional<FString>()),
        AreaModelNameValue(TOptional<FString>()),
        LayerModelNameValue(TOptional<FString>()),
        UserIdsValue(nullptr)
    {
    }

    FFetchPositionRequest::FFetchPositionRequest(
        const FFetchPositionRequest& From
    ):
        NamespaceNameValue(From.NamespaceNameValue),
        AccessTokenValue(From.AccessTokenValue),
        AreaModelNameValue(From.AreaModelNameValue),
        LayerModelNameValue(From.LayerModelNameValue),
        UserIdsValue(From.UserIdsValue)
    {
    }

    TSharedPtr<FFetchPositionRequest> FFetchPositionRequest::WithContextStack(
        const TOptional<FString> ContextStack
    )
    {
        this->ContextStackValue = ContextStack;
        return SharedThis(this);
    }

    TSharedPtr<FFetchPositionRequest> FFetchPositionRequest::WithNamespaceName(
        const TOptional<FString> NamespaceName
    )
    {
        this->NamespaceNameValue = NamespaceName;
        return SharedThis(this);
    }

    TSharedPtr<FFetchPositionRequest> FFetchPositionRequest::WithAccessToken(
        const TOptional<FString> AccessToken
    )
    {
        this->AccessTokenValue = AccessToken;
        return SharedThis(this);
    }

    TSharedPtr<FFetchPositionRequest> FFetchPositionRequest::WithAreaModelName(
        const TOptional<FString> AreaModelName
    )
    {
        this->AreaModelNameValue = AreaModelName;
        return SharedThis(this);
    }

    TSharedPtr<FFetchPositionRequest> FFetchPositionRequest::WithLayerModelName(
        const TOptional<FString> LayerModelName
    )
    {
        this->LayerModelNameValue = LayerModelName;
        return SharedThis(this);
    }

    TSharedPtr<FFetchPositionRequest> FFetchPositionRequest::WithUserIds(
        const TSharedPtr<TArray<FString>> UserIds
    )
    {
        this->UserIdsValue = UserIds;
        return SharedThis(this);
    }

    TSharedPtr<FFetchPositionRequest> FFetchPositionRequest::WithDuplicationAvoider(
        const TOptional<FString> DuplicationAvoider
    )
    {
        this->DuplicationAvoiderValue = DuplicationAvoider;
        return SharedThis(this);
    }

    TOptional<FString> FFetchPositionRequest::GetContextStack() const
    {
        return ContextStackValue;
    }

    TOptional<FString> FFetchPositionRequest::GetNamespaceName() const
    {
        return NamespaceNameValue;
    }

    TOptional<FString> FFetchPositionRequest::GetAccessToken() const
    {
        return AccessTokenValue;
    }

    TOptional<FString> FFetchPositionRequest::GetAreaModelName() const
    {
        return AreaModelNameValue;
    }

    TOptional<FString> FFetchPositionRequest::GetLayerModelName() const
    {
        return LayerModelNameValue;
    }

    TSharedPtr<TArray<FString>> FFetchPositionRequest::GetUserIds() const
    {
        if (!UserIdsValue.IsValid())
        {
            return nullptr;
        }
        return UserIdsValue;
    }

    TOptional<FString> FFetchPositionRequest::GetDuplicationAvoider() const
    {
        return DuplicationAvoiderValue;
    }

    TSharedPtr<FFetchPositionRequest> FFetchPositionRequest::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FFetchPositionRequest>()
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
          ->WithUserIds(Data->HasField("userIds") ? [Data]() -> TSharedPtr<TArray<FString>>
              {
                  auto v = MakeShared<TArray<FString>>();
                  if (!Data->HasTypedField<EJson::Null>("userIds") && Data->HasTypedField<EJson::Array>("userIds"))
                  {
                      for (auto JsonObjectValue : Data->GetArrayField("userIds"))
                      {
                          v->Add(JsonObjectValue->AsString());
                      }
                  }
                  return v;
             }() : nullptr)
          ->WithDuplicationAvoider(Data->HasField("duplicationAvoider") ? TOptional<FString>(Data->GetStringField("duplicationAvoider")) : TOptional<FString>());
    }

    TSharedPtr<FJsonObject> FFetchPositionRequest::ToJson() const
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
        if (UserIdsValue != nullptr && UserIdsValue.IsValid())
        {
            TArray<TSharedPtr<FJsonValue>> v;
            for (auto JsonObjectValue : *UserIdsValue)
            {
                v.Add(MakeShared<FJsonValueString>(JsonObjectValue));
            }
            JsonRootObject->SetArrayField("userIds", v);
        }
        if (DuplicationAvoiderValue.IsSet())
        {
            JsonRootObject->SetStringField("duplicationAvoider", DuplicationAvoiderValue.GetValue());
        }
        return JsonRootObject;
    }
}