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
#include "JobResultBody.h"

namespace Gs2::JobQueue::Model
{
    class GS2JOBQUEUE_API FDeadLetterJob final : public TSharedFromThis<FDeadLetterJob>
    {
        TOptional<FString> DeadLetterJobIdValue;
        TOptional<FString> NameValue;
        TOptional<FString> UserIdValue;
        TOptional<FString> ScriptIdValue;
        TOptional<FString> ArgsValue;
        TSharedPtr<TArray<TSharedPtr<FJobResultBody>>> ResultValue;
        TOptional<int64> CreatedAtValue;
        TOptional<int64> UpdatedAtValue;

    public:
        FDeadLetterJob();
        FDeadLetterJob(
            const FDeadLetterJob& From
        );
        ~FDeadLetterJob() = default;

        TSharedPtr<FDeadLetterJob> WithDeadLetterJobId(const TOptional<FString> DeadLetterJobId);
        TSharedPtr<FDeadLetterJob> WithName(const TOptional<FString> Name);
        TSharedPtr<FDeadLetterJob> WithUserId(const TOptional<FString> UserId);
        TSharedPtr<FDeadLetterJob> WithScriptId(const TOptional<FString> ScriptId);
        TSharedPtr<FDeadLetterJob> WithArgs(const TOptional<FString> Args);
        TSharedPtr<FDeadLetterJob> WithResult(const TSharedPtr<TArray<TSharedPtr<FJobResultBody>>> Result);
        TSharedPtr<FDeadLetterJob> WithCreatedAt(const TOptional<int64> CreatedAt);
        TSharedPtr<FDeadLetterJob> WithUpdatedAt(const TOptional<int64> UpdatedAt);

        TOptional<FString> GetDeadLetterJobId() const;
        TOptional<FString> GetName() const;
        TOptional<FString> GetUserId() const;
        TOptional<FString> GetScriptId() const;
        TOptional<FString> GetArgs() const;
        TSharedPtr<TArray<TSharedPtr<FJobResultBody>>> GetResult() const;
        TOptional<int64> GetCreatedAt() const;
        FString GetCreatedAtString() const;
        TOptional<int64> GetUpdatedAt() const;
        FString GetUpdatedAtString() const;

        static TOptional<FString> GetRegionFromGrn(const FString Grn);
        static TOptional<FString> GetOwnerIdFromGrn(const FString Grn);
        static TOptional<FString> GetNamespaceNameFromGrn(const FString Grn);
        static TOptional<FString> GetUserIdFromGrn(const FString Grn);
        static TOptional<FString> GetDeadLetterJobNameFromGrn(const FString Grn);

        static TSharedPtr<FDeadLetterJob> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;

        static FString TypeName;
    };
    typedef TSharedPtr<FDeadLetterJob, ESPMode::ThreadSafe> FDeadLetterJobPtr;
}