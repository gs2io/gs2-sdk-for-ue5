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
    class FPutScoreRequest;

    class GS2RANKING_API FPutScoreRequest final : public TSharedFromThis<FPutScoreRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> CategoryNameValue;
        TOptional<FString> AccessTokenValue;
        TOptional<int64> ScoreValue;
        TOptional<FString> MetadataValue;
        TOptional<FString> DuplicationAvoiderValue;
        
    public:
        
        FPutScoreRequest();
        FPutScoreRequest(
            const FPutScoreRequest& From
        );
        ~FPutScoreRequest() = default;

        TSharedPtr<FPutScoreRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FPutScoreRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FPutScoreRequest> WithCategoryName(const TOptional<FString> CategoryName);
        TSharedPtr<FPutScoreRequest> WithAccessToken(const TOptional<FString> AccessToken);
        TSharedPtr<FPutScoreRequest> WithScore(const TOptional<int64> Score);
        TSharedPtr<FPutScoreRequest> WithMetadata(const TOptional<FString> Metadata);
        TSharedPtr<FPutScoreRequest> WithDuplicationAvoider(const TOptional<FString> DuplicationAvoider);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetCategoryName() const;
        TOptional<FString> GetAccessToken() const;
        TOptional<int64> GetScore() const;
        FString GetScoreString() const;
        TOptional<FString> GetMetadata() const;
        TOptional<FString> GetDuplicationAvoider() const;

        static TSharedPtr<FPutScoreRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FPutScoreRequest> FPutScoreRequestPtr;
}