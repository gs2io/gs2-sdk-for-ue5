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

#include "Experience/Result/SetExperienceByUserIdResult.h"

namespace Gs2::Experience::Result
{
    FSetExperienceByUserIdResult::FSetExperienceByUserIdResult():
        ItemValue(nullptr),
        OldValue(nullptr)
    {
    }

    FSetExperienceByUserIdResult::FSetExperienceByUserIdResult(
        const FSetExperienceByUserIdResult& From
    ):
        ItemValue(From.ItemValue),
        OldValue(From.OldValue)
    {
    }

    TSharedPtr<FSetExperienceByUserIdResult> FSetExperienceByUserIdResult::WithItem(
        const TSharedPtr<Model::FStatus> Item
    )
    {
        this->ItemValue = Item;
        return SharedThis(this);
    }

    TSharedPtr<FSetExperienceByUserIdResult> FSetExperienceByUserIdResult::WithOld(
        const TSharedPtr<Model::FStatus> Old
    )
    {
        this->OldValue = Old;
        return SharedThis(this);
    }

    TSharedPtr<Model::FStatus> FSetExperienceByUserIdResult::GetItem() const
    {
        if (!ItemValue.IsValid())
        {
            return nullptr;
        }
        return ItemValue;
    }

    TSharedPtr<Model::FStatus> FSetExperienceByUserIdResult::GetOld() const
    {
        if (!OldValue.IsValid())
        {
            return nullptr;
        }
        return OldValue;
    }

    TSharedPtr<FSetExperienceByUserIdResult> FSetExperienceByUserIdResult::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FSetExperienceByUserIdResult>()
            ->WithItem(Data->HasField("item") ? [Data]() -> Model::FStatusPtr
                 {
                    if (Data->HasTypedField<EJson::Null>("item"))
                    {
                        return nullptr;
                    }
                    return Model::FStatus::FromJson(Data->GetObjectField("item"));
                 }() : nullptr)
            ->WithOld(Data->HasField("old") ? [Data]() -> Model::FStatusPtr
                 {
                    if (Data->HasTypedField<EJson::Null>("old"))
                    {
                        return nullptr;
                    }
                    return Model::FStatus::FromJson(Data->GetObjectField("old"));
                 }() : nullptr);
    }

    TSharedPtr<FJsonObject> FSetExperienceByUserIdResult::ToJson() const
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