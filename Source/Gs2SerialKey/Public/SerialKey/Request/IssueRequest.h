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
    class FIssueRequest;

    class GS2SERIALKEY_API FIssueRequest final : public TSharedFromThis<FIssueRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> CampaignModelNameValue;
        TOptional<FString> MetadataValue;
        TOptional<int32> IssueRequestCountValue;
        
    public:
        
        FIssueRequest();
        FIssueRequest(
            const FIssueRequest& From
        );
        ~FIssueRequest() = default;

        TSharedPtr<FIssueRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FIssueRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FIssueRequest> WithCampaignModelName(const TOptional<FString> CampaignModelName);
        TSharedPtr<FIssueRequest> WithMetadata(const TOptional<FString> Metadata);
        TSharedPtr<FIssueRequest> WithIssueRequestCount(const TOptional<int32> IssueRequestCount);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetCampaignModelName() const;
        TOptional<FString> GetMetadata() const;
        TOptional<int32> GetIssueRequestCount() const;
        FString GetIssueRequestCountString() const;

        static TSharedPtr<FIssueRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FIssueRequest, ESPMode::ThreadSafe> FIssueRequestPtr;
}