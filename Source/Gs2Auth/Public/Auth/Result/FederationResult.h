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

namespace Gs2::Auth::Result
{
    class GS2AUTH_API FFederationResult final : public TSharedFromThis<FFederationResult>
    {
        TOptional<FString> TokenValue;
        TOptional<FString> UserIdValue;
        TOptional<int64> ExpireValue;
        
    public:
        
        FFederationResult();
        FFederationResult(
            const FFederationResult& From
        );
        ~FFederationResult() = default;

        TSharedPtr<FFederationResult> WithToken(const TOptional<FString> Token);
        TSharedPtr<FFederationResult> WithUserId(const TOptional<FString> UserId);
        TSharedPtr<FFederationResult> WithExpire(const TOptional<int64> Expire);

        TOptional<FString> GetToken() const;
        TOptional<FString> GetUserId() const;
        TOptional<int64> GetExpire() const;
        FString GetExpireString() const;

        static TSharedPtr<FFederationResult> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FFederationResult, ESPMode::ThreadSafe> FFederationResultPtr;
}