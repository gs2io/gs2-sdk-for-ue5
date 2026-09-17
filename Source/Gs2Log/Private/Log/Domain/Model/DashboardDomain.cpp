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

#include "Log/Domain/Model/Dashboard.h"
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
#include "Log/Model/Cache/Dashboard.h"

#include "Core/Domain/Gs2.h"
#include "Core/Domain/Transaction/JobQueueJobDomainFactory.h"
#include "Core/Domain/Transaction/InternalTransactionDomainFactory.h"
#include "Core/Domain/Transaction/ManualTransactionDomain.h"

namespace Gs2::Log::Domain::Model
{

    FDashboardDomain::FDashboardDomain(
        const Core::Domain::FGs2Ptr& Gs2,
        const Log::Domain::FGs2LogDomainPtr& Service,
        const TOptional<FString> NamespaceName,
        const TOptional<FString> DashboardName
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Gs2(Gs2),
        Service(Service),
        Client(MakeShared<Gs2::Log::FGs2LogRestClient>(Gs2->RestSession)),
        NamespaceName(NamespaceName),
        DashboardName(DashboardName),
        ParentKey(Gs2::Log::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
            NamespaceName,
            "Dashboard"
        ))
    {
    }

    FDashboardDomain::FDashboardDomain(
        const FDashboardDomain& From
    ):
        Gs2(From.Gs2),
        Service(From.Service),
        Client(From.Client),
        NamespaceName(From.NamespaceName),
        DashboardName(From.DashboardName),
        ParentKey(From.ParentKey)
    {

    }

    FDashboardDomain::FGetTask::FGetTask(
        const TSharedPtr<FDashboardDomain>& Self,
        const Request::FGetDashboardRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FDashboardDomain::FGetTask::FGetTask(
        const FGetTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FDashboardDomain::FGetTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Log::Model::FDashboard>> Result
    )
    {
        Request
            ->WithContextStack((!Request->GetContextStack().IsSet() || Request->GetContextStack()->IsEmpty()) ? Self->Gs2->DefaultContextStack : Request->GetContextStack())
            ->WithNamespaceName(Self->NamespaceName)
            ->WithDashboardName(Self->DashboardName);
        const auto Future = Self->Client->GetDashboard(
            Request
        );
        Future->StartSynchronousTask();
        if (Future->GetTask().IsError())
        {
            return Future->GetTask().Error();
        }
        const auto ResultModel = Future->GetTask().Result();
        Future->EnsureCompletion();

            if (ResultModel.IsValid() && ResultModel->GetItem() != nullptr)
            {


        Gs2::Log::Model::Cache::FDashboardCache::Put(
            Self->Gs2->Cache,

            Request->GetNamespaceName(),
            Request->GetDashboardName(),
            TOptional<int32>(),
            ResultModel->GetItem()
        );
            }
        *Result = ResultModel->GetItem();
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FDashboardDomain::FGetTask>> FDashboardDomain::Get(
        Request::FGetDashboardRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FGetTask>>(this->AsShared(), Request);
    }

    FDashboardDomain::FUpdateTask::FUpdateTask(
        const TSharedPtr<FDashboardDomain>& Self,
        const Request::FUpdateDashboardRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FDashboardDomain::FUpdateTask::FUpdateTask(
        const FUpdateTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FDashboardDomain::FUpdateTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Log::Domain::Model::FDashboardDomain>> Result
    )
    {
        Request
            ->WithContextStack((!Request->GetContextStack().IsSet() || Request->GetContextStack()->IsEmpty()) ? Self->Gs2->DefaultContextStack : Request->GetContextStack())
            ->WithNamespaceName(Self->NamespaceName)
            ->WithDashboardName(Self->DashboardName);
        const auto Future = Self->Client->UpdateDashboard(
            Request
        );
        Future->StartSynchronousTask();
        if (Future->GetTask().IsError())
        {
            return Future->GetTask().Error();
        }
        const auto ResultModel = Future->GetTask().Result();
        Future->EnsureCompletion();

            if (ResultModel.IsValid() && ResultModel->GetItem() != nullptr)
            {


        Gs2::Log::Model::Cache::FDashboardCache::Put(
            Self->Gs2->Cache,

            Request->GetNamespaceName(),
            Request->GetDashboardName(),
            TOptional<int32>(),
            ResultModel->GetItem()
        );
            }
        auto Domain = Self;

        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FDashboardDomain::FUpdateTask>> FDashboardDomain::Update(
        Request::FUpdateDashboardRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FUpdateTask>>(this->AsShared(), Request);
    }

    FDashboardDomain::FDuplicateTask::FDuplicateTask(
        const TSharedPtr<FDashboardDomain>& Self,
        const Request::FDuplicateDashboardRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FDashboardDomain::FDuplicateTask::FDuplicateTask(
        const FDuplicateTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FDashboardDomain::FDuplicateTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Log::Domain::Model::FDashboardDomain>> Result
    )
    {
        Request
            ->WithContextStack((!Request->GetContextStack().IsSet() || Request->GetContextStack()->IsEmpty()) ? Self->Gs2->DefaultContextStack : Request->GetContextStack())
            ->WithNamespaceName(Self->NamespaceName)
            ->WithDashboardName(Self->DashboardName);
        const auto Future = Self->Client->DuplicateDashboard(
            Request
        );
        Future->StartSynchronousTask();
        if (Future->GetTask().IsError())
        {
            return Future->GetTask().Error();
        }
        const auto ResultModel = Future->GetTask().Result();
        Future->EnsureCompletion();

            if (ResultModel.IsValid() && ResultModel->GetItem() != nullptr)
            {


        Gs2::Log::Model::Cache::FDashboardCache::Put(
            Self->Gs2->Cache,

            Request->GetNamespaceName(),
            Request->GetDashboardName(),
            TOptional<int32>(),
            ResultModel->GetItem()
        );
            }
        auto Domain = Self;

        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FDashboardDomain::FDuplicateTask>> FDashboardDomain::Duplicate(
        Request::FDuplicateDashboardRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FDuplicateTask>>(this->AsShared(), Request);
    }

    FDashboardDomain::FDeleteTask::FDeleteTask(
        const TSharedPtr<FDashboardDomain>& Self,
        const Request::FDeleteDashboardRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FDashboardDomain::FDeleteTask::FDeleteTask(
        const FDeleteTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FDashboardDomain::FDeleteTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Log::Domain::Model::FDashboardDomain>> Result
    )
    {
        Request
            ->WithContextStack((!Request->GetContextStack().IsSet() || Request->GetContextStack()->IsEmpty()) ? Self->Gs2->DefaultContextStack : Request->GetContextStack())
            ->WithNamespaceName(Self->NamespaceName)
            ->WithDashboardName(Self->DashboardName);
        const auto Future = Self->Client->DeleteDashboard(
            Request
        );
        Future->StartSynchronousTask();
        if (Future->GetTask().IsError())
        {
            const auto Error = Future->GetTask().Error();
            if (Error.IsValid() && Error->IsChildOf(Gs2::Core::Model::FNotFoundError::Class))
            {
                *Result = Self;
                return nullptr;
            }
            return Error;
        }
        const auto ResultModel = Future->GetTask().Result();
        Future->EnsureCompletion();


              Gs2::Log::Model::Cache::FDashboardCache::Delete(
            Self->Gs2->Cache,

            Request->GetNamespaceName(),
            Request->GetDashboardName(),
            TOptional<int32>()
        );
        auto Domain = Self;

        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FDashboardDomain::FDeleteTask>> FDashboardDomain::Delete(
        Request::FDeleteDashboardRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FDeleteTask>>(this->AsShared(), Request);
    }

    FString FDashboardDomain::CreateCacheParentKey(
        TOptional<FString> NamespaceName,
        TOptional<FString> DashboardName,
        FString ChildType
    )
    {
        return FString("") +
            (NamespaceName.IsSet() ? *NamespaceName : "null") + ":" +
            (DashboardName.IsSet() ? *DashboardName : "null") + ":" +
            ChildType;
    }

    FString FDashboardDomain::CreateCacheKey(
        TOptional<FString> DashboardName
    )
    {
        return FString("") +
            (DashboardName.IsSet() ? *DashboardName : "null");
    }

    FDashboardDomain::FModelTask::FModelTask(
        const TSharedPtr<FDashboardDomain> Self
    ): Self(Self)
    {

    }

    FDashboardDomain::FModelTask::FModelTask(
        const FModelTask& From
    ): TGs2Future(From), Self(From.Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FDashboardDomain::FModelTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Log::Model::FDashboard>> Result
    )
    {
        const auto CacheParentKey = Gs2::Log::Model::Cache::FDashboardCache::CreateCacheParentKey(

            Self->NamespaceName,
            TOptional<int32>()
        );
        const auto CacheKey = Gs2::Log::Model::Cache::FDashboardCache::CreateCacheKey(

            Self->DashboardName
        );
        return Self->Gs2->Cache->ExecuteWithKeyLock(
            Gs2::Log::Model::FDashboard::TypeName,
            CacheParentKey,
            CacheKey,
            [Self = Self, Result]() -> Gs2::Core::Model::FGs2ErrorPtr
            {
                Gs2::Log::Model::FDashboardPtr Value;
                const auto CacheHit = Gs2::Log::Model::Cache::FDashboardCache::TryGet(
                    Self->Gs2->Cache,

                    Self->NamespaceName,
                    Self->DashboardName,
                    TOptional<int32>(),
                    &Value
                );
                if (CacheHit)
                {
                    *Result = Value;
                    return nullptr;
                }
                const auto Error = Gs2::Log::Model::Cache::FDashboardCache::Fetch(
                    Self->Gs2->Cache,

                    Self->NamespaceName,
                    Self->DashboardName,
                    TOptional<int32>(),
                    [Self](Gs2::Log::Model::FDashboardPtr* OutItem) -> Gs2::Core::Model::FGs2ErrorPtr
                    {
                        const auto Future = Self->Get(
                            MakeShared<Gs2::Log::Request::FGetDashboardRequest>()
                        );
                        Future->StartSynchronousTask();
                        if (Future->GetTask().IsError()) return Future->GetTask().Error();
                        *OutItem = Future->GetTask().Result();
                        Future->EnsureCompletion();
                        return nullptr;
                    },
                    &Value
                );
                if (Error.IsValid()) return Error;
                *Result = Value;
                return nullptr;
            }
        );
    }

    TSharedPtr<FAsyncTask<FDashboardDomain::FModelTask>> FDashboardDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FDashboardDomain::FModelTask>>(this->AsShared());
    }

    void FDashboardDomain::Invalidate()
    {
        Gs2::Log::Model::Cache::FDashboardCache::Delete(
            Gs2->Cache,

            NamespaceName,
            DashboardName,
            TOptional<int32>()
        );
    }

    FDashboardDomain::FSubscribeWithInitialCallTask::FSubscribeWithInitialCallTask(
        const TSharedPtr<FDashboardDomain>& Self,
        TFunction<void(Gs2::Log::Model::FDashboardPtr)> Callback
    ):
        Self(Self),
        Callback(Callback)
    {
    }

    FDashboardDomain::FSubscribeWithInitialCallTask::FSubscribeWithInitialCallTask(
        const FSubscribeWithInitialCallTask& From
    ):
        TGs2Future(From),
        Self(From.Self),
        Callback(From.Callback)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FDashboardDomain::FSubscribeWithInitialCallTask::Action(
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

    TSharedPtr<FAsyncTask<FDashboardDomain::FSubscribeWithInitialCallTask>> FDashboardDomain::SubscribeWithInitialCall(
        TFunction<void(Gs2::Log::Model::FDashboardPtr)> Callback
    )
    {
        return Gs2::Core::Util::New<FAsyncTask<FSubscribeWithInitialCallTask>>(this->AsShared(), Callback);
    }

    Gs2::Core::Domain::CallbackID FDashboardDomain::Subscribe(
        TFunction<void(Gs2::Log::Model::FDashboardPtr)> Callback
    )
    {
        const auto SubscriptionParentKey = Gs2::Log::Model::Cache::FDashboardCache::CreateCacheParentKey(

            NamespaceName,
            TOptional<int32>()
        );
        const auto SubscriptionCacheKey = Gs2::Log::Model::Cache::FDashboardCache::CreateCacheKey(

            DashboardName
        );
        const TWeakPtr<Gs2::Core::Domain::FGs2> WeakGs2 = Gs2;
        const TWeakPtr<Log::Domain::FGs2LogDomain> WeakService = Service;
        const FString RegisteredParentKey = SubscriptionParentKey;
        const TOptional<FString> QueryNamespaceName = NamespaceName;
        const TOptional<FString> QueryDashboardName = DashboardName;
        return Gs2->Cache->Subscribe(
            Gs2::Log::Model::FDashboard::TypeName,
            SubscriptionParentKey,
            SubscriptionCacheKey,
            [Callback](TSharedPtr<FGs2Object> obj)
            {
                Callback(StaticCastSharedPtr<Gs2::Log::Model::FDashboard>(obj));
            },
            [WeakGs2, WeakService, RegisteredParentKey, QueryNamespaceName, QueryDashboardName]()
            {
                const auto Owner = WeakGs2.Pin();
                if (!Owner.IsValid())
                {
                    return;
                }
                const auto Domain = MakeShared<FDashboardDomain>(
                    Owner,
                    WeakService.Pin(),
                    QueryNamespaceName,
                    QueryDashboardName
                );
                Domain->ParentKey = RegisteredParentKey;
                const auto Task = Domain->Model();
                Task->StartBackgroundTask();
            }
        );
    }

    void FDashboardDomain::Unsubscribe(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        const auto SubscriptionParentKey = Gs2::Log::Model::Cache::FDashboardCache::CreateCacheParentKey(

            NamespaceName,
            TOptional<int32>()
        );
        const auto SubscriptionCacheKey = Gs2::Log::Model::Cache::FDashboardCache::CreateCacheKey(

            DashboardName
        );
        Gs2->Cache->Unsubscribe(
            Gs2::Log::Model::FDashboard::TypeName,
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
