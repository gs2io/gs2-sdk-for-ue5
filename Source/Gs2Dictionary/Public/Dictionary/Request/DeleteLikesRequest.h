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
    class FDeleteLikesRequest;

    class GS2DICTIONARY_API FDeleteLikesRequest final : public TSharedFromThis<FDeleteLikesRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> AccessTokenValue;
        TSharedPtr<TArray<FString>> EntryModelNamesValue;
        TOptional<FString> DuplicationAvoiderValue;
        
    public:
        
        FDeleteLikesRequest();
        FDeleteLikesRequest(
            const FDeleteLikesRequest& From
        );
        ~FDeleteLikesRequest() = default;

        TSharedPtr<FDeleteLikesRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FDeleteLikesRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FDeleteLikesRequest> WithAccessToken(const TOptional<FString> AccessToken);
        TSharedPtr<FDeleteLikesRequest> WithEntryModelNames(
            const TSharedPtr<TArray<FString>> EntryModelNames);
        TSharedPtr<FDeleteLikesRequest> WithDuplicationAvoider(const TOptional<FString> DuplicationAvoider);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetAccessToken() const;
        TSharedPtr<TArray<FString>> GetEntryModelNames() const;
        TOptional<FString> GetDuplicationAvoider() const;

        static TSharedPtr<FDeleteLikesRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FDeleteLikesRequest> FDeleteLikesRequestPtr;
}