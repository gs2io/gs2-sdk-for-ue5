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
#include "Stamina/Request/DescribeRecoverValueTableMastersRequest.h"
#include "Stamina/Result/DescribeRecoverValueTableMastersResult.h"

namespace Gs2::Stamina::Task::Rest
{
    class GS2STAMINA_API FDescribeRecoverValueTableMastersTask final : public Gs2::Core::Util::TGs2Future<Result::FDescribeRecoverValueTableMastersResult>
    {
        Core::Net::Rest::FGs2RestSessionPtr Session;
        Request::FDescribeRecoverValueTableMastersRequestPtr Request;
    public:
        explicit FDescribeRecoverValueTableMastersTask(
            const Core::Net::Rest::FGs2RestSessionPtr Session,
            const Request::FDescribeRecoverValueTableMastersRequestPtr Request
        );
        FDescribeRecoverValueTableMastersTask(
            const FDescribeRecoverValueTableMastersTask& From
        );
        virtual ~FDescribeRecoverValueTableMastersTask() override = default;

        virtual Core::Model::FGs2ErrorPtr Action(const TSharedPtr<Result::FDescribeRecoverValueTableMastersResultPtr> Result) override;
    };
    typedef TSharedPtr<FDescribeRecoverValueTableMastersTask, ESPMode::ThreadSafe> FDescribeRecoverValueTableMastersTaskPtr;
}