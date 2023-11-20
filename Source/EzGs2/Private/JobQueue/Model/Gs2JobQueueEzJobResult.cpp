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

#include "JobQueue/Model/Gs2JobQueueEzJobResult.h"

namespace Gs2::UE5::JobQueue::Model
{

    TSharedPtr<FEzJobResult> FEzJobResult::WithStatusCode(
        const TOptional<int32> StatusCode
    )
    {
        this->StatusCodeValue = StatusCode;
        return SharedThis(this);
    }

    TSharedPtr<FEzJobResult> FEzJobResult::WithResult(
        const TOptional<FString> Result
    )
    {
        this->ResultValue = Result;
        return SharedThis(this);
    }
    TOptional<int32> FEzJobResult::GetStatusCode() const
    {
        return StatusCodeValue;
    }

    FString FEzJobResult::GetStatusCodeString() const
    {
        if (!StatusCodeValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%d"), StatusCodeValue.GetValue());
    }
    TOptional<FString> FEzJobResult::GetResult() const
    {
        return ResultValue;
    }

    Gs2::JobQueue::Model::FJobResultPtr FEzJobResult::ToModel() const
    {
        return MakeShared<Gs2::JobQueue::Model::FJobResult>()
            ->WithStatusCode(StatusCodeValue)
            ->WithResult(ResultValue);
    }

    TSharedPtr<FEzJobResult> FEzJobResult::FromModel(const Gs2::JobQueue::Model::FJobResultPtr Model)
    {
        if (Model == nullptr)
        {
            return nullptr;
        }
        return MakeShared<FEzJobResult>()
            ->WithStatusCode(Model->GetStatusCode())
            ->WithResult(Model->GetResult());
    }
}