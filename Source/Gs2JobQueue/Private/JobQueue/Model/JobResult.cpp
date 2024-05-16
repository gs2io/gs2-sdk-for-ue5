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

#include "JobQueue/Model/JobResult.h"

namespace Gs2::JobQueue::Model
{
    FJobResult::FJobResult():
        JobResultIdValue(TOptional<FString>()),
        JobIdValue(TOptional<FString>()),
        ScriptIdValue(TOptional<FString>()),
        ArgsValue(TOptional<FString>()),
        TryNumberValue(TOptional<int32>()),
        StatusCodeValue(TOptional<int32>()),
        ResultValue(TOptional<FString>()),
        TryAtValue(TOptional<int64>())
    {
    }

    FJobResult::FJobResult(
        const FJobResult& From
    ):
        JobResultIdValue(From.JobResultIdValue),
        JobIdValue(From.JobIdValue),
        ScriptIdValue(From.ScriptIdValue),
        ArgsValue(From.ArgsValue),
        TryNumberValue(From.TryNumberValue),
        StatusCodeValue(From.StatusCodeValue),
        ResultValue(From.ResultValue),
        TryAtValue(From.TryAtValue)
    {
    }

    TSharedPtr<FJobResult> FJobResult::WithJobResultId(
        const TOptional<FString> JobResultId
    )
    {
        this->JobResultIdValue = JobResultId;
        return SharedThis(this);
    }

    TSharedPtr<FJobResult> FJobResult::WithJobId(
        const TOptional<FString> JobId
    )
    {
        this->JobIdValue = JobId;
        return SharedThis(this);
    }

    TSharedPtr<FJobResult> FJobResult::WithScriptId(
        const TOptional<FString> ScriptId
    )
    {
        this->ScriptIdValue = ScriptId;
        return SharedThis(this);
    }

    TSharedPtr<FJobResult> FJobResult::WithArgs(
        const TOptional<FString> Args
    )
    {
        this->ArgsValue = Args;
        return SharedThis(this);
    }

    TSharedPtr<FJobResult> FJobResult::WithTryNumber(
        const TOptional<int32> TryNumber
    )
    {
        this->TryNumberValue = TryNumber;
        return SharedThis(this);
    }

    TSharedPtr<FJobResult> FJobResult::WithStatusCode(
        const TOptional<int32> StatusCode
    )
    {
        this->StatusCodeValue = StatusCode;
        return SharedThis(this);
    }

    TSharedPtr<FJobResult> FJobResult::WithResult(
        const TOptional<FString> Result
    )
    {
        this->ResultValue = Result;
        return SharedThis(this);
    }

    TSharedPtr<FJobResult> FJobResult::WithTryAt(
        const TOptional<int64> TryAt
    )
    {
        this->TryAtValue = TryAt;
        return SharedThis(this);
    }
    TOptional<FString> FJobResult::GetJobResultId() const
    {
        return JobResultIdValue;
    }
    TOptional<FString> FJobResult::GetJobId() const
    {
        return JobIdValue;
    }
    TOptional<FString> FJobResult::GetScriptId() const
    {
        return ScriptIdValue;
    }
    TOptional<FString> FJobResult::GetArgs() const
    {
        return ArgsValue;
    }
    TOptional<int32> FJobResult::GetTryNumber() const
    {
        return TryNumberValue;
    }

    FString FJobResult::GetTryNumberString() const
    {
        if (!TryNumberValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%d"), TryNumberValue.GetValue());
    }
    TOptional<int32> FJobResult::GetStatusCode() const
    {
        return StatusCodeValue;
    }

    FString FJobResult::GetStatusCodeString() const
    {
        if (!StatusCodeValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%d"), StatusCodeValue.GetValue());
    }
    TOptional<FString> FJobResult::GetResult() const
    {
        return ResultValue;
    }
    TOptional<int64> FJobResult::GetTryAt() const
    {
        return TryAtValue;
    }

    FString FJobResult::GetTryAtString() const
    {
        if (!TryAtValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), TryAtValue.GetValue());
    }

    TOptional<FString> FJobResult::GetRegionFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):queue:(?<namespaceName>.+):user:(?<userId>.+):job:(?<jobName>.+):jobResult:(?<tryNumber>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(1);
        }
        return TOptional<FString>();
    }

    TOptional<FString> FJobResult::GetOwnerIdFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):queue:(?<namespaceName>.+):user:(?<userId>.+):job:(?<jobName>.+):jobResult:(?<tryNumber>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(2);
        }
        return TOptional<FString>();
    }

    TOptional<FString> FJobResult::GetNamespaceNameFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):queue:(?<namespaceName>.+):user:(?<userId>.+):job:(?<jobName>.+):jobResult:(?<tryNumber>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(3);
        }
        return TOptional<FString>();
    }

    TOptional<FString> FJobResult::GetUserIdFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):queue:(?<namespaceName>.+):user:(?<userId>.+):job:(?<jobName>.+):jobResult:(?<tryNumber>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(4);
        }
        return TOptional<FString>();
    }

    TOptional<FString> FJobResult::GetJobNameFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):queue:(?<namespaceName>.+):user:(?<userId>.+):job:(?<jobName>.+):jobResult:(?<tryNumber>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(5);
        }
        return TOptional<FString>();
    }

    TOptional<FString> FJobResult::GetTryNumberFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):queue:(?<namespaceName>.+):user:(?<userId>.+):job:(?<jobName>.+):jobResult:(?<tryNumber>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(6);
        }
        return TOptional<FString>();
    }

    TSharedPtr<FJobResult> FJobResult::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FJobResult>()
            ->WithJobResultId(Data->HasField(ANSI_TO_TCHAR("jobResultId")) ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("jobResultId"), v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithJobId(Data->HasField(ANSI_TO_TCHAR("jobId")) ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("jobId"), v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithScriptId(Data->HasField(ANSI_TO_TCHAR("scriptId")) ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("scriptId"), v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithArgs(Data->HasField(ANSI_TO_TCHAR("args")) ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("args"), v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithTryNumber(Data->HasField(ANSI_TO_TCHAR("tryNumber")) ? [Data]() -> TOptional<int32>
                {
                    int32 v;
                    if (Data->TryGetNumberField(ANSI_TO_TCHAR("tryNumber"), v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<int32>();
                }() : TOptional<int32>())
            ->WithStatusCode(Data->HasField(ANSI_TO_TCHAR("statusCode")) ? [Data]() -> TOptional<int32>
                {
                    int32 v;
                    if (Data->TryGetNumberField(ANSI_TO_TCHAR("statusCode"), v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<int32>();
                }() : TOptional<int32>())
            ->WithResult(Data->HasField(ANSI_TO_TCHAR("result")) ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("result"), v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithTryAt(Data->HasField(ANSI_TO_TCHAR("tryAt")) ? [Data]() -> TOptional<int64>
                {
                    int64 v;
                    if (Data->TryGetNumberField(ANSI_TO_TCHAR("tryAt"), v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<int64>();
                }() : TOptional<int64>());
    }

    TSharedPtr<FJsonObject> FJobResult::ToJson() const
    {
        const TSharedPtr<FJsonObject> JsonRootObject = MakeShared<FJsonObject>();
        if (JobResultIdValue.IsSet())
        {
            JsonRootObject->SetStringField("jobResultId", JobResultIdValue.GetValue());
        }
        if (JobIdValue.IsSet())
        {
            JsonRootObject->SetStringField("jobId", JobIdValue.GetValue());
        }
        if (ScriptIdValue.IsSet())
        {
            JsonRootObject->SetStringField("scriptId", ScriptIdValue.GetValue());
        }
        if (ArgsValue.IsSet())
        {
            JsonRootObject->SetStringField("args", ArgsValue.GetValue());
        }
        if (TryNumberValue.IsSet())
        {
            JsonRootObject->SetNumberField("tryNumber", TryNumberValue.GetValue());
        }
        if (StatusCodeValue.IsSet())
        {
            JsonRootObject->SetNumberField("statusCode", StatusCodeValue.GetValue());
        }
        if (ResultValue.IsSet())
        {
            JsonRootObject->SetStringField("result", ResultValue.GetValue());
        }
        if (TryAtValue.IsSet())
        {
            JsonRootObject->SetStringField("tryAt", FString::Printf(TEXT("%lld"), TryAtValue.GetValue()));
        }
        return JsonRootObject;
    }

    FString FJobResult::TypeName = "JobResult";
}