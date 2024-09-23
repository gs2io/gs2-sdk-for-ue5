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
    class FAddExperienceByUserIdRequest;

    class GS2EXPERIENCE_API FAddExperienceByUserIdRequest final : public TSharedFromThis<FAddExperienceByUserIdRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> UserIdValue;
        TOptional<FString> ExperienceNameValue;
        TOptional<FString> PropertyIdValue;
        TOptional<int64> ExperienceValueValue;
        TOptional<bool> TruncateExperienceWhenRankUpValue;
        TOptional<FString> TimeOffsetTokenValue;
        TOptional<FString> DuplicationAvoiderValue;
        
    public:
        
        FAddExperienceByUserIdRequest();
        FAddExperienceByUserIdRequest(
            const FAddExperienceByUserIdRequest& From
        );
        ~FAddExperienceByUserIdRequest() = default;

        TSharedPtr<FAddExperienceByUserIdRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FAddExperienceByUserIdRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FAddExperienceByUserIdRequest> WithUserId(const TOptional<FString> UserId);
        TSharedPtr<FAddExperienceByUserIdRequest> WithExperienceName(const TOptional<FString> ExperienceName);
        TSharedPtr<FAddExperienceByUserIdRequest> WithPropertyId(const TOptional<FString> PropertyId);
        TSharedPtr<FAddExperienceByUserIdRequest> WithExperienceValue(const TOptional<int64> ExperienceValue);
        TSharedPtr<FAddExperienceByUserIdRequest> WithTruncateExperienceWhenRankUp(const TOptional<bool> TruncateExperienceWhenRankUp);
        TSharedPtr<FAddExperienceByUserIdRequest> WithTimeOffsetToken(const TOptional<FString> TimeOffsetToken);
        TSharedPtr<FAddExperienceByUserIdRequest> WithDuplicationAvoider(const TOptional<FString> DuplicationAvoider);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetUserId() const;
        TOptional<FString> GetExperienceName() const;
        TOptional<FString> GetPropertyId() const;
        TOptional<int64> GetExperienceValue() const;
        FString GetExperienceValueString() const;
        TOptional<bool> GetTruncateExperienceWhenRankUp() const;
        FString GetTruncateExperienceWhenRankUpString() const;
        TOptional<FString> GetTimeOffsetToken() const;
        TOptional<FString> GetDuplicationAvoider() const;

        static TSharedPtr<FAddExperienceByUserIdRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FAddExperienceByUserIdRequest, ESPMode::ThreadSafe> FAddExperienceByUserIdRequestPtr;
}