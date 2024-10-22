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
#include "Distributor/Request/FreezeMasterDataRequest.h"
#include "Distributor/Result/FreezeMasterDataResult.h"

namespace Gs2::Distributor::Task::Rest
{
    class GS2DISTRIBUTOR_API FFreezeMasterDataTask final : public Gs2::Core::Util::TGs2Future<Result::FFreezeMasterDataResult>
    {
        Core::Net::Rest::FGs2RestSessionPtr Session;
        Request::FFreezeMasterDataRequestPtr Request;
    public:
        explicit FFreezeMasterDataTask(
            const Core::Net::Rest::FGs2RestSessionPtr Session,
            const Request::FFreezeMasterDataRequestPtr Request
        );
        FFreezeMasterDataTask(
            const FFreezeMasterDataTask& From
        );
        virtual ~FFreezeMasterDataTask() override = default;

        virtual Core::Model::FGs2ErrorPtr Action(const TSharedPtr<Result::FFreezeMasterDataResultPtr> Result) override;
    };
    typedef TSharedPtr<FFreezeMasterDataTask, ESPMode::ThreadSafe> FFreezeMasterDataTaskPtr;
}