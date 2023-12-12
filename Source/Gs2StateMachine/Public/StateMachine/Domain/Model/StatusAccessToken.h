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

namespace Gs2::StateMachine::Domain
{
    class FGs2StateMachineDomain;
    typedef TSharedPtr<FGs2StateMachineDomain> FGs2StateMachineDomainPtr;
}

namespace Gs2::StateMachine::Domain::Model
{
    class FNamespaceDomain;
    class FStateMachineMasterDomain;
    class FStatusDomain;
    class FStatusAccessTokenDomain;
    class FUserDomain;
    class FUserAccessTokenDomain;

    class GS2STATEMACHINE_API FStatusAccessTokenDomain:
        public TSharedFromThis<FStatusAccessTokenDomain>
    {
        const Core::Domain::FGs2Ptr Gs2;
        const StateMachine::Domain::FGs2StateMachineDomainPtr Service;
        const Gs2::StateMachine::FGs2StateMachineRestClientPtr Client;

        public:
        TOptional<FString> NamespaceName;
        Gs2::Auth::Model::FAccessTokenPtr AccessToken;
        TOptional<FString> UserId() const { return AccessToken->GetUserId(); }
        TOptional<FString> StatusName;
    private:

        FString ParentKey;

    public:

        FStatusAccessTokenDomain(
            const Core::Domain::FGs2Ptr& Gs2,
            const StateMachine::Domain::FGs2StateMachineDomainPtr& Service,
            const TOptional<FString> NamespaceName,
            const Gs2::Auth::Model::FAccessTokenPtr& AccessToken,
            const TOptional<FString> StatusName
            // ReSharper disable once CppMemberInitializersOrder
        );

        FStatusAccessTokenDomain(
            const FStatusAccessTokenDomain& From
        );

        class GS2STATEMACHINE_API FGetTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::StateMachine::Model::FStatus>,
            public TSharedFromThis<FGetTask>
        {
            const TSharedPtr<FStatusAccessTokenDomain> Self;
            const Request::FGetStatusRequestPtr Request;
        public:
            explicit FGetTask(
                const TSharedPtr<FStatusAccessTokenDomain>& Self,
                const Request::FGetStatusRequestPtr Request
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
            Request::FGetStatusRequestPtr Request
        );

        class GS2STATEMACHINE_API FEmitTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::StateMachine::Domain::Model::FStatusAccessTokenDomain>,
            public TSharedFromThis<FEmitTask>
        {
            const TSharedPtr<FStatusAccessTokenDomain> Self;
            const Request::FEmitRequestPtr Request;
        public:
            explicit FEmitTask(
                const TSharedPtr<FStatusAccessTokenDomain>& Self,
                const Request::FEmitRequestPtr Request
            );

            FEmitTask(
                const FEmitTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::StateMachine::Domain::Model::FStatusAccessTokenDomain>> Result
            ) override;
        };
        friend FEmitTask;

        TSharedPtr<FAsyncTask<FEmitTask>> Emit(
            Request::FEmitRequestPtr Request
        );

        class GS2STATEMACHINE_API FReportTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::StateMachine::Domain::Model::FStatusAccessTokenDomain>,
            public TSharedFromThis<FReportTask>
        {
            const TSharedPtr<FStatusAccessTokenDomain> Self;
            const Request::FReportRequestPtr Request;
        public:
            explicit FReportTask(
                const TSharedPtr<FStatusAccessTokenDomain>& Self,
                const Request::FReportRequestPtr Request
            );

            FReportTask(
                const FReportTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::StateMachine::Domain::Model::FStatusAccessTokenDomain>> Result
            ) override;
        };
        friend FReportTask;

        TSharedPtr<FAsyncTask<FReportTask>> Report(
            Request::FReportRequestPtr Request
        );

        class GS2STATEMACHINE_API FExitStateMachineTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::StateMachine::Domain::Model::FStatusAccessTokenDomain>,
            public TSharedFromThis<FExitStateMachineTask>
        {
            const TSharedPtr<FStatusAccessTokenDomain> Self;
            const Request::FExitStateMachineRequestPtr Request;
        public:
            explicit FExitStateMachineTask(
                const TSharedPtr<FStatusAccessTokenDomain>& Self,
                const Request::FExitStateMachineRequestPtr Request
            );

            FExitStateMachineTask(
                const FExitStateMachineTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::StateMachine::Domain::Model::FStatusAccessTokenDomain>> Result
            ) override;
        };
        friend FExitStateMachineTask;

        TSharedPtr<FAsyncTask<FExitStateMachineTask>> ExitStateMachine(
            Request::FExitStateMachineRequestPtr Request
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
            const TSharedPtr<FStatusAccessTokenDomain> Self;
        public:
            explicit FModelTask(
                const TSharedPtr<FStatusAccessTokenDomain> Self
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

    typedef TSharedPtr<FStatusAccessTokenDomain> FStatusAccessTokenDomainPtr;
}
