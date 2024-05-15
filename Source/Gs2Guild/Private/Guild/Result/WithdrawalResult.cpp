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

#include "Guild/Result/WithdrawalResult.h"

namespace Gs2::Guild::Result
{
    FWithdrawalResult::FWithdrawalResult():
        ItemValue(nullptr),
        GuildValue(nullptr)
    {
    }

    FWithdrawalResult::FWithdrawalResult(
        const FWithdrawalResult& From
    ):
        ItemValue(From.ItemValue),
        GuildValue(From.GuildValue)
    {
    }

    TSharedPtr<FWithdrawalResult> FWithdrawalResult::WithItem(
        const TSharedPtr<Model::FJoinedGuild> Item
    )
    {
        this->ItemValue = Item;
        return SharedThis(this);
    }

    TSharedPtr<FWithdrawalResult> FWithdrawalResult::WithGuild(
        const TSharedPtr<Model::FGuild> Guild
    )
    {
        this->GuildValue = Guild;
        return SharedThis(this);
    }

    TSharedPtr<Model::FJoinedGuild> FWithdrawalResult::GetItem() const
    {
        if (!ItemValue.IsValid())
        {
            return nullptr;
        }
        return ItemValue;
    }

    TSharedPtr<Model::FGuild> FWithdrawalResult::GetGuild() const
    {
        if (!GuildValue.IsValid())
        {
            return nullptr;
        }
        return GuildValue;
    }

    TSharedPtr<FWithdrawalResult> FWithdrawalResult::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FWithdrawalResult>()
            ->WithItem(Data->HasField("item") ? [Data]() -> Model::FJoinedGuildPtr
                 {
                    if (Data->HasTypedField<EJson::Null>("item"))
                    {
                        return nullptr;
                    }
                    return Model::FJoinedGuild::FromJson(Data->GetObjectField("item"));
                 }() : nullptr)
            ->WithGuild(Data->HasField("guild") ? [Data]() -> Model::FGuildPtr
                 {
                    if (Data->HasTypedField<EJson::Null>("guild"))
                    {
                        return nullptr;
                    }
                    return Model::FGuild::FromJson(Data->GetObjectField("guild"));
                 }() : nullptr);
    }

    TSharedPtr<FJsonObject> FWithdrawalResult::ToJson() const
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