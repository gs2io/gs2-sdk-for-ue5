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

namespace Gs2::Schedule::Request
{
    class FGetTriggerRequest;

    class GS2SCHEDULE_API FGetTriggerRequest final : public TSharedFromThis<FGetTriggerRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> AccessTokenValue;
        TOptional<FString> TriggerNameValue;
        
    public:
        
        FGetTriggerRequest();
        FGetTriggerRequest(
            const FGetTriggerRequest& From
        );
        ~FGetTriggerRequest() = default;

        TSharedPtr<FGetTriggerRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FGetTriggerRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FGetTriggerRequest> WithAccessToken(const TOptional<FString> AccessToken);
        TSharedPtr<FGetTriggerRequest> WithTriggerName(const TOptional<FString> TriggerName);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetAccessToken() const;
        TOptional<FString> GetTriggerName() const;

        static TSharedPtr<FGetTriggerRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FGetTriggerRequest, ESPMode::ThreadSafe> FGetTriggerRequestPtr;
}