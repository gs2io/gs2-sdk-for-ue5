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

namespace Gs2::StateMachine::Request
{
    class FUpdateStateMachineMasterRequest;

    class GS2STATEMACHINE_API FUpdateStateMachineMasterRequest final : public TSharedFromThis<FUpdateStateMachineMasterRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> MainStateMachineNameValue;
        TOptional<FString> PayloadValue;
        
    public:
        
        FUpdateStateMachineMasterRequest();
        FUpdateStateMachineMasterRequest(
            const FUpdateStateMachineMasterRequest& From
        );
        ~FUpdateStateMachineMasterRequest() = default;

        TSharedPtr<FUpdateStateMachineMasterRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FUpdateStateMachineMasterRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FUpdateStateMachineMasterRequest> WithMainStateMachineName(const TOptional<FString> MainStateMachineName);
        TSharedPtr<FUpdateStateMachineMasterRequest> WithPayload(const TOptional<FString> Payload);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetMainStateMachineName() const;
        TOptional<FString> GetPayload() const;

        static TSharedPtr<FUpdateStateMachineMasterRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FUpdateStateMachineMasterRequest, ESPMode::ThreadSafe> FUpdateStateMachineMasterRequestPtr;
}