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
#include "Core/Util/Gs2Future.h"
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
    DECLARE_EVENT_TwoParams(FJobQueueDomain, FJobQueueExecutedEvent, Gs2::JobQueue::Model::FJobPtr, Gs2::JobQueue::Model::FJobResultBodyPtr);

    class GS2CORE_API FJobQueueDomain :
        public TSharedFromThis<FJobQueueDomain>
    {
        FCriticalSection Mutex;
        TArray<FString> Tasks;
        TFunction<bool (FString, Gs2::Auth::Model::FAccessTokenPtr)> RunFunc;
        FJobQueueExecutedEvent JobQueueExecutedEvent;
    public:
        explicit FJobQueueDomain(
            TFunction<bool (FString, Gs2::Auth::Model::FAccessTokenPtr)> RunFunc
            );
        explicit FJobQueueDomain(
            const FJobQueueDomain& From
        );
        ~FJobQueueDomain() = default;

        class FRunTask final :
            public Gs2::Core::Util::TGs2Future<bool>,
            public TSharedFromThis<FRunTask>
        {
            const TSharedPtr<FJobQueueDomain> Self;
            const Gs2::Auth::Model::FAccessTokenPtr AccessToken;
        public:
            explicit FRunTask(
                const TSharedPtr<FJobQueueDomain> Self,
                const Gs2::Auth::Model::FAccessTokenPtr AccessToken
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<bool>> Result
            ) override;
        };
        friend FRunTask;

        void Push(
            FString NamespaceName
        );

        TSharedPtr<FAsyncTask<FRunTask>> Run(
            Gs2::Auth::Model::FAccessTokenPtr AccessToken
        );
        
        FJobQueueExecutedEvent& OnExecutedEvent();
    };

    typedef TSharedPtr<FJobQueueDomain> FJobQueueDomainPtr;
}