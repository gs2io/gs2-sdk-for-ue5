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

#include "EzGs2/Public/SkillTree/Model/Gs2SkillTreeEzStatus.h"

namespace Gs2::UE5::SkillTree::Model
{

    TSharedPtr<FEzStatus> FEzStatus::WithStatusId(
        const TOptional<FString> StatusId
    )
    {
        this->StatusIdValue = StatusId;
        return SharedThis(this);
    }

    TSharedPtr<FEzStatus> FEzStatus::WithUserId(
        const TOptional<FString> UserId
    )
    {
        this->UserIdValue = UserId;
        return SharedThis(this);
    }

    TSharedPtr<FEzStatus> FEzStatus::WithReleasedNodeNames(
        const TSharedPtr<TArray<FString>> ReleasedNodeNames
    )
    {
        this->ReleasedNodeNamesValue = ReleasedNodeNames;
        return SharedThis(this);
    }
    TOptional<FString> FEzStatus::GetStatusId() const
    {
        return StatusIdValue;
    }
    TOptional<FString> FEzStatus::GetUserId() const
    {
        return UserIdValue;
    }
    TSharedPtr<TArray<FString>> FEzStatus::GetReleasedNodeNames() const
    {
        return ReleasedNodeNamesValue;
    }

    Gs2::SkillTree::Model::FStatusPtr FEzStatus::ToModel() const
    {
        return MakeShared<Gs2::SkillTree::Model::FStatus>()
            ->WithStatusId(StatusIdValue)
            ->WithUserId(UserIdValue)
            ->WithReleasedNodeNames(ReleasedNodeNamesValue);
    }

    TSharedPtr<FEzStatus> FEzStatus::FromModel(const Gs2::SkillTree::Model::FStatusPtr Model)
    {
        if (Model == nullptr)
        {
            return nullptr;
        }
        return MakeShared<FEzStatus>()
            ->WithStatusId(Model->GetStatusId())
            ->WithUserId(Model->GetUserId())
            ->WithReleasedNodeNames(Model->GetReleasedNodeNames());
    }
}