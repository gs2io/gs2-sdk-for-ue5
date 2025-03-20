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
#include "Core/Gs2Object.h"

namespace Gs2::JobQueue::Model
{
    class GS2JOBQUEUE_API FJob final : public FGs2Object, public TSharedFromThis<FJob>
    {
        TOptional<FString> JobIdValue;
        TOptional<FString> NameValue;
        TOptional<FString> UserIdValue;
        TOptional<FString> ScriptIdValue;
        TOptional<FString> ArgsValue;
        TOptional<int32> CurrentRetryCountValue;
        TOptional<int32> MaxTryCountValue;
        TOptional<int64> CreatedAtValue;
        TOptional<int64> UpdatedAtValue;

    public:
        FJob();
        FJob(
            const FJob& From
        );
        virtual ~FJob() override = default;

        TSharedPtr<FJob> WithJobId(const TOptional<FString> JobId);
        TSharedPtr<FJob> WithName(const TOptional<FString> Name);
        TSharedPtr<FJob> WithUserId(const TOptional<FString> UserId);
        TSharedPtr<FJob> WithScriptId(const TOptional<FString> ScriptId);
        TSharedPtr<FJob> WithArgs(const TOptional<FString> Args);
        TSharedPtr<FJob> WithCurrentRetryCount(const TOptional<int32> CurrentRetryCount);
        TSharedPtr<FJob> WithMaxTryCount(const TOptional<int32> MaxTryCount);
        TSharedPtr<FJob> WithCreatedAt(const TOptional<int64> CreatedAt);
        TSharedPtr<FJob> WithUpdatedAt(const TOptional<int64> UpdatedAt);

        TOptional<FString> GetJobId() const;
        TOptional<FString> GetName() const;
        TOptional<FString> GetUserId() const;
        TOptional<FString> GetScriptId() const;
        TOptional<FString> GetArgs() const;
        TOptional<int32> GetCurrentRetryCount() const;
        FString GetCurrentRetryCountString() const;
        TOptional<int32> GetMaxTryCount() const;
        FString GetMaxTryCountString() const;
        TOptional<int64> GetCreatedAt() const;
        FString GetCreatedAtString() const;
        TOptional<int64> GetUpdatedAt() const;
        FString GetUpdatedAtString() const;

        static TOptional<FString> GetRegionFromGrn(const FString Grn);
        static TOptional<FString> GetOwnerIdFromGrn(const FString Grn);
        static TOptional<FString> GetNamespaceNameFromGrn(const FString Grn);
        static TOptional<FString> GetUserIdFromGrn(const FString Grn);
        static TOptional<FString> GetJobNameFromGrn(const FString Grn);

        static TSharedPtr<FJob> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;

        static FString TypeName;
    };
    typedef TSharedPtr<FJob, ESPMode::ThreadSafe> FJobPtr;
}