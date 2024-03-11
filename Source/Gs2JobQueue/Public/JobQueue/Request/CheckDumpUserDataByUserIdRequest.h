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

namespace Gs2::JobQueue::Request
{
    class FCheckDumpUserDataByUserIdRequest;

    class GS2JOBQUEUE_API FCheckDumpUserDataByUserIdRequest final : public TSharedFromThis<FCheckDumpUserDataByUserIdRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> UserIdValue;
        TOptional<FString> TimeOffsetTokenValue;
        TOptional<FString> DuplicationAvoiderValue;
        
    public:
        
        FCheckDumpUserDataByUserIdRequest();
        FCheckDumpUserDataByUserIdRequest(
            const FCheckDumpUserDataByUserIdRequest& From
        );
        ~FCheckDumpUserDataByUserIdRequest() = default;

        TSharedPtr<FCheckDumpUserDataByUserIdRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FCheckDumpUserDataByUserIdRequest> WithUserId(const TOptional<FString> UserId);
        TSharedPtr<FCheckDumpUserDataByUserIdRequest> WithTimeOffsetToken(const TOptional<FString> TimeOffsetToken);
        TSharedPtr<FCheckDumpUserDataByUserIdRequest> WithDuplicationAvoider(const TOptional<FString> DuplicationAvoider);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetUserId() const;
        TOptional<FString> GetTimeOffsetToken() const;
        TOptional<FString> GetDuplicationAvoider() const;

        static TSharedPtr<FCheckDumpUserDataByUserIdRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FCheckDumpUserDataByUserIdRequest, ESPMode::ThreadSafe> FCheckDumpUserDataByUserIdRequestPtr;
}