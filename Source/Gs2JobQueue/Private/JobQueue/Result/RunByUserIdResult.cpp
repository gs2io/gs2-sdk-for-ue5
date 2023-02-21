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

#include "JobQueue/Result/RunByUserIdResult.h"

namespace Gs2::JobQueue::Result
{
    FRunByUserIdResult::FRunByUserIdResult():
        ItemValue(nullptr),
        ResultValue(nullptr),
        IsLastJobValue(TOptional<bool>())
    {
    }

    FRunByUserIdResult::FRunByUserIdResult(
        const FRunByUserIdResult& From
    ):
        ItemValue(From.ItemValue),
        ResultValue(From.ResultValue),
        IsLastJobValue(From.IsLastJobValue)
    {
    }

    TSharedPtr<FRunByUserIdResult> FRunByUserIdResult::WithItem(
        const TSharedPtr<Model::FJob> Item
    )
    {
        this->ItemValue = Item;
        return SharedThis(this);
    }

    TSharedPtr<FRunByUserIdResult> FRunByUserIdResult::WithResult(
        const TSharedPtr<Model::FJobResultBody> Result
    )
    {
        this->ResultValue = Result;
        return SharedThis(this);
    }

    TSharedPtr<FRunByUserIdResult> FRunByUserIdResult::WithIsLastJob(
        const TOptional<bool> IsLastJob
    )
    {
        this->IsLastJobValue = IsLastJob;
        return SharedThis(this);
    }

    TSharedPtr<Model::FJob> FRunByUserIdResult::GetItem() const
    {
        if (!ItemValue.IsValid())
        {
            return nullptr;
        }
        return ItemValue;
    }

    TSharedPtr<Model::FJobResultBody> FRunByUserIdResult::GetResult() const
    {
        if (!ResultValue.IsValid())
        {
            return nullptr;
        }
        return ResultValue;
    }

    TOptional<bool> FRunByUserIdResult::GetIsLastJob() const
    {
        return IsLastJobValue;
    }

    FString FRunByUserIdResult::GetIsLastJobString() const
    {
        if (!IsLastJobValue.IsSet())
        {
            return FString("null");
        }
        return FString(IsLastJobValue.GetValue() ? "true" : "false");
    }

    TSharedPtr<FRunByUserIdResult> FRunByUserIdResult::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FRunByUserIdResult>()
            ->WithItem(Data->HasField("item") ? [Data]() -> Model::FJobPtr
                 {
                    if (Data->HasTypedField<EJson::Null>("item"))
                    {
                        return nullptr;
                    }
                    return Model::FJob::FromJson(Data->GetObjectField("item"));
                 }() : nullptr)
            ->WithResult(Data->HasField("result") ? [Data]() -> Model::FJobResultBodyPtr
                 {
                    if (Data->HasTypedField<EJson::Null>("result"))
                    {
                        return nullptr;
                    }
                    return Model::FJobResultBody::FromJson(Data->GetObjectField("result"));
                 }() : nullptr)
            ->WithIsLastJob(Data->HasField("isLastJob") ? [Data]() -> TOptional<bool>
                {
                    bool v;
                    if (Data->TryGetBoolField("isLastJob", v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<bool>();
                }() : TOptional<bool>());
    }

    TSharedPtr<FJsonObject> FRunByUserIdResult::ToJson() const
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