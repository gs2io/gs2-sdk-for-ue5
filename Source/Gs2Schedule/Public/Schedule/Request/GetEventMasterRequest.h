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
    class FGetEventMasterRequest;

    class GS2SCHEDULE_API FGetEventMasterRequest final : public TSharedFromThis<FGetEventMasterRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> EventNameValue;
        
    public:
        
        FGetEventMasterRequest();
        FGetEventMasterRequest(
            const FGetEventMasterRequest& From
        );
        ~FGetEventMasterRequest() = default;

        TSharedPtr<FGetEventMasterRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FGetEventMasterRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FGetEventMasterRequest> WithEventName(const TOptional<FString> EventName);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetEventName() const;

        static TSharedPtr<FGetEventMasterRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FGetEventMasterRequest, ESPMode::ThreadSafe> FGetEventMasterRequestPtr;
}