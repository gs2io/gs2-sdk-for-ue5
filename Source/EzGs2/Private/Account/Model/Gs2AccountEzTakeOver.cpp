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

#include "EzGs2/Public/Account/Model/Gs2AccountEzTakeOver.h"

namespace Gs2::UE5::Account::Model
{

    TSharedPtr<FEzTakeOver> FEzTakeOver::WithUserId(
        const TOptional<FString> UserId
    )
    {
        this->UserIdValue = UserId;
        return SharedThis(this);
    }

    TSharedPtr<FEzTakeOver> FEzTakeOver::WithType(
        const TOptional<int32> Type
    )
    {
        this->TypeValue = Type;
        return SharedThis(this);
    }

    TSharedPtr<FEzTakeOver> FEzTakeOver::WithUserIdentifier(
        const TOptional<FString> UserIdentifier
    )
    {
        this->UserIdentifierValue = UserIdentifier;
        return SharedThis(this);
    }

    TSharedPtr<FEzTakeOver> FEzTakeOver::WithCreatedAt(
        const TOptional<int64> CreatedAt
    )
    {
        this->CreatedAtValue = CreatedAt;
        return SharedThis(this);
    }
    TOptional<FString> FEzTakeOver::GetUserId() const
    {
        return UserIdValue;
    }
    TOptional<int32> FEzTakeOver::GetType() const
    {
        return TypeValue;
    }

    FString FEzTakeOver::GetTypeString() const
    {
        if (!TypeValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%d"), TypeValue.GetValue());
    }
    TOptional<FString> FEzTakeOver::GetUserIdentifier() const
    {
        return UserIdentifierValue;
    }
    TOptional<int64> FEzTakeOver::GetCreatedAt() const
    {
        return CreatedAtValue;
    }

    FString FEzTakeOver::GetCreatedAtString() const
    {
        if (!CreatedAtValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), CreatedAtValue.GetValue());
    }

    Gs2::Account::Model::FTakeOverPtr FEzTakeOver::ToModel() const
    {
        return MakeShared<Gs2::Account::Model::FTakeOver>()
            ->WithUserId(UserIdValue)
            ->WithType(TypeValue)
            ->WithUserIdentifier(UserIdentifierValue)
            ->WithCreatedAt(CreatedAtValue);
    }

    TSharedPtr<FEzTakeOver> FEzTakeOver::FromModel(const Gs2::Account::Model::FTakeOverPtr Model)
    {
        if (Model == nullptr)
        {
            return nullptr;
        }
        return MakeShared<FEzTakeOver>()
            ->WithUserId(Model->GetUserId())
            ->WithType(Model->GetType())
            ->WithUserIdentifier(Model->GetUserIdentifier())
            ->WithCreatedAt(Model->GetCreatedAt());
    }
}