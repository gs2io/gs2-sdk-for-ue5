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
#include "AcquireAction.h"
#include "TimeSpan.h"

namespace Gs2::Inbox::Model
{
    class GS2INBOX_API FGlobalMessageMaster final : public Gs2Object, public TSharedFromThis<FGlobalMessageMaster>
    {
        TOptional<FString> GlobalMessageIdValue;
        TOptional<FString> NameValue;
        TOptional<FString> MetadataValue;
        TSharedPtr<TArray<TSharedPtr<FAcquireAction>>> ReadAcquireActionsValue;
        TSharedPtr<FTimeSpan> ExpiresTimeSpanValue;
        TOptional<int64> CreatedAtValue;
        TOptional<int64> ExpiresAtValue;

    public:
        FGlobalMessageMaster();
        FGlobalMessageMaster(
            const FGlobalMessageMaster& From
        );
        virtual ~FGlobalMessageMaster() override = default;

        TSharedPtr<FGlobalMessageMaster> WithGlobalMessageId(const TOptional<FString> GlobalMessageId);
        TSharedPtr<FGlobalMessageMaster> WithName(const TOptional<FString> Name);
        TSharedPtr<FGlobalMessageMaster> WithMetadata(const TOptional<FString> Metadata);
        TSharedPtr<FGlobalMessageMaster> WithReadAcquireActions(const TSharedPtr<TArray<TSharedPtr<FAcquireAction>>> ReadAcquireActions);
        TSharedPtr<FGlobalMessageMaster> WithExpiresTimeSpan(const TSharedPtr<FTimeSpan> ExpiresTimeSpan);
        TSharedPtr<FGlobalMessageMaster> WithCreatedAt(const TOptional<int64> CreatedAt);
        TSharedPtr<FGlobalMessageMaster> WithExpiresAt(const TOptional<int64> ExpiresAt);

        TOptional<FString> GetGlobalMessageId() const;
        TOptional<FString> GetName() const;
        TOptional<FString> GetMetadata() const;
        TSharedPtr<TArray<TSharedPtr<FAcquireAction>>> GetReadAcquireActions() const;
        TSharedPtr<FTimeSpan> GetExpiresTimeSpan() const;
        TOptional<int64> GetCreatedAt() const;
        FString GetCreatedAtString() const;
        TOptional<int64> GetExpiresAt() const;
        FString GetExpiresAtString() const;

        static TOptional<FString> GetRegionFromGrn(const FString Grn);
        static TOptional<FString> GetOwnerIdFromGrn(const FString Grn);
        static TOptional<FString> GetNamespaceNameFromGrn(const FString Grn);
        static TOptional<FString> GetGlobalMessageNameFromGrn(const FString Grn);

        static TSharedPtr<FGlobalMessageMaster> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;

        static FString TypeName;
    };
    typedef TSharedPtr<FGlobalMessageMaster, ESPMode::ThreadSafe> FGlobalMessageMasterPtr;
}