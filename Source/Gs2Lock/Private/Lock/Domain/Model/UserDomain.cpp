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

#if defined(_MSC_VER)
#pragma warning (push)
#pragma warning (disable: 4458) // Declaration hides class member
#elif defined(__clang__)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wshadow" // declaration shadows a field of
#endif

#include "Lock/Domain/Model/User.h"
#include "Lock/Domain/Model/Namespace.h"
#include "Lock/Domain/Model/Mutex.h"
#include "Lock/Domain/Model/MutexAccessToken.h"
#include "Lock/Domain/Model/User.h"
#include "Lock/Domain/Model/UserAccessToken.h"

#include "Core/Domain/Gs2.h"
#include "Core/Domain/Transaction/JobQueueJobDomainFactory.h"
#include "Core/Domain/Transaction/InternalTransactionDomainFactory.h"
#include "Core/Domain/Transaction/ManualTransactionDomain.h"

namespace Gs2::Lock::Domain::Model
{

    FUserDomain::FUserDomain(
        const Core::Domain::FGs2Ptr& Gs2,
        const Lock::Domain::FGs2LockDomainPtr& Service,
        const TOptional<FString> NamespaceName,
        const TOptional<FString> UserId
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Gs2(Gs2),
        Service(Service),
        Client(MakeShared<Gs2::Lock::FGs2LockRestClient>(Gs2->RestSession)),
        NamespaceName(NamespaceName),
        UserId(UserId),
        ParentKey(Gs2::Lock::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
            NamespaceName,
            "User"
        ))
    {
    }

    FUserDomain::FUserDomain(
        const FUserDomain& From
    ):
        Gs2(From.Gs2),
        Service(From.Service),
        Client(From.Client),
        NamespaceName(From.NamespaceName),
        UserId(From.UserId),
        ParentKey(From.ParentKey)
    {

    }

    Gs2::Lock::Domain::Iterator::FDescribeMutexesByUserIdIteratorPtr FUserDomain::Mutexes(
        const TOptional<FString> TimeOffsetToken
    ) const
    {
        return MakeShared<Gs2::Lock::Domain::Iterator::FDescribeMutexesByUserIdIterator>(
            Gs2->Cache,
            Client,
            NamespaceName,
            UserId,
            TimeOffsetToken
        );
    }

    Gs2::Core::Domain::CallbackID FUserDomain::SubscribeMutexes(
    TFunction<void()> Callback
    )
    {
        return Gs2->Cache->ListSubscribe(
            Gs2::Lock::Model::FMutex::TypeName,
            Gs2::Lock::Domain::Model::FUserDomain::CreateCacheParentKey(
                NamespaceName,
                UserId,
                "Mutex"
            ),
            Callback
        );
    }

    void FUserDomain::UnsubscribeMutexes(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        Gs2->Cache->ListUnsubscribe(
            Gs2::Lock::Model::FMutex::TypeName,
            Gs2::Lock::Domain::Model::FUserDomain::CreateCacheParentKey(
                NamespaceName,
                UserId,
                "Mutex"
            ),
            CallbackID
        );
    }

    TSharedPtr<Gs2::Lock::Domain::Model::FMutexDomain> FUserDomain::Mutex(
        const FString PropertyId
    )
    {
        return MakeShared<Gs2::Lock::Domain::Model::FMutexDomain>(
            Gs2,
            Service,
            NamespaceName,
            UserId,
            PropertyId == TEXT("") ? TOptional<FString>() : TOptional<FString>(PropertyId)
        );
    }

    FString FUserDomain::CreateCacheParentKey(
        TOptional<FString> NamespaceName,
        TOptional<FString> UserId,
        FString ChildType
    )
    {
        return FString("") +
            (NamespaceName.IsSet() ? *NamespaceName : "null") + ":" +
            (UserId.IsSet() ? *UserId : "null") + ":" +
            ChildType;
    }

    FString FUserDomain::CreateCacheKey(
        TOptional<FString> UserId
    )
    {
        return FString("") +
            (UserId.IsSet() ? *UserId : "null");
    }
}

#if defined(_MSC_VER)
#pragma warning (pop)
#elif defined(__clang__)
#pragma clang diagnostic pop
#endif

