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

#include "Guild/Model/Gs2GuildEzIgnoreUser.h"

namespace Gs2::UE5::Guild::Model
{

    TSharedPtr<FEzIgnoreUser> FEzIgnoreUser::WithUserId(
        const TOptional<FString> UserId
    )
    {
        this->UserIdValue = UserId;
        return SharedThis(this);
    }
    TOptional<FString> FEzIgnoreUser::GetUserId() const
    {
        return UserIdValue;
    }

    Gs2::Guild::Model::FIgnoreUserPtr FEzIgnoreUser::ToModel() const
    {
        return MakeShared<Gs2::Guild::Model::FIgnoreUser>()
            ->WithUserId(UserIdValue);
    }

    TSharedPtr<FEzIgnoreUser> FEzIgnoreUser::FromModel(const Gs2::Guild::Model::FIgnoreUserPtr Model)
    {
        if (Model == nullptr)
        {
            return nullptr;
        }
        return MakeShared<FEzIgnoreUser>()
            ->WithUserId(Model->GetUserId());
    }
}