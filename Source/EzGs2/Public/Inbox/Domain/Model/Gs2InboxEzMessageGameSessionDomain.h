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
#include "Inbox/Domain/Model/MessageAccessToken.h"
#include "Inbox/Model/Gs2InboxEzMessage.h"
#include "Inbox/Model/Gs2InboxEzConfig.h"
#include "Inbox/Model/Gs2InboxEzAcquireAction.h"
#include "Inbox/Model/Gs2InboxEzVerifyActionResult.h"
#include "Inbox/Model/Gs2InboxEzConsumeActionResult.h"
#include "Inbox/Model/Gs2InboxEzAcquireActionResult.h"
#include "Inbox/Model/Gs2InboxEzTransactionResult.h"
#include "Gs2InboxEzMessageGameSessionDomain.h"
#include "Inbox/Domain/Iterator/Gs2InboxEzDescribeMessagesIterator.h"
#include "Core/EzTransactionGameSessionDomain.h"
#include "Util/Net/GameSession.h"
#include "Util/Net/Gs2Connection.h"

namespace Gs2::UE5::Inbox::Domain::Model
{

    class EZGS2_API FEzMessageGameSessionDomain final :
        public TSharedFromThis<FEzMessageGameSessionDomain>
    {
        Gs2::Inbox::Domain::Model::FMessageAccessTokenDomainPtr Domain;
        Gs2::UE5::Util::IGameSessionPtr GameSession;
        Gs2::UE5::Util::FGs2ConnectionPtr ConnectionValue;

        public:
        TOptional<FString> NamespaceName() const;
        TOptional<FString> UserId() const;
        TOptional<FString> MessageName() const;

        FEzMessageGameSessionDomain(
            Gs2::Inbox::Domain::Model::FMessageAccessTokenDomainPtr Domain,
            Gs2::UE5::Util::IGameSessionPtr GameSession,
            Gs2::UE5::Util::FGs2ConnectionPtr Connection
        );

        class EZGS2_API FReadTask :
            public Gs2::Core::Util::TGs2Future<Gs2::UE5::Core::Domain::FEzTransactionGameSessionDomain>,
            public TSharedFromThis<FReadTask>
        {
            TSharedPtr<FEzMessageGameSessionDomain> Self;

        public:
            explicit FReadTask(
                TSharedPtr<FEzMessageGameSessionDomain> Self
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::UE5::Core::Domain::FEzTransactionGameSessionDomain>> Result
            ) override;
        };
        friend FReadTask;

        TSharedPtr<FAsyncTask<FReadTask>> Read(
        );

        class EZGS2_API FDeleteTask :
            public Gs2::Core::Util::TGs2Future<Gs2::UE5::Inbox::Domain::Model::FEzMessageGameSessionDomain>,
            public TSharedFromThis<FDeleteTask>
        {
            TSharedPtr<FEzMessageGameSessionDomain> Self;

        public:
            explicit FDeleteTask(
                TSharedPtr<FEzMessageGameSessionDomain> Self
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::UE5::Inbox::Domain::Model::FEzMessageGameSessionDomain>> Result
            ) override;
        };
        friend FDeleteTask;

        TSharedPtr<FAsyncTask<FDeleteTask>> Delete(
        );

        class EZGS2_API FModelTask :
            public Gs2::Core::Util::TGs2Future<Gs2::UE5::Inbox::Model::FEzMessage>,
            public TSharedFromThis<FModelTask>
        {
            TSharedPtr<FEzMessageGameSessionDomain> Self;

        public:
            explicit FModelTask(
                TSharedPtr<FEzMessageGameSessionDomain> Self
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<Gs2::UE5::Inbox::Model::FEzMessagePtr> Result
            ) override;
        };

        TSharedPtr<FAsyncTask<FModelTask>> Model();

        Gs2::Core::Domain::CallbackID Subscribe(TFunction<void(Gs2::UE5::Inbox::Model::FEzMessagePtr)> Callback);

        void Unsubscribe(Gs2::Core::Domain::CallbackID CallbackId);

    };
    typedef TSharedPtr<FEzMessageGameSessionDomain> FEzMessageGameSessionDomainPtr;
}
