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
#include "../Model/TransactionSetting.h"
#include "../Model/ScriptSetting.h"
#include "../Model/LogSetting.h"

namespace Gs2::Experience::Request
{
    class FCreateNamespaceRequest;

    class GS2EXPERIENCE_API FCreateNamespaceRequest final : public TSharedFromThis<FCreateNamespaceRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NameValue;
        TOptional<FString> DescriptionValue;
        TSharedPtr<Model::FTransactionSetting> TransactionSettingValue;
        TOptional<FString> RankCapScriptIdValue;
        TSharedPtr<Model::FScriptSetting> ChangeExperienceScriptValue;
        TSharedPtr<Model::FScriptSetting> ChangeRankScriptValue;
        TSharedPtr<Model::FScriptSetting> ChangeRankCapScriptValue;
        TOptional<FString> OverflowExperienceScriptValue;
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
        TSharedPtr<FCreateNamespaceRequest> WithTransactionSetting(const TSharedPtr<Model::FTransactionSetting> TransactionSetting);
        TSharedPtr<FCreateNamespaceRequest> WithRankCapScriptId(const TOptional<FString> RankCapScriptId);
        TSharedPtr<FCreateNamespaceRequest> WithChangeExperienceScript(const TSharedPtr<Model::FScriptSetting> ChangeExperienceScript);
        TSharedPtr<FCreateNamespaceRequest> WithChangeRankScript(const TSharedPtr<Model::FScriptSetting> ChangeRankScript);
        TSharedPtr<FCreateNamespaceRequest> WithChangeRankCapScript(const TSharedPtr<Model::FScriptSetting> ChangeRankCapScript);
        TSharedPtr<FCreateNamespaceRequest> WithOverflowExperienceScript(const TOptional<FString> OverflowExperienceScript);
        TSharedPtr<FCreateNamespaceRequest> WithLogSetting(const TSharedPtr<Model::FLogSetting> LogSetting);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetName() const;
        TOptional<FString> GetDescription() const;
        TSharedPtr<Model::FTransactionSetting> GetTransactionSetting() const;
        TOptional<FString> GetRankCapScriptId() const;
        TSharedPtr<Model::FScriptSetting> GetChangeExperienceScript() const;
        TSharedPtr<Model::FScriptSetting> GetChangeRankScript() const;
        TSharedPtr<Model::FScriptSetting> GetChangeRankCapScript() const;
        TOptional<FString> GetOverflowExperienceScript() const;
        TSharedPtr<Model::FLogSetting> GetLogSetting() const;

        static TSharedPtr<FCreateNamespaceRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FCreateNamespaceRequest> FCreateNamespaceRequestPtr;
}