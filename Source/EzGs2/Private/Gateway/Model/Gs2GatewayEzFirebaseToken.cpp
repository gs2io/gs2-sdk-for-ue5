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

#include "Gateway/Model/Gs2GatewayEzFirebaseToken.h"

namespace Gs2::UE5::Gateway::Model
{

    TSharedPtr<FEzFirebaseToken> FEzFirebaseToken::WithUserId(
        const TOptional<FString> UserId
    )
    {
        this->UserIdValue = UserId;
        return SharedThis(this);
    }

    TSharedPtr<FEzFirebaseToken> FEzFirebaseToken::WithToken(
        const TOptional<FString> Token
    )
    {
        this->TokenValue = Token;
        return SharedThis(this);
    }

    TSharedPtr<FEzFirebaseToken> FEzFirebaseToken::WithLocale(
        const TOptional<FString> Locale
    )
    {
        this->LocaleValue = Locale;
        return SharedThis(this);
    }
    TOptional<FString> FEzFirebaseToken::GetUserId() const
    {
        return UserIdValue;
    }
    TOptional<FString> FEzFirebaseToken::GetToken() const
    {
        return TokenValue;
    }
    TOptional<FString> FEzFirebaseToken::GetLocale() const
    {
        return LocaleValue;
    }

    Gs2::Gateway::Model::FFirebaseTokenPtr FEzFirebaseToken::ToModel() const
    {
        return MakeShared<Gs2::Gateway::Model::FFirebaseToken>()
            ->WithUserId(UserIdValue)
            ->WithToken(TokenValue)
            ->WithLocale(LocaleValue);
    }

    TSharedPtr<FEzFirebaseToken> FEzFirebaseToken::FromModel(const Gs2::Gateway::Model::FFirebaseTokenPtr Model)
    {
        if (Model == nullptr)
        {
            return nullptr;
        }
        return MakeShared<FEzFirebaseToken>()
            ->WithUserId(Model->GetUserId())
            ->WithToken(Model->GetToken())
            ->WithLocale(Model->GetLocale());
    }
}