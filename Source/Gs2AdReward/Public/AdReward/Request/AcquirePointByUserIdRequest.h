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

namespace Gs2::AdReward::Request
{
    class FAcquirePointByUserIdRequest;

    class GS2ADREWARD_API FAcquirePointByUserIdRequest final : public TSharedFromThis<FAcquirePointByUserIdRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> UserIdValue;
        TOptional<int64> PointValue;
        TOptional<FString> TimeOffsetTokenValue;
        TOptional<FString> DuplicationAvoiderValue;
        
    public:
        
        FAcquirePointByUserIdRequest();
        FAcquirePointByUserIdRequest(
            const FAcquirePointByUserIdRequest& From
        );
        ~FAcquirePointByUserIdRequest() = default;

        TSharedPtr<FAcquirePointByUserIdRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FAcquirePointByUserIdRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FAcquirePointByUserIdRequest> WithUserId(const TOptional<FString> UserId);
        TSharedPtr<FAcquirePointByUserIdRequest> WithPoint(const TOptional<int64> Point);
        TSharedPtr<FAcquirePointByUserIdRequest> WithTimeOffsetToken(const TOptional<FString> TimeOffsetToken);
        TSharedPtr<FAcquirePointByUserIdRequest> WithDuplicationAvoider(const TOptional<FString> DuplicationAvoider);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetUserId() const;
        TOptional<int64> GetPoint() const;
        FString GetPointString() const;
        TOptional<FString> GetTimeOffsetToken() const;
        TOptional<FString> GetDuplicationAvoider() const;

        static TSharedPtr<FAcquirePointByUserIdRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FAcquirePointByUserIdRequest> FAcquirePointByUserIdRequestPtr;
}