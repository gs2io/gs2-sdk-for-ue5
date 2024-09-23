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

namespace Gs2::MegaField::Request
{
    class FGetLayerModelMasterRequest;

    class GS2MEGAFIELD_API FGetLayerModelMasterRequest final : public TSharedFromThis<FGetLayerModelMasterRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> AreaModelNameValue;
        TOptional<FString> LayerModelNameValue;
        
    public:
        
        FGetLayerModelMasterRequest();
        FGetLayerModelMasterRequest(
            const FGetLayerModelMasterRequest& From
        );
        ~FGetLayerModelMasterRequest() = default;

        TSharedPtr<FGetLayerModelMasterRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FGetLayerModelMasterRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FGetLayerModelMasterRequest> WithAreaModelName(const TOptional<FString> AreaModelName);
        TSharedPtr<FGetLayerModelMasterRequest> WithLayerModelName(const TOptional<FString> LayerModelName);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetAreaModelName() const;
        TOptional<FString> GetLayerModelName() const;

        static TSharedPtr<FGetLayerModelMasterRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FGetLayerModelMasterRequest, ESPMode::ThreadSafe> FGetLayerModelMasterRequestPtr;
}