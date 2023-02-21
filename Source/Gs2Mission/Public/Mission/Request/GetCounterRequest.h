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

namespace Gs2::Mission::Request
{
    class FGetCounterRequest;

    class GS2MISSION_API FGetCounterRequest final : public TSharedFromThis<FGetCounterRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> CounterNameValue;
        TOptional<FString> AccessTokenValue;
        
    public:
        
        FGetCounterRequest();
        FGetCounterRequest(
            const FGetCounterRequest& From
        );
        ~FGetCounterRequest() = default;

        TSharedPtr<FGetCounterRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FGetCounterRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FGetCounterRequest> WithCounterName(const TOptional<FString> CounterName);
        TSharedPtr<FGetCounterRequest> WithAccessToken(const TOptional<FString> AccessToken);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetCounterName() const;
        TOptional<FString> GetAccessToken() const;

        static TSharedPtr<FGetCounterRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FGetCounterRequest, ESPMode::ThreadSafe> FGetCounterRequestPtr;
}