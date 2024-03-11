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

namespace Gs2::Grade::Request
{
    class FDeleteStatusByUserIdRequest;

    class GS2GRADE_API FDeleteStatusByUserIdRequest final : public TSharedFromThis<FDeleteStatusByUserIdRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> UserIdValue;
        TOptional<FString> GradeNameValue;
        TOptional<FString> PropertyIdValue;
        TOptional<FString> TimeOffsetTokenValue;
        TOptional<FString> DuplicationAvoiderValue;
        
    public:
        
        FDeleteStatusByUserIdRequest();
        FDeleteStatusByUserIdRequest(
            const FDeleteStatusByUserIdRequest& From
        );
        ~FDeleteStatusByUserIdRequest() = default;

        TSharedPtr<FDeleteStatusByUserIdRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FDeleteStatusByUserIdRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FDeleteStatusByUserIdRequest> WithUserId(const TOptional<FString> UserId);
        TSharedPtr<FDeleteStatusByUserIdRequest> WithGradeName(const TOptional<FString> GradeName);
        TSharedPtr<FDeleteStatusByUserIdRequest> WithPropertyId(const TOptional<FString> PropertyId);
        TSharedPtr<FDeleteStatusByUserIdRequest> WithTimeOffsetToken(const TOptional<FString> TimeOffsetToken);
        TSharedPtr<FDeleteStatusByUserIdRequest> WithDuplicationAvoider(const TOptional<FString> DuplicationAvoider);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetUserId() const;
        TOptional<FString> GetGradeName() const;
        TOptional<FString> GetPropertyId() const;
        TOptional<FString> GetTimeOffsetToken() const;
        TOptional<FString> GetDuplicationAvoider() const;

        static TSharedPtr<FDeleteStatusByUserIdRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FDeleteStatusByUserIdRequest, ESPMode::ThreadSafe> FDeleteStatusByUserIdRequestPtr;
}