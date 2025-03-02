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
    class FCreateStoreSubscriptionContentModelMasterRequest;

    class GS2MONEY2_API FCreateStoreSubscriptionContentModelMasterRequest final : public TSharedFromThis<FCreateStoreSubscriptionContentModelMasterRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> NameValue;
        TOptional<FString> DescriptionValue;
        TOptional<FString> MetadataValue;
        TOptional<FString> ScheduleNamespaceIdValue;
        TOptional<FString> TriggerNameValue;
        TSharedPtr<Model::FAppleAppStoreSubscriptionContent> AppleAppStoreValue;
        TSharedPtr<Model::FGooglePlaySubscriptionContent> GooglePlayValue;
        
    public:
        
        FCreateStoreSubscriptionContentModelMasterRequest();
        FCreateStoreSubscriptionContentModelMasterRequest(
            const FCreateStoreSubscriptionContentModelMasterRequest& From
        );
        ~FCreateStoreSubscriptionContentModelMasterRequest() = default;

        TSharedPtr<FCreateStoreSubscriptionContentModelMasterRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FCreateStoreSubscriptionContentModelMasterRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FCreateStoreSubscriptionContentModelMasterRequest> WithName(const TOptional<FString> Name);
        TSharedPtr<FCreateStoreSubscriptionContentModelMasterRequest> WithDescription(const TOptional<FString> Description);
        TSharedPtr<FCreateStoreSubscriptionContentModelMasterRequest> WithMetadata(const TOptional<FString> Metadata);
        TSharedPtr<FCreateStoreSubscriptionContentModelMasterRequest> WithScheduleNamespaceId(const TOptional<FString> ScheduleNamespaceId);
        TSharedPtr<FCreateStoreSubscriptionContentModelMasterRequest> WithTriggerName(const TOptional<FString> TriggerName);
        TSharedPtr<FCreateStoreSubscriptionContentModelMasterRequest> WithAppleAppStore(const TSharedPtr<Model::FAppleAppStoreSubscriptionContent> AppleAppStore);
        TSharedPtr<FCreateStoreSubscriptionContentModelMasterRequest> WithGooglePlay(const TSharedPtr<Model::FGooglePlaySubscriptionContent> GooglePlay);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetName() const;
        TOptional<FString> GetDescription() const;
        TOptional<FString> GetMetadata() const;
        TOptional<FString> GetScheduleNamespaceId() const;
        TOptional<FString> GetTriggerName() const;
        TSharedPtr<Model::FAppleAppStoreSubscriptionContent> GetAppleAppStore() const;
        TSharedPtr<Model::FGooglePlaySubscriptionContent> GetGooglePlay() const;

        static TSharedPtr<FCreateStoreSubscriptionContentModelMasterRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FCreateStoreSubscriptionContentModelMasterRequest> FCreateStoreSubscriptionContentModelMasterRequestPtr;
}