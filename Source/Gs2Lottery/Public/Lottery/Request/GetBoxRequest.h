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

namespace Gs2::Lottery::Request
{
    class FGetBoxRequest;

    class GS2LOTTERY_API FGetBoxRequest final : public TSharedFromThis<FGetBoxRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> PrizeTableNameValue;
        TOptional<FString> AccessTokenValue;
        
    public:
        
        FGetBoxRequest();
        FGetBoxRequest(
            const FGetBoxRequest& From
        );
        ~FGetBoxRequest() = default;

        TSharedPtr<FGetBoxRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FGetBoxRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FGetBoxRequest> WithPrizeTableName(const TOptional<FString> PrizeTableName);
        TSharedPtr<FGetBoxRequest> WithAccessToken(const TOptional<FString> AccessToken);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetPrizeTableName() const;
        TOptional<FString> GetAccessToken() const;

        static TSharedPtr<FGetBoxRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FGetBoxRequest, ESPMode::ThreadSafe> FGetBoxRequestPtr;
}