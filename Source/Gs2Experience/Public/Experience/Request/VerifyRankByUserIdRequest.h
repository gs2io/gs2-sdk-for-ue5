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

namespace Gs2::Experience::Request
{
    class FVerifyRankByUserIdRequest;

    class GS2EXPERIENCE_API FVerifyRankByUserIdRequest final : public TSharedFromThis<FVerifyRankByUserIdRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> UserIdValue;
        TOptional<FString> ExperienceNameValue;
        TOptional<FString> VerifyTypeValue;
        TOptional<FString> PropertyIdValue;
        TOptional<int64> RankValueValue;
        TOptional<bool> MultiplyValueSpecifyingQuantityValue;
        TOptional<FString> TimeOffsetTokenValue;
        TOptional<FString> DuplicationAvoiderValue;
        
    public:
        
        FVerifyRankByUserIdRequest();
        FVerifyRankByUserIdRequest(
            const FVerifyRankByUserIdRequest& From
        );
        ~FVerifyRankByUserIdRequest() = default;

        TSharedPtr<FVerifyRankByUserIdRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FVerifyRankByUserIdRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FVerifyRankByUserIdRequest> WithUserId(const TOptional<FString> UserId);
        TSharedPtr<FVerifyRankByUserIdRequest> WithExperienceName(const TOptional<FString> ExperienceName);
        TSharedPtr<FVerifyRankByUserIdRequest> WithVerifyType(const TOptional<FString> VerifyType);
        TSharedPtr<FVerifyRankByUserIdRequest> WithPropertyId(const TOptional<FString> PropertyId);
        TSharedPtr<FVerifyRankByUserIdRequest> WithRankValue(const TOptional<int64> RankValue);
        TSharedPtr<FVerifyRankByUserIdRequest> WithMultiplyValueSpecifyingQuantity(const TOptional<bool> MultiplyValueSpecifyingQuantity);
        TSharedPtr<FVerifyRankByUserIdRequest> WithTimeOffsetToken(const TOptional<FString> TimeOffsetToken);
        TSharedPtr<FVerifyRankByUserIdRequest> WithDuplicationAvoider(const TOptional<FString> DuplicationAvoider);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetUserId() const;
        TOptional<FString> GetExperienceName() const;
        TOptional<FString> GetVerifyType() const;
        TOptional<FString> GetPropertyId() const;
        TOptional<int64> GetRankValue() const;
        FString GetRankValueString() const;
        TOptional<bool> GetMultiplyValueSpecifyingQuantity() const;
        FString GetMultiplyValueSpecifyingQuantityString() const;
        TOptional<FString> GetTimeOffsetToken() const;
        TOptional<FString> GetDuplicationAvoider() const;

        static TSharedPtr<FVerifyRankByUserIdRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FVerifyRankByUserIdRequest> FVerifyRankByUserIdRequestPtr;
}