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
    class FSetRankCapByUserIdRequest;

    class GS2EXPERIENCE_API FSetRankCapByUserIdRequest final : public TSharedFromThis<FSetRankCapByUserIdRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> UserIdValue;
        TOptional<FString> ExperienceNameValue;
        TOptional<FString> PropertyIdValue;
        TOptional<int64> RankCapValueValue;
        TOptional<FString> TimeOffsetTokenValue;
        TOptional<FString> DuplicationAvoiderValue;
        
    public:
        
        FSetRankCapByUserIdRequest();
        FSetRankCapByUserIdRequest(
            const FSetRankCapByUserIdRequest& From
        );
        ~FSetRankCapByUserIdRequest() = default;

        TSharedPtr<FSetRankCapByUserIdRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FSetRankCapByUserIdRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FSetRankCapByUserIdRequest> WithUserId(const TOptional<FString> UserId);
        TSharedPtr<FSetRankCapByUserIdRequest> WithExperienceName(const TOptional<FString> ExperienceName);
        TSharedPtr<FSetRankCapByUserIdRequest> WithPropertyId(const TOptional<FString> PropertyId);
        TSharedPtr<FSetRankCapByUserIdRequest> WithRankCapValue(const TOptional<int64> RankCapValue);
        TSharedPtr<FSetRankCapByUserIdRequest> WithTimeOffsetToken(const TOptional<FString> TimeOffsetToken);
        TSharedPtr<FSetRankCapByUserIdRequest> WithDuplicationAvoider(const TOptional<FString> DuplicationAvoider);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetUserId() const;
        TOptional<FString> GetExperienceName() const;
        TOptional<FString> GetPropertyId() const;
        TOptional<int64> GetRankCapValue() const;
        FString GetRankCapValueString() const;
        TOptional<FString> GetTimeOffsetToken() const;
        TOptional<FString> GetDuplicationAvoider() const;

        static TSharedPtr<FSetRankCapByUserIdRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FSetRankCapByUserIdRequest, ESPMode::ThreadSafe> FSetRankCapByUserIdRequestPtr;
}