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
    class FCreateDistributorModelMasterRequest;

    class GS2DISTRIBUTOR_API FCreateDistributorModelMasterRequest final : public TSharedFromThis<FCreateDistributorModelMasterRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> NameValue;
        TOptional<FString> DescriptionValue;
        TOptional<FString> MetadataValue;
        TOptional<FString> InboxNamespaceIdValue;
        TSharedPtr<TArray<FString>> WhiteListTargetIdsValue;
        
    public:
        
        FCreateDistributorModelMasterRequest();
        FCreateDistributorModelMasterRequest(
            const FCreateDistributorModelMasterRequest& From
        );
        ~FCreateDistributorModelMasterRequest() = default;

        TSharedPtr<FCreateDistributorModelMasterRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FCreateDistributorModelMasterRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FCreateDistributorModelMasterRequest> WithName(const TOptional<FString> Name);
        TSharedPtr<FCreateDistributorModelMasterRequest> WithDescription(const TOptional<FString> Description);
        TSharedPtr<FCreateDistributorModelMasterRequest> WithMetadata(const TOptional<FString> Metadata);
        TSharedPtr<FCreateDistributorModelMasterRequest> WithInboxNamespaceId(const TOptional<FString> InboxNamespaceId);
        TSharedPtr<FCreateDistributorModelMasterRequest> WithWhiteListTargetIds(
            const TSharedPtr<TArray<FString>> WhiteListTargetIds);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetName() const;
        TOptional<FString> GetDescription() const;
        TOptional<FString> GetMetadata() const;
        TOptional<FString> GetInboxNamespaceId() const;
        TSharedPtr<TArray<FString>> GetWhiteListTargetIds() const;

        static TSharedPtr<FCreateDistributorModelMasterRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FCreateDistributorModelMasterRequest> FCreateDistributorModelMasterRequestPtr;
}