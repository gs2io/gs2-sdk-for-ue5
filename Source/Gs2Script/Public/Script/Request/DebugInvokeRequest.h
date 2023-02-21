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
    class FDebugInvokeRequest;

    class GS2SCRIPT_API FDebugInvokeRequest final : public TSharedFromThis<FDebugInvokeRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> ScriptValue;
        TOptional<FString> ArgsValue;
        
    public:
        
        FDebugInvokeRequest();
        FDebugInvokeRequest(
            const FDebugInvokeRequest& From
        );
        ~FDebugInvokeRequest() = default;

        TSharedPtr<FDebugInvokeRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FDebugInvokeRequest> WithScript(const TOptional<FString> Script);
        TSharedPtr<FDebugInvokeRequest> WithArgs(const TOptional<FString> Args);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetScript() const;
        TOptional<FString> GetArgs() const;

        static TSharedPtr<FDebugInvokeRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FDebugInvokeRequest, ESPMode::ThreadSafe> FDebugInvokeRequestPtr;
}