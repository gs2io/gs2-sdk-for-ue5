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
#include "Inbox/Domain/Model/User.h"
#include "Inbox/Model/Gs2InboxEzMessage.h"
#include "Inbox/Model/Gs2InboxEzConfig.h"
#include "Inbox/Model/Gs2InboxEzAcquireAction.h"
#include "Inbox/Model/Gs2InboxEzVerifyActionResult.h"
#include "Inbox/Model/Gs2InboxEzConsumeActionResult.h"
#include "Inbox/Model/Gs2InboxEzAcquireActionResult.h"
#include "Inbox/Model/Gs2InboxEzTransactionResult.h"
#include "Gs2InboxEzMessageDomain.h"
#include "Gs2InboxEzUserDomain.h"
#include "Gs2InboxEzUserDomain.h"
#include "Gs2InboxEzUserGameSessionDomain.h"
#include "Core/EzTransactionDomain.h"
#include "Util/Net/GameSession.h"
#include "Util/Net/Gs2Connection.h"

namespace Gs2::UE5::Inbox::Domain::Model
{

    class EZGS2_API FEzUserDomain final :
        public TSharedFromThis<FEzUserDomain>
    {
        Gs2::Inbox::Domain::Model::FUserDomainPtr Domain;
        Gs2::UE5::Util::FGs2ConnectionPtr ConnectionValue;

        public:
        TOptional<FString> NextPageToken() const;
        TOptional<FString> NamespaceName() const;
        TOptional<FString> UserId() const;

        FEzUserDomain(
            Gs2::Inbox::Domain::Model::FUserDomainPtr Domain,
            Gs2::UE5::Util::FGs2ConnectionPtr Connection
        );

        Gs2::UE5::Inbox::Domain::Model::FEzMessageDomainPtr Message(
            const FString MessageName
        ) const;

    };
    typedef TSharedPtr<FEzUserDomain> FEzUserDomainPtr;
}
