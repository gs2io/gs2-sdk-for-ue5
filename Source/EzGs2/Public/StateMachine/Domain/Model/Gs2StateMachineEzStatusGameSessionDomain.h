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
#include "StateMachine/Domain/Model/StatusAccessToken.h"
#include "StateMachine/Model/Gs2StateMachineEzStatus.h"
#include "StateMachine/Model/Gs2StateMachineEzStackEntry.h"
#include "StateMachine/Model/Gs2StateMachineEzVariable.h"
#include "StateMachine/Model/Gs2StateMachineEzChangeStateEvent.h"
#include "StateMachine/Model/Gs2StateMachineEzEmitEvent.h"
#include "StateMachine/Model/Gs2StateMachineEzEvent.h"
#include "StateMachine/Model/Gs2StateMachineEzRandomStatus.h"
#include "StateMachine/Model/Gs2StateMachineEzRandomUsed.h"
#include "StateMachine/Model/Gs2StateMachineEzVerifyActionResult.h"
#include "StateMachine/Model/Gs2StateMachineEzConsumeActionResult.h"
#include "StateMachine/Model/Gs2StateMachineEzAcquireActionResult.h"
#include "StateMachine/Model/Gs2StateMachineEzTransactionResult.h"
#include "Gs2StateMachineEzStatusGameSessionDomain.h"
#include "StateMachine/Domain/Iterator/Gs2StateMachineEzDescribeStatusesIterator.h"
#include "Core/EzTransactionGameSessionDomain.h"
#include "Util/Net/GameSession.h"
#include "Util/Net/Gs2Connection.h"

namespace Gs2::UE5::StateMachine::Domain::Model
{

    class EZGS2_API FEzStatusGameSessionDomain final :
        public TSharedFromThis<FEzStatusGameSessionDomain>
    {
        Gs2::StateMachine::Domain::Model::FStatusAccessTokenDomainPtr Domain;
        Gs2::UE5::Util::IGameSessionPtr GameSession;
        Gs2::UE5::Util::FGs2ConnectionPtr ConnectionValue;

        public:
        TOptional<FString> NamespaceName() const;
        TOptional<FString> UserId() const;
        TOptional<FString> StatusName() const;

        FEzStatusGameSessionDomain(
            Gs2::StateMachine::Domain::Model::FStatusAccessTokenDomainPtr Domain,
            Gs2::UE5::Util::IGameSessionPtr GameSession,
            Gs2::UE5::Util::FGs2ConnectionPtr Connection
        );

        class EZGS2_API FEmitTask :
            public Gs2::Core::Util::TGs2Future<Gs2::UE5::StateMachine::Domain::Model::FEzStatusGameSessionDomain>,
            public TSharedFromThis<FEmitTask>
        {
            TSharedPtr<FEzStatusGameSessionDomain> Self;
            FString EventName;
            TOptional<FString> Args;

        public:
            explicit FEmitTask(
                TSharedPtr<FEzStatusGameSessionDomain> Self,
                FString EventName,
                TOptional<FString> Args = TOptional<FString>()
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::UE5::StateMachine::Domain::Model::FEzStatusGameSessionDomain>> Result
            ) override;
        };
        friend FEmitTask;

        TSharedPtr<FAsyncTask<FEmitTask>> Emit(
            FString EventName,
            TOptional<FString> Args = TOptional<FString>()
        );

        class EZGS2_API FReportTask :
            public Gs2::Core::Util::TGs2Future<Gs2::UE5::StateMachine::Domain::Model::FEzStatusGameSessionDomain>,
            public TSharedFromThis<FReportTask>
        {
            TSharedPtr<FEzStatusGameSessionDomain> Self;
            TOptional<TArray<TSharedPtr<Gs2::UE5::StateMachine::Model::FEzEvent>>> Events;

        public:
            explicit FReportTask(
                TSharedPtr<FEzStatusGameSessionDomain> Self,
                TOptional<TArray<TSharedPtr<Gs2::UE5::StateMachine::Model::FEzEvent>>> Events = TOptional<TArray<TSharedPtr<Gs2::UE5::StateMachine::Model::FEzEvent>>>()
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::UE5::StateMachine::Domain::Model::FEzStatusGameSessionDomain>> Result
            ) override;
        };
        friend FReportTask;

        TSharedPtr<FAsyncTask<FReportTask>> Report(
            TOptional<TArray<TSharedPtr<Gs2::UE5::StateMachine::Model::FEzEvent>>> Events = TOptional<TArray<TSharedPtr<Gs2::UE5::StateMachine::Model::FEzEvent>>>()
        );

        class EZGS2_API FExitTask :
            public Gs2::Core::Util::TGs2Future<Gs2::UE5::StateMachine::Domain::Model::FEzStatusGameSessionDomain>,
            public TSharedFromThis<FExitTask>
        {
            TSharedPtr<FEzStatusGameSessionDomain> Self;

        public:
            explicit FExitTask(
                TSharedPtr<FEzStatusGameSessionDomain> Self
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::UE5::StateMachine::Domain::Model::FEzStatusGameSessionDomain>> Result
            ) override;
        };
        friend FExitTask;

        TSharedPtr<FAsyncTask<FExitTask>> Exit(
        );

        class EZGS2_API FModelTask :
            public Gs2::Core::Util::TGs2Future<Gs2::UE5::StateMachine::Model::FEzStatus>,
            public TSharedFromThis<FModelTask>
        {
            TSharedPtr<FEzStatusGameSessionDomain> Self;

        public:
            explicit FModelTask(
                TSharedPtr<FEzStatusGameSessionDomain> Self
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<Gs2::UE5::StateMachine::Model::FEzStatusPtr> Result
            ) override;
        };

        TSharedPtr<FAsyncTask<FModelTask>> Model();

        Gs2::Core::Domain::CallbackID Subscribe(TFunction<void(Gs2::UE5::StateMachine::Model::FEzStatusPtr)> Callback);

        void Unsubscribe(Gs2::Core::Domain::CallbackID CallbackId);

    };
    typedef TSharedPtr<FEzStatusGameSessionDomain> FEzStatusGameSessionDomainPtr;
}
