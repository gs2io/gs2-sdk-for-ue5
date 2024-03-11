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

    class GS2STATEMACHINE_API FUserDomain:
        public TSharedFromThis<FUserDomain>
    {
        const Core::Domain::FGs2Ptr Gs2;
        const StateMachine::Domain::FGs2StateMachineDomainPtr Service;
        const Gs2::StateMachine::FGs2StateMachineRestClientPtr Client;

        public:
        TOptional<FString> NextPageToken;
        TOptional<FString> GetNextPageToken() const
        {
            return NextPageToken;
        }
        TOptional<FString> NamespaceName;
        TOptional<FString> UserId;
    private:

        FString ParentKey;

    public:

        FUserDomain(
            const Core::Domain::FGs2Ptr& Gs2,
            const StateMachine::Domain::FGs2StateMachineDomainPtr& Service,
            const TOptional<FString> NamespaceName,
            const TOptional<FString> UserId
            // ReSharper disable once CppMemberInitializersOrder
        );

        FUserDomain(
            const FUserDomain& From
        );

        class GS2STATEMACHINE_API FStartStateMachineTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::StateMachine::Domain::Model::FStatusDomain>,
            public TSharedFromThis<FStartStateMachineTask>
        {
            const TSharedPtr<FUserDomain> Self;
            const Request::FStartStateMachineByUserIdRequestPtr Request;
        public:
            explicit FStartStateMachineTask(
                const TSharedPtr<FUserDomain>& Self,
                const Request::FStartStateMachineByUserIdRequestPtr Request
            );

            FStartStateMachineTask(
                const FStartStateMachineTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::StateMachine::Domain::Model::FStatusDomain>> Result
            ) override;
        };
        friend FStartStateMachineTask;

        TSharedPtr<FAsyncTask<FStartStateMachineTask>> StartStateMachine(
            Request::FStartStateMachineByUserIdRequestPtr Request
        );

        Gs2::StateMachine::Domain::Iterator::FDescribeStatusesByUserIdIteratorPtr Statuses(
            const TOptional<FString> Status = TOptional<FString>(),
            const TOptional<FString> TimeOffsetToken = TOptional<FString>()
        ) const;

        Gs2::Core::Domain::CallbackID SubscribeStatuses(
            TFunction<void()> Callback
        );

        void UnsubscribeStatuses(
            Gs2::Core::Domain::CallbackID CallbackID
        );

        TSharedPtr<Gs2::StateMachine::Domain::Model::FStatusDomain> Status(
            const FString StatusName
        );

        static FString CreateCacheParentKey(
            TOptional<FString> NamespaceName,
            TOptional<FString> UserId,
            FString ChildType
        );

        static FString CreateCacheKey(
            TOptional<FString> UserId
        );

    };

    typedef TSharedPtr<FUserDomain> FUserDomainPtr;
}
