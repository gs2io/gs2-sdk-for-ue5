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

#include "Limit/Request/CountDownByUserIdRequest.h"

namespace Gs2::Limit::Request
{
    FCountDownByUserIdRequest::FCountDownByUserIdRequest():
        NamespaceNameValue(TOptional<FString>()),
        LimitNameValue(TOptional<FString>()),
        CounterNameValue(TOptional<FString>()),
        UserIdValue(TOptional<FString>()),
        CountDownValueValue(TOptional<int32>())
    {
    }

    FCountDownByUserIdRequest::FCountDownByUserIdRequest(
        const FCountDownByUserIdRequest& From
    ):
        NamespaceNameValue(From.NamespaceNameValue),
        LimitNameValue(From.LimitNameValue),
        CounterNameValue(From.CounterNameValue),
        UserIdValue(From.UserIdValue),
        CountDownValueValue(From.CountDownValueValue)
    {
    }

    TSharedPtr<FCountDownByUserIdRequest> FCountDownByUserIdRequest::WithContextStack(
        const TOptional<FString> ContextStack
    )
    {
        this->ContextStackValue = ContextStack;
        return SharedThis(this);
    }

    TSharedPtr<FCountDownByUserIdRequest> FCountDownByUserIdRequest::WithNamespaceName(
        const TOptional<FString> NamespaceName
    )
    {
        this->NamespaceNameValue = NamespaceName;
        return SharedThis(this);
    }

    TSharedPtr<FCountDownByUserIdRequest> FCountDownByUserIdRequest::WithLimitName(
        const TOptional<FString> LimitName
    )
    {
        this->LimitNameValue = LimitName;
        return SharedThis(this);
    }

    TSharedPtr<FCountDownByUserIdRequest> FCountDownByUserIdRequest::WithCounterName(
        const TOptional<FString> CounterName
    )
    {
        this->CounterNameValue = CounterName;
        return SharedThis(this);
    }

    TSharedPtr<FCountDownByUserIdRequest> FCountDownByUserIdRequest::WithUserId(
        const TOptional<FString> UserId
    )
    {
        this->UserIdValue = UserId;
        return SharedThis(this);
    }

    TSharedPtr<FCountDownByUserIdRequest> FCountDownByUserIdRequest::WithCountDownValue(
        const TOptional<int32> CountDownValue
    )
    {
        this->CountDownValueValue = CountDownValue;
        return SharedThis(this);
    }

    TSharedPtr<FCountDownByUserIdRequest> FCountDownByUserIdRequest::WithDuplicationAvoider(
        const TOptional<FString> DuplicationAvoider
    )
    {
        this->DuplicationAvoiderValue = DuplicationAvoider;
        return SharedThis(this);
    }

    TOptional<FString> FCountDownByUserIdRequest::GetContextStack() const
    {
        return ContextStackValue;
    }

    TOptional<FString> FCountDownByUserIdRequest::GetNamespaceName() const
    {
        return NamespaceNameValue;
    }

    TOptional<FString> FCountDownByUserIdRequest::GetLimitName() const
    {
        return LimitNameValue;
    }

    TOptional<FString> FCountDownByUserIdRequest::GetCounterName() const
    {
        return CounterNameValue;
    }

    TOptional<FString> FCountDownByUserIdRequest::GetUserId() const
    {
        return UserIdValue;
    }

    TOptional<int32> FCountDownByUserIdRequest::GetCountDownValue() const
    {
        return CountDownValueValue;
    }

    FString FCountDownByUserIdRequest::GetCountDownValueString() const
    {
        if (!CountDownValueValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%d"), CountDownValueValue.GetValue());
    }

    TOptional<FString> FCountDownByUserIdRequest::GetDuplicationAvoider() const
    {
        return DuplicationAvoiderValue;
    }

    TSharedPtr<FCountDownByUserIdRequest> FCountDownByUserIdRequest::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FCountDownByUserIdRequest>()
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
            ->WithLimitName(Data->HasField("limitName") ? [Data]() -> TOptional<FString>
              {
                  FString v;
                    if (Data->TryGetStringField("limitName", v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
            ->WithCounterName(Data->HasField("counterName") ? [Data]() -> TOptional<FString>
              {
                  FString v;
                    if (Data->TryGetStringField("counterName", v))
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
            ->WithCountDownValue(Data->HasField("countDownValue") ? [Data]() -> TOptional<int32>
              {
                  int32 v;
                    if (Data->TryGetNumberField("countDownValue", v))
                  {
                        return TOptional(v);
                  }
                  return TOptional<int32>();
              }() : TOptional<int32>())
          ->WithDuplicationAvoider(Data->HasField("duplicationAvoider") ? TOptional<FString>(Data->GetStringField("duplicationAvoider")) : TOptional<FString>());
    }

    TSharedPtr<FJsonObject> FCountDownByUserIdRequest::ToJson() const
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
        if (CountDownValueValue.IsSet())
        {
            JsonRootObject->SetNumberField("countDownValue", CountDownValueValue.GetValue());
        }
        if (DuplicationAvoiderValue.IsSet())
        {
            JsonRootObject->SetStringField("duplicationAvoider", DuplicationAvoiderValue.GetValue());
        }
        return JsonRootObject;
    }
}