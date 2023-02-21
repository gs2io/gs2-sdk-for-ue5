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
#include "Lottery/Request/DescribeLotteryModelMastersRequest.h"
#include "Lottery/Result/DescribeLotteryModelMastersResult.h"

namespace Gs2::Lottery::Task::Rest
{
    class GS2LOTTERY_API FDescribeLotteryModelMastersTask final : public Gs2::Core::Util::TGs2Future<Result::FDescribeLotteryModelMastersResult>
    {
        Core::Net::Rest::FGs2RestSessionPtr Session;
        Request::FDescribeLotteryModelMastersRequestPtr Request;
    public:
        explicit FDescribeLotteryModelMastersTask(
            const Core::Net::Rest::FGs2RestSessionPtr Session,
            const Request::FDescribeLotteryModelMastersRequestPtr Request
        );
        FDescribeLotteryModelMastersTask(
            const FDescribeLotteryModelMastersTask& From
        );
        virtual ~FDescribeLotteryModelMastersTask() override = default;

        virtual Core::Model::FGs2ErrorPtr Action(const TSharedPtr<Result::FDescribeLotteryModelMastersResultPtr> Result) override;
    };
    typedef TSharedPtr<FDescribeLotteryModelMastersTask, ESPMode::ThreadSafe> FDescribeLotteryModelMastersTaskPtr;
}