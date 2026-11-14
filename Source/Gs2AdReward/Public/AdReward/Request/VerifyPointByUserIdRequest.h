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
    class FVerifyPointByUserIdRequest;

    class GS2ADREWARD_API FVerifyPointByUserIdRequest final : public TSharedFromThis<FVerifyPointByUserIdRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> UserIdValue;
        TOptional<FString> VerifyTypeValue;
        TOptional<int64> PointValue;
        TOptional<bool> MultiplyValueSpecifyingQuantityValue;
        TOptional<FString> TimeOffsetTokenValue;
        TOptional<FString> DuplicationAvoiderValue;
        
    public:
        
        FVerifyPointByUserIdRequest();
        FVerifyPointByUserIdRequest(
            const FVerifyPointByUserIdRequest& From
        );
        ~FVerifyPointByUserIdRequest() = default;

        TSharedPtr<FVerifyPointByUserIdRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FVerifyPointByUserIdRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FVerifyPointByUserIdRequest> WithUserId(const TOptional<FString> UserId);
        TSharedPtr<FVerifyPointByUserIdRequest> WithVerifyType(const TOptional<FString> VerifyType);
        TSharedPtr<FVerifyPointByUserIdRequest> WithPoint(const TOptional<int64> Point);
        TSharedPtr<FVerifyPointByUserIdRequest> WithMultiplyValueSpecifyingQuantity(const TOptional<bool> MultiplyValueSpecifyingQuantity);
        TSharedPtr<FVerifyPointByUserIdRequest> WithTimeOffsetToken(const TOptional<FString> TimeOffsetToken);
        TSharedPtr<FVerifyPointByUserIdRequest> WithDuplicationAvoider(const TOptional<FString> DuplicationAvoider);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetUserId() const;
        TOptional<FString> GetVerifyType() const;
        TOptional<int64> GetPoint() const;
        FString GetPointString() const;
        TOptional<bool> GetMultiplyValueSpecifyingQuantity() const;
        FString GetMultiplyValueSpecifyingQuantityString() const;
        TOptional<FString> GetTimeOffsetToken() const;
        TOptional<FString> GetDuplicationAvoider() const;

        static TSharedPtr<FVerifyPointByUserIdRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FVerifyPointByUserIdRequest> FVerifyPointByUserIdRequestPtr;
}