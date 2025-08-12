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

#include "Friend/Request/GetSendRequestRequest.h"

namespace Gs2::Friend::Request
{
    FGetSendRequestRequest::FGetSendRequestRequest():
        NamespaceNameValue(TOptional<FString>()),
        AccessTokenValue(TOptional<FString>()),
        TargetUserIdValue(TOptional<FString>()),
        WithProfileValue(TOptional<bool>())
    {
    }

    FGetSendRequestRequest::FGetSendRequestRequest(
        const FGetSendRequestRequest& From
    ):
        NamespaceNameValue(From.NamespaceNameValue),
        AccessTokenValue(From.AccessTokenValue),
        TargetUserIdValue(From.TargetUserIdValue),
        WithProfileValue(From.WithProfileValue)
    {
    }

    TSharedPtr<FGetSendRequestRequest> FGetSendRequestRequest::WithContextStack(
        const TOptional<FString> ContextStack
    )
    {
        this->ContextStackValue = ContextStack;
        return SharedThis(this);
    }

    TSharedPtr<FGetSendRequestRequest> FGetSendRequestRequest::WithNamespaceName(
        const TOptional<FString> NamespaceName
    )
    {
        this->NamespaceNameValue = NamespaceName;
        return SharedThis(this);
    }

    TSharedPtr<FGetSendRequestRequest> FGetSendRequestRequest::WithAccessToken(
        const TOptional<FString> AccessToken
    )
    {
        this->AccessTokenValue = AccessToken;
        return SharedThis(this);
    }

    TSharedPtr<FGetSendRequestRequest> FGetSendRequestRequest::WithTargetUserId(
        const TOptional<FString> TargetUserId
    )
    {
        this->TargetUserIdValue = TargetUserId;
        return SharedThis(this);
    }

    TSharedPtr<FGetSendRequestRequest> FGetSendRequestRequest::WithWithProfile(
        const TOptional<bool> WithProfile
    )
    {
        this->WithProfileValue = WithProfile;
        return SharedThis(this);
    }

    TOptional<FString> FGetSendRequestRequest::GetContextStack() const
    {
        return ContextStackValue;
    }

    TOptional<FString> FGetSendRequestRequest::GetNamespaceName() const
    {
        return NamespaceNameValue;
    }

    TOptional<FString> FGetSendRequestRequest::GetAccessToken() const
    {
        return AccessTokenValue;
    }

    TOptional<FString> FGetSendRequestRequest::GetTargetUserId() const
    {
        return TargetUserIdValue;
    }

    TOptional<bool> FGetSendRequestRequest::GetWithProfile() const
    {
        return WithProfileValue;
    }

    FString FGetSendRequestRequest::GetWithProfileString() const
    {
        if (!WithProfileValue.IsSet())
        {
            return FString("null");
        }
        return FString(WithProfileValue.GetValue() ? "true" : "false");
    }

    TSharedPtr<FGetSendRequestRequest> FGetSendRequestRequest::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FGetSendRequestRequest>()
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
            ->WithTargetUserId(Data->HasField(ANSI_TO_TCHAR("targetUserId")) ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("targetUserId"), v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
            ->WithWithProfile(Data->HasField(ANSI_TO_TCHAR("withProfile")) ? [Data]() -> TOptional<bool>
              {
                  bool v;
                    if (Data->TryGetBoolField(ANSI_TO_TCHAR("withProfile"), v))
                  {
                        return TOptional(v);
                  }
                  return TOptional<bool>();
              }() : TOptional<bool>());
    }

    TSharedPtr<FJsonObject> FGetSendRequestRequest::ToJson() const
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
        if (TargetUserIdValue.IsSet())
        {
            JsonRootObject->SetStringField("targetUserId", TargetUserIdValue.GetValue());
        }
        if (WithProfileValue.IsSet())
        {
            JsonRootObject->SetBoolField("withProfile", WithProfileValue.GetValue());
        }
        return JsonRootObject;
    }
}