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
#include "Distributor/Request/IfExpressionByUserByStampTaskRequest.h"
#include "Distributor/Result/IfExpressionByUserByStampTaskResult.h"

namespace Gs2::Distributor::Task::Rest
{
    class GS2DISTRIBUTOR_API FIfExpressionByUserByStampTaskTask final : public Gs2::Core::Util::TGs2Future<Result::FIfExpressionByUserByStampTaskResult>
    {
        Core::Net::Rest::FGs2RestSessionPtr Session;
        Request::FIfExpressionByUserByStampTaskRequestPtr Request;
    public:
        explicit FIfExpressionByUserByStampTaskTask(
            const Core::Net::Rest::FGs2RestSessionPtr Session,
            const Request::FIfExpressionByUserByStampTaskRequestPtr Request
        );
        FIfExpressionByUserByStampTaskTask(
            const FIfExpressionByUserByStampTaskTask& From
        );
        virtual ~FIfExpressionByUserByStampTaskTask() override = default;

        virtual Core::Model::FGs2ErrorPtr Action(const TSharedPtr<Result::FIfExpressionByUserByStampTaskResultPtr> Result) override;
    };
    typedef TSharedPtr<FIfExpressionByUserByStampTaskTask, ESPMode::ThreadSafe> FIfExpressionByUserByStampTaskTaskPtr;
}