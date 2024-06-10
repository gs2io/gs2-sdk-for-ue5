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

#pragma once

#include "CoreMinimal.h"

#include "Core/Gs2Core.h"
#include "Ranking2/Request/ReceiveGlobalRankingReceivedRewardByUserIdRequest.h"
#include "Ranking2/Result/ReceiveGlobalRankingReceivedRewardByUserIdResult.h"

namespace Gs2::Ranking2::Task::Rest
{
    class GS2RANKING2_API FReceiveGlobalRankingReceivedRewardByUserIdTask final : public Gs2::Core::Util::TGs2Future<Result::FReceiveGlobalRankingReceivedRewardByUserIdResult>
    {
        Core::Net::Rest::FGs2RestSessionPtr Session;
        Request::FReceiveGlobalRankingReceivedRewardByUserIdRequestPtr Request;
    public:
        explicit FReceiveGlobalRankingReceivedRewardByUserIdTask(
            const Core::Net::Rest::FGs2RestSessionPtr Session,
            const Request::FReceiveGlobalRankingReceivedRewardByUserIdRequestPtr Request
        );
        FReceiveGlobalRankingReceivedRewardByUserIdTask(
            const FReceiveGlobalRankingReceivedRewardByUserIdTask& From
        );
        virtual ~FReceiveGlobalRankingReceivedRewardByUserIdTask() override = default;

        virtual Core::Model::FGs2ErrorPtr Action(const TSharedPtr<Result::FReceiveGlobalRankingReceivedRewardByUserIdResultPtr> Result) override;
    };
    typedef TSharedPtr<FReceiveGlobalRankingReceivedRewardByUserIdTask, ESPMode::ThreadSafe> FReceiveGlobalRankingReceivedRewardByUserIdTaskPtr;
}