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

#include "Guild/Gs2GuildErrorResolver.h"

#include "Core/Model/Gs2ErrorResolver.h"
#include "Guild/Error/MaximumJoinedGuildsReachedError.h"
#include "Guild/Error/GuildMasterRequiredError.h"
#include "Guild/Error/NotIncludedGuildMemberError.h"
#include "Guild/Error/MaximumMembersReachedError.h"
#include "Guild/Error/MaximumReceiveRequestsReachedError.h"
#include "Guild/Error/MaximumSendRequestsReachedError.h"
#include "Guild/Error/DotMeetJoinRequirementsError.h"

namespace Gs2::Guild
{
    namespace
    {
        [[maybe_unused]] const bool GRegistered = Core::Model::FGs2ErrorResolver::Register(
            TEXT("Gs2Guild"),
            &FGs2GuildErrorResolver::Resolve
        );
    }

    Core::Model::FGs2ErrorPtr FGs2GuildErrorResolver::Resolve(const FString& Method, Core::Model::FGs2ErrorPtr Source)
    {
        if (!Source.IsValid())
        {
            return Source;
        }
        Core::Model::FGs2ErrorPtr Resolved;
        if (Method == TEXT("CreateGuild") || Method == TEXT("CreateGuildByUserId"))
        {
            if (Core::Model::FGs2ErrorResolver::HasCode(Source, TEXT("user.joinedGuild.tooMany")))
            {
                Resolved = MakeShared<Gs2::Guild::Error::FMaximumJoinedGuildsReachedError>(Source);
            }
        }
        else if (Method == TEXT("DeleteMember") || Method == TEXT("DeleteMemberByGuildName") || Method == TEXT("Withdrawal") || Method == TEXT("WithdrawalByUserId"))
        {
            if (Core::Model::FGs2ErrorResolver::HasCode(Source, TEXT("guild.member.master.require")))
            {
                Resolved = MakeShared<Gs2::Guild::Error::FGuildMasterRequiredError>(Source);
            }
        }
        else if (Method == TEXT("Assume") || Method == TEXT("AssumeByUserId"))
        {
            if (Core::Model::FGs2ErrorResolver::HasCode(Source, TEXT("guild.member.notFound")))
            {
                Resolved = MakeShared<Gs2::Guild::Error::FNotIncludedGuildMemberError>(Source);
            }
        }
        else if (Method == TEXT("AcceptRequest") || Method == TEXT("AcceptRequestByGuildName"))
        {
            if (Core::Model::FGs2ErrorResolver::HasCode(Source, TEXT("user.joinedGuild.tooMany")))
            {
                Resolved = MakeShared<Gs2::Guild::Error::FMaximumJoinedGuildsReachedError>(Source);
            }
            else if (Core::Model::FGs2ErrorResolver::HasCode(Source, TEXT("guild.members.tooMany")))
            {
                Resolved = MakeShared<Gs2::Guild::Error::FMaximumMembersReachedError>(Source);
            }
        }
        else if (Method == TEXT("SendRequest") || Method == TEXT("SendRequestByUserId"))
        {
            if (Core::Model::FGs2ErrorResolver::HasCode(Source, TEXT("guild.members.tooMany")))
            {
                Resolved = MakeShared<Gs2::Guild::Error::FMaximumMembersReachedError>(Source);
            }
            else if (Core::Model::FGs2ErrorResolver::HasCode(Source, TEXT("user.joinedGuild.tooMany")))
            {
                Resolved = MakeShared<Gs2::Guild::Error::FMaximumJoinedGuildsReachedError>(Source);
            }
            else if (Core::Model::FGs2ErrorResolver::HasCode(Source, TEXT("guild.receiveRequests.tooMany")))
            {
                Resolved = MakeShared<Gs2::Guild::Error::FMaximumReceiveRequestsReachedError>(Source);
            }
            else if (Core::Model::FGs2ErrorResolver::HasCode(Source, TEXT("guild.sendRequests.tooMany")))
            {
                Resolved = MakeShared<Gs2::Guild::Error::FMaximumSendRequestsReachedError>(Source);
            }
            else if (Core::Model::FGs2ErrorResolver::HasCode(Source, TEXT("guild.sendRequests.notMeetJoinRequirements")))
            {
                Resolved = MakeShared<Gs2::Guild::Error::FDotMeetJoinRequirementsError>(Source);
            }
        }
        if (!Resolved.IsValid())
        {
            return Source;
        }
        Resolved->SetMetadata(Source->GetMetadata());
        return Resolved;
    }
}