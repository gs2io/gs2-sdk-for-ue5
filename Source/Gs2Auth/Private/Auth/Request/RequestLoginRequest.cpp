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

#include "Auth/Request/LoginRequest.h"

namespace Gs2::Auth::Request
{
    FLoginRequest::FLoginRequest():
        UserIdValue(TOptional<FString>()),
        TimeOffsetValue(TOptional<int32>())
    {
    }

    FLoginRequest::FLoginRequest(
        const FLoginRequest& From
    ):
        UserIdValue(From.UserIdValue),
        TimeOffsetValue(From.TimeOffsetValue)
    {
    }

    TSharedPtr<FLoginRequest> FLoginRequest::WithContextStack(
        const TOptional<FString> ContextStack
    )
    {
        this->ContextStackValue = ContextStack;
        return SharedThis(this);
    }

    TSharedPtr<FLoginRequest> FLoginRequest::WithUserId(
        const TOptional<FString> UserId
    )
    {
        this->UserIdValue = UserId;
        return SharedThis(this);
    }

    TSharedPtr<FLoginRequest> FLoginRequest::WithTimeOffset(
        const TOptional<int32> TimeOffset
    )
    {
        this->TimeOffsetValue = TimeOffset;
        return SharedThis(this);
    }

    TOptional<FString> FLoginRequest::GetContextStack() const
    {
        return ContextStackValue;
    }

    TOptional<FString> FLoginRequest::GetUserId() const
    {
        return UserIdValue;
    }

    TOptional<int32> FLoginRequest::GetTimeOffset() const
    {
        return TimeOffsetValue;
    }

    FString FLoginRequest::GetTimeOffsetString() const
    {
        if (!TimeOffsetValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%ld"), TimeOffsetValue.GetValue());
    }

    TSharedPtr<FLoginRequest> FLoginRequest::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FLoginRequest>()
            ->WithContextStack(Data->HasField("contextStack") ? TOptional<FString>(Data->GetStringField("contextStack")) : TOptional<FString>())
            ->WithUserId(Data->HasField("userId") ? [Data]() -> TOptional<FString>
              {
                  FString v;
                    if (Data->TryGetStringField("userId", v))
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
              }() : TOptional<int32>());
    }

    TSharedPtr<FJsonObject> FLoginRequest::ToJson() const
    {
        const TSharedPtr<FJsonObject> JsonRootObject = MakeShared<FJsonObject>();
        if (ContextStackValue.IsSet())
        {
            JsonRootObject->SetStringField("contextStack", ContextStackValue.GetValue());
        }
        if (UserIdValue.IsSet())
        {
            JsonRootObject->SetStringField("userId", UserIdValue.GetValue());
        }
        if (TimeOffsetValue.IsSet())
        {
            JsonRootObject->SetNumberField("timeOffset", TimeOffsetValue.GetValue());
        }
        return JsonRootObject;
    }
}