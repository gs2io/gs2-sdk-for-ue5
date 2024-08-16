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

namespace Gs2::SerialKey::Request
{
    class FRevertUseByUserIdRequest;

    class GS2SERIALKEY_API FRevertUseByUserIdRequest final : public TSharedFromThis<FRevertUseByUserIdRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> UserIdValue;
        TOptional<FString> CodeValue;
        TOptional<FString> TimeOffsetTokenValue;
        TOptional<FString> DuplicationAvoiderValue;
        
    public:
        
        FRevertUseByUserIdRequest();
        FRevertUseByUserIdRequest(
            const FRevertUseByUserIdRequest& From
        );
        ~FRevertUseByUserIdRequest() = default;

        TSharedPtr<FRevertUseByUserIdRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FRevertUseByUserIdRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FRevertUseByUserIdRequest> WithUserId(const TOptional<FString> UserId);
        TSharedPtr<FRevertUseByUserIdRequest> WithCode(const TOptional<FString> Code);
        TSharedPtr<FRevertUseByUserIdRequest> WithTimeOffsetToken(const TOptional<FString> TimeOffsetToken);
        TSharedPtr<FRevertUseByUserIdRequest> WithDuplicationAvoider(const TOptional<FString> DuplicationAvoider);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetUserId() const;
        TOptional<FString> GetCode() const;
        TOptional<FString> GetTimeOffsetToken() const;
        TOptional<FString> GetDuplicationAvoider() const;

        static TSharedPtr<FRevertUseByUserIdRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FRevertUseByUserIdRequest> FRevertUseByUserIdRequestPtr;
}