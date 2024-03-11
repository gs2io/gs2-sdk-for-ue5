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

namespace Gs2::Experience::Request
{
    class FVerifyRankCapByUserIdRequest;

    class GS2EXPERIENCE_API FVerifyRankCapByUserIdRequest final : public TSharedFromThis<FVerifyRankCapByUserIdRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> UserIdValue;
        TOptional<FString> ExperienceNameValue;
        TOptional<FString> VerifyTypeValue;
        TOptional<FString> PropertyIdValue;
        TOptional<int64> RankCapValueValue;
        TOptional<bool> MultiplyValueSpecifyingQuantityValue;
        TOptional<FString> TimeOffsetTokenValue;
        TOptional<FString> DuplicationAvoiderValue;
        
    public:
        
        FVerifyRankCapByUserIdRequest();
        FVerifyRankCapByUserIdRequest(
            const FVerifyRankCapByUserIdRequest& From
        );
        ~FVerifyRankCapByUserIdRequest() = default;

        TSharedPtr<FVerifyRankCapByUserIdRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FVerifyRankCapByUserIdRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FVerifyRankCapByUserIdRequest> WithUserId(const TOptional<FString> UserId);
        TSharedPtr<FVerifyRankCapByUserIdRequest> WithExperienceName(const TOptional<FString> ExperienceName);
        TSharedPtr<FVerifyRankCapByUserIdRequest> WithVerifyType(const TOptional<FString> VerifyType);
        TSharedPtr<FVerifyRankCapByUserIdRequest> WithPropertyId(const TOptional<FString> PropertyId);
        TSharedPtr<FVerifyRankCapByUserIdRequest> WithRankCapValue(const TOptional<int64> RankCapValue);
        TSharedPtr<FVerifyRankCapByUserIdRequest> WithMultiplyValueSpecifyingQuantity(const TOptional<bool> MultiplyValueSpecifyingQuantity);
        TSharedPtr<FVerifyRankCapByUserIdRequest> WithTimeOffsetToken(const TOptional<FString> TimeOffsetToken);
        TSharedPtr<FVerifyRankCapByUserIdRequest> WithDuplicationAvoider(const TOptional<FString> DuplicationAvoider);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetUserId() const;
        TOptional<FString> GetExperienceName() const;
        TOptional<FString> GetVerifyType() const;
        TOptional<FString> GetPropertyId() const;
        TOptional<int64> GetRankCapValue() const;
        FString GetRankCapValueString() const;
        TOptional<bool> GetMultiplyValueSpecifyingQuantity() const;
        FString GetMultiplyValueSpecifyingQuantityString() const;
        TOptional<FString> GetTimeOffsetToken() const;
        TOptional<FString> GetDuplicationAvoider() const;

        static TSharedPtr<FVerifyRankCapByUserIdRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FVerifyRankCapByUserIdRequest, ESPMode::ThreadSafe> FVerifyRankCapByUserIdRequestPtr;
}