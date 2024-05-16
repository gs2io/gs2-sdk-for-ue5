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

#include "Enchant/Result/SetBalanceParameterStatusByUserIdResult.h"

namespace Gs2::Enchant::Result
{
    FSetBalanceParameterStatusByUserIdResult::FSetBalanceParameterStatusByUserIdResult():
        ItemValue(nullptr),
        OldValue(nullptr)
    {
    }

    FSetBalanceParameterStatusByUserIdResult::FSetBalanceParameterStatusByUserIdResult(
        const FSetBalanceParameterStatusByUserIdResult& From
    ):
        ItemValue(From.ItemValue),
        OldValue(From.OldValue)
    {
    }

    TSharedPtr<FSetBalanceParameterStatusByUserIdResult> FSetBalanceParameterStatusByUserIdResult::WithItem(
        const TSharedPtr<Model::FBalanceParameterStatus> Item
    )
    {
        this->ItemValue = Item;
        return SharedThis(this);
    }

    TSharedPtr<FSetBalanceParameterStatusByUserIdResult> FSetBalanceParameterStatusByUserIdResult::WithOld(
        const TSharedPtr<Model::FBalanceParameterStatus> Old
    )
    {
        this->OldValue = Old;
        return SharedThis(this);
    }

    TSharedPtr<Model::FBalanceParameterStatus> FSetBalanceParameterStatusByUserIdResult::GetItem() const
    {
        if (!ItemValue.IsValid())
        {
            return nullptr;
        }
        return ItemValue;
    }

    TSharedPtr<Model::FBalanceParameterStatus> FSetBalanceParameterStatusByUserIdResult::GetOld() const
    {
        if (!OldValue.IsValid())
        {
            return nullptr;
        }
        return OldValue;
    }

    TSharedPtr<FSetBalanceParameterStatusByUserIdResult> FSetBalanceParameterStatusByUserIdResult::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FSetBalanceParameterStatusByUserIdResult>()
            ->WithItem(Data->HasField(ANSI_TO_TCHAR("item")) ? [Data]() -> Model::FBalanceParameterStatusPtr
                 {
                    if (Data->HasTypedField<EJson::Null>(ANSI_TO_TCHAR("item")))
                    {
                        return nullptr;
                    }
                    return Model::FBalanceParameterStatus::FromJson(Data->GetObjectField(ANSI_TO_TCHAR("item")));
                 }() : nullptr)
            ->WithOld(Data->HasField(ANSI_TO_TCHAR("old")) ? [Data]() -> Model::FBalanceParameterStatusPtr
                 {
                    if (Data->HasTypedField<EJson::Null>(ANSI_TO_TCHAR("old")))
                    {
                        return nullptr;
                    }
                    return Model::FBalanceParameterStatus::FromJson(Data->GetObjectField(ANSI_TO_TCHAR("old")));
                 }() : nullptr);
    }

    TSharedPtr<FJsonObject> FSetBalanceParameterStatusByUserIdResult::ToJson() const
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