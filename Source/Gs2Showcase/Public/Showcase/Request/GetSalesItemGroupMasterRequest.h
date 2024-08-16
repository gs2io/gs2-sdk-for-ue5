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
    class FGetSalesItemGroupMasterRequest;

    class GS2SHOWCASE_API FGetSalesItemGroupMasterRequest final : public TSharedFromThis<FGetSalesItemGroupMasterRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> SalesItemGroupNameValue;
        
    public:
        
        FGetSalesItemGroupMasterRequest();
        FGetSalesItemGroupMasterRequest(
            const FGetSalesItemGroupMasterRequest& From
        );
        ~FGetSalesItemGroupMasterRequest() = default;

        TSharedPtr<FGetSalesItemGroupMasterRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FGetSalesItemGroupMasterRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FGetSalesItemGroupMasterRequest> WithSalesItemGroupName(const TOptional<FString> SalesItemGroupName);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetSalesItemGroupName() const;

        static TSharedPtr<FGetSalesItemGroupMasterRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FGetSalesItemGroupMasterRequest> FGetSalesItemGroupMasterRequestPtr;
}