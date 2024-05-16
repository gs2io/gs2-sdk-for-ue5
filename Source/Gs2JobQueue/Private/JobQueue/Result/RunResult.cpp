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

#include "JobQueue/Result/RunResult.h"

namespace Gs2::JobQueue::Result
{
    FRunResult::FRunResult():
        ItemValue(nullptr),
        ResultValue(nullptr),
        IsLastJobValue(TOptional<bool>())
    {
    }

    FRunResult::FRunResult(
        const FRunResult& From
    ):
        ItemValue(From.ItemValue),
        ResultValue(From.ResultValue),
        IsLastJobValue(From.IsLastJobValue)
    {
    }

    TSharedPtr<FRunResult> FRunResult::WithItem(
        const TSharedPtr<Model::FJob> Item
    )
    {
        this->ItemValue = Item;
        return SharedThis(this);
    }

    TSharedPtr<FRunResult> FRunResult::WithResult(
        const TSharedPtr<Model::FJobResultBody> Result
    )
    {
        this->ResultValue = Result;
        return SharedThis(this);
    }

    TSharedPtr<FRunResult> FRunResult::WithIsLastJob(
        const TOptional<bool> IsLastJob
    )
    {
        this->IsLastJobValue = IsLastJob;
        return SharedThis(this);
    }

    TSharedPtr<Model::FJob> FRunResult::GetItem() const
    {
        if (!ItemValue.IsValid())
        {
            return nullptr;
        }
        return ItemValue;
    }

    TSharedPtr<Model::FJobResultBody> FRunResult::GetResult() const
    {
        if (!ResultValue.IsValid())
        {
            return nullptr;
        }
        return ResultValue;
    }

    TOptional<bool> FRunResult::GetIsLastJob() const
    {
        return IsLastJobValue;
    }

    FString FRunResult::GetIsLastJobString() const
    {
        if (!IsLastJobValue.IsSet())
        {
            return FString("null");
        }
        return FString(IsLastJobValue.GetValue() ? "true" : "false");
    }

    TSharedPtr<FRunResult> FRunResult::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FRunResult>()
            ->WithItem(Data->HasField(ANSI_TO_TCHAR("item")) ? [Data]() -> Model::FJobPtr
                 {
                    if (Data->HasTypedField<EJson::Null>(ANSI_TO_TCHAR("item")))
                    {
                        return nullptr;
                    }
                    return Model::FJob::FromJson(Data->GetObjectField(ANSI_TO_TCHAR("item")));
                 }() : nullptr)
            ->WithResult(Data->HasField(ANSI_TO_TCHAR("result")) ? [Data]() -> Model::FJobResultBodyPtr
                 {
                    if (Data->HasTypedField<EJson::Null>(ANSI_TO_TCHAR("result")))
                    {
                        return nullptr;
                    }
                    return Model::FJobResultBody::FromJson(Data->GetObjectField(ANSI_TO_TCHAR("result")));
                 }() : nullptr)
            ->WithIsLastJob(Data->HasField(ANSI_TO_TCHAR("isLastJob")) ? [Data]() -> TOptional<bool>
                {
                    bool v;
                    if (Data->TryGetBoolField(ANSI_TO_TCHAR("isLastJob"), v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<bool>();
                }() : TOptional<bool>());
    }

    TSharedPtr<FJsonObject> FRunResult::ToJson() const
    {
        const TSharedPtr<FJsonObject> JsonRootObject = MakeShared<FJsonObject>();
        if (ItemValue != nullptr && ItemValue.IsValid())
        {
            JsonRootObject->SetObjectField("item", ItemValue->ToJson());
        }
        if (ResultValue != nullptr && ResultValue.IsValid())
        {
            JsonRootObject->SetObjectField("result", ResultValue->ToJson());
        }
        if (IsLastJobValue.IsSet())
        {
            JsonRootObject->SetBoolField("isLastJob", IsLastJobValue.GetValue());
        }
        return JsonRootObject;
    }
}