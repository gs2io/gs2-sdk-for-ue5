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

#include "Money2/Request/WithdrawRequest.h"

namespace Gs2::Money2::Request
{
    FWithdrawRequest::FWithdrawRequest():
        NamespaceNameValue(TOptional<FString>()),
        AccessTokenValue(TOptional<FString>()),
        SlotValue(TOptional<int32>()),
        WithdrawCountValue(TOptional<int32>()),
        PaidOnlyValue(TOptional<bool>())
    {
    }

    FWithdrawRequest::FWithdrawRequest(
        const FWithdrawRequest& From
    ):
        NamespaceNameValue(From.NamespaceNameValue),
        AccessTokenValue(From.AccessTokenValue),
        SlotValue(From.SlotValue),
        WithdrawCountValue(From.WithdrawCountValue),
        PaidOnlyValue(From.PaidOnlyValue)
    {
    }

    TSharedPtr<FWithdrawRequest> FWithdrawRequest::WithContextStack(
        const TOptional<FString> ContextStack
    )
    {
        this->ContextStackValue = ContextStack;
        return SharedThis(this);
    }

    TSharedPtr<FWithdrawRequest> FWithdrawRequest::WithNamespaceName(
        const TOptional<FString> NamespaceName
    )
    {
        this->NamespaceNameValue = NamespaceName;
        return SharedThis(this);
    }

    TSharedPtr<FWithdrawRequest> FWithdrawRequest::WithAccessToken(
        const TOptional<FString> AccessToken
    )
    {
        this->AccessTokenValue = AccessToken;
        return SharedThis(this);
    }

    TSharedPtr<FWithdrawRequest> FWithdrawRequest::WithSlot(
        const TOptional<int32> Slot
    )
    {
        this->SlotValue = Slot;
        return SharedThis(this);
    }

    TSharedPtr<FWithdrawRequest> FWithdrawRequest::WithWithdrawCount(
        const TOptional<int32> WithdrawCount
    )
    {
        this->WithdrawCountValue = WithdrawCount;
        return SharedThis(this);
    }

    TSharedPtr<FWithdrawRequest> FWithdrawRequest::WithPaidOnly(
        const TOptional<bool> PaidOnly
    )
    {
        this->PaidOnlyValue = PaidOnly;
        return SharedThis(this);
    }

    TSharedPtr<FWithdrawRequest> FWithdrawRequest::WithDuplicationAvoider(
        const TOptional<FString> DuplicationAvoider
    )
    {
        this->DuplicationAvoiderValue = DuplicationAvoider;
        return SharedThis(this);
    }

    TOptional<FString> FWithdrawRequest::GetContextStack() const
    {
        return ContextStackValue;
    }

    TOptional<FString> FWithdrawRequest::GetNamespaceName() const
    {
        return NamespaceNameValue;
    }

    TOptional<FString> FWithdrawRequest::GetAccessToken() const
    {
        return AccessTokenValue;
    }

    TOptional<int32> FWithdrawRequest::GetSlot() const
    {
        return SlotValue;
    }

    FString FWithdrawRequest::GetSlotString() const
    {
        if (!SlotValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%d"), SlotValue.GetValue());
    }

    TOptional<int32> FWithdrawRequest::GetWithdrawCount() const
    {
        return WithdrawCountValue;
    }

    FString FWithdrawRequest::GetWithdrawCountString() const
    {
        if (!WithdrawCountValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%d"), WithdrawCountValue.GetValue());
    }

    TOptional<bool> FWithdrawRequest::GetPaidOnly() const
    {
        return PaidOnlyValue;
    }

    FString FWithdrawRequest::GetPaidOnlyString() const
    {
        if (!PaidOnlyValue.IsSet())
        {
            return FString("null");
        }
        return FString(PaidOnlyValue.GetValue() ? "true" : "false");
    }

    TOptional<FString> FWithdrawRequest::GetDuplicationAvoider() const
    {
        return DuplicationAvoiderValue;
    }

    TSharedPtr<FWithdrawRequest> FWithdrawRequest::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FWithdrawRequest>()
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
            ->WithSlot(Data->HasField(ANSI_TO_TCHAR("slot")) ? [Data]() -> TOptional<int32>
              {
                  int32 v;
                    if (Data->TryGetNumberField(ANSI_TO_TCHAR("slot"), v))
                  {
                        return TOptional(v);
                  }
                  return TOptional<int32>();
              }() : TOptional<int32>())
            ->WithWithdrawCount(Data->HasField(ANSI_TO_TCHAR("withdrawCount")) ? [Data]() -> TOptional<int32>
              {
                  int32 v;
                    if (Data->TryGetNumberField(ANSI_TO_TCHAR("withdrawCount"), v))
                  {
                        return TOptional(v);
                  }
                  return TOptional<int32>();
              }() : TOptional<int32>())
            ->WithPaidOnly(Data->HasField(ANSI_TO_TCHAR("paidOnly")) ? [Data]() -> TOptional<bool>
              {
                  bool v;
                    if (Data->TryGetBoolField(ANSI_TO_TCHAR("paidOnly"), v))
                  {
                        return TOptional(v);
                  }
                  return TOptional<bool>();
              }() : TOptional<bool>())
          ->WithDuplicationAvoider(Data->HasField(ANSI_TO_TCHAR("duplicationAvoider")) ? TOptional<FString>(Data->GetStringField(ANSI_TO_TCHAR("duplicationAvoider"))) : TOptional<FString>());
    }

    TSharedPtr<FJsonObject> FWithdrawRequest::ToJson() const
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
        if (SlotValue.IsSet())
        {
            JsonRootObject->SetNumberField("slot", SlotValue.GetValue());
        }
        if (WithdrawCountValue.IsSet())
        {
            JsonRootObject->SetNumberField("withdrawCount", WithdrawCountValue.GetValue());
        }
        if (PaidOnlyValue.IsSet())
        {
            JsonRootObject->SetBoolField("paidOnly", PaidOnlyValue.GetValue());
        }
        if (DuplicationAvoiderValue.IsSet())
        {
            JsonRootObject->SetStringField("duplicationAvoider", DuplicationAvoiderValue.GetValue());
        }
        return JsonRootObject;
    }
}