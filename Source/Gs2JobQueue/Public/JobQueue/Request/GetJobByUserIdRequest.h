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
    class FGetJobByUserIdRequest;

    class GS2JOBQUEUE_API FGetJobByUserIdRequest final : public TSharedFromThis<FGetJobByUserIdRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> UserIdValue;
        TOptional<FString> JobNameValue;
        
    public:
        
        FGetJobByUserIdRequest();
        FGetJobByUserIdRequest(
            const FGetJobByUserIdRequest& From
        );
        ~FGetJobByUserIdRequest() = default;

        TSharedPtr<FGetJobByUserIdRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FGetJobByUserIdRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FGetJobByUserIdRequest> WithUserId(const TOptional<FString> UserId);
        TSharedPtr<FGetJobByUserIdRequest> WithJobName(const TOptional<FString> JobName);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetUserId() const;
        TOptional<FString> GetJobName() const;

        static TSharedPtr<FGetJobByUserIdRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FGetJobByUserIdRequest, ESPMode::ThreadSafe> FGetJobByUserIdRequestPtr;
}