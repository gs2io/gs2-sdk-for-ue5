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

#include "Stamina/Request/DecreaseMaxValueByUserIdRequest.h"

namespace Gs2::Stamina::Request
{
    FDecreaseMaxValueByUserIdRequest::FDecreaseMaxValueByUserIdRequest():
        NamespaceNameValue(TOptional<FString>()),
        StaminaNameValue(TOptional<FString>()),
        UserIdValue(TOptional<FString>()),
        DecreaseValueValue(TOptional<int32>())
    {
    }

    FDecreaseMaxValueByUserIdRequest::FDecreaseMaxValueByUserIdRequest(
        const FDecreaseMaxValueByUserIdRequest& From
    ):
        NamespaceNameValue(From.NamespaceNameValue),
        StaminaNameValue(From.StaminaNameValue),
        UserIdValue(From.UserIdValue),
        DecreaseValueValue(From.DecreaseValueValue)
    {
    }

    TSharedPtr<FDecreaseMaxValueByUserIdRequest> FDecreaseMaxValueByUserIdRequest::WithContextStack(
        const TOptional<FString> ContextStack
    )
    {
        this->ContextStackValue = ContextStack;
        return SharedThis(this);
    }

    TSharedPtr<FDecreaseMaxValueByUserIdRequest> FDecreaseMaxValueByUserIdRequest::WithNamespaceName(
        const TOptional<FString> NamespaceName
    )
    {
        this->NamespaceNameValue = NamespaceName;
        return SharedThis(this);
    }

    TSharedPtr<FDecreaseMaxValueByUserIdRequest> FDecreaseMaxValueByUserIdRequest::WithStaminaName(
        const TOptional<FString> StaminaName
    )
    {
        this->StaminaNameValue = StaminaName;
        return SharedThis(this);
    }

    TSharedPtr<FDecreaseMaxValueByUserIdRequest> FDecreaseMaxValueByUserIdRequest::WithUserId(
        const TOptional<FString> UserId
    )
    {
        this->UserIdValue = UserId;
        return SharedThis(this);
    }

    TSharedPtr<FDecreaseMaxValueByUserIdRequest> FDecreaseMaxValueByUserIdRequest::WithDecreaseValue(
        const TOptional<int32> DecreaseValue
    )
    {
        this->DecreaseValueValue = DecreaseValue;
        return SharedThis(this);
    }

    TSharedPtr<FDecreaseMaxValueByUserIdRequest> FDecreaseMaxValueByUserIdRequest::WithDuplicationAvoider(
        const TOptional<FString> DuplicationAvoider
    )
    {
        this->DuplicationAvoiderValue = DuplicationAvoider;
        return SharedThis(this);
    }

    TOptional<FString> FDecreaseMaxValueByUserIdRequest::GetContextStack() const
    {
        return ContextStackValue;
    }

    TOptional<FString> FDecreaseMaxValueByUserIdRequest::GetNamespaceName() const
    {
        return NamespaceNameValue;
    }

    TOptional<FString> FDecreaseMaxValueByUserIdRequest::GetStaminaName() const
    {
        return StaminaNameValue;
    }

    TOptional<FString> FDecreaseMaxValueByUserIdRequest::GetUserId() const
    {
        return UserIdValue;
    }

    TOptional<int32> FDecreaseMaxValueByUserIdRequest::GetDecreaseValue() const
    {
        return DecreaseValueValue;
    }

    FString FDecreaseMaxValueByUserIdRequest::GetDecreaseValueString() const
    {
        if (!DecreaseValueValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%d"), DecreaseValueValue.GetValue());
    }

    TOptional<FString> FDecreaseMaxValueByUserIdRequest::GetDuplicationAvoider() const
    {
        return DuplicationAvoiderValue;
    }

    TSharedPtr<FDecreaseMaxValueByUserIdRequest> FDecreaseMaxValueByUserIdRequest::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FDecreaseMaxValueByUserIdRequest>()
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
            ->WithStaminaName(Data->HasField("staminaName") ? [Data]() -> TOptional<FString>
              {
                  FString v;
                    if (Data->TryGetStringField("staminaName", v))
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
            ->WithDecreaseValue(Data->HasField("decreaseValue") ? [Data]() -> TOptional<int32>
              {
                  int32 v;
                    if (Data->TryGetNumberField("decreaseValue", v))
                  {
                        return TOptional(v);
                  }
                  return TOptional<int32>();
              }() : TOptional<int32>())
          ->WithDuplicationAvoider(Data->HasField("duplicationAvoider") ? TOptional<FString>(Data->GetStringField("duplicationAvoider")) : TOptional<FString>());
    }

    TSharedPtr<FJsonObject> FDecreaseMaxValueByUserIdRequest::ToJson() const
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
        if (UserIdValue.IsSet())
        {
            JsonRootObject->SetStringField("userId", UserIdValue.GetValue());
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