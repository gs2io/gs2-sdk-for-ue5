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

namespace Gs2::Identifier::Model
{
    class GS2IDENTIFIER_API FAttachSecurityPolicy final : public TSharedFromThis<FAttachSecurityPolicy>
    {
        TOptional<FString> UserIdValue;
        TSharedPtr<TArray<FString>> SecurityPolicyIdsValue;
        TOptional<int64> AttachedAtValue;

    public:
        FAttachSecurityPolicy();
        FAttachSecurityPolicy(
            const FAttachSecurityPolicy& From
        );
        ~FAttachSecurityPolicy() = default;

        TSharedPtr<FAttachSecurityPolicy> WithUserId(const TOptional<FString> UserId);
        TSharedPtr<FAttachSecurityPolicy> WithSecurityPolicyIds(const TSharedPtr<TArray<FString>> SecurityPolicyIds);
        TSharedPtr<FAttachSecurityPolicy> WithAttachedAt(const TOptional<int64> AttachedAt);

        TOptional<FString> GetUserId() const;
        TSharedPtr<TArray<FString>> GetSecurityPolicyIds() const;
        TOptional<int64> GetAttachedAt() const;
        FString GetAttachedAtString() const;

        static TOptional<FString> GetOwnerIdFromGrn(const FString Grn);
        static TOptional<FString> GetUserNameFromGrn(const FString Grn);

        static TSharedPtr<FAttachSecurityPolicy> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;

        static FString TypeName;
    };
    typedef TSharedPtr<FAttachSecurityPolicy, ESPMode::ThreadSafe> FAttachSecurityPolicyPtr;
}