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

namespace Gs2::Log::Model
{
    class GS2LOG_API FNamespace final : public FGs2Object, public TSharedFromThis<FNamespace>
    {
        TOptional<FString> NamespaceIdValue;
        TOptional<FString> NameValue;
        TOptional<FString> DescriptionValue;
        TOptional<FString> TypeValue;
        TOptional<FString> GcpCredentialJsonValue;
        TOptional<FString> BigQueryDatasetNameValue;
        TOptional<int32> LogExpireDaysValue;
        TOptional<FString> AwsRegionValue;
        TOptional<FString> AwsAccessKeyIdValue;
        TOptional<FString> AwsSecretAccessKeyValue;
        TOptional<FString> FirehoseStreamNameValue;
        TOptional<FString> FirehoseCompressDataValue;
        TOptional<FString> StatusValue;
        TOptional<int64> CreatedAtValue;
        TOptional<int64> UpdatedAtValue;
        TOptional<int64> RevisionValue;

    public:
        FNamespace();
        FNamespace(
            const FNamespace& From
        );
        virtual ~FNamespace() override = default;

        TSharedPtr<FNamespace> WithNamespaceId(const TOptional<FString> NamespaceId);
        TSharedPtr<FNamespace> WithName(const TOptional<FString> Name);
        TSharedPtr<FNamespace> WithDescription(const TOptional<FString> Description);
        TSharedPtr<FNamespace> WithType(const TOptional<FString> Type);
        TSharedPtr<FNamespace> WithGcpCredentialJson(const TOptional<FString> GcpCredentialJson);
        TSharedPtr<FNamespace> WithBigQueryDatasetName(const TOptional<FString> BigQueryDatasetName);
        TSharedPtr<FNamespace> WithLogExpireDays(const TOptional<int32> LogExpireDays);
        TSharedPtr<FNamespace> WithAwsRegion(const TOptional<FString> AwsRegion);
        TSharedPtr<FNamespace> WithAwsAccessKeyId(const TOptional<FString> AwsAccessKeyId);
        TSharedPtr<FNamespace> WithAwsSecretAccessKey(const TOptional<FString> AwsSecretAccessKey);
        TSharedPtr<FNamespace> WithFirehoseStreamName(const TOptional<FString> FirehoseStreamName);
        TSharedPtr<FNamespace> WithFirehoseCompressData(const TOptional<FString> FirehoseCompressData);
        TSharedPtr<FNamespace> WithStatus(const TOptional<FString> Status);
        TSharedPtr<FNamespace> WithCreatedAt(const TOptional<int64> CreatedAt);
        TSharedPtr<FNamespace> WithUpdatedAt(const TOptional<int64> UpdatedAt);
        TSharedPtr<FNamespace> WithRevision(const TOptional<int64> Revision);

        TOptional<FString> GetNamespaceId() const;
        TOptional<FString> GetName() const;
        TOptional<FString> GetDescription() const;
        TOptional<FString> GetType() const;
        TOptional<FString> GetGcpCredentialJson() const;
        TOptional<FString> GetBigQueryDatasetName() const;
        TOptional<int32> GetLogExpireDays() const;
        FString GetLogExpireDaysString() const;
        TOptional<FString> GetAwsRegion() const;
        TOptional<FString> GetAwsAccessKeyId() const;
        TOptional<FString> GetAwsSecretAccessKey() const;
        TOptional<FString> GetFirehoseStreamName() const;
        TOptional<FString> GetFirehoseCompressData() const;
        TOptional<FString> GetStatus() const;
        TOptional<int64> GetCreatedAt() const;
        FString GetCreatedAtString() const;
        TOptional<int64> GetUpdatedAt() const;
        FString GetUpdatedAtString() const;
        TOptional<int64> GetRevision() const;
        FString GetRevisionString() const;

        static TOptional<FString> GetRegionFromGrn(const FString Grn);
        static TOptional<FString> GetOwnerIdFromGrn(const FString Grn);
        static TOptional<FString> GetNamespaceNameFromGrn(const FString Grn);

        static TSharedPtr<FNamespace> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;

        static FString TypeName;
    };
    typedef TSharedPtr<FNamespace, ESPMode::ThreadSafe> FNamespacePtr;
}