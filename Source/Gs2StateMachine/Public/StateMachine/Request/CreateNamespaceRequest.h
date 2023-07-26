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
#include "../Model/ScriptSetting.h"
#include "../Model/LogSetting.h"

namespace Gs2::StateMachine::Request
{
    class FCreateNamespaceRequest;

    class GS2STATEMACHINE_API FCreateNamespaceRequest final : public TSharedFromThis<FCreateNamespaceRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NameValue;
        TOptional<FString> DescriptionValue;
        TSharedPtr<Model::FScriptSetting> StartScriptValue;
        TSharedPtr<Model::FScriptSetting> PassScriptValue;
        TSharedPtr<Model::FScriptSetting> ErrorScriptValue;
        TOptional<int64> LowestStateMachineVersionValue;
        TSharedPtr<Model::FLogSetting> LogSettingValue;
        
    public:
        
        FCreateNamespaceRequest();
        FCreateNamespaceRequest(
            const FCreateNamespaceRequest& From
        );
        ~FCreateNamespaceRequest() = default;

        TSharedPtr<FCreateNamespaceRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FCreateNamespaceRequest> WithName(const TOptional<FString> Name);
        TSharedPtr<FCreateNamespaceRequest> WithDescription(const TOptional<FString> Description);
        TSharedPtr<FCreateNamespaceRequest> WithStartScript(const TSharedPtr<Model::FScriptSetting> StartScript);
        TSharedPtr<FCreateNamespaceRequest> WithPassScript(const TSharedPtr<Model::FScriptSetting> PassScript);
        TSharedPtr<FCreateNamespaceRequest> WithErrorScript(const TSharedPtr<Model::FScriptSetting> ErrorScript);
        TSharedPtr<FCreateNamespaceRequest> WithLowestStateMachineVersion(const TOptional<int64> LowestStateMachineVersion);
        TSharedPtr<FCreateNamespaceRequest> WithLogSetting(const TSharedPtr<Model::FLogSetting> LogSetting);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetName() const;
        TOptional<FString> GetDescription() const;
        TSharedPtr<Model::FScriptSetting> GetStartScript() const;
        TSharedPtr<Model::FScriptSetting> GetPassScript() const;
        TSharedPtr<Model::FScriptSetting> GetErrorScript() const;
        TOptional<int64> GetLowestStateMachineVersion() const;
        FString GetLowestStateMachineVersionString() const;
        TSharedPtr<Model::FLogSetting> GetLogSetting() const;

        static TSharedPtr<FCreateNamespaceRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FCreateNamespaceRequest, ESPMode::ThreadSafe> FCreateNamespaceRequestPtr;
}