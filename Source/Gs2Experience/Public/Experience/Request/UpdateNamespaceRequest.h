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
#include "../Model/TransactionSetting.h"
#include "../Model/ScriptSetting.h"
#include "../Model/LogSetting.h"

namespace Gs2::Experience::Request
{
    class FUpdateNamespaceRequest;

    class GS2EXPERIENCE_API FUpdateNamespaceRequest final : public TSharedFromThis<FUpdateNamespaceRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> DescriptionValue;
        TSharedPtr<Model::FTransactionSetting> TransactionSettingValue;
        TOptional<FString> RankCapScriptIdValue;
        TSharedPtr<Model::FScriptSetting> ChangeExperienceScriptValue;
        TSharedPtr<Model::FScriptSetting> ChangeRankScriptValue;
        TSharedPtr<Model::FScriptSetting> ChangeRankCapScriptValue;
        TSharedPtr<Model::FScriptSetting> OverflowExperienceScriptValue;
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
        TSharedPtr<FUpdateNamespaceRequest> WithTransactionSetting(const TSharedPtr<Model::FTransactionSetting> TransactionSetting);
        TSharedPtr<FUpdateNamespaceRequest> WithRankCapScriptId(const TOptional<FString> RankCapScriptId);
        TSharedPtr<FUpdateNamespaceRequest> WithChangeExperienceScript(const TSharedPtr<Model::FScriptSetting> ChangeExperienceScript);
        TSharedPtr<FUpdateNamespaceRequest> WithChangeRankScript(const TSharedPtr<Model::FScriptSetting> ChangeRankScript);
        TSharedPtr<FUpdateNamespaceRequest> WithChangeRankCapScript(const TSharedPtr<Model::FScriptSetting> ChangeRankCapScript);
        TSharedPtr<FUpdateNamespaceRequest> WithOverflowExperienceScript(const TSharedPtr<Model::FScriptSetting> OverflowExperienceScript);
        TSharedPtr<FUpdateNamespaceRequest> WithLogSetting(const TSharedPtr<Model::FLogSetting> LogSetting);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetDescription() const;
        TSharedPtr<Model::FTransactionSetting> GetTransactionSetting() const;
        TOptional<FString> GetRankCapScriptId() const;
        TSharedPtr<Model::FScriptSetting> GetChangeExperienceScript() const;
        TSharedPtr<Model::FScriptSetting> GetChangeRankScript() const;
        TSharedPtr<Model::FScriptSetting> GetChangeRankCapScript() const;
        TSharedPtr<Model::FScriptSetting> GetOverflowExperienceScript() const;
        TSharedPtr<Model::FLogSetting> GetLogSetting() const;

        static TSharedPtr<FUpdateNamespaceRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FUpdateNamespaceRequest, ESPMode::ThreadSafe> FUpdateNamespaceRequestPtr;
}