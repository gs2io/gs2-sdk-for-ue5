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

#include "Guild/Result/AcceptRequestResult.h"

namespace Gs2::Guild::Result
{
    FAcceptRequestResult::FAcceptRequestResult():
        ItemValue(nullptr),
        GuildValue(nullptr)
    {
    }

    FAcceptRequestResult::FAcceptRequestResult(
        const FAcceptRequestResult& From
    ):
        ItemValue(From.ItemValue),
        GuildValue(From.GuildValue)
    {
    }

    TSharedPtr<FAcceptRequestResult> FAcceptRequestResult::WithItem(
        const TSharedPtr<Model::FReceiveMemberRequest> Item
    )
    {
        this->ItemValue = Item;
        return SharedThis(this);
    }

    TSharedPtr<FAcceptRequestResult> FAcceptRequestResult::WithGuild(
        const TSharedPtr<Model::FGuild> Guild
    )
    {
        this->GuildValue = Guild;
        return SharedThis(this);
    }

    TSharedPtr<Model::FReceiveMemberRequest> FAcceptRequestResult::GetItem() const
    {
        if (!ItemValue.IsValid())
        {
            return nullptr;
        }
        return ItemValue;
    }

    TSharedPtr<Model::FGuild> FAcceptRequestResult::GetGuild() const
    {
        if (!GuildValue.IsValid())
        {
            return nullptr;
        }
        return GuildValue;
    }

    TSharedPtr<FAcceptRequestResult> FAcceptRequestResult::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FAcceptRequestResult>()
            ->WithItem(Data->HasField("item") ? [Data]() -> Model::FReceiveMemberRequestPtr
                 {
                    if (Data->HasTypedField<EJson::Null>("item"))
                    {
                        return nullptr;
                    }
                    return Model::FReceiveMemberRequest::FromJson(Data->GetObjectField("item"));
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

    TSharedPtr<FJsonObject> FAcceptRequestResult::ToJson() const
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