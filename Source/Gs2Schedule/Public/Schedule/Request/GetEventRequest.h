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
    class FGetEventRequest;

    class GS2SCHEDULE_API FGetEventRequest final : public TSharedFromThis<FGetEventRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> EventNameValue;
        TOptional<FString> AccessTokenValue;
        
    public:
        
        FGetEventRequest();
        FGetEventRequest(
            const FGetEventRequest& From
        );
        ~FGetEventRequest() = default;

        TSharedPtr<FGetEventRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FGetEventRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FGetEventRequest> WithEventName(const TOptional<FString> EventName);
        TSharedPtr<FGetEventRequest> WithAccessToken(const TOptional<FString> AccessToken);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetEventName() const;
        TOptional<FString> GetAccessToken() const;

        static TSharedPtr<FGetEventRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FGetEventRequest, ESPMode::ThreadSafe> FGetEventRequestPtr;
}