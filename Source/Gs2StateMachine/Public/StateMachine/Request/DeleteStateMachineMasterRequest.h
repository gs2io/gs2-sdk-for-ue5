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

namespace Gs2::StateMachine::Request
{
    class FDeleteStateMachineMasterRequest;

    class GS2STATEMACHINE_API FDeleteStateMachineMasterRequest final : public TSharedFromThis<FDeleteStateMachineMasterRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<int64> VersionValue;
        
    public:
        
        FDeleteStateMachineMasterRequest();
        FDeleteStateMachineMasterRequest(
            const FDeleteStateMachineMasterRequest& From
        );
        ~FDeleteStateMachineMasterRequest() = default;

        TSharedPtr<FDeleteStateMachineMasterRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FDeleteStateMachineMasterRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FDeleteStateMachineMasterRequest> WithVersion(const TOptional<int64> Version);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<int64> GetVersion() const;
        FString GetVersionString() const;

        static TSharedPtr<FDeleteStateMachineMasterRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FDeleteStateMachineMasterRequest> FDeleteStateMachineMasterRequestPtr;
}