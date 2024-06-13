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
#include "Idle/Domain/Model/StatusAccessToken.h"
#include "Idle/Model/Gs2IdleEzCategoryModel.h"
#include "Idle/Model/Gs2IdleEzStatus.h"
#include "Idle/Model/Gs2IdleEzConfig.h"
#include "Idle/Model/Gs2IdleEzAcquireAction.h"
#include "Idle/Model/Gs2IdleEzAcquireActionList.h"
#include "Gs2IdleEzStatusGameSessionDomain.h"
#include "Idle/Domain/Iterator/Gs2IdleEzDescribeStatusesIterator.h"
#include "Util/Net/GameSession.h"
#include "Util/Net/Gs2Connection.h"

namespace Gs2::UE5::Idle::Domain::Model
{

    class EZGS2_API FEzStatusGameSessionDomain final :
        public TSharedFromThis<FEzStatusGameSessionDomain>
    {
        Gs2::Idle::Domain::Model::FStatusAccessTokenDomainPtr Domain;
        Gs2::UE5::Util::IGameSessionPtr GameSession;
        Gs2::UE5::Util::FGs2ConnectionPtr ConnectionValue;

        public:
        TOptional<FString> TransactionId() const;
        TOptional<bool> AutoRunStampSheet() const;
        TOptional<FString> NamespaceName() const;
        TOptional<FString> UserId() const;
        TOptional<FString> CategoryName() const;

        FEzStatusGameSessionDomain(
            Gs2::Idle::Domain::Model::FStatusAccessTokenDomainPtr Domain,
            Gs2::UE5::Util::IGameSessionPtr GameSession,
            Gs2::UE5::Util::FGs2ConnectionPtr Connection
        );

        class EZGS2_API FPredictionTask :
            public Gs2::Core::Util::TGs2Future<TArray<TSharedPtr<Gs2::UE5::Idle::Model::FEzAcquireAction>>>,
            public TSharedFromThis<FPredictionTask>
        {
            TSharedPtr<FEzStatusGameSessionDomain> Self;

        public:
            explicit FPredictionTask(
                TSharedPtr<FEzStatusGameSessionDomain> Self
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<TArray<TSharedPtr<Gs2::UE5::Idle::Model::FEzAcquireAction>>>> Result
            ) override;
        };
        friend FPredictionTask;

        TSharedPtr<FAsyncTask<FPredictionTask>> Prediction(
        );

        class EZGS2_API FReceiveTask :
            public Gs2::Core::Util::TGs2Future<Gs2::UE5::Idle::Domain::Model::FEzStatusGameSessionDomain>,
            public TSharedFromThis<FReceiveTask>
        {
            TSharedPtr<FEzStatusGameSessionDomain> Self;

        public:
            explicit FReceiveTask(
                TSharedPtr<FEzStatusGameSessionDomain> Self
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::UE5::Idle::Domain::Model::FEzStatusGameSessionDomain>> Result
            ) override;
        };
        friend FReceiveTask;

        TSharedPtr<FAsyncTask<FReceiveTask>> Receive(
        );

        class EZGS2_API FModelTask :
            public Gs2::Core::Util::TGs2Future<Gs2::UE5::Idle::Model::FEzStatus>,
            public TSharedFromThis<FModelTask>
        {
            TSharedPtr<FEzStatusGameSessionDomain> Self;

        public:
            explicit FModelTask(
                TSharedPtr<FEzStatusGameSessionDomain> Self
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<Gs2::UE5::Idle::Model::FEzStatusPtr> Result
            ) override;
        };

        TSharedPtr<FAsyncTask<FModelTask>> Model();

        Gs2::Core::Domain::CallbackID Subscribe(TFunction<void(Gs2::UE5::Idle::Model::FEzStatusPtr)> Callback);

        void Unsubscribe(Gs2::Core::Domain::CallbackID CallbackId);

    };
    typedef TSharedPtr<FEzStatusGameSessionDomain> FEzStatusGameSessionDomainPtr;
}
