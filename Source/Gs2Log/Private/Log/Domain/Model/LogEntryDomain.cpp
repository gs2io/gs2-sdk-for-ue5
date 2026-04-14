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
 *
 * deny overwrite
 */

#if defined(_MSC_VER)
#pragma warning (push)
#pragma warning (disable: 4458) // Declaration hides class member
#elif defined(__clang__)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wshadow" // declaration shadows a field of
#endif

#include "Log/Domain/Model/LogEntry.h"
#include "Log/Domain/Model/Facet.h"
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

    FLogEntryDomain::FLogEntryDomain(
        const Core::Domain::FGs2Ptr& Gs2,
        const Log::Domain::FGs2LogDomainPtr& Service
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Gs2(Gs2),
        Service(Service),
        Client(MakeShared<Gs2::Log::FGs2LogRestClient>(Gs2->RestSession)),
        ParentKey("log:LogEntry")
    {
    }

    FLogEntryDomain::FLogEntryDomain(
        const FLogEntryDomain& From
    ):
        Gs2(From.Gs2),
        Service(From.Service),
        Client(From.Client),
        ParentKey(From.ParentKey)
    {

    }

    FLogEntryDomain::FGetLogTask::FGetLogTask(
        const TSharedPtr<FLogEntryDomain>& Self,
        const Request::FGetLogRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FLogEntryDomain::FGetLogTask::FGetLogTask(
        const FGetLogTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FLogEntryDomain::FGetLogTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Log::Domain::Model::FLogEntryDomain>> Result
    )
    {
        const auto Future = Self->Client->GetLog(
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
            const auto Key = Gs2::Log::Domain::Model::FLogEntryDomain::CreateCacheKey(
            );
            Self->Gs2->Cache->Put(
                Gs2::Log::Model::FLogEntry::TypeName,
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

    TSharedPtr<FAsyncTask<FLogEntryDomain::FGetLogTask>> FLogEntryDomain::GetLog(
        Request::FGetLogRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FGetLogTask>>(this->AsShared(), Request);
    }

    FLogEntryDomain::FFacetsTask::FFacetsTask(
        const TSharedPtr<FLogEntryDomain>& Self,
        const Request::FQueryFacetsRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FLogEntryDomain::FFacetsTask::FFacetsTask(
        const FFacetsTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FLogEntryDomain::FFacetsTask::Action(
        TSharedPtr<TSharedPtr<TArray<TSharedPtr<Gs2::Log::Domain::Model::FFacetDomain>>>> Result
    )
    {
        const auto Future = Self->Client->QueryFacets(
            Request
        );
        Future->StartSynchronousTask();
        if (Future->GetTask().IsError())
        {
            return Future->GetTask().Error();
        }
        const auto ResultModel = Future->GetTask().Result();
        Future->EnsureCompletion();
        auto Domain = MakeShared<TArray<TSharedPtr<Gs2::Log::Domain::Model::FFacetDomain>>>();
        for (auto i=0; i<ResultModel->GetItems()->Num(); i++)
        {
            Domain->Add(
                MakeShared<Gs2::Log::Domain::Model::FFacetDomain>(
                    Self->Gs2,
                    Self->Service
                )
            );
            const auto ParentKey = "log:Facet";
            const auto Key = Gs2::Log::Domain::Model::FFacetDomain::CreateCacheKey(
            );
            Self->Gs2->Cache->Put(
                Gs2::Log::Model::FFacet::TypeName,
                ParentKey,
                Key,
                (*ResultModel->GetItems())[i],
                FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
            );
        }
        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FLogEntryDomain::FFacetsTask>> FLogEntryDomain::Facets(
        Request::FQueryFacetsRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FFacetsTask>>(this->AsShared(), Request);
    }

    FLogEntryDomain::FGetTraceTask::FGetTraceTask(
        const TSharedPtr<FLogEntryDomain>& Self,
        const Request::FGetTraceRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FLogEntryDomain::FGetTraceTask::FGetTraceTask(
        const FGetTraceTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FLogEntryDomain::FGetTraceTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Log::Domain::Model::FLogEntryDomain>> Result
    )
    {
        const auto Future = Self->Client->GetTrace(
            Request
        );
        Future->StartSynchronousTask();
        if (Future->GetTask().IsError())
        {
            return Future->GetTask().Error();
        }
        const auto ResultModel = Future->GetTask().Result();
        Future->EnsureCompletion();
        const auto Domain = Self;
        if (ResultModel != nullptr)
        {
            Self->Parallels = Domain->Parallels = ResultModel->GetParallels();
            if (ResultModel->GetParallelTruncated().IsSet())
            {
                Self->ParallelTruncated = Domain->ParallelTruncated = ResultModel->GetParallelTruncated();
            }
        }
        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FLogEntryDomain::FGetTraceTask>> FLogEntryDomain::GetTrace(
        Request::FGetTraceRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FGetTraceTask>>(this->AsShared(), Request);
    }

    FString FLogEntryDomain::CreateCacheParentKey(
        FString ChildType
    )
    {
        return FString("") +
            ChildType;
    }

    FString FLogEntryDomain::CreateCacheKey(
    )
    {
        return "Singleton";
    }

    FLogEntryDomain::FModelTask::FModelTask(
        const TSharedPtr<FLogEntryDomain> Self
    ): Self(Self)
    {

    }

    FLogEntryDomain::FModelTask::FModelTask(
        const FModelTask& From
    ): TGs2Future(From), Self(From.Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FLogEntryDomain::FModelTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Log::Model::FLogEntry>> Result
    )
    {
        const auto ParentKey = FString("log:LogEntry");
        // ReSharper disable once CppLocalVariableMayBeConst
        TSharedPtr<Gs2::Log::Model::FLogEntry> Value;
        auto bCacheHit = Self->Gs2->Cache->TryGet<Gs2::Log::Model::FLogEntry>(
            ParentKey,
            Gs2::Log::Domain::Model::FLogEntryDomain::CreateCacheKey(
            ),
            &Value
        );
        *Result = Value;

        return nullptr;
    }

    TSharedPtr<FAsyncTask<FLogEntryDomain::FModelTask>> FLogEntryDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FLogEntryDomain::FModelTask>>(this->AsShared());
    }

    Gs2::Core::Domain::CallbackID FLogEntryDomain::Subscribe(
        TFunction<void(Gs2::Log::Model::FLogEntryPtr)> Callback
    )
    {
        return Gs2->Cache->Subscribe(
            Gs2::Log::Model::FLogEntry::TypeName,
            ParentKey,
            Gs2::Log::Domain::Model::FLogEntryDomain::CreateCacheKey(
            ),
            [Callback](TSharedPtr<FGs2Object> obj)
            {
                Callback(StaticCastSharedPtr<Gs2::Log::Model::FLogEntry>(obj));
            }
        );
    }

    void FLogEntryDomain::Unsubscribe(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        Gs2->Cache->Unsubscribe(
            Gs2::Log::Model::FLogEntry::TypeName,
            ParentKey,
            Gs2::Log::Domain::Model::FLogEntryDomain::CreateCacheKey(
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

