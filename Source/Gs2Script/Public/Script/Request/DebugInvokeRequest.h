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
#include "../Model/RandomStatus.h"

namespace Gs2::Script::Request
{
    class FDebugInvokeRequest;

    class GS2SCRIPT_API FDebugInvokeRequest final : public TSharedFromThis<FDebugInvokeRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> ScriptValue;
        TOptional<FString> ArgsValue;
        TSharedPtr<Model::FRandomStatus> RandomStatusValue;
        
    public:
        
        FDebugInvokeRequest();
        FDebugInvokeRequest(
            const FDebugInvokeRequest& From
        );
        ~FDebugInvokeRequest() = default;

        TSharedPtr<FDebugInvokeRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FDebugInvokeRequest> WithScript(const TOptional<FString> Script);
        TSharedPtr<FDebugInvokeRequest> WithArgs(const TOptional<FString> Args);
        TSharedPtr<FDebugInvokeRequest> WithRandomStatus(const TSharedPtr<Model::FRandomStatus> RandomStatus);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetScript() const;
        TOptional<FString> GetArgs() const;
        TSharedPtr<Model::FRandomStatus> GetRandomStatus() const;

        static TSharedPtr<FDebugInvokeRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FDebugInvokeRequest> FDebugInvokeRequestPtr;
}