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
#include "Account/Model/Account.h"

namespace Gs2::UE5::Account::Model
{
	class EZGS2_API FEzAccount final : public TSharedFromThis<FEzAccount>
	{
        TOptional<FString> UserIdValue;
        TOptional<FString> PasswordValue;
        TOptional<int64> CreatedAtValue;

	public:
        TSharedPtr<FEzAccount> WithUserId(const TOptional<FString> UserId);
        TSharedPtr<FEzAccount> WithPassword(const TOptional<FString> Password);
        TSharedPtr<FEzAccount> WithCreatedAt(const TOptional<int64> CreatedAt);

        TOptional<FString> GetUserId() const;

        TOptional<FString> GetPassword() const;

        TOptional<int64> GetCreatedAt() const;
        FString GetCreatedAtString() const;

        Gs2::Account::Model::FAccountPtr ToModel() const;
        static TSharedPtr<FEzAccount> FromModel(Gs2::Account::Model::FAccountPtr Model);
    };
    typedef TSharedPtr<FEzAccount> FEzAccountPtr;
}