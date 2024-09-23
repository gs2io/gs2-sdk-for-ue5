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
    class FEarlyCompleteByUserIdRequest;

    class GS2MATCHMAKING_API FEarlyCompleteByUserIdRequest final : public TSharedFromThis<FEarlyCompleteByUserIdRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> GatheringNameValue;
        TOptional<FString> UserIdValue;
        TOptional<FString> TimeOffsetTokenValue;
        TOptional<FString> DuplicationAvoiderValue;
        
    public:
        
        FEarlyCompleteByUserIdRequest();
        FEarlyCompleteByUserIdRequest(
            const FEarlyCompleteByUserIdRequest& From
        );
        ~FEarlyCompleteByUserIdRequest() = default;

        TSharedPtr<FEarlyCompleteByUserIdRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FEarlyCompleteByUserIdRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FEarlyCompleteByUserIdRequest> WithGatheringName(const TOptional<FString> GatheringName);
        TSharedPtr<FEarlyCompleteByUserIdRequest> WithUserId(const TOptional<FString> UserId);
        TSharedPtr<FEarlyCompleteByUserIdRequest> WithTimeOffsetToken(const TOptional<FString> TimeOffsetToken);
        TSharedPtr<FEarlyCompleteByUserIdRequest> WithDuplicationAvoider(const TOptional<FString> DuplicationAvoider);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetGatheringName() const;
        TOptional<FString> GetUserId() const;
        TOptional<FString> GetTimeOffsetToken() const;
        TOptional<FString> GetDuplicationAvoider() const;

        static TSharedPtr<FEarlyCompleteByUserIdRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FEarlyCompleteByUserIdRequest, ESPMode::ThreadSafe> FEarlyCompleteByUserIdRequestPtr;
}