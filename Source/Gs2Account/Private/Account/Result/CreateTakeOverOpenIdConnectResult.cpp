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

#include "Account/Result/CreateTakeOverOpenIdConnectResult.h"

namespace Gs2::Account::Result
{
    FCreateTakeOverOpenIdConnectResult::FCreateTakeOverOpenIdConnectResult():
        ItemValue(nullptr)
    {
    }

    FCreateTakeOverOpenIdConnectResult::FCreateTakeOverOpenIdConnectResult(
        const FCreateTakeOverOpenIdConnectResult& From
    ):
        ItemValue(From.ItemValue)
    {
    }

    TSharedPtr<FCreateTakeOverOpenIdConnectResult> FCreateTakeOverOpenIdConnectResult::WithItem(
        const TSharedPtr<Model::FTakeOver> Item
    )
    {
        this->ItemValue = Item;
        return SharedThis(this);
    }

    TSharedPtr<Model::FTakeOver> FCreateTakeOverOpenIdConnectResult::GetItem() const
    {
        if (!ItemValue.IsValid())
        {
            return nullptr;
        }
        return ItemValue;
    }

    TSharedPtr<FCreateTakeOverOpenIdConnectResult> FCreateTakeOverOpenIdConnectResult::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FCreateTakeOverOpenIdConnectResult>()
            ->WithItem(Data->HasField(ANSI_TO_TCHAR("item")) ? [Data]() -> Model::FTakeOverPtr
                 {
                    if (Data->HasTypedField<EJson::Null>(ANSI_TO_TCHAR("item")))
                    {
                        return nullptr;
                    }
                    return Model::FTakeOver::FromJson(Data->GetObjectField(ANSI_TO_TCHAR("item")));
                 }() : nullptr);
    }

    TSharedPtr<FJsonObject> FCreateTakeOverOpenIdConnectResult::ToJson() const
    {
        const TSharedPtr<FJsonObject> JsonRootObject = MakeShared<FJsonObject>();
        if (ItemValue != nullptr && ItemValue.IsValid())
        {
            JsonRootObject->SetObjectField("item", ItemValue->ToJson());
        }
        return JsonRootObject;
    }
}