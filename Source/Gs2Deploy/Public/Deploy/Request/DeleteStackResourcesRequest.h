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
    class FDeleteStackResourcesRequest;

    class GS2DEPLOY_API FDeleteStackResourcesRequest final : public TSharedFromThis<FDeleteStackResourcesRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> StackNameValue;
        
    public:
        
        FDeleteStackResourcesRequest();
        FDeleteStackResourcesRequest(
            const FDeleteStackResourcesRequest& From
        );
        ~FDeleteStackResourcesRequest() = default;

        TSharedPtr<FDeleteStackResourcesRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FDeleteStackResourcesRequest> WithStackName(const TOptional<FString> StackName);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetStackName() const;

        static TSharedPtr<FDeleteStackResourcesRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FDeleteStackResourcesRequest, ESPMode::ThreadSafe> FDeleteStackResourcesRequestPtr;
}