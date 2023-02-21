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
#include "Lock/Request/GetMutexByUserIdRequest.h"
#include "Lock/Result/GetMutexByUserIdResult.h"

namespace Gs2::Lock::Task::Rest
{
    class GS2LOCK_API FGetMutexByUserIdTask final : public Gs2::Core::Util::TGs2Future<Result::FGetMutexByUserIdResult>
    {
        Core::Net::Rest::FGs2RestSessionPtr Session;
        Request::FGetMutexByUserIdRequestPtr Request;
    public:
        explicit FGetMutexByUserIdTask(
            const Core::Net::Rest::FGs2RestSessionPtr Session,
            const Request::FGetMutexByUserIdRequestPtr Request
        );
        FGetMutexByUserIdTask(
            const FGetMutexByUserIdTask& From
        );
        virtual ~FGetMutexByUserIdTask() override = default;

        virtual Core::Model::FGs2ErrorPtr Action(const TSharedPtr<Result::FGetMutexByUserIdResultPtr> Result) override;
    };
    typedef TSharedPtr<FGetMutexByUserIdTask, ESPMode::ThreadSafe> FGetMutexByUserIdTaskPtr;
}