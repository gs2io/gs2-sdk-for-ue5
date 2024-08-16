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

namespace Gs2::Script::Request
{
    class FUpdateScriptRequest;

    class GS2SCRIPT_API FUpdateScriptRequest final : public TSharedFromThis<FUpdateScriptRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> ScriptNameValue;
        TOptional<FString> DescriptionValue;
        TOptional<FString> ScriptValue;
        
    public:
        
        FUpdateScriptRequest();
        FUpdateScriptRequest(
            const FUpdateScriptRequest& From
        );
        ~FUpdateScriptRequest() = default;

        TSharedPtr<FUpdateScriptRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FUpdateScriptRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FUpdateScriptRequest> WithScriptName(const TOptional<FString> ScriptName);
        TSharedPtr<FUpdateScriptRequest> WithDescription(const TOptional<FString> Description);
        TSharedPtr<FUpdateScriptRequest> WithScript(const TOptional<FString> Script);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetScriptName() const;
        TOptional<FString> GetDescription() const;
        TOptional<FString> GetScript() const;

        static TSharedPtr<FUpdateScriptRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FUpdateScriptRequest> FUpdateScriptRequestPtr;
}