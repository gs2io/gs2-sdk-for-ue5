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

namespace Gs2::Formation::Request
{
    class FGetPropertyFormModelRequest;

    class GS2FORMATION_API FGetPropertyFormModelRequest final : public TSharedFromThis<FGetPropertyFormModelRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> PropertyFormModelNameValue;
        
    public:
        
        FGetPropertyFormModelRequest();
        FGetPropertyFormModelRequest(
            const FGetPropertyFormModelRequest& From
        );
        ~FGetPropertyFormModelRequest() = default;

        TSharedPtr<FGetPropertyFormModelRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FGetPropertyFormModelRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FGetPropertyFormModelRequest> WithPropertyFormModelName(const TOptional<FString> PropertyFormModelName);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetPropertyFormModelName() const;

        static TSharedPtr<FGetPropertyFormModelRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FGetPropertyFormModelRequest> FGetPropertyFormModelRequestPtr;
}