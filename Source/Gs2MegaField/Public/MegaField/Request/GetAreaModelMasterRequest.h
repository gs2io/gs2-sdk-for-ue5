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
    class FGetAreaModelMasterRequest;

    class GS2MEGAFIELD_API FGetAreaModelMasterRequest final : public TSharedFromThis<FGetAreaModelMasterRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> AreaModelNameValue;
        
    public:
        
        FGetAreaModelMasterRequest();
        FGetAreaModelMasterRequest(
            const FGetAreaModelMasterRequest& From
        );
        ~FGetAreaModelMasterRequest() = default;

        TSharedPtr<FGetAreaModelMasterRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FGetAreaModelMasterRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FGetAreaModelMasterRequest> WithAreaModelName(const TOptional<FString> AreaModelName);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetAreaModelName() const;

        static TSharedPtr<FGetAreaModelMasterRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FGetAreaModelMasterRequest, ESPMode::ThreadSafe> FGetAreaModelMasterRequestPtr;
}