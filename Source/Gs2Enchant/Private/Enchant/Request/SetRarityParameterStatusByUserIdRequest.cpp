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

#include "Enchant/Request/SetRarityParameterStatusByUserIdRequest.h"

namespace Gs2::Enchant::Request
{
    FSetRarityParameterStatusByUserIdRequest::FSetRarityParameterStatusByUserIdRequest():
        NamespaceNameValue(TOptional<FString>()),
        UserIdValue(TOptional<FString>()),
        ParameterNameValue(TOptional<FString>()),
        PropertyIdValue(TOptional<FString>()),
        ParameterValuesValue(nullptr)
    {
    }

    FSetRarityParameterStatusByUserIdRequest::FSetRarityParameterStatusByUserIdRequest(
        const FSetRarityParameterStatusByUserIdRequest& From
    ):
        NamespaceNameValue(From.NamespaceNameValue),
        UserIdValue(From.UserIdValue),
        ParameterNameValue(From.ParameterNameValue),
        PropertyIdValue(From.PropertyIdValue),
        ParameterValuesValue(From.ParameterValuesValue)
    {
    }

    TSharedPtr<FSetRarityParameterStatusByUserIdRequest> FSetRarityParameterStatusByUserIdRequest::WithContextStack(
        const TOptional<FString> ContextStack
    )
    {
        this->ContextStackValue = ContextStack;
        return SharedThis(this);
    }

    TSharedPtr<FSetRarityParameterStatusByUserIdRequest> FSetRarityParameterStatusByUserIdRequest::WithNamespaceName(
        const TOptional<FString> NamespaceName
    )
    {
        this->NamespaceNameValue = NamespaceName;
        return SharedThis(this);
    }

    TSharedPtr<FSetRarityParameterStatusByUserIdRequest> FSetRarityParameterStatusByUserIdRequest::WithUserId(
        const TOptional<FString> UserId
    )
    {
        this->UserIdValue = UserId;
        return SharedThis(this);
    }

    TSharedPtr<FSetRarityParameterStatusByUserIdRequest> FSetRarityParameterStatusByUserIdRequest::WithParameterName(
        const TOptional<FString> ParameterName
    )
    {
        this->ParameterNameValue = ParameterName;
        return SharedThis(this);
    }

    TSharedPtr<FSetRarityParameterStatusByUserIdRequest> FSetRarityParameterStatusByUserIdRequest::WithPropertyId(
        const TOptional<FString> PropertyId
    )
    {
        this->PropertyIdValue = PropertyId;
        return SharedThis(this);
    }

    TSharedPtr<FSetRarityParameterStatusByUserIdRequest> FSetRarityParameterStatusByUserIdRequest::WithParameterValues(
        const TSharedPtr<TArray<TSharedPtr<Model::FRarityParameterValue>>> ParameterValues
    )
    {
        this->ParameterValuesValue = ParameterValues;
        return SharedThis(this);
    }

    TSharedPtr<FSetRarityParameterStatusByUserIdRequest> FSetRarityParameterStatusByUserIdRequest::WithDuplicationAvoider(
        const TOptional<FString> DuplicationAvoider
    )
    {
        this->DuplicationAvoiderValue = DuplicationAvoider;
        return SharedThis(this);
    }

    TOptional<FString> FSetRarityParameterStatusByUserIdRequest::GetContextStack() const
    {
        return ContextStackValue;
    }

    TOptional<FString> FSetRarityParameterStatusByUserIdRequest::GetNamespaceName() const
    {
        return NamespaceNameValue;
    }

    TOptional<FString> FSetRarityParameterStatusByUserIdRequest::GetUserId() const
    {
        return UserIdValue;
    }

    TOptional<FString> FSetRarityParameterStatusByUserIdRequest::GetParameterName() const
    {
        return ParameterNameValue;
    }

    TOptional<FString> FSetRarityParameterStatusByUserIdRequest::GetPropertyId() const
    {
        return PropertyIdValue;
    }

    TSharedPtr<TArray<TSharedPtr<Model::FRarityParameterValue>>> FSetRarityParameterStatusByUserIdRequest::GetParameterValues() const
    {
        if (!ParameterValuesValue.IsValid())
        {
            return nullptr;
        }
        return ParameterValuesValue;
    }

    TOptional<FString> FSetRarityParameterStatusByUserIdRequest::GetDuplicationAvoider() const
    {
        return DuplicationAvoiderValue;
    }

    TSharedPtr<FSetRarityParameterStatusByUserIdRequest> FSetRarityParameterStatusByUserIdRequest::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FSetRarityParameterStatusByUserIdRequest>()
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
            ->WithUserId(Data->HasField("userId") ? [Data]() -> TOptional<FString>
              {
                  FString v;
                    if (Data->TryGetStringField("userId", v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
            ->WithParameterName(Data->HasField("parameterName") ? [Data]() -> TOptional<FString>
              {
                  FString v;
                    if (Data->TryGetStringField("parameterName", v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
            ->WithPropertyId(Data->HasField("propertyId") ? [Data]() -> TOptional<FString>
              {
                  FString v;
                    if (Data->TryGetStringField("propertyId", v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
          ->WithParameterValues(Data->HasField("parameterValues") ? [Data]() -> TSharedPtr<TArray<Model::FRarityParameterValuePtr>>
              {
                  auto v = MakeShared<TArray<Model::FRarityParameterValuePtr>>();
                  if (!Data->HasTypedField<EJson::Null>("parameterValues") && Data->HasTypedField<EJson::Array>("parameterValues"))
                  {
                      for (auto JsonObjectValue : Data->GetArrayField("parameterValues"))
                      {
                          v->Add(Model::FRarityParameterValue::FromJson(JsonObjectValue->AsObject()));
                      }
                  }
                  return v;
             }() : nullptr)
          ->WithDuplicationAvoider(Data->HasField("duplicationAvoider") ? TOptional<FString>(Data->GetStringField("duplicationAvoider")) : TOptional<FString>());
    }

    TSharedPtr<FJsonObject> FSetRarityParameterStatusByUserIdRequest::ToJson() const
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
        if (ParameterNameValue.IsSet())
        {
            JsonRootObject->SetStringField("parameterName", ParameterNameValue.GetValue());
        }
        if (PropertyIdValue.IsSet())
        {
            JsonRootObject->SetStringField("propertyId", PropertyIdValue.GetValue());
        }
        if (ParameterValuesValue != nullptr && ParameterValuesValue.IsValid())
        {
            TArray<TSharedPtr<FJsonValue>> v;
            for (auto JsonObjectValue : *ParameterValuesValue)
            {
                v.Add(MakeShared<FJsonValueObject>(JsonObjectValue->ToJson()));
            }
            JsonRootObject->SetArrayField("parameterValues", v);
        }
        if (DuplicationAvoiderValue.IsSet())
        {
            JsonRootObject->SetStringField("duplicationAvoider", DuplicationAvoiderValue.GetValue());
        }
        return JsonRootObject;
    }
}