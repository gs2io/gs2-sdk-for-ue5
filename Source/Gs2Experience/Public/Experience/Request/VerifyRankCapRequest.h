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
    class FVerifyRankCapRequest;

    class GS2EXPERIENCE_API FVerifyRankCapRequest final : public TSharedFromThis<FVerifyRankCapRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> AccessTokenValue;
        TOptional<FString> ExperienceNameValue;
        TOptional<FString> VerifyTypeValue;
        TOptional<FString> PropertyIdValue;
        TOptional<int64> RankCapValueValue;
        TOptional<FString> DuplicationAvoiderValue;
        
    public:
        
        FVerifyRankCapRequest();
        FVerifyRankCapRequest(
            const FVerifyRankCapRequest& From
        );
        ~FVerifyRankCapRequest() = default;

        TSharedPtr<FVerifyRankCapRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FVerifyRankCapRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FVerifyRankCapRequest> WithAccessToken(const TOptional<FString> AccessToken);
        TSharedPtr<FVerifyRankCapRequest> WithExperienceName(const TOptional<FString> ExperienceName);
        TSharedPtr<FVerifyRankCapRequest> WithVerifyType(const TOptional<FString> VerifyType);
        TSharedPtr<FVerifyRankCapRequest> WithPropertyId(const TOptional<FString> PropertyId);
        TSharedPtr<FVerifyRankCapRequest> WithRankCapValue(const TOptional<int64> RankCapValue);
        TSharedPtr<FVerifyRankCapRequest> WithDuplicationAvoider(const TOptional<FString> DuplicationAvoider);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetAccessToken() const;
        TOptional<FString> GetExperienceName() const;
        TOptional<FString> GetVerifyType() const;
        TOptional<FString> GetPropertyId() const;
        TOptional<int64> GetRankCapValue() const;
        FString GetRankCapValueString() const;
        TOptional<FString> GetDuplicationAvoider() const;

        static TSharedPtr<FVerifyRankCapRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FVerifyRankCapRequest, ESPMode::ThreadSafe> FVerifyRankCapRequestPtr;
}