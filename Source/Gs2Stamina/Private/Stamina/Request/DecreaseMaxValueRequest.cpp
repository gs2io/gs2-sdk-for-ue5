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

#include "Stamina/Request/DecreaseMaxValueRequest.h"

namespace Gs2::Stamina::Request
{
    FDecreaseMaxValueRequest::FDecreaseMaxValueRequest():
        NamespaceNameValue(TOptional<FString>()),
        StaminaNameValue(TOptional<FString>()),
        AccessTokenValue(TOptional<FString>()),
        DecreaseValueValue(TOptional<int32>())
    {
    }

    FDecreaseMaxValueRequest::FDecreaseMaxValueRequest(
        const FDecreaseMaxValueRequest& From
    ):
        NamespaceNameValue(From.NamespaceNameValue),
        StaminaNameValue(From.StaminaNameValue),
        AccessTokenValue(From.AccessTokenValue),
        DecreaseValueValue(From.DecreaseValueValue)
    {
    }

    TSharedPtr<FDecreaseMaxValueRequest> FDecreaseMaxValueRequest::WithContextStack(
        const TOptional<FString> ContextStack
    )
    {
        this->ContextStackValue = ContextStack;
        return SharedThis(this);
    }

    TSharedPtr<FDecreaseMaxValueRequest> FDecreaseMaxValueRequest::WithNamespaceName(
        const TOptional<FString> NamespaceName
    )
    {
        this->NamespaceNameValue = NamespaceName;
        return SharedThis(this);
    }

    TSharedPtr<FDecreaseMaxValueRequest> FDecreaseMaxValueRequest::WithStaminaName(
        const TOptional<FString> StaminaName
    )
    {
        this->StaminaNameValue = StaminaName;
        return SharedThis(this);
    }

    TSharedPtr<FDecreaseMaxValueRequest> FDecreaseMaxValueRequest::WithAccessToken(
        const TOptional<FString> AccessToken
    )
    {
        this->AccessTokenValue = AccessToken;
        return SharedThis(this);
    }

    TSharedPtr<FDecreaseMaxValueRequest> FDecreaseMaxValueRequest::WithDecreaseValue(
        const TOptional<int32> DecreaseValue
    )
    {
        this->DecreaseValueValue = DecreaseValue;
        return SharedThis(this);
    }

    TSharedPtr<FDecreaseMaxValueRequest> FDecreaseMaxValueRequest::WithDuplicationAvoider(
        const TOptional<FString> DuplicationAvoider
    )
    {
        this->DuplicationAvoiderValue = DuplicationAvoider;
        return SharedThis(this);
    }

    TOptional<FString> FDecreaseMaxValueRequest::GetContextStack() const
    {
        return ContextStackValue;
    }

    TOptional<FString> FDecreaseMaxValueRequest::GetNamespaceName() const
    {
        return NamespaceNameValue;
    }

    TOptional<FString> FDecreaseMaxValueRequest::GetStaminaName() const
    {
        return StaminaNameValue;
    }

    TOptional<FString> FDecreaseMaxValueRequest::GetAccessToken() const
    {
        return AccessTokenValue;
    }

    TOptional<int32> FDecreaseMaxValueRequest::GetDecreaseValue() const
    {
        return DecreaseValueValue;
    }

    FString FDecreaseMaxValueRequest::GetDecreaseValueString() const
    {
        if (!DecreaseValueValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%d"), DecreaseValueValue.GetValue());
    }

    TOptional<FString> FDecreaseMaxValueRequest::GetDuplicationAvoider() const
    {
        return DuplicationAvoiderValue;
    }

    TSharedPtr<FDecreaseMaxValueRequest> FDecreaseMaxValueRequest::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FDecreaseMaxValueRequest>()
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
            ->WithStaminaName(Data->HasField(ANSI_TO_TCHAR("staminaName")) ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("staminaName"), v))
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
            ->WithDecreaseValue(Data->HasField(ANSI_TO_TCHAR("decreaseValue")) ? [Data]() -> TOptional<int32>
              {
                  int32 v;
                    if (Data->TryGetNumberField(ANSI_TO_TCHAR("decreaseValue"), v))
                  {
                        return TOptional(v);
                  }
                  return TOptional<int32>();
              }() : TOptional<int32>())
          ->WithDuplicationAvoider(Data->HasField(ANSI_TO_TCHAR("duplicationAvoider")) ? TOptional<FString>(Data->GetStringField(ANSI_TO_TCHAR("duplicationAvoider"))) : TOptional<FString>());
    }

    TSharedPtr<FJsonObject> FDecreaseMaxValueRequest::ToJson() const
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
        if (StaminaNameValue.IsSet())
        {
            JsonRootObject->SetStringField("staminaName", StaminaNameValue.GetValue());
        }
        if (AccessTokenValue.IsSet())
        {
            JsonRootObject->SetStringField("xGs2AccessToken", AccessTokenValue.GetValue());
        }
        if (DecreaseValueValue.IsSet())
        {
            JsonRootObject->SetNumberField("decreaseValue", DecreaseValueValue.GetValue());
        }
        if (DuplicationAvoiderValue.IsSet())
        {
            JsonRootObject->SetStringField("duplicationAvoider", DuplicationAvoiderValue.GetValue());
        }
        return JsonRootObject;
    }
}