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

#include "SkillTree/Result/MarkRestrainByStampTaskResult.h"

namespace Gs2::SkillTree::Result
{
    FMarkRestrainByStampTaskResult::FMarkRestrainByStampTaskResult():
        ItemValue(nullptr),
        NewContextStackValue(TOptional<FString>())
    {
    }

    FMarkRestrainByStampTaskResult::FMarkRestrainByStampTaskResult(
        const FMarkRestrainByStampTaskResult& From
    ):
        ItemValue(From.ItemValue),
        NewContextStackValue(From.NewContextStackValue)
    {
    }

    TSharedPtr<FMarkRestrainByStampTaskResult> FMarkRestrainByStampTaskResult::WithItem(
        const TSharedPtr<Model::FStatus> Item
    )
    {
        this->ItemValue = Item;
        return SharedThis(this);
    }

    TSharedPtr<FMarkRestrainByStampTaskResult> FMarkRestrainByStampTaskResult::WithNewContextStack(
        const TOptional<FString> NewContextStack
    )
    {
        this->NewContextStackValue = NewContextStack;
        return SharedThis(this);
    }

    TSharedPtr<Model::FStatus> FMarkRestrainByStampTaskResult::GetItem() const
    {
        if (!ItemValue.IsValid())
        {
            return nullptr;
        }
        return ItemValue;
    }

    TOptional<FString> FMarkRestrainByStampTaskResult::GetNewContextStack() const
    {
        return NewContextStackValue;
    }

    TSharedPtr<FMarkRestrainByStampTaskResult> FMarkRestrainByStampTaskResult::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FMarkRestrainByStampTaskResult>()
            ->WithItem(Data->HasField("item") ? [Data]() -> Model::FStatusPtr
                 {
                    if (Data->HasTypedField<EJson::Null>("item"))
                    {
                        return nullptr;
                    }
                    return Model::FStatus::FromJson(Data->GetObjectField("item"));
                 }() : nullptr)
            ->WithNewContextStack(Data->HasField("newContextStack") ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField("newContextStack", v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>());
    }

    TSharedPtr<FJsonObject> FMarkRestrainByStampTaskResult::ToJson() const
    {
        const TSharedPtr<FJsonObject> JsonRootObject = MakeShared<FJsonObject>();
        if (ItemValue != nullptr && ItemValue.IsValid())
        {
            JsonRootObject->SetObjectField("item", ItemValue->ToJson());
        }
        if (NewContextStackValue.IsSet())
        {
            JsonRootObject->SetStringField("newContextStack", NewContextStackValue.GetValue());
        }
        return JsonRootObject;
    }
}