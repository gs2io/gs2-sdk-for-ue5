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
#include "../Model/ScriptSetting.h"
#include "../Model/LogSetting.h"

namespace Gs2::Inventory::Request
{
    class FCreateNamespaceRequest;

    class GS2INVENTORY_API FCreateNamespaceRequest final : public TSharedFromThis<FCreateNamespaceRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NameValue;
        TOptional<FString> DescriptionValue;
        TSharedPtr<Model::FScriptSetting> AcquireScriptValue;
        TSharedPtr<Model::FScriptSetting> OverflowScriptValue;
        TSharedPtr<Model::FScriptSetting> ConsumeScriptValue;
        TSharedPtr<Model::FScriptSetting> SimpleItemAcquireScriptValue;
        TSharedPtr<Model::FScriptSetting> SimpleItemConsumeScriptValue;
        TSharedPtr<Model::FScriptSetting> BigItemAcquireScriptValue;
        TSharedPtr<Model::FScriptSetting> BigItemConsumeScriptValue;
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
        TSharedPtr<FCreateNamespaceRequest> WithAcquireScript(const TSharedPtr<Model::FScriptSetting> AcquireScript);
        TSharedPtr<FCreateNamespaceRequest> WithOverflowScript(const TSharedPtr<Model::FScriptSetting> OverflowScript);
        TSharedPtr<FCreateNamespaceRequest> WithConsumeScript(const TSharedPtr<Model::FScriptSetting> ConsumeScript);
        TSharedPtr<FCreateNamespaceRequest> WithSimpleItemAcquireScript(const TSharedPtr<Model::FScriptSetting> SimpleItemAcquireScript);
        TSharedPtr<FCreateNamespaceRequest> WithSimpleItemConsumeScript(const TSharedPtr<Model::FScriptSetting> SimpleItemConsumeScript);
        TSharedPtr<FCreateNamespaceRequest> WithBigItemAcquireScript(const TSharedPtr<Model::FScriptSetting> BigItemAcquireScript);
        TSharedPtr<FCreateNamespaceRequest> WithBigItemConsumeScript(const TSharedPtr<Model::FScriptSetting> BigItemConsumeScript);
        TSharedPtr<FCreateNamespaceRequest> WithLogSetting(const TSharedPtr<Model::FLogSetting> LogSetting);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetName() const;
        TOptional<FString> GetDescription() const;
        TSharedPtr<Model::FScriptSetting> GetAcquireScript() const;
        TSharedPtr<Model::FScriptSetting> GetOverflowScript() const;
        TSharedPtr<Model::FScriptSetting> GetConsumeScript() const;
        TSharedPtr<Model::FScriptSetting> GetSimpleItemAcquireScript() const;
        TSharedPtr<Model::FScriptSetting> GetSimpleItemConsumeScript() const;
        TSharedPtr<Model::FScriptSetting> GetBigItemAcquireScript() const;
        TSharedPtr<Model::FScriptSetting> GetBigItemConsumeScript() const;
        TSharedPtr<Model::FLogSetting> GetLogSetting() const;

        static TSharedPtr<FCreateNamespaceRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FCreateNamespaceRequest> FCreateNamespaceRequestPtr;
}