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
    class FVerifyEntryRequest;

    class GS2DICTIONARY_API FVerifyEntryRequest final : public TSharedFromThis<FVerifyEntryRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> AccessTokenValue;
        TOptional<FString> EntryModelNameValue;
        TOptional<FString> VerifyTypeValue;
        TOptional<FString> DuplicationAvoiderValue;
        
    public:
        
        FVerifyEntryRequest();
        FVerifyEntryRequest(
            const FVerifyEntryRequest& From
        );
        ~FVerifyEntryRequest() = default;

        TSharedPtr<FVerifyEntryRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FVerifyEntryRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FVerifyEntryRequest> WithAccessToken(const TOptional<FString> AccessToken);
        TSharedPtr<FVerifyEntryRequest> WithEntryModelName(const TOptional<FString> EntryModelName);
        TSharedPtr<FVerifyEntryRequest> WithVerifyType(const TOptional<FString> VerifyType);
        TSharedPtr<FVerifyEntryRequest> WithDuplicationAvoider(const TOptional<FString> DuplicationAvoider);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetAccessToken() const;
        TOptional<FString> GetEntryModelName() const;
        TOptional<FString> GetVerifyType() const;
        TOptional<FString> GetDuplicationAvoider() const;

        static TSharedPtr<FVerifyEntryRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FVerifyEntryRequest> FVerifyEntryRequestPtr;
}