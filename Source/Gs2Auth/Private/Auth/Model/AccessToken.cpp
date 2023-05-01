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

#include "Auth/Model/AccessToken.h"

namespace Gs2::Auth::Model
{
    FAccessToken::FAccessToken():
        TokenValue(TOptional<FString>()),
        UserIdValue(TOptional<FString>()),
        ExpireValue(TOptional<int64>()),
        TimeOffsetValue(TOptional<int32>())
    {
    }

    FAccessToken::FAccessToken(
        const FAccessToken& From
    ):
        TokenValue(From.TokenValue),
        UserIdValue(From.UserIdValue),
        ExpireValue(From.ExpireValue),
        TimeOffsetValue(From.TimeOffsetValue)
    {
    }

    TSharedPtr<FAccessToken> FAccessToken::WithToken(
        const TOptional<FString> Token
    )
    {
        this->TokenValue = Token;
        return SharedThis(this);
    }

    TSharedPtr<FAccessToken> FAccessToken::WithUserId(
        const TOptional<FString> UserId
    )
    {
        this->UserIdValue = UserId;
        return SharedThis(this);
    }

    TSharedPtr<FAccessToken> FAccessToken::WithExpire(
        const TOptional<int64> Expire
    )
    {
        this->ExpireValue = Expire;
        return SharedThis(this);
    }

    TSharedPtr<FAccessToken> FAccessToken::WithTimeOffset(
        const TOptional<int32> TimeOffset
    )
    {
        this->TimeOffsetValue = TimeOffset;
        return SharedThis(this);
    }
    TOptional<FString> FAccessToken::GetToken() const
    {
        return TokenValue;
    }
    TOptional<FString> FAccessToken::GetUserId() const
    {
        return UserIdValue;
    }
    TOptional<int64> FAccessToken::GetExpire() const
    {
        return ExpireValue;
    }

    FString FAccessToken::GetExpireString() const
    {
        if (!ExpireValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), ExpireValue.GetValue());
    }
    TOptional<int32> FAccessToken::GetTimeOffset() const
    {
        return TimeOffsetValue;
    }

    FString FAccessToken::GetTimeOffsetString() const
    {
        if (!TimeOffsetValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%d"), TimeOffsetValue.GetValue());
    }

    TSharedPtr<FAccessToken> FAccessToken::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FAccessToken>()
            ->WithToken(Data->HasField("token") ? [Data]() -> TOptional<FString>
                {
                    FString v;
                    if (Data->TryGetStringField("token", v))
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
            ->WithExpire(Data->HasField("expire") ? [Data]() -> TOptional<int64>
                {
                    int64 v;
                    if (Data->TryGetNumberField("expire", v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<int64>();
                }() : TOptional<int64>())
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

    TSharedPtr<FJsonObject> FAccessToken::ToJson() const
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
        if (TimeOffsetValue.IsSet())
        {
            JsonRootObject->SetNumberField("timeOffset", TimeOffsetValue.GetValue());
        }
        return JsonRootObject;
    }

    FString FAccessToken::TypeName = "AccessToken";
}