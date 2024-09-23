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

namespace Gs2::Deploy::Request
{
    class FGetResourceRequest;

    class GS2DEPLOY_API FGetResourceRequest final : public TSharedFromThis<FGetResourceRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> StackNameValue;
        TOptional<FString> ResourceNameValue;
        
    public:
        
        FGetResourceRequest();
        FGetResourceRequest(
            const FGetResourceRequest& From
        );
        ~FGetResourceRequest() = default;

        TSharedPtr<FGetResourceRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FGetResourceRequest> WithStackName(const TOptional<FString> StackName);
        TSharedPtr<FGetResourceRequest> WithResourceName(const TOptional<FString> ResourceName);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetStackName() const;
        TOptional<FString> GetResourceName() const;

        static TSharedPtr<FGetResourceRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FGetResourceRequest, ESPMode::ThreadSafe> FGetResourceRequestPtr;
}