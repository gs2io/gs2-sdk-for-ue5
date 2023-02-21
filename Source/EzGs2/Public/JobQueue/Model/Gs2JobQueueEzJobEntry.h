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
#include "JobQueue/Model/JobEntry.h"

namespace Gs2::UE5::JobQueue::Model
{
	class EZGS2_API FEzJobEntry final : public TSharedFromThis<FEzJobEntry>
	{
        TOptional<FString> ScriptIdValue;
        TOptional<FString> ArgsValue;
        TOptional<int32> MaxTryCountValue;

	public:
        TSharedPtr<FEzJobEntry> WithScriptId(const TOptional<FString> ScriptId);
        TSharedPtr<FEzJobEntry> WithArgs(const TOptional<FString> Args);
        TSharedPtr<FEzJobEntry> WithMaxTryCount(const TOptional<int32> MaxTryCount);

        TOptional<FString> GetScriptId() const;

        TOptional<FString> GetArgs() const;

        TOptional<int32> GetMaxTryCount() const;
        FString GetMaxTryCountString() const;

        Gs2::JobQueue::Model::FJobEntryPtr ToModel() const;
        static TSharedPtr<FEzJobEntry> FromModel(Gs2::JobQueue::Model::FJobEntryPtr Model);
    };
    typedef TSharedPtr<FEzJobEntry> FEzJobEntryPtr;
}