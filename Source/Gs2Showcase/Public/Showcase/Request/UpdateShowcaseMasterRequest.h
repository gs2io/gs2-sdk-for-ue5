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
#include "../Model/DisplayItemMaster.h"

namespace Gs2::Showcase::Request
{
    class FUpdateShowcaseMasterRequest;

    class GS2SHOWCASE_API FUpdateShowcaseMasterRequest final : public TSharedFromThis<FUpdateShowcaseMasterRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> ShowcaseNameValue;
        TOptional<FString> DescriptionValue;
        TOptional<FString> MetadataValue;
        TSharedPtr<TArray<TSharedPtr<Model::FDisplayItemMaster>>> DisplayItemsValue;
        TOptional<FString> SalesPeriodEventIdValue;
        
    public:
        
        FUpdateShowcaseMasterRequest();
        FUpdateShowcaseMasterRequest(
            const FUpdateShowcaseMasterRequest& From
        );
        ~FUpdateShowcaseMasterRequest() = default;

        TSharedPtr<FUpdateShowcaseMasterRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FUpdateShowcaseMasterRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FUpdateShowcaseMasterRequest> WithShowcaseName(const TOptional<FString> ShowcaseName);
        TSharedPtr<FUpdateShowcaseMasterRequest> WithDescription(const TOptional<FString> Description);
        TSharedPtr<FUpdateShowcaseMasterRequest> WithMetadata(const TOptional<FString> Metadata);
        TSharedPtr<FUpdateShowcaseMasterRequest> WithDisplayItems(const TSharedPtr<TArray<TSharedPtr<Model::FDisplayItemMaster>>> DisplayItems);
        TSharedPtr<FUpdateShowcaseMasterRequest> WithSalesPeriodEventId(const TOptional<FString> SalesPeriodEventId);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetShowcaseName() const;
        TOptional<FString> GetDescription() const;
        TOptional<FString> GetMetadata() const;TSharedPtr<TArray<TSharedPtr<Model::FDisplayItemMaster>>> GetDisplayItems() const;
        TOptional<FString> GetSalesPeriodEventId() const;

        static TSharedPtr<FUpdateShowcaseMasterRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FUpdateShowcaseMasterRequest, ESPMode::ThreadSafe> FUpdateShowcaseMasterRequestPtr;
}