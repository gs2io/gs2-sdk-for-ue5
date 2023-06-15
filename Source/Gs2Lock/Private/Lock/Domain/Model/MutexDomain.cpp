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

#include "Lock/Domain/Model/Mutex.h"
#include "Lock/Domain/Model/Namespace.h"
#include "Lock/Domain/Model/Mutex.h"
#include "Lock/Domain/Model/MutexAccessToken.h"
#include "Lock/Domain/Model/User.h"
#include "Lock/Domain/Model/UserAccessToken.h"

#include "Core/Domain/Model/AutoStampSheetDomain.h"
#include "Core/Domain/Model/StampSheetDomain.h"

namespace Gs2::Lock::Domain::Model
{

    FMutexDomain::FMutexDomain(
        const Core::Domain::FCacheDatabasePtr Cache,
        const Gs2::Core::Domain::Model::FJobQueueDomainPtr JobQueueDomain,
        const Gs2::Core::Domain::Model::FStampSheetConfigurationPtr StampSheetConfiguration,
        const Gs2::Core::Net::Rest::FGs2RestSessionPtr Session,
        const TOptional<FString> NamespaceName,
        const TOptional<FString> UserId,
        const TOptional<FString> PropertyId
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Cache(Cache),
        JobQueueDomain(JobQueueDomain),
        StampSheetConfiguration(StampSheetConfiguration),
        Session(Session),
        Client(MakeShared<Gs2::Lock::FGs2LockRestClient>(Session)),
        NamespaceName(NamespaceName),
        UserId(UserId),
        PropertyId(PropertyId),
        ParentKey(Gs2::Lock::Domain::Model::FUserDomain::CreateCacheParentKey(
            NamespaceName,
            UserId,
            "Mutex"
        ))
    {
    }

    FMutexDomain::FMutexDomain(
        const FMutexDomain& From
    ):
        Cache(From.Cache),
        JobQueueDomain(From.JobQueueDomain),
        StampSheetConfiguration(From.StampSheetConfiguration),
        Session(From.Session),
        Client(From.Client)
    {

    }

    FMutexDomain::FLockTask::FLockTask(
        const TSharedPtr<FMutexDomain> Self,
        const Request::FLockByUserIdRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FMutexDomain::FLockTask::FLockTask(
        const FLockTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FMutexDomain::FLockTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Lock::Domain::Model::FMutexDomain>> Result
    )
    {
        Request
            ->WithNamespaceName(Self->NamespaceName)
            ->WithUserId(Self->UserId)
            ->WithPropertyId(Self->PropertyId);
        const auto Future = Self->Client->LockByUserId(
            Request
        );
        Future->StartSynchronousTask();
        if (Future->GetTask().IsError())
        {
            return Future->GetTask().Error();
        }
        const auto RequestModel = Request;
        const auto ResultModel = Future->GetTask().Result();
        Future->EnsureCompletion();
        if (ResultModel != nullptr) {
            
            if (ResultModel->GetItem() != nullptr)
            {
                const auto ParentKey = Gs2::Lock::Domain::Model::FUserDomain::CreateCacheParentKey(
                    Self->NamespaceName,
                    Self->UserId,
                    "Mutex"
                );
                const auto Key = Gs2::Lock::Domain::Model::FMutexDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetPropertyId()
                );
                Self->Cache->Put(
                    Gs2::Lock::Model::FMutex::TypeName,
                    ParentKey,
                    Key,
                    ResultModel->GetItem(),
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );
            }
        }
        auto Domain = Self;

        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FMutexDomain::FLockTask>> FMutexDomain::Lock(
        Request::FLockByUserIdRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FLockTask>>(this->AsShared(), Request);
    }

    FMutexDomain::FUnlockTask::FUnlockTask(
        const TSharedPtr<FMutexDomain> Self,
        const Request::FUnlockByUserIdRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FMutexDomain::FUnlockTask::FUnlockTask(
        const FUnlockTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FMutexDomain::FUnlockTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Lock::Domain::Model::FMutexDomain>> Result
    )
    {
        Request
            ->WithNamespaceName(Self->NamespaceName)
            ->WithUserId(Self->UserId)
            ->WithPropertyId(Self->PropertyId);
        const auto Future = Self->Client->UnlockByUserId(
            Request
        );
        Future->StartSynchronousTask();
        if (Future->GetTask().IsError())
        {
            return Future->GetTask().Error();
        }
        const auto RequestModel = Request;
        const auto ResultModel = Future->GetTask().Result();
        Future->EnsureCompletion();
        if (ResultModel != nullptr) {
            
            if (ResultModel->GetItem() != nullptr)
            {
                const auto ParentKey = Gs2::Lock::Domain::Model::FUserDomain::CreateCacheParentKey(
                    Self->NamespaceName,
                    Self->UserId,
                    "Mutex"
                );
                const auto Key = Gs2::Lock::Domain::Model::FMutexDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetPropertyId()
                );
                Self->Cache->Put(
                    Gs2::Lock::Model::FMutex::TypeName,
                    ParentKey,
                    Key,
                    ResultModel->GetItem(),
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );
            }
        }
        auto Domain = Self;

        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FMutexDomain::FUnlockTask>> FMutexDomain::Unlock(
        Request::FUnlockByUserIdRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FUnlockTask>>(this->AsShared(), Request);
    }

    FMutexDomain::FGetTask::FGetTask(
        const TSharedPtr<FMutexDomain> Self,
        const Request::FGetMutexByUserIdRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FMutexDomain::FGetTask::FGetTask(
        const FGetTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FMutexDomain::FGetTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Lock::Model::FMutex>> Result
    )
    {
        Request
            ->WithNamespaceName(Self->NamespaceName)
            ->WithUserId(Self->UserId)
            ->WithPropertyId(Self->PropertyId);
        const auto Future = Self->Client->GetMutexByUserId(
            Request
        );
        Future->StartSynchronousTask();
        if (Future->GetTask().IsError())
        {
            return Future->GetTask().Error();
        }
        const auto RequestModel = Request;
        const auto ResultModel = Future->GetTask().Result();
        Future->EnsureCompletion();
        if (ResultModel != nullptr) {
            
            if (ResultModel->GetItem() != nullptr)
            {
                const auto ParentKey = Gs2::Lock::Domain::Model::FUserDomain::CreateCacheParentKey(
                    Self->NamespaceName,
                    Self->UserId,
                    "Mutex"
                );
                const auto Key = Gs2::Lock::Domain::Model::FMutexDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetPropertyId()
                );
                Self->Cache->Put(
                    Gs2::Lock::Model::FMutex::TypeName,
                    ParentKey,
                    Key,
                    ResultModel->GetItem(),
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );
            }
        }
        *Result = ResultModel->GetItem();
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FMutexDomain::FGetTask>> FMutexDomain::Get(
        Request::FGetMutexByUserIdRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FGetTask>>(this->AsShared(), Request);
    }

    FMutexDomain::FDeleteTask::FDeleteTask(
        const TSharedPtr<FMutexDomain> Self,
        const Request::FDeleteMutexByUserIdRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FMutexDomain::FDeleteTask::FDeleteTask(
        const FDeleteTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FMutexDomain::FDeleteTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Lock::Domain::Model::FMutexDomain>> Result
    )
    {
        Request
            ->WithNamespaceName(Self->NamespaceName)
            ->WithUserId(Self->UserId)
            ->WithPropertyId(Self->PropertyId);
        const auto Future = Self->Client->DeleteMutexByUserId(
            Request
        );
        Future->StartSynchronousTask();
        if (Future->GetTask().IsError())
        {
            return Future->GetTask().Error();
        }
        const auto RequestModel = Request;
        const auto ResultModel = Future->GetTask().Result();
        Future->EnsureCompletion();
        if (ResultModel != nullptr) {
            
            if (ResultModel->GetItem() != nullptr)
            {
                const auto ParentKey = Gs2::Lock::Domain::Model::FUserDomain::CreateCacheParentKey(
                    Self->NamespaceName,
                    Self->UserId,
                    "Mutex"
                );
                const auto Key = Gs2::Lock::Domain::Model::FMutexDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetPropertyId()
                );
                Self->Cache->Delete(Gs2::Lock::Model::FMutex::TypeName, ParentKey, Key);
            }
        }
        auto Domain = Self;

        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FMutexDomain::FDeleteTask>> FMutexDomain::Delete(
        Request::FDeleteMutexByUserIdRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FDeleteTask>>(this->AsShared(), Request);
    }

    FString FMutexDomain::CreateCacheParentKey(
        TOptional<FString> NamespaceName,
        TOptional<FString> UserId,
        TOptional<FString> PropertyId,
        FString ChildType
    )
    {
        return FString() +
            (NamespaceName.IsSet() ? *NamespaceName : "null") + ":" +
            (UserId.IsSet() ? *UserId : "null") + ":" +
            (PropertyId.IsSet() ? *PropertyId : "null") + ":" +
            ChildType;
    }

    FString FMutexDomain::CreateCacheKey(
        TOptional<FString> PropertyId
    )
    {
        return FString() +
            (PropertyId.IsSet() ? *PropertyId : "null");
    }

    FMutexDomain::FModelTask::FModelTask(
        const TSharedPtr<FMutexDomain> Self
    ): Self(Self)
    {

    }

    FMutexDomain::FModelTask::FModelTask(
        const FModelTask& From
    ): TGs2Future(From), Self(From.Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FMutexDomain::FModelTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Lock::Model::FMutex>> Result
    )
    {
        // ReSharper disable once CppLocalVariableMayBeConst
        TSharedPtr<Gs2::Lock::Model::FMutex> Value;
        auto bCacheHit = Self->Cache->TryGet<Gs2::Lock::Model::FMutex>(
            Self->ParentKey,
            Gs2::Lock::Domain::Model::FMutexDomain::CreateCacheKey(
                Self->PropertyId
            ),
            &Value
        );
        if (!bCacheHit) {
            const auto Future = Self->Get(
                MakeShared<Gs2::Lock::Request::FGetMutexByUserIdRequest>()
            );
            Future->StartSynchronousTask();
            if (Future->GetTask().IsError())
            {
                if (Future->GetTask().Error()->Type() != Gs2::Core::Model::FNotFoundError::TypeString)
                {
                    return Future->GetTask().Error();
                }

                const auto Key = Gs2::Lock::Domain::Model::FMutexDomain::CreateCacheKey(
                    Self->PropertyId
                );
                Self->Cache->Put(
                    Gs2::Lock::Model::FMutex::TypeName,
                    Self->ParentKey,
                    Key,
                    nullptr,
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );

                if (Future->GetTask().Error()->Detail(0)->GetComponent() != "mutex")
                {
                    return Future->GetTask().Error();
                }
            }
            Self->Cache->TryGet<Gs2::Lock::Model::FMutex>(
                Self->ParentKey,
                Gs2::Lock::Domain::Model::FMutexDomain::CreateCacheKey(
                    Self->PropertyId
                ),
                &Value
            );
            Future->EnsureCompletion();
        }
        *Result = Value;

        return nullptr;
    }

    TSharedPtr<FAsyncTask<FMutexDomain::FModelTask>> FMutexDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FMutexDomain::FModelTask>>(this->AsShared());
    }
}

#if defined(_MSC_VER)
#pragma warning (pop)
#elif defined(__clang__)
#pragma clang diagnostic pop
#endif

