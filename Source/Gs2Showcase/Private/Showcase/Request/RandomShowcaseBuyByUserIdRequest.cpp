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

#include "Showcase/Request/RandomShowcaseBuyByUserIdRequest.h"

namespace Gs2::Showcase::Request
{
    FRandomShowcaseBuyByUserIdRequest::FRandomShowcaseBuyByUserIdRequest():
        NamespaceNameValue(TOptional<FString>()),
        ShowcaseNameValue(TOptional<FString>()),
        DisplayItemNameValue(TOptional<FString>()),
        UserIdValue(TOptional<FString>()),
        QuantityValue(TOptional<int32>()),
        ConfigValue(nullptr)
    {
    }

    FRandomShowcaseBuyByUserIdRequest::FRandomShowcaseBuyByUserIdRequest(
        const FRandomShowcaseBuyByUserIdRequest& From
    ):
        NamespaceNameValue(From.NamespaceNameValue),
        ShowcaseNameValue(From.ShowcaseNameValue),
        DisplayItemNameValue(From.DisplayItemNameValue),
        UserIdValue(From.UserIdValue),
        QuantityValue(From.QuantityValue),
        ConfigValue(From.ConfigValue)
    {
    }

    TSharedPtr<FRandomShowcaseBuyByUserIdRequest> FRandomShowcaseBuyByUserIdRequest::WithContextStack(
        const TOptional<FString> ContextStack
    )
    {
        this->ContextStackValue = ContextStack;
        return SharedThis(this);
    }

    TSharedPtr<FRandomShowcaseBuyByUserIdRequest> FRandomShowcaseBuyByUserIdRequest::WithNamespaceName(
        const TOptional<FString> NamespaceName
    )
    {
        this->NamespaceNameValue = NamespaceName;
        return SharedThis(this);
    }

    TSharedPtr<FRandomShowcaseBuyByUserIdRequest> FRandomShowcaseBuyByUserIdRequest::WithShowcaseName(
        const TOptional<FString> ShowcaseName
    )
    {
        this->ShowcaseNameValue = ShowcaseName;
        return SharedThis(this);
    }

    TSharedPtr<FRandomShowcaseBuyByUserIdRequest> FRandomShowcaseBuyByUserIdRequest::WithDisplayItemName(
        const TOptional<FString> DisplayItemName
    )
    {
        this->DisplayItemNameValue = DisplayItemName;
        return SharedThis(this);
    }

    TSharedPtr<FRandomShowcaseBuyByUserIdRequest> FRandomShowcaseBuyByUserIdRequest::WithUserId(
        const TOptional<FString> UserId
    )
    {
        this->UserIdValue = UserId;
        return SharedThis(this);
    }

    TSharedPtr<FRandomShowcaseBuyByUserIdRequest> FRandomShowcaseBuyByUserIdRequest::WithQuantity(
        const TOptional<int32> Quantity
    )
    {
        this->QuantityValue = Quantity;
        return SharedThis(this);
    }

    TSharedPtr<FRandomShowcaseBuyByUserIdRequest> FRandomShowcaseBuyByUserIdRequest::WithConfig(
        const TSharedPtr<TArray<TSharedPtr<Model::FConfig>>> Config
    )
    {
        this->ConfigValue = Config;
        return SharedThis(this);
    }

    TSharedPtr<FRandomShowcaseBuyByUserIdRequest> FRandomShowcaseBuyByUserIdRequest::WithDuplicationAvoider(
        const TOptional<FString> DuplicationAvoider
    )
    {
        this->DuplicationAvoiderValue = DuplicationAvoider;
        return SharedThis(this);
    }

    TOptional<FString> FRandomShowcaseBuyByUserIdRequest::GetContextStack() const
    {
        return ContextStackValue;
    }

    TOptional<FString> FRandomShowcaseBuyByUserIdRequest::GetNamespaceName() const
    {
        return NamespaceNameValue;
    }

    TOptional<FString> FRandomShowcaseBuyByUserIdRequest::GetShowcaseName() const
    {
        return ShowcaseNameValue;
    }

    TOptional<FString> FRandomShowcaseBuyByUserIdRequest::GetDisplayItemName() const
    {
        return DisplayItemNameValue;
    }

    TOptional<FString> FRandomShowcaseBuyByUserIdRequest::GetUserId() const
    {
        return UserIdValue;
    }

    TOptional<int32> FRandomShowcaseBuyByUserIdRequest::GetQuantity() const
    {
        return QuantityValue;
    }

    FString FRandomShowcaseBuyByUserIdRequest::GetQuantityString() const
    {
        if (!QuantityValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%d"), QuantityValue.GetValue());
    }

    TSharedPtr<TArray<TSharedPtr<Model::FConfig>>> FRandomShowcaseBuyByUserIdRequest::GetConfig() const
    {
        if (!ConfigValue.IsValid())
        {
            return nullptr;
        }
        return ConfigValue;
    }

    TOptional<FString> FRandomShowcaseBuyByUserIdRequest::GetDuplicationAvoider() const
    {
        return DuplicationAvoiderValue;
    }

    TSharedPtr<FRandomShowcaseBuyByUserIdRequest> FRandomShowcaseBuyByUserIdRequest::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FRandomShowcaseBuyByUserIdRequest>()
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
            ->WithShowcaseName(Data->HasField("showcaseName") ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField("showcaseName", v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
            ->WithDisplayItemName(Data->HasField("displayItemName") ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField("displayItemName", v))
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
              }() : MakeShared<TArray<Model::FConfigPtr>>())
          ->WithDuplicationAvoider(Data->HasField("duplicationAvoider") ? TOptional<FString>(Data->GetStringField("duplicationAvoider")) : TOptional<FString>());
    }

    TSharedPtr<FJsonObject> FRandomShowcaseBuyByUserIdRequest::ToJson() const
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
        if (DisplayItemNameValue.IsSet())
        {
            JsonRootObject->SetStringField("displayItemName", DisplayItemNameValue.GetValue());
        }
        if (UserIdValue.IsSet())
        {
            JsonRootObject->SetStringField("userId", UserIdValue.GetValue());
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