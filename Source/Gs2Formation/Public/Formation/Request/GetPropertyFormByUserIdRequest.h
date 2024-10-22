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

namespace Gs2::Formation::Request
{
    class FGetPropertyFormByUserIdRequest;

    class GS2FORMATION_API FGetPropertyFormByUserIdRequest final : public TSharedFromThis<FGetPropertyFormByUserIdRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> UserIdValue;
        TOptional<FString> PropertyFormModelNameValue;
        TOptional<FString> PropertyIdValue;
        TOptional<FString> TimeOffsetTokenValue;
        
    public:
        
        FGetPropertyFormByUserIdRequest();
        FGetPropertyFormByUserIdRequest(
            const FGetPropertyFormByUserIdRequest& From
        );
        ~FGetPropertyFormByUserIdRequest() = default;

        TSharedPtr<FGetPropertyFormByUserIdRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FGetPropertyFormByUserIdRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FGetPropertyFormByUserIdRequest> WithUserId(const TOptional<FString> UserId);
        TSharedPtr<FGetPropertyFormByUserIdRequest> WithPropertyFormModelName(const TOptional<FString> PropertyFormModelName);
        TSharedPtr<FGetPropertyFormByUserIdRequest> WithPropertyId(const TOptional<FString> PropertyId);
        TSharedPtr<FGetPropertyFormByUserIdRequest> WithTimeOffsetToken(const TOptional<FString> TimeOffsetToken);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetUserId() const;
        TOptional<FString> GetPropertyFormModelName() const;
        TOptional<FString> GetPropertyId() const;
        TOptional<FString> GetTimeOffsetToken() const;

        static TSharedPtr<FGetPropertyFormByUserIdRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FGetPropertyFormByUserIdRequest> FGetPropertyFormByUserIdRequestPtr;
}