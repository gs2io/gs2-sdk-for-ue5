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

#include "Showcase/Request/BuyRequest.h"

namespace Gs2::Showcase::Request
{
    FBuyRequest::FBuyRequest():
        NamespaceNameValue(TOptional<FString>()),
        ShowcaseNameValue(TOptional<FString>()),
        DisplayItemIdValue(TOptional<FString>()),
        AccessTokenValue(TOptional<FString>()),
        QuantityValue(TOptional<int32>()),
        ConfigValue(nullptr)
    {
    }

    FBuyRequest::FBuyRequest(
        const FBuyRequest& From
    ):
        NamespaceNameValue(From.NamespaceNameValue),
        ShowcaseNameValue(From.ShowcaseNameValue),
        DisplayItemIdValue(From.DisplayItemIdValue),
        AccessTokenValue(From.AccessTokenValue),
        QuantityValue(From.QuantityValue),
        ConfigValue(From.ConfigValue)
    {
    }

    TSharedPtr<FBuyRequest> FBuyRequest::WithContextStack(
        const TOptional<FString> ContextStack
    )
    {
        this->ContextStackValue = ContextStack;
        return SharedThis(this);
    }

    TSharedPtr<FBuyRequest> FBuyRequest::WithNamespaceName(
        const TOptional<FString> NamespaceName
    )
    {
        this->NamespaceNameValue = NamespaceName;
        return SharedThis(this);
    }

    TSharedPtr<FBuyRequest> FBuyRequest::WithShowcaseName(
        const TOptional<FString> ShowcaseName
    )
    {
        this->ShowcaseNameValue = ShowcaseName;
        return SharedThis(this);
    }

    TSharedPtr<FBuyRequest> FBuyRequest::WithDisplayItemId(
        const TOptional<FString> DisplayItemId
    )
    {
        this->DisplayItemIdValue = DisplayItemId;
        return SharedThis(this);
    }

    TSharedPtr<FBuyRequest> FBuyRequest::WithAccessToken(
        const TOptional<FString> AccessToken
    )
    {
        this->AccessTokenValue = AccessToken;
        return SharedThis(this);
    }

    TSharedPtr<FBuyRequest> FBuyRequest::WithQuantity(
        const TOptional<int32> Quantity
    )
    {
        this->QuantityValue = Quantity;
        return SharedThis(this);
    }

    TSharedPtr<FBuyRequest> FBuyRequest::WithConfig(
        const TSharedPtr<TArray<TSharedPtr<Model::FConfig>>> Config
    )
    {
        this->ConfigValue = Config;
        return SharedThis(this);
    }

    TSharedPtr<FBuyRequest> FBuyRequest::WithDuplicationAvoider(
        const TOptional<FString> DuplicationAvoider
    )
    {
        this->DuplicationAvoiderValue = DuplicationAvoider;
        return SharedThis(this);
    }

    TOptional<FString> FBuyRequest::GetContextStack() const
    {
        return ContextStackValue;
    }

    TOptional<FString> FBuyRequest::GetNamespaceName() const
    {
        return NamespaceNameValue;
    }

    TOptional<FString> FBuyRequest::GetShowcaseName() const
    {
        return ShowcaseNameValue;
    }

    TOptional<FString> FBuyRequest::GetDisplayItemId() const
    {
        return DisplayItemIdValue;
    }

    TOptional<FString> FBuyRequest::GetAccessToken() const
    {
        return AccessTokenValue;
    }

    TOptional<int32> FBuyRequest::GetQuantity() const
    {
        return QuantityValue;
    }

    FString FBuyRequest::GetQuantityString() const
    {
        if (!QuantityValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%d"), QuantityValue.GetValue());
    }

    TSharedPtr<TArray<TSharedPtr<Model::FConfig>>> FBuyRequest::GetConfig() const
    {
        if (!ConfigValue.IsValid())
        {
            return nullptr;
        }
        return ConfigValue;
    }

    TOptional<FString> FBuyRequest::GetDuplicationAvoider() const
    {
        return DuplicationAvoiderValue;
    }

    TSharedPtr<FBuyRequest> FBuyRequest::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FBuyRequest>()
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
            ->WithShowcaseName(Data->HasField("showcaseName") ? [Data]() -> TOptional<FString>
              {
                  FString v;
                    if (Data->TryGetStringField("showcaseName", v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
            ->WithDisplayItemId(Data->HasField("displayItemId") ? [Data]() -> TOptional<FString>
              {
                  FString v;
                    if (Data->TryGetStringField("displayItemId", v))
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
            ->WithQuantity(Data->HasField("quantity") ? [Data]() -> TOptional<int32>
              {
                  int32 v;
                    if (Data->TryGetNumberField("quantity", v))
                  {
                        return TOptional(v);
                  }
                  return TOptional<int32>();
              }() : TOptional<int32>())
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

    TSharedPtr<FJsonObject> FBuyRequest::ToJson() const
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
        if (ShowcaseNameValue.IsSet())
        {
            JsonRootObject->SetStringField("showcaseName", ShowcaseNameValue.GetValue());
        }
        if (DisplayItemIdValue.IsSet())
        {
            JsonRootObject->SetStringField("displayItemId", DisplayItemIdValue.GetValue());
        }
        if (AccessTokenValue.IsSet())
        {
            JsonRootObject->SetStringField("xGs2AccessToken", AccessTokenValue.GetValue());
        }
        if (QuantityValue.IsSet())
        {
            JsonRootObject->SetNumberField("quantity", QuantityValue.GetValue());
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