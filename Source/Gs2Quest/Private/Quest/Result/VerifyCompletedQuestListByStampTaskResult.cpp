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

#include "Quest/Result/VerifyCompletedQuestListByStampTaskResult.h"

namespace Gs2::Quest::Result
{
    FVerifyCompletedQuestListByStampTaskResult::FVerifyCompletedQuestListByStampTaskResult():
        ItemValue(nullptr),
        NewContextStackValue(TOptional<FString>())
    {
    }

    FVerifyCompletedQuestListByStampTaskResult::FVerifyCompletedQuestListByStampTaskResult(
        const FVerifyCompletedQuestListByStampTaskResult& From
    ):
        ItemValue(From.ItemValue),
        NewContextStackValue(From.NewContextStackValue)
    {
    }

    TSharedPtr<FVerifyCompletedQuestListByStampTaskResult> FVerifyCompletedQuestListByStampTaskResult::WithItem(
        const TSharedPtr<Model::FCompletedQuestList> Item
    )
    {
        this->ItemValue = Item;
        return SharedThis(this);
    }

    TSharedPtr<FVerifyCompletedQuestListByStampTaskResult> FVerifyCompletedQuestListByStampTaskResult::WithNewContextStack(
        const TOptional<FString> NewContextStack
    )
    {
        this->NewContextStackValue = NewContextStack;
        return SharedThis(this);
    }

    TSharedPtr<Model::FCompletedQuestList> FVerifyCompletedQuestListByStampTaskResult::GetItem() const
    {
        if (!ItemValue.IsValid())
        {
            return nullptr;
        }
        return ItemValue;
    }

    TOptional<FString> FVerifyCompletedQuestListByStampTaskResult::GetNewContextStack() const
    {
        return NewContextStackValue;
    }

    TSharedPtr<FVerifyCompletedQuestListByStampTaskResult> FVerifyCompletedQuestListByStampTaskResult::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FVerifyCompletedQuestListByStampTaskResult>()
            ->WithItem(Data->HasField(ANSI_TO_TCHAR("item")) ? [Data]() -> Model::FCompletedQuestListPtr
                 {
                    if (Data->HasTypedField<EJson::Null>(ANSI_TO_TCHAR("item")))
                    {
                        return nullptr;
                    }
                    return Model::FCompletedQuestList::FromJson(Data->GetObjectField(ANSI_TO_TCHAR("item")));
                 }() : nullptr)
            ->WithNewContextStack(Data->HasField(ANSI_TO_TCHAR("newContextStack")) ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("newContextStack"), v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>());
    }

    TSharedPtr<FJsonObject> FVerifyCompletedQuestListByStampTaskResult::ToJson() const
    {
        const TSharedPtr<FJsonObject> JsonRootObject = MakeShared<FJsonObject>();
        if (ItemValue != nullptr && ItemValue.IsValid())
        {
            JsonRootObject->SetObjectField(TEXT("item"), ItemValue->ToJson());
        }
        if (NewContextStackValue.IsSet())
        {
            JsonRootObject->SetStringField(TEXT("newContextStack"), NewContextStackValue.GetValue());
        }
        return JsonRootObject;
    }
}