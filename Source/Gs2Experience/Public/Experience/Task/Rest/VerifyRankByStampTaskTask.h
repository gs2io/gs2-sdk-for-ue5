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
#include "Experience/Request/VerifyRankByStampTaskRequest.h"
#include "Experience/Result/VerifyRankByStampTaskResult.h"

namespace Gs2::Experience::Task::Rest
{
    class GS2EXPERIENCE_API FVerifyRankByStampTaskTask final : public Gs2::Core::Util::TGs2Future<Result::FVerifyRankByStampTaskResult>
    {
        Core::Net::Rest::FGs2RestSessionPtr Session;
        Request::FVerifyRankByStampTaskRequestPtr Request;
    public:
        explicit FVerifyRankByStampTaskTask(
            const Core::Net::Rest::FGs2RestSessionPtr Session,
            const Request::FVerifyRankByStampTaskRequestPtr Request
        );
        FVerifyRankByStampTaskTask(
            const FVerifyRankByStampTaskTask& From
        );
        virtual ~FVerifyRankByStampTaskTask() override = default;

        virtual Core::Model::FGs2ErrorPtr Action(const TSharedPtr<Result::FVerifyRankByStampTaskResultPtr> Result) override;
    };
    typedef TSharedPtr<FVerifyRankByStampTaskTask, ESPMode::ThreadSafe> FVerifyRankByStampTaskTaskPtr;
}