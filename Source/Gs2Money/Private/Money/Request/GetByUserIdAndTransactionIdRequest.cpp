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

#include "Money/Request/GetByUserIdAndTransactionIdRequest.h"

namespace Gs2::Money::Request
{
    FGetByUserIdAndTransactionIdRequest::FGetByUserIdAndTransactionIdRequest():
        NamespaceNameValue(TOptional<FString>()),
        UserIdValue(TOptional<FString>()),
        TransactionIdValue(TOptional<FString>())
    {
    }

    FGetByUserIdAndTransactionIdRequest::FGetByUserIdAndTransactionIdRequest(
        const FGetByUserIdAndTransactionIdRequest& From
    ):
        NamespaceNameValue(From.NamespaceNameValue),
        UserIdValue(From.UserIdValue),
        TransactionIdValue(From.TransactionIdValue)
    {
    }

    TSharedPtr<FGetByUserIdAndTransactionIdRequest> FGetByUserIdAndTransactionIdRequest::WithContextStack(
        const TOptional<FString> ContextStack
    )
    {
        this->ContextStackValue = ContextStack;
        return SharedThis(this);
    }

    TSharedPtr<FGetByUserIdAndTransactionIdRequest> FGetByUserIdAndTransactionIdRequest::WithNamespaceName(
        const TOptional<FString> NamespaceName
    )
    {
        this->NamespaceNameValue = NamespaceName;
        return SharedThis(this);
    }

    TSharedPtr<FGetByUserIdAndTransactionIdRequest> FGetByUserIdAndTransactionIdRequest::WithUserId(
        const TOptional<FString> UserId
    )
    {
        this->UserIdValue = UserId;
        return SharedThis(this);
    }

    TSharedPtr<FGetByUserIdAndTransactionIdRequest> FGetByUserIdAndTransactionIdRequest::WithTransactionId(
        const TOptional<FString> TransactionId
    )
    {
        this->TransactionIdValue = TransactionId;
        return SharedThis(this);
    }

    TOptional<FString> FGetByUserIdAndTransactionIdRequest::GetContextStack() const
    {
        return ContextStackValue;
    }

    TOptional<FString> FGetByUserIdAndTransactionIdRequest::GetNamespaceName() const
    {
        return NamespaceNameValue;
    }

    TOptional<FString> FGetByUserIdAndTransactionIdRequest::GetUserId() const
    {
        return UserIdValue;
    }

    TOptional<FString> FGetByUserIdAndTransactionIdRequest::GetTransactionId() const
    {
        return TransactionIdValue;
    }

    TSharedPtr<FGetByUserIdAndTransactionIdRequest> FGetByUserIdAndTransactionIdRequest::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FGetByUserIdAndTransactionIdRequest>()
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
              }() : TOptional<FString>());
    }

    TSharedPtr<FJsonObject> FGetByUserIdAndTransactionIdRequest::ToJson() const
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
        if (TransactionIdValue.IsSet())
        {
            JsonRootObject->SetStringField("transactionId", TransactionIdValue.GetValue());
        }
        return JsonRootObject;
    }
}