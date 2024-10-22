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
    class FGetDeadLetterJobByUserIdRequest;

    class GS2JOBQUEUE_API FGetDeadLetterJobByUserIdRequest final : public TSharedFromThis<FGetDeadLetterJobByUserIdRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> UserIdValue;
        TOptional<FString> DeadLetterJobNameValue;
        TOptional<FString> TimeOffsetTokenValue;
        
    public:
        
        FGetDeadLetterJobByUserIdRequest();
        FGetDeadLetterJobByUserIdRequest(
            const FGetDeadLetterJobByUserIdRequest& From
        );
        ~FGetDeadLetterJobByUserIdRequest() = default;

        TSharedPtr<FGetDeadLetterJobByUserIdRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FGetDeadLetterJobByUserIdRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FGetDeadLetterJobByUserIdRequest> WithUserId(const TOptional<FString> UserId);
        TSharedPtr<FGetDeadLetterJobByUserIdRequest> WithDeadLetterJobName(const TOptional<FString> DeadLetterJobName);
        TSharedPtr<FGetDeadLetterJobByUserIdRequest> WithTimeOffsetToken(const TOptional<FString> TimeOffsetToken);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetUserId() const;
        TOptional<FString> GetDeadLetterJobName() const;
        TOptional<FString> GetTimeOffsetToken() const;

        static TSharedPtr<FGetDeadLetterJobByUserIdRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FGetDeadLetterJobByUserIdRequest> FGetDeadLetterJobByUserIdRequestPtr;
}