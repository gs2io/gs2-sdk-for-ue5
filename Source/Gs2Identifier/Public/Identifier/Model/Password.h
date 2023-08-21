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
    class GS2IDENTIFIER_API FPassword final : public Gs2Object, public TSharedFromThis<FPassword>
    {
        TOptional<FString> PasswordIdValue;
        TOptional<FString> UserIdValue;
        TOptional<FString> UserNameValue;
        TOptional<int64> CreatedAtValue;
        TOptional<int64> RevisionValue;

    public:
        FPassword();
        FPassword(
            const FPassword& From
        );
        virtual ~FPassword() override = default;

        TSharedPtr<FPassword> WithPasswordId(const TOptional<FString> PasswordId);
        TSharedPtr<FPassword> WithUserId(const TOptional<FString> UserId);
        TSharedPtr<FPassword> WithUserName(const TOptional<FString> UserName);
        TSharedPtr<FPassword> WithCreatedAt(const TOptional<int64> CreatedAt);
        TSharedPtr<FPassword> WithRevision(const TOptional<int64> Revision);

        TOptional<FString> GetPasswordId() const;
        TOptional<FString> GetUserId() const;
        TOptional<FString> GetUserName() const;
        TOptional<int64> GetCreatedAt() const;
        FString GetCreatedAtString() const;
        TOptional<int64> GetRevision() const;
        FString GetRevisionString() const;

        static TOptional<FString> GetOwnerIdFromGrn(const FString Grn);
        static TOptional<FString> GetUserNameFromGrn(const FString Grn);

        static TSharedPtr<FPassword> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;

        static FString TypeName;
    };
    typedef TSharedPtr<FPassword, ESPMode::ThreadSafe> FPasswordPtr;
}