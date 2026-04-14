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
            ->WithContextStack(Self->Gs2->DefaultContextStack)
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
            ->WithContextStack(Self->Gs2->DefaultContextStack)
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
        if (ResultModel->GetItem() != nullptr)
        {
            const auto Key = Gs2::Log::Domain::Model::FDashboardDomain::CreateCacheKey(
                ResultModel->GetItem()->GetName()
            );
            Self->Gs2->Cache->Put(
                Gs2::Log::Model::FDashboard::TypeName,
                Self->ParentKey,
                Key,
                ResultModel->GetItem(),
                FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
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
            ->WithContextStack(Self->Gs2->DefaultContextStack)
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
        if (ResultModel->GetItem() != nullptr)
        {
            const auto Key = Gs2::Log::Domain::Model::FDashboardDomain::CreateCacheKey(
                ResultModel->GetItem()->GetName()
            );
            Self->Gs2->Cache->Put(
                Gs2::Log::Model::FDashboard::TypeName,
                Self->ParentKey,
                Key,
                ResultModel->GetItem(),
                FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
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
            ->WithContextStack(Self->Gs2->DefaultContextStack)
            ->WithNamespaceName(Self->NamespaceName)
            ->WithDashboardName(Self->DashboardName);
        const auto Future = Self->Client->DeleteDashboard(
            Request
        );
        Future->StartSynchronousTask();
        if (Future->GetTask().IsError())
        {
            return Future->GetTask().Error();
        }
        const auto ResultModel = Future->GetTask().Result();
        Future->EnsureCompletion();
        if (ResultModel->GetItem() != nullptr)
        {
            const auto Key = Gs2::Log::Domain::Model::FDashboardDomain::CreateCacheKey(
                ResultModel->GetItem()->GetName()
            );
            Self->Gs2->Cache->Delete(
                Gs2::Log::Model::FDashboard::TypeName,
                Self->ParentKey,
                Key
            );
        }
        Self->Gs2->Cache->ClearListCache(
            Gs2::Log::Model::FDashboard::TypeName,
            Self->ParentKey
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
        // ReSharper disable once CppLocalVariableMayBeConst
        TSharedPtr<Gs2::Log::Model::FDashboard> Value;
        auto bCacheHit = Self->Gs2->Cache->TryGet<Gs2::Log::Model::FDashboard>(
            Self->ParentKey,
            Gs2::Log::Domain::Model::FDashboardDomain::CreateCacheKey(
                Self->DashboardName
            ),
            &Value
        );
        if (!bCacheHit) {
            const auto Future = Self->Get(
                MakeShared<Gs2::Log::Request::FGetDashboardRequest>()
            );
            Future->StartSynchronousTask();
            if (Future->GetTask().IsError())
            {
                if (Future->GetTask().Error()->Type() != Gs2::Core::Model::FNotFoundError::TypeString)
                {
                    return Future->GetTask().Error();
                }

                const auto Key = Gs2::Log::Domain::Model::FDashboardDomain::CreateCacheKey(
                    Self->DashboardName
                );
                Self->Gs2->Cache->Put(
                    Gs2::Log::Model::FDashboard::TypeName,
                    Self->ParentKey,
                    Key,
                    nullptr,
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );

                if (Future->GetTask().Error()->Detail(0)->GetComponent() != "dashboard")
                {
                    return Future->GetTask().Error();
                }
            }
            else
            {
                Value = Future->GetTask().Result();
            }
            Future->EnsureCompletion();
        }
        *Result = Value;

        return nullptr;
    }

    TSharedPtr<FAsyncTask<FDashboardDomain::FModelTask>> FDashboardDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FDashboardDomain::FModelTask>>(this->AsShared());
    }

    Gs2::Core::Domain::CallbackID FDashboardDomain::Subscribe(
        TFunction<void(Gs2::Log::Model::FDashboardPtr)> Callback
    )
    {
        return Gs2->Cache->Subscribe(
            Gs2::Log::Model::FDashboard::TypeName,
            ParentKey,
            Gs2::Log::Domain::Model::FDashboardDomain::CreateCacheKey(
                DashboardName
            ),
            [Callback](TSharedPtr<FGs2Object> obj)
            {
                Callback(StaticCastSharedPtr<Gs2::Log::Model::FDashboard>(obj));
            }
        );
    }

    void FDashboardDomain::Unsubscribe(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        Gs2->Cache->Unsubscribe(
            Gs2::Log::Model::FDashboard::TypeName,
            ParentKey,
            Gs2::Log::Domain::Model::FDashboardDomain::CreateCacheKey(
                DashboardName
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

