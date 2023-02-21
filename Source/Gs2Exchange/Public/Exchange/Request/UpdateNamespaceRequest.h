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

namespace Gs2::Exchange::Request
{
    class FUpdateNamespaceRequest;

    class GS2EXCHANGE_API FUpdateNamespaceRequest final : public TSharedFromThis<FUpdateNamespaceRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> DescriptionValue;
        TOptional<bool> EnableAwaitExchangeValue;
        TOptional<bool> EnableDirectExchangeValue;
        TSharedPtr<Model::FTransactionSetting> TransactionSettingValue;
        TSharedPtr<Model::FScriptSetting> ExchangeScriptValue;
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
        TSharedPtr<FUpdateNamespaceRequest> WithEnableAwaitExchange(const TOptional<bool> EnableAwaitExchange);
        TSharedPtr<FUpdateNamespaceRequest> WithEnableDirectExchange(const TOptional<bool> EnableDirectExchange);
        TSharedPtr<FUpdateNamespaceRequest> WithTransactionSetting(const TSharedPtr<Model::FTransactionSetting> TransactionSetting);
        TSharedPtr<FUpdateNamespaceRequest> WithExchangeScript(const TSharedPtr<Model::FScriptSetting> ExchangeScript);
        TSharedPtr<FUpdateNamespaceRequest> WithLogSetting(const TSharedPtr<Model::FLogSetting> LogSetting);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetDescription() const;
        TOptional<bool> GetEnableAwaitExchange() const;
        FString GetEnableAwaitExchangeString() const;
        TOptional<bool> GetEnableDirectExchange() const;
        FString GetEnableDirectExchangeString() const;
        TSharedPtr<Model::FTransactionSetting> GetTransactionSetting() const;
        TSharedPtr<Model::FScriptSetting> GetExchangeScript() const;
        TSharedPtr<Model::FLogSetting> GetLogSetting() const;

        static TSharedPtr<FUpdateNamespaceRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FUpdateNamespaceRequest, ESPMode::ThreadSafe> FUpdateNamespaceRequestPtr;
}