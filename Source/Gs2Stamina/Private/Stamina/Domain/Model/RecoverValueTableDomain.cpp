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

#include "Stamina/Domain/Model/RecoverValueTable.h"
#include "Stamina/Domain/Model/Namespace.h"
#include "Stamina/Domain/Model/StaminaModelMaster.h"
#include "Stamina/Domain/Model/MaxStaminaTableMaster.h"
#include "Stamina/Domain/Model/RecoverIntervalTableMaster.h"
#include "Stamina/Domain/Model/RecoverValueTableMaster.h"
#include "Stamina/Domain/Model/CurrentStaminaMaster.h"
#include "Stamina/Domain/Model/StaminaModel.h"
#include "Stamina/Domain/Model/Stamina.h"
#include "Stamina/Domain/Model/StaminaAccessToken.h"
#include "Stamina/Domain/Model/User.h"
#include "Stamina/Domain/Model/UserAccessToken.h"

#include "Core/Domain/Gs2.h"
#include "Core/Domain/Transaction/JobQueueJobDomainFactory.h"
#include "Core/Domain/Transaction/InternalTransactionDomainFactory.h"
#include "Core/Domain/Transaction/ManualTransactionDomain.h"

namespace Gs2::Stamina::Domain::Model
{

    FRecoverValueTableDomain::FRecoverValueTableDomain(
        const Core::Domain::FGs2Ptr& Gs2,
        const Stamina::Domain::FGs2StaminaDomainPtr& Service
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Gs2(Gs2),
        Service(Service),
        Client(MakeShared<Gs2::Stamina::FGs2StaminaRestClient>(Gs2->RestSession)),
        ParentKey("stamina:RecoverValueTable")
    {
    }

    FRecoverValueTableDomain::FRecoverValueTableDomain(
        const FRecoverValueTableDomain& From
    ):
        Gs2(From.Gs2),
        Service(From.Service),
        Client(From.Client),
        ParentKey(From.ParentKey)
    {

    }

    FString FRecoverValueTableDomain::CreateCacheParentKey(
        FString ChildType
    )
    {
        return FString("") +
            ChildType;
    }

    FString FRecoverValueTableDomain::CreateCacheKey(
    )
    {
        return "Singleton";
    }

    FRecoverValueTableDomain::FModelTask::FModelTask(
        const TSharedPtr<FRecoverValueTableDomain> Self
    ): Self(Self)
    {

    }

    FRecoverValueTableDomain::FModelTask::FModelTask(
        const FModelTask& From
    ): TGs2Future(From), Self(From.Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FRecoverValueTableDomain::FModelTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Stamina::Model::FRecoverValueTable>> Result
    )
    {
        const FString CacheKey = Gs2::Stamina::Domain::Model::FRecoverValueTableDomain::CreateCacheKey(
        );
        return Self->Gs2->Cache->ExecuteWithKeyLock(
            Gs2::Stamina::Model::FRecoverValueTable::TypeName,
            Self->ParentKey,
            CacheKey,
            [this, Result, CacheKey]() -> Gs2::Core::Model::FGs2ErrorPtr
            {
                // ReSharper disable once CppLocalVariableMayBeConst
                TSharedPtr<Gs2::Stamina::Model::FRecoverValueTable> Value;
                auto bCacheHit = Self->Gs2->Cache->TryGet<Gs2::Stamina::Model::FRecoverValueTable>(
                    Self->ParentKey,
                    CacheKey,
                    &Value
                );
                *Result = Value;

                return nullptr;
            }
        );
    }

    TSharedPtr<FAsyncTask<FRecoverValueTableDomain::FModelTask>> FRecoverValueTableDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FRecoverValueTableDomain::FModelTask>>(this->AsShared());
    }

    void FRecoverValueTableDomain::Invalidate()
    {
        Gs2->Cache->Delete(
            Gs2::Stamina::Model::FRecoverValueTable::TypeName,
            ParentKey,
            Gs2::Stamina::Domain::Model::FRecoverValueTableDomain::CreateCacheKey(
            )
        );
    }

    FRecoverValueTableDomain::FSubscribeWithInitialCallTask::FSubscribeWithInitialCallTask(
        const TSharedPtr<FRecoverValueTableDomain>& Self,
        TFunction<void(Gs2::Stamina::Model::FRecoverValueTablePtr)> Callback
    ):
        Self(Self),
        Callback(Callback)
    {
    }

    FRecoverValueTableDomain::FSubscribeWithInitialCallTask::FSubscribeWithInitialCallTask(
        const FSubscribeWithInitialCallTask& From
    ):
        TGs2Future(From),
        Self(From.Self),
        Callback(From.Callback)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FRecoverValueTableDomain::FSubscribeWithInitialCallTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Core::Domain::CallbackID>> Result
    )
    {
        const auto Task = Self->Model();
        Task->StartSynchronousTask();
        Task->EnsureCompletion();
        if (Task->GetTask().IsError()) return Task->GetTask().Error();
        const auto Item = Task->GetTask().Result();
        const auto CallbackId = Self->Subscribe(Callback);
        Callback(Item);
        *Result = MakeShared<Gs2::Core::Domain::CallbackID>(CallbackId);
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FRecoverValueTableDomain::FSubscribeWithInitialCallTask>> FRecoverValueTableDomain::SubscribeWithInitialCall(
        TFunction<void(Gs2::Stamina::Model::FRecoverValueTablePtr)> Callback
    )
    {
        return Gs2::Core::Util::New<FAsyncTask<FSubscribeWithInitialCallTask>>(this->AsShared(), Callback);
    }

    Gs2::Core::Domain::CallbackID FRecoverValueTableDomain::Subscribe(
        TFunction<void(Gs2::Stamina::Model::FRecoverValueTablePtr)> Callback
    )
    {
        const TWeakPtr<Gs2::Core::Domain::FGs2> WeakGs2 = Gs2;
        const TWeakPtr<Stamina::Domain::FGs2StaminaDomain> WeakService = Service;
        const FString RegisteredParentKey = ParentKey;
        return Gs2->Cache->Subscribe(
            Gs2::Stamina::Model::FRecoverValueTable::TypeName,
            ParentKey,
            Gs2::Stamina::Domain::Model::FRecoverValueTableDomain::CreateCacheKey(
            ),
            [Callback](TSharedPtr<FGs2Object> obj)
            {
                Callback(StaticCastSharedPtr<Gs2::Stamina::Model::FRecoverValueTable>(obj));
            },
            [WeakGs2, WeakService, RegisteredParentKey]()
            {
                const auto Owner = WeakGs2.Pin();
                if (!Owner.IsValid())
                {
                    return;
                }
                const auto Domain = MakeShared<FRecoverValueTableDomain>(
                    Owner,
                    WeakService.Pin()
                );
                Domain->ParentKey = RegisteredParentKey;
                const auto Task = Domain->Model();
                Task->StartBackgroundTask();
            }
        );
    }

    void FRecoverValueTableDomain::Unsubscribe(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        Gs2->Cache->Unsubscribe(
            Gs2::Stamina::Model::FRecoverValueTable::TypeName,
            ParentKey,
            Gs2::Stamina::Domain::Model::FRecoverValueTableDomain::CreateCacheKey(
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
