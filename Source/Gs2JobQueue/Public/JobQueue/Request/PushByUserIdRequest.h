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
#include "../Model/JobEntry.h"

namespace Gs2::JobQueue::Request
{
    class FPushByUserIdRequest;

    class GS2JOBQUEUE_API FPushByUserIdRequest final : public TSharedFromThis<FPushByUserIdRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> UserIdValue;
        TSharedPtr<TArray<TSharedPtr<Model::FJobEntry>>> JobsValue;
        TOptional<FString> TimeOffsetTokenValue;
        TOptional<FString> DuplicationAvoiderValue;
        
    public:
        
        FPushByUserIdRequest();
        FPushByUserIdRequest(
            const FPushByUserIdRequest& From
        );
        ~FPushByUserIdRequest() = default;

        TSharedPtr<FPushByUserIdRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FPushByUserIdRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FPushByUserIdRequest> WithUserId(const TOptional<FString> UserId);
        TSharedPtr<FPushByUserIdRequest> WithJobs(const TSharedPtr<TArray<TSharedPtr<Model::FJobEntry>>> Jobs);
        TSharedPtr<FPushByUserIdRequest> WithTimeOffsetToken(const TOptional<FString> TimeOffsetToken);
        TSharedPtr<FPushByUserIdRequest> WithDuplicationAvoider(const TOptional<FString> DuplicationAvoider);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetUserId() const;TSharedPtr<TArray<TSharedPtr<Model::FJobEntry>>> GetJobs() const;
        TOptional<FString> GetTimeOffsetToken() const;
        TOptional<FString> GetDuplicationAvoider() const;

        static TSharedPtr<FPushByUserIdRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FPushByUserIdRequest> FPushByUserIdRequestPtr;
}