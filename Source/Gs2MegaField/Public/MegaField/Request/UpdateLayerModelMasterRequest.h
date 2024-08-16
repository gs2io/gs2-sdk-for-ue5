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

namespace Gs2::MegaField::Request
{
    class FUpdateLayerModelMasterRequest;

    class GS2MEGAFIELD_API FUpdateLayerModelMasterRequest final : public TSharedFromThis<FUpdateLayerModelMasterRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> AreaModelNameValue;
        TOptional<FString> LayerModelNameValue;
        TOptional<FString> DescriptionValue;
        TOptional<FString> MetadataValue;
        
    public:
        
        FUpdateLayerModelMasterRequest();
        FUpdateLayerModelMasterRequest(
            const FUpdateLayerModelMasterRequest& From
        );
        ~FUpdateLayerModelMasterRequest() = default;

        TSharedPtr<FUpdateLayerModelMasterRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FUpdateLayerModelMasterRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FUpdateLayerModelMasterRequest> WithAreaModelName(const TOptional<FString> AreaModelName);
        TSharedPtr<FUpdateLayerModelMasterRequest> WithLayerModelName(const TOptional<FString> LayerModelName);
        TSharedPtr<FUpdateLayerModelMasterRequest> WithDescription(const TOptional<FString> Description);
        TSharedPtr<FUpdateLayerModelMasterRequest> WithMetadata(const TOptional<FString> Metadata);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetAreaModelName() const;
        TOptional<FString> GetLayerModelName() const;
        TOptional<FString> GetDescription() const;
        TOptional<FString> GetMetadata() const;

        static TSharedPtr<FUpdateLayerModelMasterRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FUpdateLayerModelMasterRequest> FUpdateLayerModelMasterRequestPtr;
}