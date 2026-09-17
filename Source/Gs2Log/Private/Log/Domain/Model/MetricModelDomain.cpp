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

#include "Log/Domain/Model/MetricModel.h"
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
#include "Log/Model/Cache/MetricModel.h"

#include "Core/Domain/Gs2.h"
#include "Core/Domain/Transaction/JobQueueJobDomainFactory.h"
#include "Core/Domain/Transaction/InternalTransactionDomainFactory.h"
#include "Core/Domain/Transaction/ManualTransactionDomain.h"

namespace Gs2::Log::Domain::Model
{

    FMetricModelDomain::FMetricModelDomain(
        const Core::Domain::FGs2Ptr& Gs2,
        const Log::Domain::FGs2LogDomainPtr& Service,
        const TOptional<FString> NamespaceName,
        const TOptional<FString> Name
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Gs2(Gs2),
        Service(Service),
        Client(MakeShared<Gs2::Log::FGs2LogRestClient>(Gs2->RestSession)),
        NamespaceName(NamespaceName),
        Name(Name),
        ParentKey(Gs2::Log::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
            NamespaceName,
            "MetricModel"
        ))
    {
    }

    FMetricModelDomain::FMetricModelDomain(
        const FMetricModelDomain& From
    ):
        Gs2(From.Gs2),
        Service(From.Service),
        Client(From.Client),
        NamespaceName(From.NamespaceName),
        Name(From.Name),
        ParentKey(From.ParentKey)
    {

    }

    FString FMetricModelDomain::CreateCacheParentKey(
        TOptional<FString> NamespaceName,
        TOptional<FString> Name,
        FString ChildType
    )
    {
        return FString("") +
            (NamespaceName.IsSet() ? *NamespaceName : "null") + ":" +
            (Name.IsSet() ? *Name : "null") + ":" +
            ChildType;
    }

    FString FMetricModelDomain::CreateCacheKey(
        TOptional<FString> Name
    )
    {
        return FString("") +
            (Name.IsSet() ? *Name : "null");
    }

    FMetricModelDomain::FModelTask::FModelTask(
        const TSharedPtr<FMetricModelDomain> Self
    ): Self(Self)
    {

    }

    FMetricModelDomain::FModelTask::FModelTask(
        const FModelTask& From
    ): TGs2Future(From), Self(From.Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FMetricModelDomain::FModelTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Log::Model::FMetricModel>> Result
    )
    {
        const auto CacheParentKey = Gs2::Log::Model::Cache::FMetricModelCache::CreateCacheParentKey(

            Self->NamespaceName,
            TOptional<int32>()
        );
        const auto CacheKey = Gs2::Log::Model::Cache::FMetricModelCache::CreateCacheKey(

            Self->Name
        );
        return Self->Gs2->Cache->ExecuteWithKeyLock(
            Gs2::Log::Model::FMetricModel::TypeName,
            CacheParentKey,
            CacheKey,
            [Self = Self, Result]() -> Gs2::Core::Model::FGs2ErrorPtr
            {
                Gs2::Log::Model::FMetricModelPtr Value;
                const auto CacheHit = Gs2::Log::Model::Cache::FMetricModelCache::TryGet(
                    Self->Gs2->Cache,

                    Self->NamespaceName,
                    Self->Name,
                    TOptional<int32>(),
                    &Value
                );
                if (CacheHit)
                {
                    *Result = Value;
                    return nullptr;
                }
                *Result = Value;
                return nullptr;
            }
        );
    }

    TSharedPtr<FAsyncTask<FMetricModelDomain::FModelTask>> FMetricModelDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FMetricModelDomain::FModelTask>>(this->AsShared());
    }

    void FMetricModelDomain::Invalidate()
    {
        Gs2::Log::Model::Cache::FMetricModelCache::Delete(
            Gs2->Cache,

            NamespaceName,
            Name,
            TOptional<int32>()
        );
    }

    FMetricModelDomain::FSubscribeWithInitialCallTask::FSubscribeWithInitialCallTask(
        const TSharedPtr<FMetricModelDomain>& Self,
        TFunction<void(Gs2::Log::Model::FMetricModelPtr)> Callback
    ):
        Self(Self),
        Callback(Callback)
    {
    }

    FMetricModelDomain::FSubscribeWithInitialCallTask::FSubscribeWithInitialCallTask(
        const FSubscribeWithInitialCallTask& From
    ):
        TGs2Future(From),
        Self(From.Self),
        Callback(From.Callback)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FMetricModelDomain::FSubscribeWithInitialCallTask::Action(
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

    TSharedPtr<FAsyncTask<FMetricModelDomain::FSubscribeWithInitialCallTask>> FMetricModelDomain::SubscribeWithInitialCall(
        TFunction<void(Gs2::Log::Model::FMetricModelPtr)> Callback
    )
    {
        return Gs2::Core::Util::New<FAsyncTask<FSubscribeWithInitialCallTask>>(this->AsShared(), Callback);
    }

    Gs2::Core::Domain::CallbackID FMetricModelDomain::Subscribe(
        TFunction<void(Gs2::Log::Model::FMetricModelPtr)> Callback
    )
    {
        const auto SubscriptionParentKey = Gs2::Log::Model::Cache::FMetricModelCache::CreateCacheParentKey(

            NamespaceName,
            TOptional<int32>()
        );
        const auto SubscriptionCacheKey = Gs2::Log::Model::Cache::FMetricModelCache::CreateCacheKey(

            Name
        );
        const TWeakPtr<Gs2::Core::Domain::FGs2> WeakGs2 = Gs2;
        const TWeakPtr<Log::Domain::FGs2LogDomain> WeakService = Service;
        const FString RegisteredParentKey = SubscriptionParentKey;
        const TOptional<FString> QueryNamespaceName = NamespaceName;
        const TOptional<FString> QueryName = Name;
        return Gs2->Cache->Subscribe(
            Gs2::Log::Model::FMetricModel::TypeName,
            SubscriptionParentKey,
            SubscriptionCacheKey,
            [Callback](TSharedPtr<FGs2Object> obj)
            {
                Callback(StaticCastSharedPtr<Gs2::Log::Model::FMetricModel>(obj));
            },
            [WeakGs2, WeakService, RegisteredParentKey, QueryNamespaceName, QueryName]()
            {
                const auto Owner = WeakGs2.Pin();
                if (!Owner.IsValid())
                {
                    return;
                }
                const auto Domain = MakeShared<FMetricModelDomain>(
                    Owner,
                    WeakService.Pin(),
                    QueryNamespaceName,
                    QueryName
                );
                Domain->ParentKey = RegisteredParentKey;
                const auto Task = Domain->Model();
                Task->StartBackgroundTask();
            }
        );
    }

    void FMetricModelDomain::Unsubscribe(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        const auto SubscriptionParentKey = Gs2::Log::Model::Cache::FMetricModelCache::CreateCacheParentKey(

            NamespaceName,
            TOptional<int32>()
        );
        const auto SubscriptionCacheKey = Gs2::Log::Model::Cache::FMetricModelCache::CreateCacheKey(

            Name
        );
        Gs2->Cache->Unsubscribe(
            Gs2::Log::Model::FMetricModel::TypeName,
            SubscriptionParentKey,
            SubscriptionCacheKey,
            CallbackID
        );
    }
}

#if defined(_MSC_VER)
#pragma warning (pop)
#elif defined(__clang__)
#pragma clang diagnostic pop
#endif
