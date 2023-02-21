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

#pragma once

#include "CoreMinimal.h"
#include "JobQueue/Model/Job.h"

namespace Gs2::UE5::JobQueue::Model
{
	class EZGS2_API FEzJob final : public TSharedFromThis<FEzJob>
	{
        TOptional<FString> JobIdValue;
        TOptional<FString> ScriptIdValue;
        TOptional<FString> ArgsValue;
        TOptional<int32> CurrentRetryCountValue;
        TOptional<int32> MaxTryCountValue;

	public:
        TSharedPtr<FEzJob> WithJobId(const TOptional<FString> JobId);
        TSharedPtr<FEzJob> WithScriptId(const TOptional<FString> ScriptId);
        TSharedPtr<FEzJob> WithArgs(const TOptional<FString> Args);
        TSharedPtr<FEzJob> WithCurrentRetryCount(const TOptional<int32> CurrentRetryCount);
        TSharedPtr<FEzJob> WithMaxTryCount(const TOptional<int32> MaxTryCount);

        TOptional<FString> GetJobId() const;

        TOptional<FString> GetScriptId() const;

        TOptional<FString> GetArgs() const;

        TOptional<int32> GetCurrentRetryCount() const;
        FString GetCurrentRetryCountString() const;

        TOptional<int32> GetMaxTryCount() const;
        FString GetMaxTryCountString() const;

        Gs2::JobQueue::Model::FJobPtr ToModel() const;
        static TSharedPtr<FEzJob> FromModel(Gs2::JobQueue::Model::FJobPtr Model);
    };
    typedef TSharedPtr<FEzJob> FEzJobPtr;
}