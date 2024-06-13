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
#include "Inbox/Domain/Model/UserAccessToken.h"
#include "Inbox/Model/Gs2InboxEzMessage.h"
#include "Inbox/Model/Gs2InboxEzConfig.h"
#include "Inbox/Model/Gs2InboxEzAcquireAction.h"
#include "Gs2InboxEzMessageGameSessionDomain.h"
#include "Inbox/Domain/Iterator/Gs2InboxEzDescribeMessagesIterator.h"
#include "Gs2InboxEzUserGameSessionDomain.h"
#include "Util/Net/GameSession.h"
#include "Util/Net/Gs2Connection.h"

namespace Gs2::UE5::Inbox::Domain::Model
{

    class EZGS2_API FEzUserGameSessionDomain final :
        public TSharedFromThis<FEzUserGameSessionDomain>
    {
        Gs2::Inbox::Domain::Model::FUserAccessTokenDomainPtr Domain;
        Gs2::UE5::Util::IGameSessionPtr GameSession;
        Gs2::UE5::Util::FGs2ConnectionPtr ConnectionValue;

        public:
        TOptional<FString> NextPageToken() const;
        TOptional<FString> NamespaceName() const;
        TOptional<FString> UserId() const;

        FEzUserGameSessionDomain(
            Gs2::Inbox::Domain::Model::FUserAccessTokenDomainPtr Domain,
            Gs2::UE5::Util::IGameSessionPtr GameSession,
            Gs2::UE5::Util::FGs2ConnectionPtr Connection
        );

        class EZGS2_API FReceiveGlobalMessageTask :
            public Gs2::Core::Util::TGs2Future<TArray<TSharedPtr<Gs2::UE5::Inbox::Domain::Model::FEzMessageGameSessionDomain>>>,
            public TSharedFromThis<FReceiveGlobalMessageTask>
        {
            TSharedPtr<FEzUserGameSessionDomain> Self;

        public:
            explicit FReceiveGlobalMessageTask(
                TSharedPtr<FEzUserGameSessionDomain> Self
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<TArray<TSharedPtr<Gs2::UE5::Inbox::Domain::Model::FEzMessageGameSessionDomain>>>> Result
            ) override;
        };
        friend FReceiveGlobalMessageTask;

        TSharedPtr<FAsyncTask<FReceiveGlobalMessageTask>> ReceiveGlobalMessage(
        );

        Gs2::UE5::Inbox::Domain::Iterator::FEzDescribeMessagesIteratorPtr Messages(
            const TOptional<bool> IsRead = TOptional<bool>()
        ) const;

        Gs2::Core::Domain::CallbackID SubscribeMessages(TFunction<void()> Callback);

        void UnsubscribeMessages(Gs2::Core::Domain::CallbackID CallbackId);

        Gs2::UE5::Inbox::Domain::Model::FEzMessageGameSessionDomainPtr Message(
            const FString MessageName
        ) const;

    };
    typedef TSharedPtr<FEzUserGameSessionDomain> FEzUserGameSessionDomainPtr;
}
