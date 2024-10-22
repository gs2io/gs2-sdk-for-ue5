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
    class FAddEntriesByUserIdRequest;

    class GS2DICTIONARY_API FAddEntriesByUserIdRequest final : public TSharedFromThis<FAddEntriesByUserIdRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> UserIdValue;
        TSharedPtr<TArray<FString>> EntryModelNamesValue;
        TOptional<FString> TimeOffsetTokenValue;
        TOptional<FString> DuplicationAvoiderValue;
        
    public:
        
        FAddEntriesByUserIdRequest();
        FAddEntriesByUserIdRequest(
            const FAddEntriesByUserIdRequest& From
        );
        ~FAddEntriesByUserIdRequest() = default;

        TSharedPtr<FAddEntriesByUserIdRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FAddEntriesByUserIdRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FAddEntriesByUserIdRequest> WithUserId(const TOptional<FString> UserId);
        TSharedPtr<FAddEntriesByUserIdRequest> WithEntryModelNames(
            const TSharedPtr<TArray<FString>> EntryModelNames);
        TSharedPtr<FAddEntriesByUserIdRequest> WithTimeOffsetToken(const TOptional<FString> TimeOffsetToken);
        TSharedPtr<FAddEntriesByUserIdRequest> WithDuplicationAvoider(const TOptional<FString> DuplicationAvoider);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetUserId() const;
        TSharedPtr<TArray<FString>> GetEntryModelNames() const;
        TOptional<FString> GetTimeOffsetToken() const;
        TOptional<FString> GetDuplicationAvoider() const;

        static TSharedPtr<FAddEntriesByUserIdRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FAddEntriesByUserIdRequest> FAddEntriesByUserIdRequestPtr;
}