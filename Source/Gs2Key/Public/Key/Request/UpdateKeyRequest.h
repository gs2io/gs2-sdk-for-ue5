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
    class FUpdateKeyRequest;

    class GS2KEY_API FUpdateKeyRequest final : public TSharedFromThis<FUpdateKeyRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> KeyNameValue;
        TOptional<FString> DescriptionValue;
        
    public:
        
        FUpdateKeyRequest();
        FUpdateKeyRequest(
            const FUpdateKeyRequest& From
        );
        ~FUpdateKeyRequest() = default;

        TSharedPtr<FUpdateKeyRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FUpdateKeyRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FUpdateKeyRequest> WithKeyName(const TOptional<FString> KeyName);
        TSharedPtr<FUpdateKeyRequest> WithDescription(const TOptional<FString> Description);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetKeyName() const;
        TOptional<FString> GetDescription() const;

        static TSharedPtr<FUpdateKeyRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FUpdateKeyRequest> FUpdateKeyRequestPtr;
}