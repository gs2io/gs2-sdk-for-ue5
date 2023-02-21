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
    class GS2IDENTIFIER_API FUser final : public TSharedFromThis<FUser>
    {
        TOptional<FString> UserIdValue;
        TOptional<FString> NameValue;
        TOptional<FString> DescriptionValue;
        TOptional<int64> CreatedAtValue;
        TOptional<int64> UpdatedAtValue;

    public:
        FUser();
        FUser(
            const FUser& From
        );
        ~FUser() = default;

        TSharedPtr<FUser> WithUserId(const TOptional<FString> UserId);
        TSharedPtr<FUser> WithName(const TOptional<FString> Name);
        TSharedPtr<FUser> WithDescription(const TOptional<FString> Description);
        TSharedPtr<FUser> WithCreatedAt(const TOptional<int64> CreatedAt);
        TSharedPtr<FUser> WithUpdatedAt(const TOptional<int64> UpdatedAt);

        TOptional<FString> GetUserId() const;
        TOptional<FString> GetName() const;
        TOptional<FString> GetDescription() const;
        TOptional<int64> GetCreatedAt() const;
        FString GetCreatedAtString() const;
        TOptional<int64> GetUpdatedAt() const;
        FString GetUpdatedAtString() const;

        static TOptional<FString> GetOwnerIdFromGrn(const FString Grn);
        static TOptional<FString> GetUserNameFromGrn(const FString Grn);

        static TSharedPtr<FUser> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;

        static FString TypeName;
    };
    typedef TSharedPtr<FUser, ESPMode::ThreadSafe> FUserPtr;
}