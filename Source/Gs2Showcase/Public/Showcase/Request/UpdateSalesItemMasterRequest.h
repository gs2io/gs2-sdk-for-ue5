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
#include "../Model/ConsumeAction.h"
#include "../Model/AcquireAction.h"

namespace Gs2::Showcase::Request
{
    class FUpdateSalesItemMasterRequest;

    class GS2SHOWCASE_API FUpdateSalesItemMasterRequest final : public TSharedFromThis<FUpdateSalesItemMasterRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> SalesItemNameValue;
        TOptional<FString> DescriptionValue;
        TOptional<FString> MetadataValue;
        TSharedPtr<TArray<TSharedPtr<Model::FConsumeAction>>> ConsumeActionsValue;
        TSharedPtr<TArray<TSharedPtr<Model::FAcquireAction>>> AcquireActionsValue;
        
    public:
        
        FUpdateSalesItemMasterRequest();
        FUpdateSalesItemMasterRequest(
            const FUpdateSalesItemMasterRequest& From
        );
        ~FUpdateSalesItemMasterRequest() = default;

        TSharedPtr<FUpdateSalesItemMasterRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FUpdateSalesItemMasterRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FUpdateSalesItemMasterRequest> WithSalesItemName(const TOptional<FString> SalesItemName);
        TSharedPtr<FUpdateSalesItemMasterRequest> WithDescription(const TOptional<FString> Description);
        TSharedPtr<FUpdateSalesItemMasterRequest> WithMetadata(const TOptional<FString> Metadata);
        TSharedPtr<FUpdateSalesItemMasterRequest> WithConsumeActions(const TSharedPtr<TArray<TSharedPtr<Model::FConsumeAction>>> ConsumeActions);
        TSharedPtr<FUpdateSalesItemMasterRequest> WithAcquireActions(const TSharedPtr<TArray<TSharedPtr<Model::FAcquireAction>>> AcquireActions);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetSalesItemName() const;
        TOptional<FString> GetDescription() const;
        TOptional<FString> GetMetadata() const;TSharedPtr<TArray<TSharedPtr<Model::FConsumeAction>>> GetConsumeActions() const;TSharedPtr<TArray<TSharedPtr<Model::FAcquireAction>>> GetAcquireActions() const;

        static TSharedPtr<FUpdateSalesItemMasterRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FUpdateSalesItemMasterRequest, ESPMode::ThreadSafe> FUpdateSalesItemMasterRequestPtr;
}