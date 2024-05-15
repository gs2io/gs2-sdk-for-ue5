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
#include "Guild/Request/DescribeGuildModelsRequest.h"
#include "Guild/Result/DescribeGuildModelsResult.h"

namespace Gs2::Guild::Task::Rest
{
    class GS2GUILD_API FDescribeGuildModelsTask final : public Gs2::Core::Util::TGs2Future<Result::FDescribeGuildModelsResult>
    {
        Core::Net::Rest::FGs2RestSessionPtr Session;
        Request::FDescribeGuildModelsRequestPtr Request;
    public:
        explicit FDescribeGuildModelsTask(
            const Core::Net::Rest::FGs2RestSessionPtr Session,
            const Request::FDescribeGuildModelsRequestPtr Request
        );
        FDescribeGuildModelsTask(
            const FDescribeGuildModelsTask& From
        );
        virtual ~FDescribeGuildModelsTask() override = default;

        virtual Core::Model::FGs2ErrorPtr Action(const TSharedPtr<Result::FDescribeGuildModelsResultPtr> Result) override;
    };
    typedef TSharedPtr<FDescribeGuildModelsTask, ESPMode::ThreadSafe> FDescribeGuildModelsTaskPtr;
}