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

#include "EzGs2/Public/Ranking/Model/Gs2RankingEzSubscribeUser.h"

namespace Gs2::UE5::Ranking::Model
{

    TSharedPtr<FEzSubscribeUser> FEzSubscribeUser::WithUserId(
        const TOptional<FString> UserId
    )
    {
        this->UserIdValue = UserId;
        return SharedThis(this);
    }

    TSharedPtr<FEzSubscribeUser> FEzSubscribeUser::WithTargetUserId(
        const TOptional<FString> TargetUserId
    )
    {
        this->TargetUserIdValue = TargetUserId;
        return SharedThis(this);
    }
    TOptional<FString> FEzSubscribeUser::GetUserId() const
    {
        return UserIdValue;
    }
    TOptional<FString> FEzSubscribeUser::GetTargetUserId() const
    {
        return TargetUserIdValue;
    }

    Gs2::Ranking::Model::FSubscribeUserPtr FEzSubscribeUser::ToModel() const
    {
        return MakeShared<Gs2::Ranking::Model::FSubscribeUser>()
            ->WithUserId(UserIdValue)
            ->WithTargetUserId(TargetUserIdValue);
    }

    TSharedPtr<FEzSubscribeUser> FEzSubscribeUser::FromModel(const Gs2::Ranking::Model::FSubscribeUserPtr Model)
    {
        if (Model == nullptr)
        {
            return nullptr;
        }
        return MakeShared<FEzSubscribeUser>()
            ->WithUserId(Model->GetUserId())
            ->WithTargetUserId(Model->GetTargetUserId());
    }
}