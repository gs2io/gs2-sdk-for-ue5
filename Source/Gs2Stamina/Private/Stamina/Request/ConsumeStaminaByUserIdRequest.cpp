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

#include "Stamina/Request/ConsumeStaminaByUserIdRequest.h"

namespace Gs2::Stamina::Request
{
    FConsumeStaminaByUserIdRequest::FConsumeStaminaByUserIdRequest():
        NamespaceNameValue(TOptional<FString>()),
        StaminaNameValue(TOptional<FString>()),
        UserIdValue(TOptional<FString>()),
        ConsumeValueValue(TOptional<int32>())
    {
    }

    FConsumeStaminaByUserIdRequest::FConsumeStaminaByUserIdRequest(
        const FConsumeStaminaByUserIdRequest& From
    ):
        NamespaceNameValue(From.NamespaceNameValue),
        StaminaNameValue(From.StaminaNameValue),
        UserIdValue(From.UserIdValue),
        ConsumeValueValue(From.ConsumeValueValue)
    {
    }

    TSharedPtr<FConsumeStaminaByUserIdRequest> FConsumeStaminaByUserIdRequest::WithContextStack(
        const TOptional<FString> ContextStack
    )
    {
        this->ContextStackValue = ContextStack;
        return SharedThis(this);
    }

    TSharedPtr<FConsumeStaminaByUserIdRequest> FConsumeStaminaByUserIdRequest::WithNamespaceName(
        const TOptional<FString> NamespaceName
    )
    {
        this->NamespaceNameValue = NamespaceName;
        return SharedThis(this);
    }

    TSharedPtr<FConsumeStaminaByUserIdRequest> FConsumeStaminaByUserIdRequest::WithStaminaName(
        const TOptional<FString> StaminaName
    )
    {
        this->StaminaNameValue = StaminaName;
        return SharedThis(this);
    }

    TSharedPtr<FConsumeStaminaByUserIdRequest> FConsumeStaminaByUserIdRequest::WithUserId(
        const TOptional<FString> UserId
    )
    {
        this->UserIdValue = UserId;
        return SharedThis(this);
    }

    TSharedPtr<FConsumeStaminaByUserIdRequest> FConsumeStaminaByUserIdRequest::WithConsumeValue(
        const TOptional<int32> ConsumeValue
    )
    {
        this->ConsumeValueValue = ConsumeValue;
        return SharedThis(this);
    }

    TSharedPtr<FConsumeStaminaByUserIdRequest> FConsumeStaminaByUserIdRequest::WithDuplicationAvoider(
        const TOptional<FString> DuplicationAvoider
    )
    {
        this->DuplicationAvoiderValue = DuplicationAvoider;
        return SharedThis(this);
    }

    TOptional<FString> FConsumeStaminaByUserIdRequest::GetContextStack() const
    {
        return ContextStackValue;
    }

    TOptional<FString> FConsumeStaminaByUserIdRequest::GetNamespaceName() const
    {
        return NamespaceNameValue;
    }

    TOptional<FString> FConsumeStaminaByUserIdRequest::GetStaminaName() const
    {
        return StaminaNameValue;
    }

    TOptional<FString> FConsumeStaminaByUserIdRequest::GetUserId() const
    {
        return UserIdValue;
    }

    TOptional<int32> FConsumeStaminaByUserIdRequest::GetConsumeValue() const
    {
        return ConsumeValueValue;
    }

    FString FConsumeStaminaByUserIdRequest::GetConsumeValueString() const
    {
        if (!ConsumeValueValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%d"), ConsumeValueValue.GetValue());
    }

    TOptional<FString> FConsumeStaminaByUserIdRequest::GetDuplicationAvoider() const
    {
        return DuplicationAvoiderValue;
    }

    TSharedPtr<FConsumeStaminaByUserIdRequest> FConsumeStaminaByUserIdRequest::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FConsumeStaminaByUserIdRequest>()
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
            ->WithConsumeValue(Data->HasField("consumeValue") ? [Data]() -> TOptional<int32>
              {
                  int32 v;
                    if (Data->TryGetNumberField("consumeValue", v))
                  {
                        return TOptional(v);
                  }
                  return TOptional<int32>();
              }() : TOptional<int32>())
          ->WithDuplicationAvoider(Data->HasField("duplicationAvoider") ? TOptional<FString>(Data->GetStringField("duplicationAvoider")) : TOptional<FString>());
    }

    TSharedPtr<FJsonObject> FConsumeStaminaByUserIdRequest::ToJson() const
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
        if (ConsumeValueValue.IsSet())
        {
            JsonRootObject->SetNumberField("consumeValue", ConsumeValueValue.GetValue());
        }
        if (DuplicationAvoiderValue.IsSet())
        {
            JsonRootObject->SetStringField("duplicationAvoider", DuplicationAvoiderValue.GetValue());
        }
        return JsonRootObject;
    }
}