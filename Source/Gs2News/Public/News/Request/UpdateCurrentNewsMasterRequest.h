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

namespace Gs2::News::Request
{
    class FUpdateCurrentNewsMasterRequest;

    class GS2NEWS_API FUpdateCurrentNewsMasterRequest final : public TSharedFromThis<FUpdateCurrentNewsMasterRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> UploadTokenValue;
        
    public:
        
        FUpdateCurrentNewsMasterRequest();
        FUpdateCurrentNewsMasterRequest(
            const FUpdateCurrentNewsMasterRequest& From
        );
        ~FUpdateCurrentNewsMasterRequest() = default;

        TSharedPtr<FUpdateCurrentNewsMasterRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FUpdateCurrentNewsMasterRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FUpdateCurrentNewsMasterRequest> WithUploadToken(const TOptional<FString> UploadToken);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetUploadToken() const;

        static TSharedPtr<FUpdateCurrentNewsMasterRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FUpdateCurrentNewsMasterRequest, ESPMode::ThreadSafe> FUpdateCurrentNewsMasterRequestPtr;
}