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

namespace Gs2::JobQueue::Request
{
    class FCleanUserDataByUserIdRequest;

    class GS2JOBQUEUE_API FCleanUserDataByUserIdRequest final : public TSharedFromThis<FCleanUserDataByUserIdRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> UserIdValue;
        TOptional<FString> TimeOffsetTokenValue;
        
    public:
        
        FCleanUserDataByUserIdRequest();
        FCleanUserDataByUserIdRequest(
            const FCleanUserDataByUserIdRequest& From
        );
        ~FCleanUserDataByUserIdRequest() = default;

        TSharedPtr<FCleanUserDataByUserIdRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FCleanUserDataByUserIdRequest> WithUserId(const TOptional<FString> UserId);
        TSharedPtr<FCleanUserDataByUserIdRequest> WithTimeOffsetToken(const TOptional<FString> TimeOffsetToken);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetUserId() const;
        TOptional<FString> GetTimeOffsetToken() const;

        static TSharedPtr<FCleanUserDataByUserIdRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FCleanUserDataByUserIdRequest> FCleanUserDataByUserIdRequestPtr;
}