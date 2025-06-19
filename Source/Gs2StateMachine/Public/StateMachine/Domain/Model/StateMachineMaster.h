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

    class GS2STATEMACHINE_API FStateMachineMasterDomain:
        public TSharedFromThis<FStateMachineMasterDomain>
    {
        const Core::Domain::FGs2Ptr Gs2;
        const StateMachine::Domain::FGs2StateMachineDomainPtr Service;
        const Gs2::StateMachine::FGs2StateMachineRestClientPtr Client;

        public:
        TOptional<FString> NamespaceName;
        TOptional<int64> Version;
    private:

        FString ParentKey;

    public:

        FStateMachineMasterDomain(
            const Core::Domain::FGs2Ptr& Gs2,
            const StateMachine::Domain::FGs2StateMachineDomainPtr& Service,
            const TOptional<FString> NamespaceName,
            const TOptional<int64> Version
            // ReSharper disable once CppMemberInitializersOrder
        );

        FStateMachineMasterDomain(
            const FStateMachineMasterDomain& From
        );

        class GS2STATEMACHINE_API FGetTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::StateMachine::Model::FStateMachineMaster>,
            public TSharedFromThis<FGetTask>
        {
            const TSharedPtr<FStateMachineMasterDomain> Self;
            const Request::FGetStateMachineMasterRequestPtr Request;
        public:
            explicit FGetTask(
                const TSharedPtr<FStateMachineMasterDomain>& Self,
                const Request::FGetStateMachineMasterRequestPtr Request
            );

            FGetTask(
                const FGetTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::StateMachine::Model::FStateMachineMaster>> Result
            ) override;
        };
        friend FGetTask;

        TSharedPtr<FAsyncTask<FGetTask>> Get(
            Request::FGetStateMachineMasterRequestPtr Request
        );

        class GS2STATEMACHINE_API FDeleteTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::StateMachine::Domain::Model::FStateMachineMasterDomain>,
            public TSharedFromThis<FDeleteTask>
        {
            const TSharedPtr<FStateMachineMasterDomain> Self;
            const Request::FDeleteStateMachineMasterRequestPtr Request;
        public:
            explicit FDeleteTask(
                const TSharedPtr<FStateMachineMasterDomain>& Self,
                const Request::FDeleteStateMachineMasterRequestPtr Request
            );

            FDeleteTask(
                const FDeleteTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::StateMachine::Domain::Model::FStateMachineMasterDomain>> Result
            ) override;
        };
        friend FDeleteTask;

        TSharedPtr<FAsyncTask<FDeleteTask>> Delete(
            Request::FDeleteStateMachineMasterRequestPtr Request
        );

        static FString CreateCacheParentKey(
            TOptional<FString> NamespaceName,
            TOptional<int64> Version,
            FString ChildType
        );

        static FString CreateCacheKey(
            TOptional<int64> Version
        );

        class GS2STATEMACHINE_API FModelTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::StateMachine::Model::FStateMachineMaster>,
            public TSharedFromThis<FModelTask>
        {
            const TSharedPtr<FStateMachineMasterDomain> Self;
        public:
            explicit FModelTask(
                const TSharedPtr<FStateMachineMasterDomain> Self
            );

            FModelTask(
                const FModelTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::StateMachine::Model::FStateMachineMaster>> Result
            ) override;
        };
        friend FModelTask;

        TSharedPtr<FAsyncTask<FModelTask>> Model();

        Gs2::Core::Domain::CallbackID Subscribe(
            TFunction<void(Gs2::StateMachine::Model::FStateMachineMasterPtr)> Callback
        );

        void Unsubscribe(
            Gs2::Core::Domain::CallbackID CallbackID
        );

    };

    typedef TSharedPtr<FStateMachineMasterDomain> FStateMachineMasterDomainPtr;
}
