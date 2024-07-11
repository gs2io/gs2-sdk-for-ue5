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

#include "Account/Model/Gs2AccountEzPlatformUser.h"

namespace Gs2::UE5::Account::Model
{

    TSharedPtr<FEzPlatformUser> FEzPlatformUser::WithType(
        const TOptional<int32> Type
    )
    {
        this->TypeValue = Type;
        return SharedThis(this);
    }

    TSharedPtr<FEzPlatformUser> FEzPlatformUser::WithUserIdentifier(
        const TOptional<FString> UserIdentifier
    )
    {
        this->UserIdentifierValue = UserIdentifier;
        return SharedThis(this);
    }

    TSharedPtr<FEzPlatformUser> FEzPlatformUser::WithUserId(
        const TOptional<FString> UserId
    )
    {
        this->UserIdValue = UserId;
        return SharedThis(this);
    }
    TOptional<int32> FEzPlatformUser::GetType() const
    {
        return TypeValue;
    }

    FString FEzPlatformUser::GetTypeString() const
    {
        if (!TypeValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%d"), TypeValue.GetValue());
    }
    TOptional<FString> FEzPlatformUser::GetUserIdentifier() const
    {
        return UserIdentifierValue;
    }
    TOptional<FString> FEzPlatformUser::GetUserId() const
    {
        return UserIdValue;
    }

    Gs2::Account::Model::FPlatformUserPtr FEzPlatformUser::ToModel() const
    {
        return MakeShared<Gs2::Account::Model::FPlatformUser>()
            ->WithType(TypeValue)
            ->WithUserIdentifier(UserIdentifierValue)
            ->WithUserId(UserIdValue);
    }

    TSharedPtr<FEzPlatformUser> FEzPlatformUser::FromModel(const Gs2::Account::Model::FPlatformUserPtr Model)
    {
        if (Model == nullptr)
        {
            return nullptr;
        }
        return MakeShared<FEzPlatformUser>()
            ->WithType(Model->GetType())
            ->WithUserIdentifier(Model->GetUserIdentifier())
            ->WithUserId(Model->GetUserId());
    }
}