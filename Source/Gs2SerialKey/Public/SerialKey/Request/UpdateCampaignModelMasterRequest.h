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

namespace Gs2::SerialKey::Request
{
    class FUpdateCampaignModelMasterRequest;

    class GS2SERIALKEY_API FUpdateCampaignModelMasterRequest final : public TSharedFromThis<FUpdateCampaignModelMasterRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> CampaignModelNameValue;
        TOptional<FString> DescriptionValue;
        TOptional<FString> MetadataValue;
        TOptional<bool> EnableCampaignCodeValue;
        
    public:
        
        FUpdateCampaignModelMasterRequest();
        FUpdateCampaignModelMasterRequest(
            const FUpdateCampaignModelMasterRequest& From
        );
        ~FUpdateCampaignModelMasterRequest() = default;

        TSharedPtr<FUpdateCampaignModelMasterRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FUpdateCampaignModelMasterRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FUpdateCampaignModelMasterRequest> WithCampaignModelName(const TOptional<FString> CampaignModelName);
        TSharedPtr<FUpdateCampaignModelMasterRequest> WithDescription(const TOptional<FString> Description);
        TSharedPtr<FUpdateCampaignModelMasterRequest> WithMetadata(const TOptional<FString> Metadata);
        TSharedPtr<FUpdateCampaignModelMasterRequest> WithEnableCampaignCode(const TOptional<bool> EnableCampaignCode);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetCampaignModelName() const;
        TOptional<FString> GetDescription() const;
        TOptional<FString> GetMetadata() const;
        TOptional<bool> GetEnableCampaignCode() const;
        FString GetEnableCampaignCodeString() const;

        static TSharedPtr<FUpdateCampaignModelMasterRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FUpdateCampaignModelMasterRequest> FUpdateCampaignModelMasterRequestPtr;
}