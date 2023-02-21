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

namespace Gs2::Auth::Model
{
    class GS2AUTH_API FAccessToken final : public TSharedFromThis<FAccessToken>
    {
        TOptional<FString> TokenValue;
        TOptional<FString> UserIdValue;
        TOptional<int64> ExpireValue;
        TOptional<int32> TimeOffsetValue;

    public:
        FAccessToken();
        FAccessToken(
            const FAccessToken& From
        );
        ~FAccessToken() = default;

        TSharedPtr<FAccessToken> WithToken(const TOptional<FString> Token);
        TSharedPtr<FAccessToken> WithUserId(const TOptional<FString> UserId);
        TSharedPtr<FAccessToken> WithExpire(const TOptional<int64> Expire);
        TSharedPtr<FAccessToken> WithTimeOffset(const TOptional<int32> TimeOffset);

        TOptional<FString> GetToken() const;
        TOptional<FString> GetUserId() const;
        TOptional<int64> GetExpire() const;
        FString GetExpireString() const;
        TOptional<int32> GetTimeOffset() const;
        FString GetTimeOffsetString() const;


        static TSharedPtr<FAccessToken> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;

        static FString TypeName;
    };
    typedef TSharedPtr<FAccessToken, ESPMode::ThreadSafe> FAccessTokenPtr;
}