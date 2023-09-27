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

namespace Gs2::StateMachine::Domain::Model
{
    class FNamespaceDomain;
    class FStateMachineMasterDomain;
    class FStatusDomain;
    class FStatusAccessTokenDomain;
    class FUserDomain;
    class FUserAccessTokenDomain;

    class GS2STATEMACHINE_API FUserAccessTokenDomain:
        public TSharedFromThis<FUserAccessTokenDomain>
    {
        Core::Domain::FCacheDatabasePtr Cache;
        Gs2::Core::Domain::Model::FJobQueueDomainPtr JobQueueDomain;
        Gs2::Core::Domain::Model::FStampSheetConfigurationPtr StampSheetConfiguration;
        Gs2::Core::Net::Rest::FGs2RestSessionPtr Session;
        Gs2::StateMachine::FGs2StateMachineRestClientPtr Client;

        public:
        TOptional<FString> NextPageToken;
        TOptional<FString> GetNextPageToken() const
        {
            return NextPageToken;
        }
        TOptional<FString> NamespaceName;
        Gs2::Auth::Model::FAccessTokenPtr AccessToken;
        TOptional<FString> UserId() const { return AccessToken->GetUserId(); }
    private:

        FString ParentKey;

    public:

        FUserAccessTokenDomain(
            const Core::Domain::FCacheDatabasePtr Cache,
            const Gs2::Core::Domain::Model::FJobQueueDomainPtr JobQueueDomain,
            const Gs2::Core::Domain::Model::FStampSheetConfigurationPtr StampSheetConfiguration,
            const Gs2::Core::Net::Rest::FGs2RestSessionPtr Session,
            const TOptional<FString> NamespaceName,
            const Gs2::Auth::Model::FAccessTokenPtr AccessToken
            // ReSharper disable once CppMemberInitializersOrder
        );

        FUserAccessTokenDomain(
            const FUserAccessTokenDomain& From
        );

        Gs2::StateMachine::Domain::Iterator::FDescribeStatusesIteratorPtr Statuses(
            const TOptional<FString> Status
        ) const;

        Gs2::Core::Domain::CallbackID SubscribeStatuses(
            TFunction<void()> Callback
        );

        void UnsubscribeStatuses(
            Gs2::Core::Domain::CallbackID CallbackID
        );

        TSharedPtr<Gs2::StateMachine::Domain::Model::FStatusAccessTokenDomain> Status(
            const FString StatusName
        ) const;

        static FString CreateCacheParentKey(
            TOptional<FString> NamespaceName,
            TOptional<FString> UserId,
            FString ChildType
        );

        static FString CreateCacheKey(
            TOptional<FString> UserId
        );

    };

    typedef TSharedPtr<FUserAccessTokenDomain> FUserAccessTokenDomainPtr;
}
