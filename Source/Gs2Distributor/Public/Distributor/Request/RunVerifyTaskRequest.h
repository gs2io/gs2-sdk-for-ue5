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

namespace Gs2::Distributor::Request
{
    class FRunVerifyTaskRequest;

    class GS2DISTRIBUTOR_API FRunVerifyTaskRequest final : public TSharedFromThis<FRunVerifyTaskRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> VerifyTaskValue;
        TOptional<FString> KeyIdValue;
        
    public:
        
        FRunVerifyTaskRequest();
        FRunVerifyTaskRequest(
            const FRunVerifyTaskRequest& From
        );
        ~FRunVerifyTaskRequest() = default;

        TSharedPtr<FRunVerifyTaskRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FRunVerifyTaskRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FRunVerifyTaskRequest> WithVerifyTask(const TOptional<FString> VerifyTask);
        TSharedPtr<FRunVerifyTaskRequest> WithKeyId(const TOptional<FString> KeyId);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetVerifyTask() const;
        TOptional<FString> GetKeyId() const;

        static TSharedPtr<FRunVerifyTaskRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FRunVerifyTaskRequest, ESPMode::ThreadSafe> FRunVerifyTaskRequestPtr;
}