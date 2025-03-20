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

namespace Gs2::SerialKey::Model
{
    class GS2SERIALKEY_API FIssueJob final : public FGs2Object, public TSharedFromThis<FIssueJob>
    {
        TOptional<FString> IssueJobIdValue;
        TOptional<FString> NameValue;
        TOptional<FString> MetadataValue;
        TOptional<int32> IssuedCountValue;
        TOptional<int32> IssueRequestCountValue;
        TOptional<FString> StatusValue;
        TOptional<int64> CreatedAtValue;
        TOptional<int64> RevisionValue;

    public:
        FIssueJob();
        FIssueJob(
            const FIssueJob& From
        );
        virtual ~FIssueJob() override = default;

        TSharedPtr<FIssueJob> WithIssueJobId(const TOptional<FString> IssueJobId);
        TSharedPtr<FIssueJob> WithName(const TOptional<FString> Name);
        TSharedPtr<FIssueJob> WithMetadata(const TOptional<FString> Metadata);
        TSharedPtr<FIssueJob> WithIssuedCount(const TOptional<int32> IssuedCount);
        TSharedPtr<FIssueJob> WithIssueRequestCount(const TOptional<int32> IssueRequestCount);
        TSharedPtr<FIssueJob> WithStatus(const TOptional<FString> Status);
        TSharedPtr<FIssueJob> WithCreatedAt(const TOptional<int64> CreatedAt);
        TSharedPtr<FIssueJob> WithRevision(const TOptional<int64> Revision);

        TOptional<FString> GetIssueJobId() const;
        TOptional<FString> GetName() const;
        TOptional<FString> GetMetadata() const;
        TOptional<int32> GetIssuedCount() const;
        FString GetIssuedCountString() const;
        TOptional<int32> GetIssueRequestCount() const;
        FString GetIssueRequestCountString() const;
        TOptional<FString> GetStatus() const;
        TOptional<int64> GetCreatedAt() const;
        FString GetCreatedAtString() const;
        TOptional<int64> GetRevision() const;
        FString GetRevisionString() const;

        static TOptional<FString> GetRegionFromGrn(const FString Grn);
        static TOptional<FString> GetOwnerIdFromGrn(const FString Grn);
        static TOptional<FString> GetNamespaceNameFromGrn(const FString Grn);
        static TOptional<FString> GetCampaignModelNameFromGrn(const FString Grn);
        static TOptional<FString> GetIssueJobNameFromGrn(const FString Grn);

        static TSharedPtr<FIssueJob> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;

        static FString TypeName;
    };
    typedef TSharedPtr<FIssueJob, ESPMode::ThreadSafe> FIssueJobPtr;
}