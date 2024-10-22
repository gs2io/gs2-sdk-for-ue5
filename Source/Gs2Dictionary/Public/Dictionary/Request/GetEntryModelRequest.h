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
    class FGetEntryModelRequest;

    class GS2DICTIONARY_API FGetEntryModelRequest final : public TSharedFromThis<FGetEntryModelRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> EntryNameValue;
        
    public:
        
        FGetEntryModelRequest();
        FGetEntryModelRequest(
            const FGetEntryModelRequest& From
        );
        ~FGetEntryModelRequest() = default;

        TSharedPtr<FGetEntryModelRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FGetEntryModelRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FGetEntryModelRequest> WithEntryName(const TOptional<FString> EntryName);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetEntryName() const;

        static TSharedPtr<FGetEntryModelRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FGetEntryModelRequest> FGetEntryModelRequestPtr;
}