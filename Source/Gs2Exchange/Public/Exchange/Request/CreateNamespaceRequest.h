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

namespace Gs2::Exchange::Request
{
    class FCreateNamespaceRequest;

    class GS2EXCHANGE_API FCreateNamespaceRequest final : public TSharedFromThis<FCreateNamespaceRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NameValue;
        TOptional<FString> DescriptionValue;
        TOptional<bool> EnableAwaitExchangeValue;
        TOptional<bool> EnableDirectExchangeValue;
        TSharedPtr<Model::FTransactionSetting> TransactionSettingValue;
        TSharedPtr<Model::FScriptSetting> ExchangeScriptValue;
        TSharedPtr<Model::FScriptSetting> IncrementalExchangeScriptValue;
        TSharedPtr<Model::FLogSetting> LogSettingValue;
        TOptional<FString> QueueNamespaceIdValue;
        TOptional<FString> KeyIdValue;
        
    public:
        
        FCreateNamespaceRequest();
        FCreateNamespaceRequest(
            const FCreateNamespaceRequest& From
        );
        ~FCreateNamespaceRequest() = default;

        TSharedPtr<FCreateNamespaceRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FCreateNamespaceRequest> WithName(const TOptional<FString> Name);
        TSharedPtr<FCreateNamespaceRequest> WithDescription(const TOptional<FString> Description);
        TSharedPtr<FCreateNamespaceRequest> WithEnableAwaitExchange(const TOptional<bool> EnableAwaitExchange);
        TSharedPtr<FCreateNamespaceRequest> WithEnableDirectExchange(const TOptional<bool> EnableDirectExchange);
        TSharedPtr<FCreateNamespaceRequest> WithTransactionSetting(const TSharedPtr<Model::FTransactionSetting> TransactionSetting);
        TSharedPtr<FCreateNamespaceRequest> WithExchangeScript(const TSharedPtr<Model::FScriptSetting> ExchangeScript);
        TSharedPtr<FCreateNamespaceRequest> WithIncrementalExchangeScript(const TSharedPtr<Model::FScriptSetting> IncrementalExchangeScript);
        TSharedPtr<FCreateNamespaceRequest> WithLogSetting(const TSharedPtr<Model::FLogSetting> LogSetting);
        TSharedPtr<FCreateNamespaceRequest> WithQueueNamespaceId(const TOptional<FString> QueueNamespaceId);
        TSharedPtr<FCreateNamespaceRequest> WithKeyId(const TOptional<FString> KeyId);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetName() const;
        TOptional<FString> GetDescription() const;
        TOptional<bool> GetEnableAwaitExchange() const;
        FString GetEnableAwaitExchangeString() const;
        TOptional<bool> GetEnableDirectExchange() const;
        FString GetEnableDirectExchangeString() const;
        TSharedPtr<Model::FTransactionSetting> GetTransactionSetting() const;
        TSharedPtr<Model::FScriptSetting> GetExchangeScript() const;
        TSharedPtr<Model::FScriptSetting> GetIncrementalExchangeScript() const;
        TSharedPtr<Model::FLogSetting> GetLogSetting() const;
        TOptional<FString> GetQueueNamespaceId() const;
        TOptional<FString> GetKeyId() const;

        static TSharedPtr<FCreateNamespaceRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FCreateNamespaceRequest> FCreateNamespaceRequestPtr;
}