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
    class FSubExperienceRequest;

    class GS2EXPERIENCE_API FSubExperienceRequest final : public TSharedFromThis<FSubExperienceRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> AccessTokenValue;
        TOptional<FString> ExperienceNameValue;
        TOptional<FString> PropertyIdValue;
        TOptional<int64> ExperienceValueValue;
        TOptional<FString> DuplicationAvoiderValue;
        
    public:
        
        FSubExperienceRequest();
        FSubExperienceRequest(
            const FSubExperienceRequest& From
        );
        ~FSubExperienceRequest() = default;

        TSharedPtr<FSubExperienceRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FSubExperienceRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FSubExperienceRequest> WithAccessToken(const TOptional<FString> AccessToken);
        TSharedPtr<FSubExperienceRequest> WithExperienceName(const TOptional<FString> ExperienceName);
        TSharedPtr<FSubExperienceRequest> WithPropertyId(const TOptional<FString> PropertyId);
        TSharedPtr<FSubExperienceRequest> WithExperienceValue(const TOptional<int64> ExperienceValue);
        TSharedPtr<FSubExperienceRequest> WithDuplicationAvoider(const TOptional<FString> DuplicationAvoider);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetAccessToken() const;
        TOptional<FString> GetExperienceName() const;
        TOptional<FString> GetPropertyId() const;
        TOptional<int64> GetExperienceValue() const;
        FString GetExperienceValueString() const;
        TOptional<FString> GetDuplicationAvoider() const;

        static TSharedPtr<FSubExperienceRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FSubExperienceRequest, ESPMode::ThreadSafe> FSubExperienceRequestPtr;
}