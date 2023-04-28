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

#include "Stamina/Request/UpdateStaminaByUserIdRequest.h"

namespace Gs2::Stamina::Request
{
    FUpdateStaminaByUserIdRequest::FUpdateStaminaByUserIdRequest():
        NamespaceNameValue(TOptional<FString>()),
        StaminaNameValue(TOptional<FString>()),
        UserIdValue(TOptional<FString>()),
        ValueValue(TOptional<int32>()),
        MaxValueValue(TOptional<int32>()),
        RecoverIntervalMinutesValue(TOptional<int32>()),
        RecoverValueValue(TOptional<int32>())
    {
    }

    FUpdateStaminaByUserIdRequest::FUpdateStaminaByUserIdRequest(
        const FUpdateStaminaByUserIdRequest& From
    ):
        NamespaceNameValue(From.NamespaceNameValue),
        StaminaNameValue(From.StaminaNameValue),
        UserIdValue(From.UserIdValue),
        ValueValue(From.ValueValue),
        MaxValueValue(From.MaxValueValue),
        RecoverIntervalMinutesValue(From.RecoverIntervalMinutesValue),
        RecoverValueValue(From.RecoverValueValue)
    {
    }

    TSharedPtr<FUpdateStaminaByUserIdRequest> FUpdateStaminaByUserIdRequest::WithContextStack(
        const TOptional<FString> ContextStack
    )
    {
        this->ContextStackValue = ContextStack;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateStaminaByUserIdRequest> FUpdateStaminaByUserIdRequest::WithNamespaceName(
        const TOptional<FString> NamespaceName
    )
    {
        this->NamespaceNameValue = NamespaceName;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateStaminaByUserIdRequest> FUpdateStaminaByUserIdRequest::WithStaminaName(
        const TOptional<FString> StaminaName
    )
    {
        this->StaminaNameValue = StaminaName;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateStaminaByUserIdRequest> FUpdateStaminaByUserIdRequest::WithUserId(
        const TOptional<FString> UserId
    )
    {
        this->UserIdValue = UserId;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateStaminaByUserIdRequest> FUpdateStaminaByUserIdRequest::WithValue(
        const TOptional<int32> Value
    )
    {
        this->ValueValue = Value;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateStaminaByUserIdRequest> FUpdateStaminaByUserIdRequest::WithMaxValue(
        const TOptional<int32> MaxValue
    )
    {
        this->MaxValueValue = MaxValue;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateStaminaByUserIdRequest> FUpdateStaminaByUserIdRequest::WithRecoverIntervalMinutes(
        const TOptional<int32> RecoverIntervalMinutes
    )
    {
        this->RecoverIntervalMinutesValue = RecoverIntervalMinutes;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateStaminaByUserIdRequest> FUpdateStaminaByUserIdRequest::WithRecoverValue(
        const TOptional<int32> RecoverValue
    )
    {
        this->RecoverValueValue = RecoverValue;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateStaminaByUserIdRequest> FUpdateStaminaByUserIdRequest::WithDuplicationAvoider(
        const TOptional<FString> DuplicationAvoider
    )
    {
        this->DuplicationAvoiderValue = DuplicationAvoider;
        return SharedThis(this);
    }

    TOptional<FString> FUpdateStaminaByUserIdRequest::GetContextStack() const
    {
        return ContextStackValue;
    }

    TOptional<FString> FUpdateStaminaByUserIdRequest::GetNamespaceName() const
    {
        return NamespaceNameValue;
    }

    TOptional<FString> FUpdateStaminaByUserIdRequest::GetStaminaName() const
    {
        return StaminaNameValue;
    }

    TOptional<FString> FUpdateStaminaByUserIdRequest::GetUserId() const
    {
        return UserIdValue;
    }

    TOptional<int32> FUpdateStaminaByUserIdRequest::GetValue() const
    {
        return ValueValue;
    }

    FString FUpdateStaminaByUserIdRequest::GetValueString() const
    {
        if (!ValueValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%d"), ValueValue.GetValue());
    }

    TOptional<int32> FUpdateStaminaByUserIdRequest::GetMaxValue() const
    {
        return MaxValueValue;
    }

    FString FUpdateStaminaByUserIdRequest::GetMaxValueString() const
    {
        if (!MaxValueValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%d"), MaxValueValue.GetValue());
    }

    TOptional<int32> FUpdateStaminaByUserIdRequest::GetRecoverIntervalMinutes() const
    {
        return RecoverIntervalMinutesValue;
    }

    FString FUpdateStaminaByUserIdRequest::GetRecoverIntervalMinutesString() const
    {
        if (!RecoverIntervalMinutesValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%d"), RecoverIntervalMinutesValue.GetValue());
    }

    TOptional<int32> FUpdateStaminaByUserIdRequest::GetRecoverValue() const
    {
        return RecoverValueValue;
    }

    FString FUpdateStaminaByUserIdRequest::GetRecoverValueString() const
    {
        if (!RecoverValueValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%d"), RecoverValueValue.GetValue());
    }

    TOptional<FString> FUpdateStaminaByUserIdRequest::GetDuplicationAvoider() const
    {
        return DuplicationAvoiderValue;
    }

    TSharedPtr<FUpdateStaminaByUserIdRequest> FUpdateStaminaByUserIdRequest::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FUpdateStaminaByUserIdRequest>()
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
            ->WithValue(Data->HasField("value") ? [Data]() -> TOptional<int32>
              {
                  int32 v;
                    if (Data->TryGetNumberField("value", v))
                  {
                        return TOptional(v);
                  }
                  return TOptional<int32>();
              }() : TOptional<int32>())
            ->WithMaxValue(Data->HasField("maxValue") ? [Data]() -> TOptional<int32>
              {
                  int32 v;
                    if (Data->TryGetNumberField("maxValue", v))
                  {
                        return TOptional(v);
                  }
                  return TOptional<int32>();
              }() : TOptional<int32>())
            ->WithRecoverIntervalMinutes(Data->HasField("recoverIntervalMinutes") ? [Data]() -> TOptional<int32>
              {
                  int32 v;
                    if (Data->TryGetNumberField("recoverIntervalMinutes", v))
                  {
                        return TOptional(v);
                  }
                  return TOptional<int32>();
              }() : TOptional<int32>())
            ->WithRecoverValue(Data->HasField("recoverValue") ? [Data]() -> TOptional<int32>
              {
                  int32 v;
                    if (Data->TryGetNumberField("recoverValue", v))
                  {
                        return TOptional(v);
                  }
                  return TOptional<int32>();
              }() : TOptional<int32>())
          ->WithDuplicationAvoider(Data->HasField("duplicationAvoider") ? TOptional<FString>(Data->GetStringField("duplicationAvoider")) : TOptional<FString>());
    }

    TSharedPtr<FJsonObject> FUpdateStaminaByUserIdRequest::ToJson() const
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
        if (ValueValue.IsSet())
        {
            JsonRootObject->SetNumberField("value", ValueValue.GetValue());
        }
        if (MaxValueValue.IsSet())
        {
            JsonRootObject->SetNumberField("maxValue", MaxValueValue.GetValue());
        }
        if (RecoverIntervalMinutesValue.IsSet())
        {
            JsonRootObject->SetNumberField("recoverIntervalMinutes", RecoverIntervalMinutesValue.GetValue());
        }
        if (RecoverValueValue.IsSet())
        {
            JsonRootObject->SetNumberField("recoverValue", RecoverValueValue.GetValue());
        }
        if (DuplicationAvoiderValue.IsSet())
        {
            JsonRootObject->SetStringField("duplicationAvoider", DuplicationAvoiderValue.GetValue());
        }
        return JsonRootObject;
    }
}