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

#include "Ranking2/Model/Gs2Ranking2EzSubscribeUser.h"

namespace Gs2::UE5::Ranking2::Model
{

    TSharedPtr<FEzSubscribeUser> FEzSubscribeUser::WithRankingName(
        const TOptional<FString> RankingName
    )
    {
        this->RankingNameValue = RankingName;
        return SharedThis(this);
    }

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
    TOptional<FString> FEzSubscribeUser::GetRankingName() const
    {
        return RankingNameValue;
    }
    TOptional<FString> FEzSubscribeUser::GetUserId() const
    {
        return UserIdValue;
    }
    TOptional<FString> FEzSubscribeUser::GetTargetUserId() const
    {
        return TargetUserIdValue;
    }

    Gs2::Ranking2::Model::FSubscribeUserPtr FEzSubscribeUser::ToModel() const
    {
        return MakeShared<Gs2::Ranking2::Model::FSubscribeUser>()
            ->WithRankingName(RankingNameValue)
            ->WithUserId(UserIdValue)
            ->WithTargetUserId(TargetUserIdValue);
    }

    TSharedPtr<FEzSubscribeUser> FEzSubscribeUser::FromModel(const Gs2::Ranking2::Model::FSubscribeUserPtr Model)
    {
        if (Model == nullptr)
        {
            return nullptr;
        }
        return MakeShared<FEzSubscribeUser>()
            ->WithRankingName(Model->GetRankingName())
            ->WithUserId(Model->GetUserId())
            ->WithTargetUserId(Model->GetTargetUserId());
    }
}