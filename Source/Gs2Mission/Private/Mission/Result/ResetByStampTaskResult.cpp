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

#include "Mission/Result/ResetByStampTaskResult.h"

namespace Gs2::Mission::Result
{
    FResetByStampTaskResult::FResetByStampTaskResult():
        ItemValue(nullptr),
        NewContextStackValue(TOptional<FString>())
    {
    }

    FResetByStampTaskResult::FResetByStampTaskResult(
        const FResetByStampTaskResult& From
    ):
        ItemValue(From.ItemValue),
        NewContextStackValue(From.NewContextStackValue)
    {
    }

    TSharedPtr<FResetByStampTaskResult> FResetByStampTaskResult::WithItem(
        const TSharedPtr<Model::FCounter> Item
    )
    {
        this->ItemValue = Item;
        return SharedThis(this);
    }

    TSharedPtr<FResetByStampTaskResult> FResetByStampTaskResult::WithNewContextStack(
        const TOptional<FString> NewContextStack
    )
    {
        this->NewContextStackValue = NewContextStack;
        return SharedThis(this);
    }

    TSharedPtr<Model::FCounter> FResetByStampTaskResult::GetItem() const
    {
        if (!ItemValue.IsValid())
        {
            return nullptr;
        }
        return ItemValue;
    }

    TOptional<FString> FResetByStampTaskResult::GetNewContextStack() const
    {
        return NewContextStackValue;
    }

    TSharedPtr<FResetByStampTaskResult> FResetByStampTaskResult::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FResetByStampTaskResult>()
            ->WithItem(Data->HasField(ANSI_TO_TCHAR("item")) ? [Data]() -> Model::FCounterPtr
                 {
                    if (Data->HasTypedField<EJson::Null>(ANSI_TO_TCHAR("item")))
                    {
                        return nullptr;
                    }
                    return Model::FCounter::FromJson(Data->GetObjectField(ANSI_TO_TCHAR("item")));
                 }() : nullptr)
            ->WithNewContextStack(Data->HasField(ANSI_TO_TCHAR("newContextStack")) ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("newContextStack"), v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>());
    }

    TSharedPtr<FJsonObject> FResetByStampTaskResult::ToJson() const
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