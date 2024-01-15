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

namespace Gs2::Inventory::Request
{
    class FUpdateNamespaceRequest;

    class GS2INVENTORY_API FUpdateNamespaceRequest final : public TSharedFromThis<FUpdateNamespaceRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> DescriptionValue;
        TSharedPtr<Model::FScriptSetting> AcquireScriptValue;
        TSharedPtr<Model::FScriptSetting> OverflowScriptValue;
        TSharedPtr<Model::FScriptSetting> ConsumeScriptValue;
        TSharedPtr<Model::FScriptSetting> SimpleItemAcquireScriptValue;
        TSharedPtr<Model::FScriptSetting> SimpleItemConsumeScriptValue;
        TSharedPtr<Model::FLogSetting> LogSettingValue;
        
    public:
        
        FUpdateNamespaceRequest();
        FUpdateNamespaceRequest(
            const FUpdateNamespaceRequest& From
        );
        ~FUpdateNamespaceRequest() = default;

        TSharedPtr<FUpdateNamespaceRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FUpdateNamespaceRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FUpdateNamespaceRequest> WithDescription(const TOptional<FString> Description);
        TSharedPtr<FUpdateNamespaceRequest> WithAcquireScript(const TSharedPtr<Model::FScriptSetting> AcquireScript);
        TSharedPtr<FUpdateNamespaceRequest> WithOverflowScript(const TSharedPtr<Model::FScriptSetting> OverflowScript);
        TSharedPtr<FUpdateNamespaceRequest> WithConsumeScript(const TSharedPtr<Model::FScriptSetting> ConsumeScript);
        TSharedPtr<FUpdateNamespaceRequest> WithSimpleItemAcquireScript(const TSharedPtr<Model::FScriptSetting> SimpleItemAcquireScript);
        TSharedPtr<FUpdateNamespaceRequest> WithSimpleItemConsumeScript(const TSharedPtr<Model::FScriptSetting> SimpleItemConsumeScript);
        TSharedPtr<FUpdateNamespaceRequest> WithLogSetting(const TSharedPtr<Model::FLogSetting> LogSetting);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetDescription() const;
        TSharedPtr<Model::FScriptSetting> GetAcquireScript() const;
        TSharedPtr<Model::FScriptSetting> GetOverflowScript() const;
        TSharedPtr<Model::FScriptSetting> GetConsumeScript() const;
        TSharedPtr<Model::FScriptSetting> GetSimpleItemAcquireScript() const;
        TSharedPtr<Model::FScriptSetting> GetSimpleItemConsumeScript() const;
        TSharedPtr<Model::FLogSetting> GetLogSetting() const;

        static TSharedPtr<FUpdateNamespaceRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FUpdateNamespaceRequest, ESPMode::ThreadSafe> FUpdateNamespaceRequestPtr;
}