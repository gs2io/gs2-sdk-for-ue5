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

#include "Guild/Model/Gs2GuildEzSendMemberRequest.h"

namespace Gs2::UE5::Guild::Model
{

    TSharedPtr<FEzSendMemberRequest> FEzSendMemberRequest::WithUserId(
        const TOptional<FString> UserId
    )
    {
        this->UserIdValue = UserId;
        return SharedThis(this);
    }

    TSharedPtr<FEzSendMemberRequest> FEzSendMemberRequest::WithTargetGuildName(
        const TOptional<FString> TargetGuildName
    )
    {
        this->TargetGuildNameValue = TargetGuildName;
        return SharedThis(this);
    }
    TOptional<FString> FEzSendMemberRequest::GetUserId() const
    {
        return UserIdValue;
    }
    TOptional<FString> FEzSendMemberRequest::GetTargetGuildName() const
    {
        return TargetGuildNameValue;
    }

    Gs2::Guild::Model::FSendMemberRequestPtr FEzSendMemberRequest::ToModel() const
    {
        return MakeShared<Gs2::Guild::Model::FSendMemberRequest>()
            ->WithUserId(UserIdValue)
            ->WithTargetGuildName(TargetGuildNameValue);
    }

    TSharedPtr<FEzSendMemberRequest> FEzSendMemberRequest::FromModel(const Gs2::Guild::Model::FSendMemberRequestPtr Model)
    {
        if (Model == nullptr)
        {
            return nullptr;
        }
        return MakeShared<FEzSendMemberRequest>()
            ->WithUserId(Model->GetUserId())
            ->WithTargetGuildName(Model->GetTargetGuildName());
    }
}