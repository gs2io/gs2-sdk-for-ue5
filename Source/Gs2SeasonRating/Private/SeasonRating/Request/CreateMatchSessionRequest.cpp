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

#include "SeasonRating/Request/CreateMatchSessionRequest.h"

namespace Gs2::SeasonRating::Request
{
    FCreateMatchSessionRequest::FCreateMatchSessionRequest():
        NamespaceNameValue(TOptional<FString>()),
        SessionNameValue(TOptional<FString>()),
        TtlSecondsValue(TOptional<int32>())
    {
    }

    FCreateMatchSessionRequest::FCreateMatchSessionRequest(
        const FCreateMatchSessionRequest& From
    ):
        NamespaceNameValue(From.NamespaceNameValue),
        SessionNameValue(From.SessionNameValue),
        TtlSecondsValue(From.TtlSecondsValue)
    {
    }

    TSharedPtr<FCreateMatchSessionRequest> FCreateMatchSessionRequest::WithContextStack(
        const TOptional<FString> ContextStack
    )
    {
        this->ContextStackValue = ContextStack;
        return SharedThis(this);
    }

    TSharedPtr<FCreateMatchSessionRequest> FCreateMatchSessionRequest::WithNamespaceName(
        const TOptional<FString> NamespaceName
    )
    {
        this->NamespaceNameValue = NamespaceName;
        return SharedThis(this);
    }

    TSharedPtr<FCreateMatchSessionRequest> FCreateMatchSessionRequest::WithSessionName(
        const TOptional<FString> SessionName
    )
    {
        this->SessionNameValue = SessionName;
        return SharedThis(this);
    }

    TSharedPtr<FCreateMatchSessionRequest> FCreateMatchSessionRequest::WithTtlSeconds(
        const TOptional<int32> TtlSeconds
    )
    {
        this->TtlSecondsValue = TtlSeconds;
        return SharedThis(this);
    }

    TOptional<FString> FCreateMatchSessionRequest::GetContextStack() const
    {
        return ContextStackValue;
    }

    TOptional<FString> FCreateMatchSessionRequest::GetNamespaceName() const
    {
        return NamespaceNameValue;
    }

    TOptional<FString> FCreateMatchSessionRequest::GetSessionName() const
    {
        return SessionNameValue;
    }

    TOptional<int32> FCreateMatchSessionRequest::GetTtlSeconds() const
    {
        return TtlSecondsValue;
    }

    FString FCreateMatchSessionRequest::GetTtlSecondsString() const
    {
        if (!TtlSecondsValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%d"), TtlSecondsValue.GetValue());
    }

    TSharedPtr<FCreateMatchSessionRequest> FCreateMatchSessionRequest::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FCreateMatchSessionRequest>()
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
            ->WithSessionName(Data->HasField(ANSI_TO_TCHAR("sessionName")) ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("sessionName"), v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
            ->WithTtlSeconds(Data->HasField(ANSI_TO_TCHAR("ttlSeconds")) ? [Data]() -> TOptional<int32>
              {
                  int32 v;
                    if (Data->TryGetNumberField(ANSI_TO_TCHAR("ttlSeconds"), v))
                  {
                        return TOptional(v);
                  }
                  return TOptional<int32>();
              }() : TOptional<int32>());
    }

    TSharedPtr<FJsonObject> FCreateMatchSessionRequest::ToJson() const
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
        if (SessionNameValue.IsSet())
        {
            JsonRootObject->SetStringField("sessionName", SessionNameValue.GetValue());
        }
        if (TtlSecondsValue.IsSet())
        {
            JsonRootObject->SetNumberField("ttlSeconds", TtlSecondsValue.GetValue());
        }
        return JsonRootObject;
    }
}