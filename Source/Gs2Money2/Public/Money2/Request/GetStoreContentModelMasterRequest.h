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

namespace Gs2::Money2::Request
{
    class FGetStoreContentModelMasterRequest;

    class GS2MONEY2_API FGetStoreContentModelMasterRequest final : public TSharedFromThis<FGetStoreContentModelMasterRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> ContentNameValue;
        
    public:
        
        FGetStoreContentModelMasterRequest();
        FGetStoreContentModelMasterRequest(
            const FGetStoreContentModelMasterRequest& From
        );
        ~FGetStoreContentModelMasterRequest() = default;

        TSharedPtr<FGetStoreContentModelMasterRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FGetStoreContentModelMasterRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FGetStoreContentModelMasterRequest> WithContentName(const TOptional<FString> ContentName);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetContentName() const;

        static TSharedPtr<FGetStoreContentModelMasterRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FGetStoreContentModelMasterRequest, ESPMode::ThreadSafe> FGetStoreContentModelMasterRequestPtr;
}