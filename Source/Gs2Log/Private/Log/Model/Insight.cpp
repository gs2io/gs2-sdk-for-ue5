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

#include "Log/Model/Insight.h"

namespace Gs2::Log::Model
{
    FInsight::FInsight():
        InsightIdValue(TOptional<FString>()),
        NameValue(TOptional<FString>()),
        TaskIdValue(TOptional<FString>()),
        HostValue(TOptional<FString>()),
        PasswordValue(TOptional<FString>()),
        StatusValue(TOptional<FString>()),
        CreatedAtValue(TOptional<int64>()),
        RevisionValue(TOptional<int64>())
    {
    }

    FInsight::FInsight(
        const FInsight& From
    ):
        InsightIdValue(From.InsightIdValue),
        NameValue(From.NameValue),
        TaskIdValue(From.TaskIdValue),
        HostValue(From.HostValue),
        PasswordValue(From.PasswordValue),
        StatusValue(From.StatusValue),
        CreatedAtValue(From.CreatedAtValue),
        RevisionValue(From.RevisionValue)
    {
    }

    TSharedPtr<FInsight> FInsight::WithInsightId(
        const TOptional<FString> InsightId
    )
    {
        this->InsightIdValue = InsightId;
        return SharedThis(this);
    }

    TSharedPtr<FInsight> FInsight::WithName(
        const TOptional<FString> Name
    )
    {
        this->NameValue = Name;
        return SharedThis(this);
    }

    TSharedPtr<FInsight> FInsight::WithTaskId(
        const TOptional<FString> TaskId
    )
    {
        this->TaskIdValue = TaskId;
        return SharedThis(this);
    }

    TSharedPtr<FInsight> FInsight::WithHost(
        const TOptional<FString> Host
    )
    {
        this->HostValue = Host;
        return SharedThis(this);
    }

    TSharedPtr<FInsight> FInsight::WithPassword(
        const TOptional<FString> Password
    )
    {
        this->PasswordValue = Password;
        return SharedThis(this);
    }

    TSharedPtr<FInsight> FInsight::WithStatus(
        const TOptional<FString> Status
    )
    {
        this->StatusValue = Status;
        return SharedThis(this);
    }

    TSharedPtr<FInsight> FInsight::WithCreatedAt(
        const TOptional<int64> CreatedAt
    )
    {
        this->CreatedAtValue = CreatedAt;
        return SharedThis(this);
    }

    TSharedPtr<FInsight> FInsight::WithRevision(
        const TOptional<int64> Revision
    )
    {
        this->RevisionValue = Revision;
        return SharedThis(this);
    }
    TOptional<FString> FInsight::GetInsightId() const
    {
        return InsightIdValue;
    }
    TOptional<FString> FInsight::GetName() const
    {
        return NameValue;
    }
    TOptional<FString> FInsight::GetTaskId() const
    {
        return TaskIdValue;
    }
    TOptional<FString> FInsight::GetHost() const
    {
        return HostValue;
    }
    TOptional<FString> FInsight::GetPassword() const
    {
        return PasswordValue;
    }
    TOptional<FString> FInsight::GetStatus() const
    {
        return StatusValue;
    }
    TOptional<int64> FInsight::GetCreatedAt() const
    {
        return CreatedAtValue;
    }

    FString FInsight::GetCreatedAtString() const
    {
        if (!CreatedAtValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), CreatedAtValue.GetValue());
    }
    TOptional<int64> FInsight::GetRevision() const
    {
        return RevisionValue;
    }

    FString FInsight::GetRevisionString() const
    {
        if (!RevisionValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), RevisionValue.GetValue());
    }

    TOptional<FString> FInsight::GetRegionFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):log:(?<namespaceName>.+):insight:(?<insightName>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(1);
        }
        return TOptional<FString>();
    }

    TOptional<FString> FInsight::GetOwnerIdFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):log:(?<namespaceName>.+):insight:(?<insightName>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(2);
        }
        return TOptional<FString>();
    }

    TOptional<FString> FInsight::GetNamespaceNameFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):log:(?<namespaceName>.+):insight:(?<insightName>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(3);
        }
        return TOptional<FString>();
    }

    TOptional<FString> FInsight::GetInsightNameFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):log:(?<namespaceName>.+):insight:(?<insightName>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(4);
        }
        return TOptional<FString>();
    }

    TSharedPtr<FInsight> FInsight::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FInsight>()
            ->WithInsightId(Data->HasField(ANSI_TO_TCHAR("insightId")) ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("insightId"), v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithName(Data->HasField(ANSI_TO_TCHAR("name")) ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("name"), v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithTaskId(Data->HasField(ANSI_TO_TCHAR("taskId")) ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("taskId"), v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithHost(Data->HasField(ANSI_TO_TCHAR("host")) ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("host"), v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithPassword(Data->HasField(ANSI_TO_TCHAR("password")) ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("password"), v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithStatus(Data->HasField(ANSI_TO_TCHAR("status")) ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("status"), v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithCreatedAt(Data->HasField(ANSI_TO_TCHAR("createdAt")) ? [Data]() -> TOptional<int64>
                {
                    int64 v;
                    if (Data->TryGetNumberField(ANSI_TO_TCHAR("createdAt"), v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<int64>();
                }() : TOptional<int64>())
            ->WithRevision(Data->HasField(ANSI_TO_TCHAR("revision")) ? [Data]() -> TOptional<int64>
                {
                    int64 v;
                    if (Data->TryGetNumberField(ANSI_TO_TCHAR("revision"), v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<int64>();
                }() : TOptional<int64>());
    }

    TSharedPtr<FJsonObject> FInsight::ToJson() const
    {
        const TSharedPtr<FJsonObject> JsonRootObject = MakeShared<FJsonObject>();
        if (InsightIdValue.IsSet())
        {
            JsonRootObject->SetStringField("insightId", InsightIdValue.GetValue());
        }
        if (NameValue.IsSet())
        {
            JsonRootObject->SetStringField("name", NameValue.GetValue());
        }
        if (TaskIdValue.IsSet())
        {
            JsonRootObject->SetStringField("taskId", TaskIdValue.GetValue());
        }
        if (HostValue.IsSet())
        {
            JsonRootObject->SetStringField("host", HostValue.GetValue());
        }
        if (PasswordValue.IsSet())
        {
            JsonRootObject->SetStringField("password", PasswordValue.GetValue());
        }
        if (StatusValue.IsSet())
        {
            JsonRootObject->SetStringField("status", StatusValue.GetValue());
        }
        if (CreatedAtValue.IsSet())
        {
            JsonRootObject->SetStringField("createdAt", FString::Printf(TEXT("%lld"), CreatedAtValue.GetValue()));
        }
        if (RevisionValue.IsSet())
        {
            JsonRootObject->SetStringField("revision", FString::Printf(TEXT("%lld"), RevisionValue.GetValue()));
        }
        return JsonRootObject;
    }

    FString FInsight::TypeName = "Insight";
}