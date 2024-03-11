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

namespace Gs2::Exchange::Request
{
    class FSkipByUserIdRequest;

    class GS2EXCHANGE_API FSkipByUserIdRequest final : public TSharedFromThis<FSkipByUserIdRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> UserIdValue;
        TOptional<FString> AwaitNameValue;
        TSharedPtr<TArray<TSharedPtr<Model::FConfig>>> ConfigValue;
        TOptional<FString> TimeOffsetTokenValue;
        TOptional<FString> DuplicationAvoiderValue;
        
    public:
        
        FSkipByUserIdRequest();
        FSkipByUserIdRequest(
            const FSkipByUserIdRequest& From
        );
        ~FSkipByUserIdRequest() = default;

        TSharedPtr<FSkipByUserIdRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FSkipByUserIdRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FSkipByUserIdRequest> WithUserId(const TOptional<FString> UserId);
        TSharedPtr<FSkipByUserIdRequest> WithAwaitName(const TOptional<FString> AwaitName);
        TSharedPtr<FSkipByUserIdRequest> WithConfig(const TSharedPtr<TArray<TSharedPtr<Model::FConfig>>> Config);
        TSharedPtr<FSkipByUserIdRequest> WithTimeOffsetToken(const TOptional<FString> TimeOffsetToken);
        TSharedPtr<FSkipByUserIdRequest> WithDuplicationAvoider(const TOptional<FString> DuplicationAvoider);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetUserId() const;
        TOptional<FString> GetAwaitName() const;TSharedPtr<TArray<TSharedPtr<Model::FConfig>>> GetConfig() const;
        TOptional<FString> GetTimeOffsetToken() const;
        TOptional<FString> GetDuplicationAvoider() const;

        static TSharedPtr<FSkipByUserIdRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FSkipByUserIdRequest, ESPMode::ThreadSafe> FSkipByUserIdRequestPtr;
}