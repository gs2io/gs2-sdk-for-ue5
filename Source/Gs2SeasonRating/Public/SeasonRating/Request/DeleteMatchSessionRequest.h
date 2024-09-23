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

namespace Gs2::SeasonRating::Request
{
    class FDeleteMatchSessionRequest;

    class GS2SEASONRATING_API FDeleteMatchSessionRequest final : public TSharedFromThis<FDeleteMatchSessionRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> SessionNameValue;
        
    public:
        
        FDeleteMatchSessionRequest();
        FDeleteMatchSessionRequest(
            const FDeleteMatchSessionRequest& From
        );
        ~FDeleteMatchSessionRequest() = default;

        TSharedPtr<FDeleteMatchSessionRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FDeleteMatchSessionRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FDeleteMatchSessionRequest> WithSessionName(const TOptional<FString> SessionName);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetSessionName() const;

        static TSharedPtr<FDeleteMatchSessionRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FDeleteMatchSessionRequest, ESPMode::ThreadSafe> FDeleteMatchSessionRequestPtr;
}