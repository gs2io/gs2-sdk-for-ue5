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

#include "JobQueue/Model/Job.h"

namespace Gs2::JobQueue::Model
{
    FJob::FJob():
        JobIdValue(TOptional<FString>()),
        NameValue(TOptional<FString>()),
        UserIdValue(TOptional<FString>()),
        ScriptIdValue(TOptional<FString>()),
        ArgsValue(TOptional<FString>()),
        CurrentRetryCountValue(TOptional<int32>()),
        MaxTryCountValue(TOptional<int32>()),
        CreatedAtValue(TOptional<int64>()),
        UpdatedAtValue(TOptional<int64>())
    {
    }

    FJob::FJob(
        const FJob& From
    ):
        JobIdValue(From.JobIdValue),
        NameValue(From.NameValue),
        UserIdValue(From.UserIdValue),
        ScriptIdValue(From.ScriptIdValue),
        ArgsValue(From.ArgsValue),
        CurrentRetryCountValue(From.CurrentRetryCountValue),
        MaxTryCountValue(From.MaxTryCountValue),
        CreatedAtValue(From.CreatedAtValue),
        UpdatedAtValue(From.UpdatedAtValue)
    {
    }

    TSharedPtr<FJob> FJob::WithJobId(
        const TOptional<FString> JobId
    )
    {
        this->JobIdValue = JobId;
        return SharedThis(this);
    }

    TSharedPtr<FJob> FJob::WithName(
        const TOptional<FString> Name
    )
    {
        this->NameValue = Name;
        return SharedThis(this);
    }

    TSharedPtr<FJob> FJob::WithUserId(
        const TOptional<FString> UserId
    )
    {
        this->UserIdValue = UserId;
        return SharedThis(this);
    }

    TSharedPtr<FJob> FJob::WithScriptId(
        const TOptional<FString> ScriptId
    )
    {
        this->ScriptIdValue = ScriptId;
        return SharedThis(this);
    }

    TSharedPtr<FJob> FJob::WithArgs(
        const TOptional<FString> Args
    )
    {
        this->ArgsValue = Args;
        return SharedThis(this);
    }

    TSharedPtr<FJob> FJob::WithCurrentRetryCount(
        const TOptional<int32> CurrentRetryCount
    )
    {
        this->CurrentRetryCountValue = CurrentRetryCount;
        return SharedThis(this);
    }

    TSharedPtr<FJob> FJob::WithMaxTryCount(
        const TOptional<int32> MaxTryCount
    )
    {
        this->MaxTryCountValue = MaxTryCount;
        return SharedThis(this);
    }

    TSharedPtr<FJob> FJob::WithCreatedAt(
        const TOptional<int64> CreatedAt
    )
    {
        this->CreatedAtValue = CreatedAt;
        return SharedThis(this);
    }

    TSharedPtr<FJob> FJob::WithUpdatedAt(
        const TOptional<int64> UpdatedAt
    )
    {
        this->UpdatedAtValue = UpdatedAt;
        return SharedThis(this);
    }
    TOptional<FString> FJob::GetJobId() const
    {
        return JobIdValue;
    }
    TOptional<FString> FJob::GetName() const
    {
        return NameValue;
    }
    TOptional<FString> FJob::GetUserId() const
    {
        return UserIdValue;
    }
    TOptional<FString> FJob::GetScriptId() const
    {
        return ScriptIdValue;
    }
    TOptional<FString> FJob::GetArgs() const
    {
        return ArgsValue;
    }
    TOptional<int32> FJob::GetCurrentRetryCount() const
    {
        return CurrentRetryCountValue;
    }

    FString FJob::GetCurrentRetryCountString() const
    {
        if (!CurrentRetryCountValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%ld"), CurrentRetryCountValue.GetValue());
    }
    TOptional<int32> FJob::GetMaxTryCount() const
    {
        return MaxTryCountValue;
    }

    FString FJob::GetMaxTryCountString() const
    {
        if (!MaxTryCountValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%ld"), MaxTryCountValue.GetValue());
    }
    TOptional<int64> FJob::GetCreatedAt() const
    {
        return CreatedAtValue;
    }

    FString FJob::GetCreatedAtString() const
    {
        if (!CreatedAtValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), CreatedAtValue.GetValue());
    }
    TOptional<int64> FJob::GetUpdatedAt() const
    {
        return UpdatedAtValue;
    }

    FString FJob::GetUpdatedAtString() const
    {
        if (!UpdatedAtValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), UpdatedAtValue.GetValue());
    }

    TOptional<FString> FJob::GetRegionFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):queue:(?<namespaceName>.+):user:(?<userId>.+):job:(?<jobName>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(1);
        }
        return TOptional<FString>();
    }

    TOptional<FString> FJob::GetOwnerIdFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):queue:(?<namespaceName>.+):user:(?<userId>.+):job:(?<jobName>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(2);
        }
        return TOptional<FString>();
    }

    TOptional<FString> FJob::GetNamespaceNameFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):queue:(?<namespaceName>.+):user:(?<userId>.+):job:(?<jobName>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(3);
        }
        return TOptional<FString>();
    }

    TOptional<FString> FJob::GetUserIdFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):queue:(?<namespaceName>.+):user:(?<userId>.+):job:(?<jobName>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(4);
        }
        return TOptional<FString>();
    }

    TOptional<FString> FJob::GetJobNameFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):queue:(?<namespaceName>.+):user:(?<userId>.+):job:(?<jobName>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(5);
        }
        return TOptional<FString>();
    }

    TSharedPtr<FJob> FJob::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FJob>()
            ->WithJobId(Data->HasField("jobId") ? [Data]() -> TOptional<FString>
                {
                    FString v;
                    if (Data->TryGetStringField("jobId", v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithName(Data->HasField("name") ? [Data]() -> TOptional<FString>
                {
                    FString v;
                    if (Data->TryGetStringField("name", v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithUserId(Data->HasField("userId") ? [Data]() -> TOptional<FString>
                {
                    FString v;
                    if (Data->TryGetStringField("userId", v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithScriptId(Data->HasField("scriptId") ? [Data]() -> TOptional<FString>
                {
                    FString v;
                    if (Data->TryGetStringField("scriptId", v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithArgs(Data->HasField("args") ? [Data]() -> TOptional<FString>
                {
                    FString v;
                    if (Data->TryGetStringField("args", v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithCurrentRetryCount(Data->HasField("currentRetryCount") ? [Data]() -> TOptional<int32>
                {
                    int32 v;
                    if (Data->TryGetNumberField("currentRetryCount", v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<int32>();
                }() : TOptional<int32>())
            ->WithMaxTryCount(Data->HasField("maxTryCount") ? [Data]() -> TOptional<int32>
                {
                    int32 v;
                    if (Data->TryGetNumberField("maxTryCount", v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<int32>();
                }() : TOptional<int32>())
            ->WithCreatedAt(Data->HasField("createdAt") ? [Data]() -> TOptional<int64>
                {
                    int64 v;
                    if (Data->TryGetNumberField("createdAt", v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<int64>();
                }() : TOptional<int64>())
            ->WithUpdatedAt(Data->HasField("updatedAt") ? [Data]() -> TOptional<int64>
                {
                    int64 v;
                    if (Data->TryGetNumberField("updatedAt", v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<int64>();
                }() : TOptional<int64>());
    }

    TSharedPtr<FJsonObject> FJob::ToJson() const
    {
        const TSharedPtr<FJsonObject> JsonRootObject = MakeShared<FJsonObject>();
        if (JobIdValue.IsSet())
        {
            JsonRootObject->SetStringField("jobId", JobIdValue.GetValue());
        }
        if (NameValue.IsSet())
        {
            JsonRootObject->SetStringField("name", NameValue.GetValue());
        }
        if (UserIdValue.IsSet())
        {
            JsonRootObject->SetStringField("userId", UserIdValue.GetValue());
        }
        if (ScriptIdValue.IsSet())
        {
            JsonRootObject->SetStringField("scriptId", ScriptIdValue.GetValue());
        }
        if (ArgsValue.IsSet())
        {
            JsonRootObject->SetStringField("args", ArgsValue.GetValue());
        }
        if (CurrentRetryCountValue.IsSet())
        {
            JsonRootObject->SetNumberField("currentRetryCount", CurrentRetryCountValue.GetValue());
        }
        if (MaxTryCountValue.IsSet())
        {
            JsonRootObject->SetNumberField("maxTryCount", MaxTryCountValue.GetValue());
        }
        if (CreatedAtValue.IsSet())
        {
            JsonRootObject->SetStringField("createdAt", FString::Printf(TEXT("%lld"), CreatedAtValue.GetValue()));
        }
        if (UpdatedAtValue.IsSet())
        {
            JsonRootObject->SetStringField("updatedAt", FString::Printf(TEXT("%lld"), UpdatedAtValue.GetValue()));
        }
        return JsonRootObject;
    }

    FString FJob::TypeName = "Job";
}