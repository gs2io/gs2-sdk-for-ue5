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
#include "JobQueue/Domain/Model/JobResultAccessToken.h"
#include "JobQueue/Model/Gs2JobQueueEzJob.h"
#include "JobQueue/Model/Gs2JobQueueEzJobResult.h"
#include "JobQueue/Model/Gs2JobQueueEzJobEntry.h"
#include "JobQueue/Model/Gs2JobQueueEzJobResultBody.h"
#include "Gs2JobQueueEzJobResultGameSessionDomain.h"
#include "Util/Net/GameSession.h"
#include "Util/Net/Gs2Connection.h"

namespace Gs2::UE5::JobQueue::Domain::Model
{

    class EZGS2_API FEzJobResultGameSessionDomain final :
        public TSharedFromThis<FEzJobResultGameSessionDomain>
    {
        Gs2::JobQueue::Domain::Model::FJobResultAccessTokenDomainPtr Domain;
        Gs2::UE5::Util::IGameSessionPtr GameSession;
        Gs2::UE5::Util::FGs2ConnectionPtr ConnectionValue;

        public:
        TOptional<FString> NamespaceName() const;
        TOptional<FString> UserId() const;
        TOptional<FString> JobName() const;
        TOptional<int32> TryNumber() const;

        FEzJobResultGameSessionDomain(
            Gs2::JobQueue::Domain::Model::FJobResultAccessTokenDomainPtr Domain,
            Gs2::UE5::Util::IGameSessionPtr GameSession,
            Gs2::UE5::Util::FGs2ConnectionPtr Connection
        );

        class EZGS2_API FModelTask :
            public Gs2::Core::Util::TGs2Future<Gs2::UE5::JobQueue::Model::FEzJobResult>,
            public TSharedFromThis<FModelTask>
        {
            TSharedPtr<FEzJobResultGameSessionDomain> Self;

        public:
            explicit FModelTask(
                TSharedPtr<FEzJobResultGameSessionDomain> Self
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<Gs2::UE5::JobQueue::Model::FEzJobResultPtr> Result
            ) override;
        };

        TSharedPtr<FAsyncTask<FModelTask>> Model();

        Gs2::Core::Domain::CallbackID Subscribe(TFunction<void(Gs2::UE5::JobQueue::Model::FEzJobResultPtr)> Callback);

        void Unsubscribe(Gs2::Core::Domain::CallbackID CallbackId);

    };
    typedef TSharedPtr<FEzJobResultGameSessionDomain> FEzJobResultGameSessionDomainPtr;
}
