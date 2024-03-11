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

#include "Limit/Request/CountUpByUserIdRequest.h"

namespace Gs2::Limit::Request
{
    FCountUpByUserIdRequest::FCountUpByUserIdRequest():
        NamespaceNameValue(TOptional<FString>()),
        LimitNameValue(TOptional<FString>()),
        CounterNameValue(TOptional<FString>()),
        UserIdValue(TOptional<FString>()),
        CountUpValueValue(TOptional<int32>()),
        MaxValueValue(TOptional<int32>()),
        TimeOffsetTokenValue(TOptional<FString>())
    {
    }

    FCountUpByUserIdRequest::FCountUpByUserIdRequest(
        const FCountUpByUserIdRequest& From
    ):
        NamespaceNameValue(From.NamespaceNameValue),
        LimitNameValue(From.LimitNameValue),
        CounterNameValue(From.CounterNameValue),
        UserIdValue(From.UserIdValue),
        CountUpValueValue(From.CountUpValueValue),
        MaxValueValue(From.MaxValueValue),
        TimeOffsetTokenValue(From.TimeOffsetTokenValue)
    {
    }

    TSharedPtr<FCountUpByUserIdRequest> FCountUpByUserIdRequest::WithContextStack(
        const TOptional<FString> ContextStack
    )
    {
        this->ContextStackValue = ContextStack;
        return SharedThis(this);
    }

    TSharedPtr<FCountUpByUserIdRequest> FCountUpByUserIdRequest::WithNamespaceName(
        const TOptional<FString> NamespaceName
    )
    {
        this->NamespaceNameValue = NamespaceName;
        return SharedThis(this);
    }

    TSharedPtr<FCountUpByUserIdRequest> FCountUpByUserIdRequest::WithLimitName(
        const TOptional<FString> LimitName
    )
    {
        this->LimitNameValue = LimitName;
        return SharedThis(this);
    }

    TSharedPtr<FCountUpByUserIdRequest> FCountUpByUserIdRequest::WithCounterName(
        const TOptional<FString> CounterName
    )
    {
        this->CounterNameValue = CounterName;
        return SharedThis(this);
    }

    TSharedPtr<FCountUpByUserIdRequest> FCountUpByUserIdRequest::WithUserId(
        const TOptional<FString> UserId
    )
    {
        this->UserIdValue = UserId;
        return SharedThis(this);
    }

    TSharedPtr<FCountUpByUserIdRequest> FCountUpByUserIdRequest::WithCountUpValue(
        const TOptional<int32> CountUpValue
    )
    {
        this->CountUpValueValue = CountUpValue;
        return SharedThis(this);
    }

    TSharedPtr<FCountUpByUserIdRequest> FCountUpByUserIdRequest::WithMaxValue(
        const TOptional<int32> MaxValue
    )
    {
        this->MaxValueValue = MaxValue;
        return SharedThis(this);
    }

    TSharedPtr<FCountUpByUserIdRequest> FCountUpByUserIdRequest::WithTimeOffsetToken(
        const TOptional<FString> TimeOffsetToken
    )
    {
        this->TimeOffsetTokenValue = TimeOffsetToken;
        return SharedThis(this);
    }

    TSharedPtr<FCountUpByUserIdRequest> FCountUpByUserIdRequest::WithDuplicationAvoider(
        const TOptional<FString> DuplicationAvoider
    )
    {
        this->DuplicationAvoiderValue = DuplicationAvoider;
        return SharedThis(this);
    }

    TOptional<FString> FCountUpByUserIdRequest::GetContextStack() const
    {
        return ContextStackValue;
    }

    TOptional<FString> FCountUpByUserIdRequest::GetNamespaceName() const
    {
        return NamespaceNameValue;
    }

    TOptional<FString> FCountUpByUserIdRequest::GetLimitName() const
    {
        return LimitNameValue;
    }

    TOptional<FString> FCountUpByUserIdRequest::GetCounterName() const
    {
        return CounterNameValue;
    }

    TOptional<FString> FCountUpByUserIdRequest::GetUserId() const
    {
        return UserIdValue;
    }

    TOptional<int32> FCountUpByUserIdRequest::GetCountUpValue() const
    {
        return CountUpValueValue;
    }

    FString FCountUpByUserIdRequest::GetCountUpValueString() const
    {
        if (!CountUpValueValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%d"), CountUpValueValue.GetValue());
    }

    TOptional<int32> FCountUpByUserIdRequest::GetMaxValue() const
    {
        return MaxValueValue;
    }

    FString FCountUpByUserIdRequest::GetMaxValueString() const
    {
        if (!MaxValueValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%d"), MaxValueValue.GetValue());
    }

    TOptional<FString> FCountUpByUserIdRequest::GetTimeOffsetToken() const
    {
        return TimeOffsetTokenValue;
    }

    TOptional<FString> FCountUpByUserIdRequest::GetDuplicationAvoider() const
    {
        return DuplicationAvoiderValue;
    }

    TSharedPtr<FCountUpByUserIdRequest> FCountUpByUserIdRequest::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FCountUpByUserIdRequest>()
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
            ->WithLimitName(Data->HasField("limitName") ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField("limitName", v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
            ->WithCounterName(Data->HasField("counterName") ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField("counterName", v))
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
            ->WithCountUpValue(Data->HasField("countUpValue") ? [Data]() -> TOptional<int32>
              {
                  int32 v;
                    if (Data->TryGetNumberField("countUpValue", v))
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
            ->WithTimeOffsetToken(Data->HasField("timeOffsetToken") ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField("timeOffsetToken", v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
          ->WithDuplicationAvoider(Data->HasField("duplicationAvoider") ? TOptional<FString>(Data->GetStringField("duplicationAvoider")) : TOptional<FString>());
    }

    TSharedPtr<FJsonObject> FCountUpByUserIdRequest::ToJson() const
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
        if (LimitNameValue.IsSet())
        {
            JsonRootObject->SetStringField("limitName", LimitNameValue.GetValue());
        }
        if (CounterNameValue.IsSet())
        {
            JsonRootObject->SetStringField("counterName", CounterNameValue.GetValue());
        }
        if (UserIdValue.IsSet())
        {
            JsonRootObject->SetStringField("userId", UserIdValue.GetValue());
        }
        if (CountUpValueValue.IsSet())
        {
            JsonRootObject->SetNumberField("countUpValue", CountUpValueValue.GetValue());
        }
        if (MaxValueValue.IsSet())
        {
            JsonRootObject->SetNumberField("maxValue", MaxValueValue.GetValue());
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