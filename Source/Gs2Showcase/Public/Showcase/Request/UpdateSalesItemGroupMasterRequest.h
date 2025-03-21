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

namespace Gs2::Showcase::Request
{
    class FUpdateSalesItemGroupMasterRequest;

    class GS2SHOWCASE_API FUpdateSalesItemGroupMasterRequest final : public TSharedFromThis<FUpdateSalesItemGroupMasterRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> SalesItemGroupNameValue;
        TOptional<FString> DescriptionValue;
        TOptional<FString> MetadataValue;
        TSharedPtr<TArray<FString>> SalesItemNamesValue;
        
    public:
        
        FUpdateSalesItemGroupMasterRequest();
        FUpdateSalesItemGroupMasterRequest(
            const FUpdateSalesItemGroupMasterRequest& From
        );
        ~FUpdateSalesItemGroupMasterRequest() = default;

        TSharedPtr<FUpdateSalesItemGroupMasterRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FUpdateSalesItemGroupMasterRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FUpdateSalesItemGroupMasterRequest> WithSalesItemGroupName(const TOptional<FString> SalesItemGroupName);
        TSharedPtr<FUpdateSalesItemGroupMasterRequest> WithDescription(const TOptional<FString> Description);
        TSharedPtr<FUpdateSalesItemGroupMasterRequest> WithMetadata(const TOptional<FString> Metadata);
        TSharedPtr<FUpdateSalesItemGroupMasterRequest> WithSalesItemNames(
            const TSharedPtr<TArray<FString>> SalesItemNames);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetSalesItemGroupName() const;
        TOptional<FString> GetDescription() const;
        TOptional<FString> GetMetadata() const;
        TSharedPtr<TArray<FString>> GetSalesItemNames() const;

        static TSharedPtr<FUpdateSalesItemGroupMasterRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FUpdateSalesItemGroupMasterRequest> FUpdateSalesItemGroupMasterRequestPtr;
}