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

#include "Guild/Result/SetMaximumCurrentMaximumMemberCountByGuildNameResult.h"

namespace Gs2::Guild::Result
{
    FSetMaximumCurrentMaximumMemberCountByGuildNameResult::FSetMaximumCurrentMaximumMemberCountByGuildNameResult():
        ItemValue(nullptr),
        OldValue(nullptr)
    {
    }

    FSetMaximumCurrentMaximumMemberCountByGuildNameResult::FSetMaximumCurrentMaximumMemberCountByGuildNameResult(
        const FSetMaximumCurrentMaximumMemberCountByGuildNameResult& From
    ):
        ItemValue(From.ItemValue),
        OldValue(From.OldValue)
    {
    }

    TSharedPtr<FSetMaximumCurrentMaximumMemberCountByGuildNameResult> FSetMaximumCurrentMaximumMemberCountByGuildNameResult::WithItem(
        const TSharedPtr<Model::FGuild> Item
    )
    {
        this->ItemValue = Item;
        return SharedThis(this);
    }

    TSharedPtr<FSetMaximumCurrentMaximumMemberCountByGuildNameResult> FSetMaximumCurrentMaximumMemberCountByGuildNameResult::WithOld(
        const TSharedPtr<Model::FGuild> Old
    )
    {
        this->OldValue = Old;
        return SharedThis(this);
    }

    TSharedPtr<Model::FGuild> FSetMaximumCurrentMaximumMemberCountByGuildNameResult::GetItem() const
    {
        if (!ItemValue.IsValid())
        {
            return nullptr;
        }
        return ItemValue;
    }

    TSharedPtr<Model::FGuild> FSetMaximumCurrentMaximumMemberCountByGuildNameResult::GetOld() const
    {
        if (!OldValue.IsValid())
        {
            return nullptr;
        }
        return OldValue;
    }

    TSharedPtr<FSetMaximumCurrentMaximumMemberCountByGuildNameResult> FSetMaximumCurrentMaximumMemberCountByGuildNameResult::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FSetMaximumCurrentMaximumMemberCountByGuildNameResult>()
            ->WithItem(Data->HasField("item") ? [Data]() -> Model::FGuildPtr
                 {
                    if (Data->HasTypedField<EJson::Null>("item"))
                    {
                        return nullptr;
                    }
                    return Model::FGuild::FromJson(Data->GetObjectField("item"));
                 }() : nullptr)
            ->WithOld(Data->HasField("old") ? [Data]() -> Model::FGuildPtr
                 {
                    if (Data->HasTypedField<EJson::Null>("old"))
                    {
                        return nullptr;
                    }
                    return Model::FGuild::FromJson(Data->GetObjectField("old"));
                 }() : nullptr);
    }

    TSharedPtr<FJsonObject> FSetMaximumCurrentMaximumMemberCountByGuildNameResult::ToJson() const
    {
        const TSharedPtr<FJsonObject> JsonRootObject = MakeShared<FJsonObject>();
        if (ItemValue != nullptr && ItemValue.IsValid())
        {
            JsonRootObject->SetObjectField("item", ItemValue->ToJson());
        }
        if (OldValue != nullptr && OldValue.IsValid())
        {
            JsonRootObject->SetObjectField("old", OldValue->ToJson());
        }
        return JsonRootObject;
    }
}