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

#include "JobQueue/Model/Gs2JobQueueEzJob.h"

namespace Gs2::UE5::JobQueue::Model
{

    TSharedPtr<FEzJob> FEzJob::WithJobId(
        const TOptional<FString> JobId
    )
    {
        this->JobIdValue = JobId;
        return SharedThis(this);
    }

    TSharedPtr<FEzJob> FEzJob::WithScriptId(
        const TOptional<FString> ScriptId
    )
    {
        this->ScriptIdValue = ScriptId;
        return SharedThis(this);
    }

    TSharedPtr<FEzJob> FEzJob::WithArgs(
        const TOptional<FString> Args
    )
    {
        this->ArgsValue = Args;
        return SharedThis(this);
    }

    TSharedPtr<FEzJob> FEzJob::WithCurrentRetryCount(
        const TOptional<int32> CurrentRetryCount
    )
    {
        this->CurrentRetryCountValue = CurrentRetryCount;
        return SharedThis(this);
    }

    TSharedPtr<FEzJob> FEzJob::WithMaxTryCount(
        const TOptional<int32> MaxTryCount
    )
    {
        this->MaxTryCountValue = MaxTryCount;
        return SharedThis(this);
    }
    TOptional<FString> FEzJob::GetJobId() const
    {
        return JobIdValue;
    }
    TOptional<FString> FEzJob::GetScriptId() const
    {
        return ScriptIdValue;
    }
    TOptional<FString> FEzJob::GetArgs() const
    {
        return ArgsValue;
    }
    TOptional<int32> FEzJob::GetCurrentRetryCount() const
    {
        return CurrentRetryCountValue;
    }

    FString FEzJob::GetCurrentRetryCountString() const
    {
        if (!CurrentRetryCountValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%d"), CurrentRetryCountValue.GetValue());
    }
    TOptional<int32> FEzJob::GetMaxTryCount() const
    {
        return MaxTryCountValue;
    }

    FString FEzJob::GetMaxTryCountString() const
    {
        if (!MaxTryCountValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%d"), MaxTryCountValue.GetValue());
    }

    Gs2::JobQueue::Model::FJobPtr FEzJob::ToModel() const
    {
        return MakeShared<Gs2::JobQueue::Model::FJob>()
            ->WithJobId(JobIdValue)
            ->WithScriptId(ScriptIdValue)
            ->WithArgs(ArgsValue)
            ->WithCurrentRetryCount(CurrentRetryCountValue)
            ->WithMaxTryCount(MaxTryCountValue);
    }

    TSharedPtr<FEzJob> FEzJob::FromModel(const Gs2::JobQueue::Model::FJobPtr Model)
    {
        if (Model == nullptr)
        {
            return nullptr;
        }
        return MakeShared<FEzJob>()
            ->WithJobId(Model->GetJobId())
            ->WithScriptId(Model->GetScriptId())
            ->WithArgs(Model->GetArgs())
            ->WithCurrentRetryCount(Model->GetCurrentRetryCount())
            ->WithMaxTryCount(Model->GetMaxTryCount());
    }
}