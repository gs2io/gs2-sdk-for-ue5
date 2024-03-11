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

namespace Gs2::Dictionary::Request
{
    class FDeleteEntriesByUserIdRequest;

    class GS2DICTIONARY_API FDeleteEntriesByUserIdRequest final : public TSharedFromThis<FDeleteEntriesByUserIdRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> UserIdValue;
        TSharedPtr<TArray<FString>> EntryModelNamesValue;
        TOptional<FString> TimeOffsetTokenValue;
        TOptional<FString> DuplicationAvoiderValue;
        
    public:
        
        FDeleteEntriesByUserIdRequest();
        FDeleteEntriesByUserIdRequest(
            const FDeleteEntriesByUserIdRequest& From
        );
        ~FDeleteEntriesByUserIdRequest() = default;

        TSharedPtr<FDeleteEntriesByUserIdRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FDeleteEntriesByUserIdRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FDeleteEntriesByUserIdRequest> WithUserId(const TOptional<FString> UserId);
        TSharedPtr<FDeleteEntriesByUserIdRequest> WithEntryModelNames(
            const TSharedPtr<TArray<FString>> EntryModelNames);
        TSharedPtr<FDeleteEntriesByUserIdRequest> WithTimeOffsetToken(const TOptional<FString> TimeOffsetToken);
        TSharedPtr<FDeleteEntriesByUserIdRequest> WithDuplicationAvoider(const TOptional<FString> DuplicationAvoider);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetUserId() const;
        TSharedPtr<TArray<FString>> GetEntryModelNames() const;
        TOptional<FString> GetTimeOffsetToken() const;
        TOptional<FString> GetDuplicationAvoider() const;

        static TSharedPtr<FDeleteEntriesByUserIdRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FDeleteEntriesByUserIdRequest, ESPMode::ThreadSafe> FDeleteEntriesByUserIdRequestPtr;
}