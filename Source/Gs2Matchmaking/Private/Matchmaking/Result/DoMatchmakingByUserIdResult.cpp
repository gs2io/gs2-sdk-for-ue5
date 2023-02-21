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

#include "Matchmaking/Result/DoMatchmakingByUserIdResult.h"

namespace Gs2::Matchmaking::Result
{
    FDoMatchmakingByUserIdResult::FDoMatchmakingByUserIdResult():
        ItemValue(nullptr),
        MatchmakingContextTokenValue(TOptional<FString>())
    {
    }

    FDoMatchmakingByUserIdResult::FDoMatchmakingByUserIdResult(
        const FDoMatchmakingByUserIdResult& From
    ):
        ItemValue(From.ItemValue),
        MatchmakingContextTokenValue(From.MatchmakingContextTokenValue)
    {
    }

    TSharedPtr<FDoMatchmakingByUserIdResult> FDoMatchmakingByUserIdResult::WithItem(
        const TSharedPtr<Model::FGathering> Item
    )
    {
        this->ItemValue = Item;
        return SharedThis(this);
    }

    TSharedPtr<FDoMatchmakingByUserIdResult> FDoMatchmakingByUserIdResult::WithMatchmakingContextToken(
        const TOptional<FString> MatchmakingContextToken
    )
    {
        this->MatchmakingContextTokenValue = MatchmakingContextToken;
        return SharedThis(this);
    }

    TSharedPtr<Model::FGathering> FDoMatchmakingByUserIdResult::GetItem() const
    {
        if (!ItemValue.IsValid())
        {
            return nullptr;
        }
        return ItemValue;
    }

    TOptional<FString> FDoMatchmakingByUserIdResult::GetMatchmakingContextToken() const
    {
        return MatchmakingContextTokenValue;
    }

    TSharedPtr<FDoMatchmakingByUserIdResult> FDoMatchmakingByUserIdResult::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FDoMatchmakingByUserIdResult>()
            ->WithItem(Data->HasField("item") ? [Data]() -> Model::FGatheringPtr
                 {
                    if (Data->HasTypedField<EJson::Null>("item"))
                    {
                        return nullptr;
                    }
                    return Model::FGathering::FromJson(Data->GetObjectField("item"));
                 }() : nullptr)
            ->WithMatchmakingContextToken(Data->HasField("matchmakingContextToken") ? [Data]() -> TOptional<FString>
                {
                    FString v;
                    if (Data->TryGetStringField("matchmakingContextToken", v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>());
    }

    TSharedPtr<FJsonObject> FDoMatchmakingByUserIdResult::ToJson() const
    {
        const TSharedPtr<FJsonObject> JsonRootObject = MakeShared<FJsonObject>();
        if (ItemValue != nullptr && ItemValue.IsValid())
        {
            JsonRootObject->SetObjectField("item", ItemValue->ToJson());
        }
        if (MatchmakingContextTokenValue.IsSet())
        {
            JsonRootObject->SetStringField("matchmakingContextToken", MatchmakingContextTokenValue.GetValue());
        }
        return JsonRootObject;
    }
}