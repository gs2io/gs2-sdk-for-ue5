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

namespace Gs2::Account::Model
{
    class GS2ACCOUNT_API FAccount final : public TSharedFromThis<FAccount>
    {
        TOptional<FString> AccountIdValue;
        TOptional<FString> UserIdValue;
        TOptional<FString> PasswordValue;
        TOptional<int32> TimeOffsetValue;
        TOptional<bool> BannedValue;
        TOptional<int64> CreatedAtValue;

    public:
        FAccount();
        FAccount(
            const FAccount& From
        );
        ~FAccount() = default;

        TSharedPtr<FAccount> WithAccountId(const TOptional<FString> AccountId);
        TSharedPtr<FAccount> WithUserId(const TOptional<FString> UserId);
        TSharedPtr<FAccount> WithPassword(const TOptional<FString> Password);
        TSharedPtr<FAccount> WithTimeOffset(const TOptional<int32> TimeOffset);
        TSharedPtr<FAccount> WithBanned(const TOptional<bool> Banned);
        TSharedPtr<FAccount> WithCreatedAt(const TOptional<int64> CreatedAt);

        TOptional<FString> GetAccountId() const;
        TOptional<FString> GetUserId() const;
        TOptional<FString> GetPassword() const;
        TOptional<int32> GetTimeOffset() const;
        FString GetTimeOffsetString() const;
        TOptional<bool> GetBanned() const;
        FString GetBannedString() const;
        TOptional<int64> GetCreatedAt() const;
        FString GetCreatedAtString() const;

        static TOptional<FString> GetRegionFromGrn(const FString Grn);
        static TOptional<FString> GetOwnerIdFromGrn(const FString Grn);
        static TOptional<FString> GetNamespaceNameFromGrn(const FString Grn);
        static TOptional<FString> GetUserIdFromGrn(const FString Grn);

        static TSharedPtr<FAccount> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;

        static FString TypeName;
    };
    typedef TSharedPtr<FAccount, ESPMode::ThreadSafe> FAccountPtr;
}