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
    class FSubExperienceByUserIdRequest;

    class GS2EXPERIENCE_API FSubExperienceByUserIdRequest final : public TSharedFromThis<FSubExperienceByUserIdRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> UserIdValue;
        TOptional<FString> ExperienceNameValue;
        TOptional<FString> PropertyIdValue;
        TOptional<int64> ExperienceValueValue;
        TOptional<FString> DuplicationAvoiderValue;
        
    public:
        
        FSubExperienceByUserIdRequest();
        FSubExperienceByUserIdRequest(
            const FSubExperienceByUserIdRequest& From
        );
        ~FSubExperienceByUserIdRequest() = default;

        TSharedPtr<FSubExperienceByUserIdRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FSubExperienceByUserIdRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FSubExperienceByUserIdRequest> WithUserId(const TOptional<FString> UserId);
        TSharedPtr<FSubExperienceByUserIdRequest> WithExperienceName(const TOptional<FString> ExperienceName);
        TSharedPtr<FSubExperienceByUserIdRequest> WithPropertyId(const TOptional<FString> PropertyId);
        TSharedPtr<FSubExperienceByUserIdRequest> WithExperienceValue(const TOptional<int64> ExperienceValue);
        TSharedPtr<FSubExperienceByUserIdRequest> WithDuplicationAvoider(const TOptional<FString> DuplicationAvoider);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetUserId() const;
        TOptional<FString> GetExperienceName() const;
        TOptional<FString> GetPropertyId() const;
        TOptional<int64> GetExperienceValue() const;
        FString GetExperienceValueString() const;
        TOptional<FString> GetDuplicationAvoider() const;

        static TSharedPtr<FSubExperienceByUserIdRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FSubExperienceByUserIdRequest, ESPMode::ThreadSafe> FSubExperienceByUserIdRequestPtr;
}