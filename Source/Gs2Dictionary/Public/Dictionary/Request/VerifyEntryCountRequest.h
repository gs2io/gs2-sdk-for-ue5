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
    class FVerifyEntryCountRequest;

    class GS2DICTIONARY_API FVerifyEntryCountRequest final : public TSharedFromThis<FVerifyEntryCountRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> AccessTokenValue;
        TSharedPtr<TArray<FString>> EntryModelNamesValue;
        TOptional<FString> VerifyTypeValue;
        TOptional<int32> CountValue;
        TOptional<FString> DuplicationAvoiderValue;
        
    public:
        
        FVerifyEntryCountRequest();
        FVerifyEntryCountRequest(
            const FVerifyEntryCountRequest& From
        );
        ~FVerifyEntryCountRequest() = default;

        TSharedPtr<FVerifyEntryCountRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FVerifyEntryCountRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FVerifyEntryCountRequest> WithAccessToken(const TOptional<FString> AccessToken);
        TSharedPtr<FVerifyEntryCountRequest> WithEntryModelNames(
            const TSharedPtr<TArray<FString>> EntryModelNames);
        TSharedPtr<FVerifyEntryCountRequest> WithVerifyType(const TOptional<FString> VerifyType);
        TSharedPtr<FVerifyEntryCountRequest> WithCount(const TOptional<int32> Count);
        TSharedPtr<FVerifyEntryCountRequest> WithDuplicationAvoider(const TOptional<FString> DuplicationAvoider);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetAccessToken() const;
        TSharedPtr<TArray<FString>> GetEntryModelNames() const;
        TOptional<FString> GetVerifyType() const;
        TOptional<int32> GetCount() const;
        FString GetCountString() const;
        TOptional<FString> GetDuplicationAvoider() const;

        static TSharedPtr<FVerifyEntryCountRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FVerifyEntryCountRequest> FVerifyEntryCountRequestPtr;
}