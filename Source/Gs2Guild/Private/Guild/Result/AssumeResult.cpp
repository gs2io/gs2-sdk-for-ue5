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

#include "Guild/Result/AssumeResult.h"

namespace Gs2::Guild::Result
{
    FAssumeResult::FAssumeResult():
        TokenValue(TOptional<FString>()),
        UserIdValue(TOptional<FString>()),
        ExpireValue(TOptional<int64>())
    {
    }

    FAssumeResult::FAssumeResult(
        const FAssumeResult& From
    ):
        TokenValue(From.TokenValue),
        UserIdValue(From.UserIdValue),
        ExpireValue(From.ExpireValue)
    {
    }

    TSharedPtr<FAssumeResult> FAssumeResult::WithToken(
        const TOptional<FString> Token
    )
    {
        this->TokenValue = Token;
        return SharedThis(this);
    }

    TSharedPtr<FAssumeResult> FAssumeResult::WithUserId(
        const TOptional<FString> UserId
    )
    {
        this->UserIdValue = UserId;
        return SharedThis(this);
    }

    TSharedPtr<FAssumeResult> FAssumeResult::WithExpire(
        const TOptional<int64> Expire
    )
    {
        this->ExpireValue = Expire;
        return SharedThis(this);
    }

    TOptional<FString> FAssumeResult::GetToken() const
    {
        return TokenValue;
    }

    TOptional<FString> FAssumeResult::GetUserId() const
    {
        return UserIdValue;
    }

    TOptional<int64> FAssumeResult::GetExpire() const
    {
        return ExpireValue;
    }

    FString FAssumeResult::GetExpireString() const
    {
        if (!ExpireValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), ExpireValue.GetValue());
    }

    TSharedPtr<FAssumeResult> FAssumeResult::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FAssumeResult>()
            ->WithToken(Data->HasField(ANSI_TO_TCHAR("token")) ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("token"), v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithUserId(Data->HasField(ANSI_TO_TCHAR("userId")) ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("userId"), v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithExpire(Data->HasField(ANSI_TO_TCHAR("expire")) ? [Data]() -> TOptional<int64>
                {
                    int64 v;
                    if (Data->TryGetNumberField(ANSI_TO_TCHAR("expire"), v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<int64>();
                }() : TOptional<int64>());
    }

    TSharedPtr<FJsonObject> FAssumeResult::ToJson() const
    {
        const TSharedPtr<FJsonObject> JsonRootObject = MakeShared<FJsonObject>();
        if (TokenValue.IsSet())
        {
            JsonRootObject->SetStringField("token", TokenValue.GetValue());
        }
        if (UserIdValue.IsSet())
        {
            JsonRootObject->SetStringField("userId", UserIdValue.GetValue());
        }
        if (ExpireValue.IsSet())
        {
            JsonRootObject->SetStringField("expire", FString::Printf(TEXT("%lld"), ExpireValue.GetValue()));
        }
        return JsonRootObject;
    }
}