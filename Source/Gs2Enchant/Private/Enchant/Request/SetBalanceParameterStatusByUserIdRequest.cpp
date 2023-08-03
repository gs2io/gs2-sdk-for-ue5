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

#include "Enchant/Request/SetBalanceParameterStatusByUserIdRequest.h"

namespace Gs2::Enchant::Request
{
    FSetBalanceParameterStatusByUserIdRequest::FSetBalanceParameterStatusByUserIdRequest():
        NamespaceNameValue(TOptional<FString>()),
        UserIdValue(TOptional<FString>()),
        ParameterNameValue(TOptional<FString>()),
        PropertyIdValue(TOptional<FString>()),
        ParameterValuesValue(nullptr)
    {
    }

    FSetBalanceParameterStatusByUserIdRequest::FSetBalanceParameterStatusByUserIdRequest(
        const FSetBalanceParameterStatusByUserIdRequest& From
    ):
        NamespaceNameValue(From.NamespaceNameValue),
        UserIdValue(From.UserIdValue),
        ParameterNameValue(From.ParameterNameValue),
        PropertyIdValue(From.PropertyIdValue),
        ParameterValuesValue(From.ParameterValuesValue)
    {
    }

    TSharedPtr<FSetBalanceParameterStatusByUserIdRequest> FSetBalanceParameterStatusByUserIdRequest::WithContextStack(
        const TOptional<FString> ContextStack
    )
    {
        this->ContextStackValue = ContextStack;
        return SharedThis(this);
    }

    TSharedPtr<FSetBalanceParameterStatusByUserIdRequest> FSetBalanceParameterStatusByUserIdRequest::WithNamespaceName(
        const TOptional<FString> NamespaceName
    )
    {
        this->NamespaceNameValue = NamespaceName;
        return SharedThis(this);
    }

    TSharedPtr<FSetBalanceParameterStatusByUserIdRequest> FSetBalanceParameterStatusByUserIdRequest::WithUserId(
        const TOptional<FString> UserId
    )
    {
        this->UserIdValue = UserId;
        return SharedThis(this);
    }

    TSharedPtr<FSetBalanceParameterStatusByUserIdRequest> FSetBalanceParameterStatusByUserIdRequest::WithParameterName(
        const TOptional<FString> ParameterName
    )
    {
        this->ParameterNameValue = ParameterName;
        return SharedThis(this);
    }

    TSharedPtr<FSetBalanceParameterStatusByUserIdRequest> FSetBalanceParameterStatusByUserIdRequest::WithPropertyId(
        const TOptional<FString> PropertyId
    )
    {
        this->PropertyIdValue = PropertyId;
        return SharedThis(this);
    }

    TSharedPtr<FSetBalanceParameterStatusByUserIdRequest> FSetBalanceParameterStatusByUserIdRequest::WithParameterValues(
        const TSharedPtr<TArray<TSharedPtr<Model::FBalanceParameterValue>>> ParameterValues
    )
    {
        this->ParameterValuesValue = ParameterValues;
        return SharedThis(this);
    }

    TSharedPtr<FSetBalanceParameterStatusByUserIdRequest> FSetBalanceParameterStatusByUserIdRequest::WithDuplicationAvoider(
        const TOptional<FString> DuplicationAvoider
    )
    {
        this->DuplicationAvoiderValue = DuplicationAvoider;
        return SharedThis(this);
    }

    TOptional<FString> FSetBalanceParameterStatusByUserIdRequest::GetContextStack() const
    {
        return ContextStackValue;
    }

    TOptional<FString> FSetBalanceParameterStatusByUserIdRequest::GetNamespaceName() const
    {
        return NamespaceNameValue;
    }

    TOptional<FString> FSetBalanceParameterStatusByUserIdRequest::GetUserId() const
    {
        return UserIdValue;
    }

    TOptional<FString> FSetBalanceParameterStatusByUserIdRequest::GetParameterName() const
    {
        return ParameterNameValue;
    }

    TOptional<FString> FSetBalanceParameterStatusByUserIdRequest::GetPropertyId() const
    {
        return PropertyIdValue;
    }

    TSharedPtr<TArray<TSharedPtr<Model::FBalanceParameterValue>>> FSetBalanceParameterStatusByUserIdRequest::GetParameterValues() const
    {
        if (!ParameterValuesValue.IsValid())
        {
            return nullptr;
        }
        return ParameterValuesValue;
    }

    TOptional<FString> FSetBalanceParameterStatusByUserIdRequest::GetDuplicationAvoider() const
    {
        return DuplicationAvoiderValue;
    }

    TSharedPtr<FSetBalanceParameterStatusByUserIdRequest> FSetBalanceParameterStatusByUserIdRequest::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FSetBalanceParameterStatusByUserIdRequest>()
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
          ->WithParameterValues(Data->HasField("parameterValues") ? [Data]() -> TSharedPtr<TArray<Model::FBalanceParameterValuePtr>>
              {
                  auto v = MakeShared<TArray<Model::FBalanceParameterValuePtr>>();
                  if (!Data->HasTypedField<EJson::Null>("parameterValues") && Data->HasTypedField<EJson::Array>("parameterValues"))
                  {
                      for (auto JsonObjectValue : Data->GetArrayField("parameterValues"))
                      {
                          v->Add(Model::FBalanceParameterValue::FromJson(JsonObjectValue->AsObject()));
                      }
                  }
                  return v;
             }() : nullptr)
          ->WithDuplicationAvoider(Data->HasField("duplicationAvoider") ? TOptional<FString>(Data->GetStringField("duplicationAvoider")) : TOptional<FString>());
    }

    TSharedPtr<FJsonObject> FSetBalanceParameterStatusByUserIdRequest::ToJson() const
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