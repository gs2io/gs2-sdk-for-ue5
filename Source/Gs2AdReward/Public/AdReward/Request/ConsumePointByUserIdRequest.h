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
    class FConsumePointByUserIdRequest;

    class GS2ADREWARD_API FConsumePointByUserIdRequest final : public TSharedFromThis<FConsumePointByUserIdRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> UserIdValue;
        TOptional<int64> PointValue;
        TOptional<FString> TimeOffsetTokenValue;
        TOptional<FString> DuplicationAvoiderValue;
        
    public:
        
        FConsumePointByUserIdRequest();
        FConsumePointByUserIdRequest(
            const FConsumePointByUserIdRequest& From
        );
        ~FConsumePointByUserIdRequest() = default;

        TSharedPtr<FConsumePointByUserIdRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FConsumePointByUserIdRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FConsumePointByUserIdRequest> WithUserId(const TOptional<FString> UserId);
        TSharedPtr<FConsumePointByUserIdRequest> WithPoint(const TOptional<int64> Point);
        TSharedPtr<FConsumePointByUserIdRequest> WithTimeOffsetToken(const TOptional<FString> TimeOffsetToken);
        TSharedPtr<FConsumePointByUserIdRequest> WithDuplicationAvoider(const TOptional<FString> DuplicationAvoider);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetUserId() const;
        TOptional<int64> GetPoint() const;
        FString GetPointString() const;
        TOptional<FString> GetTimeOffsetToken() const;
        TOptional<FString> GetDuplicationAvoider() const;

        static TSharedPtr<FConsumePointByUserIdRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FConsumePointByUserIdRequest> FConsumePointByUserIdRequestPtr;
}