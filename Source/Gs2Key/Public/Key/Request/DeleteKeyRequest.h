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

namespace Gs2::Key::Request
{
    class FDeleteKeyRequest;

    class GS2KEY_API FDeleteKeyRequest final : public TSharedFromThis<FDeleteKeyRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> KeyNameValue;
        
    public:
        
        FDeleteKeyRequest();
        FDeleteKeyRequest(
            const FDeleteKeyRequest& From
        );
        ~FDeleteKeyRequest() = default;

        TSharedPtr<FDeleteKeyRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FDeleteKeyRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FDeleteKeyRequest> WithKeyName(const TOptional<FString> KeyName);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetKeyName() const;

        static TSharedPtr<FDeleteKeyRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FDeleteKeyRequest, ESPMode::ThreadSafe> FDeleteKeyRequestPtr;
}