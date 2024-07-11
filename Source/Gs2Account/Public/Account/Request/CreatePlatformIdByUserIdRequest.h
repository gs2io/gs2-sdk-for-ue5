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

namespace Gs2::Account::Request
{
    class FCreatePlatformIdByUserIdRequest;

    class GS2ACCOUNT_API FCreatePlatformIdByUserIdRequest final : public TSharedFromThis<FCreatePlatformIdByUserIdRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> UserIdValue;
        TOptional<int32> TypeValue;
        TOptional<FString> UserIdentifierValue;
        TOptional<FString> TimeOffsetTokenValue;
        TOptional<FString> DuplicationAvoiderValue;
        
    public:
        
        FCreatePlatformIdByUserIdRequest();
        FCreatePlatformIdByUserIdRequest(
            const FCreatePlatformIdByUserIdRequest& From
        );
        ~FCreatePlatformIdByUserIdRequest() = default;

        TSharedPtr<FCreatePlatformIdByUserIdRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FCreatePlatformIdByUserIdRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FCreatePlatformIdByUserIdRequest> WithUserId(const TOptional<FString> UserId);
        TSharedPtr<FCreatePlatformIdByUserIdRequest> WithType(const TOptional<int32> Type);
        TSharedPtr<FCreatePlatformIdByUserIdRequest> WithUserIdentifier(const TOptional<FString> UserIdentifier);
        TSharedPtr<FCreatePlatformIdByUserIdRequest> WithTimeOffsetToken(const TOptional<FString> TimeOffsetToken);
        TSharedPtr<FCreatePlatformIdByUserIdRequest> WithDuplicationAvoider(const TOptional<FString> DuplicationAvoider);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetUserId() const;
        TOptional<int32> GetType() const;
        FString GetTypeString() const;
        TOptional<FString> GetUserIdentifier() const;
        TOptional<FString> GetTimeOffsetToken() const;
        TOptional<FString> GetDuplicationAvoider() const;

        static TSharedPtr<FCreatePlatformIdByUserIdRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FCreatePlatformIdByUserIdRequest, ESPMode::ThreadSafe> FCreatePlatformIdByUserIdRequestPtr;
}