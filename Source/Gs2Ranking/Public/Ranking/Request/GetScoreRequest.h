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
    class FGetScoreRequest;

    class GS2RANKING_API FGetScoreRequest final : public TSharedFromThis<FGetScoreRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> CategoryNameValue;
        TOptional<FString> AccessTokenValue;
        TOptional<FString> ScorerUserIdValue;
        TOptional<FString> UniqueIdValue;
        
    public:
        
        FGetScoreRequest();
        FGetScoreRequest(
            const FGetScoreRequest& From
        );
        ~FGetScoreRequest() = default;

        TSharedPtr<FGetScoreRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FGetScoreRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FGetScoreRequest> WithCategoryName(const TOptional<FString> CategoryName);
        TSharedPtr<FGetScoreRequest> WithAccessToken(const TOptional<FString> AccessToken);
        TSharedPtr<FGetScoreRequest> WithScorerUserId(const TOptional<FString> ScorerUserId);
        TSharedPtr<FGetScoreRequest> WithUniqueId(const TOptional<FString> UniqueId);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetCategoryName() const;
        TOptional<FString> GetAccessToken() const;
        TOptional<FString> GetScorerUserId() const;
        TOptional<FString> GetUniqueId() const;

        static TSharedPtr<FGetScoreRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FGetScoreRequest> FGetScoreRequestPtr;
}