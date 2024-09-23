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
#include "../Model/Config.h"

namespace Gs2::Distributor::Request
{
    class FSetTransactionDefaultConfigRequest;

    class GS2DISTRIBUTOR_API FSetTransactionDefaultConfigRequest final : public TSharedFromThis<FSetTransactionDefaultConfigRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> AccessTokenValue;
        TSharedPtr<TArray<TSharedPtr<Model::FConfig>>> ConfigValue;
        TOptional<FString> DuplicationAvoiderValue;
        
    public:
        
        FSetTransactionDefaultConfigRequest();
        FSetTransactionDefaultConfigRequest(
            const FSetTransactionDefaultConfigRequest& From
        );
        ~FSetTransactionDefaultConfigRequest() = default;

        TSharedPtr<FSetTransactionDefaultConfigRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FSetTransactionDefaultConfigRequest> WithAccessToken(const TOptional<FString> AccessToken);
        TSharedPtr<FSetTransactionDefaultConfigRequest> WithConfig(const TSharedPtr<TArray<TSharedPtr<Model::FConfig>>> Config);
        TSharedPtr<FSetTransactionDefaultConfigRequest> WithDuplicationAvoider(const TOptional<FString> DuplicationAvoider);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetAccessToken() const;TSharedPtr<TArray<TSharedPtr<Model::FConfig>>> GetConfig() const;
        TOptional<FString> GetDuplicationAvoider() const;

        static TSharedPtr<FSetTransactionDefaultConfigRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FSetTransactionDefaultConfigRequest, ESPMode::ThreadSafe> FSetTransactionDefaultConfigRequestPtr;
}