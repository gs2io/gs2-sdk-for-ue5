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

namespace Gs2::Enhance::Request
{
    class FGetProgressByUserIdRequest;

    class GS2ENHANCE_API FGetProgressByUserIdRequest final : public TSharedFromThis<FGetProgressByUserIdRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> UserIdValue;
        TOptional<FString> TimeOffsetTokenValue;
        
    public:
        
        FGetProgressByUserIdRequest();
        FGetProgressByUserIdRequest(
            const FGetProgressByUserIdRequest& From
        );
        ~FGetProgressByUserIdRequest() = default;

        TSharedPtr<FGetProgressByUserIdRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FGetProgressByUserIdRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FGetProgressByUserIdRequest> WithUserId(const TOptional<FString> UserId);
        TSharedPtr<FGetProgressByUserIdRequest> WithTimeOffsetToken(const TOptional<FString> TimeOffsetToken);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetUserId() const;
        TOptional<FString> GetTimeOffsetToken() const;

        static TSharedPtr<FGetProgressByUserIdRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FGetProgressByUserIdRequest> FGetProgressByUserIdRequestPtr;
}