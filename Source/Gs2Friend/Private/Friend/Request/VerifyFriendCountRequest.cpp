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

#include "Friend/Request/VerifyFriendCountRequest.h"

namespace Gs2::Friend::Request
{
    FVerifyFriendCountRequest::FVerifyFriendCountRequest():
        NamespaceNameValue(TOptional<FString>()),
        AccessTokenValue(TOptional<FString>()),
        VerifyTypeValue(TOptional<FString>()),
        CountValue(TOptional<int32>())
    {
    }

    FVerifyFriendCountRequest::FVerifyFriendCountRequest(
        const FVerifyFriendCountRequest& From
    ):
        NamespaceNameValue(From.NamespaceNameValue),
        AccessTokenValue(From.AccessTokenValue),
        VerifyTypeValue(From.VerifyTypeValue),
        CountValue(From.CountValue)
    {
    }

    TSharedPtr<FVerifyFriendCountRequest> FVerifyFriendCountRequest::WithContextStack(
        const TOptional<FString> ContextStack
    )
    {
        this->ContextStackValue = ContextStack;
        return SharedThis(this);
    }

    TSharedPtr<FVerifyFriendCountRequest> FVerifyFriendCountRequest::WithNamespaceName(
        const TOptional<FString> NamespaceName
    )
    {
        this->NamespaceNameValue = NamespaceName;
        return SharedThis(this);
    }

    TSharedPtr<FVerifyFriendCountRequest> FVerifyFriendCountRequest::WithAccessToken(
        const TOptional<FString> AccessToken
    )
    {
        this->AccessTokenValue = AccessToken;
        return SharedThis(this);
    }

    TSharedPtr<FVerifyFriendCountRequest> FVerifyFriendCountRequest::WithVerifyType(
        const TOptional<FString> VerifyType
    )
    {
        this->VerifyTypeValue = VerifyType;
        return SharedThis(this);
    }

    TSharedPtr<FVerifyFriendCountRequest> FVerifyFriendCountRequest::WithCount(
        const TOptional<int32> Count
    )
    {
        this->CountValue = Count;
        return SharedThis(this);
    }

    TSharedPtr<FVerifyFriendCountRequest> FVerifyFriendCountRequest::WithDuplicationAvoider(
        const TOptional<FString> DuplicationAvoider
    )
    {
        this->DuplicationAvoiderValue = DuplicationAvoider;
        return SharedThis(this);
    }

    TOptional<FString> FVerifyFriendCountRequest::GetContextStack() const
    {
        return ContextStackValue;
    }

    TOptional<FString> FVerifyFriendCountRequest::GetNamespaceName() const
    {
        return NamespaceNameValue;
    }

    TOptional<FString> FVerifyFriendCountRequest::GetAccessToken() const
    {
        return AccessTokenValue;
    }

    TOptional<FString> FVerifyFriendCountRequest::GetVerifyType() const
    {
        return VerifyTypeValue;
    }

    TOptional<int32> FVerifyFriendCountRequest::GetCount() const
    {
        return CountValue;
    }

    FString FVerifyFriendCountRequest::GetCountString() const
    {
        if (!CountValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%d"), CountValue.GetValue());
    }

    TOptional<FString> FVerifyFriendCountRequest::GetDuplicationAvoider() const
    {
        return DuplicationAvoiderValue;
    }

    TSharedPtr<FVerifyFriendCountRequest> FVerifyFriendCountRequest::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FVerifyFriendCountRequest>()
            ->WithContextStack(Data->HasField(ANSI_TO_TCHAR("contextStack")) ? TOptional<FString>(Data->GetStringField(ANSI_TO_TCHAR("contextStack"))) : TOptional<FString>())
            ->WithNamespaceName(Data->HasField(ANSI_TO_TCHAR("namespaceName")) ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("namespaceName"), v))
                  {
                        return TOptional(v);
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
            ->WithAccessToken(Data->HasField(ANSI_TO_TCHAR("xGs2AccessToken")) ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("xGs2AccessToken"), v))
                  {
                        return TOptional(v);
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
            ->WithVerifyType(Data->HasField(ANSI_TO_TCHAR("verifyType")) ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("verifyType"), v))
                  {
                        return TOptional(v);
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
            ->WithCount(Data->HasField(ANSI_TO_TCHAR("count")) ? [Data]() -> TOptional<int32>
              {
                  int32 v;
                    if (Data->TryGetNumberField(ANSI_TO_TCHAR("count"), v))
                  {
                        return TOptional(v);
                  }
                  return TOptional<int32>();
              }() : TOptional<int32>())
          ->WithDuplicationAvoider(Data->HasField(ANSI_TO_TCHAR("duplicationAvoider")) ? TOptional<FString>(Data->GetStringField(ANSI_TO_TCHAR("duplicationAvoider"))) : TOptional<FString>());
    }

    TSharedPtr<FJsonObject> FVerifyFriendCountRequest::ToJson() const
    {
        const TSharedPtr<FJsonObject> JsonRootObject = MakeShared<FJsonObject>();
        if (ContextStackValue.IsSet())
        {
            JsonRootObject->SetStringField(TEXT("contextStack"), ContextStackValue.GetValue());
        }
        if (NamespaceNameValue.IsSet())
        {
            JsonRootObject->SetStringField(TEXT("namespaceName"), NamespaceNameValue.GetValue());
        }
        if (AccessTokenValue.IsSet())
        {
            JsonRootObject->SetStringField(TEXT("xGs2AccessToken"), AccessTokenValue.GetValue());
        }
        if (VerifyTypeValue.IsSet())
        {
            JsonRootObject->SetStringField(TEXT("verifyType"), VerifyTypeValue.GetValue());
        }
        if (CountValue.IsSet())
        {
            JsonRootObject->SetNumberField(TEXT("count"), CountValue.GetValue());
        }
        if (DuplicationAvoiderValue.IsSet())
        {
            JsonRootObject->SetStringField(TEXT("duplicationAvoider"), DuplicationAvoiderValue.GetValue());
        }
        return JsonRootObject;
    }
}