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
    class FGetEntryWithSignatureRequest;

    class GS2DICTIONARY_API FGetEntryWithSignatureRequest final : public TSharedFromThis<FGetEntryWithSignatureRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> AccessTokenValue;
        TOptional<FString> EntryModelNameValue;
        TOptional<FString> KeyIdValue;
        
    public:
        
        FGetEntryWithSignatureRequest();
        FGetEntryWithSignatureRequest(
            const FGetEntryWithSignatureRequest& From
        );
        ~FGetEntryWithSignatureRequest() = default;

        TSharedPtr<FGetEntryWithSignatureRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FGetEntryWithSignatureRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FGetEntryWithSignatureRequest> WithAccessToken(const TOptional<FString> AccessToken);
        TSharedPtr<FGetEntryWithSignatureRequest> WithEntryModelName(const TOptional<FString> EntryModelName);
        TSharedPtr<FGetEntryWithSignatureRequest> WithKeyId(const TOptional<FString> KeyId);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetAccessToken() const;
        TOptional<FString> GetEntryModelName() const;
        TOptional<FString> GetKeyId() const;

        static TSharedPtr<FGetEntryWithSignatureRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FGetEntryWithSignatureRequest> FGetEntryWithSignatureRequestPtr;
}