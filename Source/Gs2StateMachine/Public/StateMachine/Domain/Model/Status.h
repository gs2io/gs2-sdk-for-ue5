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

// ReSharper disable CppUnusedIncludeDirective

#pragma once

#include "Core/Domain/Gs2Core.h"
#include "Auth/Gs2Auth.h"
#include "StateMachine/Gs2StateMachine.h"
#include "StateMachine/Domain/Iterator/DescribeNamespacesIterator.h"
#include "StateMachine/Domain/Iterator/DescribeStateMachineMastersIterator.h"
#include "StateMachine/Domain/Iterator/DescribeStatusesIterator.h"
#include "StateMachine/Domain/Iterator/DescribeStatusesByUserIdIterator.h"

namespace Gs2::Core::Domain
{
    class FGs2;
    typedef TSharedPtr<FGs2> FGs2Ptr;
}

namespace Gs2::StateMachine::Domain::Model
{
    class FNamespaceDomain;
    class FStateMachineMasterDomain;
    class FStatusDomain;
    class FStatusAccessTokenDomain;
    class FUserDomain;
    class FUserAccessTokenDomain;

    class GS2STATEMACHINE_API FStatusDomain:
        public TSharedFromThis<FStatusDomain>
    {
        const Core::Domain::FGs2Ptr Gs2;
        Gs2::StateMachine::FGs2StateMachineRestClientPtr Client;

        public:
        TOptional<FString> NamespaceName;
        TOptional<FString> UserId;
        TOptional<FString> StatusName;
    private:

        FString ParentKey;

    public:

        FStatusDomain(
            const Core::Domain::FGs2Ptr Gs2,
            const TOptional<FString> NamespaceName,
            const TOptional<FString> UserId,
            const TOptional<FString> StatusName
            // ReSharper disable once CppMemberInitializersOrder
        );

        FStatusDomain(
            const FStatusDomain& From
        );

        class GS2STATEMACHINE_API FGetTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::StateMachine::Model::FStatus>,
            public TSharedFromThis<FGetTask>
        {
            const TSharedPtr<FStatusDomain> Self;
            const Request::FGetStatusByUserIdRequestPtr Request;
        public:
            explicit FGetTask(
                const TSharedPtr<FStatusDomain> Self,
                const Request::FGetStatusByUserIdRequestPtr Request
            );

            FGetTask(
                const FGetTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::StateMachine::Model::FStatus>> Result
            ) override;
        };
        friend FGetTask;

        TSharedPtr<FAsyncTask<FGetTask>> Get(
            Request::FGetStatusByUserIdRequestPtr Request
        );

        class GS2STATEMACHINE_API FEmitTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::StateMachine::Domain::Model::FStatusDomain>,
            public TSharedFromThis<FEmitTask>
        {
            const TSharedPtr<FStatusDomain> Self;
            const Request::FEmitByUserIdRequestPtr Request;
        public:
            explicit FEmitTask(
                const TSharedPtr<FStatusDomain> Self,
                const Request::FEmitByUserIdRequestPtr Request
            );

            FEmitTask(
                const FEmitTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::StateMachine::Domain::Model::FStatusDomain>> Result
            ) override;
        };
        friend FEmitTask;

        TSharedPtr<FAsyncTask<FEmitTask>> Emit(
            Request::FEmitByUserIdRequestPtr Request
        );

        class GS2STATEMACHINE_API FDeleteTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::StateMachine::Domain::Model::FStatusDomain>,
            public TSharedFromThis<FDeleteTask>
        {
            const TSharedPtr<FStatusDomain> Self;
            const Request::FDeleteStatusByUserIdRequestPtr Request;
        public:
            explicit FDeleteTask(
                const TSharedPtr<FStatusDomain> Self,
                const Request::FDeleteStatusByUserIdRequestPtr Request
            );

            FDeleteTask(
                const FDeleteTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::StateMachine::Domain::Model::FStatusDomain>> Result
            ) override;
        };
        friend FDeleteTask;

        TSharedPtr<FAsyncTask<FDeleteTask>> Delete(
            Request::FDeleteStatusByUserIdRequestPtr Request
        );

        class GS2STATEMACHINE_API FExitStateMachineTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::StateMachine::Domain::Model::FStatusDomain>,
            public TSharedFromThis<FExitStateMachineTask>
        {
            const TSharedPtr<FStatusDomain> Self;
            const Request::FExitStateMachineByUserIdRequestPtr Request;
        public:
            explicit FExitStateMachineTask(
                const TSharedPtr<FStatusDomain> Self,
                const Request::FExitStateMachineByUserIdRequestPtr Request
            );

            FExitStateMachineTask(
                const FExitStateMachineTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::StateMachine::Domain::Model::FStatusDomain>> Result
            ) override;
        };
        friend FExitStateMachineTask;

        TSharedPtr<FAsyncTask<FExitStateMachineTask>> ExitStateMachine(
            Request::FExitStateMachineByUserIdRequestPtr Request
        );

        static FString CreateCacheParentKey(
            TOptional<FString> NamespaceName,
            TOptional<FString> UserId,
            TOptional<FString> StatusName,
            FString ChildType
        );

        static FString CreateCacheKey(
            TOptional<FString> StatusName
        );

        class GS2STATEMACHINE_API FModelTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::StateMachine::Model::FStatus>,
            public TSharedFromThis<FModelTask>
        {
            const TSharedPtr<FStatusDomain> Self;
        public:
            explicit FModelTask(
                const TSharedPtr<FStatusDomain> Self
            );

            FModelTask(
                const FModelTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::StateMachine::Model::FStatus>> Result
            ) override;
        };
        friend FModelTask;

        TSharedPtr<FAsyncTask<FModelTask>> Model();

        Gs2::Core::Domain::CallbackID Subscribe(
            TFunction<void(Gs2::StateMachine::Model::FStatusPtr)> Callback
        );

        void Unsubscribe(
            Gs2::Core::Domain::CallbackID CallbackID
        );

    };

    typedef TSharedPtr<FStatusDomain> FStatusDomainPtr;
}
