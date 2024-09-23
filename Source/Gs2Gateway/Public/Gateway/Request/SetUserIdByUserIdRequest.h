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

namespace Gs2::Gateway::Request
{
    class FSetUserIdByUserIdRequest;

    class GS2GATEWAY_API FSetUserIdByUserIdRequest final : public TSharedFromThis<FSetUserIdByUserIdRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> UserIdValue;
        TOptional<bool> AllowConcurrentAccessValue;
        TOptional<FString> TimeOffsetTokenValue;
        TOptional<FString> DuplicationAvoiderValue;
        
    public:
        
        FSetUserIdByUserIdRequest();
        FSetUserIdByUserIdRequest(
            const FSetUserIdByUserIdRequest& From
        );
        ~FSetUserIdByUserIdRequest() = default;

        TSharedPtr<FSetUserIdByUserIdRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FSetUserIdByUserIdRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FSetUserIdByUserIdRequest> WithUserId(const TOptional<FString> UserId);
        TSharedPtr<FSetUserIdByUserIdRequest> WithAllowConcurrentAccess(const TOptional<bool> AllowConcurrentAccess);
        TSharedPtr<FSetUserIdByUserIdRequest> WithTimeOffsetToken(const TOptional<FString> TimeOffsetToken);
        TSharedPtr<FSetUserIdByUserIdRequest> WithDuplicationAvoider(const TOptional<FString> DuplicationAvoider);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetUserId() const;
        TOptional<bool> GetAllowConcurrentAccess() const;
        FString GetAllowConcurrentAccessString() const;
        TOptional<FString> GetTimeOffsetToken() const;
        TOptional<FString> GetDuplicationAvoider() const;

        static TSharedPtr<FSetUserIdByUserIdRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FSetUserIdByUserIdRequest, ESPMode::ThreadSafe> FSetUserIdByUserIdRequestPtr;
}