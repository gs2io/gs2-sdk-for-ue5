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
    class FVerifyRankRequest;

    class GS2EXPERIENCE_API FVerifyRankRequest final : public TSharedFromThis<FVerifyRankRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> AccessTokenValue;
        TOptional<FString> ExperienceNameValue;
        TOptional<FString> VerifyTypeValue;
        TOptional<FString> PropertyIdValue;
        TOptional<int64> RankValueValue;
        TOptional<bool> MultiplyValueSpecifyingQuantityValue;
        TOptional<FString> DuplicationAvoiderValue;
        
    public:
        
        FVerifyRankRequest();
        FVerifyRankRequest(
            const FVerifyRankRequest& From
        );
        ~FVerifyRankRequest() = default;

        TSharedPtr<FVerifyRankRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FVerifyRankRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FVerifyRankRequest> WithAccessToken(const TOptional<FString> AccessToken);
        TSharedPtr<FVerifyRankRequest> WithExperienceName(const TOptional<FString> ExperienceName);
        TSharedPtr<FVerifyRankRequest> WithVerifyType(const TOptional<FString> VerifyType);
        TSharedPtr<FVerifyRankRequest> WithPropertyId(const TOptional<FString> PropertyId);
        TSharedPtr<FVerifyRankRequest> WithRankValue(const TOptional<int64> RankValue);
        TSharedPtr<FVerifyRankRequest> WithMultiplyValueSpecifyingQuantity(const TOptional<bool> MultiplyValueSpecifyingQuantity);
        TSharedPtr<FVerifyRankRequest> WithDuplicationAvoider(const TOptional<FString> DuplicationAvoider);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetAccessToken() const;
        TOptional<FString> GetExperienceName() const;
        TOptional<FString> GetVerifyType() const;
        TOptional<FString> GetPropertyId() const;
        TOptional<int64> GetRankValue() const;
        FString GetRankValueString() const;
        TOptional<bool> GetMultiplyValueSpecifyingQuantity() const;
        FString GetMultiplyValueSpecifyingQuantityString() const;
        TOptional<FString> GetDuplicationAvoider() const;

        static TSharedPtr<FVerifyRankRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FVerifyRankRequest, ESPMode::ThreadSafe> FVerifyRankRequestPtr;
}