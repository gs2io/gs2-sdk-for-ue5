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

#include "Friend/Model/Gs2FriendEzBlackList.h"

namespace Gs2::UE5::Friend::Model
{

    TSharedPtr<FEzBlackList> FEzBlackList::WithUserId(
        const TOptional<FString> UserId
    )
    {
        this->UserIdValue = UserId;
        return SharedThis(this);
    }

    TSharedPtr<FEzBlackList> FEzBlackList::WithTargetUserIds(
        const TSharedPtr<TArray<FString>> TargetUserIds
    )
    {
        this->TargetUserIdsValue = TargetUserIds;
        return SharedThis(this);
    }
    TOptional<FString> FEzBlackList::GetUserId() const
    {
        return UserIdValue;
    }
    TSharedPtr<TArray<FString>> FEzBlackList::GetTargetUserIds() const
    {
        return TargetUserIdsValue;
    }

    Gs2::Friend::Model::FBlackListPtr FEzBlackList::ToModel() const
    {
        return MakeShared<Gs2::Friend::Model::FBlackList>()
            ->WithUserId(UserIdValue)
            ->WithTargetUserIds(TargetUserIdsValue);
    }

    TSharedPtr<FEzBlackList> FEzBlackList::FromModel(const Gs2::Friend::Model::FBlackListPtr Model)
    {
        if (Model == nullptr)
        {
            return nullptr;
        }
        return MakeShared<FEzBlackList>()
            ->WithUserId(Model->GetUserId())
            ->WithTargetUserIds(Model->GetTargetUserIds());
    }
}