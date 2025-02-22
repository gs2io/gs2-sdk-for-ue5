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
    class FIssueTimeOffsetTokenByUserIdRequest;

    class GS2AUTH_API FIssueTimeOffsetTokenByUserIdRequest final : public TSharedFromThis<FIssueTimeOffsetTokenByUserIdRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> UserIdValue;
        TOptional<int32> TimeOffsetValue;
        TOptional<FString> TimeOffsetTokenValue;
        
    public:
        
        FIssueTimeOffsetTokenByUserIdRequest();
        FIssueTimeOffsetTokenByUserIdRequest(
            const FIssueTimeOffsetTokenByUserIdRequest& From
        );
        ~FIssueTimeOffsetTokenByUserIdRequest() = default;

        TSharedPtr<FIssueTimeOffsetTokenByUserIdRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FIssueTimeOffsetTokenByUserIdRequest> WithUserId(const TOptional<FString> UserId);
        TSharedPtr<FIssueTimeOffsetTokenByUserIdRequest> WithTimeOffset(const TOptional<int32> TimeOffset);
        TSharedPtr<FIssueTimeOffsetTokenByUserIdRequest> WithTimeOffsetToken(const TOptional<FString> TimeOffsetToken);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetUserId() const;
        TOptional<int32> GetTimeOffset() const;
        FString GetTimeOffsetString() const;
        TOptional<FString> GetTimeOffsetToken() const;

        static TSharedPtr<FIssueTimeOffsetTokenByUserIdRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FIssueTimeOffsetTokenByUserIdRequest> FIssueTimeOffsetTokenByUserIdRequestPtr;
}