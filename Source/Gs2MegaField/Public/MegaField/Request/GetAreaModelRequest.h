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
    class FGetAreaModelRequest;

    class GS2MEGAFIELD_API FGetAreaModelRequest final : public TSharedFromThis<FGetAreaModelRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> AreaModelNameValue;
        
    public:
        
        FGetAreaModelRequest();
        FGetAreaModelRequest(
            const FGetAreaModelRequest& From
        );
        ~FGetAreaModelRequest() = default;

        TSharedPtr<FGetAreaModelRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FGetAreaModelRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FGetAreaModelRequest> WithAreaModelName(const TOptional<FString> AreaModelName);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetAreaModelName() const;

        static TSharedPtr<FGetAreaModelRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FGetAreaModelRequest> FGetAreaModelRequestPtr;
}