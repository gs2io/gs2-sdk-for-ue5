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
    class FGetBoxByUserIdRequest;

    class GS2LOTTERY_API FGetBoxByUserIdRequest final : public TSharedFromThis<FGetBoxByUserIdRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> PrizeTableNameValue;
        TOptional<FString> UserIdValue;
        
    public:
        
        FGetBoxByUserIdRequest();
        FGetBoxByUserIdRequest(
            const FGetBoxByUserIdRequest& From
        );
        ~FGetBoxByUserIdRequest() = default;

        TSharedPtr<FGetBoxByUserIdRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FGetBoxByUserIdRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FGetBoxByUserIdRequest> WithPrizeTableName(const TOptional<FString> PrizeTableName);
        TSharedPtr<FGetBoxByUserIdRequest> WithUserId(const TOptional<FString> UserId);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetPrizeTableName() const;
        TOptional<FString> GetUserId() const;

        static TSharedPtr<FGetBoxByUserIdRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FGetBoxByUserIdRequest, ESPMode::ThreadSafe> FGetBoxByUserIdRequestPtr;
}