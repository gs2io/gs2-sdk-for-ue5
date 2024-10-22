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
    class FDeleteEntriesRequest;

    class GS2DICTIONARY_API FDeleteEntriesRequest final : public TSharedFromThis<FDeleteEntriesRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> AccessTokenValue;
        TSharedPtr<TArray<FString>> EntryModelNamesValue;
        TOptional<FString> DuplicationAvoiderValue;
        
    public:
        
        FDeleteEntriesRequest();
        FDeleteEntriesRequest(
            const FDeleteEntriesRequest& From
        );
        ~FDeleteEntriesRequest() = default;

        TSharedPtr<FDeleteEntriesRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FDeleteEntriesRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FDeleteEntriesRequest> WithAccessToken(const TOptional<FString> AccessToken);
        TSharedPtr<FDeleteEntriesRequest> WithEntryModelNames(
            const TSharedPtr<TArray<FString>> EntryModelNames);
        TSharedPtr<FDeleteEntriesRequest> WithDuplicationAvoider(const TOptional<FString> DuplicationAvoider);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetAccessToken() const;
        TSharedPtr<TArray<FString>> GetEntryModelNames() const;
        TOptional<FString> GetDuplicationAvoider() const;

        static TSharedPtr<FDeleteEntriesRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FDeleteEntriesRequest> FDeleteEntriesRequestPtr;
}