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

#include "Account/Model/Gs2AccountEzPlatformId.h"

namespace Gs2::UE5::Account::Model
{

    TSharedPtr<FEzPlatformId> FEzPlatformId::WithType(
        const TOptional<int32> Type
    )
    {
        this->TypeValue = Type;
        return SharedThis(this);
    }

    TSharedPtr<FEzPlatformId> FEzPlatformId::WithUserIdentifier(
        const TOptional<FString> UserIdentifier
    )
    {
        this->UserIdentifierValue = UserIdentifier;
        return SharedThis(this);
    }

    TSharedPtr<FEzPlatformId> FEzPlatformId::WithUserId(
        const TOptional<FString> UserId
    )
    {
        this->UserIdValue = UserId;
        return SharedThis(this);
    }

    TSharedPtr<FEzPlatformId> FEzPlatformId::WithCreatedAt(
        const TOptional<int64> CreatedAt
    )
    {
        this->CreatedAtValue = CreatedAt;
        return SharedThis(this);
    }
    TOptional<int32> FEzPlatformId::GetType() const
    {
        return TypeValue;
    }

    FString FEzPlatformId::GetTypeString() const
    {
        if (!TypeValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%d"), TypeValue.GetValue());
    }
    TOptional<FString> FEzPlatformId::GetUserIdentifier() const
    {
        return UserIdentifierValue;
    }
    TOptional<FString> FEzPlatformId::GetUserId() const
    {
        return UserIdValue;
    }
    TOptional<int64> FEzPlatformId::GetCreatedAt() const
    {
        return CreatedAtValue;
    }

    FString FEzPlatformId::GetCreatedAtString() const
    {
        if (!CreatedAtValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), CreatedAtValue.GetValue());
    }

    Gs2::Account::Model::FPlatformIdPtr FEzPlatformId::ToModel() const
    {
        return MakeShared<Gs2::Account::Model::FPlatformId>()
            ->WithType(TypeValue)
            ->WithUserIdentifier(UserIdentifierValue)
            ->WithUserId(UserIdValue)
            ->WithCreatedAt(CreatedAtValue);
    }

    TSharedPtr<FEzPlatformId> FEzPlatformId::FromModel(const Gs2::Account::Model::FPlatformIdPtr Model)
    {
        if (Model == nullptr)
        {
            return nullptr;
        }
        return MakeShared<FEzPlatformId>()
            ->WithType(Model->GetType())
            ->WithUserIdentifier(Model->GetUserIdentifier())
            ->WithUserId(Model->GetUserId())
            ->WithCreatedAt(Model->GetCreatedAt());
    }
}