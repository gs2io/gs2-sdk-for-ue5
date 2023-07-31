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
#include "LoginReward/Request/DescribeBonusModelMastersRequest.h"
#include "LoginReward/Result/DescribeBonusModelMastersResult.h"

namespace Gs2::LoginReward::Task::Rest
{
    class GS2LOGINREWARD_API FDescribeBonusModelMastersTask final : public Gs2::Core::Util::TGs2Future<Result::FDescribeBonusModelMastersResult>
    {
        Core::Net::Rest::FGs2RestSessionPtr Session;
        Request::FDescribeBonusModelMastersRequestPtr Request;
    public:
        explicit FDescribeBonusModelMastersTask(
            const Core::Net::Rest::FGs2RestSessionPtr Session,
            const Request::FDescribeBonusModelMastersRequestPtr Request
        );
        FDescribeBonusModelMastersTask(
            const FDescribeBonusModelMastersTask& From
        );
        virtual ~FDescribeBonusModelMastersTask() override = default;

        virtual Core::Model::FGs2ErrorPtr Action(const TSharedPtr<Result::FDescribeBonusModelMastersResultPtr> Result) override;
    };
    typedef TSharedPtr<FDescribeBonusModelMastersTask, ESPMode::ThreadSafe> FDescribeBonusModelMastersTaskPtr;
}