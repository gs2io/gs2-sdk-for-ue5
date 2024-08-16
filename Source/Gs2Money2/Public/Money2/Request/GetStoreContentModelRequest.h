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

namespace Gs2::Money2::Request
{
    class FGetStoreContentModelRequest;

    class GS2MONEY2_API FGetStoreContentModelRequest final : public TSharedFromThis<FGetStoreContentModelRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> ContentNameValue;
        
    public:
        
        FGetStoreContentModelRequest();
        FGetStoreContentModelRequest(
            const FGetStoreContentModelRequest& From
        );
        ~FGetStoreContentModelRequest() = default;

        TSharedPtr<FGetStoreContentModelRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FGetStoreContentModelRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FGetStoreContentModelRequest> WithContentName(const TOptional<FString> ContentName);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetContentName() const;

        static TSharedPtr<FGetStoreContentModelRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FGetStoreContentModelRequest> FGetStoreContentModelRequestPtr;
}