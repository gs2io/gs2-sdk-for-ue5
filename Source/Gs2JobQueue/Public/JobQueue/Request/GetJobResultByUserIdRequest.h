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
    class FGetJobResultByUserIdRequest;

    class GS2JOBQUEUE_API FGetJobResultByUserIdRequest final : public TSharedFromThis<FGetJobResultByUserIdRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> UserIdValue;
        TOptional<FString> JobNameValue;
        TOptional<int32> TryNumberValue;
        
    public:
        
        FGetJobResultByUserIdRequest();
        FGetJobResultByUserIdRequest(
            const FGetJobResultByUserIdRequest& From
        );
        ~FGetJobResultByUserIdRequest() = default;

        TSharedPtr<FGetJobResultByUserIdRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FGetJobResultByUserIdRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FGetJobResultByUserIdRequest> WithUserId(const TOptional<FString> UserId);
        TSharedPtr<FGetJobResultByUserIdRequest> WithJobName(const TOptional<FString> JobName);
        TSharedPtr<FGetJobResultByUserIdRequest> WithTryNumber(const TOptional<int32> TryNumber);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetUserId() const;
        TOptional<FString> GetJobName() const;
        TOptional<int32> GetTryNumber() const;
        FString GetTryNumberString() const;

        static TSharedPtr<FGetJobResultByUserIdRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FGetJobResultByUserIdRequest, ESPMode::ThreadSafe> FGetJobResultByUserIdRequestPtr;
}