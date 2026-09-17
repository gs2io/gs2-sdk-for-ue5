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

#include "Log/Domain/Model/TimeseriesPoint.h"
#include "Log/Domain/Model/Namespace.h"
#include "Log/Domain/Model/AccessLog.h"
#include "Log/Domain/Model/IssueStampSheetLog.h"
#include "Log/Domain/Model/ExecuteStampSheetLog.h"
#include "Log/Domain/Model/ExecuteStampTaskLog.h"
#include "Log/Domain/Model/InGameLog.h"
#include "Log/Domain/Model/InGameLogAccessToken.h"
#include "Log/Domain/Model/AccessLogWithTelemetry.h"
#include "Log/Domain/Model/User.h"
#include "Log/Domain/Model/UserAccessToken.h"
#include "Log/Domain/Model/Insight.h"
#include "Log/Domain/Model/FacetModel.h"
#include "Log/Domain/Model/Dashboard.h"
#include "Log/Domain/Model/LogEntry.h"
#include "Log/Domain/Model/MetricModel.h"

#include "Core/Domain/Gs2.h"
#include "Core/Domain/Transaction/JobQueueJobDomainFactory.h"
#include "Core/Domain/Transaction/InternalTransactionDomainFactory.h"
#include "Core/Domain/Transaction/ManualTransactionDomain.h"

namespace Gs2::Log::Domain::Model
{

    FTimeseriesPointDomain::FTimeseriesPointDomain(
        const Core::Domain::FGs2Ptr& Gs2,
        const Log::Domain::FGs2LogDomainPtr& Service
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Gs2(Gs2),
        Service(Service),
        Client(MakeShared<Gs2::Log::FGs2LogRestClient>(Gs2->RestSession)),
        ParentKey("log:TimeseriesPoint")
    {
    }

    FTimeseriesPointDomain::FTimeseriesPointDomain(
        const FTimeseriesPointDomain& From
    ):
        Gs2(From.Gs2),
        Service(From.Service),
        Client(From.Client),
        ParentKey(From.ParentKey)
    {

    }

    FString FTimeseriesPointDomain::CreateCacheParentKey(
        FString ChildType
    )
    {
        return FString("") +
            ChildType;
    }

    FString FTimeseriesPointDomain::CreateCacheKey(
    )
    {
        return "Singleton";
    }

    FTimeseriesPointDomain::FModelTask::FModelTask(
        const TSharedPtr<FTimeseriesPointDomain> Self
    ): Self(Self)
    {

    }

    FTimeseriesPointDomain::FModelTask::FModelTask(
        const FModelTask& From
    ): TGs2Future(From), Self(From.Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FTimeseriesPointDomain::FModelTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Log::Model::FTimeseriesPoint>> Result
    )
    {
        const FString CacheKey = Gs2::Log::Domain::Model::FTimeseriesPointDomain::CreateCacheKey(
        );
        return Self->Gs2->Cache->ExecuteWithKeyLock(
            Gs2::Log::Model::FTimeseriesPoint::TypeName,
            Self->ParentKey,
            CacheKey,
            [this, Result, CacheKey]() -> Gs2::Core::Model::FGs2ErrorPtr
            {
                // ReSharper disable once CppLocalVariableMayBeConst
                TSharedPtr<Gs2::Log::Model::FTimeseriesPoint> Value;
                auto bCacheHit = Self->Gs2->Cache->TryGet<Gs2::Log::Model::FTimeseriesPoint>(
                    Self->ParentKey,
                    CacheKey,
                    &Value
                );
                *Result = Value;

                return nullptr;
            }
        );
    }

    TSharedPtr<FAsyncTask<FTimeseriesPointDomain::FModelTask>> FTimeseriesPointDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FTimeseriesPointDomain::FModelTask>>(this->AsShared());
    }

    void FTimeseriesPointDomain::Invalidate()
    {
        Gs2->Cache->Delete(
            Gs2::Log::Model::FTimeseriesPoint::TypeName,
            ParentKey,
            Gs2::Log::Domain::Model::FTimeseriesPointDomain::CreateCacheKey(
            )
        );
    }

    FTimeseriesPointDomain::FSubscribeWithInitialCallTask::FSubscribeWithInitialCallTask(
        const TSharedPtr<FTimeseriesPointDomain>& Self,
        TFunction<void(Gs2::Log::Model::FTimeseriesPointPtr)> Callback
    ):
        Self(Self),
        Callback(Callback)
    {
    }

    FTimeseriesPointDomain::FSubscribeWithInitialCallTask::FSubscribeWithInitialCallTask(
        const FSubscribeWithInitialCallTask& From
    ):
        TGs2Future(From),
        Self(From.Self),
        Callback(From.Callback)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FTimeseriesPointDomain::FSubscribeWithInitialCallTask::Action(
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

    TSharedPtr<FAsyncTask<FTimeseriesPointDomain::FSubscribeWithInitialCallTask>> FTimeseriesPointDomain::SubscribeWithInitialCall(
        TFunction<void(Gs2::Log::Model::FTimeseriesPointPtr)> Callback
    )
    {
        return Gs2::Core::Util::New<FAsyncTask<FSubscribeWithInitialCallTask>>(this->AsShared(), Callback);
    }

    Gs2::Core::Domain::CallbackID FTimeseriesPointDomain::Subscribe(
        TFunction<void(Gs2::Log::Model::FTimeseriesPointPtr)> Callback
    )
    {
        const TWeakPtr<Gs2::Core::Domain::FGs2> WeakGs2 = Gs2;
        const TWeakPtr<Log::Domain::FGs2LogDomain> WeakService = Service;
        const FString RegisteredParentKey = ParentKey;
        return Gs2->Cache->Subscribe(
            Gs2::Log::Model::FTimeseriesPoint::TypeName,
            ParentKey,
            Gs2::Log::Domain::Model::FTimeseriesPointDomain::CreateCacheKey(
            ),
            [Callback](TSharedPtr<FGs2Object> obj)
            {
                Callback(StaticCastSharedPtr<Gs2::Log::Model::FTimeseriesPoint>(obj));
            },
            [WeakGs2, WeakService, RegisteredParentKey]()
            {
                const auto Owner = WeakGs2.Pin();
                if (!Owner.IsValid())
                {
                    return;
                }
                const auto Domain = MakeShared<FTimeseriesPointDomain>(
                    Owner,
                    WeakService.Pin()
                );
                Domain->ParentKey = RegisteredParentKey;
                const auto Task = Domain->Model();
                Task->StartBackgroundTask();
            }
        );
    }

    void FTimeseriesPointDomain::Unsubscribe(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        Gs2->Cache->Unsubscribe(
            Gs2::Log::Model::FTimeseriesPoint::TypeName,
            ParentKey,
            Gs2::Log::Domain::Model::FTimeseriesPointDomain::CreateCacheKey(
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
