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

namespace Gs2::JobQueue::Model
{
    class GS2JOBQUEUE_API FJobResult final : public TSharedFromThis<FJobResult>
    {
        TOptional<FString> JobResultIdValue;
        TOptional<FString> JobIdValue;
        TOptional<FString> ScriptIdValue;
        TOptional<FString> ArgsValue;
        TOptional<int32> TryNumberValue;
        TOptional<int32> StatusCodeValue;
        TOptional<FString> ResultValue;
        TOptional<int64> TryAtValue;

    public:
        FJobResult();
        FJobResult(
            const FJobResult& From
        );
        ~FJobResult() = default;

        TSharedPtr<FJobResult> WithJobResultId(const TOptional<FString> JobResultId);
        TSharedPtr<FJobResult> WithJobId(const TOptional<FString> JobId);
        TSharedPtr<FJobResult> WithScriptId(const TOptional<FString> ScriptId);
        TSharedPtr<FJobResult> WithArgs(const TOptional<FString> Args);
        TSharedPtr<FJobResult> WithTryNumber(const TOptional<int32> TryNumber);
        TSharedPtr<FJobResult> WithStatusCode(const TOptional<int32> StatusCode);
        TSharedPtr<FJobResult> WithResult(const TOptional<FString> Result);
        TSharedPtr<FJobResult> WithTryAt(const TOptional<int64> TryAt);

        TOptional<FString> GetJobResultId() const;
        TOptional<FString> GetJobId() const;
        TOptional<FString> GetScriptId() const;
        TOptional<FString> GetArgs() const;
        TOptional<int32> GetTryNumber() const;
        FString GetTryNumberString() const;
        TOptional<int32> GetStatusCode() const;
        FString GetStatusCodeString() const;
        TOptional<FString> GetResult() const;
        TOptional<int64> GetTryAt() const;
        FString GetTryAtString() const;

        static TOptional<FString> GetRegionFromGrn(const FString Grn);
        static TOptional<FString> GetOwnerIdFromGrn(const FString Grn);
        static TOptional<FString> GetNamespaceNameFromGrn(const FString Grn);
        static TOptional<FString> GetUserIdFromGrn(const FString Grn);
        static TOptional<FString> GetJobNameFromGrn(const FString Grn);
        static TOptional<FString> GetTryNumberFromGrn(const FString Grn);

        static TSharedPtr<FJobResult> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;

        static FString TypeName;
    };
    typedef TSharedPtr<FJobResult, ESPMode::ThreadSafe> FJobResultPtr;
}