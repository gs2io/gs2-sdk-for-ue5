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

#include "Core/Gs2Core.h"
#include "Core/Domain/Gs2Core.h"
#include "JobQueue/Gs2JobQueue.h"
#include "Lock/Gs2Lock.h"

// Model
#include "Lock/Domain/Model/Namespace.h"
#include "Lock/Domain/Model/Mutex.h"
#include "Lock/Domain/Model/MutexAccessToken.h"
#include "Lock/Domain/Model/User.h"
#include "Lock/Domain/Model/UserAccessToken.h"

// Iterator
#include "Lock/Domain/Iterator/DescribeNamespacesIterator.h"
#include "Lock/Domain/Iterator/DescribeMutexesIterator.h"
#include "Lock/Domain/Iterator/DescribeMutexesByUserIdIterator.h"

// Notification

namespace Gs2::Lock::Domain
{

    class GS2LOCK_API FGs2LockDomain:
        public TSharedFromThis<FGs2LockDomain>
    {
        Core::Domain::FCacheDatabasePtr Cache;
        Gs2::Core::Domain::Model::FJobQueueDomainPtr JobQueueDomain;
        Gs2::Core::Domain::Model::FStampSheetConfigurationPtr StampSheetConfiguration;
        Gs2::Core::Net::Rest::FGs2RestSessionPtr Session;
        Gs2::Lock::FGs2LockRestClientPtr Client;

        public:
    private:

        FString ParentKey;

    public:

        FGs2LockDomain(
            const Core::Domain::FCacheDatabasePtr Cache,
            const Gs2::Core::Domain::Model::FJobQueueDomainPtr JobQueueDomain,
            const Gs2::Core::Domain::Model::FStampSheetConfigurationPtr StampSheetConfiguration,
            const Gs2::Core::Net::Rest::FGs2RestSessionPtr Session
            // ReSharper disable once CppMemberInitializersOrder
        );

        FGs2LockDomain(
            const FGs2LockDomain& From
        );

        class GS2LOCK_API FCreateNamespaceTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Lock::Domain::Model::FNamespaceDomain>,
            public TSharedFromThis<FCreateNamespaceTask>
        {
            const TSharedPtr<FGs2LockDomain> Self;
            const Request::FCreateNamespaceRequestPtr Request;
        public:
            explicit FCreateNamespaceTask(
                const TSharedPtr<FGs2LockDomain> Self,
                const Request::FCreateNamespaceRequestPtr Request
            );

            FCreateNamespaceTask(
                const FCreateNamespaceTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Lock::Domain::Model::FNamespaceDomain>> Result
            ) override;
        };
        friend FCreateNamespaceTask;

        TSharedPtr<FAsyncTask<FCreateNamespaceTask>> CreateNamespace(
            Request::FCreateNamespaceRequestPtr Request
        );

        Gs2::Lock::Domain::Iterator::FDescribeNamespacesIteratorPtr Namespaces(
        ) const;

        Gs2::Core::Domain::CallbackID SubscribeNamespaces(
            TFunction<void()> Callback
        );

        void UnsubscribeNamespaces(
            Gs2::Core::Domain::CallbackID CallbackID
        );

        TSharedPtr<Gs2::Lock::Domain::Model::FNamespaceDomain> Namespace(
            const FString NamespaceName
        ) const;

        void UpdateCacheFromStampSheet(
            const FString Method,
            const FString Request,
            const FString Result
        );

        void UpdateCacheFromStampTask(
            const FString Method,
            const FString Request,
            const FString Result
        );

        void UpdateCacheFromJobResult(
            const FString Method,
            const Gs2::JobQueue::Model::FJobPtr Job,
            const Gs2::JobQueue::Model::FJobResultBodyPtr Result
        );

        void HandleNotification(
            const FString Action,
            const FString Payload
        );
    };
    typedef TSharedPtr<FGs2LockDomain> FGs2LockDomainPtr;
}
