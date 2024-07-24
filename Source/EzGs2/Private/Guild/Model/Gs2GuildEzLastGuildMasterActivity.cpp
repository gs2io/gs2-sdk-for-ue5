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

#include "Guild/Model/Gs2GuildEzLastGuildMasterActivity.h"

namespace Gs2::UE5::Guild::Model
{

    TSharedPtr<FEzLastGuildMasterActivity> FEzLastGuildMasterActivity::WithUserId(
        const TOptional<FString> UserId
    )
    {
        this->UserIdValue = UserId;
        return SharedThis(this);
    }

    TSharedPtr<FEzLastGuildMasterActivity> FEzLastGuildMasterActivity::WithUpdatedAt(
        const TOptional<int64> UpdatedAt
    )
    {
        this->UpdatedAtValue = UpdatedAt;
        return SharedThis(this);
    }
    TOptional<FString> FEzLastGuildMasterActivity::GetUserId() const
    {
        return UserIdValue;
    }
    TOptional<int64> FEzLastGuildMasterActivity::GetUpdatedAt() const
    {
        return UpdatedAtValue;
    }

    FString FEzLastGuildMasterActivity::GetUpdatedAtString() const
    {
        if (!UpdatedAtValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), UpdatedAtValue.GetValue());
    }

    Gs2::Guild::Model::FLastGuildMasterActivityPtr FEzLastGuildMasterActivity::ToModel() const
    {
        return MakeShared<Gs2::Guild::Model::FLastGuildMasterActivity>()
            ->WithUserId(UserIdValue)
            ->WithUpdatedAt(UpdatedAtValue);
    }

    TSharedPtr<FEzLastGuildMasterActivity> FEzLastGuildMasterActivity::FromModel(const Gs2::Guild::Model::FLastGuildMasterActivityPtr Model)
    {
        if (Model == nullptr)
        {
            return nullptr;
        }
        return MakeShared<FEzLastGuildMasterActivity>()
            ->WithUserId(Model->GetUserId())
            ->WithUpdatedAt(Model->GetUpdatedAt());
    }
}