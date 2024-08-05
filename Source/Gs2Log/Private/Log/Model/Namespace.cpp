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

#include "Log/Model/Namespace.h"

namespace Gs2::Log::Model
{
    FNamespace::FNamespace():
        NamespaceIdValue(TOptional<FString>()),
        NameValue(TOptional<FString>()),
        DescriptionValue(TOptional<FString>()),
        TypeValue(TOptional<FString>()),
        GcpCredentialJsonValue(TOptional<FString>()),
        BigQueryDatasetNameValue(TOptional<FString>()),
        LogExpireDaysValue(TOptional<int32>()),
        AwsRegionValue(TOptional<FString>()),
        AwsAccessKeyIdValue(TOptional<FString>()),
        AwsSecretAccessKeyValue(TOptional<FString>()),
        FirehoseStreamNameValue(TOptional<FString>()),
        StatusValue(TOptional<FString>()),
        CreatedAtValue(TOptional<int64>()),
        UpdatedAtValue(TOptional<int64>()),
        RevisionValue(TOptional<int64>())
    {
    }

    FNamespace::FNamespace(
        const FNamespace& From
    ):
        NamespaceIdValue(From.NamespaceIdValue),
        NameValue(From.NameValue),
        DescriptionValue(From.DescriptionValue),
        TypeValue(From.TypeValue),
        GcpCredentialJsonValue(From.GcpCredentialJsonValue),
        BigQueryDatasetNameValue(From.BigQueryDatasetNameValue),
        LogExpireDaysValue(From.LogExpireDaysValue),
        AwsRegionValue(From.AwsRegionValue),
        AwsAccessKeyIdValue(From.AwsAccessKeyIdValue),
        AwsSecretAccessKeyValue(From.AwsSecretAccessKeyValue),
        FirehoseStreamNameValue(From.FirehoseStreamNameValue),
        StatusValue(From.StatusValue),
        CreatedAtValue(From.CreatedAtValue),
        UpdatedAtValue(From.UpdatedAtValue),
        RevisionValue(From.RevisionValue)
    {
    }

    TSharedPtr<FNamespace> FNamespace::WithNamespaceId(
        const TOptional<FString> NamespaceId
    )
    {
        this->NamespaceIdValue = NamespaceId;
        return SharedThis(this);
    }

    TSharedPtr<FNamespace> FNamespace::WithName(
        const TOptional<FString> Name
    )
    {
        this->NameValue = Name;
        return SharedThis(this);
    }

    TSharedPtr<FNamespace> FNamespace::WithDescription(
        const TOptional<FString> Description
    )
    {
        this->DescriptionValue = Description;
        return SharedThis(this);
    }

    TSharedPtr<FNamespace> FNamespace::WithType(
        const TOptional<FString> Type
    )
    {
        this->TypeValue = Type;
        return SharedThis(this);
    }

    TSharedPtr<FNamespace> FNamespace::WithGcpCredentialJson(
        const TOptional<FString> GcpCredentialJson
    )
    {
        this->GcpCredentialJsonValue = GcpCredentialJson;
        return SharedThis(this);
    }

    TSharedPtr<FNamespace> FNamespace::WithBigQueryDatasetName(
        const TOptional<FString> BigQueryDatasetName
    )
    {
        this->BigQueryDatasetNameValue = BigQueryDatasetName;
        return SharedThis(this);
    }

    TSharedPtr<FNamespace> FNamespace::WithLogExpireDays(
        const TOptional<int32> LogExpireDays
    )
    {
        this->LogExpireDaysValue = LogExpireDays;
        return SharedThis(this);
    }

    TSharedPtr<FNamespace> FNamespace::WithAwsRegion(
        const TOptional<FString> AwsRegion
    )
    {
        this->AwsRegionValue = AwsRegion;
        return SharedThis(this);
    }

    TSharedPtr<FNamespace> FNamespace::WithAwsAccessKeyId(
        const TOptional<FString> AwsAccessKeyId
    )
    {
        this->AwsAccessKeyIdValue = AwsAccessKeyId;
        return SharedThis(this);
    }

    TSharedPtr<FNamespace> FNamespace::WithAwsSecretAccessKey(
        const TOptional<FString> AwsSecretAccessKey
    )
    {
        this->AwsSecretAccessKeyValue = AwsSecretAccessKey;
        return SharedThis(this);
    }

    TSharedPtr<FNamespace> FNamespace::WithFirehoseStreamName(
        const TOptional<FString> FirehoseStreamName
    )
    {
        this->FirehoseStreamNameValue = FirehoseStreamName;
        return SharedThis(this);
    }

    TSharedPtr<FNamespace> FNamespace::WithStatus(
        const TOptional<FString> Status
    )
    {
        this->StatusValue = Status;
        return SharedThis(this);
    }

    TSharedPtr<FNamespace> FNamespace::WithCreatedAt(
        const TOptional<int64> CreatedAt
    )
    {
        this->CreatedAtValue = CreatedAt;
        return SharedThis(this);
    }

    TSharedPtr<FNamespace> FNamespace::WithUpdatedAt(
        const TOptional<int64> UpdatedAt
    )
    {
        this->UpdatedAtValue = UpdatedAt;
        return SharedThis(this);
    }

    TSharedPtr<FNamespace> FNamespace::WithRevision(
        const TOptional<int64> Revision
    )
    {
        this->RevisionValue = Revision;
        return SharedThis(this);
    }
    TOptional<FString> FNamespace::GetNamespaceId() const
    {
        return NamespaceIdValue;
    }
    TOptional<FString> FNamespace::GetName() const
    {
        return NameValue;
    }
    TOptional<FString> FNamespace::GetDescription() const
    {
        return DescriptionValue;
    }
    TOptional<FString> FNamespace::GetType() const
    {
        return TypeValue;
    }
    TOptional<FString> FNamespace::GetGcpCredentialJson() const
    {
        return GcpCredentialJsonValue;
    }
    TOptional<FString> FNamespace::GetBigQueryDatasetName() const
    {
        return BigQueryDatasetNameValue;
    }
    TOptional<int32> FNamespace::GetLogExpireDays() const
    {
        return LogExpireDaysValue;
    }

    FString FNamespace::GetLogExpireDaysString() const
    {
        if (!LogExpireDaysValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%d"), LogExpireDaysValue.GetValue());
    }
    TOptional<FString> FNamespace::GetAwsRegion() const
    {
        return AwsRegionValue;
    }
    TOptional<FString> FNamespace::GetAwsAccessKeyId() const
    {
        return AwsAccessKeyIdValue;
    }
    TOptional<FString> FNamespace::GetAwsSecretAccessKey() const
    {
        return AwsSecretAccessKeyValue;
    }
    TOptional<FString> FNamespace::GetFirehoseStreamName() const
    {
        return FirehoseStreamNameValue;
    }
    TOptional<FString> FNamespace::GetStatus() const
    {
        return StatusValue;
    }
    TOptional<int64> FNamespace::GetCreatedAt() const
    {
        return CreatedAtValue;
    }

    FString FNamespace::GetCreatedAtString() const
    {
        if (!CreatedAtValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), CreatedAtValue.GetValue());
    }
    TOptional<int64> FNamespace::GetUpdatedAt() const
    {
        return UpdatedAtValue;
    }

    FString FNamespace::GetUpdatedAtString() const
    {
        if (!UpdatedAtValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), UpdatedAtValue.GetValue());
    }
    TOptional<int64> FNamespace::GetRevision() const
    {
        return RevisionValue;
    }

    FString FNamespace::GetRevisionString() const
    {
        if (!RevisionValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), RevisionValue.GetValue());
    }

    TOptional<FString> FNamespace::GetRegionFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):log:(?<namespaceName>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(1);
        }
        return TOptional<FString>();
    }

    TOptional<FString> FNamespace::GetOwnerIdFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):log:(?<namespaceName>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(2);
        }
        return TOptional<FString>();
    }

    TOptional<FString> FNamespace::GetNamespaceNameFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):log:(?<namespaceName>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(3);
        }
        return TOptional<FString>();
    }

    TSharedPtr<FNamespace> FNamespace::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FNamespace>()
            ->WithNamespaceId(Data->HasField(ANSI_TO_TCHAR("namespaceId")) ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("namespaceId"), v))
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
            ->WithDescription(Data->HasField(ANSI_TO_TCHAR("description")) ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("description"), v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithType(Data->HasField(ANSI_TO_TCHAR("type")) ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("type"), v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithGcpCredentialJson(Data->HasField(ANSI_TO_TCHAR("gcpCredentialJson")) ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("gcpCredentialJson"), v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithBigQueryDatasetName(Data->HasField(ANSI_TO_TCHAR("bigQueryDatasetName")) ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("bigQueryDatasetName"), v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithLogExpireDays(Data->HasField(ANSI_TO_TCHAR("logExpireDays")) ? [Data]() -> TOptional<int32>
                {
                    int32 v;
                    if (Data->TryGetNumberField(ANSI_TO_TCHAR("logExpireDays"), v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<int32>();
                }() : TOptional<int32>())
            ->WithAwsRegion(Data->HasField(ANSI_TO_TCHAR("awsRegion")) ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("awsRegion"), v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithAwsAccessKeyId(Data->HasField(ANSI_TO_TCHAR("awsAccessKeyId")) ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("awsAccessKeyId"), v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithAwsSecretAccessKey(Data->HasField(ANSI_TO_TCHAR("awsSecretAccessKey")) ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("awsSecretAccessKey"), v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithFirehoseStreamName(Data->HasField(ANSI_TO_TCHAR("firehoseStreamName")) ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("firehoseStreamName"), v))
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
            ->WithUpdatedAt(Data->HasField(ANSI_TO_TCHAR("updatedAt")) ? [Data]() -> TOptional<int64>
                {
                    int64 v;
                    if (Data->TryGetNumberField(ANSI_TO_TCHAR("updatedAt"), v))
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

    TSharedPtr<FJsonObject> FNamespace::ToJson() const
    {
        const TSharedPtr<FJsonObject> JsonRootObject = MakeShared<FJsonObject>();
        if (NamespaceIdValue.IsSet())
        {
            JsonRootObject->SetStringField("namespaceId", NamespaceIdValue.GetValue());
        }
        if (NameValue.IsSet())
        {
            JsonRootObject->SetStringField("name", NameValue.GetValue());
        }
        if (DescriptionValue.IsSet())
        {
            JsonRootObject->SetStringField("description", DescriptionValue.GetValue());
        }
        if (TypeValue.IsSet())
        {
            JsonRootObject->SetStringField("type", TypeValue.GetValue());
        }
        if (GcpCredentialJsonValue.IsSet())
        {
            JsonRootObject->SetStringField("gcpCredentialJson", GcpCredentialJsonValue.GetValue());
        }
        if (BigQueryDatasetNameValue.IsSet())
        {
            JsonRootObject->SetStringField("bigQueryDatasetName", BigQueryDatasetNameValue.GetValue());
        }
        if (LogExpireDaysValue.IsSet())
        {
            JsonRootObject->SetNumberField("logExpireDays", LogExpireDaysValue.GetValue());
        }
        if (AwsRegionValue.IsSet())
        {
            JsonRootObject->SetStringField("awsRegion", AwsRegionValue.GetValue());
        }
        if (AwsAccessKeyIdValue.IsSet())
        {
            JsonRootObject->SetStringField("awsAccessKeyId", AwsAccessKeyIdValue.GetValue());
        }
        if (AwsSecretAccessKeyValue.IsSet())
        {
            JsonRootObject->SetStringField("awsSecretAccessKey", AwsSecretAccessKeyValue.GetValue());
        }
        if (FirehoseStreamNameValue.IsSet())
        {
            JsonRootObject->SetStringField("firehoseStreamName", FirehoseStreamNameValue.GetValue());
        }
        if (StatusValue.IsSet())
        {
            JsonRootObject->SetStringField("status", StatusValue.GetValue());
        }
        if (CreatedAtValue.IsSet())
        {
            JsonRootObject->SetStringField("createdAt", FString::Printf(TEXT("%lld"), CreatedAtValue.GetValue()));
        }
        if (UpdatedAtValue.IsSet())
        {
            JsonRootObject->SetStringField("updatedAt", FString::Printf(TEXT("%lld"), UpdatedAtValue.GetValue()));
        }
        if (RevisionValue.IsSet())
        {
            JsonRootObject->SetStringField("revision", FString::Printf(TEXT("%lld"), RevisionValue.GetValue()));
        }
        return JsonRootObject;
    }

    FString FNamespace::TypeName = "Namespace";
}