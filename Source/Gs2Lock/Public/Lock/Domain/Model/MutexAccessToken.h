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

namespace Gs2::Core::Domain
{
    class FGs2;
    typedef TSharedPtr<FGs2> FGs2Ptr;
}

namespace Gs2::Lock::Domain
{
    class FGs2LockDomain;
    typedef TSharedPtr<FGs2LockDomain> FGs2LockDomainPtr;
}

namespace Gs2::Lock::Domain::Model
{
    class FNamespaceDomain;
    class FMutexDomain;
    class FMutexAccessTokenDomain;
    class FUserDomain;
    class FUserAccessTokenDomain;

    class GS2LOCK_API FMutexAccessTokenDomain:
        public TSharedFromThis<FMutexAccessTokenDomain>
    {
        const Core::Domain::FGs2Ptr Gs2;
        const Lock::Domain::FGs2LockDomainPtr Service;
        const Gs2::Lock::FGs2LockRestClientPtr Client;

        public:
        TOptional<FString> NamespaceName;
        Gs2::Auth::Model::FAccessTokenPtr AccessToken;
        TOptional<FString> UserId() const { return AccessToken->GetUserId(); }
        TOptional<FString> PropertyId;
    private:

        FString ParentKey;

    public:

        FMutexAccessTokenDomain(
            const Core::Domain::FGs2Ptr& Gs2,
            const Lock::Domain::FGs2LockDomainPtr& Service,
            const TOptional<FString> NamespaceName,
            const Gs2::Auth::Model::FAccessTokenPtr& AccessToken,
            const TOptional<FString> PropertyId
            // ReSharper disable once CppMemberInitializersOrder
        );

        FMutexAccessTokenDomain(
            const FMutexAccessTokenDomain& From
        );

        class GS2LOCK_API FLockTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Lock::Domain::Model::FMutexAccessTokenDomain>,
            public TSharedFromThis<FLockTask>
        {
            const TSharedPtr<FMutexAccessTokenDomain> Self;
            const Request::FLockRequestPtr Request;
        public:
            explicit FLockTask(
                const TSharedPtr<FMutexAccessTokenDomain>& Self,
                const Request::FLockRequestPtr Request
            );

            FLockTask(
                const FLockTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Lock::Domain::Model::FMutexAccessTokenDomain>> Result
            ) override;
        };
        friend FLockTask;

        TSharedPtr<FAsyncTask<FLockTask>> Lock(
            Request::FLockRequestPtr Request
        );

        class GS2LOCK_API FUnlockTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Lock::Domain::Model::FMutexAccessTokenDomain>,
            public TSharedFromThis<FUnlockTask>
        {
            const TSharedPtr<FMutexAccessTokenDomain> Self;
            const Request::FUnlockRequestPtr Request;
        public:
            explicit FUnlockTask(
                const TSharedPtr<FMutexAccessTokenDomain>& Self,
                const Request::FUnlockRequestPtr Request
            );

            FUnlockTask(
                const FUnlockTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Lock::Domain::Model::FMutexAccessTokenDomain>> Result
            ) override;
        };
        friend FUnlockTask;

        TSharedPtr<FAsyncTask<FUnlockTask>> Unlock(
            Request::FUnlockRequestPtr Request
        );

        class GS2LOCK_API FGetTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Lock::Model::FMutex>,
            public TSharedFromThis<FGetTask>
        {
            const TSharedPtr<FMutexAccessTokenDomain> Self;
            const Request::FGetMutexRequestPtr Request;
        public:
            explicit FGetTask(
                const TSharedPtr<FMutexAccessTokenDomain>& Self,
                const Request::FGetMutexRequestPtr Request
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
            Request::FGetMutexRequestPtr Request
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
            const TSharedPtr<FMutexAccessTokenDomain> Self;
        public:
            explicit FModelTask(
                const TSharedPtr<FMutexAccessTokenDomain> Self
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

    typedef TSharedPtr<FMutexAccessTokenDomain> FMutexAccessTokenDomainPtr;
}
