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
    class FCreateScriptRequest;

    class GS2SCRIPT_API FCreateScriptRequest final : public TSharedFromThis<FCreateScriptRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> NameValue;
        TOptional<FString> DescriptionValue;
        TOptional<FString> ScriptValue;
        
    public:
        
        FCreateScriptRequest();
        FCreateScriptRequest(
            const FCreateScriptRequest& From
        );
        ~FCreateScriptRequest() = default;

        TSharedPtr<FCreateScriptRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FCreateScriptRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FCreateScriptRequest> WithName(const TOptional<FString> Name);
        TSharedPtr<FCreateScriptRequest> WithDescription(const TOptional<FString> Description);
        TSharedPtr<FCreateScriptRequest> WithScript(const TOptional<FString> Script);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetName() const;
        TOptional<FString> GetDescription() const;
        TOptional<FString> GetScript() const;

        static TSharedPtr<FCreateScriptRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FCreateScriptRequest> FCreateScriptRequestPtr;
}