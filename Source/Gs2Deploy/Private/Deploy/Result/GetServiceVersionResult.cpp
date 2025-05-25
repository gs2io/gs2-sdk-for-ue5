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

#include "Deploy/Result/GetServiceVersionResult.h"

namespace Gs2::Deploy::Result
{
    FGetServiceVersionResult::FGetServiceVersionResult():
        ItemValue(TOptional<FString>())
    {
    }

    FGetServiceVersionResult::FGetServiceVersionResult(
        const FGetServiceVersionResult& From
    ):
        ItemValue(From.ItemValue)
    {
    }

    TSharedPtr<FGetServiceVersionResult> FGetServiceVersionResult::WithItem(
        const TOptional<FString> Item
    )
    {
        this->ItemValue = Item;
        return SharedThis(this);
    }

    TOptional<FString> FGetServiceVersionResult::GetItem() const
    {
        return ItemValue;
    }

    TSharedPtr<FGetServiceVersionResult> FGetServiceVersionResult::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FGetServiceVersionResult>()
            ->WithItem(Data->HasField(ANSI_TO_TCHAR("item")) ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("item"), v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>());
    }

    TSharedPtr<FJsonObject> FGetServiceVersionResult::ToJson() const
    {
        const TSharedPtr<FJsonObject> JsonRootObject = MakeShared<FJsonObject>();
        if (ItemValue.IsSet())
        {
            JsonRootObject->SetStringField("item", ItemValue.GetValue());
        }
        return JsonRootObject;
    }
}