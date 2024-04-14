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
#include "../Model/RandomStatus.h"

namespace Gs2::Script::Request
{
    class FInvokeScriptRequest;

    class GS2SCRIPT_API FInvokeScriptRequest final : public TSharedFromThis<FInvokeScriptRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> ScriptIdValue;
        TOptional<FString> UserIdValue;
        TOptional<FString> ArgsValue;
        TSharedPtr<Model::FRandomStatus> RandomStatusValue;
        TOptional<FString> TimeOffsetTokenValue;
        TOptional<FString> DuplicationAvoiderValue;
        
    public:
        
        FInvokeScriptRequest();
        FInvokeScriptRequest(
            const FInvokeScriptRequest& From
        );
        ~FInvokeScriptRequest() = default;

        TSharedPtr<FInvokeScriptRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FInvokeScriptRequest> WithScriptId(const TOptional<FString> ScriptId);
        TSharedPtr<FInvokeScriptRequest> WithUserId(const TOptional<FString> UserId);
        TSharedPtr<FInvokeScriptRequest> WithArgs(const TOptional<FString> Args);
        TSharedPtr<FInvokeScriptRequest> WithRandomStatus(const TSharedPtr<Model::FRandomStatus> RandomStatus);
        TSharedPtr<FInvokeScriptRequest> WithTimeOffsetToken(const TOptional<FString> TimeOffsetToken);
        TSharedPtr<FInvokeScriptRequest> WithDuplicationAvoider(const TOptional<FString> DuplicationAvoider);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetScriptId() const;
        TOptional<FString> GetUserId() const;
        TOptional<FString> GetArgs() const;
        TSharedPtr<Model::FRandomStatus> GetRandomStatus() const;
        TOptional<FString> GetTimeOffsetToken() const;
        TOptional<FString> GetDuplicationAvoider() const;

        static TSharedPtr<FInvokeScriptRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FInvokeScriptRequest, ESPMode::ThreadSafe> FInvokeScriptRequestPtr;
}