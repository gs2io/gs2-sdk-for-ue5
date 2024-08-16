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
    class FDeleteJobRequest;

    class GS2JOBQUEUE_API FDeleteJobRequest final : public TSharedFromThis<FDeleteJobRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> AccessTokenValue;
        TOptional<FString> JobNameValue;
        TOptional<FString> DuplicationAvoiderValue;
        
    public:
        
        FDeleteJobRequest();
        FDeleteJobRequest(
            const FDeleteJobRequest& From
        );
        ~FDeleteJobRequest() = default;

        TSharedPtr<FDeleteJobRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FDeleteJobRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FDeleteJobRequest> WithAccessToken(const TOptional<FString> AccessToken);
        TSharedPtr<FDeleteJobRequest> WithJobName(const TOptional<FString> JobName);
        TSharedPtr<FDeleteJobRequest> WithDuplicationAvoider(const TOptional<FString> DuplicationAvoider);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetAccessToken() const;
        TOptional<FString> GetJobName() const;
        TOptional<FString> GetDuplicationAvoider() const;

        static TSharedPtr<FDeleteJobRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FDeleteJobRequest> FDeleteJobRequestPtr;
}