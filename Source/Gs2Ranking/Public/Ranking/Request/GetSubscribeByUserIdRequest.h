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

namespace Gs2::Ranking::Request
{
    class FGetSubscribeByUserIdRequest;

    class GS2RANKING_API FGetSubscribeByUserIdRequest final : public TSharedFromThis<FGetSubscribeByUserIdRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> CategoryNameValue;
        TOptional<FString> UserIdValue;
        TOptional<FString> TargetUserIdValue;
        TOptional<FString> TimeOffsetTokenValue;
        
    public:
        
        FGetSubscribeByUserIdRequest();
        FGetSubscribeByUserIdRequest(
            const FGetSubscribeByUserIdRequest& From
        );
        ~FGetSubscribeByUserIdRequest() = default;

        TSharedPtr<FGetSubscribeByUserIdRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FGetSubscribeByUserIdRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FGetSubscribeByUserIdRequest> WithCategoryName(const TOptional<FString> CategoryName);
        TSharedPtr<FGetSubscribeByUserIdRequest> WithUserId(const TOptional<FString> UserId);
        TSharedPtr<FGetSubscribeByUserIdRequest> WithTargetUserId(const TOptional<FString> TargetUserId);
        TSharedPtr<FGetSubscribeByUserIdRequest> WithTimeOffsetToken(const TOptional<FString> TimeOffsetToken);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetCategoryName() const;
        TOptional<FString> GetUserId() const;
        TOptional<FString> GetTargetUserId() const;
        TOptional<FString> GetTimeOffsetToken() const;

        static TSharedPtr<FGetSubscribeByUserIdRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FGetSubscribeByUserIdRequest> FGetSubscribeByUserIdRequestPtr;
}