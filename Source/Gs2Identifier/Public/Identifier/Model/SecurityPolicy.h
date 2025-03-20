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
#include "Core/Gs2Object.h"

namespace Gs2::Identifier::Model
{
    class GS2IDENTIFIER_API FSecurityPolicy final : public FGs2Object, public TSharedFromThis<FSecurityPolicy>
    {
        TOptional<FString> SecurityPolicyIdValue;
        TOptional<FString> NameValue;
        TOptional<FString> DescriptionValue;
        TOptional<FString> PolicyValue;
        TOptional<int64> CreatedAtValue;
        TOptional<int64> UpdatedAtValue;

    public:
        FSecurityPolicy();
        FSecurityPolicy(
            const FSecurityPolicy& From
        );
        virtual ~FSecurityPolicy() override = default;

        TSharedPtr<FSecurityPolicy> WithSecurityPolicyId(const TOptional<FString> SecurityPolicyId);
        TSharedPtr<FSecurityPolicy> WithName(const TOptional<FString> Name);
        TSharedPtr<FSecurityPolicy> WithDescription(const TOptional<FString> Description);
        TSharedPtr<FSecurityPolicy> WithPolicy(const TOptional<FString> Policy);
        TSharedPtr<FSecurityPolicy> WithCreatedAt(const TOptional<int64> CreatedAt);
        TSharedPtr<FSecurityPolicy> WithUpdatedAt(const TOptional<int64> UpdatedAt);

        TOptional<FString> GetSecurityPolicyId() const;
        TOptional<FString> GetName() const;
        TOptional<FString> GetDescription() const;
        TOptional<FString> GetPolicy() const;
        TOptional<int64> GetCreatedAt() const;
        FString GetCreatedAtString() const;
        TOptional<int64> GetUpdatedAt() const;
        FString GetUpdatedAtString() const;

        static TOptional<FString> GetOwnerIdFromGrn(const FString Grn);
        static TOptional<FString> GetSecurityPolicyNameFromGrn(const FString Grn);

        static TSharedPtr<FSecurityPolicy> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;

        static FString TypeName;
    };
    typedef TSharedPtr<FSecurityPolicy, ESPMode::ThreadSafe> FSecurityPolicyPtr;
}