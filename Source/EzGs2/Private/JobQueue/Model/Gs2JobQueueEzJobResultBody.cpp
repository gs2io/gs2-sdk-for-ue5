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

#include "JobQueue/Model/Gs2JobQueueEzJobResultBody.h"

namespace Gs2::UE5::JobQueue::Model
{

    TSharedPtr<FEzJobResultBody> FEzJobResultBody::WithTryNumber(
        const TOptional<int32> TryNumber
    )
    {
        this->TryNumberValue = TryNumber;
        return SharedThis(this);
    }

    TSharedPtr<FEzJobResultBody> FEzJobResultBody::WithStatusCode(
        const TOptional<int32> StatusCode
    )
    {
        this->StatusCodeValue = StatusCode;
        return SharedThis(this);
    }

    TSharedPtr<FEzJobResultBody> FEzJobResultBody::WithResult(
        const TOptional<FString> Result
    )
    {
        this->ResultValue = Result;
        return SharedThis(this);
    }

    TSharedPtr<FEzJobResultBody> FEzJobResultBody::WithTryAt(
        const TOptional<int64> TryAt
    )
    {
        this->TryAtValue = TryAt;
        return SharedThis(this);
    }
    TOptional<int32> FEzJobResultBody::GetTryNumber() const
    {
        return TryNumberValue;
    }

    FString FEzJobResultBody::GetTryNumberString() const
    {
        if (!TryNumberValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%d"), TryNumberValue.GetValue());
    }
    TOptional<int32> FEzJobResultBody::GetStatusCode() const
    {
        return StatusCodeValue;
    }

    FString FEzJobResultBody::GetStatusCodeString() const
    {
        if (!StatusCodeValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%d"), StatusCodeValue.GetValue());
    }
    TOptional<FString> FEzJobResultBody::GetResult() const
    {
        return ResultValue;
    }
    TOptional<int64> FEzJobResultBody::GetTryAt() const
    {
        return TryAtValue;
    }

    FString FEzJobResultBody::GetTryAtString() const
    {
        if (!TryAtValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), TryAtValue.GetValue());
    }

    Gs2::JobQueue::Model::FJobResultBodyPtr FEzJobResultBody::ToModel() const
    {
        return MakeShared<Gs2::JobQueue::Model::FJobResultBody>()
            ->WithTryNumber(TryNumberValue)
            ->WithStatusCode(StatusCodeValue)
            ->WithResult(ResultValue)
            ->WithTryAt(TryAtValue);
    }

    TSharedPtr<FEzJobResultBody> FEzJobResultBody::FromModel(const Gs2::JobQueue::Model::FJobResultBodyPtr Model)
    {
        if (Model == nullptr)
        {
            return nullptr;
        }
        return MakeShared<FEzJobResultBody>()
            ->WithTryNumber(Model->GetTryNumber())
            ->WithStatusCode(Model->GetStatusCode())
            ->WithResult(Model->GetResult())
            ->WithTryAt(Model->GetTryAt());
    }
}