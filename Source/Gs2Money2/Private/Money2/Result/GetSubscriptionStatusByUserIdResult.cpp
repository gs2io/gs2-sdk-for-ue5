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

#include "Money2/Result/GetSubscriptionStatusByUserIdResult.h"

namespace Gs2::Money2::Result
{
    FGetSubscriptionStatusByUserIdResult::FGetSubscriptionStatusByUserIdResult():
        ItemValue(nullptr)
    {
    }

    FGetSubscriptionStatusByUserIdResult::FGetSubscriptionStatusByUserIdResult(
        const FGetSubscriptionStatusByUserIdResult& From
    ):
        ItemValue(From.ItemValue)
    {
    }

    TSharedPtr<FGetSubscriptionStatusByUserIdResult> FGetSubscriptionStatusByUserIdResult::WithItem(
        const TSharedPtr<Model::FSubscriptionStatus> Item
    )
    {
        this->ItemValue = Item;
        return SharedThis(this);
    }

    TSharedPtr<Model::FSubscriptionStatus> FGetSubscriptionStatusByUserIdResult::GetItem() const
    {
        if (!ItemValue.IsValid())
        {
            return nullptr;
        }
        return ItemValue;
    }

    TSharedPtr<FGetSubscriptionStatusByUserIdResult> FGetSubscriptionStatusByUserIdResult::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FGetSubscriptionStatusByUserIdResult>()
            ->WithItem(Data->HasField(ANSI_TO_TCHAR("item")) ? [Data]() -> Model::FSubscriptionStatusPtr
                 {
                    if (Data->HasTypedField<EJson::Null>(ANSI_TO_TCHAR("item")))
                    {
                        return nullptr;
                    }
                    return Model::FSubscriptionStatus::FromJson(Data->GetObjectField(ANSI_TO_TCHAR("item")));
                 }() : nullptr);
    }

    TSharedPtr<FJsonObject> FGetSubscriptionStatusByUserIdResult::ToJson() const
    {
        const TSharedPtr<FJsonObject> JsonRootObject = MakeShared<FJsonObject>();
        if (ItemValue != nullptr && ItemValue.IsValid())
        {
            JsonRootObject->SetObjectField("item", ItemValue->ToJson());
        }
        return JsonRootObject;
    }
}