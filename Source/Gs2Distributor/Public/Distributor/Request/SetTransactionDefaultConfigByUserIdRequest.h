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
    class FSetTransactionDefaultConfigByUserIdRequest;

    class GS2DISTRIBUTOR_API FSetTransactionDefaultConfigByUserIdRequest final : public TSharedFromThis<FSetTransactionDefaultConfigByUserIdRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> UserIdValue;
        TSharedPtr<TArray<TSharedPtr<Model::FConfig>>> ConfigValue;
        TOptional<FString> TimeOffsetTokenValue;
        
    public:
        
        FSetTransactionDefaultConfigByUserIdRequest();
        FSetTransactionDefaultConfigByUserIdRequest(
            const FSetTransactionDefaultConfigByUserIdRequest& From
        );
        ~FSetTransactionDefaultConfigByUserIdRequest() = default;

        TSharedPtr<FSetTransactionDefaultConfigByUserIdRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FSetTransactionDefaultConfigByUserIdRequest> WithUserId(const TOptional<FString> UserId);
        TSharedPtr<FSetTransactionDefaultConfigByUserIdRequest> WithConfig(const TSharedPtr<TArray<TSharedPtr<Model::FConfig>>> Config);
        TSharedPtr<FSetTransactionDefaultConfigByUserIdRequest> WithTimeOffsetToken(const TOptional<FString> TimeOffsetToken);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetUserId() const;TSharedPtr<TArray<TSharedPtr<Model::FConfig>>> GetConfig() const;
        TOptional<FString> GetTimeOffsetToken() const;

        static TSharedPtr<FSetTransactionDefaultConfigByUserIdRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FSetTransactionDefaultConfigByUserIdRequest, ESPMode::ThreadSafe> FSetTransactionDefaultConfigByUserIdRequestPtr;
}