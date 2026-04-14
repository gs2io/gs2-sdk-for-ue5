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

namespace Gs2::Log::Request
{
    class FGetLogRequest;

    class GS2LOG_API FGetLogRequest final : public TSharedFromThis<FGetLogRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> LogRequestIdValue;
        TOptional<int64> BeginValue;
        TOptional<int64> EndValue;
        
    public:
        
        FGetLogRequest();
        FGetLogRequest(
            const FGetLogRequest& From
        );
        ~FGetLogRequest() = default;

        TSharedPtr<FGetLogRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FGetLogRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FGetLogRequest> WithLogRequestId(const TOptional<FString> LogRequestId);
        TSharedPtr<FGetLogRequest> WithBegin(const TOptional<int64> Begin);
        TSharedPtr<FGetLogRequest> WithEnd(const TOptional<int64> End);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetLogRequestId() const;
        TOptional<int64> GetBegin() const;
        FString GetBeginString() const;
        TOptional<int64> GetEnd() const;
        FString GetEndString() const;

        static TSharedPtr<FGetLogRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FGetLogRequest> FGetLogRequestPtr;
}