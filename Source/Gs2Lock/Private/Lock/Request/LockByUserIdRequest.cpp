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

#include "Lock/Request/LockByUserIdRequest.h"

namespace Gs2::Lock::Request
{
    FLockByUserIdRequest::FLockByUserIdRequest():
        NamespaceNameValue(TOptional<FString>()),
        PropertyIdValue(TOptional<FString>()),
        UserIdValue(TOptional<FString>()),
        TransactionIdValue(TOptional<FString>()),
        TtlValue(TOptional<int64>())
    {
    }

    FLockByUserIdRequest::FLockByUserIdRequest(
        const FLockByUserIdRequest& From
    ):
        NamespaceNameValue(From.NamespaceNameValue),
        PropertyIdValue(From.PropertyIdValue),
        UserIdValue(From.UserIdValue),
        TransactionIdValue(From.TransactionIdValue),
        TtlValue(From.TtlValue)
    {
    }

    TSharedPtr<FLockByUserIdRequest> FLockByUserIdRequest::WithContextStack(
        const TOptional<FString> ContextStack
    )
    {
        this->ContextStackValue = ContextStack;
        return SharedThis(this);
    }

    TSharedPtr<FLockByUserIdRequest> FLockByUserIdRequest::WithNamespaceName(
        const TOptional<FString> NamespaceName
    )
    {
        this->NamespaceNameValue = NamespaceName;
        return SharedThis(this);
    }

    TSharedPtr<FLockByUserIdRequest> FLockByUserIdRequest::WithPropertyId(
        const TOptional<FString> PropertyId
    )
    {
        this->PropertyIdValue = PropertyId;
        return SharedThis(this);
    }

    TSharedPtr<FLockByUserIdRequest> FLockByUserIdRequest::WithUserId(
        const TOptional<FString> UserId
    )
    {
        this->UserIdValue = UserId;
        return SharedThis(this);
    }

    TSharedPtr<FLockByUserIdRequest> FLockByUserIdRequest::WithTransactionId(
        const TOptional<FString> TransactionId
    )
    {
        this->TransactionIdValue = TransactionId;
        return SharedThis(this);
    }

    TSharedPtr<FLockByUserIdRequest> FLockByUserIdRequest::WithTtl(
        const TOptional<int64> Ttl
    )
    {
        this->TtlValue = Ttl;
        return SharedThis(this);
    }

    TSharedPtr<FLockByUserIdRequest> FLockByUserIdRequest::WithDuplicationAvoider(
        const TOptional<FString> DuplicationAvoider
    )
    {
        this->DuplicationAvoiderValue = DuplicationAvoider;
        return SharedThis(this);
    }

    TOptional<FString> FLockByUserIdRequest::GetContextStack() const
    {
        return ContextStackValue;
    }

    TOptional<FString> FLockByUserIdRequest::GetNamespaceName() const
    {
        return NamespaceNameValue;
    }

    TOptional<FString> FLockByUserIdRequest::GetPropertyId() const
    {
        return PropertyIdValue;
    }

    TOptional<FString> FLockByUserIdRequest::GetUserId() const
    {
        return UserIdValue;
    }

    TOptional<FString> FLockByUserIdRequest::GetTransactionId() const
    {
        return TransactionIdValue;
    }

    TOptional<int64> FLockByUserIdRequest::GetTtl() const
    {
        return TtlValue;
    }

    FString FLockByUserIdRequest::GetTtlString() const
    {
        if (!TtlValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), TtlValue.GetValue());
    }

    TOptional<FString> FLockByUserIdRequest::GetDuplicationAvoider() const
    {
        return DuplicationAvoiderValue;
    }

    TSharedPtr<FLockByUserIdRequest> FLockByUserIdRequest::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FLockByUserIdRequest>()
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
            ->WithPropertyId(Data->HasField("propertyId") ? [Data]() -> TOptional<FString>
              {
                  FString v;
                    if (Data->TryGetStringField("propertyId", v))
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
            ->WithTransactionId(Data->HasField("transactionId") ? [Data]() -> TOptional<FString>
              {
                  FString v;
                    if (Data->TryGetStringField("transactionId", v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
            ->WithTtl(Data->HasField("ttl") ? [Data]() -> TOptional<int64>
              {
                  int64 v;
                    if (Data->TryGetNumberField("ttl", v))
                  {
                        return TOptional(v);
                  }
                  return TOptional<int64>();
              }() : TOptional<int64>())
          ->WithDuplicationAvoider(Data->HasField("duplicationAvoider") ? TOptional<FString>(Data->GetStringField("duplicationAvoider")) : TOptional<FString>());
    }

    TSharedPtr<FJsonObject> FLockByUserIdRequest::ToJson() const
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
        if (PropertyIdValue.IsSet())
        {
            JsonRootObject->SetStringField("propertyId", PropertyIdValue.GetValue());
        }
        if (UserIdValue.IsSet())
        {
            JsonRootObject->SetStringField("userId", UserIdValue.GetValue());
        }
        if (TransactionIdValue.IsSet())
        {
            JsonRootObject->SetStringField("transactionId", TransactionIdValue.GetValue());
        }
        if (TtlValue.IsSet())
        {
            JsonRootObject->SetStringField("ttl", FString::Printf(TEXT("%lld"), TtlValue.GetValue()));
        }
        if (DuplicationAvoiderValue.IsSet())
        {
            JsonRootObject->SetStringField("duplicationAvoider", DuplicationAvoiderValue.GetValue());
        }
        return JsonRootObject;
    }
}