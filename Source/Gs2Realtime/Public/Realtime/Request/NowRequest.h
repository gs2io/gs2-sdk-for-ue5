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

namespace Gs2::Realtime::Request
{
    class FNowRequest;

    class GS2REALTIME_API FNowRequest final : public TSharedFromThis<FNowRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> AccessTokenValue;
        
    public:
        
        FNowRequest();
        FNowRequest(
            const FNowRequest& From
        );
        ~FNowRequest() = default;

        TSharedPtr<FNowRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FNowRequest> WithAccessToken(const TOptional<FString> AccessToken);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetAccessToken() const;

        static TSharedPtr<FNowRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FNowRequest, ESPMode::ThreadSafe> FNowRequestPtr;
}