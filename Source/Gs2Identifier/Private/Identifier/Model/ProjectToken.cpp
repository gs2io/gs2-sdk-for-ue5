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

#include "Identifier/Model/ProjectToken.h"

namespace Gs2::Identifier::Model
{
    FProjectToken::FProjectToken():
        TokenValue(TOptional<FString>())
    {
    }

    FProjectToken::FProjectToken(
        const FProjectToken& From
    ):
        TokenValue(From.TokenValue)
    {
    }

    TSharedPtr<FProjectToken> FProjectToken::WithToken(
        const TOptional<FString> Token
    )
    {
        this->TokenValue = Token;
        return SharedThis(this);
    }
    TOptional<FString> FProjectToken::GetToken() const
    {
        return TokenValue;
    }

    TSharedPtr<FProjectToken> FProjectToken::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FProjectToken>()
            ->WithToken(Data->HasField("token") ? [Data]() -> TOptional<FString>
                {
                    FString v;
                    if (Data->TryGetStringField("token", v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>());
    }

    TSharedPtr<FJsonObject> FProjectToken::ToJson() const
    {
        const TSharedPtr<FJsonObject> JsonRootObject = MakeShared<FJsonObject>();
        if (TokenValue.IsSet())
        {
            JsonRootObject->SetStringField("token", TokenValue.GetValue());
        }
        return JsonRootObject;
    }

    FString FProjectToken::TypeName = "ProjectToken";
}