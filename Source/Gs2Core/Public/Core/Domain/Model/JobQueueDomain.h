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
#include "Auth/Model/AccessToken.h"

namespace Gs2::JobQueue::Model
{
    class FJob;
    typedef TSharedPtr<FJob> FJobPtr;
    
    class FJobResultBody;
    typedef TSharedPtr<FJobResultBody> FJobResultBodyPtr;
}

namespace Gs2::Core::Domain
{
    class FGs2;
}

namespace Gs2::Core::Domain::Model
{
    typedef TFunction<void (const Gs2::JobQueue::Model::FJobPtr&, const Gs2::JobQueue::Model::FJobResultBodyPtr&)> FJobQueueExecutedEvent;

    class GS2CORE_API FJobQueueDomain :
        public TSharedFromThis<FJobQueueDomain>
    {
        FCriticalSection Mutex;
        TArray<FString> Tasks;
    public:
        FJobQueueExecutedEvent JobQueueExecutedEventHandler;
        
        explicit FJobQueueDomain(
            FJobQueueExecutedEvent JobQueueExecutedEvent
        );
        explicit FJobQueueDomain(
            const FJobQueueDomain& From
        );
        ~FJobQueueDomain() = default;

        void Push(
            FString NamespaceName
        );
    };

    typedef TSharedPtr<FJobQueueDomain> FJobQueueDomainPtr;
}