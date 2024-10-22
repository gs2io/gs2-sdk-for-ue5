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
    class FDeletePlatformIdByUserIdentifierRequest;

    class GS2ACCOUNT_API FDeletePlatformIdByUserIdentifierRequest final : public TSharedFromThis<FDeletePlatformIdByUserIdentifierRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<int32> TypeValue;
        TOptional<FString> UserIdentifierValue;
        TOptional<FString> DuplicationAvoiderValue;
        
    public:
        
        FDeletePlatformIdByUserIdentifierRequest();
        FDeletePlatformIdByUserIdentifierRequest(
            const FDeletePlatformIdByUserIdentifierRequest& From
        );
        ~FDeletePlatformIdByUserIdentifierRequest() = default;

        TSharedPtr<FDeletePlatformIdByUserIdentifierRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FDeletePlatformIdByUserIdentifierRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FDeletePlatformIdByUserIdentifierRequest> WithType(const TOptional<int32> Type);
        TSharedPtr<FDeletePlatformIdByUserIdentifierRequest> WithUserIdentifier(const TOptional<FString> UserIdentifier);
        TSharedPtr<FDeletePlatformIdByUserIdentifierRequest> WithDuplicationAvoider(const TOptional<FString> DuplicationAvoider);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<int32> GetType() const;
        FString GetTypeString() const;
        TOptional<FString> GetUserIdentifier() const;
        TOptional<FString> GetDuplicationAvoider() const;

        static TSharedPtr<FDeletePlatformIdByUserIdentifierRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FDeletePlatformIdByUserIdentifierRequest> FDeletePlatformIdByUserIdentifierRequestPtr;
}