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
#include "JobQueue/Domain/Model/Job.h"
#include "JobQueue/Model/Gs2JobQueueEzJob.h"
#include "JobQueue/Model/Gs2JobQueueEzJobResult.h"
#include "JobQueue/Model/Gs2JobQueueEzJobEntry.h"
#include "JobQueue/Model/Gs2JobQueueEzJobResultBody.h"
#include "Gs2JobQueueEzJobResultDomain.h"
#include "Gs2JobQueueEzJobDomain.h"
#include "Auth/Model/Gs2AuthEzAccessToken.h"
#include "Util/Profile.h"

namespace Gs2::UE5::JobQueue::Domain::Model
{

    class EZGS2_API FEzJobDomain final :
        public TSharedFromThis<FEzJobDomain>
    {
        Gs2::JobQueue::Domain::Model::FJobDomainPtr Domain;
        Gs2::UE5::Util::FProfilePtr ProfileValue;

        public:
        TOptional<bool> AutoRun() const;
        TOptional<bool> IsLastJob() const;
        TOptional<bool> NeedRetry() const;
        TOptional<FString> NamespaceName() const;
        TOptional<FString> UserId() const;
        TOptional<FString> JobName() const;

        FEzJobDomain(
            Gs2::JobQueue::Domain::Model::FJobDomainPtr Domain,
            Gs2::UE5::Util::FProfilePtr Profile
        );

        Gs2::UE5::JobQueue::Domain::Model::FEzJobResultDomainPtr JobResult(
            const int32 TryNumber
        ) const;

        class FModelTask :
            public Gs2::Core::Util::TGs2Future<Gs2::UE5::JobQueue::Model::FEzJob>,
            public TSharedFromThis<FModelTask>
        {
            TSharedPtr<FEzJobDomain> Self;

        public:
            explicit FModelTask(
                TSharedPtr<FEzJobDomain> Self
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<Gs2::UE5::JobQueue::Model::FEzJobPtr> Result
            ) override;
        };

        TSharedPtr<FAsyncTask<FModelTask>> Model();

    };
    typedef TSharedPtr<FEzJobDomain> FEzJobDomainPtr;
}
