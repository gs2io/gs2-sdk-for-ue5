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

namespace Gs2::Dictionary::Request
{
    class FGetLikeByUserIdRequest;

    class GS2DICTIONARY_API FGetLikeByUserIdRequest final : public TSharedFromThis<FGetLikeByUserIdRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> UserIdValue;
        TOptional<FString> EntryModelNameValue;
        TOptional<FString> TimeOffsetTokenValue;
        
    public:
        
        FGetLikeByUserIdRequest();
        FGetLikeByUserIdRequest(
            const FGetLikeByUserIdRequest& From
        );
        ~FGetLikeByUserIdRequest() = default;

        TSharedPtr<FGetLikeByUserIdRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FGetLikeByUserIdRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FGetLikeByUserIdRequest> WithUserId(const TOptional<FString> UserId);
        TSharedPtr<FGetLikeByUserIdRequest> WithEntryModelName(const TOptional<FString> EntryModelName);
        TSharedPtr<FGetLikeByUserIdRequest> WithTimeOffsetToken(const TOptional<FString> TimeOffsetToken);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetUserId() const;
        TOptional<FString> GetEntryModelName() const;
        TOptional<FString> GetTimeOffsetToken() const;

        static TSharedPtr<FGetLikeByUserIdRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FGetLikeByUserIdRequest> FGetLikeByUserIdRequestPtr;
}