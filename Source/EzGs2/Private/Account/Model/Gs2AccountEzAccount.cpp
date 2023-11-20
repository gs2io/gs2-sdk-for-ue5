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

#include "Account/Model/Gs2AccountEzAccount.h"

namespace Gs2::UE5::Account::Model
{

    TSharedPtr<FEzAccount> FEzAccount::WithUserId(
        const TOptional<FString> UserId
    )
    {
        this->UserIdValue = UserId;
        return SharedThis(this);
    }

    TSharedPtr<FEzAccount> FEzAccount::WithPassword(
        const TOptional<FString> Password
    )
    {
        this->PasswordValue = Password;
        return SharedThis(this);
    }

    TSharedPtr<FEzAccount> FEzAccount::WithCreatedAt(
        const TOptional<int64> CreatedAt
    )
    {
        this->CreatedAtValue = CreatedAt;
        return SharedThis(this);
    }
    TOptional<FString> FEzAccount::GetUserId() const
    {
        return UserIdValue;
    }
    TOptional<FString> FEzAccount::GetPassword() const
    {
        return PasswordValue;
    }
    TOptional<int64> FEzAccount::GetCreatedAt() const
    {
        return CreatedAtValue;
    }

    FString FEzAccount::GetCreatedAtString() const
    {
        if (!CreatedAtValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), CreatedAtValue.GetValue());
    }

    Gs2::Account::Model::FAccountPtr FEzAccount::ToModel() const
    {
        return MakeShared<Gs2::Account::Model::FAccount>()
            ->WithUserId(UserIdValue)
            ->WithPassword(PasswordValue)
            ->WithCreatedAt(CreatedAtValue);
    }

    TSharedPtr<FEzAccount> FEzAccount::FromModel(const Gs2::Account::Model::FAccountPtr Model)
    {
        if (Model == nullptr)
        {
            return nullptr;
        }
        return MakeShared<FEzAccount>()
            ->WithUserId(Model->GetUserId())
            ->WithPassword(Model->GetPassword())
            ->WithCreatedAt(Model->GetCreatedAt());
    }
}