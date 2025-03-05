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
#include "../Model/AppleAppStoreSubscriptionContent.h"
#include "../Model/GooglePlaySubscriptionContent.h"

namespace Gs2::Money2::Request
{
    class FUpdateStoreSubscriptionContentModelMasterRequest;

    class GS2MONEY2_API FUpdateStoreSubscriptionContentModelMasterRequest final : public TSharedFromThis<FUpdateStoreSubscriptionContentModelMasterRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> ContentNameValue;
        TOptional<FString> DescriptionValue;
        TOptional<FString> MetadataValue;
        TOptional<FString> ScheduleNamespaceIdValue;
        TOptional<FString> TriggerNameValue;
        TOptional<FString> TriggerExtendModeValue;
        TOptional<int32> RollupHourValue;
        TOptional<int32> ReallocateSpanDaysValue;
        TSharedPtr<Model::FAppleAppStoreSubscriptionContent> AppleAppStoreValue;
        TSharedPtr<Model::FGooglePlaySubscriptionContent> GooglePlayValue;
        
    public:
        
        FUpdateStoreSubscriptionContentModelMasterRequest();
        FUpdateStoreSubscriptionContentModelMasterRequest(
            const FUpdateStoreSubscriptionContentModelMasterRequest& From
        );
        ~FUpdateStoreSubscriptionContentModelMasterRequest() = default;

        TSharedPtr<FUpdateStoreSubscriptionContentModelMasterRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FUpdateStoreSubscriptionContentModelMasterRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FUpdateStoreSubscriptionContentModelMasterRequest> WithContentName(const TOptional<FString> ContentName);
        TSharedPtr<FUpdateStoreSubscriptionContentModelMasterRequest> WithDescription(const TOptional<FString> Description);
        TSharedPtr<FUpdateStoreSubscriptionContentModelMasterRequest> WithMetadata(const TOptional<FString> Metadata);
        TSharedPtr<FUpdateStoreSubscriptionContentModelMasterRequest> WithScheduleNamespaceId(const TOptional<FString> ScheduleNamespaceId);
        TSharedPtr<FUpdateStoreSubscriptionContentModelMasterRequest> WithTriggerName(const TOptional<FString> TriggerName);
        TSharedPtr<FUpdateStoreSubscriptionContentModelMasterRequest> WithTriggerExtendMode(const TOptional<FString> TriggerExtendMode);
        TSharedPtr<FUpdateStoreSubscriptionContentModelMasterRequest> WithRollupHour(const TOptional<int32> RollupHour);
        TSharedPtr<FUpdateStoreSubscriptionContentModelMasterRequest> WithReallocateSpanDays(const TOptional<int32> ReallocateSpanDays);
        TSharedPtr<FUpdateStoreSubscriptionContentModelMasterRequest> WithAppleAppStore(const TSharedPtr<Model::FAppleAppStoreSubscriptionContent> AppleAppStore);
        TSharedPtr<FUpdateStoreSubscriptionContentModelMasterRequest> WithGooglePlay(const TSharedPtr<Model::FGooglePlaySubscriptionContent> GooglePlay);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetContentName() const;
        TOptional<FString> GetDescription() const;
        TOptional<FString> GetMetadata() const;
        TOptional<FString> GetScheduleNamespaceId() const;
        TOptional<FString> GetTriggerName() const;
        TOptional<FString> GetTriggerExtendMode() const;
        TOptional<int32> GetRollupHour() const;
        FString GetRollupHourString() const;
        TOptional<int32> GetReallocateSpanDays() const;
        FString GetReallocateSpanDaysString() const;
        TSharedPtr<Model::FAppleAppStoreSubscriptionContent> GetAppleAppStore() const;
        TSharedPtr<Model::FGooglePlaySubscriptionContent> GetGooglePlay() const;

        static TSharedPtr<FUpdateStoreSubscriptionContentModelMasterRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FUpdateStoreSubscriptionContentModelMasterRequest> FUpdateStoreSubscriptionContentModelMasterRequestPtr;
}