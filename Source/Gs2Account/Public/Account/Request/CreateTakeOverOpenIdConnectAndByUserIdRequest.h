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

namespace Gs2::Account::Request
{
    class FCreateTakeOverOpenIdConnectAndByUserIdRequest;

    class GS2ACCOUNT_API FCreateTakeOverOpenIdConnectAndByUserIdRequest final : public TSharedFromThis<FCreateTakeOverOpenIdConnectAndByUserIdRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> UserIdValue;
        TOptional<int32> TypeValue;
        TOptional<FString> IdTokenValue;
        TOptional<FString> TimeOffsetTokenValue;
        TOptional<FString> DuplicationAvoiderValue;
        
    public:
        
        FCreateTakeOverOpenIdConnectAndByUserIdRequest();
        FCreateTakeOverOpenIdConnectAndByUserIdRequest(
            const FCreateTakeOverOpenIdConnectAndByUserIdRequest& From
        );
        ~FCreateTakeOverOpenIdConnectAndByUserIdRequest() = default;

        TSharedPtr<FCreateTakeOverOpenIdConnectAndByUserIdRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FCreateTakeOverOpenIdConnectAndByUserIdRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FCreateTakeOverOpenIdConnectAndByUserIdRequest> WithUserId(const TOptional<FString> UserId);
        TSharedPtr<FCreateTakeOverOpenIdConnectAndByUserIdRequest> WithType(const TOptional<int32> Type);
        TSharedPtr<FCreateTakeOverOpenIdConnectAndByUserIdRequest> WithIdToken(const TOptional<FString> IdToken);
        TSharedPtr<FCreateTakeOverOpenIdConnectAndByUserIdRequest> WithTimeOffsetToken(const TOptional<FString> TimeOffsetToken);
        TSharedPtr<FCreateTakeOverOpenIdConnectAndByUserIdRequest> WithDuplicationAvoider(const TOptional<FString> DuplicationAvoider);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetUserId() const;
        TOptional<int32> GetType() const;
        FString GetTypeString() const;
        TOptional<FString> GetIdToken() const;
        TOptional<FString> GetTimeOffsetToken() const;
        TOptional<FString> GetDuplicationAvoider() const;

        static TSharedPtr<FCreateTakeOverOpenIdConnectAndByUserIdRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FCreateTakeOverOpenIdConnectAndByUserIdRequest> FCreateTakeOverOpenIdConnectAndByUserIdRequestPtr;
}