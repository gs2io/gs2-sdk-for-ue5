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
    class FGetEntryWithSignatureByUserIdRequest;

    class GS2DICTIONARY_API FGetEntryWithSignatureByUserIdRequest final : public TSharedFromThis<FGetEntryWithSignatureByUserIdRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> UserIdValue;
        TOptional<FString> EntryModelNameValue;
        TOptional<FString> KeyIdValue;
        
    public:
        
        FGetEntryWithSignatureByUserIdRequest();
        FGetEntryWithSignatureByUserIdRequest(
            const FGetEntryWithSignatureByUserIdRequest& From
        );
        ~FGetEntryWithSignatureByUserIdRequest() = default;

        TSharedPtr<FGetEntryWithSignatureByUserIdRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FGetEntryWithSignatureByUserIdRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FGetEntryWithSignatureByUserIdRequest> WithUserId(const TOptional<FString> UserId);
        TSharedPtr<FGetEntryWithSignatureByUserIdRequest> WithEntryModelName(const TOptional<FString> EntryModelName);
        TSharedPtr<FGetEntryWithSignatureByUserIdRequest> WithKeyId(const TOptional<FString> KeyId);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetUserId() const;
        TOptional<FString> GetEntryModelName() const;
        TOptional<FString> GetKeyId() const;

        static TSharedPtr<FGetEntryWithSignatureByUserIdRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FGetEntryWithSignatureByUserIdRequest, ESPMode::ThreadSafe> FGetEntryWithSignatureByUserIdRequestPtr;
}