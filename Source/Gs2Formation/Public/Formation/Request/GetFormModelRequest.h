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

namespace Gs2::Formation::Request
{
    class FGetFormModelRequest;

    class GS2FORMATION_API FGetFormModelRequest final : public TSharedFromThis<FGetFormModelRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> FormModelNameValue;
        
    public:
        
        FGetFormModelRequest();
        FGetFormModelRequest(
            const FGetFormModelRequest& From
        );
        ~FGetFormModelRequest() = default;

        TSharedPtr<FGetFormModelRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FGetFormModelRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FGetFormModelRequest> WithFormModelName(const TOptional<FString> FormModelName);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetFormModelName() const;

        static TSharedPtr<FGetFormModelRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FGetFormModelRequest, ESPMode::ThreadSafe> FGetFormModelRequestPtr;
}