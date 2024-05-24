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

#include "Mission/Request/VerifyCounterValueRequest.h"

namespace Gs2::Mission::Request
{
    FVerifyCounterValueRequest::FVerifyCounterValueRequest():
        NamespaceNameValue(TOptional<FString>()),
        AccessTokenValue(TOptional<FString>()),
        CounterNameValue(TOptional<FString>()),
        VerifyTypeValue(TOptional<FString>()),
        ResetTypeValue(TOptional<FString>()),
        ValueValue(TOptional<int64>()),
        MultiplyValueSpecifyingQuantityValue(TOptional<bool>())
    {
    }

    FVerifyCounterValueRequest::FVerifyCounterValueRequest(
        const FVerifyCounterValueRequest& From
    ):
        NamespaceNameValue(From.NamespaceNameValue),
        AccessTokenValue(From.AccessTokenValue),
        CounterNameValue(From.CounterNameValue),
        VerifyTypeValue(From.VerifyTypeValue),
        ResetTypeValue(From.ResetTypeValue),
        ValueValue(From.ValueValue),
        MultiplyValueSpecifyingQuantityValue(From.MultiplyValueSpecifyingQuantityValue)
    {
    }

    TSharedPtr<FVerifyCounterValueRequest> FVerifyCounterValueRequest::WithContextStack(
        const TOptional<FString> ContextStack
    )
    {
        this->ContextStackValue = ContextStack;
        return SharedThis(this);
    }

    TSharedPtr<FVerifyCounterValueRequest> FVerifyCounterValueRequest::WithNamespaceName(
        const TOptional<FString> NamespaceName
    )
    {
        this->NamespaceNameValue = NamespaceName;
        return SharedThis(this);
    }

    TSharedPtr<FVerifyCounterValueRequest> FVerifyCounterValueRequest::WithAccessToken(
        const TOptional<FString> AccessToken
    )
    {
        this->AccessTokenValue = AccessToken;
        return SharedThis(this);
    }

    TSharedPtr<FVerifyCounterValueRequest> FVerifyCounterValueRequest::WithCounterName(
        const TOptional<FString> CounterName
    )
    {
        this->CounterNameValue = CounterName;
        return SharedThis(this);
    }

    TSharedPtr<FVerifyCounterValueRequest> FVerifyCounterValueRequest::WithVerifyType(
        const TOptional<FString> VerifyType
    )
    {
        this->VerifyTypeValue = VerifyType;
        return SharedThis(this);
    }

    TSharedPtr<FVerifyCounterValueRequest> FVerifyCounterValueRequest::WithResetType(
        const TOptional<FString> ResetType
    )
    {
        this->ResetTypeValue = ResetType;
        return SharedThis(this);
    }

    TSharedPtr<FVerifyCounterValueRequest> FVerifyCounterValueRequest::WithValue(
        const TOptional<int64> Value
    )
    {
        this->ValueValue = Value;
        return SharedThis(this);
    }

    TSharedPtr<FVerifyCounterValueRequest> FVerifyCounterValueRequest::WithMultiplyValueSpecifyingQuantity(
        const TOptional<bool> MultiplyValueSpecifyingQuantity
    )
    {
        this->MultiplyValueSpecifyingQuantityValue = MultiplyValueSpecifyingQuantity;
        return SharedThis(this);
    }

    TSharedPtr<FVerifyCounterValueRequest> FVerifyCounterValueRequest::WithDuplicationAvoider(
        const TOptional<FString> DuplicationAvoider
    )
    {
        this->DuplicationAvoiderValue = DuplicationAvoider;
        return SharedThis(this);
    }

    TOptional<FString> FVerifyCounterValueRequest::GetContextStack() const
    {
        return ContextStackValue;
    }

    TOptional<FString> FVerifyCounterValueRequest::GetNamespaceName() const
    {
        return NamespaceNameValue;
    }

    TOptional<FString> FVerifyCounterValueRequest::GetAccessToken() const
    {
        return AccessTokenValue;
    }

    TOptional<FString> FVerifyCounterValueRequest::GetCounterName() const
    {
        return CounterNameValue;
    }

    TOptional<FString> FVerifyCounterValueRequest::GetVerifyType() const
    {
        return VerifyTypeValue;
    }

    TOptional<FString> FVerifyCounterValueRequest::GetResetType() const
    {
        return ResetTypeValue;
    }

    TOptional<int64> FVerifyCounterValueRequest::GetValue() const
    {
        return ValueValue;
    }

    FString FVerifyCounterValueRequest::GetValueString() const
    {
        if (!ValueValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), ValueValue.GetValue());
    }

    TOptional<bool> FVerifyCounterValueRequest::GetMultiplyValueSpecifyingQuantity() const
    {
        return MultiplyValueSpecifyingQuantityValue;
    }

    FString FVerifyCounterValueRequest::GetMultiplyValueSpecifyingQuantityString() const
    {
        if (!MultiplyValueSpecifyingQuantityValue.IsSet())
        {
            return FString("null");
        }
        return FString(MultiplyValueSpecifyingQuantityValue.GetValue() ? "true" : "false");
    }

    TOptional<FString> FVerifyCounterValueRequest::GetDuplicationAvoider() const
    {
        return DuplicationAvoiderValue;
    }

    TSharedPtr<FVerifyCounterValueRequest> FVerifyCounterValueRequest::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FVerifyCounterValueRequest>()
            ->WithContextStack(Data->HasField(ANSI_TO_TCHAR("contextStack")) ? TOptional<FString>(Data->GetStringField(ANSI_TO_TCHAR("contextStack"))) : TOptional<FString>())
            ->WithNamespaceName(Data->HasField(ANSI_TO_TCHAR("namespaceName")) ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("namespaceName"), v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
            ->WithAccessToken(Data->HasField(ANSI_TO_TCHAR("xGs2AccessToken")) ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("xGs2AccessToken"), v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
            ->WithCounterName(Data->HasField(ANSI_TO_TCHAR("counterName")) ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("counterName"), v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
            ->WithVerifyType(Data->HasField(ANSI_TO_TCHAR("verifyType")) ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("verifyType"), v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
            ->WithResetType(Data->HasField(ANSI_TO_TCHAR("resetType")) ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("resetType"), v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
            ->WithValue(Data->HasField(ANSI_TO_TCHAR("value")) ? [Data]() -> TOptional<int64>
              {
                  int64 v;
                    if (Data->TryGetNumberField(ANSI_TO_TCHAR("value"), v))
                  {
                        return TOptional(v);
                  }
                  return TOptional<int64>();
              }() : TOptional<int64>())
            ->WithMultiplyValueSpecifyingQuantity(Data->HasField(ANSI_TO_TCHAR("multiplyValueSpecifyingQuantity")) ? [Data]() -> TOptional<bool>
              {
                  bool v;
                    if (Data->TryGetBoolField(ANSI_TO_TCHAR("multiplyValueSpecifyingQuantity"), v))
                  {
                        return TOptional(v);
                  }
                  return TOptional<bool>();
              }() : TOptional<bool>())
          ->WithDuplicationAvoider(Data->HasField(ANSI_TO_TCHAR("duplicationAvoider")) ? TOptional<FString>(Data->GetStringField(ANSI_TO_TCHAR("duplicationAvoider"))) : TOptional<FString>());
    }

    TSharedPtr<FJsonObject> FVerifyCounterValueRequest::ToJson() const
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
        if (CounterNameValue.IsSet())
        {
            JsonRootObject->SetStringField("counterName", CounterNameValue.GetValue());
        }
        if (VerifyTypeValue.IsSet())
        {
            JsonRootObject->SetStringField("verifyType", VerifyTypeValue.GetValue());
        }
        if (ResetTypeValue.IsSet())
        {
            JsonRootObject->SetStringField("resetType", ResetTypeValue.GetValue());
        }
        if (ValueValue.IsSet())
        {
            JsonRootObject->SetStringField("value", FString::Printf(TEXT("%lld"), ValueValue.GetValue()));
        }
        if (MultiplyValueSpecifyingQuantityValue.IsSet())
        {
            JsonRootObject->SetBoolField("multiplyValueSpecifyingQuantity", MultiplyValueSpecifyingQuantityValue.GetValue());
        }
        if (DuplicationAvoiderValue.IsSet())
        {
            JsonRootObject->SetStringField("duplicationAvoider", DuplicationAvoiderValue.GetValue());
        }
        return JsonRootObject;
    }
}