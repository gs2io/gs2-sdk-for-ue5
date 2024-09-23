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
    class FRunStampTaskRequest;

    class GS2DISTRIBUTOR_API FRunStampTaskRequest final : public TSharedFromThis<FRunStampTaskRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> StampTaskValue;
        TOptional<FString> KeyIdValue;
        
    public:
        
        FRunStampTaskRequest();
        FRunStampTaskRequest(
            const FRunStampTaskRequest& From
        );
        ~FRunStampTaskRequest() = default;

        TSharedPtr<FRunStampTaskRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FRunStampTaskRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FRunStampTaskRequest> WithStampTask(const TOptional<FString> StampTask);
        TSharedPtr<FRunStampTaskRequest> WithKeyId(const TOptional<FString> KeyId);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetStampTask() const;
        TOptional<FString> GetKeyId() const;

        static TSharedPtr<FRunStampTaskRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FRunStampTaskRequest, ESPMode::ThreadSafe> FRunStampTaskRequestPtr;
}