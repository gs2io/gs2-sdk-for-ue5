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

namespace Gs2::Idle::Request
{
    class FGetStatusByUserIdRequest;

    class GS2IDLE_API FGetStatusByUserIdRequest final : public TSharedFromThis<FGetStatusByUserIdRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> UserIdValue;
        TOptional<FString> CategoryNameValue;
        TOptional<FString> TimeOffsetTokenValue;
        
    public:
        
        FGetStatusByUserIdRequest();
        FGetStatusByUserIdRequest(
            const FGetStatusByUserIdRequest& From
        );
        ~FGetStatusByUserIdRequest() = default;

        TSharedPtr<FGetStatusByUserIdRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FGetStatusByUserIdRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FGetStatusByUserIdRequest> WithUserId(const TOptional<FString> UserId);
        TSharedPtr<FGetStatusByUserIdRequest> WithCategoryName(const TOptional<FString> CategoryName);
        TSharedPtr<FGetStatusByUserIdRequest> WithTimeOffsetToken(const TOptional<FString> TimeOffsetToken);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetUserId() const;
        TOptional<FString> GetCategoryName() const;
        TOptional<FString> GetTimeOffsetToken() const;

        static TSharedPtr<FGetStatusByUserIdRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FGetStatusByUserIdRequest> FGetStatusByUserIdRequestPtr;
}