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

#include "Lock/Domain/Model/MutexAccessToken.h"
#include "Lock/Domain/Model/Mutex.h"
#include "Lock/Domain/Model/Namespace.h"
#include "Lock/Domain/Model/Mutex.h"
#include "Lock/Domain/Model/MutexAccessToken.h"
#include "Lock/Domain/Model/User.h"
#include "Lock/Domain/Model/UserAccessToken.h"

#include "Core/Domain/Gs2.h"
#include "Core/Domain/Transaction/JobQueueJobDomainFactory.h"
#include "Core/Domain/Transaction/InternalTransactionDomainFactory.h"
#include "Core/Domain/Transaction/ManualTransactionAccessTokenDomain.h"

namespace Gs2::Lock::Domain::Model
{

    FMutexAccessTokenDomain::FMutexAccessTokenDomain(
        const Core::Domain::FGs2Ptr& Gs2,
        const Lock::Domain::FGs2LockDomainPtr& Service,
        const TOptional<FString> NamespaceName,
        const Gs2::Auth::Model::FAccessTokenPtr& AccessToken,
        const TOptional<FString> PropertyId
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Gs2(Gs2),
        Service(Service),
        Client(MakeShared<Gs2::Lock::FGs2LockRestClient>(Gs2->RestSession)),
        NamespaceName(NamespaceName),
        AccessToken(AccessToken),
        PropertyId(PropertyId),
        ParentKey(Gs2::Lock::Domain::Model::FUserDomain::CreateCacheParentKey(
            NamespaceName,
            UserId(),
            "Mutex"
        ))
    {
    }

    FMutexAccessTokenDomain::FMutexAccessTokenDomain(
        const FMutexAccessTokenDomain& From
    ):
        Gs2(From.Gs2),
        Service(From.Service),
        Client(From.Client),
        NamespaceName(From.NamespaceName),
        AccessToken(From.AccessToken),
        PropertyId(From.PropertyId),
        ParentKey(From.ParentKey)
    {

    }

    FMutexAccessTokenDomain::FLockTask::FLockTask(
        const TSharedPtr<FMutexAccessTokenDomain>& Self,
        const Request::FLockRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FMutexAccessTokenDomain::FLockTask::FLockTask(
        const FLockTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FMutexAccessTokenDomain::FLockTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Lock::Domain::Model::FMutexAccessTokenDomain>> Result
    )
    {
        Request
            ->WithContextStack(Self->Gs2->DefaultContextStack)
            ->WithNamespaceName(Self->NamespaceName)
            ->WithPropertyId(Self->PropertyId)
            ->WithAccessToken(Self->AccessToken->GetToken());
        const auto Future = Self->Client->Lock(
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
                    Self->UserId(),
                    "Mutex"
                );
                const auto Key = Gs2::Lock::Domain::Model::FMutexDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetPropertyId()
                );
                Self->Gs2->Cache->Put(
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

    TSharedPtr<FAsyncTask<FMutexAccessTokenDomain::FLockTask>> FMutexAccessTokenDomain::Lock(
        Request::FLockRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FLockTask>>(this->AsShared(), Request);
    }

    FMutexAccessTokenDomain::FUnlockTask::FUnlockTask(
        const TSharedPtr<FMutexAccessTokenDomain>& Self,
        const Request::FUnlockRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FMutexAccessTokenDomain::FUnlockTask::FUnlockTask(
        const FUnlockTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FMutexAccessTokenDomain::FUnlockTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Lock::Domain::Model::FMutexAccessTokenDomain>> Result
    )
    {
        Request
            ->WithContextStack(Self->Gs2->DefaultContextStack)
            ->WithNamespaceName(Self->NamespaceName)
            ->WithPropertyId(Self->PropertyId)
            ->WithAccessToken(Self->AccessToken->GetToken());
        const auto Future = Self->Client->Unlock(
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
                    Self->UserId(),
                    "Mutex"
                );
                const auto Key = Gs2::Lock::Domain::Model::FMutexDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetPropertyId()
                );
                Self->Gs2->Cache->Delete(Gs2::Lock::Model::FMutex::TypeName, ParentKey, Key);
            }
        }
        auto Domain = Self;

        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FMutexAccessTokenDomain::FUnlockTask>> FMutexAccessTokenDomain::Unlock(
        Request::FUnlockRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FUnlockTask>>(this->AsShared(), Request);
    }

    FMutexAccessTokenDomain::FGetTask::FGetTask(
        const TSharedPtr<FMutexAccessTokenDomain>& Self,
        const Request::FGetMutexRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FMutexAccessTokenDomain::FGetTask::FGetTask(
        const FGetTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FMutexAccessTokenDomain::FGetTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Lock::Model::FMutex>> Result
    )
    {
        Request
            ->WithContextStack(Self->Gs2->DefaultContextStack)
            ->WithNamespaceName(Self->NamespaceName)
            ->WithAccessToken(Self->AccessToken->GetToken())
            ->WithPropertyId(Self->PropertyId);
        const auto Future = Self->Client->GetMutex(
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
                    Self->UserId(),
                    "Mutex"
                );
                const auto Key = Gs2::Lock::Domain::Model::FMutexDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetPropertyId()
                );
                Self->Gs2->Cache->Put(
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

    TSharedPtr<FAsyncTask<FMutexAccessTokenDomain::FGetTask>> FMutexAccessTokenDomain::Get(
        Request::FGetMutexRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FGetTask>>(this->AsShared(), Request);
    }

    FString FMutexAccessTokenDomain::CreateCacheParentKey(
        TOptional<FString> NamespaceName,
        TOptional<FString> UserId,
        TOptional<FString> PropertyId,
        FString ChildType
    )
    {
        return FString("") +
            (NamespaceName.IsSet() ? *NamespaceName : "null") + ":" +
            (UserId.IsSet() ? *UserId : "null") + ":" +
            (PropertyId.IsSet() ? *PropertyId : "null") + ":" +
            ChildType;
    }

    FString FMutexAccessTokenDomain::CreateCacheKey(
        TOptional<FString> PropertyId
    )
    {
        return FString("") +
            (PropertyId.IsSet() ? *PropertyId : "null");
    }

    FMutexAccessTokenDomain::FModelTask::FModelTask(
        const TSharedPtr<FMutexAccessTokenDomain> Self
    ): Self(Self)
    {

    }

    FMutexAccessTokenDomain::FModelTask::FModelTask(
        const FModelTask& From
    ): TGs2Future(From), Self(From.Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FMutexAccessTokenDomain::FModelTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Lock::Model::FMutex>> Result
    )
    {
        // ReSharper disable once CppLocalVariableMayBeConst
        TSharedPtr<Gs2::Lock::Model::FMutex> Value;
        auto bCacheHit = Self->Gs2->Cache->TryGet<Gs2::Lock::Model::FMutex>(
            Self->ParentKey,
            Gs2::Lock::Domain::Model::FMutexDomain::CreateCacheKey(
                Self->PropertyId
            ),
            &Value
        );
        if (!bCacheHit) {
            const auto Future = Self->Get(
                MakeShared<Gs2::Lock::Request::FGetMutexRequest>()
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
                Self->Gs2->Cache->Put(
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
            Self->Gs2->Cache->TryGet<Gs2::Lock::Model::FMutex>(
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

    TSharedPtr<FAsyncTask<FMutexAccessTokenDomain::FModelTask>> FMutexAccessTokenDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FMutexAccessTokenDomain::FModelTask>>(this->AsShared());
    }

    Gs2::Core::Domain::CallbackID FMutexAccessTokenDomain::Subscribe(
        TFunction<void(Gs2::Lock::Model::FMutexPtr)> Callback
    )
    {
        return Gs2->Cache->Subscribe(
            Gs2::Lock::Model::FMutex::TypeName,
            ParentKey,
            Gs2::Lock::Domain::Model::FMutexDomain::CreateCacheKey(
                PropertyId
            ),
            [Callback](TSharedPtr<FGs2Object> obj)
            {
                Callback(StaticCastSharedPtr<Gs2::Lock::Model::FMutex>(obj));
            }
        );
    }

    void FMutexAccessTokenDomain::Unsubscribe(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        Gs2->Cache->Unsubscribe(
            Gs2::Lock::Model::FMutex::TypeName,
            ParentKey,
            Gs2::Lock::Domain::Model::FMutexDomain::CreateCacheKey(
                PropertyId
            ),
            CallbackID
        );
    }
}

#if defined(_MSC_VER)
#pragma warning (pop)
#elif defined(__clang__)
#pragma clang diagnostic pop
#endif

