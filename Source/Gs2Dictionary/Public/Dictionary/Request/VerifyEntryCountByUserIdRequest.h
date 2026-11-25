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
    class FVerifyEntryCountByUserIdRequest;

    class GS2DICTIONARY_API FVerifyEntryCountByUserIdRequest final : public TSharedFromThis<FVerifyEntryCountByUserIdRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> UserIdValue;
        TSharedPtr<TArray<FString>> EntryModelNamesValue;
        TOptional<FString> VerifyTypeValue;
        TOptional<int32> CountValue;
        TOptional<FString> TimeOffsetTokenValue;
        TOptional<FString> DuplicationAvoiderValue;
        
    public:
        
        FVerifyEntryCountByUserIdRequest();
        FVerifyEntryCountByUserIdRequest(
            const FVerifyEntryCountByUserIdRequest& From
        );
        ~FVerifyEntryCountByUserIdRequest() = default;

        TSharedPtr<FVerifyEntryCountByUserIdRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FVerifyEntryCountByUserIdRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FVerifyEntryCountByUserIdRequest> WithUserId(const TOptional<FString> UserId);
        TSharedPtr<FVerifyEntryCountByUserIdRequest> WithEntryModelNames(
            const TSharedPtr<TArray<FString>> EntryModelNames);
        TSharedPtr<FVerifyEntryCountByUserIdRequest> WithVerifyType(const TOptional<FString> VerifyType);
        TSharedPtr<FVerifyEntryCountByUserIdRequest> WithCount(const TOptional<int32> Count);
        TSharedPtr<FVerifyEntryCountByUserIdRequest> WithTimeOffsetToken(const TOptional<FString> TimeOffsetToken);
        TSharedPtr<FVerifyEntryCountByUserIdRequest> WithDuplicationAvoider(const TOptional<FString> DuplicationAvoider);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetUserId() const;
        TSharedPtr<TArray<FString>> GetEntryModelNames() const;
        TOptional<FString> GetVerifyType() const;
        TOptional<int32> GetCount() const;
        FString GetCountString() const;
        TOptional<FString> GetTimeOffsetToken() const;
        TOptional<FString> GetDuplicationAvoider() const;

        static TSharedPtr<FVerifyEntryCountByUserIdRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FVerifyEntryCountByUserIdRequest> FVerifyEntryCountByUserIdRequestPtr;
}