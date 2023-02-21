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

#include "Lock/Request/LockRequest.h"

namespace Gs2::Lock::Request
{
    FLockRequest::FLockRequest():
        NamespaceNameValue(TOptional<FString>()),
        PropertyIdValue(TOptional<FString>()),
        AccessTokenValue(TOptional<FString>()),
        TransactionIdValue(TOptional<FString>()),
        TtlValue(TOptional<int64>())
    {
    }

    FLockRequest::FLockRequest(
        const FLockRequest& From
    ):
        NamespaceNameValue(From.NamespaceNameValue),
        PropertyIdValue(From.PropertyIdValue),
        AccessTokenValue(From.AccessTokenValue),
        TransactionIdValue(From.TransactionIdValue),
        TtlValue(From.TtlValue)
    {
    }

    TSharedPtr<FLockRequest> FLockRequest::WithContextStack(
        const TOptional<FString> ContextStack
    )
    {
        this->ContextStackValue = ContextStack;
        return SharedThis(this);
    }

    TSharedPtr<FLockRequest> FLockRequest::WithNamespaceName(
        const TOptional<FString> NamespaceName
    )
    {
        this->NamespaceNameValue = NamespaceName;
        return SharedThis(this);
    }

    TSharedPtr<FLockRequest> FLockRequest::WithPropertyId(
        const TOptional<FString> PropertyId
    )
    {
        this->PropertyIdValue = PropertyId;
        return SharedThis(this);
    }

    TSharedPtr<FLockRequest> FLockRequest::WithAccessToken(
        const TOptional<FString> AccessToken
    )
    {
        this->AccessTokenValue = AccessToken;
        return SharedThis(this);
    }

    TSharedPtr<FLockRequest> FLockRequest::WithTransactionId(
        const TOptional<FString> TransactionId
    )
    {
        this->TransactionIdValue = TransactionId;
        return SharedThis(this);
    }

    TSharedPtr<FLockRequest> FLockRequest::WithTtl(
        const TOptional<int64> Ttl
    )
    {
        this->TtlValue = Ttl;
        return SharedThis(this);
    }

    TSharedPtr<FLockRequest> FLockRequest::WithDuplicationAvoider(
        const TOptional<FString> DuplicationAvoider
    )
    {
        this->DuplicationAvoiderValue = DuplicationAvoider;
        return SharedThis(this);
    }

    TOptional<FString> FLockRequest::GetContextStack() const
    {
        return ContextStackValue;
    }

    TOptional<FString> FLockRequest::GetNamespaceName() const
    {
        return NamespaceNameValue;
    }

    TOptional<FString> FLockRequest::GetPropertyId() const
    {
        return PropertyIdValue;
    }

    TOptional<FString> FLockRequest::GetAccessToken() const
    {
        return AccessTokenValue;
    }

    TOptional<FString> FLockRequest::GetTransactionId() const
    {
        return TransactionIdValue;
    }

    TOptional<int64> FLockRequest::GetTtl() const
    {
        return TtlValue;
    }

    FString FLockRequest::GetTtlString() const
    {
        if (!TtlValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), TtlValue.GetValue());
    }

    TOptional<FString> FLockRequest::GetDuplicationAvoider() const
    {
        return DuplicationAvoiderValue;
    }

    TSharedPtr<FLockRequest> FLockRequest::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FLockRequest>()
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
            ->WithAccessToken(Data->HasField("xGs2AccessToken") ? [Data]() -> TOptional<FString>
              {
                  FString v;
                    if (Data->TryGetStringField("xGs2AccessToken", v))
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

    TSharedPtr<FJsonObject> FLockRequest::ToJson() const
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
        if (AccessTokenValue.IsSet())
        {
            JsonRootObject->SetStringField("xGs2AccessToken", AccessTokenValue.GetValue());
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