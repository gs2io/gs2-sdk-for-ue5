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

namespace Gs2::Enchant::Request
{
    class FGetRarityParameterModelMasterRequest;

    class GS2ENCHANT_API FGetRarityParameterModelMasterRequest final : public TSharedFromThis<FGetRarityParameterModelMasterRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> ParameterNameValue;
        
    public:
        
        FGetRarityParameterModelMasterRequest();
        FGetRarityParameterModelMasterRequest(
            const FGetRarityParameterModelMasterRequest& From
        );
        ~FGetRarityParameterModelMasterRequest() = default;

        TSharedPtr<FGetRarityParameterModelMasterRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FGetRarityParameterModelMasterRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FGetRarityParameterModelMasterRequest> WithParameterName(const TOptional<FString> ParameterName);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetParameterName() const;

        static TSharedPtr<FGetRarityParameterModelMasterRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FGetRarityParameterModelMasterRequest> FGetRarityParameterModelMasterRequestPtr;
}