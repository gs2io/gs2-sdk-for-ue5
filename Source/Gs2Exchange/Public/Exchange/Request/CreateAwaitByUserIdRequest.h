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
#include "../Model/Config.h"

namespace Gs2::Exchange::Request
{
    class FCreateAwaitByUserIdRequest;

    class GS2EXCHANGE_API FCreateAwaitByUserIdRequest final : public TSharedFromThis<FCreateAwaitByUserIdRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> UserIdValue;
        TOptional<FString> RateNameValue;
        TOptional<int32> CountValue;
        TSharedPtr<TArray<TSharedPtr<Model::FConfig>>> ConfigValue;
        TOptional<FString> TimeOffsetTokenValue;
        TOptional<FString> DuplicationAvoiderValue;
        
    public:
        
        FCreateAwaitByUserIdRequest();
        FCreateAwaitByUserIdRequest(
            const FCreateAwaitByUserIdRequest& From
        );
        ~FCreateAwaitByUserIdRequest() = default;

        TSharedPtr<FCreateAwaitByUserIdRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FCreateAwaitByUserIdRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FCreateAwaitByUserIdRequest> WithUserId(const TOptional<FString> UserId);
        TSharedPtr<FCreateAwaitByUserIdRequest> WithRateName(const TOptional<FString> RateName);
        TSharedPtr<FCreateAwaitByUserIdRequest> WithCount(const TOptional<int32> Count);
        TSharedPtr<FCreateAwaitByUserIdRequest> WithConfig(const TSharedPtr<TArray<TSharedPtr<Model::FConfig>>> Config);
        TSharedPtr<FCreateAwaitByUserIdRequest> WithTimeOffsetToken(const TOptional<FString> TimeOffsetToken);
        TSharedPtr<FCreateAwaitByUserIdRequest> WithDuplicationAvoider(const TOptional<FString> DuplicationAvoider);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetUserId() const;
        TOptional<FString> GetRateName() const;
        TOptional<int32> GetCount() const;
        FString GetCountString() const;TSharedPtr<TArray<TSharedPtr<Model::FConfig>>> GetConfig() const;
        TOptional<FString> GetTimeOffsetToken() const;
        TOptional<FString> GetDuplicationAvoider() const;

        static TSharedPtr<FCreateAwaitByUserIdRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FCreateAwaitByUserIdRequest> FCreateAwaitByUserIdRequestPtr;
}