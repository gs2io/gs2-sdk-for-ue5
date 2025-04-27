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
#include "Dom/JsonObject.h"

namespace Gs2::Log::Request
{
    class FCreateNamespaceRequest;

    class GS2LOG_API FCreateNamespaceRequest final : public TSharedFromThis<FCreateNamespaceRequest>
    {
        TOptional<FString> ContextStackValue;
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
        
    public:
        
        FCreateNamespaceRequest();
        FCreateNamespaceRequest(
            const FCreateNamespaceRequest& From
        );
        ~FCreateNamespaceRequest() = default;

        TSharedPtr<FCreateNamespaceRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FCreateNamespaceRequest> WithName(const TOptional<FString> Name);
        TSharedPtr<FCreateNamespaceRequest> WithDescription(const TOptional<FString> Description);
        TSharedPtr<FCreateNamespaceRequest> WithType(const TOptional<FString> Type);
        TSharedPtr<FCreateNamespaceRequest> WithGcpCredentialJson(const TOptional<FString> GcpCredentialJson);
        TSharedPtr<FCreateNamespaceRequest> WithBigQueryDatasetName(const TOptional<FString> BigQueryDatasetName);
        TSharedPtr<FCreateNamespaceRequest> WithLogExpireDays(const TOptional<int32> LogExpireDays);
        TSharedPtr<FCreateNamespaceRequest> WithAwsRegion(const TOptional<FString> AwsRegion);
        TSharedPtr<FCreateNamespaceRequest> WithAwsAccessKeyId(const TOptional<FString> AwsAccessKeyId);
        TSharedPtr<FCreateNamespaceRequest> WithAwsSecretAccessKey(const TOptional<FString> AwsSecretAccessKey);
        TSharedPtr<FCreateNamespaceRequest> WithFirehoseStreamName(const TOptional<FString> FirehoseStreamName);
        TSharedPtr<FCreateNamespaceRequest> WithFirehoseCompressData(const TOptional<FString> FirehoseCompressData);

        TOptional<FString> GetContextStack() const;
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

        static TSharedPtr<FCreateNamespaceRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FCreateNamespaceRequest> FCreateNamespaceRequestPtr;
}