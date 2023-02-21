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

namespace Gs2::SerialKey::Request
{
    class FUseByUserIdRequest;

    class GS2SERIALKEY_API FUseByUserIdRequest final : public TSharedFromThis<FUseByUserIdRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> UserIdValue;
        TOptional<FString> CodeValue;
        TOptional<FString> DuplicationAvoiderValue;
        
    public:
        
        FUseByUserIdRequest();
        FUseByUserIdRequest(
            const FUseByUserIdRequest& From
        );
        ~FUseByUserIdRequest() = default;

        TSharedPtr<FUseByUserIdRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FUseByUserIdRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FUseByUserIdRequest> WithUserId(const TOptional<FString> UserId);
        TSharedPtr<FUseByUserIdRequest> WithCode(const TOptional<FString> Code);
        TSharedPtr<FUseByUserIdRequest> WithDuplicationAvoider(const TOptional<FString> DuplicationAvoider);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetUserId() const;
        TOptional<FString> GetCode() const;
        TOptional<FString> GetDuplicationAvoider() const;

        static TSharedPtr<FUseByUserIdRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FUseByUserIdRequest, ESPMode::ThreadSafe> FUseByUserIdRequestPtr;
}