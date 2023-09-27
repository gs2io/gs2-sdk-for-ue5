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
#include "Lock/Gs2Lock.h"
#include "Lock/Domain/Iterator/DescribeNamespacesIterator.h"
#include "Lock/Domain/Iterator/DescribeMutexesIterator.h"
#include "Lock/Domain/Iterator/DescribeMutexesByUserIdIterator.h"

namespace Gs2::Lock::Domain::Model
{
    class FNamespaceDomain;
    class FMutexDomain;
    class FMutexAccessTokenDomain;
    class FUserDomain;
    class FUserAccessTokenDomain;

    class GS2LOCK_API FMutexDomain:
        public TSharedFromThis<FMutexDomain>
    {
        Core::Domain::FCacheDatabasePtr Cache;
        Gs2::Core::Domain::Model::FJobQueueDomainPtr JobQueueDomain;
        Gs2::Core::Domain::Model::FStampSheetConfigurationPtr StampSheetConfiguration;
        Gs2::Core::Net::Rest::FGs2RestSessionPtr Session;
        Gs2::Lock::FGs2LockRestClientPtr Client;

        public:
        TOptional<FString> NamespaceName;
        TOptional<FString> UserId;
        TOptional<FString> PropertyId;
    private:

        FString ParentKey;

    public:

        FMutexDomain(
            const Core::Domain::FCacheDatabasePtr Cache,
            const Gs2::Core::Domain::Model::FJobQueueDomainPtr JobQueueDomain,
            const Gs2::Core::Domain::Model::FStampSheetConfigurationPtr StampSheetConfiguration,
            const Gs2::Core::Net::Rest::FGs2RestSessionPtr Session,
            const TOptional<FString> NamespaceName,
            const TOptional<FString> UserId,
            const TOptional<FString> PropertyId
            // ReSharper disable once CppMemberInitializersOrder
        );

        FMutexDomain(
            const FMutexDomain& From
        );

        class GS2LOCK_API FLockTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Lock::Domain::Model::FMutexDomain>,
            public TSharedFromThis<FLockTask>
        {
            const TSharedPtr<FMutexDomain> Self;
            const Request::FLockByUserIdRequestPtr Request;
        public:
            explicit FLockTask(
                const TSharedPtr<FMutexDomain> Self,
                const Request::FLockByUserIdRequestPtr Request
            );

            FLockTask(
                const FLockTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Lock::Domain::Model::FMutexDomain>> Result
            ) override;
        };
        friend FLockTask;

        TSharedPtr<FAsyncTask<FLockTask>> Lock(
            Request::FLockByUserIdRequestPtr Request
        );

        class GS2LOCK_API FUnlockTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Lock::Domain::Model::FMutexDomain>,
            public TSharedFromThis<FUnlockTask>
        {
            const TSharedPtr<FMutexDomain> Self;
            const Request::FUnlockByUserIdRequestPtr Request;
        public:
            explicit FUnlockTask(
                const TSharedPtr<FMutexDomain> Self,
                const Request::FUnlockByUserIdRequestPtr Request
            );

            FUnlockTask(
                const FUnlockTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Lock::Domain::Model::FMutexDomain>> Result
            ) override;
        };
        friend FUnlockTask;

        TSharedPtr<FAsyncTask<FUnlockTask>> Unlock(
            Request::FUnlockByUserIdRequestPtr Request
        );

        class GS2LOCK_API FGetTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Lock::Model::FMutex>,
            public TSharedFromThis<FGetTask>
        {
            const TSharedPtr<FMutexDomain> Self;
            const Request::FGetMutexByUserIdRequestPtr Request;
        public:
            explicit FGetTask(
                const TSharedPtr<FMutexDomain> Self,
                const Request::FGetMutexByUserIdRequestPtr Request
            );

            FGetTask(
                const FGetTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Lock::Model::FMutex>> Result
            ) override;
        };
        friend FGetTask;

        TSharedPtr<FAsyncTask<FGetTask>> Get(
            Request::FGetMutexByUserIdRequestPtr Request
        );

        class GS2LOCK_API FDeleteTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Lock::Domain::Model::FMutexDomain>,
            public TSharedFromThis<FDeleteTask>
        {
            const TSharedPtr<FMutexDomain> Self;
            const Request::FDeleteMutexByUserIdRequestPtr Request;
        public:
            explicit FDeleteTask(
                const TSharedPtr<FMutexDomain> Self,
                const Request::FDeleteMutexByUserIdRequestPtr Request
            );

            FDeleteTask(
                const FDeleteTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Lock::Domain::Model::FMutexDomain>> Result
            ) override;
        };
        friend FDeleteTask;

        TSharedPtr<FAsyncTask<FDeleteTask>> Delete(
            Request::FDeleteMutexByUserIdRequestPtr Request
        );

        static FString CreateCacheParentKey(
            TOptional<FString> NamespaceName,
            TOptional<FString> UserId,
            TOptional<FString> PropertyId,
            FString ChildType
        );

        static FString CreateCacheKey(
            TOptional<FString> PropertyId
        );

        class GS2LOCK_API FModelTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Lock::Model::FMutex>,
            public TSharedFromThis<FModelTask>
        {
            const TSharedPtr<FMutexDomain> Self;
        public:
            explicit FModelTask(
                const TSharedPtr<FMutexDomain> Self
            );

            FModelTask(
                const FModelTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Lock::Model::FMutex>> Result
            ) override;
        };
        friend FModelTask;

        TSharedPtr<FAsyncTask<FModelTask>> Model();

        Gs2::Core::Domain::CallbackID Subscribe(
            TFunction<void(Gs2::Lock::Model::FMutexPtr)> Callback
        );

        void Unsubscribe(
            Gs2::Core::Domain::CallbackID CallbackID
        );

    };

    typedef TSharedPtr<FMutexDomain> FMutexDomainPtr;
}
