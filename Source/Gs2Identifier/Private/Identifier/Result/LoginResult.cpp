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
 *
 * deny overwrite
 */

#include "Identifier/Result/LoginResult.h"

namespace Gs2::Identifier::Result
{
    FLoginResult::FLoginResult():
        AccessTokenValue(TOptional<FString>()),
        TokenTypeValue(TOptional<FString>()),
        ExpiresInValue(TOptional<int32>())
    {
    }

    FLoginResult::FLoginResult(
        const FLoginResult& From
    ):
        AccessTokenValue(From.AccessTokenValue),
        TokenTypeValue(From.TokenTypeValue),
        ExpiresInValue(From.ExpiresInValue)
    {
    }

    TSharedPtr<FLoginResult> FLoginResult::WithAccessToken(
        const TOptional<FString> AccessToken
    )
    {
        this->AccessTokenValue = AccessToken;
        return SharedThis(this);
    }

    TSharedPtr<FLoginResult> FLoginResult::WithTokenType(
        const TOptional<FString> TokenType
    )
    {
        this->TokenTypeValue = TokenType;
        return SharedThis(this);
    }

    TSharedPtr<FLoginResult> FLoginResult::WithExpiresIn(
        const TOptional<int32> ExpiresIn
    )
    {
        this->ExpiresInValue = ExpiresIn;
        return SharedThis(this);
    }

    TOptional<FString> FLoginResult::GetAccessToken() const
    {
        return AccessTokenValue;
    }

    TOptional<FString> FLoginResult::GetTokenType() const
    {
        return TokenTypeValue;
    }

    TOptional<int32> FLoginResult::GetExpiresIn() const
    {
        return ExpiresInValue;
    }

    FString FLoginResult::GetExpiresInString() const
    {
        if (!ExpiresInValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%ld"), ExpiresInValue.GetValue());
    }

    TSharedPtr<FLoginResult> FLoginResult::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FLoginResult>()
            ->WithAccessToken(Data->HasField("access_token") ? [Data]() -> TOptional<FString>
                {
                    FString v;
                    if (Data->TryGetStringField("access_token", v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithTokenType(Data->HasField("token_type") ? [Data]() -> TOptional<FString>
                {
                    FString v;
                    if (Data->TryGetStringField("token_type", v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithExpiresIn(Data->HasField("expires_in") ? [Data]() -> TOptional<int32>
                {
                    int32 v;
                    if (Data->TryGetNumberField("expires_in", v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<int32>();
                }() : TOptional<int32>());
    }

    TSharedPtr<FJsonObject> FLoginResult::ToJson() const
    {
        const TSharedPtr<FJsonObject> JsonRootObject = MakeShared<FJsonObject>();
        if (AccessTokenValue.IsSet())
        {
            JsonRootObject->SetStringField("access_token", AccessTokenValue.GetValue());
        }
        if (TokenTypeValue.IsSet())
        {
            JsonRootObject->SetStringField("token_type", TokenTypeValue.GetValue());
        }
        if (ExpiresInValue.IsSet())
        {
            JsonRootObject->SetNumberField("expires_in", ExpiresInValue.GetValue());
        }
        return JsonRootObject;
    }
}