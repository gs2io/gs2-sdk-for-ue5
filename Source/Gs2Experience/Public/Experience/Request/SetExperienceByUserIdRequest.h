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
    class FSetExperienceByUserIdRequest;

    class GS2EXPERIENCE_API FSetExperienceByUserIdRequest final : public TSharedFromThis<FSetExperienceByUserIdRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> UserIdValue;
        TOptional<FString> ExperienceNameValue;
        TOptional<FString> PropertyIdValue;
        TOptional<int64> ExperienceValueValue;
        TOptional<FString> TimeOffsetTokenValue;
        TOptional<FString> DuplicationAvoiderValue;
        
    public:
        
        FSetExperienceByUserIdRequest();
        FSetExperienceByUserIdRequest(
            const FSetExperienceByUserIdRequest& From
        );
        ~FSetExperienceByUserIdRequest() = default;

        TSharedPtr<FSetExperienceByUserIdRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FSetExperienceByUserIdRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FSetExperienceByUserIdRequest> WithUserId(const TOptional<FString> UserId);
        TSharedPtr<FSetExperienceByUserIdRequest> WithExperienceName(const TOptional<FString> ExperienceName);
        TSharedPtr<FSetExperienceByUserIdRequest> WithPropertyId(const TOptional<FString> PropertyId);
        TSharedPtr<FSetExperienceByUserIdRequest> WithExperienceValue(const TOptional<int64> ExperienceValue);
        TSharedPtr<FSetExperienceByUserIdRequest> WithTimeOffsetToken(const TOptional<FString> TimeOffsetToken);
        TSharedPtr<FSetExperienceByUserIdRequest> WithDuplicationAvoider(const TOptional<FString> DuplicationAvoider);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetUserId() const;
        TOptional<FString> GetExperienceName() const;
        TOptional<FString> GetPropertyId() const;
        TOptional<int64> GetExperienceValue() const;
        FString GetExperienceValueString() const;
        TOptional<FString> GetTimeOffsetToken() const;
        TOptional<FString> GetDuplicationAvoider() const;

        static TSharedPtr<FSetExperienceByUserIdRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FSetExperienceByUserIdRequest, ESPMode::ThreadSafe> FSetExperienceByUserIdRequestPtr;
}