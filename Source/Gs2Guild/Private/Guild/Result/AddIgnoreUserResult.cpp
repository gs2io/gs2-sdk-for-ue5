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

#include "Guild/Result/AddIgnoreUserResult.h"

namespace Gs2::Guild::Result
{
    FAddIgnoreUserResult::FAddIgnoreUserResult():
        ItemValue(nullptr),
        GuildValue(nullptr)
    {
    }

    FAddIgnoreUserResult::FAddIgnoreUserResult(
        const FAddIgnoreUserResult& From
    ):
        ItemValue(From.ItemValue),
        GuildValue(From.GuildValue)
    {
    }

    TSharedPtr<FAddIgnoreUserResult> FAddIgnoreUserResult::WithItem(
        const TSharedPtr<Model::FIgnoreUser> Item
    )
    {
        this->ItemValue = Item;
        return SharedThis(this);
    }

    TSharedPtr<FAddIgnoreUserResult> FAddIgnoreUserResult::WithGuild(
        const TSharedPtr<Model::FGuild> Guild
    )
    {
        this->GuildValue = Guild;
        return SharedThis(this);
    }

    TSharedPtr<Model::FIgnoreUser> FAddIgnoreUserResult::GetItem() const
    {
        if (!ItemValue.IsValid())
        {
            return nullptr;
        }
        return ItemValue;
    }

    TSharedPtr<Model::FGuild> FAddIgnoreUserResult::GetGuild() const
    {
        if (!GuildValue.IsValid())
        {
            return nullptr;
        }
        return GuildValue;
    }

    TSharedPtr<FAddIgnoreUserResult> FAddIgnoreUserResult::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FAddIgnoreUserResult>()
            ->WithItem(Data->HasField(ANSI_TO_TCHAR("item")) ? [Data]() -> Model::FIgnoreUserPtr
                 {
                    if (Data->HasTypedField<EJson::Null>(ANSI_TO_TCHAR("item")))
                    {
                        return nullptr;
                    }
                    return Model::FIgnoreUser::FromJson(Data->GetObjectField(ANSI_TO_TCHAR("item")));
                 }() : nullptr)
            ->WithGuild(Data->HasField(ANSI_TO_TCHAR("guild")) ? [Data]() -> Model::FGuildPtr
                 {
                    if (Data->HasTypedField<EJson::Null>(ANSI_TO_TCHAR("guild")))
                    {
                        return nullptr;
                    }
                    return Model::FGuild::FromJson(Data->GetObjectField(ANSI_TO_TCHAR("guild")));
                 }() : nullptr);
    }

    TSharedPtr<FJsonObject> FAddIgnoreUserResult::ToJson() const
    {
        const TSharedPtr<FJsonObject> JsonRootObject = MakeShared<FJsonObject>();
        if (ItemValue != nullptr && ItemValue.IsValid())
        {
            JsonRootObject->SetObjectField("item", ItemValue->ToJson());
        }
        if (GuildValue != nullptr && GuildValue.IsValid())
        {
            JsonRootObject->SetObjectField("guild", GuildValue->ToJson());
        }
        return JsonRootObject;
    }
}