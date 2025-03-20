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
    class GS2MONEY2_API FStoreSubscriptionContentModel final : public FGs2Object, public TSharedFromThis<FStoreSubscriptionContentModel>
    {
        TOptional<FString> StoreSubscriptionContentModelIdValue;
        TOptional<FString> NameValue;
        TOptional<FString> MetadataValue;
        TOptional<FString> ScheduleNamespaceIdValue;
        TOptional<FString> TriggerNameValue;
        TOptional<FString> TriggerExtendModeValue;
        TOptional<int32> RollupHourValue;
        TOptional<int32> ReallocateSpanDaysValue;
        TSharedPtr<FAppleAppStoreSubscriptionContent> AppleAppStoreValue;
        TSharedPtr<FGooglePlaySubscriptionContent> GooglePlayValue;

    public:
        FStoreSubscriptionContentModel();
        FStoreSubscriptionContentModel(
            const FStoreSubscriptionContentModel& From
        );
        virtual ~FStoreSubscriptionContentModel() override = default;

        TSharedPtr<FStoreSubscriptionContentModel> WithStoreSubscriptionContentModelId(const TOptional<FString> StoreSubscriptionContentModelId);
        TSharedPtr<FStoreSubscriptionContentModel> WithName(const TOptional<FString> Name);
        TSharedPtr<FStoreSubscriptionContentModel> WithMetadata(const TOptional<FString> Metadata);
        TSharedPtr<FStoreSubscriptionContentModel> WithScheduleNamespaceId(const TOptional<FString> ScheduleNamespaceId);
        TSharedPtr<FStoreSubscriptionContentModel> WithTriggerName(const TOptional<FString> TriggerName);
        TSharedPtr<FStoreSubscriptionContentModel> WithTriggerExtendMode(const TOptional<FString> TriggerExtendMode);
        TSharedPtr<FStoreSubscriptionContentModel> WithRollupHour(const TOptional<int32> RollupHour);
        TSharedPtr<FStoreSubscriptionContentModel> WithReallocateSpanDays(const TOptional<int32> ReallocateSpanDays);
        TSharedPtr<FStoreSubscriptionContentModel> WithAppleAppStore(const TSharedPtr<FAppleAppStoreSubscriptionContent> AppleAppStore);
        TSharedPtr<FStoreSubscriptionContentModel> WithGooglePlay(const TSharedPtr<FGooglePlaySubscriptionContent> GooglePlay);

        TOptional<FString> GetStoreSubscriptionContentModelId() const;
        TOptional<FString> GetName() const;
        TOptional<FString> GetMetadata() const;
        TOptional<FString> GetScheduleNamespaceId() const;
        TOptional<FString> GetTriggerName() const;
        TOptional<FString> GetTriggerExtendMode() const;
        TOptional<int32> GetRollupHour() const;
        FString GetRollupHourString() const;
        TOptional<int32> GetReallocateSpanDays() const;
        FString GetReallocateSpanDaysString() const;
        TSharedPtr<FAppleAppStoreSubscriptionContent> GetAppleAppStore() const;
        TSharedPtr<FGooglePlaySubscriptionContent> GetGooglePlay() const;

        static TOptional<FString> GetRegionFromGrn(const FString Grn);
        static TOptional<FString> GetOwnerIdFromGrn(const FString Grn);
        static TOptional<FString> GetNamespaceNameFromGrn(const FString Grn);
        static TOptional<FString> GetContentNameFromGrn(const FString Grn);

        static TSharedPtr<FStoreSubscriptionContentModel> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;

        static FString TypeName;
    };
    typedef TSharedPtr<FStoreSubscriptionContentModel, ESPMode::ThreadSafe> FStoreSubscriptionContentModelPtr;
}