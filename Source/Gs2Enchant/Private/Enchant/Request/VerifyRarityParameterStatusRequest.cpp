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

#include "Enchant/Request/VerifyRarityParameterStatusRequest.h"

namespace Gs2::Enchant::Request
{
    FVerifyRarityParameterStatusRequest::FVerifyRarityParameterStatusRequest():
        NamespaceNameValue(TOptional<FString>()),
        ParameterNameValue(TOptional<FString>()),
        AccessTokenValue(TOptional<FString>()),
        PropertyIdValue(TOptional<FString>()),
        VerifyTypeValue(TOptional<FString>()),
        ParameterValueNameValue(TOptional<FString>()),
        ParameterCountValue(TOptional<int32>())
    {
    }

    FVerifyRarityParameterStatusRequest::FVerifyRarityParameterStatusRequest(
        const FVerifyRarityParameterStatusRequest& From
    ):
        NamespaceNameValue(From.NamespaceNameValue),
        ParameterNameValue(From.ParameterNameValue),
        AccessTokenValue(From.AccessTokenValue),
        PropertyIdValue(From.PropertyIdValue),
        VerifyTypeValue(From.VerifyTypeValue),
        ParameterValueNameValue(From.ParameterValueNameValue),
        ParameterCountValue(From.ParameterCountValue)
    {
    }

    TSharedPtr<FVerifyRarityParameterStatusRequest> FVerifyRarityParameterStatusRequest::WithContextStack(
        const TOptional<FString> ContextStack
    )
    {
        this->ContextStackValue = ContextStack;
        return SharedThis(this);
    }

    TSharedPtr<FVerifyRarityParameterStatusRequest> FVerifyRarityParameterStatusRequest::WithNamespaceName(
        const TOptional<FString> NamespaceName
    )
    {
        this->NamespaceNameValue = NamespaceName;
        return SharedThis(this);
    }

    TSharedPtr<FVerifyRarityParameterStatusRequest> FVerifyRarityParameterStatusRequest::WithParameterName(
        const TOptional<FString> ParameterName
    )
    {
        this->ParameterNameValue = ParameterName;
        return SharedThis(this);
    }

    TSharedPtr<FVerifyRarityParameterStatusRequest> FVerifyRarityParameterStatusRequest::WithAccessToken(
        const TOptional<FString> AccessToken
    )
    {
        this->AccessTokenValue = AccessToken;
        return SharedThis(this);
    }

    TSharedPtr<FVerifyRarityParameterStatusRequest> FVerifyRarityParameterStatusRequest::WithPropertyId(
        const TOptional<FString> PropertyId
    )
    {
        this->PropertyIdValue = PropertyId;
        return SharedThis(this);
    }

    TSharedPtr<FVerifyRarityParameterStatusRequest> FVerifyRarityParameterStatusRequest::WithVerifyType(
        const TOptional<FString> VerifyType
    )
    {
        this->VerifyTypeValue = VerifyType;
        return SharedThis(this);
    }

    TSharedPtr<FVerifyRarityParameterStatusRequest> FVerifyRarityParameterStatusRequest::WithParameterValueName(
        const TOptional<FString> ParameterValueName
    )
    {
        this->ParameterValueNameValue = ParameterValueName;
        return SharedThis(this);
    }

    TSharedPtr<FVerifyRarityParameterStatusRequest> FVerifyRarityParameterStatusRequest::WithParameterCount(
        const TOptional<int32> ParameterCount
    )
    {
        this->ParameterCountValue = ParameterCount;
        return SharedThis(this);
    }

    TSharedPtr<FVerifyRarityParameterStatusRequest> FVerifyRarityParameterStatusRequest::WithDuplicationAvoider(
        const TOptional<FString> DuplicationAvoider
    )
    {
        this->DuplicationAvoiderValue = DuplicationAvoider;
        return SharedThis(this);
    }

    TOptional<FString> FVerifyRarityParameterStatusRequest::GetContextStack() const
    {
        return ContextStackValue;
    }

    TOptional<FString> FVerifyRarityParameterStatusRequest::GetNamespaceName() const
    {
        return NamespaceNameValue;
    }

    TOptional<FString> FVerifyRarityParameterStatusRequest::GetParameterName() const
    {
        return ParameterNameValue;
    }

    TOptional<FString> FVerifyRarityParameterStatusRequest::GetAccessToken() const
    {
        return AccessTokenValue;
    }

    TOptional<FString> FVerifyRarityParameterStatusRequest::GetPropertyId() const
    {
        return PropertyIdValue;
    }

    TOptional<FString> FVerifyRarityParameterStatusRequest::GetVerifyType() const
    {
        return VerifyTypeValue;
    }

    TOptional<FString> FVerifyRarityParameterStatusRequest::GetParameterValueName() const
    {
        return ParameterValueNameValue;
    }

    TOptional<int32> FVerifyRarityParameterStatusRequest::GetParameterCount() const
    {
        return ParameterCountValue;
    }

    FString FVerifyRarityParameterStatusRequest::GetParameterCountString() const
    {
        if (!ParameterCountValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%d"), ParameterCountValue.GetValue());
    }

    TOptional<FString> FVerifyRarityParameterStatusRequest::GetDuplicationAvoider() const
    {
        return DuplicationAvoiderValue;
    }

    TSharedPtr<FVerifyRarityParameterStatusRequest> FVerifyRarityParameterStatusRequest::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FVerifyRarityParameterStatusRequest>()
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
            ->WithParameterName(Data->HasField("parameterName") ? [Data]() -> TOptional<FString>
              {
                  FString v;
                    if (Data->TryGetStringField("parameterName", v))
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
            ->WithPropertyId(Data->HasField("propertyId") ? [Data]() -> TOptional<FString>
              {
                  FString v;
                    if (Data->TryGetStringField("propertyId", v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
            ->WithVerifyType(Data->HasField("verifyType") ? [Data]() -> TOptional<FString>
              {
                  FString v;
                    if (Data->TryGetStringField("verifyType", v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
            ->WithParameterValueName(Data->HasField("parameterValueName") ? [Data]() -> TOptional<FString>
              {
                  FString v;
                    if (Data->TryGetStringField("parameterValueName", v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
            ->WithParameterCount(Data->HasField("parameterCount") ? [Data]() -> TOptional<int32>
              {
                  int32 v;
                    if (Data->TryGetNumberField("parameterCount", v))
                  {
                        return TOptional(v);
                  }
                  return TOptional<int32>();
              }() : TOptional<int32>())
          ->WithDuplicationAvoider(Data->HasField("duplicationAvoider") ? TOptional<FString>(Data->GetStringField("duplicationAvoider")) : TOptional<FString>());
    }

    TSharedPtr<FJsonObject> FVerifyRarityParameterStatusRequest::ToJson() const
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
        if (ParameterNameValue.IsSet())
        {
            JsonRootObject->SetStringField("parameterName", ParameterNameValue.GetValue());
        }
        if (AccessTokenValue.IsSet())
        {
            JsonRootObject->SetStringField("xGs2AccessToken", AccessTokenValue.GetValue());
        }
        if (PropertyIdValue.IsSet())
        {
            JsonRootObject->SetStringField("propertyId", PropertyIdValue.GetValue());
        }
        if (VerifyTypeValue.IsSet())
        {
            JsonRootObject->SetStringField("verifyType", VerifyTypeValue.GetValue());
        }
        if (ParameterValueNameValue.IsSet())
        {
            JsonRootObject->SetStringField("parameterValueName", ParameterValueNameValue.GetValue());
        }
        if (ParameterCountValue.IsSet())
        {
            JsonRootObject->SetNumberField("parameterCount", ParameterCountValue.GetValue());
        }
        if (DuplicationAvoiderValue.IsSet())
        {
            JsonRootObject->SetStringField("duplicationAvoider", DuplicationAvoiderValue.GetValue());
        }
        return JsonRootObject;
    }
}