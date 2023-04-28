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

#include "SerialKey/Model/IssueJob.h"

namespace Gs2::SerialKey::Model
{
    FIssueJob::FIssueJob():
        IssueJobIdValue(TOptional<FString>()),
        NameValue(TOptional<FString>()),
        MetadataValue(TOptional<FString>()),
        IssuedCountValue(TOptional<int32>()),
        IssueRequestCountValue(TOptional<int32>()),
        StatusValue(TOptional<FString>()),
        CreatedAtValue(TOptional<int64>())
    {
    }

    FIssueJob::FIssueJob(
        const FIssueJob& From
    ):
        IssueJobIdValue(From.IssueJobIdValue),
        NameValue(From.NameValue),
        MetadataValue(From.MetadataValue),
        IssuedCountValue(From.IssuedCountValue),
        IssueRequestCountValue(From.IssueRequestCountValue),
        StatusValue(From.StatusValue),
        CreatedAtValue(From.CreatedAtValue)
    {
    }

    TSharedPtr<FIssueJob> FIssueJob::WithIssueJobId(
        const TOptional<FString> IssueJobId
    )
    {
        this->IssueJobIdValue = IssueJobId;
        return SharedThis(this);
    }

    TSharedPtr<FIssueJob> FIssueJob::WithName(
        const TOptional<FString> Name
    )
    {
        this->NameValue = Name;
        return SharedThis(this);
    }

    TSharedPtr<FIssueJob> FIssueJob::WithMetadata(
        const TOptional<FString> Metadata
    )
    {
        this->MetadataValue = Metadata;
        return SharedThis(this);
    }

    TSharedPtr<FIssueJob> FIssueJob::WithIssuedCount(
        const TOptional<int32> IssuedCount
    )
    {
        this->IssuedCountValue = IssuedCount;
        return SharedThis(this);
    }

    TSharedPtr<FIssueJob> FIssueJob::WithIssueRequestCount(
        const TOptional<int32> IssueRequestCount
    )
    {
        this->IssueRequestCountValue = IssueRequestCount;
        return SharedThis(this);
    }

    TSharedPtr<FIssueJob> FIssueJob::WithStatus(
        const TOptional<FString> Status
    )
    {
        this->StatusValue = Status;
        return SharedThis(this);
    }

    TSharedPtr<FIssueJob> FIssueJob::WithCreatedAt(
        const TOptional<int64> CreatedAt
    )
    {
        this->CreatedAtValue = CreatedAt;
        return SharedThis(this);
    }
    TOptional<FString> FIssueJob::GetIssueJobId() const
    {
        return IssueJobIdValue;
    }
    TOptional<FString> FIssueJob::GetName() const
    {
        return NameValue;
    }
    TOptional<FString> FIssueJob::GetMetadata() const
    {
        return MetadataValue;
    }
    TOptional<int32> FIssueJob::GetIssuedCount() const
    {
        return IssuedCountValue;
    }

    FString FIssueJob::GetIssuedCountString() const
    {
        if (!IssuedCountValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%d"), IssuedCountValue.GetValue());
    }
    TOptional<int32> FIssueJob::GetIssueRequestCount() const
    {
        return IssueRequestCountValue;
    }

    FString FIssueJob::GetIssueRequestCountString() const
    {
        if (!IssueRequestCountValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%d"), IssueRequestCountValue.GetValue());
    }
    TOptional<FString> FIssueJob::GetStatus() const
    {
        return StatusValue;
    }
    TOptional<int64> FIssueJob::GetCreatedAt() const
    {
        return CreatedAtValue;
    }

    FString FIssueJob::GetCreatedAtString() const
    {
        if (!CreatedAtValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), CreatedAtValue.GetValue());
    }

    TOptional<FString> FIssueJob::GetRegionFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):serialKey:(?<namespaceName>.+):master:campaign:(?<campaignModelName>.+):issue:job:(?<issueJobName>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(1);
        }
        return TOptional<FString>();
    }

    TOptional<FString> FIssueJob::GetOwnerIdFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):serialKey:(?<namespaceName>.+):master:campaign:(?<campaignModelName>.+):issue:job:(?<issueJobName>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(2);
        }
        return TOptional<FString>();
    }

    TOptional<FString> FIssueJob::GetNamespaceNameFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):serialKey:(?<namespaceName>.+):master:campaign:(?<campaignModelName>.+):issue:job:(?<issueJobName>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(3);
        }
        return TOptional<FString>();
    }

    TOptional<FString> FIssueJob::GetCampaignModelNameFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):serialKey:(?<namespaceName>.+):master:campaign:(?<campaignModelName>.+):issue:job:(?<issueJobName>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(4);
        }
        return TOptional<FString>();
    }

    TOptional<FString> FIssueJob::GetIssueJobNameFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):serialKey:(?<namespaceName>.+):master:campaign:(?<campaignModelName>.+):issue:job:(?<issueJobName>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(5);
        }
        return TOptional<FString>();
    }

    TSharedPtr<FIssueJob> FIssueJob::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FIssueJob>()
            ->WithIssueJobId(Data->HasField("issueJobId") ? [Data]() -> TOptional<FString>
                {
                    FString v;
                    if (Data->TryGetStringField("issueJobId", v))
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
            ->WithMetadata(Data->HasField("metadata") ? [Data]() -> TOptional<FString>
                {
                    FString v;
                    if (Data->TryGetStringField("metadata", v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithIssuedCount(Data->HasField("issuedCount") ? [Data]() -> TOptional<int32>
                {
                    int32 v;
                    if (Data->TryGetNumberField("issuedCount", v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<int32>();
                }() : TOptional<int32>())
            ->WithIssueRequestCount(Data->HasField("issueRequestCount") ? [Data]() -> TOptional<int32>
                {
                    int32 v;
                    if (Data->TryGetNumberField("issueRequestCount", v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<int32>();
                }() : TOptional<int32>())
            ->WithStatus(Data->HasField("status") ? [Data]() -> TOptional<FString>
                {
                    FString v;
                    if (Data->TryGetStringField("status", v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithCreatedAt(Data->HasField("createdAt") ? [Data]() -> TOptional<int64>
                {
                    int64 v;
                    if (Data->TryGetNumberField("createdAt", v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<int64>();
                }() : TOptional<int64>());
    }

    TSharedPtr<FJsonObject> FIssueJob::ToJson() const
    {
        const TSharedPtr<FJsonObject> JsonRootObject = MakeShared<FJsonObject>();
        if (IssueJobIdValue.IsSet())
        {
            JsonRootObject->SetStringField("issueJobId", IssueJobIdValue.GetValue());
        }
        if (NameValue.IsSet())
        {
            JsonRootObject->SetStringField("name", NameValue.GetValue());
        }
        if (MetadataValue.IsSet())
        {
            JsonRootObject->SetStringField("metadata", MetadataValue.GetValue());
        }
        if (IssuedCountValue.IsSet())
        {
            JsonRootObject->SetNumberField("issuedCount", IssuedCountValue.GetValue());
        }
        if (IssueRequestCountValue.IsSet())
        {
            JsonRootObject->SetNumberField("issueRequestCount", IssueRequestCountValue.GetValue());
        }
        if (StatusValue.IsSet())
        {
            JsonRootObject->SetStringField("status", StatusValue.GetValue());
        }
        if (CreatedAtValue.IsSet())
        {
            JsonRootObject->SetStringField("createdAt", FString::Printf(TEXT("%lld"), CreatedAtValue.GetValue()));
        }
        return JsonRootObject;
    }

    FString FIssueJob::TypeName = "IssueJob";
}