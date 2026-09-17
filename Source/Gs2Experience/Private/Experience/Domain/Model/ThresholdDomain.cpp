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

#include "Experience/Domain/Model/Threshold.h"
#include "Experience/Domain/Model/Namespace.h"
#include "Experience/Domain/Model/ExperienceModelMaster.h"
#include "Experience/Domain/Model/ExperienceModel.h"
#include "Experience/Domain/Model/ThresholdMaster.h"
#include "Experience/Domain/Model/CurrentExperienceMaster.h"
#include "Experience/Domain/Model/User.h"
#include "Experience/Domain/Model/UserAccessToken.h"
#include "Experience/Domain/Model/Status.h"
#include "Experience/Domain/Model/StatusAccessToken.h"

#include "Core/Domain/Gs2.h"
#include "Core/Domain/Transaction/JobQueueJobDomainFactory.h"
#include "Core/Domain/Transaction/InternalTransactionDomainFactory.h"
#include "Core/Domain/Transaction/ManualTransactionDomain.h"

namespace Gs2::Experience::Domain::Model
{

    FThresholdDomain::FThresholdDomain(
        const Core::Domain::FGs2Ptr& Gs2,
        const Experience::Domain::FGs2ExperienceDomainPtr& Service
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Gs2(Gs2),
        Service(Service),
        Client(MakeShared<Gs2::Experience::FGs2ExperienceRestClient>(Gs2->RestSession)),
        ParentKey("experience:Threshold")
    {
    }

    FThresholdDomain::FThresholdDomain(
        const FThresholdDomain& From
    ):
        Gs2(From.Gs2),
        Service(From.Service),
        Client(From.Client),
        ParentKey(From.ParentKey)
    {

    }

    FString FThresholdDomain::CreateCacheParentKey(
        FString ChildType
    )
    {
        return FString("") +
            ChildType;
    }

    FString FThresholdDomain::CreateCacheKey(
    )
    {
        return "Singleton";
    }

    FThresholdDomain::FModelTask::FModelTask(
        const TSharedPtr<FThresholdDomain> Self
    ): Self(Self)
    {

    }

    FThresholdDomain::FModelTask::FModelTask(
        const FModelTask& From
    ): TGs2Future(From), Self(From.Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FThresholdDomain::FModelTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Experience::Model::FThreshold>> Result
    )
    {
        const FString CacheKey = Gs2::Experience::Domain::Model::FThresholdDomain::CreateCacheKey(
        );
        return Self->Gs2->Cache->ExecuteWithKeyLock(
            Gs2::Experience::Model::FThreshold::TypeName,
            Self->ParentKey,
            CacheKey,
            [this, Result, CacheKey]() -> Gs2::Core::Model::FGs2ErrorPtr
            {
                // ReSharper disable once CppLocalVariableMayBeConst
                TSharedPtr<Gs2::Experience::Model::FThreshold> Value;
                auto bCacheHit = Self->Gs2->Cache->TryGet<Gs2::Experience::Model::FThreshold>(
                    Self->ParentKey,
                    CacheKey,
                    &Value
                );
                *Result = Value;

                return nullptr;
            }
        );
    }

    TSharedPtr<FAsyncTask<FThresholdDomain::FModelTask>> FThresholdDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FThresholdDomain::FModelTask>>(this->AsShared());
    }

    void FThresholdDomain::Invalidate()
    {
        Gs2->Cache->Delete(
            Gs2::Experience::Model::FThreshold::TypeName,
            ParentKey,
            Gs2::Experience::Domain::Model::FThresholdDomain::CreateCacheKey(
            )
        );
    }

    FThresholdDomain::FSubscribeWithInitialCallTask::FSubscribeWithInitialCallTask(
        const TSharedPtr<FThresholdDomain>& Self,
        TFunction<void(Gs2::Experience::Model::FThresholdPtr)> Callback
    ):
        Self(Self),
        Callback(Callback)
    {
    }

    FThresholdDomain::FSubscribeWithInitialCallTask::FSubscribeWithInitialCallTask(
        const FSubscribeWithInitialCallTask& From
    ):
        TGs2Future(From),
        Self(From.Self),
        Callback(From.Callback)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FThresholdDomain::FSubscribeWithInitialCallTask::Action(
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

    TSharedPtr<FAsyncTask<FThresholdDomain::FSubscribeWithInitialCallTask>> FThresholdDomain::SubscribeWithInitialCall(
        TFunction<void(Gs2::Experience::Model::FThresholdPtr)> Callback
    )
    {
        return Gs2::Core::Util::New<FAsyncTask<FSubscribeWithInitialCallTask>>(this->AsShared(), Callback);
    }

    Gs2::Core::Domain::CallbackID FThresholdDomain::Subscribe(
        TFunction<void(Gs2::Experience::Model::FThresholdPtr)> Callback
    )
    {
        const TWeakPtr<Gs2::Core::Domain::FGs2> WeakGs2 = Gs2;
        const TWeakPtr<Experience::Domain::FGs2ExperienceDomain> WeakService = Service;
        const FString RegisteredParentKey = ParentKey;
        return Gs2->Cache->Subscribe(
            Gs2::Experience::Model::FThreshold::TypeName,
            ParentKey,
            Gs2::Experience::Domain::Model::FThresholdDomain::CreateCacheKey(
            ),
            [Callback](TSharedPtr<FGs2Object> obj)
            {
                Callback(StaticCastSharedPtr<Gs2::Experience::Model::FThreshold>(obj));
            },
            [WeakGs2, WeakService, RegisteredParentKey]()
            {
                const auto Owner = WeakGs2.Pin();
                if (!Owner.IsValid())
                {
                    return;
                }
                const auto Domain = MakeShared<FThresholdDomain>(
                    Owner,
                    WeakService.Pin()
                );
                Domain->ParentKey = RegisteredParentKey;
                const auto Task = Domain->Model();
                Task->StartBackgroundTask();
            }
        );
    }

    void FThresholdDomain::Unsubscribe(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        Gs2->Cache->Unsubscribe(
            Gs2::Experience::Model::FThreshold::TypeName,
            ParentKey,
            Gs2::Experience::Domain::Model::FThresholdDomain::CreateCacheKey(
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
