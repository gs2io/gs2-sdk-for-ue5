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

namespace Gs2::Enchant::Request
{
    class FGetRarityParameterModelRequest;

    class GS2ENCHANT_API FGetRarityParameterModelRequest final : public TSharedFromThis<FGetRarityParameterModelRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> ParameterNameValue;
        
    public:
        
        FGetRarityParameterModelRequest();
        FGetRarityParameterModelRequest(
            const FGetRarityParameterModelRequest& From
        );
        ~FGetRarityParameterModelRequest() = default;

        TSharedPtr<FGetRarityParameterModelRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FGetRarityParameterModelRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FGetRarityParameterModelRequest> WithParameterName(const TOptional<FString> ParameterName);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetParameterName() const;

        static TSharedPtr<FGetRarityParameterModelRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FGetRarityParameterModelRequest, ESPMode::ThreadSafe> FGetRarityParameterModelRequestPtr;
}