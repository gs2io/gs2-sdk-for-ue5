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

namespace Gs2::Formation::Request
{
    class FDeletePropertyFormByUserIdRequest;

    class GS2FORMATION_API FDeletePropertyFormByUserIdRequest final : public TSharedFromThis<FDeletePropertyFormByUserIdRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> UserIdValue;
        TOptional<FString> PropertyFormModelNameValue;
        TOptional<FString> PropertyIdValue;
        TOptional<FString> TimeOffsetTokenValue;
        TOptional<FString> DuplicationAvoiderValue;
        
    public:
        
        FDeletePropertyFormByUserIdRequest();
        FDeletePropertyFormByUserIdRequest(
            const FDeletePropertyFormByUserIdRequest& From
        );
        ~FDeletePropertyFormByUserIdRequest() = default;

        TSharedPtr<FDeletePropertyFormByUserIdRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FDeletePropertyFormByUserIdRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FDeletePropertyFormByUserIdRequest> WithUserId(const TOptional<FString> UserId);
        TSharedPtr<FDeletePropertyFormByUserIdRequest> WithPropertyFormModelName(const TOptional<FString> PropertyFormModelName);
        TSharedPtr<FDeletePropertyFormByUserIdRequest> WithPropertyId(const TOptional<FString> PropertyId);
        TSharedPtr<FDeletePropertyFormByUserIdRequest> WithTimeOffsetToken(const TOptional<FString> TimeOffsetToken);
        TSharedPtr<FDeletePropertyFormByUserIdRequest> WithDuplicationAvoider(const TOptional<FString> DuplicationAvoider);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetUserId() const;
        TOptional<FString> GetPropertyFormModelName() const;
        TOptional<FString> GetPropertyId() const;
        TOptional<FString> GetTimeOffsetToken() const;
        TOptional<FString> GetDuplicationAvoider() const;

        static TSharedPtr<FDeletePropertyFormByUserIdRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FDeletePropertyFormByUserIdRequest, ESPMode::ThreadSafe> FDeletePropertyFormByUserIdRequestPtr;
}