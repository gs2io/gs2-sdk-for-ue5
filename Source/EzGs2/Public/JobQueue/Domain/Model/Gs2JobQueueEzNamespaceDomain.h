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
#include "JobQueue/Domain/Model/Namespace.h"
#include "JobQueue/Model/Gs2JobQueueEzJob.h"
#include "JobQueue/Model/Gs2JobQueueEzJobResult.h"
#include "JobQueue/Model/Gs2JobQueueEzJobEntry.h"
#include "JobQueue/Model/Gs2JobQueueEzJobResultBody.h"
#include "Gs2JobQueueEzUserDomain.h"
#include "Gs2JobQueueEzUserDomain.h"
#include "Gs2JobQueueEzUserGameSessionDomain.h"
#include "Gs2JobQueueEzNamespaceDomain.h"
#include "Core/EzTransactionDomain.h"
#include "Util/Net/GameSession.h"
#include "Util/Net/Gs2Connection.h"

namespace Gs2::UE5::JobQueue::Domain::Model
{

    class EZGS2_API FEzNamespaceDomain final :
        public TSharedFromThis<FEzNamespaceDomain>
    {
        Gs2::JobQueue::Domain::Model::FNamespaceDomainPtr Domain;
        Gs2::UE5::Util::FGs2ConnectionPtr ConnectionValue;

        public:
        TOptional<FString> Status() const;
        TOptional<FString> Url() const;
        TOptional<FString> UploadToken() const;
        TOptional<FString> UploadUrl() const;
        TOptional<FString> NamespaceName() const;

        FEzNamespaceDomain(
            Gs2::JobQueue::Domain::Model::FNamespaceDomainPtr Domain,
            Gs2::UE5::Util::FGs2ConnectionPtr Connection
        );

        Gs2::UE5::JobQueue::Domain::Model::FEzUserDomainPtr User(
            const FString UserId
        ) const;

        Gs2::UE5::JobQueue::Domain::Model::FEzUserGameSessionDomainPtr Me(
            Gs2::UE5::Util::IGameSessionPtr GameSession
        ) const;

    };
    typedef TSharedPtr<FEzNamespaceDomain> FEzNamespaceDomainPtr;
}
