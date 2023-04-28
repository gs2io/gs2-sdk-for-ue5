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

#include "Core/Model/Gs2Error.h"

namespace Gs2::JobQueue::Error
{
    class GS2JOBQUEUE_API FConflictError : public Core::Model::FConflictError
    {
    public:
        inline static const FGs2ErrorType TypeString = "Conflict";

        explicit FConflictError(Core::Model::FGs2ErrorPtr Error);

        virtual FGs2ErrorType Type() const override
        {
            return TypeString;
        }
    };
    typedef TSharedPtr<FConflictError, ESPMode::ThreadSafe> FConflictErrorPtr;
}