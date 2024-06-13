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

#include "Matchmaking/Result/DoSeasonMatchmakingResult.h"

namespace Gs2::Matchmaking::Result
{
    FDoSeasonMatchmakingResult::FDoSeasonMatchmakingResult():
        ItemValue(nullptr),
        MatchmakingContextTokenValue(TOptional<FString>())
    {
    }

    FDoSeasonMatchmakingResult::FDoSeasonMatchmakingResult(
        const FDoSeasonMatchmakingResult& From
    ):
        ItemValue(From.ItemValue),
        MatchmakingContextTokenValue(From.MatchmakingContextTokenValue)
    {
    }

    TSharedPtr<FDoSeasonMatchmakingResult> FDoSeasonMatchmakingResult::WithItem(
        const TSharedPtr<Model::FSeasonGathering> Item
    )
    {
        this->ItemValue = Item;
        return SharedThis(this);
    }

    TSharedPtr<FDoSeasonMatchmakingResult> FDoSeasonMatchmakingResult::WithMatchmakingContextToken(
        const TOptional<FString> MatchmakingContextToken
    )
    {
        this->MatchmakingContextTokenValue = MatchmakingContextToken;
        return SharedThis(this);
    }

    TSharedPtr<Model::FSeasonGathering> FDoSeasonMatchmakingResult::GetItem() const
    {
        if (!ItemValue.IsValid())
        {
            return nullptr;
        }
        return ItemValue;
    }

    TOptional<FString> FDoSeasonMatchmakingResult::GetMatchmakingContextToken() const
    {
        return MatchmakingContextTokenValue;
    }

    TSharedPtr<FDoSeasonMatchmakingResult> FDoSeasonMatchmakingResult::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FDoSeasonMatchmakingResult>()
            ->WithItem(Data->HasField(ANSI_TO_TCHAR("item")) ? [Data]() -> Model::FSeasonGatheringPtr
                 {
                    if (Data->HasTypedField<EJson::Null>(ANSI_TO_TCHAR("item")))
                    {
                        return nullptr;
                    }
                    return Model::FSeasonGathering::FromJson(Data->GetObjectField(ANSI_TO_TCHAR("item")));
                 }() : nullptr)
            ->WithMatchmakingContextToken(Data->HasField(ANSI_TO_TCHAR("matchmakingContextToken")) ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("matchmakingContextToken"), v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>());
    }

    TSharedPtr<FJsonObject> FDoSeasonMatchmakingResult::ToJson() const
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