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
#include "AppleAppStoreSubscriptionContent.h"
#include "GooglePlaySubscriptionContent.h"

namespace Gs2::Money2::Model
{
    class GS2MONEY2_API FStoreSubscriptionContentModelMaster final : public Gs2Object, public TSharedFromThis<FStoreSubscriptionContentModelMaster>
    {
        TOptional<FString> StoreSubscriptionContentModelIdValue;
        TOptional<FString> NameValue;
        TOptional<FString> DescriptionValue;
        TOptional<FString> MetadataValue;
        TOptional<FString> ScheduleNamespaceIdValue;
        TOptional<FString> TriggerNameValue;
        TOptional<int32> ReallocateSpanDaysValue;
        TSharedPtr<FAppleAppStoreSubscriptionContent> AppleAppStoreValue;
        TSharedPtr<FGooglePlaySubscriptionContent> GooglePlayValue;
        TOptional<int64> CreatedAtValue;
        TOptional<int64> UpdatedAtValue;
        TOptional<int64> RevisionValue;

    public:
        FStoreSubscriptionContentModelMaster();
        FStoreSubscriptionContentModelMaster(
            const FStoreSubscriptionContentModelMaster& From
        );
        virtual ~FStoreSubscriptionContentModelMaster() override = default;

        TSharedPtr<FStoreSubscriptionContentModelMaster> WithStoreSubscriptionContentModelId(const TOptional<FString> StoreSubscriptionContentModelId);
        TSharedPtr<FStoreSubscriptionContentModelMaster> WithName(const TOptional<FString> Name);
        TSharedPtr<FStoreSubscriptionContentModelMaster> WithDescription(const TOptional<FString> Description);
        TSharedPtr<FStoreSubscriptionContentModelMaster> WithMetadata(const TOptional<FString> Metadata);
        TSharedPtr<FStoreSubscriptionContentModelMaster> WithScheduleNamespaceId(const TOptional<FString> ScheduleNamespaceId);
        TSharedPtr<FStoreSubscriptionContentModelMaster> WithTriggerName(const TOptional<FString> TriggerName);
        TSharedPtr<FStoreSubscriptionContentModelMaster> WithReallocateSpanDays(const TOptional<int32> ReallocateSpanDays);
        TSharedPtr<FStoreSubscriptionContentModelMaster> WithAppleAppStore(const TSharedPtr<FAppleAppStoreSubscriptionContent> AppleAppStore);
        TSharedPtr<FStoreSubscriptionContentModelMaster> WithGooglePlay(const TSharedPtr<FGooglePlaySubscriptionContent> GooglePlay);
        TSharedPtr<FStoreSubscriptionContentModelMaster> WithCreatedAt(const TOptional<int64> CreatedAt);
        TSharedPtr<FStoreSubscriptionContentModelMaster> WithUpdatedAt(const TOptional<int64> UpdatedAt);
        TSharedPtr<FStoreSubscriptionContentModelMaster> WithRevision(const TOptional<int64> Revision);

        TOptional<FString> GetStoreSubscriptionContentModelId() const;
        TOptional<FString> GetName() const;
        TOptional<FString> GetDescription() const;
        TOptional<FString> GetMetadata() const;
        TOptional<FString> GetScheduleNamespaceId() const;
        TOptional<FString> GetTriggerName() const;
        TOptional<int32> GetReallocateSpanDays() const;
        FString GetReallocateSpanDaysString() const;
        TSharedPtr<FAppleAppStoreSubscriptionContent> GetAppleAppStore() const;
        TSharedPtr<FGooglePlaySubscriptionContent> GetGooglePlay() const;
        TOptional<int64> GetCreatedAt() const;
        FString GetCreatedAtString() const;
        TOptional<int64> GetUpdatedAt() const;
        FString GetUpdatedAtString() const;
        TOptional<int64> GetRevision() const;
        FString GetRevisionString() const;

        static TOptional<FString> GetRegionFromGrn(const FString Grn);
        static TOptional<FString> GetOwnerIdFromGrn(const FString Grn);
        static TOptional<FString> GetNamespaceNameFromGrn(const FString Grn);
        static TOptional<FString> GetContentNameFromGrn(const FString Grn);

        static TSharedPtr<FStoreSubscriptionContentModelMaster> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;

        static FString TypeName;
    };
    typedef TSharedPtr<FStoreSubscriptionContentModelMaster, ESPMode::ThreadSafe> FStoreSubscriptionContentModelMasterPtr;
}