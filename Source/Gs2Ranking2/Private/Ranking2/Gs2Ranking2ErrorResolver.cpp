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

#include "Ranking2/Gs2Ranking2ErrorResolver.h"

#include "Core/Model/Gs2ErrorResolver.h"
#include "Ranking2/Error/SeasonNotEndedError.h"
#include "Ranking2/Error/RewardAlreadyReceivedError.h"
#include "Ranking2/Error/NoRankingRewardError.h"
#include "Ranking2/Error/SeasonNotStartedError.h"
#include "Ranking2/Error/NotIncludedInClusterError.h"

namespace Gs2::Ranking2
{
    namespace
    {
        [[maybe_unused]] const bool GRegistered = Core::Model::FGs2ErrorResolver::Register(
            TEXT("Gs2Ranking2"),
            &FGs2Ranking2ErrorResolver::Resolve
        );
    }

    Core::Model::FGs2ErrorPtr FGs2Ranking2ErrorResolver::Resolve(const FString& Method, Core::Model::FGs2ErrorPtr Source)
    {
        if (!Source.IsValid())
        {
            return Source;
        }
        Core::Model::FGs2ErrorPtr Resolved;
        if (Method == TEXT("ReceiveGlobalRankingReceivedReward") || Method == TEXT("ReceiveGlobalRankingReceivedRewardByUserId") || Method == TEXT("ReceiveClusterRankingReceivedReward") || Method == TEXT("ReceiveClusterRankingReceivedRewardByUserId"))
        {
            if (Core::Model::FGs2ErrorResolver::HasCode(Source, TEXT("ranking2.rankingReward.inSchedule")))
            {
                Resolved = MakeShared<Gs2::Ranking2::Error::FSeasonNotEndedError>(Source);
            }
            else if (Core::Model::FGs2ErrorResolver::HasCode(Source, TEXT("ranking2.rankingReward.alreadyReceived")))
            {
                Resolved = MakeShared<Gs2::Ranking2::Error::FRewardAlreadyReceivedError>(Source);
            }
            else if (Core::Model::FGs2ErrorResolver::HasCode(Source, TEXT("ranking2.rankingReward.noRewards")))
            {
                Resolved = MakeShared<Gs2::Ranking2::Error::FNoRankingRewardError>(Source);
            }
            else if (Core::Model::FGs2ErrorResolver::HasCode(Source, TEXT("ranking2.rankingReward.outOfSchedule")))
            {
                Resolved = MakeShared<Gs2::Ranking2::Error::FSeasonNotStartedError>(Source);
            }
        }
        else if (Method == TEXT("PutClusterRankingScore") || Method == TEXT("PutClusterRankingScoreByUserId"))
        {
            if (Core::Model::FGs2ErrorResolver::HasCode(Source, TEXT("ranking2.cluster.notInclude")))
            {
                Resolved = MakeShared<Gs2::Ranking2::Error::FNotIncludedInClusterError>(Source);
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