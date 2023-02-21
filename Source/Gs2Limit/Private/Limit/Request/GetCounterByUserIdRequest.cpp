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

#include "Limit/Request/GetCounterByUserIdRequest.h"

namespace Gs2::Limit::Request
{
    FGetCounterByUserIdRequest::FGetCounterByUserIdRequest():
        NamespaceNameValue(TOptional<FString>()),
        LimitNameValue(TOptional<FString>()),
        UserIdValue(TOptional<FString>()),
        CounterNameValue(TOptional<FString>())
    {
    }

    FGetCounterByUserIdRequest::FGetCounterByUserIdRequest(
        const FGetCounterByUserIdRequest& From
    ):
        NamespaceNameValue(From.NamespaceNameValue),
        LimitNameValue(From.LimitNameValue),
        UserIdValue(From.UserIdValue),
        CounterNameValue(From.CounterNameValue)
    {
    }

    TSharedPtr<FGetCounterByUserIdRequest> FGetCounterByUserIdRequest::WithContextStack(
        const TOptional<FString> ContextStack
    )
    {
        this->ContextStackValue = ContextStack;
        return SharedThis(this);
    }

    TSharedPtr<FGetCounterByUserIdRequest> FGetCounterByUserIdRequest::WithNamespaceName(
        const TOptional<FString> NamespaceName
    )
    {
        this->NamespaceNameValue = NamespaceName;
        return SharedThis(this);
    }

    TSharedPtr<FGetCounterByUserIdRequest> FGetCounterByUserIdRequest::WithLimitName(
        const TOptional<FString> LimitName
    )
    {
        this->LimitNameValue = LimitName;
        return SharedThis(this);
    }

    TSharedPtr<FGetCounterByUserIdRequest> FGetCounterByUserIdRequest::WithUserId(
        const TOptional<FString> UserId
    )
    {
        this->UserIdValue = UserId;
        return SharedThis(this);
    }

    TSharedPtr<FGetCounterByUserIdRequest> FGetCounterByUserIdRequest::WithCounterName(
        const TOptional<FString> CounterName
    )
    {
        this->CounterNameValue = CounterName;
        return SharedThis(this);
    }

    TOptional<FString> FGetCounterByUserIdRequest::GetContextStack() const
    {
        return ContextStackValue;
    }

    TOptional<FString> FGetCounterByUserIdRequest::GetNamespaceName() const
    {
        return NamespaceNameValue;
    }

    TOptional<FString> FGetCounterByUserIdRequest::GetLimitName() const
    {
        return LimitNameValue;
    }

    TOptional<FString> FGetCounterByUserIdRequest::GetUserId() const
    {
        return UserIdValue;
    }

    TOptional<FString> FGetCounterByUserIdRequest::GetCounterName() const
    {
        return CounterNameValue;
    }

    TSharedPtr<FGetCounterByUserIdRequest> FGetCounterByUserIdRequest::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FGetCounterByUserIdRequest>()
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
            ->WithUserId(Data->HasField("userId") ? [Data]() -> TOptional<FString>
              {
                  FString v;
                    if (Data->TryGetStringField("userId", v))
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
              }() : TOptional<FString>());
    }

    TSharedPtr<FJsonObject> FGetCounterByUserIdRequest::ToJson() const
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
        if (UserIdValue.IsSet())
        {
            JsonRootObject->SetStringField("userId", UserIdValue.GetValue());
        }
        if (CounterNameValue.IsSet())
        {
            JsonRootObject->SetStringField("counterName", CounterNameValue.GetValue());
        }
        return JsonRootObject;
    }
}