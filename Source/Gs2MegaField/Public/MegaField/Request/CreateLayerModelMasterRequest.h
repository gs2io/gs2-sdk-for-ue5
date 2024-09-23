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
    class FCreateLayerModelMasterRequest;

    class GS2MEGAFIELD_API FCreateLayerModelMasterRequest final : public TSharedFromThis<FCreateLayerModelMasterRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> AreaModelNameValue;
        TOptional<FString> NameValue;
        TOptional<FString> DescriptionValue;
        TOptional<FString> MetadataValue;
        
    public:
        
        FCreateLayerModelMasterRequest();
        FCreateLayerModelMasterRequest(
            const FCreateLayerModelMasterRequest& From
        );
        ~FCreateLayerModelMasterRequest() = default;

        TSharedPtr<FCreateLayerModelMasterRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FCreateLayerModelMasterRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FCreateLayerModelMasterRequest> WithAreaModelName(const TOptional<FString> AreaModelName);
        TSharedPtr<FCreateLayerModelMasterRequest> WithName(const TOptional<FString> Name);
        TSharedPtr<FCreateLayerModelMasterRequest> WithDescription(const TOptional<FString> Description);
        TSharedPtr<FCreateLayerModelMasterRequest> WithMetadata(const TOptional<FString> Metadata);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetAreaModelName() const;
        TOptional<FString> GetName() const;
        TOptional<FString> GetDescription() const;
        TOptional<FString> GetMetadata() const;

        static TSharedPtr<FCreateLayerModelMasterRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FCreateLayerModelMasterRequest, ESPMode::ThreadSafe> FCreateLayerModelMasterRequestPtr;
}