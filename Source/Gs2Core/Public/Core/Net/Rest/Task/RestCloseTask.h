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
#include "Core/Net/Rest/Gs2RestSession.h"
#include "Core/Net/Task/CloseTask.h"
#include "Core/Util/Gs2Future.h"

namespace Gs2::Core::Net::Rest::Task
{
    class GS2CORE_API FRestCloseTask final :
        public Net::Task::FCloseTask,
        public TSharedFromThis<FRestCloseTask>
    {
        const FGs2RestSessionPtr Session;
    public:
        explicit FRestCloseTask(
            const FGs2RestSessionPtr Session
        );
        virtual ~FRestCloseTask() override;

        virtual Model::FGs2ErrorPtr Action(TSharedPtr<TSharedPtr<Result::FCloseTaskResult>> Result) override;
    };
    typedef TSharedPtr<FRestCloseTask, ESPMode::ThreadSafe> FRestCloseTaskPtr;
}