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
#include "../Model/VerifyAction.h"
#include "../Model/ConsumeAction.h"
#include "../Model/AcquireAction.h"

namespace Gs2::Showcase::Request
{
    class FCreateSalesItemMasterRequest;

    class GS2SHOWCASE_API FCreateSalesItemMasterRequest final : public TSharedFromThis<FCreateSalesItemMasterRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> NameValue;
        TOptional<FString> DescriptionValue;
        TOptional<FString> MetadataValue;
        TSharedPtr<TArray<TSharedPtr<Model::FVerifyAction>>> VerifyActionsValue;
        TSharedPtr<TArray<TSharedPtr<Model::FConsumeAction>>> ConsumeActionsValue;
        TSharedPtr<TArray<TSharedPtr<Model::FAcquireAction>>> AcquireActionsValue;
        
    public:
        
        FCreateSalesItemMasterRequest();
        FCreateSalesItemMasterRequest(
            const FCreateSalesItemMasterRequest& From
        );
        ~FCreateSalesItemMasterRequest() = default;

        TSharedPtr<FCreateSalesItemMasterRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FCreateSalesItemMasterRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FCreateSalesItemMasterRequest> WithName(const TOptional<FString> Name);
        TSharedPtr<FCreateSalesItemMasterRequest> WithDescription(const TOptional<FString> Description);
        TSharedPtr<FCreateSalesItemMasterRequest> WithMetadata(const TOptional<FString> Metadata);
        TSharedPtr<FCreateSalesItemMasterRequest> WithVerifyActions(const TSharedPtr<TArray<TSharedPtr<Model::FVerifyAction>>> VerifyActions);
        TSharedPtr<FCreateSalesItemMasterRequest> WithConsumeActions(const TSharedPtr<TArray<TSharedPtr<Model::FConsumeAction>>> ConsumeActions);
        TSharedPtr<FCreateSalesItemMasterRequest> WithAcquireActions(const TSharedPtr<TArray<TSharedPtr<Model::FAcquireAction>>> AcquireActions);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetName() const;
        TOptional<FString> GetDescription() const;
        TOptional<FString> GetMetadata() const;TSharedPtr<TArray<TSharedPtr<Model::FVerifyAction>>> GetVerifyActions() const;TSharedPtr<TArray<TSharedPtr<Model::FConsumeAction>>> GetConsumeActions() const;TSharedPtr<TArray<TSharedPtr<Model::FAcquireAction>>> GetAcquireActions() const;

        static TSharedPtr<FCreateSalesItemMasterRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FCreateSalesItemMasterRequest> FCreateSalesItemMasterRequestPtr;
}