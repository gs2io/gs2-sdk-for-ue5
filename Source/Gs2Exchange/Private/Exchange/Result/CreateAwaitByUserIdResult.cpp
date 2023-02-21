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

#include "Exchange/Result/CreateAwaitByUserIdResult.h"

namespace Gs2::Exchange::Result
{
    FCreateAwaitByUserIdResult::FCreateAwaitByUserIdResult():
        ItemValue(nullptr),
        UnlockAtValue(TOptional<int64>())
    {
    }

    FCreateAwaitByUserIdResult::FCreateAwaitByUserIdResult(
        const FCreateAwaitByUserIdResult& From
    ):
        ItemValue(From.ItemValue),
        UnlockAtValue(From.UnlockAtValue)
    {
    }

    TSharedPtr<FCreateAwaitByUserIdResult> FCreateAwaitByUserIdResult::WithItem(
        const TSharedPtr<Model::FAwait> Item
    )
    {
        this->ItemValue = Item;
        return SharedThis(this);
    }

    TSharedPtr<FCreateAwaitByUserIdResult> FCreateAwaitByUserIdResult::WithUnlockAt(
        const TOptional<int64> UnlockAt
    )
    {
        this->UnlockAtValue = UnlockAt;
        return SharedThis(this);
    }

    TSharedPtr<Model::FAwait> FCreateAwaitByUserIdResult::GetItem() const
    {
        if (!ItemValue.IsValid())
        {
            return nullptr;
        }
        return ItemValue;
    }

    TOptional<int64> FCreateAwaitByUserIdResult::GetUnlockAt() const
    {
        return UnlockAtValue;
    }

    FString FCreateAwaitByUserIdResult::GetUnlockAtString() const
    {
        if (!UnlockAtValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), UnlockAtValue.GetValue());
    }

    TSharedPtr<FCreateAwaitByUserIdResult> FCreateAwaitByUserIdResult::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FCreateAwaitByUserIdResult>()
            ->WithItem(Data->HasField("item") ? [Data]() -> Model::FAwaitPtr
                 {
                    if (Data->HasTypedField<EJson::Null>("item"))
                    {
                        return nullptr;
                    }
                    return Model::FAwait::FromJson(Data->GetObjectField("item"));
                 }() : nullptr)
            ->WithUnlockAt(Data->HasField("unlockAt") ? [Data]() -> TOptional<int64>
                {
                    int64 v;
                    if (Data->TryGetNumberField("unlockAt", v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<int64>();
                }() : TOptional<int64>());
    }

    TSharedPtr<FJsonObject> FCreateAwaitByUserIdResult::ToJson() const
    {
        const TSharedPtr<FJsonObject> JsonRootObject = MakeShared<FJsonObject>();
        if (ItemValue != nullptr && ItemValue.IsValid())
        {
            JsonRootObject->SetObjectField("item", ItemValue->ToJson());
        }
        if (UnlockAtValue.IsSet())
        {
            JsonRootObject->SetStringField("unlockAt", FString::Printf(TEXT("%lld"), UnlockAtValue.GetValue()));
        }
        return JsonRootObject;
    }
}