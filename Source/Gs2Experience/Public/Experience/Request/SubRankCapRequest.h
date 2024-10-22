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
    class FSubRankCapRequest;

    class GS2EXPERIENCE_API FSubRankCapRequest final : public TSharedFromThis<FSubRankCapRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> AccessTokenValue;
        TOptional<FString> ExperienceNameValue;
        TOptional<FString> PropertyIdValue;
        TOptional<int64> RankCapValueValue;
        TOptional<FString> DuplicationAvoiderValue;
        
    public:
        
        FSubRankCapRequest();
        FSubRankCapRequest(
            const FSubRankCapRequest& From
        );
        ~FSubRankCapRequest() = default;

        TSharedPtr<FSubRankCapRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FSubRankCapRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FSubRankCapRequest> WithAccessToken(const TOptional<FString> AccessToken);
        TSharedPtr<FSubRankCapRequest> WithExperienceName(const TOptional<FString> ExperienceName);
        TSharedPtr<FSubRankCapRequest> WithPropertyId(const TOptional<FString> PropertyId);
        TSharedPtr<FSubRankCapRequest> WithRankCapValue(const TOptional<int64> RankCapValue);
        TSharedPtr<FSubRankCapRequest> WithDuplicationAvoider(const TOptional<FString> DuplicationAvoider);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetAccessToken() const;
        TOptional<FString> GetExperienceName() const;
        TOptional<FString> GetPropertyId() const;
        TOptional<int64> GetRankCapValue() const;
        FString GetRankCapValueString() const;
        TOptional<FString> GetDuplicationAvoider() const;

        static TSharedPtr<FSubRankCapRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FSubRankCapRequest> FSubRankCapRequestPtr;
}