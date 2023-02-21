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
#include "MegaField/Request/DescribeAreaModelMastersRequest.h"
#include "MegaField/Result/DescribeAreaModelMastersResult.h"

namespace Gs2::MegaField::Task::Rest
{
    class GS2MEGAFIELD_API FDescribeAreaModelMastersTask final : public Gs2::Core::Util::TGs2Future<Result::FDescribeAreaModelMastersResult>
    {
        Core::Net::Rest::FGs2RestSessionPtr Session;
        Request::FDescribeAreaModelMastersRequestPtr Request;
    public:
        explicit FDescribeAreaModelMastersTask(
            const Core::Net::Rest::FGs2RestSessionPtr Session,
            const Request::FDescribeAreaModelMastersRequestPtr Request
        );
        FDescribeAreaModelMastersTask(
            const FDescribeAreaModelMastersTask& From
        );
        virtual ~FDescribeAreaModelMastersTask() override = default;

        virtual Core::Model::FGs2ErrorPtr Action(const TSharedPtr<Result::FDescribeAreaModelMastersResultPtr> Result) override;
    };
    typedef TSharedPtr<FDescribeAreaModelMastersTask, ESPMode::ThreadSafe> FDescribeAreaModelMastersTaskPtr;
}