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

#include "Auth/Request/FederationRequest.h"

namespace Gs2::Auth::Request
{
    FFederationRequest::FFederationRequest():
        OriginalUserIdValue(TOptional<FString>()),
        UserIdValue(TOptional<FString>()),
        PolicyDocumentValue(TOptional<FString>()),
        TimeOffsetValue(TOptional<int32>()),
        TimeOffsetTokenValue(TOptional<FString>())
    {
    }

    FFederationRequest::FFederationRequest(
        const FFederationRequest& From
    ):
        OriginalUserIdValue(From.OriginalUserIdValue),
        UserIdValue(From.UserIdValue),
        PolicyDocumentValue(From.PolicyDocumentValue),
        TimeOffsetValue(From.TimeOffsetValue),
        TimeOffsetTokenValue(From.TimeOffsetTokenValue)
    {
    }

    TSharedPtr<FFederationRequest> FFederationRequest::WithContextStack(
        const TOptional<FString> ContextStack
    )
    {
        this->ContextStackValue = ContextStack;
        return SharedThis(this);
    }

    TSharedPtr<FFederationRequest> FFederationRequest::WithOriginalUserId(
        const TOptional<FString> OriginalUserId
    )
    {
        this->OriginalUserIdValue = OriginalUserId;
        return SharedThis(this);
    }

    TSharedPtr<FFederationRequest> FFederationRequest::WithUserId(
        const TOptional<FString> UserId
    )
    {
        this->UserIdValue = UserId;
        return SharedThis(this);
    }

    TSharedPtr<FFederationRequest> FFederationRequest::WithPolicyDocument(
        const TOptional<FString> PolicyDocument
    )
    {
        this->PolicyDocumentValue = PolicyDocument;
        return SharedThis(this);
    }

    TSharedPtr<FFederationRequest> FFederationRequest::WithTimeOffset(
        const TOptional<int32> TimeOffset
    )
    {
        this->TimeOffsetValue = TimeOffset;
        return SharedThis(this);
    }

    TSharedPtr<FFederationRequest> FFederationRequest::WithTimeOffsetToken(
        const TOptional<FString> TimeOffsetToken
    )
    {
        this->TimeOffsetTokenValue = TimeOffsetToken;
        return SharedThis(this);
    }

    TOptional<FString> FFederationRequest::GetContextStack() const
    {
        return ContextStackValue;
    }

    TOptional<FString> FFederationRequest::GetOriginalUserId() const
    {
        return OriginalUserIdValue;
    }

    TOptional<FString> FFederationRequest::GetUserId() const
    {
        return UserIdValue;
    }

    TOptional<FString> FFederationRequest::GetPolicyDocument() const
    {
        return PolicyDocumentValue;
    }

    TOptional<int32> FFederationRequest::GetTimeOffset() const
    {
        return TimeOffsetValue;
    }

    FString FFederationRequest::GetTimeOffsetString() const
    {
        if (!TimeOffsetValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%d"), TimeOffsetValue.GetValue());
    }

    TOptional<FString> FFederationRequest::GetTimeOffsetToken() const
    {
        return TimeOffsetTokenValue;
    }

    TSharedPtr<FFederationRequest> FFederationRequest::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FFederationRequest>()
            ->WithContextStack(Data->HasField("contextStack") ? TOptional<FString>(Data->GetStringField("contextStack")) : TOptional<FString>())
            ->WithOriginalUserId(Data->HasField("originalUserId") ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField("originalUserId", v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
            ->WithUserId(Data->HasField("userId") ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField("userId", v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
            ->WithPolicyDocument(Data->HasField("policyDocument") ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField("policyDocument", v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
            ->WithTimeOffset(Data->HasField("timeOffset") ? [Data]() -> TOptional<int32>
              {
                  int32 v;
                    if (Data->TryGetNumberField("timeOffset", v))
                  {
                        return TOptional(v);
                  }
                  return TOptional<int32>();
              }() : TOptional<int32>())
            ->WithTimeOffsetToken(Data->HasField("timeOffsetToken") ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField("timeOffsetToken", v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>());
    }

    TSharedPtr<FJsonObject> FFederationRequest::ToJson() const
    {
        const TSharedPtr<FJsonObject> JsonRootObject = MakeShared<FJsonObject>();
        if (ContextStackValue.IsSet())
        {
            JsonRootObject->SetStringField("contextStack", ContextStackValue.GetValue());
        }
        if (OriginalUserIdValue.IsSet())
        {
            JsonRootObject->SetStringField("originalUserId", OriginalUserIdValue.GetValue());
        }
        if (UserIdValue.IsSet())
        {
            JsonRootObject->SetStringField("userId", UserIdValue.GetValue());
        }
        if (PolicyDocumentValue.IsSet())
        {
            JsonRootObject->SetStringField("policyDocument", PolicyDocumentValue.GetValue());
        }
        if (TimeOffsetValue.IsSet())
        {
            JsonRootObject->SetNumberField("timeOffset", TimeOffsetValue.GetValue());
        }
        if (TimeOffsetTokenValue.IsSet())
        {
            JsonRootObject->SetStringField("timeOffsetToken", TimeOffsetTokenValue.GetValue());
        }
        return JsonRootObject;
    }
}