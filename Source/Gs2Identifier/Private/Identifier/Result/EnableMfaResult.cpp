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

#include "Identifier/Result/EnableMfaResult.h"

namespace Gs2::Identifier::Result
{
    FEnableMfaResult::FEnableMfaResult():
        ItemValue(nullptr),
        ChallengeTokenValue(TOptional<FString>())
    {
    }

    FEnableMfaResult::FEnableMfaResult(
        const FEnableMfaResult& From
    ):
        ItemValue(From.ItemValue),
        ChallengeTokenValue(From.ChallengeTokenValue)
    {
    }

    TSharedPtr<FEnableMfaResult> FEnableMfaResult::WithItem(
        const TSharedPtr<Model::FPassword> Item
    )
    {
        this->ItemValue = Item;
        return SharedThis(this);
    }

    TSharedPtr<FEnableMfaResult> FEnableMfaResult::WithChallengeToken(
        const TOptional<FString> ChallengeToken
    )
    {
        this->ChallengeTokenValue = ChallengeToken;
        return SharedThis(this);
    }

    TSharedPtr<Model::FPassword> FEnableMfaResult::GetItem() const
    {
        if (!ItemValue.IsValid())
        {
            return nullptr;
        }
        return ItemValue;
    }

    TOptional<FString> FEnableMfaResult::GetChallengeToken() const
    {
        return ChallengeTokenValue;
    }

    TSharedPtr<FEnableMfaResult> FEnableMfaResult::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FEnableMfaResult>()
            ->WithItem(Data->HasField(ANSI_TO_TCHAR("item")) ? [Data]() -> Model::FPasswordPtr
                 {
                    if (Data->HasTypedField<EJson::Null>(ANSI_TO_TCHAR("item")))
                    {
                        return nullptr;
                    }
                    return Model::FPassword::FromJson(Data->GetObjectField(ANSI_TO_TCHAR("item")));
                 }() : nullptr)
            ->WithChallengeToken(Data->HasField(ANSI_TO_TCHAR("challengeToken")) ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("challengeToken"), v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>());
    }

    TSharedPtr<FJsonObject> FEnableMfaResult::ToJson() const
    {
        const TSharedPtr<FJsonObject> JsonRootObject = MakeShared<FJsonObject>();
        if (ItemValue != nullptr && ItemValue.IsValid())
        {
            JsonRootObject->SetObjectField("item", ItemValue->ToJson());
        }
        if (ChallengeTokenValue.IsSet())
        {
            JsonRootObject->SetStringField("challengeToken", ChallengeTokenValue.GetValue());
        }
        return JsonRootObject;
    }
}