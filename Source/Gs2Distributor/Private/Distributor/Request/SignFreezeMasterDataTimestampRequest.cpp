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

#include "Distributor/Request/SignFreezeMasterDataTimestampRequest.h"

namespace Gs2::Distributor::Request
{
    FSignFreezeMasterDataTimestampRequest::FSignFreezeMasterDataTimestampRequest():
        NamespaceNameValue(TOptional<FString>()),
        TimestampValue(TOptional<int64>()),
        KeyIdValue(TOptional<FString>())
    {
    }

    FSignFreezeMasterDataTimestampRequest::FSignFreezeMasterDataTimestampRequest(
        const FSignFreezeMasterDataTimestampRequest& From
    ):
        NamespaceNameValue(From.NamespaceNameValue),
        TimestampValue(From.TimestampValue),
        KeyIdValue(From.KeyIdValue)
    {
    }

    TSharedPtr<FSignFreezeMasterDataTimestampRequest> FSignFreezeMasterDataTimestampRequest::WithContextStack(
        const TOptional<FString> ContextStack
    )
    {
        this->ContextStackValue = ContextStack;
        return SharedThis(this);
    }

    TSharedPtr<FSignFreezeMasterDataTimestampRequest> FSignFreezeMasterDataTimestampRequest::WithNamespaceName(
        const TOptional<FString> NamespaceName
    )
    {
        this->NamespaceNameValue = NamespaceName;
        return SharedThis(this);
    }

    TSharedPtr<FSignFreezeMasterDataTimestampRequest> FSignFreezeMasterDataTimestampRequest::WithTimestamp(
        const TOptional<int64> Timestamp
    )
    {
        this->TimestampValue = Timestamp;
        return SharedThis(this);
    }

    TSharedPtr<FSignFreezeMasterDataTimestampRequest> FSignFreezeMasterDataTimestampRequest::WithKeyId(
        const TOptional<FString> KeyId
    )
    {
        this->KeyIdValue = KeyId;
        return SharedThis(this);
    }

    TOptional<FString> FSignFreezeMasterDataTimestampRequest::GetContextStack() const
    {
        return ContextStackValue;
    }

    TOptional<FString> FSignFreezeMasterDataTimestampRequest::GetNamespaceName() const
    {
        return NamespaceNameValue;
    }

    TOptional<int64> FSignFreezeMasterDataTimestampRequest::GetTimestamp() const
    {
        return TimestampValue;
    }

    FString FSignFreezeMasterDataTimestampRequest::GetTimestampString() const
    {
        if (!TimestampValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), TimestampValue.GetValue());
    }

    TOptional<FString> FSignFreezeMasterDataTimestampRequest::GetKeyId() const
    {
        return KeyIdValue;
    }

    TSharedPtr<FSignFreezeMasterDataTimestampRequest> FSignFreezeMasterDataTimestampRequest::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FSignFreezeMasterDataTimestampRequest>()
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
            ->WithTimestamp(Data->HasField(ANSI_TO_TCHAR("timestamp")) ? [Data]() -> TOptional<int64>
              {
                  int64 v;
                    if (Data->TryGetNumberField(ANSI_TO_TCHAR("timestamp"), v))
                  {
                        return TOptional(v);
                  }
                  return TOptional<int64>();
              }() : TOptional<int64>())
            ->WithKeyId(Data->HasField(ANSI_TO_TCHAR("keyId")) ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("keyId"), v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>());
    }

    TSharedPtr<FJsonObject> FSignFreezeMasterDataTimestampRequest::ToJson() const
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
        if (TimestampValue.IsSet())
        {
            JsonRootObject->SetStringField("timestamp", FString::Printf(TEXT("%lld"), TimestampValue.GetValue()));
        }
        if (KeyIdValue.IsSet())
        {
            JsonRootObject->SetStringField("keyId", KeyIdValue.GetValue());
        }
        return JsonRootObject;
    }
}