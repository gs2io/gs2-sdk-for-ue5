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

namespace Gs2::Script::Request
{
    class FDeleteScriptRequest;

    class GS2SCRIPT_API FDeleteScriptRequest final : public TSharedFromThis<FDeleteScriptRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> ScriptNameValue;
        
    public:
        
        FDeleteScriptRequest();
        FDeleteScriptRequest(
            const FDeleteScriptRequest& From
        );
        ~FDeleteScriptRequest() = default;

        TSharedPtr<FDeleteScriptRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FDeleteScriptRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FDeleteScriptRequest> WithScriptName(const TOptional<FString> ScriptName);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetScriptName() const;

        static TSharedPtr<FDeleteScriptRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FDeleteScriptRequest, ESPMode::ThreadSafe> FDeleteScriptRequestPtr;
}