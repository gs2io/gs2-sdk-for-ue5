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

#include "Money2/Request/TakeoverSubscriptionStatusRequest.h"

namespace Gs2::Money2::Request
{
    FTakeoverSubscriptionStatusRequest::FTakeoverSubscriptionStatusRequest():
        NamespaceNameValue(TOptional<FString>()),
        AccessTokenValue(TOptional<FString>()),
        ReceiptValue(nullptr)
    {
    }

    FTakeoverSubscriptionStatusRequest::FTakeoverSubscriptionStatusRequest(
        const FTakeoverSubscriptionStatusRequest& From
    ):
        NamespaceNameValue(From.NamespaceNameValue),
        AccessTokenValue(From.AccessTokenValue),
        ReceiptValue(From.ReceiptValue)
    {
    }

    TSharedPtr<FTakeoverSubscriptionStatusRequest> FTakeoverSubscriptionStatusRequest::WithContextStack(
        const TOptional<FString> ContextStack
    )
    {
        this->ContextStackValue = ContextStack;
        return SharedThis(this);
    }

    TSharedPtr<FTakeoverSubscriptionStatusRequest> FTakeoverSubscriptionStatusRequest::WithNamespaceName(
        const TOptional<FString> NamespaceName
    )
    {
        this->NamespaceNameValue = NamespaceName;
        return SharedThis(this);
    }

    TSharedPtr<FTakeoverSubscriptionStatusRequest> FTakeoverSubscriptionStatusRequest::WithAccessToken(
        const TOptional<FString> AccessToken
    )
    {
        this->AccessTokenValue = AccessToken;
        return SharedThis(this);
    }

    TSharedPtr<FTakeoverSubscriptionStatusRequest> FTakeoverSubscriptionStatusRequest::WithReceipt(
        const TSharedPtr<Model::FReceipt> Receipt
    )
    {
        this->ReceiptValue = Receipt;
        return SharedThis(this);
    }

    TSharedPtr<FTakeoverSubscriptionStatusRequest> FTakeoverSubscriptionStatusRequest::WithDuplicationAvoider(
        const TOptional<FString> DuplicationAvoider
    )
    {
        this->DuplicationAvoiderValue = DuplicationAvoider;
        return SharedThis(this);
    }

    TOptional<FString> FTakeoverSubscriptionStatusRequest::GetContextStack() const
    {
        return ContextStackValue;
    }

    TOptional<FString> FTakeoverSubscriptionStatusRequest::GetNamespaceName() const
    {
        return NamespaceNameValue;
    }

    TOptional<FString> FTakeoverSubscriptionStatusRequest::GetAccessToken() const
    {
        return AccessTokenValue;
    }

    TSharedPtr<Model::FReceipt> FTakeoverSubscriptionStatusRequest::GetReceipt() const
    {
        if (!ReceiptValue.IsValid())
        {
            return nullptr;
        }
        return ReceiptValue;
    }

    TOptional<FString> FTakeoverSubscriptionStatusRequest::GetDuplicationAvoider() const
    {
        return DuplicationAvoiderValue;
    }

    TSharedPtr<FTakeoverSubscriptionStatusRequest> FTakeoverSubscriptionStatusRequest::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FTakeoverSubscriptionStatusRequest>()
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
            ->WithAccessToken(Data->HasField(ANSI_TO_TCHAR("xGs2AccessToken")) ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("xGs2AccessToken"), v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
          ->WithReceipt(Data->HasField(ANSI_TO_TCHAR("receipt")) ? [Data]() -> Model::FReceiptPtr
              {
                  if (Data->HasTypedField<EJson::Null>(ANSI_TO_TCHAR("receipt")))
                  {
                      return nullptr;
                  }
                  return Model::FReceipt::FromJson(Data->GetObjectField(ANSI_TO_TCHAR("receipt")));
              }() : nullptr)
          ->WithDuplicationAvoider(Data->HasField(ANSI_TO_TCHAR("duplicationAvoider")) ? TOptional<FString>(Data->GetStringField(ANSI_TO_TCHAR("duplicationAvoider"))) : TOptional<FString>());
    }

    TSharedPtr<FJsonObject> FTakeoverSubscriptionStatusRequest::ToJson() const
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
        if (AccessTokenValue.IsSet())
        {
            JsonRootObject->SetStringField("xGs2AccessToken", AccessTokenValue.GetValue());
        }
        if (ReceiptValue != nullptr && ReceiptValue.IsValid())
        {
            JsonRootObject->SetObjectField("receipt", ReceiptValue->ToJson());
        }
        if (DuplicationAvoiderValue.IsSet())
        {
            JsonRootObject->SetStringField("duplicationAvoider", DuplicationAvoiderValue.GetValue());
        }
        return JsonRootObject;
    }
}