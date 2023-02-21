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

#include "JobQueue/Result/PushByStampSheetResult.h"

namespace Gs2::JobQueue::Result
{
    FPushByStampSheetResult::FPushByStampSheetResult():
        ItemsValue(nullptr),
        AutoRunValue(TOptional<bool>())
    {
    }

    FPushByStampSheetResult::FPushByStampSheetResult(
        const FPushByStampSheetResult& From
    ):
        ItemsValue(From.ItemsValue),
        AutoRunValue(From.AutoRunValue)
    {
    }

    TSharedPtr<FPushByStampSheetResult> FPushByStampSheetResult::WithItems(
        const TSharedPtr<TArray<TSharedPtr<Model::FJob>>> Items
    )
    {
        this->ItemsValue = Items;
        return SharedThis(this);
    }

    TSharedPtr<FPushByStampSheetResult> FPushByStampSheetResult::WithAutoRun(
        const TOptional<bool> AutoRun
    )
    {
        this->AutoRunValue = AutoRun;
        return SharedThis(this);
    }

    TSharedPtr<TArray<TSharedPtr<Model::FJob>>> FPushByStampSheetResult::GetItems() const
    {
        if (!ItemsValue.IsValid())
        {
            return nullptr;
        }
        return ItemsValue;
    }

    TOptional<bool> FPushByStampSheetResult::GetAutoRun() const
    {
        return AutoRunValue;
    }

    FString FPushByStampSheetResult::GetAutoRunString() const
    {
        if (!AutoRunValue.IsSet())
        {
            return FString("null");
        }
        return FString(AutoRunValue.GetValue() ? "true" : "false");
    }

    TSharedPtr<FPushByStampSheetResult> FPushByStampSheetResult::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FPushByStampSheetResult>()
            ->WithItems(Data->HasField("items") ? [Data]() -> TSharedPtr<TArray<Model::FJobPtr>>
                 {
                    auto v = MakeShared<TArray<Model::FJobPtr>>();
                    if (!Data->HasTypedField<EJson::Null>("items") && Data->HasTypedField<EJson::Array>("items"))
                    {
                        for (auto JsonObjectValue : Data->GetArrayField("items"))
                        {
                            v->Add(Model::FJob::FromJson(JsonObjectValue->AsObject()));
                        }
                    }
                    return v;
                 }() : nullptr)
            ->WithAutoRun(Data->HasField("autoRun") ? [Data]() -> TOptional<bool>
                {
                    bool v;
                    if (Data->TryGetBoolField("autoRun", v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<bool>();
                }() : TOptional<bool>());
    }

    TSharedPtr<FJsonObject> FPushByStampSheetResult::ToJson() const
    {
        const TSharedPtr<FJsonObject> JsonRootObject = MakeShared<FJsonObject>();
        if (ItemsValue != nullptr && ItemsValue.IsValid())
        {
            TArray<TSharedPtr<FJsonValue>> v;
            for (auto JsonObjectValue : *ItemsValue)
            {
                v.Add(MakeShared<FJsonValueObject>(JsonObjectValue->ToJson()));
            }
            JsonRootObject->SetArrayField("items", v);
        }
        if (AutoRunValue.IsSet())
        {
            JsonRootObject->SetBoolField("autoRun", AutoRunValue.GetValue());
        }
        return JsonRootObject;
    }
}