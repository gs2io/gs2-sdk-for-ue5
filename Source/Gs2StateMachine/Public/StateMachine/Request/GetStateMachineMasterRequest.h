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
    class FGetStateMachineMasterRequest;

    class GS2STATEMACHINE_API FGetStateMachineMasterRequest final : public TSharedFromThis<FGetStateMachineMasterRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<int64> VersionValue;
        
    public:
        
        FGetStateMachineMasterRequest();
        FGetStateMachineMasterRequest(
            const FGetStateMachineMasterRequest& From
        );
        ~FGetStateMachineMasterRequest() = default;

        TSharedPtr<FGetStateMachineMasterRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FGetStateMachineMasterRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FGetStateMachineMasterRequest> WithVersion(const TOptional<int64> Version);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<int64> GetVersion() const;
        FString GetVersionString() const;

        static TSharedPtr<FGetStateMachineMasterRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FGetStateMachineMasterRequest, ESPMode::ThreadSafe> FGetStateMachineMasterRequestPtr;
}