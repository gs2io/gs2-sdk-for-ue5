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


#include "Core/Net/Rest/Task/RestCloseTask.h"
#include "Core/Model/Gs2Error.h"

#include "HttpManager.h"

namespace Gs2::Core::Net::Rest::Task
{
    FRestCloseTask::FRestCloseTask(const FGs2RestSessionPtr Session): Session(Session)
    {
   
    }

    FRestCloseTask::~FRestCloseTask()
    {
    }

    Model::FGs2ErrorPtr FRestCloseTask::Action(TSharedPtr<TSharedPtr<Result::FCloseTaskResult>> Result)
    {
        *Result = MakeShared<Result::FCloseTaskResult>();
        return nullptr;
    }
}
