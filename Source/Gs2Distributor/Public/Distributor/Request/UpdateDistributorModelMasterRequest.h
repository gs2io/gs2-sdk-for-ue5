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

namespace Gs2::Distributor::Request
{
    class FUpdateDistributorModelMasterRequest;

    class GS2DISTRIBUTOR_API FUpdateDistributorModelMasterRequest final : public TSharedFromThis<FUpdateDistributorModelMasterRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> DistributorNameValue;
        TOptional<FString> DescriptionValue;
        TOptional<FString> MetadataValue;
        TOptional<FString> InboxNamespaceIdValue;
        TSharedPtr<TArray<FString>> WhiteListTargetIdsValue;
        
    public:
        
        FUpdateDistributorModelMasterRequest();
        FUpdateDistributorModelMasterRequest(
            const FUpdateDistributorModelMasterRequest& From
        );
        ~FUpdateDistributorModelMasterRequest() = default;

        TSharedPtr<FUpdateDistributorModelMasterRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FUpdateDistributorModelMasterRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FUpdateDistributorModelMasterRequest> WithDistributorName(const TOptional<FString> DistributorName);
        TSharedPtr<FUpdateDistributorModelMasterRequest> WithDescription(const TOptional<FString> Description);
        TSharedPtr<FUpdateDistributorModelMasterRequest> WithMetadata(const TOptional<FString> Metadata);
        TSharedPtr<FUpdateDistributorModelMasterRequest> WithInboxNamespaceId(const TOptional<FString> InboxNamespaceId);
        TSharedPtr<FUpdateDistributorModelMasterRequest> WithWhiteListTargetIds(
            const TSharedPtr<TArray<FString>> WhiteListTargetIds);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetDistributorName() const;
        TOptional<FString> GetDescription() const;
        TOptional<FString> GetMetadata() const;
        TOptional<FString> GetInboxNamespaceId() const;
        TSharedPtr<TArray<FString>> GetWhiteListTargetIds() const;

        static TSharedPtr<FUpdateDistributorModelMasterRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FUpdateDistributorModelMasterRequest> FUpdateDistributorModelMasterRequestPtr;
}