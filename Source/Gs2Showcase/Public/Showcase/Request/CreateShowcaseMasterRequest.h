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
#include "../Model/DisplayItemMaster.h"

namespace Gs2::Showcase::Request
{
    class FCreateShowcaseMasterRequest;

    class GS2SHOWCASE_API FCreateShowcaseMasterRequest final : public TSharedFromThis<FCreateShowcaseMasterRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> NameValue;
        TOptional<FString> DescriptionValue;
        TOptional<FString> MetadataValue;
        TSharedPtr<TArray<TSharedPtr<Model::FDisplayItemMaster>>> DisplayItemsValue;
        TOptional<FString> SalesPeriodEventIdValue;
        
    public:
        
        FCreateShowcaseMasterRequest();
        FCreateShowcaseMasterRequest(
            const FCreateShowcaseMasterRequest& From
        );
        ~FCreateShowcaseMasterRequest() = default;

        TSharedPtr<FCreateShowcaseMasterRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FCreateShowcaseMasterRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FCreateShowcaseMasterRequest> WithName(const TOptional<FString> Name);
        TSharedPtr<FCreateShowcaseMasterRequest> WithDescription(const TOptional<FString> Description);
        TSharedPtr<FCreateShowcaseMasterRequest> WithMetadata(const TOptional<FString> Metadata);
        TSharedPtr<FCreateShowcaseMasterRequest> WithDisplayItems(const TSharedPtr<TArray<TSharedPtr<Model::FDisplayItemMaster>>> DisplayItems);
        TSharedPtr<FCreateShowcaseMasterRequest> WithSalesPeriodEventId(const TOptional<FString> SalesPeriodEventId);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetName() const;
        TOptional<FString> GetDescription() const;
        TOptional<FString> GetMetadata() const;TSharedPtr<TArray<TSharedPtr<Model::FDisplayItemMaster>>> GetDisplayItems() const;
        TOptional<FString> GetSalesPeriodEventId() const;

        static TSharedPtr<FCreateShowcaseMasterRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FCreateShowcaseMasterRequest> FCreateShowcaseMasterRequestPtr;
}