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

namespace Gs2::Key::Request
{
    class FCreateKeyRequest;

    class GS2KEY_API FCreateKeyRequest final : public TSharedFromThis<FCreateKeyRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> NameValue;
        TOptional<FString> DescriptionValue;
        
    public:
        
        FCreateKeyRequest();
        FCreateKeyRequest(
            const FCreateKeyRequest& From
        );
        ~FCreateKeyRequest() = default;

        TSharedPtr<FCreateKeyRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FCreateKeyRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FCreateKeyRequest> WithName(const TOptional<FString> Name);
        TSharedPtr<FCreateKeyRequest> WithDescription(const TOptional<FString> Description);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetName() const;
        TOptional<FString> GetDescription() const;

        static TSharedPtr<FCreateKeyRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FCreateKeyRequest> FCreateKeyRequestPtr;
}