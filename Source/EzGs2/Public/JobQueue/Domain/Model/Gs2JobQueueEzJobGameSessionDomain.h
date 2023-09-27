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
#include "JobQueue/Domain/Model/JobAccessToken.h"
#include "JobQueue/Model/Gs2JobQueueEzJob.h"
#include "JobQueue/Model/Gs2JobQueueEzJobResult.h"
#include "JobQueue/Model/Gs2JobQueueEzJobEntry.h"
#include "JobQueue/Model/Gs2JobQueueEzJobResultBody.h"
#include "Gs2JobQueueEzJobResultGameSessionDomain.h"
#include "Gs2JobQueueEzJobGameSessionDomain.h"
#include "Auth/Model/Gs2AuthEzAccessToken.h"
#include "Util/Profile.h"

namespace Gs2::UE5::JobQueue::Domain::Model
{

    class EZGS2_API FEzJobGameSessionDomain final :
        public TSharedFromThis<FEzJobGameSessionDomain>
    {
        Gs2::JobQueue::Domain::Model::FJobAccessTokenDomainPtr Domain;
        Gs2::UE5::Util::FProfilePtr ProfileValue;

        public:
        TOptional<bool> AutoRun() const;
        TOptional<bool> IsLastJob() const;
        TOptional<bool> NeedRetry() const;
        TOptional<FString> NamespaceName() const;
        TOptional<FString> UserId() const;
        TOptional<FString> JobName() const;

        FEzJobGameSessionDomain(
            Gs2::JobQueue::Domain::Model::FJobAccessTokenDomainPtr Domain,
            Gs2::UE5::Util::FProfilePtr Profile
        );

        Gs2::UE5::JobQueue::Domain::Model::FEzJobResultGameSessionDomainPtr JobResult(
            const int32 TryNumber
        ) const;

        class FModelTask :
            public Gs2::Core::Util::TGs2Future<Gs2::UE5::JobQueue::Model::FEzJob>,
            public TSharedFromThis<FModelTask>
        {
            TSharedPtr<FEzJobGameSessionDomain> Self;

        public:
            explicit FModelTask(
                TSharedPtr<FEzJobGameSessionDomain> Self
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<Gs2::UE5::JobQueue::Model::FEzJobPtr> Result
            ) override;
        };

        TSharedPtr<FAsyncTask<FModelTask>> Model();

        Gs2::Core::Domain::CallbackID Subscribe(TFunction<void(Gs2::UE5::JobQueue::Model::FEzJobPtr)> Callback);

        void Unsubscribe(Gs2::Core::Domain::CallbackID CallbackId);

    };
    typedef TSharedPtr<FEzJobGameSessionDomain> FEzJobGameSessionDomainPtr;
}
