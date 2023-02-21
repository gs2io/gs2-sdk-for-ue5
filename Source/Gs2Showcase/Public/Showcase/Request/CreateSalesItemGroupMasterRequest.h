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

namespace Gs2::Showcase::Request
{
    class FCreateSalesItemGroupMasterRequest;

    class GS2SHOWCASE_API FCreateSalesItemGroupMasterRequest final : public TSharedFromThis<FCreateSalesItemGroupMasterRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> NameValue;
        TOptional<FString> DescriptionValue;
        TOptional<FString> MetadataValue;
        TSharedPtr<TArray<FString>> SalesItemNamesValue;
        
    public:
        
        FCreateSalesItemGroupMasterRequest();
        FCreateSalesItemGroupMasterRequest(
            const FCreateSalesItemGroupMasterRequest& From
        );
        ~FCreateSalesItemGroupMasterRequest() = default;

        TSharedPtr<FCreateSalesItemGroupMasterRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FCreateSalesItemGroupMasterRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FCreateSalesItemGroupMasterRequest> WithName(const TOptional<FString> Name);
        TSharedPtr<FCreateSalesItemGroupMasterRequest> WithDescription(const TOptional<FString> Description);
        TSharedPtr<FCreateSalesItemGroupMasterRequest> WithMetadata(const TOptional<FString> Metadata);
        TSharedPtr<FCreateSalesItemGroupMasterRequest> WithSalesItemNames(
            const TSharedPtr<TArray<FString>> SalesItemNames);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetName() const;
        TOptional<FString> GetDescription() const;
        TOptional<FString> GetMetadata() const;
        TSharedPtr<TArray<FString>> GetSalesItemNames() const;

        static TSharedPtr<FCreateSalesItemGroupMasterRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FCreateSalesItemGroupMasterRequest, ESPMode::ThreadSafe> FCreateSalesItemGroupMasterRequestPtr;
}