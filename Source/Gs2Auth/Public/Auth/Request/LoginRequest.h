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

namespace Gs2::Auth::Request
{
    class FLoginRequest;

    class GS2AUTH_API FLoginRequest final : public TSharedFromThis<FLoginRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> UserIdValue;
        TOptional<int32> TimeOffsetValue;
        TOptional<FString> TimeOffsetTokenValue;
        
    public:
        
        FLoginRequest();
        FLoginRequest(
            const FLoginRequest& From
        );
        ~FLoginRequest() = default;

        TSharedPtr<FLoginRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FLoginRequest> WithUserId(const TOptional<FString> UserId);
        TSharedPtr<FLoginRequest> WithTimeOffset(const TOptional<int32> TimeOffset);
        TSharedPtr<FLoginRequest> WithTimeOffsetToken(const TOptional<FString> TimeOffsetToken);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetUserId() const;
        TOptional<int32> GetTimeOffset() const;
        FString GetTimeOffsetString() const;
        TOptional<FString> GetTimeOffsetToken() const;

        static TSharedPtr<FLoginRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FLoginRequest> FLoginRequestPtr;
}