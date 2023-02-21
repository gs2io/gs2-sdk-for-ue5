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
#include "Lock/Request/LockByUserIdRequest.h"
#include "Lock/Result/LockByUserIdResult.h"

namespace Gs2::Lock::Task::Rest
{
    class GS2LOCK_API FLockByUserIdTask final : public Gs2::Core::Util::TGs2Future<Result::FLockByUserIdResult>
    {
        Core::Net::Rest::FGs2RestSessionPtr Session;
        Request::FLockByUserIdRequestPtr Request;
    public:
        explicit FLockByUserIdTask(
            const Core::Net::Rest::FGs2RestSessionPtr Session,
            const Request::FLockByUserIdRequestPtr Request
        );
        FLockByUserIdTask(
            const FLockByUserIdTask& From
        );
        virtual ~FLockByUserIdTask() override = default;

        virtual Core::Model::FGs2ErrorPtr Action(const TSharedPtr<Result::FLockByUserIdResultPtr> Result) override;
    };
    typedef TSharedPtr<FLockByUserIdTask, ESPMode::ThreadSafe> FLockByUserIdTaskPtr;
}