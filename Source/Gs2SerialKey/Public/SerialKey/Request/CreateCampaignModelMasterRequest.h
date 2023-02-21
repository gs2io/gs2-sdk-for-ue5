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

namespace Gs2::SerialKey::Request
{
    class FCreateCampaignModelMasterRequest;

    class GS2SERIALKEY_API FCreateCampaignModelMasterRequest final : public TSharedFromThis<FCreateCampaignModelMasterRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> NameValue;
        TOptional<FString> DescriptionValue;
        TOptional<FString> MetadataValue;
        TOptional<bool> EnableCampaignCodeValue;
        
    public:
        
        FCreateCampaignModelMasterRequest();
        FCreateCampaignModelMasterRequest(
            const FCreateCampaignModelMasterRequest& From
        );
        ~FCreateCampaignModelMasterRequest() = default;

        TSharedPtr<FCreateCampaignModelMasterRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FCreateCampaignModelMasterRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FCreateCampaignModelMasterRequest> WithName(const TOptional<FString> Name);
        TSharedPtr<FCreateCampaignModelMasterRequest> WithDescription(const TOptional<FString> Description);
        TSharedPtr<FCreateCampaignModelMasterRequest> WithMetadata(const TOptional<FString> Metadata);
        TSharedPtr<FCreateCampaignModelMasterRequest> WithEnableCampaignCode(const TOptional<bool> EnableCampaignCode);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetName() const;
        TOptional<FString> GetDescription() const;
        TOptional<FString> GetMetadata() const;
        TOptional<bool> GetEnableCampaignCode() const;
        FString GetEnableCampaignCodeString() const;

        static TSharedPtr<FCreateCampaignModelMasterRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FCreateCampaignModelMasterRequest, ESPMode::ThreadSafe> FCreateCampaignModelMasterRequestPtr;
}