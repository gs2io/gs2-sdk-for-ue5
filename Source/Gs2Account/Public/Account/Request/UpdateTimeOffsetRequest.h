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

namespace Gs2::Account::Request
{
    class FUpdateTimeOffsetRequest;

    class GS2ACCOUNT_API FUpdateTimeOffsetRequest final : public TSharedFromThis<FUpdateTimeOffsetRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> UserIdValue;
        TOptional<int32> TimeOffsetValue;
        TOptional<FString> TimeOffsetTokenValue;
        TOptional<FString> DuplicationAvoiderValue;
        
    public:
        
        FUpdateTimeOffsetRequest();
        FUpdateTimeOffsetRequest(
            const FUpdateTimeOffsetRequest& From
        );
        ~FUpdateTimeOffsetRequest() = default;

        TSharedPtr<FUpdateTimeOffsetRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FUpdateTimeOffsetRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FUpdateTimeOffsetRequest> WithUserId(const TOptional<FString> UserId);
        TSharedPtr<FUpdateTimeOffsetRequest> WithTimeOffset(const TOptional<int32> TimeOffset);
        TSharedPtr<FUpdateTimeOffsetRequest> WithTimeOffsetToken(const TOptional<FString> TimeOffsetToken);
        TSharedPtr<FUpdateTimeOffsetRequest> WithDuplicationAvoider(const TOptional<FString> DuplicationAvoider);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetUserId() const;
        TOptional<int32> GetTimeOffset() const;
        FString GetTimeOffsetString() const;
        TOptional<FString> GetTimeOffsetToken() const;
        TOptional<FString> GetDuplicationAvoider() const;

        static TSharedPtr<FUpdateTimeOffsetRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FUpdateTimeOffsetRequest, ESPMode::ThreadSafe> FUpdateTimeOffsetRequestPtr;
}