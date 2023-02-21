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

#include "Limit/Result/CountUpByStampTaskResult.h"

namespace Gs2::Limit::Result
{
    FCountUpByStampTaskResult::FCountUpByStampTaskResult():
        ItemValue(nullptr),
        NewContextStackValue(TOptional<FString>())
    {
    }

    FCountUpByStampTaskResult::FCountUpByStampTaskResult(
        const FCountUpByStampTaskResult& From
    ):
        ItemValue(From.ItemValue),
        NewContextStackValue(From.NewContextStackValue)
    {
    }

    TSharedPtr<FCountUpByStampTaskResult> FCountUpByStampTaskResult::WithItem(
        const TSharedPtr<Model::FCounter> Item
    )
    {
        this->ItemValue = Item;
        return SharedThis(this);
    }

    TSharedPtr<FCountUpByStampTaskResult> FCountUpByStampTaskResult::WithNewContextStack(
        const TOptional<FString> NewContextStack
    )
    {
        this->NewContextStackValue = NewContextStack;
        return SharedThis(this);
    }

    TSharedPtr<Model::FCounter> FCountUpByStampTaskResult::GetItem() const
    {
        if (!ItemValue.IsValid())
        {
            return nullptr;
        }
        return ItemValue;
    }

    TOptional<FString> FCountUpByStampTaskResult::GetNewContextStack() const
    {
        return NewContextStackValue;
    }

    TSharedPtr<FCountUpByStampTaskResult> FCountUpByStampTaskResult::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FCountUpByStampTaskResult>()
            ->WithItem(Data->HasField("item") ? [Data]() -> Model::FCounterPtr
                 {
                    if (Data->HasTypedField<EJson::Null>("item"))
                    {
                        return nullptr;
                    }
                    return Model::FCounter::FromJson(Data->GetObjectField("item"));
                 }() : nullptr)
            ->WithNewContextStack(Data->HasField("newContextStack") ? [Data]() -> TOptional<FString>
                {
                    FString v;
                    if (Data->TryGetStringField("newContextStack", v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>());
    }

    TSharedPtr<FJsonObject> FCountUpByStampTaskResult::ToJson() const
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