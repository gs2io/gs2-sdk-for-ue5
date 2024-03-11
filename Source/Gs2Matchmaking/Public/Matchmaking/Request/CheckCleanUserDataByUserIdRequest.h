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

namespace Gs2::Matchmaking::Request
{
    class FCheckCleanUserDataByUserIdRequest;

    class GS2MATCHMAKING_API FCheckCleanUserDataByUserIdRequest final : public TSharedFromThis<FCheckCleanUserDataByUserIdRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> UserIdValue;
        TOptional<FString> TimeOffsetTokenValue;
        TOptional<FString> DuplicationAvoiderValue;
        
    public:
        
        FCheckCleanUserDataByUserIdRequest();
        FCheckCleanUserDataByUserIdRequest(
            const FCheckCleanUserDataByUserIdRequest& From
        );
        ~FCheckCleanUserDataByUserIdRequest() = default;

        TSharedPtr<FCheckCleanUserDataByUserIdRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FCheckCleanUserDataByUserIdRequest> WithUserId(const TOptional<FString> UserId);
        TSharedPtr<FCheckCleanUserDataByUserIdRequest> WithTimeOffsetToken(const TOptional<FString> TimeOffsetToken);
        TSharedPtr<FCheckCleanUserDataByUserIdRequest> WithDuplicationAvoider(const TOptional<FString> DuplicationAvoider);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetUserId() const;
        TOptional<FString> GetTimeOffsetToken() const;
        TOptional<FString> GetDuplicationAvoider() const;

        static TSharedPtr<FCheckCleanUserDataByUserIdRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FCheckCleanUserDataByUserIdRequest, ESPMode::ThreadSafe> FCheckCleanUserDataByUserIdRequestPtr;
}