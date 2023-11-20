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

#include "Auth/Model/Gs2AuthEzAccessToken.h"

namespace Gs2::UE5::Auth::Model
{

    TSharedPtr<FEzAccessToken> FEzAccessToken::WithToken(
        const TOptional<FString> Token
    )
    {
        this->TokenValue = Token;
        return SharedThis(this);
    }

    TSharedPtr<FEzAccessToken> FEzAccessToken::WithUserId(
        const TOptional<FString> UserId
    )
    {
        this->UserIdValue = UserId;
        return SharedThis(this);
    }

    TSharedPtr<FEzAccessToken> FEzAccessToken::WithExpire(
        const TOptional<int64> Expire
    )
    {
        this->ExpireValue = Expire;
        return SharedThis(this);
    }
    TOptional<FString> FEzAccessToken::GetToken() const
    {
        return TokenValue;
    }
    TOptional<FString> FEzAccessToken::GetUserId() const
    {
        return UserIdValue;
    }
    TOptional<int64> FEzAccessToken::GetExpire() const
    {
        return ExpireValue;
    }

    FString FEzAccessToken::GetExpireString() const
    {
        if (!ExpireValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), ExpireValue.GetValue());
    }

    Gs2::Auth::Model::FAccessTokenPtr FEzAccessToken::ToModel() const
    {
        return MakeShared<Gs2::Auth::Model::FAccessToken>()
            ->WithToken(TokenValue)
            ->WithUserId(UserIdValue)
            ->WithExpire(ExpireValue);
    }

    TSharedPtr<FEzAccessToken> FEzAccessToken::FromModel(const Gs2::Auth::Model::FAccessTokenPtr Model)
    {
        if (Model == nullptr)
        {
            return nullptr;
        }
        return MakeShared<FEzAccessToken>()
            ->WithToken(Model->GetToken())
            ->WithUserId(Model->GetUserId())
            ->WithExpire(Model->GetExpire());
    }
}