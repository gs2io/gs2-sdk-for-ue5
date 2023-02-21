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
    class FUpdateAreaModelMasterRequest;

    class GS2MEGAFIELD_API FUpdateAreaModelMasterRequest final : public TSharedFromThis<FUpdateAreaModelMasterRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> AreaModelNameValue;
        TOptional<FString> DescriptionValue;
        TOptional<FString> MetadataValue;
        
    public:
        
        FUpdateAreaModelMasterRequest();
        FUpdateAreaModelMasterRequest(
            const FUpdateAreaModelMasterRequest& From
        );
        ~FUpdateAreaModelMasterRequest() = default;

        TSharedPtr<FUpdateAreaModelMasterRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FUpdateAreaModelMasterRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FUpdateAreaModelMasterRequest> WithAreaModelName(const TOptional<FString> AreaModelName);
        TSharedPtr<FUpdateAreaModelMasterRequest> WithDescription(const TOptional<FString> Description);
        TSharedPtr<FUpdateAreaModelMasterRequest> WithMetadata(const TOptional<FString> Metadata);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetAreaModelName() const;
        TOptional<FString> GetDescription() const;
        TOptional<FString> GetMetadata() const;

        static TSharedPtr<FUpdateAreaModelMasterRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FUpdateAreaModelMasterRequest, ESPMode::ThreadSafe> FUpdateAreaModelMasterRequestPtr;
}