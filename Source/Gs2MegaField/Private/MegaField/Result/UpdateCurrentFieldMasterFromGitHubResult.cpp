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

#include "MegaField/Result/UpdateCurrentFieldMasterFromGitHubResult.h"

namespace Gs2::MegaField::Result
{
    FUpdateCurrentFieldMasterFromGitHubResult::FUpdateCurrentFieldMasterFromGitHubResult():
        ItemValue(nullptr)
    {
    }

    FUpdateCurrentFieldMasterFromGitHubResult::FUpdateCurrentFieldMasterFromGitHubResult(
        const FUpdateCurrentFieldMasterFromGitHubResult& From
    ):
        ItemValue(From.ItemValue)
    {
    }

    TSharedPtr<FUpdateCurrentFieldMasterFromGitHubResult> FUpdateCurrentFieldMasterFromGitHubResult::WithItem(
        const TSharedPtr<Model::FCurrentFieldMaster> Item
    )
    {
        this->ItemValue = Item;
        return SharedThis(this);
    }

    TSharedPtr<Model::FCurrentFieldMaster> FUpdateCurrentFieldMasterFromGitHubResult::GetItem() const
    {
        if (!ItemValue.IsValid())
        {
            return nullptr;
        }
        return ItemValue;
    }

    TSharedPtr<FUpdateCurrentFieldMasterFromGitHubResult> FUpdateCurrentFieldMasterFromGitHubResult::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FUpdateCurrentFieldMasterFromGitHubResult>()
            ->WithItem(Data->HasField("item") ? [Data]() -> Model::FCurrentFieldMasterPtr
                 {
                    if (Data->HasTypedField<EJson::Null>("item"))
                    {
                        return nullptr;
                    }
                    return Model::FCurrentFieldMaster::FromJson(Data->GetObjectField("item"));
                 }() : nullptr);
    }

    TSharedPtr<FJsonObject> FUpdateCurrentFieldMasterFromGitHubResult::ToJson() const
    {
        const TSharedPtr<FJsonObject> JsonRootObject = MakeShared<FJsonObject>();
        if (ItemValue != nullptr && ItemValue.IsValid())
        {
            JsonRootObject->SetObjectField("item", ItemValue->ToJson());
        }
        return JsonRootObject;
    }
}