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

#include "Stamina/Request/VerifyStaminaRecoverIntervalMinutesByUserIdRequest.h"

namespace Gs2::Stamina::Request
{
    FVerifyStaminaRecoverIntervalMinutesByUserIdRequest::FVerifyStaminaRecoverIntervalMinutesByUserIdRequest():
        NamespaceNameValue(TOptional<FString>()),
        UserIdValue(TOptional<FString>()),
        StaminaNameValue(TOptional<FString>()),
        VerifyTypeValue(TOptional<FString>()),
        ValueValue(TOptional<int32>()),
        MultiplyValueSpecifyingQuantityValue(TOptional<bool>()),
        TimeOffsetTokenValue(TOptional<FString>())
    {
    }

    FVerifyStaminaRecoverIntervalMinutesByUserIdRequest::FVerifyStaminaRecoverIntervalMinutesByUserIdRequest(
        const FVerifyStaminaRecoverIntervalMinutesByUserIdRequest& From
    ):
        NamespaceNameValue(From.NamespaceNameValue),
        UserIdValue(From.UserIdValue),
        StaminaNameValue(From.StaminaNameValue),
        VerifyTypeValue(From.VerifyTypeValue),
        ValueValue(From.ValueValue),
        MultiplyValueSpecifyingQuantityValue(From.MultiplyValueSpecifyingQuantityValue),
        TimeOffsetTokenValue(From.TimeOffsetTokenValue)
    {
    }

    TSharedPtr<FVerifyStaminaRecoverIntervalMinutesByUserIdRequest> FVerifyStaminaRecoverIntervalMinutesByUserIdRequest::WithContextStack(
        const TOptional<FString> ContextStack
    )
    {
        this->ContextStackValue = ContextStack;
        return SharedThis(this);
    }

    TSharedPtr<FVerifyStaminaRecoverIntervalMinutesByUserIdRequest> FVerifyStaminaRecoverIntervalMinutesByUserIdRequest::WithNamespaceName(
        const TOptional<FString> NamespaceName
    )
    {
        this->NamespaceNameValue = NamespaceName;
        return SharedThis(this);
    }

    TSharedPtr<FVerifyStaminaRecoverIntervalMinutesByUserIdRequest> FVerifyStaminaRecoverIntervalMinutesByUserIdRequest::WithUserId(
        const TOptional<FString> UserId
    )
    {
        this->UserIdValue = UserId;
        return SharedThis(this);
    }

    TSharedPtr<FVerifyStaminaRecoverIntervalMinutesByUserIdRequest> FVerifyStaminaRecoverIntervalMinutesByUserIdRequest::WithStaminaName(
        const TOptional<FString> StaminaName
    )
    {
        this->StaminaNameValue = StaminaName;
        return SharedThis(this);
    }

    TSharedPtr<FVerifyStaminaRecoverIntervalMinutesByUserIdRequest> FVerifyStaminaRecoverIntervalMinutesByUserIdRequest::WithVerifyType(
        const TOptional<FString> VerifyType
    )
    {
        this->VerifyTypeValue = VerifyType;
        return SharedThis(this);
    }

    TSharedPtr<FVerifyStaminaRecoverIntervalMinutesByUserIdRequest> FVerifyStaminaRecoverIntervalMinutesByUserIdRequest::WithValue(
        const TOptional<int32> Value
    )
    {
        this->ValueValue = Value;
        return SharedThis(this);
    }

    TSharedPtr<FVerifyStaminaRecoverIntervalMinutesByUserIdRequest> FVerifyStaminaRecoverIntervalMinutesByUserIdRequest::WithMultiplyValueSpecifyingQuantity(
        const TOptional<bool> MultiplyValueSpecifyingQuantity
    )
    {
        this->MultiplyValueSpecifyingQuantityValue = MultiplyValueSpecifyingQuantity;
        return SharedThis(this);
    }

    TSharedPtr<FVerifyStaminaRecoverIntervalMinutesByUserIdRequest> FVerifyStaminaRecoverIntervalMinutesByUserIdRequest::WithTimeOffsetToken(
        const TOptional<FString> TimeOffsetToken
    )
    {
        this->TimeOffsetTokenValue = TimeOffsetToken;
        return SharedThis(this);
    }

    TSharedPtr<FVerifyStaminaRecoverIntervalMinutesByUserIdRequest> FVerifyStaminaRecoverIntervalMinutesByUserIdRequest::WithDuplicationAvoider(
        const TOptional<FString> DuplicationAvoider
    )
    {
        this->DuplicationAvoiderValue = DuplicationAvoider;
        return SharedThis(this);
    }

    TOptional<FString> FVerifyStaminaRecoverIntervalMinutesByUserIdRequest::GetContextStack() const
    {
        return ContextStackValue;
    }

    TOptional<FString> FVerifyStaminaRecoverIntervalMinutesByUserIdRequest::GetNamespaceName() const
    {
        return NamespaceNameValue;
    }

    TOptional<FString> FVerifyStaminaRecoverIntervalMinutesByUserIdRequest::GetUserId() const
    {
        return UserIdValue;
    }

    TOptional<FString> FVerifyStaminaRecoverIntervalMinutesByUserIdRequest::GetStaminaName() const
    {
        return StaminaNameValue;
    }

    TOptional<FString> FVerifyStaminaRecoverIntervalMinutesByUserIdRequest::GetVerifyType() const
    {
        return VerifyTypeValue;
    }

    TOptional<int32> FVerifyStaminaRecoverIntervalMinutesByUserIdRequest::GetValue() const
    {
        return ValueValue;
    }

    FString FVerifyStaminaRecoverIntervalMinutesByUserIdRequest::GetValueString() const
    {
        if (!ValueValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%d"), ValueValue.GetValue());
    }

    TOptional<bool> FVerifyStaminaRecoverIntervalMinutesByUserIdRequest::GetMultiplyValueSpecifyingQuantity() const
    {
        return MultiplyValueSpecifyingQuantityValue;
    }

    FString FVerifyStaminaRecoverIntervalMinutesByUserIdRequest::GetMultiplyValueSpecifyingQuantityString() const
    {
        if (!MultiplyValueSpecifyingQuantityValue.IsSet())
        {
            return FString("null");
        }
        return FString(MultiplyValueSpecifyingQuantityValue.GetValue() ? "true" : "false");
    }

    TOptional<FString> FVerifyStaminaRecoverIntervalMinutesByUserIdRequest::GetTimeOffsetToken() const
    {
        return TimeOffsetTokenValue;
    }

    TOptional<FString> FVerifyStaminaRecoverIntervalMinutesByUserIdRequest::GetDuplicationAvoider() const
    {
        return DuplicationAvoiderValue;
    }

    TSharedPtr<FVerifyStaminaRecoverIntervalMinutesByUserIdRequest> FVerifyStaminaRecoverIntervalMinutesByUserIdRequest::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FVerifyStaminaRecoverIntervalMinutesByUserIdRequest>()
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
            ->WithUserId(Data->HasField(ANSI_TO_TCHAR("userId")) ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("userId"), v))
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
            ->WithVerifyType(Data->HasField(ANSI_TO_TCHAR("verifyType")) ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("verifyType"), v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
            ->WithValue(Data->HasField(ANSI_TO_TCHAR("value")) ? [Data]() -> TOptional<int32>
              {
                  int32 v;
                    if (Data->TryGetNumberField(ANSI_TO_TCHAR("value"), v))
                  {
                        return TOptional(v);
                  }
                  return TOptional<int32>();
              }() : TOptional<int32>())
            ->WithMultiplyValueSpecifyingQuantity(Data->HasField(ANSI_TO_TCHAR("multiplyValueSpecifyingQuantity")) ? [Data]() -> TOptional<bool>
              {
                  bool v;
                    if (Data->TryGetBoolField(ANSI_TO_TCHAR("multiplyValueSpecifyingQuantity"), v))
                  {
                        return TOptional(v);
                  }
                  return TOptional<bool>();
              }() : TOptional<bool>())
            ->WithTimeOffsetToken(Data->HasField(ANSI_TO_TCHAR("timeOffsetToken")) ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("timeOffsetToken"), v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
          ->WithDuplicationAvoider(Data->HasField(ANSI_TO_TCHAR("duplicationAvoider")) ? TOptional<FString>(Data->GetStringField(ANSI_TO_TCHAR("duplicationAvoider"))) : TOptional<FString>());
    }

    TSharedPtr<FJsonObject> FVerifyStaminaRecoverIntervalMinutesByUserIdRequest::ToJson() const
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
        if (StaminaNameValue.IsSet())
        {
            JsonRootObject->SetStringField("staminaName", StaminaNameValue.GetValue());
        }
        if (VerifyTypeValue.IsSet())
        {
            JsonRootObject->SetStringField("verifyType", VerifyTypeValue.GetValue());
        }
        if (ValueValue.IsSet())
        {
            JsonRootObject->SetNumberField("value", ValueValue.GetValue());
        }
        if (MultiplyValueSpecifyingQuantityValue.IsSet())
        {
            JsonRootObject->SetBoolField("multiplyValueSpecifyingQuantity", MultiplyValueSpecifyingQuantityValue.GetValue());
        }
        if (TimeOffsetTokenValue.IsSet())
        {
            JsonRootObject->SetStringField("timeOffsetToken", TimeOffsetTokenValue.GetValue());
        }
        if (DuplicationAvoiderValue.IsSet())
        {
            JsonRootObject->SetStringField("duplicationAvoider", DuplicationAvoiderValue.GetValue());
        }
        return JsonRootObject;
    }
}