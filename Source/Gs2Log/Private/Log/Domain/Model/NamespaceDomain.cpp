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

#include "Log/Domain/Model/Namespace.h"
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
#include "Log/Domain/Model/TimeseriesPoint.h"

#include "Log/Model/Cache/AccessLog.h"
#include "Log/Model/Cache/Dashboard.h"
#include "Log/Model/Cache/ExecuteStampSheetLog.h"
#include "Log/Model/Cache/ExecuteStampTaskLog.h"
#include "Log/Model/Cache/FacetModel.h"
#include "Log/Model/Cache/Insight.h"
#include "Log/Model/Cache/IssueStampSheetLog.h"
#include "Log/Model/Cache/MetricModel.h"
#include "Log/Model/Cache/InGameLog.h"
#include "Core/Domain/Gs2.h"
#include "Core/Domain/Transaction/JobQueueJobDomainFactory.h"
#include "Core/Domain/Transaction/InternalTransactionDomainFactory.h"
#include "Core/Domain/Transaction/ManualTransactionDomain.h"

namespace Gs2::Log::Domain::Model
{

    FNamespaceDomain::FNamespaceDomain(
        const Core::Domain::FGs2Ptr& Gs2,
        const Log::Domain::FGs2LogDomainPtr& Service,
        const TOptional<FString> NamespaceName
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Gs2(Gs2),
        Service(Service),
        Client(MakeShared<Gs2::Log::FGs2LogRestClient>(Gs2->RestSession)),
        NamespaceName(NamespaceName),
        ParentKey("log:Namespace")
    {
    }

    FNamespaceDomain::FNamespaceDomain(
        const FNamespaceDomain& From
    ):
        Gs2(From.Gs2),
        Service(From.Service),
        Client(From.Client),
        NamespaceName(From.NamespaceName),
        ParentKey(From.ParentKey)
    {

    }

    FNamespaceDomain::FGetStatusTask::FGetStatusTask(
        const TSharedPtr<FNamespaceDomain>& Self,
        const Request::FGetNamespaceStatusRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FNamespaceDomain::FGetStatusTask::FGetStatusTask(
        const FGetStatusTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FNamespaceDomain::FGetStatusTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Log::Domain::Model::FNamespaceDomain>> Result
    )
    {
        Request
            ->WithContextStack(Self->Gs2->DefaultContextStack)
            ->WithNamespaceName(Self->NamespaceName);
        const auto Future = Self->Client->GetNamespaceStatus(
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
            if (ResultModel->GetStatus().IsSet())
            {
                Self->Status = Domain->Status = ResultModel->GetStatus();
            }
        }
        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FNamespaceDomain::FGetStatusTask>> FNamespaceDomain::GetStatus(
        Request::FGetNamespaceStatusRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FGetStatusTask>>(this->AsShared(), Request);
    }

    FNamespaceDomain::FGetTask::FGetTask(
        const TSharedPtr<FNamespaceDomain>& Self,
        const Request::FGetNamespaceRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FNamespaceDomain::FGetTask::FGetTask(
        const FGetTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FNamespaceDomain::FGetTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Log::Model::FNamespace>> Result
    )
    {
        Request
            ->WithContextStack(Self->Gs2->DefaultContextStack)
            ->WithNamespaceName(Self->NamespaceName);
        const auto Future = Self->Client->GetNamespace(
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
            
            {
                const auto ParentKey = FString("log:Namespace");
                const auto Key = Gs2::Log::Domain::Model::FNamespaceDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetName()
                );
                Self->Gs2->Cache->Put(
                    Gs2::Log::Model::FNamespace::TypeName,
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

    TSharedPtr<FAsyncTask<FNamespaceDomain::FGetTask>> FNamespaceDomain::Get(
        Request::FGetNamespaceRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FGetTask>>(this->AsShared(), Request);
    }

    FNamespaceDomain::FUpdateTask::FUpdateTask(
        const TSharedPtr<FNamespaceDomain>& Self,
        const Request::FUpdateNamespaceRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FNamespaceDomain::FUpdateTask::FUpdateTask(
        const FUpdateTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FNamespaceDomain::FUpdateTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Log::Domain::Model::FNamespaceDomain>> Result
    )
    {
        Request
            ->WithContextStack(Self->Gs2->DefaultContextStack)
            ->WithNamespaceName(Self->NamespaceName);
        const auto Future = Self->Client->UpdateNamespace(
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
            
            {
                const auto ParentKey = FString("log:Namespace");
                const auto Key = Gs2::Log::Domain::Model::FNamespaceDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetName()
                );
                Self->Gs2->Cache->Put(
                    Gs2::Log::Model::FNamespace::TypeName,
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

    TSharedPtr<FAsyncTask<FNamespaceDomain::FUpdateTask>> FNamespaceDomain::Update(
        Request::FUpdateNamespaceRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FUpdateTask>>(this->AsShared(), Request);
    }

    FNamespaceDomain::FDeleteTask::FDeleteTask(
        const TSharedPtr<FNamespaceDomain>& Self,
        const Request::FDeleteNamespaceRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FNamespaceDomain::FDeleteTask::FDeleteTask(
        const FDeleteTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FNamespaceDomain::FDeleteTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Log::Domain::Model::FNamespaceDomain>> Result
    )
    {
        Request
            ->WithContextStack(Self->Gs2->DefaultContextStack)
            ->WithNamespaceName(Self->NamespaceName);
        const auto Future = Self->Client->DeleteNamespace(
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
            
            {
                const auto ParentKey = FString("log:Namespace");
                const auto Key = Gs2::Log::Domain::Model::FNamespaceDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetName()
                );
                Self->Gs2->Cache->Delete(Gs2::Log::Model::FNamespace::TypeName, ParentKey, Key);
            }
        }
        auto Domain = Self;

        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FNamespaceDomain::FDeleteTask>> FNamespaceDomain::Delete(
        Request::FDeleteNamespaceRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FDeleteTask>>(this->AsShared(), Request);
    }

    FNamespaceDomain::FCreateInsightTask::FCreateInsightTask(
        const TSharedPtr<FNamespaceDomain>& Self,
        const Request::FCreateInsightRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FNamespaceDomain::FCreateInsightTask::FCreateInsightTask(
        const FCreateInsightTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FNamespaceDomain::FCreateInsightTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Log::Domain::Model::FInsightDomain>> Result
    )
    {
        Request
            ->WithContextStack(Self->Gs2->DefaultContextStack)
            ->WithNamespaceName(Self->NamespaceName);
        const auto Future = Self->Client->CreateInsight(
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
                const auto ParentKey = Gs2::Log::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
                    Self->NamespaceName,
                    "Insight"
                );
                const auto Key = Gs2::Log::Domain::Model::FInsightDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetName()
                );
                Self->Gs2->Cache->Put(
                    Gs2::Log::Model::FInsight::TypeName,
                    ParentKey,
                    Key,
                    ResultModel->GetItem(),
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );
            }
        }
        auto Domain = MakeShared<Gs2::Log::Domain::Model::FInsightDomain>(
            Self->Gs2,
            Self->Service,
            Request->GetNamespaceName(),
            ResultModel->GetItem()->GetName()
        );

        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FNamespaceDomain::FCreateInsightTask>> FNamespaceDomain::CreateInsight(
        Request::FCreateInsightRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FCreateInsightTask>>(this->AsShared(), Request);
    }

    FNamespaceDomain::FCreateDashboardTask::FCreateDashboardTask(
        const TSharedPtr<FNamespaceDomain>& Self,
        const Request::FCreateDashboardRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FNamespaceDomain::FCreateDashboardTask::FCreateDashboardTask(
        const FCreateDashboardTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FNamespaceDomain::FCreateDashboardTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Log::Domain::Model::FDashboardDomain>> Result
    )
    {
        Request
            ->WithContextStack(Self->Gs2->DefaultContextStack)
            ->WithNamespaceName(Self->NamespaceName);
        const auto Future = Self->Client->CreateDashboard(
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
        auto Domain = MakeShared<Gs2::Log::Domain::Model::FDashboardDomain>(
            Self->Gs2,
            Self->Service,
            Request->GetNamespaceName(),
            ResultModel->GetItem()->GetName()
        );

        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FNamespaceDomain::FCreateDashboardTask>> FNamespaceDomain::CreateDashboard(
        Request::FCreateDashboardRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FCreateDashboardTask>>(this->AsShared(), Request);
    }

    FNamespaceDomain::FMetricsTimeseriesTask::FMetricsTimeseriesTask(
        const TSharedPtr<FNamespaceDomain>& Self,
        const Request::FQueryMetricsTimeseriesRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FNamespaceDomain::FMetricsTimeseriesTask::FMetricsTimeseriesTask(
        const FMetricsTimeseriesTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FNamespaceDomain::FMetricsTimeseriesTask::Action(
        TSharedPtr<TSharedPtr<TArray<TSharedPtr<Gs2::Log::Domain::Model::FTimeseriesPointDomain>>>> Result
    )
    {
        Request
            ->WithContextStack(Self->Gs2->DefaultContextStack)
            ->WithNamespaceName(Self->NamespaceName);
        const auto Future = Self->Client->QueryMetricsTimeseries(
            Request
        );
        Future->StartSynchronousTask();
        if (Future->GetTask().IsError())
        {
            return Future->GetTask().Error();
        }
        const auto ResultModel = Future->GetTask().Result();
        Future->EnsureCompletion();
        auto Domain = MakeShared<TArray<TSharedPtr<Gs2::Log::Domain::Model::FTimeseriesPointDomain>>>();
        for (auto i=0; i<ResultModel->GetItems()->Num(); i++)
        {
            Domain->Add(
                MakeShared<Gs2::Log::Domain::Model::FTimeseriesPointDomain>(
                    Self->Gs2,
                    Self->Service
                )
            );
            const auto ParentKey = "log:TimeseriesPoint";
            const auto Key = Gs2::Log::Domain::Model::FTimeseriesPointDomain::CreateCacheKey(
            );
            Self->Gs2->Cache->Put(
                Gs2::Log::Model::FTimeseriesPoint::TypeName,
                ParentKey,
                Key,
                (*ResultModel->GetItems())[i],
                FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
            );
        }
        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FNamespaceDomain::FMetricsTimeseriesTask>> FNamespaceDomain::MetricsTimeseries(
        Request::FQueryMetricsTimeseriesRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FMetricsTimeseriesTask>>(this->AsShared(), Request);
    }

    Gs2::Log::Domain::Iterator::FQueryAccessLogIteratorPtr FNamespaceDomain::AccessLog(
        const TOptional<FString> Service,
        const TOptional<FString> Method,
        const TOptional<FString> UserId,
        const TOptional<int64> Begin,
        const TOptional<int64> End,
        const TOptional<bool> LongTerm,
        const TOptional<FString> TimeOffsetToken
    ) const
    {
        return MakeShared<Gs2::Log::Domain::Iterator::FQueryAccessLogIterator>(
            Gs2,
            Client,
            NamespaceName,
            Service,
            Method,
            UserId,
            Begin,
            End,
            LongTerm,
            TimeOffsetToken
        );
    }

    Gs2::Core::Domain::CallbackID FNamespaceDomain::SubscribeAccessLog(
    TFunction<void()> Callback
    )
    {
        return Gs2->Cache->ListSubscribe(
            Gs2::Log::Model::FAccessLog::TypeName,
            Gs2::Log::Model::Cache::FAccessLogCache::CreateCacheParentKey(
                NamespaceName,
                TOptional<int32>()
            ),
            Callback,
            Callback
        );
    }
    void FNamespaceDomain::UnsubscribeAccessLog(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        Gs2->Cache->ListUnsubscribe(
            Gs2::Log::Model::FAccessLog::TypeName,
            Gs2::Log::Model::Cache::FAccessLogCache::CreateCacheParentKey(
                NamespaceName,
                TOptional<int32>()
            ),
            CallbackID
        );
    }
    class FNamespaceDomain::FCollectAccessLogTask : public Gs2::Core::Util::TGs2Future<TArray<Gs2::Log::Model::FAccessLogPtr>>, public TSharedFromThis<FCollectAccessLogTask>
    {
        const TSharedPtr<FNamespaceDomain> Self;
        const TFunction<void(TArray<Gs2::Log::Model::FAccessLogPtr>)> OnCollected;
    const TOptional<FString> QueryService;const TOptional<FString> QueryMethod;const TOptional<FString> QueryUserId;const TOptional<int64> QueryBegin;const TOptional<int64> QueryEnd;const TOptional<bool> QueryLongTerm;const TOptional<FString> QueryTimeOffsetToken;
    public:
        explicit FCollectAccessLogTask(const TSharedPtr<FNamespaceDomain>& Self, TFunction<void(TArray<Gs2::Log::Model::FAccessLogPtr>)> OnCollected,const TOptional<FString> Service,const TOptional<FString> Method,const TOptional<FString> UserId,const TOptional<int64> Begin,const TOptional<int64> End,const TOptional<bool> LongTerm,const TOptional<FString> TimeOffsetToken) : Self(Self), OnCollected(OnCollected), QueryService(Service), QueryMethod(Method), QueryUserId(UserId), QueryBegin(Begin), QueryEnd(End), QueryLongTerm(LongTerm), QueryTimeOffsetToken(TimeOffsetToken) {}
        FCollectAccessLogTask(const FCollectAccessLogTask& From) : TGs2Future(From), Self(From.Self), OnCollected(From.OnCollected), QueryService(From.QueryService), QueryMethod(From.QueryMethod), QueryUserId(From.QueryUserId), QueryBegin(From.QueryBegin), QueryEnd(From.QueryEnd), QueryLongTerm(From.QueryLongTerm), QueryTimeOffsetToken(From.QueryTimeOffsetToken) {}
        virtual Gs2::Core::Model::FGs2ErrorPtr Action(TSharedPtr<TSharedPtr<TArray<Gs2::Log::Model::FAccessLogPtr>>> Result) override
        {
            TArray<Gs2::Log::Model::FAccessLogPtr> Items;
            auto Iterator = Self->AccessLog(QueryService, QueryMethod, QueryUserId, QueryBegin, QueryEnd, QueryLongTerm, QueryTimeOffsetToken)->begin();
            while (Iterator.HasNext())
            {
                if (Iterator.IsError()) return Iterator.Error();
                if (Iterator.IsCurrentValid()) Items.Add(Iterator.Current());
                ++Iterator;
            }
            if (Iterator.IsError()) return Iterator.Error();
            *Result = MakeShared<TArray<Gs2::Log::Model::FAccessLogPtr>>(Items);
            if (OnCollected) OnCollected(Items);
            return nullptr;
        }
    };

    Gs2::Core::Domain::CallbackID FNamespaceDomain::SubscribeAccessLog(
        TFunction<void(TArray<Gs2::Log::Model::FAccessLogPtr>)> Callback,const TOptional<FString> Service,const TOptional<FString> Method,const TOptional<FString> UserId,const TOptional<int64> Begin,const TOptional<int64> End,const TOptional<bool> LongTerm,const TOptional<FString> TimeOffsetToken
    )
    {
        const TWeakPtr<Gs2::Core::Domain::FGs2> WeakGs2 = this->Gs2;
        const TWeakPtr<Log::Domain::FGs2LogDomain> WeakService = this->Service;
        const auto QueryNamespaceName = NamespaceName;
        const auto QueryService = Service;
        const auto QueryMethod = Method;
        const auto QueryUserId = UserId;
        const auto QueryBegin = Begin;
        const auto QueryEnd = End;
        const auto QueryLongTerm = LongTerm;
        const auto QueryTimeOffsetToken = TimeOffsetToken;
        const auto Parent = Gs2::Log::Model::Cache::FAccessLogCache::CreateCacheParentKey(
        NamespaceName,
        TOptional<int32>()
    );
        return Gs2->Cache->ListSubscribeTyped(
            Gs2::Log::Model::FAccessLog::TypeName,
            Parent,
            [Callback, WeakGs2](const TArray<FGs2ObjectPtr>& Values)
            {
                if (!WeakGs2.Pin().IsValid()) return;
                TArray<Gs2::Log::Model::FAccessLogPtr> TypedValues;
                for (const auto& Value : Values) if (Value.IsValid()) TypedValues.Add(StaticCastSharedPtr<Gs2::Log::Model::FAccessLog>(Value));
                Callback(TypedValues);
            },
            [WeakGs2, WeakService, Callback, QueryNamespaceName, QueryService, QueryMethod, QueryUserId, QueryBegin, QueryEnd, QueryLongTerm, QueryTimeOffsetToken]()
            {
                const auto Owner = WeakGs2.Pin();
                if (!Owner.IsValid()) return;
                const auto Domain = MakeShared<FNamespaceDomain>(Owner, WeakService.Pin(), QueryNamespaceName);
                const auto Task = Gs2::Core::Util::New<FAsyncTask<FCollectAccessLogTask>>(Domain, Callback, QueryService, QueryMethod, QueryUserId, QueryBegin, QueryEnd, QueryLongTerm, QueryTimeOffsetToken);
                Task->StartBackgroundTask();
            }
        );
    }

    void FNamespaceDomain::InvalidateAccessLog(const TOptional<FString> Service,const TOptional<FString> Method,const TOptional<FString> UserId,const TOptional<int64> Begin,const TOptional<int64> End,const TOptional<bool> LongTerm,const TOptional<FString> TimeOffsetToken)
    {
        Gs2->Cache->ClearListCache(
            Gs2::Log::Model::FAccessLog::TypeName,
            Gs2::Log::Model::Cache::FAccessLogCache::CreateCacheParentKey(
        NamespaceName,
        TOptional<int32>()
    )
        );
    }

    FNamespaceDomain::FSubscribeAccessLogWithInitialCallTask::FSubscribeAccessLogWithInitialCallTask(const TSharedPtr<FNamespaceDomain>& Self, TFunction<void(TArray<Gs2::Log::Model::FAccessLogPtr>)> Callback,const TOptional<FString> Service,const TOptional<FString> Method,const TOptional<FString> UserId,const TOptional<int64> Begin,const TOptional<int64> End,const TOptional<bool> LongTerm,const TOptional<FString> TimeOffsetToken) : Self(Self), Callback(Callback), QueryService(Service), QueryMethod(Method), QueryUserId(UserId), QueryBegin(Begin), QueryEnd(End), QueryLongTerm(LongTerm), QueryTimeOffsetToken(TimeOffsetToken) {}
    FNamespaceDomain::FSubscribeAccessLogWithInitialCallTask::FSubscribeAccessLogWithInitialCallTask(const FSubscribeAccessLogWithInitialCallTask& From) : TGs2Future(From), Self(From.Self), Callback(From.Callback), QueryService(From.QueryService), QueryMethod(From.QueryMethod), QueryUserId(From.QueryUserId), QueryBegin(From.QueryBegin), QueryEnd(From.QueryEnd), QueryLongTerm(From.QueryLongTerm), QueryTimeOffsetToken(From.QueryTimeOffsetToken) {}
    Gs2::Core::Model::FGs2ErrorPtr FNamespaceDomain::FSubscribeAccessLogWithInitialCallTask::Action(TSharedPtr<TSharedPtr<Gs2::Core::Domain::CallbackID>> Result)
    {
        const auto Task = Gs2::Core::Util::New<FAsyncTask<FCollectAccessLogTask>>(Self, TFunction<void(TArray<Gs2::Log::Model::FAccessLogPtr>)>(), QueryService, QueryMethod, QueryUserId, QueryBegin, QueryEnd, QueryLongTerm, QueryTimeOffsetToken);
        Task->StartSynchronousTask(); Task->EnsureCompletion();
        if (Task->GetTask().IsError()) return Task->GetTask().Error();
        const auto Values = Task->GetTask().Result();
        const auto CallbackId = Self->SubscribeAccessLog(Callback, QueryService, QueryMethod, QueryUserId, QueryBegin, QueryEnd, QueryLongTerm, QueryTimeOffsetToken);
        Callback(*Values); *Result = MakeShared<Gs2::Core::Domain::CallbackID>(CallbackId);
        return nullptr;
    }
    TSharedPtr<FAsyncTask<FNamespaceDomain::FSubscribeAccessLogWithInitialCallTask>> FNamespaceDomain::SubscribeAccessLogWithInitialCall(TFunction<void(TArray<Gs2::Log::Model::FAccessLogPtr>)> Callback,const TOptional<FString> Service,const TOptional<FString> Method,const TOptional<FString> UserId,const TOptional<int64> Begin,const TOptional<int64> End,const TOptional<bool> LongTerm,const TOptional<FString> TimeOffsetToken)
    {
        return Gs2::Core::Util::New<FAsyncTask<FSubscribeAccessLogWithInitialCallTask>>(this->AsShared(), Callback, Service, Method, UserId, Begin, End, LongTerm, TimeOffsetToken);
    }

    Gs2::Log::Domain::Iterator::FCountAccessLogIteratorPtr FNamespaceDomain::CountAccessLog(
        const TOptional<bool> Service,
        const TOptional<bool> Method,
        const TOptional<bool> UserId,
        const TOptional<int64> Begin,
        const TOptional<int64> End,
        const TOptional<bool> LongTerm,
        const TOptional<FString> TimeOffsetToken
    ) const
    {
        return MakeShared<Gs2::Log::Domain::Iterator::FCountAccessLogIterator>(
            Gs2,
            Client,
            NamespaceName,
            Service,
            Method,
            UserId,
            Begin,
            End,
            LongTerm,
            TimeOffsetToken
        );
    }

    Gs2::Core::Domain::CallbackID FNamespaceDomain::SubscribeCountAccessLog(
    TFunction<void()> Callback
    )
    {
        return Gs2->Cache->ListSubscribe(
            Gs2::Log::Model::FAccessLogCount::TypeName,
            Gs2::Log::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
                NamespaceName,
                "AccessLogCount"
            ),
            Callback,
            Callback
        );
    }
    void FNamespaceDomain::UnsubscribeCountAccessLog(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        Gs2->Cache->ListUnsubscribe(
            Gs2::Log::Model::FAccessLogCount::TypeName,
            Gs2::Log::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
                NamespaceName,
                "AccessLogCount"
            ),
            CallbackID
        );
    }
    class FNamespaceDomain::FCollectCountAccessLogTask : public Gs2::Core::Util::TGs2Future<TArray<Gs2::Log::Model::FAccessLogCountPtr>>, public TSharedFromThis<FCollectCountAccessLogTask>
    {
        const TSharedPtr<FNamespaceDomain> Self;
        const TFunction<void(TArray<Gs2::Log::Model::FAccessLogCountPtr>)> OnCollected;
    const TOptional<bool> QueryService;const TOptional<bool> QueryMethod;const TOptional<bool> QueryUserId;const TOptional<int64> QueryBegin;const TOptional<int64> QueryEnd;const TOptional<bool> QueryLongTerm;const TOptional<FString> QueryTimeOffsetToken;
    public:
        explicit FCollectCountAccessLogTask(const TSharedPtr<FNamespaceDomain>& Self, TFunction<void(TArray<Gs2::Log::Model::FAccessLogCountPtr>)> OnCollected,const TOptional<bool> Service,const TOptional<bool> Method,const TOptional<bool> UserId,const TOptional<int64> Begin,const TOptional<int64> End,const TOptional<bool> LongTerm,const TOptional<FString> TimeOffsetToken) : Self(Self), OnCollected(OnCollected), QueryService(Service), QueryMethod(Method), QueryUserId(UserId), QueryBegin(Begin), QueryEnd(End), QueryLongTerm(LongTerm), QueryTimeOffsetToken(TimeOffsetToken) {}
        FCollectCountAccessLogTask(const FCollectCountAccessLogTask& From) : TGs2Future(From), Self(From.Self), OnCollected(From.OnCollected), QueryService(From.QueryService), QueryMethod(From.QueryMethod), QueryUserId(From.QueryUserId), QueryBegin(From.QueryBegin), QueryEnd(From.QueryEnd), QueryLongTerm(From.QueryLongTerm), QueryTimeOffsetToken(From.QueryTimeOffsetToken) {}
        virtual Gs2::Core::Model::FGs2ErrorPtr Action(TSharedPtr<TSharedPtr<TArray<Gs2::Log::Model::FAccessLogCountPtr>>> Result) override
        {
            TArray<Gs2::Log::Model::FAccessLogCountPtr> Items;
            auto Iterator = Self->CountAccessLog(QueryService, QueryMethod, QueryUserId, QueryBegin, QueryEnd, QueryLongTerm, QueryTimeOffsetToken)->begin();
            while (Iterator.HasNext())
            {
                if (Iterator.IsError()) return Iterator.Error();
                if (Iterator.IsCurrentValid()) Items.Add(Iterator.Current());
                ++Iterator;
            }
            if (Iterator.IsError()) return Iterator.Error();
            *Result = MakeShared<TArray<Gs2::Log::Model::FAccessLogCountPtr>>(Items);
            if (OnCollected) OnCollected(Items);
            return nullptr;
        }
    };

    Gs2::Core::Domain::CallbackID FNamespaceDomain::SubscribeCountAccessLog(
        TFunction<void(TArray<Gs2::Log::Model::FAccessLogCountPtr>)> Callback,const TOptional<bool> Service,const TOptional<bool> Method,const TOptional<bool> UserId,const TOptional<int64> Begin,const TOptional<int64> End,const TOptional<bool> LongTerm,const TOptional<FString> TimeOffsetToken
    )
    {
        const TWeakPtr<Gs2::Core::Domain::FGs2> WeakGs2 = this->Gs2;
        const TWeakPtr<Log::Domain::FGs2LogDomain> WeakService = this->Service;
        const auto QueryNamespaceName = NamespaceName;
        const auto QueryService = Service;
        const auto QueryMethod = Method;
        const auto QueryUserId = UserId;
        const auto QueryBegin = Begin;
        const auto QueryEnd = End;
        const auto QueryLongTerm = LongTerm;
        const auto QueryTimeOffsetToken = TimeOffsetToken;
        const auto Parent = Gs2::Log::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
        NamespaceName,
        "AccessLogCount"
    );
        return Gs2->Cache->ListSubscribeTyped(
            Gs2::Log::Model::FAccessLogCount::TypeName,
            Parent,
            [Callback, WeakGs2](const TArray<FGs2ObjectPtr>& Values)
            {
                if (!WeakGs2.Pin().IsValid()) return;
                TArray<Gs2::Log::Model::FAccessLogCountPtr> TypedValues;
                for (const auto& Value : Values) if (Value.IsValid()) TypedValues.Add(StaticCastSharedPtr<Gs2::Log::Model::FAccessLogCount>(Value));
                Callback(TypedValues);
            },
            [WeakGs2, WeakService, Callback, QueryNamespaceName, QueryService, QueryMethod, QueryUserId, QueryBegin, QueryEnd, QueryLongTerm, QueryTimeOffsetToken]()
            {
                const auto Owner = WeakGs2.Pin();
                if (!Owner.IsValid()) return;
                const auto Domain = MakeShared<FNamespaceDomain>(Owner, WeakService.Pin(), QueryNamespaceName);
                const auto Task = Gs2::Core::Util::New<FAsyncTask<FCollectCountAccessLogTask>>(Domain, Callback, QueryService, QueryMethod, QueryUserId, QueryBegin, QueryEnd, QueryLongTerm, QueryTimeOffsetToken);
                Task->StartBackgroundTask();
            }
        );
    }

    void FNamespaceDomain::InvalidateCountAccessLog(const TOptional<bool> Service,const TOptional<bool> Method,const TOptional<bool> UserId,const TOptional<int64> Begin,const TOptional<int64> End,const TOptional<bool> LongTerm,const TOptional<FString> TimeOffsetToken)
    {
        Gs2->Cache->ClearListCache(
            Gs2::Log::Model::FAccessLogCount::TypeName,
            Gs2::Log::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
        NamespaceName,
        "AccessLogCount"
    )
        );
    }

    FNamespaceDomain::FSubscribeCountAccessLogWithInitialCallTask::FSubscribeCountAccessLogWithInitialCallTask(const TSharedPtr<FNamespaceDomain>& Self, TFunction<void(TArray<Gs2::Log::Model::FAccessLogCountPtr>)> Callback,const TOptional<bool> Service,const TOptional<bool> Method,const TOptional<bool> UserId,const TOptional<int64> Begin,const TOptional<int64> End,const TOptional<bool> LongTerm,const TOptional<FString> TimeOffsetToken) : Self(Self), Callback(Callback), QueryService(Service), QueryMethod(Method), QueryUserId(UserId), QueryBegin(Begin), QueryEnd(End), QueryLongTerm(LongTerm), QueryTimeOffsetToken(TimeOffsetToken) {}
    FNamespaceDomain::FSubscribeCountAccessLogWithInitialCallTask::FSubscribeCountAccessLogWithInitialCallTask(const FSubscribeCountAccessLogWithInitialCallTask& From) : TGs2Future(From), Self(From.Self), Callback(From.Callback), QueryService(From.QueryService), QueryMethod(From.QueryMethod), QueryUserId(From.QueryUserId), QueryBegin(From.QueryBegin), QueryEnd(From.QueryEnd), QueryLongTerm(From.QueryLongTerm), QueryTimeOffsetToken(From.QueryTimeOffsetToken) {}
    Gs2::Core::Model::FGs2ErrorPtr FNamespaceDomain::FSubscribeCountAccessLogWithInitialCallTask::Action(TSharedPtr<TSharedPtr<Gs2::Core::Domain::CallbackID>> Result)
    {
        const auto Task = Gs2::Core::Util::New<FAsyncTask<FCollectCountAccessLogTask>>(Self, TFunction<void(TArray<Gs2::Log::Model::FAccessLogCountPtr>)>(), QueryService, QueryMethod, QueryUserId, QueryBegin, QueryEnd, QueryLongTerm, QueryTimeOffsetToken);
        Task->StartSynchronousTask(); Task->EnsureCompletion();
        if (Task->GetTask().IsError()) return Task->GetTask().Error();
        const auto Values = Task->GetTask().Result();
        const auto CallbackId = Self->SubscribeCountAccessLog(Callback, QueryService, QueryMethod, QueryUserId, QueryBegin, QueryEnd, QueryLongTerm, QueryTimeOffsetToken);
        Callback(*Values); *Result = MakeShared<Gs2::Core::Domain::CallbackID>(CallbackId);
        return nullptr;
    }
    TSharedPtr<FAsyncTask<FNamespaceDomain::FSubscribeCountAccessLogWithInitialCallTask>> FNamespaceDomain::SubscribeCountAccessLogWithInitialCall(TFunction<void(TArray<Gs2::Log::Model::FAccessLogCountPtr>)> Callback,const TOptional<bool> Service,const TOptional<bool> Method,const TOptional<bool> UserId,const TOptional<int64> Begin,const TOptional<int64> End,const TOptional<bool> LongTerm,const TOptional<FString> TimeOffsetToken)
    {
        return Gs2::Core::Util::New<FAsyncTask<FSubscribeCountAccessLogWithInitialCallTask>>(this->AsShared(), Callback, Service, Method, UserId, Begin, End, LongTerm, TimeOffsetToken);
    }

    Gs2::Log::Domain::Iterator::FQueryExecuteStampSheetLogIteratorPtr FNamespaceDomain::ExecuteStampSheetLog(
        const TOptional<FString> Service,
        const TOptional<FString> Method,
        const TOptional<FString> UserId,
        const TOptional<FString> Action,
        const TOptional<int64> Begin,
        const TOptional<int64> End,
        const TOptional<bool> LongTerm,
        const TOptional<FString> TimeOffsetToken
    ) const
    {
        return MakeShared<Gs2::Log::Domain::Iterator::FQueryExecuteStampSheetLogIterator>(
            Gs2,
            Client,
            NamespaceName,
            Service,
            Method,
            UserId,
            Action,
            Begin,
            End,
            LongTerm,
            TimeOffsetToken
        );
    }

    Gs2::Core::Domain::CallbackID FNamespaceDomain::SubscribeExecuteStampSheetLog(
    TFunction<void()> Callback
    )
    {
        return Gs2->Cache->ListSubscribe(
            Gs2::Log::Model::FExecuteStampSheetLog::TypeName,
            Gs2::Log::Model::Cache::FExecuteStampSheetLogCache::CreateCacheParentKey(
                NamespaceName,
                TOptional<int32>()
            ),
            Callback,
            Callback
        );
    }
    void FNamespaceDomain::UnsubscribeExecuteStampSheetLog(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        Gs2->Cache->ListUnsubscribe(
            Gs2::Log::Model::FExecuteStampSheetLog::TypeName,
            Gs2::Log::Model::Cache::FExecuteStampSheetLogCache::CreateCacheParentKey(
                NamespaceName,
                TOptional<int32>()
            ),
            CallbackID
        );
    }
    class FNamespaceDomain::FCollectExecuteStampSheetLogTask : public Gs2::Core::Util::TGs2Future<TArray<Gs2::Log::Model::FExecuteStampSheetLogPtr>>, public TSharedFromThis<FCollectExecuteStampSheetLogTask>
    {
        const TSharedPtr<FNamespaceDomain> Self;
        const TFunction<void(TArray<Gs2::Log::Model::FExecuteStampSheetLogPtr>)> OnCollected;
    const TOptional<FString> QueryService;const TOptional<FString> QueryMethod;const TOptional<FString> QueryUserId;const TOptional<FString> QueryAction;const TOptional<int64> QueryBegin;const TOptional<int64> QueryEnd;const TOptional<bool> QueryLongTerm;const TOptional<FString> QueryTimeOffsetToken;
    public:
        explicit FCollectExecuteStampSheetLogTask(const TSharedPtr<FNamespaceDomain>& Self, TFunction<void(TArray<Gs2::Log::Model::FExecuteStampSheetLogPtr>)> OnCollected,const TOptional<FString> Service,const TOptional<FString> Method,const TOptional<FString> UserId,const TOptional<FString> Action,const TOptional<int64> Begin,const TOptional<int64> End,const TOptional<bool> LongTerm,const TOptional<FString> TimeOffsetToken) : Self(Self), OnCollected(OnCollected), QueryService(Service), QueryMethod(Method), QueryUserId(UserId), QueryAction(Action), QueryBegin(Begin), QueryEnd(End), QueryLongTerm(LongTerm), QueryTimeOffsetToken(TimeOffsetToken) {}
        FCollectExecuteStampSheetLogTask(const FCollectExecuteStampSheetLogTask& From) : TGs2Future(From), Self(From.Self), OnCollected(From.OnCollected), QueryService(From.QueryService), QueryMethod(From.QueryMethod), QueryUserId(From.QueryUserId), QueryAction(From.QueryAction), QueryBegin(From.QueryBegin), QueryEnd(From.QueryEnd), QueryLongTerm(From.QueryLongTerm), QueryTimeOffsetToken(From.QueryTimeOffsetToken) {}
        virtual Gs2::Core::Model::FGs2ErrorPtr Action(TSharedPtr<TSharedPtr<TArray<Gs2::Log::Model::FExecuteStampSheetLogPtr>>> Result) override
        {
            TArray<Gs2::Log::Model::FExecuteStampSheetLogPtr> Items;
            auto Iterator = Self->ExecuteStampSheetLog(QueryService, QueryMethod, QueryUserId, QueryAction, QueryBegin, QueryEnd, QueryLongTerm, QueryTimeOffsetToken)->begin();
            while (Iterator.HasNext())
            {
                if (Iterator.IsError()) return Iterator.Error();
                if (Iterator.IsCurrentValid()) Items.Add(Iterator.Current());
                ++Iterator;
            }
            if (Iterator.IsError()) return Iterator.Error();
            *Result = MakeShared<TArray<Gs2::Log::Model::FExecuteStampSheetLogPtr>>(Items);
            if (OnCollected) OnCollected(Items);
            return nullptr;
        }
    };

    Gs2::Core::Domain::CallbackID FNamespaceDomain::SubscribeExecuteStampSheetLog(
        TFunction<void(TArray<Gs2::Log::Model::FExecuteStampSheetLogPtr>)> Callback,const TOptional<FString> Service,const TOptional<FString> Method,const TOptional<FString> UserId,const TOptional<FString> Action,const TOptional<int64> Begin,const TOptional<int64> End,const TOptional<bool> LongTerm,const TOptional<FString> TimeOffsetToken
    )
    {
        const TWeakPtr<Gs2::Core::Domain::FGs2> WeakGs2 = this->Gs2;
        const TWeakPtr<Log::Domain::FGs2LogDomain> WeakService = this->Service;
        const auto QueryNamespaceName = NamespaceName;
        const auto QueryService = Service;
        const auto QueryMethod = Method;
        const auto QueryUserId = UserId;
        const auto QueryAction = Action;
        const auto QueryBegin = Begin;
        const auto QueryEnd = End;
        const auto QueryLongTerm = LongTerm;
        const auto QueryTimeOffsetToken = TimeOffsetToken;
        const auto Parent = Gs2::Log::Model::Cache::FExecuteStampSheetLogCache::CreateCacheParentKey(
        NamespaceName,
        TOptional<int32>()
    );
        return Gs2->Cache->ListSubscribeTyped(
            Gs2::Log::Model::FExecuteStampSheetLog::TypeName,
            Parent,
            [Callback, WeakGs2](const TArray<FGs2ObjectPtr>& Values)
            {
                if (!WeakGs2.Pin().IsValid()) return;
                TArray<Gs2::Log::Model::FExecuteStampSheetLogPtr> TypedValues;
                for (const auto& Value : Values) if (Value.IsValid()) TypedValues.Add(StaticCastSharedPtr<Gs2::Log::Model::FExecuteStampSheetLog>(Value));
                Callback(TypedValues);
            },
            [WeakGs2, WeakService, Callback, QueryNamespaceName, QueryService, QueryMethod, QueryUserId, QueryAction, QueryBegin, QueryEnd, QueryLongTerm, QueryTimeOffsetToken]()
            {
                const auto Owner = WeakGs2.Pin();
                if (!Owner.IsValid()) return;
                const auto Domain = MakeShared<FNamespaceDomain>(Owner, WeakService.Pin(), QueryNamespaceName);
                const auto Task = Gs2::Core::Util::New<FAsyncTask<FCollectExecuteStampSheetLogTask>>(Domain, Callback, QueryService, QueryMethod, QueryUserId, QueryAction, QueryBegin, QueryEnd, QueryLongTerm, QueryTimeOffsetToken);
                Task->StartBackgroundTask();
            }
        );
    }

    void FNamespaceDomain::InvalidateExecuteStampSheetLog(const TOptional<FString> Service,const TOptional<FString> Method,const TOptional<FString> UserId,const TOptional<FString> Action,const TOptional<int64> Begin,const TOptional<int64> End,const TOptional<bool> LongTerm,const TOptional<FString> TimeOffsetToken)
    {
        Gs2->Cache->ClearListCache(
            Gs2::Log::Model::FExecuteStampSheetLog::TypeName,
            Gs2::Log::Model::Cache::FExecuteStampSheetLogCache::CreateCacheParentKey(
        NamespaceName,
        TOptional<int32>()
    )
        );
    }

    FNamespaceDomain::FSubscribeExecuteStampSheetLogWithInitialCallTask::FSubscribeExecuteStampSheetLogWithInitialCallTask(const TSharedPtr<FNamespaceDomain>& Self, TFunction<void(TArray<Gs2::Log::Model::FExecuteStampSheetLogPtr>)> Callback,const TOptional<FString> Service,const TOptional<FString> Method,const TOptional<FString> UserId,const TOptional<FString> Action,const TOptional<int64> Begin,const TOptional<int64> End,const TOptional<bool> LongTerm,const TOptional<FString> TimeOffsetToken) : Self(Self), Callback(Callback), QueryService(Service), QueryMethod(Method), QueryUserId(UserId), QueryAction(Action), QueryBegin(Begin), QueryEnd(End), QueryLongTerm(LongTerm), QueryTimeOffsetToken(TimeOffsetToken) {}
    FNamespaceDomain::FSubscribeExecuteStampSheetLogWithInitialCallTask::FSubscribeExecuteStampSheetLogWithInitialCallTask(const FSubscribeExecuteStampSheetLogWithInitialCallTask& From) : TGs2Future(From), Self(From.Self), Callback(From.Callback), QueryService(From.QueryService), QueryMethod(From.QueryMethod), QueryUserId(From.QueryUserId), QueryAction(From.QueryAction), QueryBegin(From.QueryBegin), QueryEnd(From.QueryEnd), QueryLongTerm(From.QueryLongTerm), QueryTimeOffsetToken(From.QueryTimeOffsetToken) {}
    Gs2::Core::Model::FGs2ErrorPtr FNamespaceDomain::FSubscribeExecuteStampSheetLogWithInitialCallTask::Action(TSharedPtr<TSharedPtr<Gs2::Core::Domain::CallbackID>> Result)
    {
        const auto Task = Gs2::Core::Util::New<FAsyncTask<FCollectExecuteStampSheetLogTask>>(Self, TFunction<void(TArray<Gs2::Log::Model::FExecuteStampSheetLogPtr>)>(), QueryService, QueryMethod, QueryUserId, QueryAction, QueryBegin, QueryEnd, QueryLongTerm, QueryTimeOffsetToken);
        Task->StartSynchronousTask(); Task->EnsureCompletion();
        if (Task->GetTask().IsError()) return Task->GetTask().Error();
        const auto Values = Task->GetTask().Result();
        const auto CallbackId = Self->SubscribeExecuteStampSheetLog(Callback, QueryService, QueryMethod, QueryUserId, QueryAction, QueryBegin, QueryEnd, QueryLongTerm, QueryTimeOffsetToken);
        Callback(*Values); *Result = MakeShared<Gs2::Core::Domain::CallbackID>(CallbackId);
        return nullptr;
    }
    TSharedPtr<FAsyncTask<FNamespaceDomain::FSubscribeExecuteStampSheetLogWithInitialCallTask>> FNamespaceDomain::SubscribeExecuteStampSheetLogWithInitialCall(TFunction<void(TArray<Gs2::Log::Model::FExecuteStampSheetLogPtr>)> Callback,const TOptional<FString> Service,const TOptional<FString> Method,const TOptional<FString> UserId,const TOptional<FString> Action,const TOptional<int64> Begin,const TOptional<int64> End,const TOptional<bool> LongTerm,const TOptional<FString> TimeOffsetToken)
    {
        return Gs2::Core::Util::New<FAsyncTask<FSubscribeExecuteStampSheetLogWithInitialCallTask>>(this->AsShared(), Callback, Service, Method, UserId, Action, Begin, End, LongTerm, TimeOffsetToken);
    }

    Gs2::Log::Domain::Iterator::FCountExecuteStampSheetLogIteratorPtr FNamespaceDomain::CountExecuteStampSheetLog(
        const TOptional<bool> Service,
        const TOptional<bool> Method,
        const TOptional<bool> UserId,
        const TOptional<bool> Action,
        const TOptional<int64> Begin,
        const TOptional<int64> End,
        const TOptional<bool> LongTerm,
        const TOptional<FString> TimeOffsetToken
    ) const
    {
        return MakeShared<Gs2::Log::Domain::Iterator::FCountExecuteStampSheetLogIterator>(
            Gs2,
            Client,
            NamespaceName,
            Service,
            Method,
            UserId,
            Action,
            Begin,
            End,
            LongTerm,
            TimeOffsetToken
        );
    }

    Gs2::Core::Domain::CallbackID FNamespaceDomain::SubscribeCountExecuteStampSheetLog(
    TFunction<void()> Callback
    )
    {
        return Gs2->Cache->ListSubscribe(
            Gs2::Log::Model::FExecuteStampSheetLogCount::TypeName,
            Gs2::Log::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
                NamespaceName,
                "ExecuteStampSheetLogCount"
            ),
            Callback,
            Callback
        );
    }
    void FNamespaceDomain::UnsubscribeCountExecuteStampSheetLog(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        Gs2->Cache->ListUnsubscribe(
            Gs2::Log::Model::FExecuteStampSheetLogCount::TypeName,
            Gs2::Log::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
                NamespaceName,
                "ExecuteStampSheetLogCount"
            ),
            CallbackID
        );
    }
    class FNamespaceDomain::FCollectCountExecuteStampSheetLogTask : public Gs2::Core::Util::TGs2Future<TArray<Gs2::Log::Model::FExecuteStampSheetLogCountPtr>>, public TSharedFromThis<FCollectCountExecuteStampSheetLogTask>
    {
        const TSharedPtr<FNamespaceDomain> Self;
        const TFunction<void(TArray<Gs2::Log::Model::FExecuteStampSheetLogCountPtr>)> OnCollected;
    const TOptional<bool> QueryService;const TOptional<bool> QueryMethod;const TOptional<bool> QueryUserId;const TOptional<bool> QueryAction;const TOptional<int64> QueryBegin;const TOptional<int64> QueryEnd;const TOptional<bool> QueryLongTerm;const TOptional<FString> QueryTimeOffsetToken;
    public:
        explicit FCollectCountExecuteStampSheetLogTask(const TSharedPtr<FNamespaceDomain>& Self, TFunction<void(TArray<Gs2::Log::Model::FExecuteStampSheetLogCountPtr>)> OnCollected,const TOptional<bool> Service,const TOptional<bool> Method,const TOptional<bool> UserId,const TOptional<bool> Action,const TOptional<int64> Begin,const TOptional<int64> End,const TOptional<bool> LongTerm,const TOptional<FString> TimeOffsetToken) : Self(Self), OnCollected(OnCollected), QueryService(Service), QueryMethod(Method), QueryUserId(UserId), QueryAction(Action), QueryBegin(Begin), QueryEnd(End), QueryLongTerm(LongTerm), QueryTimeOffsetToken(TimeOffsetToken) {}
        FCollectCountExecuteStampSheetLogTask(const FCollectCountExecuteStampSheetLogTask& From) : TGs2Future(From), Self(From.Self), OnCollected(From.OnCollected), QueryService(From.QueryService), QueryMethod(From.QueryMethod), QueryUserId(From.QueryUserId), QueryAction(From.QueryAction), QueryBegin(From.QueryBegin), QueryEnd(From.QueryEnd), QueryLongTerm(From.QueryLongTerm), QueryTimeOffsetToken(From.QueryTimeOffsetToken) {}
        virtual Gs2::Core::Model::FGs2ErrorPtr Action(TSharedPtr<TSharedPtr<TArray<Gs2::Log::Model::FExecuteStampSheetLogCountPtr>>> Result) override
        {
            TArray<Gs2::Log::Model::FExecuteStampSheetLogCountPtr> Items;
            auto Iterator = Self->CountExecuteStampSheetLog(QueryService, QueryMethod, QueryUserId, QueryAction, QueryBegin, QueryEnd, QueryLongTerm, QueryTimeOffsetToken)->begin();
            while (Iterator.HasNext())
            {
                if (Iterator.IsError()) return Iterator.Error();
                if (Iterator.IsCurrentValid()) Items.Add(Iterator.Current());
                ++Iterator;
            }
            if (Iterator.IsError()) return Iterator.Error();
            *Result = MakeShared<TArray<Gs2::Log::Model::FExecuteStampSheetLogCountPtr>>(Items);
            if (OnCollected) OnCollected(Items);
            return nullptr;
        }
    };

    Gs2::Core::Domain::CallbackID FNamespaceDomain::SubscribeCountExecuteStampSheetLog(
        TFunction<void(TArray<Gs2::Log::Model::FExecuteStampSheetLogCountPtr>)> Callback,const TOptional<bool> Service,const TOptional<bool> Method,const TOptional<bool> UserId,const TOptional<bool> Action,const TOptional<int64> Begin,const TOptional<int64> End,const TOptional<bool> LongTerm,const TOptional<FString> TimeOffsetToken
    )
    {
        const TWeakPtr<Gs2::Core::Domain::FGs2> WeakGs2 = this->Gs2;
        const TWeakPtr<Log::Domain::FGs2LogDomain> WeakService = this->Service;
        const auto QueryNamespaceName = NamespaceName;
        const auto QueryService = Service;
        const auto QueryMethod = Method;
        const auto QueryUserId = UserId;
        const auto QueryAction = Action;
        const auto QueryBegin = Begin;
        const auto QueryEnd = End;
        const auto QueryLongTerm = LongTerm;
        const auto QueryTimeOffsetToken = TimeOffsetToken;
        const auto Parent = Gs2::Log::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
        NamespaceName,
        "ExecuteStampSheetLogCount"
    );
        return Gs2->Cache->ListSubscribeTyped(
            Gs2::Log::Model::FExecuteStampSheetLogCount::TypeName,
            Parent,
            [Callback, WeakGs2](const TArray<FGs2ObjectPtr>& Values)
            {
                if (!WeakGs2.Pin().IsValid()) return;
                TArray<Gs2::Log::Model::FExecuteStampSheetLogCountPtr> TypedValues;
                for (const auto& Value : Values) if (Value.IsValid()) TypedValues.Add(StaticCastSharedPtr<Gs2::Log::Model::FExecuteStampSheetLogCount>(Value));
                Callback(TypedValues);
            },
            [WeakGs2, WeakService, Callback, QueryNamespaceName, QueryService, QueryMethod, QueryUserId, QueryAction, QueryBegin, QueryEnd, QueryLongTerm, QueryTimeOffsetToken]()
            {
                const auto Owner = WeakGs2.Pin();
                if (!Owner.IsValid()) return;
                const auto Domain = MakeShared<FNamespaceDomain>(Owner, WeakService.Pin(), QueryNamespaceName);
                const auto Task = Gs2::Core::Util::New<FAsyncTask<FCollectCountExecuteStampSheetLogTask>>(Domain, Callback, QueryService, QueryMethod, QueryUserId, QueryAction, QueryBegin, QueryEnd, QueryLongTerm, QueryTimeOffsetToken);
                Task->StartBackgroundTask();
            }
        );
    }

    void FNamespaceDomain::InvalidateCountExecuteStampSheetLog(const TOptional<bool> Service,const TOptional<bool> Method,const TOptional<bool> UserId,const TOptional<bool> Action,const TOptional<int64> Begin,const TOptional<int64> End,const TOptional<bool> LongTerm,const TOptional<FString> TimeOffsetToken)
    {
        Gs2->Cache->ClearListCache(
            Gs2::Log::Model::FExecuteStampSheetLogCount::TypeName,
            Gs2::Log::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
        NamespaceName,
        "ExecuteStampSheetLogCount"
    )
        );
    }

    FNamespaceDomain::FSubscribeCountExecuteStampSheetLogWithInitialCallTask::FSubscribeCountExecuteStampSheetLogWithInitialCallTask(const TSharedPtr<FNamespaceDomain>& Self, TFunction<void(TArray<Gs2::Log::Model::FExecuteStampSheetLogCountPtr>)> Callback,const TOptional<bool> Service,const TOptional<bool> Method,const TOptional<bool> UserId,const TOptional<bool> Action,const TOptional<int64> Begin,const TOptional<int64> End,const TOptional<bool> LongTerm,const TOptional<FString> TimeOffsetToken) : Self(Self), Callback(Callback), QueryService(Service), QueryMethod(Method), QueryUserId(UserId), QueryAction(Action), QueryBegin(Begin), QueryEnd(End), QueryLongTerm(LongTerm), QueryTimeOffsetToken(TimeOffsetToken) {}
    FNamespaceDomain::FSubscribeCountExecuteStampSheetLogWithInitialCallTask::FSubscribeCountExecuteStampSheetLogWithInitialCallTask(const FSubscribeCountExecuteStampSheetLogWithInitialCallTask& From) : TGs2Future(From), Self(From.Self), Callback(From.Callback), QueryService(From.QueryService), QueryMethod(From.QueryMethod), QueryUserId(From.QueryUserId), QueryAction(From.QueryAction), QueryBegin(From.QueryBegin), QueryEnd(From.QueryEnd), QueryLongTerm(From.QueryLongTerm), QueryTimeOffsetToken(From.QueryTimeOffsetToken) {}
    Gs2::Core::Model::FGs2ErrorPtr FNamespaceDomain::FSubscribeCountExecuteStampSheetLogWithInitialCallTask::Action(TSharedPtr<TSharedPtr<Gs2::Core::Domain::CallbackID>> Result)
    {
        const auto Task = Gs2::Core::Util::New<FAsyncTask<FCollectCountExecuteStampSheetLogTask>>(Self, TFunction<void(TArray<Gs2::Log::Model::FExecuteStampSheetLogCountPtr>)>(), QueryService, QueryMethod, QueryUserId, QueryAction, QueryBegin, QueryEnd, QueryLongTerm, QueryTimeOffsetToken);
        Task->StartSynchronousTask(); Task->EnsureCompletion();
        if (Task->GetTask().IsError()) return Task->GetTask().Error();
        const auto Values = Task->GetTask().Result();
        const auto CallbackId = Self->SubscribeCountExecuteStampSheetLog(Callback, QueryService, QueryMethod, QueryUserId, QueryAction, QueryBegin, QueryEnd, QueryLongTerm, QueryTimeOffsetToken);
        Callback(*Values); *Result = MakeShared<Gs2::Core::Domain::CallbackID>(CallbackId);
        return nullptr;
    }
    TSharedPtr<FAsyncTask<FNamespaceDomain::FSubscribeCountExecuteStampSheetLogWithInitialCallTask>> FNamespaceDomain::SubscribeCountExecuteStampSheetLogWithInitialCall(TFunction<void(TArray<Gs2::Log::Model::FExecuteStampSheetLogCountPtr>)> Callback,const TOptional<bool> Service,const TOptional<bool> Method,const TOptional<bool> UserId,const TOptional<bool> Action,const TOptional<int64> Begin,const TOptional<int64> End,const TOptional<bool> LongTerm,const TOptional<FString> TimeOffsetToken)
    {
        return Gs2::Core::Util::New<FAsyncTask<FSubscribeCountExecuteStampSheetLogWithInitialCallTask>>(this->AsShared(), Callback, Service, Method, UserId, Action, Begin, End, LongTerm, TimeOffsetToken);
    }

    Gs2::Log::Domain::Iterator::FQueryExecuteStampTaskLogIteratorPtr FNamespaceDomain::ExecuteStampTaskLog(
        const TOptional<FString> Service,
        const TOptional<FString> Method,
        const TOptional<FString> UserId,
        const TOptional<FString> Action,
        const TOptional<int64> Begin,
        const TOptional<int64> End,
        const TOptional<bool> LongTerm,
        const TOptional<FString> TimeOffsetToken
    ) const
    {
        return MakeShared<Gs2::Log::Domain::Iterator::FQueryExecuteStampTaskLogIterator>(
            Gs2,
            Client,
            NamespaceName,
            Service,
            Method,
            UserId,
            Action,
            Begin,
            End,
            LongTerm,
            TimeOffsetToken
        );
    }

    Gs2::Core::Domain::CallbackID FNamespaceDomain::SubscribeExecuteStampTaskLog(
    TFunction<void()> Callback
    )
    {
        return Gs2->Cache->ListSubscribe(
            Gs2::Log::Model::FExecuteStampTaskLog::TypeName,
            Gs2::Log::Model::Cache::FExecuteStampTaskLogCache::CreateCacheParentKey(
                NamespaceName,
                TOptional<int32>()
            ),
            Callback,
            Callback
        );
    }
    void FNamespaceDomain::UnsubscribeExecuteStampTaskLog(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        Gs2->Cache->ListUnsubscribe(
            Gs2::Log::Model::FExecuteStampTaskLog::TypeName,
            Gs2::Log::Model::Cache::FExecuteStampTaskLogCache::CreateCacheParentKey(
                NamespaceName,
                TOptional<int32>()
            ),
            CallbackID
        );
    }
    class FNamespaceDomain::FCollectExecuteStampTaskLogTask : public Gs2::Core::Util::TGs2Future<TArray<Gs2::Log::Model::FExecuteStampTaskLogPtr>>, public TSharedFromThis<FCollectExecuteStampTaskLogTask>
    {
        const TSharedPtr<FNamespaceDomain> Self;
        const TFunction<void(TArray<Gs2::Log::Model::FExecuteStampTaskLogPtr>)> OnCollected;
    const TOptional<FString> QueryService;const TOptional<FString> QueryMethod;const TOptional<FString> QueryUserId;const TOptional<FString> QueryAction;const TOptional<int64> QueryBegin;const TOptional<int64> QueryEnd;const TOptional<bool> QueryLongTerm;const TOptional<FString> QueryTimeOffsetToken;
    public:
        explicit FCollectExecuteStampTaskLogTask(const TSharedPtr<FNamespaceDomain>& Self, TFunction<void(TArray<Gs2::Log::Model::FExecuteStampTaskLogPtr>)> OnCollected,const TOptional<FString> Service,const TOptional<FString> Method,const TOptional<FString> UserId,const TOptional<FString> Action,const TOptional<int64> Begin,const TOptional<int64> End,const TOptional<bool> LongTerm,const TOptional<FString> TimeOffsetToken) : Self(Self), OnCollected(OnCollected), QueryService(Service), QueryMethod(Method), QueryUserId(UserId), QueryAction(Action), QueryBegin(Begin), QueryEnd(End), QueryLongTerm(LongTerm), QueryTimeOffsetToken(TimeOffsetToken) {}
        FCollectExecuteStampTaskLogTask(const FCollectExecuteStampTaskLogTask& From) : TGs2Future(From), Self(From.Self), OnCollected(From.OnCollected), QueryService(From.QueryService), QueryMethod(From.QueryMethod), QueryUserId(From.QueryUserId), QueryAction(From.QueryAction), QueryBegin(From.QueryBegin), QueryEnd(From.QueryEnd), QueryLongTerm(From.QueryLongTerm), QueryTimeOffsetToken(From.QueryTimeOffsetToken) {}
        virtual Gs2::Core::Model::FGs2ErrorPtr Action(TSharedPtr<TSharedPtr<TArray<Gs2::Log::Model::FExecuteStampTaskLogPtr>>> Result) override
        {
            TArray<Gs2::Log::Model::FExecuteStampTaskLogPtr> Items;
            auto Iterator = Self->ExecuteStampTaskLog(QueryService, QueryMethod, QueryUserId, QueryAction, QueryBegin, QueryEnd, QueryLongTerm, QueryTimeOffsetToken)->begin();
            while (Iterator.HasNext())
            {
                if (Iterator.IsError()) return Iterator.Error();
                if (Iterator.IsCurrentValid()) Items.Add(Iterator.Current());
                ++Iterator;
            }
            if (Iterator.IsError()) return Iterator.Error();
            *Result = MakeShared<TArray<Gs2::Log::Model::FExecuteStampTaskLogPtr>>(Items);
            if (OnCollected) OnCollected(Items);
            return nullptr;
        }
    };

    Gs2::Core::Domain::CallbackID FNamespaceDomain::SubscribeExecuteStampTaskLog(
        TFunction<void(TArray<Gs2::Log::Model::FExecuteStampTaskLogPtr>)> Callback,const TOptional<FString> Service,const TOptional<FString> Method,const TOptional<FString> UserId,const TOptional<FString> Action,const TOptional<int64> Begin,const TOptional<int64> End,const TOptional<bool> LongTerm,const TOptional<FString> TimeOffsetToken
    )
    {
        const TWeakPtr<Gs2::Core::Domain::FGs2> WeakGs2 = this->Gs2;
        const TWeakPtr<Log::Domain::FGs2LogDomain> WeakService = this->Service;
        const auto QueryNamespaceName = NamespaceName;
        const auto QueryService = Service;
        const auto QueryMethod = Method;
        const auto QueryUserId = UserId;
        const auto QueryAction = Action;
        const auto QueryBegin = Begin;
        const auto QueryEnd = End;
        const auto QueryLongTerm = LongTerm;
        const auto QueryTimeOffsetToken = TimeOffsetToken;
        const auto Parent = Gs2::Log::Model::Cache::FExecuteStampTaskLogCache::CreateCacheParentKey(
        NamespaceName,
        TOptional<int32>()
    );
        return Gs2->Cache->ListSubscribeTyped(
            Gs2::Log::Model::FExecuteStampTaskLog::TypeName,
            Parent,
            [Callback, WeakGs2](const TArray<FGs2ObjectPtr>& Values)
            {
                if (!WeakGs2.Pin().IsValid()) return;
                TArray<Gs2::Log::Model::FExecuteStampTaskLogPtr> TypedValues;
                for (const auto& Value : Values) if (Value.IsValid()) TypedValues.Add(StaticCastSharedPtr<Gs2::Log::Model::FExecuteStampTaskLog>(Value));
                Callback(TypedValues);
            },
            [WeakGs2, WeakService, Callback, QueryNamespaceName, QueryService, QueryMethod, QueryUserId, QueryAction, QueryBegin, QueryEnd, QueryLongTerm, QueryTimeOffsetToken]()
            {
                const auto Owner = WeakGs2.Pin();
                if (!Owner.IsValid()) return;
                const auto Domain = MakeShared<FNamespaceDomain>(Owner, WeakService.Pin(), QueryNamespaceName);
                const auto Task = Gs2::Core::Util::New<FAsyncTask<FCollectExecuteStampTaskLogTask>>(Domain, Callback, QueryService, QueryMethod, QueryUserId, QueryAction, QueryBegin, QueryEnd, QueryLongTerm, QueryTimeOffsetToken);
                Task->StartBackgroundTask();
            }
        );
    }

    void FNamespaceDomain::InvalidateExecuteStampTaskLog(const TOptional<FString> Service,const TOptional<FString> Method,const TOptional<FString> UserId,const TOptional<FString> Action,const TOptional<int64> Begin,const TOptional<int64> End,const TOptional<bool> LongTerm,const TOptional<FString> TimeOffsetToken)
    {
        Gs2->Cache->ClearListCache(
            Gs2::Log::Model::FExecuteStampTaskLog::TypeName,
            Gs2::Log::Model::Cache::FExecuteStampTaskLogCache::CreateCacheParentKey(
        NamespaceName,
        TOptional<int32>()
    )
        );
    }

    FNamespaceDomain::FSubscribeExecuteStampTaskLogWithInitialCallTask::FSubscribeExecuteStampTaskLogWithInitialCallTask(const TSharedPtr<FNamespaceDomain>& Self, TFunction<void(TArray<Gs2::Log::Model::FExecuteStampTaskLogPtr>)> Callback,const TOptional<FString> Service,const TOptional<FString> Method,const TOptional<FString> UserId,const TOptional<FString> Action,const TOptional<int64> Begin,const TOptional<int64> End,const TOptional<bool> LongTerm,const TOptional<FString> TimeOffsetToken) : Self(Self), Callback(Callback), QueryService(Service), QueryMethod(Method), QueryUserId(UserId), QueryAction(Action), QueryBegin(Begin), QueryEnd(End), QueryLongTerm(LongTerm), QueryTimeOffsetToken(TimeOffsetToken) {}
    FNamespaceDomain::FSubscribeExecuteStampTaskLogWithInitialCallTask::FSubscribeExecuteStampTaskLogWithInitialCallTask(const FSubscribeExecuteStampTaskLogWithInitialCallTask& From) : TGs2Future(From), Self(From.Self), Callback(From.Callback), QueryService(From.QueryService), QueryMethod(From.QueryMethod), QueryUserId(From.QueryUserId), QueryAction(From.QueryAction), QueryBegin(From.QueryBegin), QueryEnd(From.QueryEnd), QueryLongTerm(From.QueryLongTerm), QueryTimeOffsetToken(From.QueryTimeOffsetToken) {}
    Gs2::Core::Model::FGs2ErrorPtr FNamespaceDomain::FSubscribeExecuteStampTaskLogWithInitialCallTask::Action(TSharedPtr<TSharedPtr<Gs2::Core::Domain::CallbackID>> Result)
    {
        const auto Task = Gs2::Core::Util::New<FAsyncTask<FCollectExecuteStampTaskLogTask>>(Self, TFunction<void(TArray<Gs2::Log::Model::FExecuteStampTaskLogPtr>)>(), QueryService, QueryMethod, QueryUserId, QueryAction, QueryBegin, QueryEnd, QueryLongTerm, QueryTimeOffsetToken);
        Task->StartSynchronousTask(); Task->EnsureCompletion();
        if (Task->GetTask().IsError()) return Task->GetTask().Error();
        const auto Values = Task->GetTask().Result();
        const auto CallbackId = Self->SubscribeExecuteStampTaskLog(Callback, QueryService, QueryMethod, QueryUserId, QueryAction, QueryBegin, QueryEnd, QueryLongTerm, QueryTimeOffsetToken);
        Callback(*Values); *Result = MakeShared<Gs2::Core::Domain::CallbackID>(CallbackId);
        return nullptr;
    }
    TSharedPtr<FAsyncTask<FNamespaceDomain::FSubscribeExecuteStampTaskLogWithInitialCallTask>> FNamespaceDomain::SubscribeExecuteStampTaskLogWithInitialCall(TFunction<void(TArray<Gs2::Log::Model::FExecuteStampTaskLogPtr>)> Callback,const TOptional<FString> Service,const TOptional<FString> Method,const TOptional<FString> UserId,const TOptional<FString> Action,const TOptional<int64> Begin,const TOptional<int64> End,const TOptional<bool> LongTerm,const TOptional<FString> TimeOffsetToken)
    {
        return Gs2::Core::Util::New<FAsyncTask<FSubscribeExecuteStampTaskLogWithInitialCallTask>>(this->AsShared(), Callback, Service, Method, UserId, Action, Begin, End, LongTerm, TimeOffsetToken);
    }

    Gs2::Log::Domain::Iterator::FCountExecuteStampTaskLogIteratorPtr FNamespaceDomain::CountExecuteStampTaskLog(
        const TOptional<bool> Service,
        const TOptional<bool> Method,
        const TOptional<bool> UserId,
        const TOptional<bool> Action,
        const TOptional<int64> Begin,
        const TOptional<int64> End,
        const TOptional<bool> LongTerm,
        const TOptional<FString> TimeOffsetToken
    ) const
    {
        return MakeShared<Gs2::Log::Domain::Iterator::FCountExecuteStampTaskLogIterator>(
            Gs2,
            Client,
            NamespaceName,
            Service,
            Method,
            UserId,
            Action,
            Begin,
            End,
            LongTerm,
            TimeOffsetToken
        );
    }

    Gs2::Core::Domain::CallbackID FNamespaceDomain::SubscribeCountExecuteStampTaskLog(
    TFunction<void()> Callback
    )
    {
        return Gs2->Cache->ListSubscribe(
            Gs2::Log::Model::FExecuteStampTaskLogCount::TypeName,
            Gs2::Log::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
                NamespaceName,
                "ExecuteStampTaskLogCount"
            ),
            Callback,
            Callback
        );
    }
    void FNamespaceDomain::UnsubscribeCountExecuteStampTaskLog(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        Gs2->Cache->ListUnsubscribe(
            Gs2::Log::Model::FExecuteStampTaskLogCount::TypeName,
            Gs2::Log::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
                NamespaceName,
                "ExecuteStampTaskLogCount"
            ),
            CallbackID
        );
    }
    class FNamespaceDomain::FCollectCountExecuteStampTaskLogTask : public Gs2::Core::Util::TGs2Future<TArray<Gs2::Log::Model::FExecuteStampTaskLogCountPtr>>, public TSharedFromThis<FCollectCountExecuteStampTaskLogTask>
    {
        const TSharedPtr<FNamespaceDomain> Self;
        const TFunction<void(TArray<Gs2::Log::Model::FExecuteStampTaskLogCountPtr>)> OnCollected;
    const TOptional<bool> QueryService;const TOptional<bool> QueryMethod;const TOptional<bool> QueryUserId;const TOptional<bool> QueryAction;const TOptional<int64> QueryBegin;const TOptional<int64> QueryEnd;const TOptional<bool> QueryLongTerm;const TOptional<FString> QueryTimeOffsetToken;
    public:
        explicit FCollectCountExecuteStampTaskLogTask(const TSharedPtr<FNamespaceDomain>& Self, TFunction<void(TArray<Gs2::Log::Model::FExecuteStampTaskLogCountPtr>)> OnCollected,const TOptional<bool> Service,const TOptional<bool> Method,const TOptional<bool> UserId,const TOptional<bool> Action,const TOptional<int64> Begin,const TOptional<int64> End,const TOptional<bool> LongTerm,const TOptional<FString> TimeOffsetToken) : Self(Self), OnCollected(OnCollected), QueryService(Service), QueryMethod(Method), QueryUserId(UserId), QueryAction(Action), QueryBegin(Begin), QueryEnd(End), QueryLongTerm(LongTerm), QueryTimeOffsetToken(TimeOffsetToken) {}
        FCollectCountExecuteStampTaskLogTask(const FCollectCountExecuteStampTaskLogTask& From) : TGs2Future(From), Self(From.Self), OnCollected(From.OnCollected), QueryService(From.QueryService), QueryMethod(From.QueryMethod), QueryUserId(From.QueryUserId), QueryAction(From.QueryAction), QueryBegin(From.QueryBegin), QueryEnd(From.QueryEnd), QueryLongTerm(From.QueryLongTerm), QueryTimeOffsetToken(From.QueryTimeOffsetToken) {}
        virtual Gs2::Core::Model::FGs2ErrorPtr Action(TSharedPtr<TSharedPtr<TArray<Gs2::Log::Model::FExecuteStampTaskLogCountPtr>>> Result) override
        {
            TArray<Gs2::Log::Model::FExecuteStampTaskLogCountPtr> Items;
            auto Iterator = Self->CountExecuteStampTaskLog(QueryService, QueryMethod, QueryUserId, QueryAction, QueryBegin, QueryEnd, QueryLongTerm, QueryTimeOffsetToken)->begin();
            while (Iterator.HasNext())
            {
                if (Iterator.IsError()) return Iterator.Error();
                if (Iterator.IsCurrentValid()) Items.Add(Iterator.Current());
                ++Iterator;
            }
            if (Iterator.IsError()) return Iterator.Error();
            *Result = MakeShared<TArray<Gs2::Log::Model::FExecuteStampTaskLogCountPtr>>(Items);
            if (OnCollected) OnCollected(Items);
            return nullptr;
        }
    };

    Gs2::Core::Domain::CallbackID FNamespaceDomain::SubscribeCountExecuteStampTaskLog(
        TFunction<void(TArray<Gs2::Log::Model::FExecuteStampTaskLogCountPtr>)> Callback,const TOptional<bool> Service,const TOptional<bool> Method,const TOptional<bool> UserId,const TOptional<bool> Action,const TOptional<int64> Begin,const TOptional<int64> End,const TOptional<bool> LongTerm,const TOptional<FString> TimeOffsetToken
    )
    {
        const TWeakPtr<Gs2::Core::Domain::FGs2> WeakGs2 = this->Gs2;
        const TWeakPtr<Log::Domain::FGs2LogDomain> WeakService = this->Service;
        const auto QueryNamespaceName = NamespaceName;
        const auto QueryService = Service;
        const auto QueryMethod = Method;
        const auto QueryUserId = UserId;
        const auto QueryAction = Action;
        const auto QueryBegin = Begin;
        const auto QueryEnd = End;
        const auto QueryLongTerm = LongTerm;
        const auto QueryTimeOffsetToken = TimeOffsetToken;
        const auto Parent = Gs2::Log::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
        NamespaceName,
        "ExecuteStampTaskLogCount"
    );
        return Gs2->Cache->ListSubscribeTyped(
            Gs2::Log::Model::FExecuteStampTaskLogCount::TypeName,
            Parent,
            [Callback, WeakGs2](const TArray<FGs2ObjectPtr>& Values)
            {
                if (!WeakGs2.Pin().IsValid()) return;
                TArray<Gs2::Log::Model::FExecuteStampTaskLogCountPtr> TypedValues;
                for (const auto& Value : Values) if (Value.IsValid()) TypedValues.Add(StaticCastSharedPtr<Gs2::Log::Model::FExecuteStampTaskLogCount>(Value));
                Callback(TypedValues);
            },
            [WeakGs2, WeakService, Callback, QueryNamespaceName, QueryService, QueryMethod, QueryUserId, QueryAction, QueryBegin, QueryEnd, QueryLongTerm, QueryTimeOffsetToken]()
            {
                const auto Owner = WeakGs2.Pin();
                if (!Owner.IsValid()) return;
                const auto Domain = MakeShared<FNamespaceDomain>(Owner, WeakService.Pin(), QueryNamespaceName);
                const auto Task = Gs2::Core::Util::New<FAsyncTask<FCollectCountExecuteStampTaskLogTask>>(Domain, Callback, QueryService, QueryMethod, QueryUserId, QueryAction, QueryBegin, QueryEnd, QueryLongTerm, QueryTimeOffsetToken);
                Task->StartBackgroundTask();
            }
        );
    }

    void FNamespaceDomain::InvalidateCountExecuteStampTaskLog(const TOptional<bool> Service,const TOptional<bool> Method,const TOptional<bool> UserId,const TOptional<bool> Action,const TOptional<int64> Begin,const TOptional<int64> End,const TOptional<bool> LongTerm,const TOptional<FString> TimeOffsetToken)
    {
        Gs2->Cache->ClearListCache(
            Gs2::Log::Model::FExecuteStampTaskLogCount::TypeName,
            Gs2::Log::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
        NamespaceName,
        "ExecuteStampTaskLogCount"
    )
        );
    }

    FNamespaceDomain::FSubscribeCountExecuteStampTaskLogWithInitialCallTask::FSubscribeCountExecuteStampTaskLogWithInitialCallTask(const TSharedPtr<FNamespaceDomain>& Self, TFunction<void(TArray<Gs2::Log::Model::FExecuteStampTaskLogCountPtr>)> Callback,const TOptional<bool> Service,const TOptional<bool> Method,const TOptional<bool> UserId,const TOptional<bool> Action,const TOptional<int64> Begin,const TOptional<int64> End,const TOptional<bool> LongTerm,const TOptional<FString> TimeOffsetToken) : Self(Self), Callback(Callback), QueryService(Service), QueryMethod(Method), QueryUserId(UserId), QueryAction(Action), QueryBegin(Begin), QueryEnd(End), QueryLongTerm(LongTerm), QueryTimeOffsetToken(TimeOffsetToken) {}
    FNamespaceDomain::FSubscribeCountExecuteStampTaskLogWithInitialCallTask::FSubscribeCountExecuteStampTaskLogWithInitialCallTask(const FSubscribeCountExecuteStampTaskLogWithInitialCallTask& From) : TGs2Future(From), Self(From.Self), Callback(From.Callback), QueryService(From.QueryService), QueryMethod(From.QueryMethod), QueryUserId(From.QueryUserId), QueryAction(From.QueryAction), QueryBegin(From.QueryBegin), QueryEnd(From.QueryEnd), QueryLongTerm(From.QueryLongTerm), QueryTimeOffsetToken(From.QueryTimeOffsetToken) {}
    Gs2::Core::Model::FGs2ErrorPtr FNamespaceDomain::FSubscribeCountExecuteStampTaskLogWithInitialCallTask::Action(TSharedPtr<TSharedPtr<Gs2::Core::Domain::CallbackID>> Result)
    {
        const auto Task = Gs2::Core::Util::New<FAsyncTask<FCollectCountExecuteStampTaskLogTask>>(Self, TFunction<void(TArray<Gs2::Log::Model::FExecuteStampTaskLogCountPtr>)>(), QueryService, QueryMethod, QueryUserId, QueryAction, QueryBegin, QueryEnd, QueryLongTerm, QueryTimeOffsetToken);
        Task->StartSynchronousTask(); Task->EnsureCompletion();
        if (Task->GetTask().IsError()) return Task->GetTask().Error();
        const auto Values = Task->GetTask().Result();
        const auto CallbackId = Self->SubscribeCountExecuteStampTaskLog(Callback, QueryService, QueryMethod, QueryUserId, QueryAction, QueryBegin, QueryEnd, QueryLongTerm, QueryTimeOffsetToken);
        Callback(*Values); *Result = MakeShared<Gs2::Core::Domain::CallbackID>(CallbackId);
        return nullptr;
    }
    TSharedPtr<FAsyncTask<FNamespaceDomain::FSubscribeCountExecuteStampTaskLogWithInitialCallTask>> FNamespaceDomain::SubscribeCountExecuteStampTaskLogWithInitialCall(TFunction<void(TArray<Gs2::Log::Model::FExecuteStampTaskLogCountPtr>)> Callback,const TOptional<bool> Service,const TOptional<bool> Method,const TOptional<bool> UserId,const TOptional<bool> Action,const TOptional<int64> Begin,const TOptional<int64> End,const TOptional<bool> LongTerm,const TOptional<FString> TimeOffsetToken)
    {
        return Gs2::Core::Util::New<FAsyncTask<FSubscribeCountExecuteStampTaskLogWithInitialCallTask>>(this->AsShared(), Callback, Service, Method, UserId, Action, Begin, End, LongTerm, TimeOffsetToken);
    }

    Gs2::Log::Domain::Iterator::FQueryIssueStampSheetLogIteratorPtr FNamespaceDomain::IssueStampSheetLog(
        const TOptional<FString> Service,
        const TOptional<FString> Method,
        const TOptional<FString> UserId,
        const TOptional<FString> Action,
        const TOptional<int64> Begin,
        const TOptional<int64> End,
        const TOptional<bool> LongTerm,
        const TOptional<FString> TimeOffsetToken
    ) const
    {
        return MakeShared<Gs2::Log::Domain::Iterator::FQueryIssueStampSheetLogIterator>(
            Gs2,
            Client,
            NamespaceName,
            Service,
            Method,
            UserId,
            Action,
            Begin,
            End,
            LongTerm,
            TimeOffsetToken
        );
    }

    Gs2::Core::Domain::CallbackID FNamespaceDomain::SubscribeIssueStampSheetLog(
    TFunction<void()> Callback
    )
    {
        return Gs2->Cache->ListSubscribe(
            Gs2::Log::Model::FIssueStampSheetLog::TypeName,
            Gs2::Log::Model::Cache::FIssueStampSheetLogCache::CreateCacheParentKey(
                NamespaceName,
                TOptional<int32>()
            ),
            Callback,
            Callback
        );
    }
    void FNamespaceDomain::UnsubscribeIssueStampSheetLog(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        Gs2->Cache->ListUnsubscribe(
            Gs2::Log::Model::FIssueStampSheetLog::TypeName,
            Gs2::Log::Model::Cache::FIssueStampSheetLogCache::CreateCacheParentKey(
                NamespaceName,
                TOptional<int32>()
            ),
            CallbackID
        );
    }
    class FNamespaceDomain::FCollectIssueStampSheetLogTask : public Gs2::Core::Util::TGs2Future<TArray<Gs2::Log::Model::FIssueStampSheetLogPtr>>, public TSharedFromThis<FCollectIssueStampSheetLogTask>
    {
        const TSharedPtr<FNamespaceDomain> Self;
        const TFunction<void(TArray<Gs2::Log::Model::FIssueStampSheetLogPtr>)> OnCollected;
    const TOptional<FString> QueryService;const TOptional<FString> QueryMethod;const TOptional<FString> QueryUserId;const TOptional<FString> QueryAction;const TOptional<int64> QueryBegin;const TOptional<int64> QueryEnd;const TOptional<bool> QueryLongTerm;const TOptional<FString> QueryTimeOffsetToken;
    public:
        explicit FCollectIssueStampSheetLogTask(const TSharedPtr<FNamespaceDomain>& Self, TFunction<void(TArray<Gs2::Log::Model::FIssueStampSheetLogPtr>)> OnCollected,const TOptional<FString> Service,const TOptional<FString> Method,const TOptional<FString> UserId,const TOptional<FString> Action,const TOptional<int64> Begin,const TOptional<int64> End,const TOptional<bool> LongTerm,const TOptional<FString> TimeOffsetToken) : Self(Self), OnCollected(OnCollected), QueryService(Service), QueryMethod(Method), QueryUserId(UserId), QueryAction(Action), QueryBegin(Begin), QueryEnd(End), QueryLongTerm(LongTerm), QueryTimeOffsetToken(TimeOffsetToken) {}
        FCollectIssueStampSheetLogTask(const FCollectIssueStampSheetLogTask& From) : TGs2Future(From), Self(From.Self), OnCollected(From.OnCollected), QueryService(From.QueryService), QueryMethod(From.QueryMethod), QueryUserId(From.QueryUserId), QueryAction(From.QueryAction), QueryBegin(From.QueryBegin), QueryEnd(From.QueryEnd), QueryLongTerm(From.QueryLongTerm), QueryTimeOffsetToken(From.QueryTimeOffsetToken) {}
        virtual Gs2::Core::Model::FGs2ErrorPtr Action(TSharedPtr<TSharedPtr<TArray<Gs2::Log::Model::FIssueStampSheetLogPtr>>> Result) override
        {
            TArray<Gs2::Log::Model::FIssueStampSheetLogPtr> Items;
            auto Iterator = Self->IssueStampSheetLog(QueryService, QueryMethod, QueryUserId, QueryAction, QueryBegin, QueryEnd, QueryLongTerm, QueryTimeOffsetToken)->begin();
            while (Iterator.HasNext())
            {
                if (Iterator.IsError()) return Iterator.Error();
                if (Iterator.IsCurrentValid()) Items.Add(Iterator.Current());
                ++Iterator;
            }
            if (Iterator.IsError()) return Iterator.Error();
            *Result = MakeShared<TArray<Gs2::Log::Model::FIssueStampSheetLogPtr>>(Items);
            if (OnCollected) OnCollected(Items);
            return nullptr;
        }
    };

    Gs2::Core::Domain::CallbackID FNamespaceDomain::SubscribeIssueStampSheetLog(
        TFunction<void(TArray<Gs2::Log::Model::FIssueStampSheetLogPtr>)> Callback,const TOptional<FString> Service,const TOptional<FString> Method,const TOptional<FString> UserId,const TOptional<FString> Action,const TOptional<int64> Begin,const TOptional<int64> End,const TOptional<bool> LongTerm,const TOptional<FString> TimeOffsetToken
    )
    {
        const TWeakPtr<Gs2::Core::Domain::FGs2> WeakGs2 = this->Gs2;
        const TWeakPtr<Log::Domain::FGs2LogDomain> WeakService = this->Service;
        const auto QueryNamespaceName = NamespaceName;
        const auto QueryService = Service;
        const auto QueryMethod = Method;
        const auto QueryUserId = UserId;
        const auto QueryAction = Action;
        const auto QueryBegin = Begin;
        const auto QueryEnd = End;
        const auto QueryLongTerm = LongTerm;
        const auto QueryTimeOffsetToken = TimeOffsetToken;
        const auto Parent = Gs2::Log::Model::Cache::FIssueStampSheetLogCache::CreateCacheParentKey(
        NamespaceName,
        TOptional<int32>()
    );
        return Gs2->Cache->ListSubscribeTyped(
            Gs2::Log::Model::FIssueStampSheetLog::TypeName,
            Parent,
            [Callback, WeakGs2](const TArray<FGs2ObjectPtr>& Values)
            {
                if (!WeakGs2.Pin().IsValid()) return;
                TArray<Gs2::Log::Model::FIssueStampSheetLogPtr> TypedValues;
                for (const auto& Value : Values) if (Value.IsValid()) TypedValues.Add(StaticCastSharedPtr<Gs2::Log::Model::FIssueStampSheetLog>(Value));
                Callback(TypedValues);
            },
            [WeakGs2, WeakService, Callback, QueryNamespaceName, QueryService, QueryMethod, QueryUserId, QueryAction, QueryBegin, QueryEnd, QueryLongTerm, QueryTimeOffsetToken]()
            {
                const auto Owner = WeakGs2.Pin();
                if (!Owner.IsValid()) return;
                const auto Domain = MakeShared<FNamespaceDomain>(Owner, WeakService.Pin(), QueryNamespaceName);
                const auto Task = Gs2::Core::Util::New<FAsyncTask<FCollectIssueStampSheetLogTask>>(Domain, Callback, QueryService, QueryMethod, QueryUserId, QueryAction, QueryBegin, QueryEnd, QueryLongTerm, QueryTimeOffsetToken);
                Task->StartBackgroundTask();
            }
        );
    }

    void FNamespaceDomain::InvalidateIssueStampSheetLog(const TOptional<FString> Service,const TOptional<FString> Method,const TOptional<FString> UserId,const TOptional<FString> Action,const TOptional<int64> Begin,const TOptional<int64> End,const TOptional<bool> LongTerm,const TOptional<FString> TimeOffsetToken)
    {
        Gs2->Cache->ClearListCache(
            Gs2::Log::Model::FIssueStampSheetLog::TypeName,
            Gs2::Log::Model::Cache::FIssueStampSheetLogCache::CreateCacheParentKey(
        NamespaceName,
        TOptional<int32>()
    )
        );
    }

    FNamespaceDomain::FSubscribeIssueStampSheetLogWithInitialCallTask::FSubscribeIssueStampSheetLogWithInitialCallTask(const TSharedPtr<FNamespaceDomain>& Self, TFunction<void(TArray<Gs2::Log::Model::FIssueStampSheetLogPtr>)> Callback,const TOptional<FString> Service,const TOptional<FString> Method,const TOptional<FString> UserId,const TOptional<FString> Action,const TOptional<int64> Begin,const TOptional<int64> End,const TOptional<bool> LongTerm,const TOptional<FString> TimeOffsetToken) : Self(Self), Callback(Callback), QueryService(Service), QueryMethod(Method), QueryUserId(UserId), QueryAction(Action), QueryBegin(Begin), QueryEnd(End), QueryLongTerm(LongTerm), QueryTimeOffsetToken(TimeOffsetToken) {}
    FNamespaceDomain::FSubscribeIssueStampSheetLogWithInitialCallTask::FSubscribeIssueStampSheetLogWithInitialCallTask(const FSubscribeIssueStampSheetLogWithInitialCallTask& From) : TGs2Future(From), Self(From.Self), Callback(From.Callback), QueryService(From.QueryService), QueryMethod(From.QueryMethod), QueryUserId(From.QueryUserId), QueryAction(From.QueryAction), QueryBegin(From.QueryBegin), QueryEnd(From.QueryEnd), QueryLongTerm(From.QueryLongTerm), QueryTimeOffsetToken(From.QueryTimeOffsetToken) {}
    Gs2::Core::Model::FGs2ErrorPtr FNamespaceDomain::FSubscribeIssueStampSheetLogWithInitialCallTask::Action(TSharedPtr<TSharedPtr<Gs2::Core::Domain::CallbackID>> Result)
    {
        const auto Task = Gs2::Core::Util::New<FAsyncTask<FCollectIssueStampSheetLogTask>>(Self, TFunction<void(TArray<Gs2::Log::Model::FIssueStampSheetLogPtr>)>(), QueryService, QueryMethod, QueryUserId, QueryAction, QueryBegin, QueryEnd, QueryLongTerm, QueryTimeOffsetToken);
        Task->StartSynchronousTask(); Task->EnsureCompletion();
        if (Task->GetTask().IsError()) return Task->GetTask().Error();
        const auto Values = Task->GetTask().Result();
        const auto CallbackId = Self->SubscribeIssueStampSheetLog(Callback, QueryService, QueryMethod, QueryUserId, QueryAction, QueryBegin, QueryEnd, QueryLongTerm, QueryTimeOffsetToken);
        Callback(*Values); *Result = MakeShared<Gs2::Core::Domain::CallbackID>(CallbackId);
        return nullptr;
    }
    TSharedPtr<FAsyncTask<FNamespaceDomain::FSubscribeIssueStampSheetLogWithInitialCallTask>> FNamespaceDomain::SubscribeIssueStampSheetLogWithInitialCall(TFunction<void(TArray<Gs2::Log::Model::FIssueStampSheetLogPtr>)> Callback,const TOptional<FString> Service,const TOptional<FString> Method,const TOptional<FString> UserId,const TOptional<FString> Action,const TOptional<int64> Begin,const TOptional<int64> End,const TOptional<bool> LongTerm,const TOptional<FString> TimeOffsetToken)
    {
        return Gs2::Core::Util::New<FAsyncTask<FSubscribeIssueStampSheetLogWithInitialCallTask>>(this->AsShared(), Callback, Service, Method, UserId, Action, Begin, End, LongTerm, TimeOffsetToken);
    }

    Gs2::Log::Domain::Iterator::FCountIssueStampSheetLogIteratorPtr FNamespaceDomain::CountIssueStampSheetLog(
        const TOptional<bool> Service,
        const TOptional<bool> Method,
        const TOptional<bool> UserId,
        const TOptional<bool> Action,
        const TOptional<int64> Begin,
        const TOptional<int64> End,
        const TOptional<bool> LongTerm,
        const TOptional<FString> TimeOffsetToken
    ) const
    {
        return MakeShared<Gs2::Log::Domain::Iterator::FCountIssueStampSheetLogIterator>(
            Gs2,
            Client,
            NamespaceName,
            Service,
            Method,
            UserId,
            Action,
            Begin,
            End,
            LongTerm,
            TimeOffsetToken
        );
    }

    Gs2::Core::Domain::CallbackID FNamespaceDomain::SubscribeCountIssueStampSheetLog(
    TFunction<void()> Callback
    )
    {
        return Gs2->Cache->ListSubscribe(
            Gs2::Log::Model::FIssueStampSheetLogCount::TypeName,
            Gs2::Log::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
                NamespaceName,
                "IssueStampSheetLogCount"
            ),
            Callback,
            Callback
        );
    }
    void FNamespaceDomain::UnsubscribeCountIssueStampSheetLog(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        Gs2->Cache->ListUnsubscribe(
            Gs2::Log::Model::FIssueStampSheetLogCount::TypeName,
            Gs2::Log::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
                NamespaceName,
                "IssueStampSheetLogCount"
            ),
            CallbackID
        );
    }
    class FNamespaceDomain::FCollectCountIssueStampSheetLogTask : public Gs2::Core::Util::TGs2Future<TArray<Gs2::Log::Model::FIssueStampSheetLogCountPtr>>, public TSharedFromThis<FCollectCountIssueStampSheetLogTask>
    {
        const TSharedPtr<FNamespaceDomain> Self;
        const TFunction<void(TArray<Gs2::Log::Model::FIssueStampSheetLogCountPtr>)> OnCollected;
    const TOptional<bool> QueryService;const TOptional<bool> QueryMethod;const TOptional<bool> QueryUserId;const TOptional<bool> QueryAction;const TOptional<int64> QueryBegin;const TOptional<int64> QueryEnd;const TOptional<bool> QueryLongTerm;const TOptional<FString> QueryTimeOffsetToken;
    public:
        explicit FCollectCountIssueStampSheetLogTask(const TSharedPtr<FNamespaceDomain>& Self, TFunction<void(TArray<Gs2::Log::Model::FIssueStampSheetLogCountPtr>)> OnCollected,const TOptional<bool> Service,const TOptional<bool> Method,const TOptional<bool> UserId,const TOptional<bool> Action,const TOptional<int64> Begin,const TOptional<int64> End,const TOptional<bool> LongTerm,const TOptional<FString> TimeOffsetToken) : Self(Self), OnCollected(OnCollected), QueryService(Service), QueryMethod(Method), QueryUserId(UserId), QueryAction(Action), QueryBegin(Begin), QueryEnd(End), QueryLongTerm(LongTerm), QueryTimeOffsetToken(TimeOffsetToken) {}
        FCollectCountIssueStampSheetLogTask(const FCollectCountIssueStampSheetLogTask& From) : TGs2Future(From), Self(From.Self), OnCollected(From.OnCollected), QueryService(From.QueryService), QueryMethod(From.QueryMethod), QueryUserId(From.QueryUserId), QueryAction(From.QueryAction), QueryBegin(From.QueryBegin), QueryEnd(From.QueryEnd), QueryLongTerm(From.QueryLongTerm), QueryTimeOffsetToken(From.QueryTimeOffsetToken) {}
        virtual Gs2::Core::Model::FGs2ErrorPtr Action(TSharedPtr<TSharedPtr<TArray<Gs2::Log::Model::FIssueStampSheetLogCountPtr>>> Result) override
        {
            TArray<Gs2::Log::Model::FIssueStampSheetLogCountPtr> Items;
            auto Iterator = Self->CountIssueStampSheetLog(QueryService, QueryMethod, QueryUserId, QueryAction, QueryBegin, QueryEnd, QueryLongTerm, QueryTimeOffsetToken)->begin();
            while (Iterator.HasNext())
            {
                if (Iterator.IsError()) return Iterator.Error();
                if (Iterator.IsCurrentValid()) Items.Add(Iterator.Current());
                ++Iterator;
            }
            if (Iterator.IsError()) return Iterator.Error();
            *Result = MakeShared<TArray<Gs2::Log::Model::FIssueStampSheetLogCountPtr>>(Items);
            if (OnCollected) OnCollected(Items);
            return nullptr;
        }
    };

    Gs2::Core::Domain::CallbackID FNamespaceDomain::SubscribeCountIssueStampSheetLog(
        TFunction<void(TArray<Gs2::Log::Model::FIssueStampSheetLogCountPtr>)> Callback,const TOptional<bool> Service,const TOptional<bool> Method,const TOptional<bool> UserId,const TOptional<bool> Action,const TOptional<int64> Begin,const TOptional<int64> End,const TOptional<bool> LongTerm,const TOptional<FString> TimeOffsetToken
    )
    {
        const TWeakPtr<Gs2::Core::Domain::FGs2> WeakGs2 = this->Gs2;
        const TWeakPtr<Log::Domain::FGs2LogDomain> WeakService = this->Service;
        const auto QueryNamespaceName = NamespaceName;
        const auto QueryService = Service;
        const auto QueryMethod = Method;
        const auto QueryUserId = UserId;
        const auto QueryAction = Action;
        const auto QueryBegin = Begin;
        const auto QueryEnd = End;
        const auto QueryLongTerm = LongTerm;
        const auto QueryTimeOffsetToken = TimeOffsetToken;
        const auto Parent = Gs2::Log::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
        NamespaceName,
        "IssueStampSheetLogCount"
    );
        return Gs2->Cache->ListSubscribeTyped(
            Gs2::Log::Model::FIssueStampSheetLogCount::TypeName,
            Parent,
            [Callback, WeakGs2](const TArray<FGs2ObjectPtr>& Values)
            {
                if (!WeakGs2.Pin().IsValid()) return;
                TArray<Gs2::Log::Model::FIssueStampSheetLogCountPtr> TypedValues;
                for (const auto& Value : Values) if (Value.IsValid()) TypedValues.Add(StaticCastSharedPtr<Gs2::Log::Model::FIssueStampSheetLogCount>(Value));
                Callback(TypedValues);
            },
            [WeakGs2, WeakService, Callback, QueryNamespaceName, QueryService, QueryMethod, QueryUserId, QueryAction, QueryBegin, QueryEnd, QueryLongTerm, QueryTimeOffsetToken]()
            {
                const auto Owner = WeakGs2.Pin();
                if (!Owner.IsValid()) return;
                const auto Domain = MakeShared<FNamespaceDomain>(Owner, WeakService.Pin(), QueryNamespaceName);
                const auto Task = Gs2::Core::Util::New<FAsyncTask<FCollectCountIssueStampSheetLogTask>>(Domain, Callback, QueryService, QueryMethod, QueryUserId, QueryAction, QueryBegin, QueryEnd, QueryLongTerm, QueryTimeOffsetToken);
                Task->StartBackgroundTask();
            }
        );
    }

    void FNamespaceDomain::InvalidateCountIssueStampSheetLog(const TOptional<bool> Service,const TOptional<bool> Method,const TOptional<bool> UserId,const TOptional<bool> Action,const TOptional<int64> Begin,const TOptional<int64> End,const TOptional<bool> LongTerm,const TOptional<FString> TimeOffsetToken)
    {
        Gs2->Cache->ClearListCache(
            Gs2::Log::Model::FIssueStampSheetLogCount::TypeName,
            Gs2::Log::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
        NamespaceName,
        "IssueStampSheetLogCount"
    )
        );
    }

    FNamespaceDomain::FSubscribeCountIssueStampSheetLogWithInitialCallTask::FSubscribeCountIssueStampSheetLogWithInitialCallTask(const TSharedPtr<FNamespaceDomain>& Self, TFunction<void(TArray<Gs2::Log::Model::FIssueStampSheetLogCountPtr>)> Callback,const TOptional<bool> Service,const TOptional<bool> Method,const TOptional<bool> UserId,const TOptional<bool> Action,const TOptional<int64> Begin,const TOptional<int64> End,const TOptional<bool> LongTerm,const TOptional<FString> TimeOffsetToken) : Self(Self), Callback(Callback), QueryService(Service), QueryMethod(Method), QueryUserId(UserId), QueryAction(Action), QueryBegin(Begin), QueryEnd(End), QueryLongTerm(LongTerm), QueryTimeOffsetToken(TimeOffsetToken) {}
    FNamespaceDomain::FSubscribeCountIssueStampSheetLogWithInitialCallTask::FSubscribeCountIssueStampSheetLogWithInitialCallTask(const FSubscribeCountIssueStampSheetLogWithInitialCallTask& From) : TGs2Future(From), Self(From.Self), Callback(From.Callback), QueryService(From.QueryService), QueryMethod(From.QueryMethod), QueryUserId(From.QueryUserId), QueryAction(From.QueryAction), QueryBegin(From.QueryBegin), QueryEnd(From.QueryEnd), QueryLongTerm(From.QueryLongTerm), QueryTimeOffsetToken(From.QueryTimeOffsetToken) {}
    Gs2::Core::Model::FGs2ErrorPtr FNamespaceDomain::FSubscribeCountIssueStampSheetLogWithInitialCallTask::Action(TSharedPtr<TSharedPtr<Gs2::Core::Domain::CallbackID>> Result)
    {
        const auto Task = Gs2::Core::Util::New<FAsyncTask<FCollectCountIssueStampSheetLogTask>>(Self, TFunction<void(TArray<Gs2::Log::Model::FIssueStampSheetLogCountPtr>)>(), QueryService, QueryMethod, QueryUserId, QueryAction, QueryBegin, QueryEnd, QueryLongTerm, QueryTimeOffsetToken);
        Task->StartSynchronousTask(); Task->EnsureCompletion();
        if (Task->GetTask().IsError()) return Task->GetTask().Error();
        const auto Values = Task->GetTask().Result();
        const auto CallbackId = Self->SubscribeCountIssueStampSheetLog(Callback, QueryService, QueryMethod, QueryUserId, QueryAction, QueryBegin, QueryEnd, QueryLongTerm, QueryTimeOffsetToken);
        Callback(*Values); *Result = MakeShared<Gs2::Core::Domain::CallbackID>(CallbackId);
        return nullptr;
    }
    TSharedPtr<FAsyncTask<FNamespaceDomain::FSubscribeCountIssueStampSheetLogWithInitialCallTask>> FNamespaceDomain::SubscribeCountIssueStampSheetLogWithInitialCall(TFunction<void(TArray<Gs2::Log::Model::FIssueStampSheetLogCountPtr>)> Callback,const TOptional<bool> Service,const TOptional<bool> Method,const TOptional<bool> UserId,const TOptional<bool> Action,const TOptional<int64> Begin,const TOptional<int64> End,const TOptional<bool> LongTerm,const TOptional<FString> TimeOffsetToken)
    {
        return Gs2::Core::Util::New<FAsyncTask<FSubscribeCountIssueStampSheetLogWithInitialCallTask>>(this->AsShared(), Callback, Service, Method, UserId, Action, Begin, End, LongTerm, TimeOffsetToken);
    }

    Gs2::Log::Domain::Iterator::FDescribeInsightsIteratorPtr FNamespaceDomain::Insights(
    ) const
    {
        return MakeShared<Gs2::Log::Domain::Iterator::FDescribeInsightsIterator>(
            Gs2,
            Client,
            NamespaceName
        );
    }

    Gs2::Core::Domain::CallbackID FNamespaceDomain::SubscribeInsights(
    TFunction<void()> Callback
    )
    {
        return Gs2->Cache->ListSubscribe(
            Gs2::Log::Model::FInsight::TypeName,
            Gs2::Log::Model::Cache::FInsightCache::CreateCacheParentKey(
                NamespaceName,
                TOptional<int32>()
            ),
            Callback,
            Callback
        );
    }
    void FNamespaceDomain::UnsubscribeInsights(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        Gs2->Cache->ListUnsubscribe(
            Gs2::Log::Model::FInsight::TypeName,
            Gs2::Log::Model::Cache::FInsightCache::CreateCacheParentKey(
                NamespaceName,
                TOptional<int32>()
            ),
            CallbackID
        );
    }
    class FNamespaceDomain::FCollectInsightsTask : public Gs2::Core::Util::TGs2Future<TArray<Gs2::Log::Model::FInsightPtr>>, public TSharedFromThis<FCollectInsightsTask>
    {
        const TSharedPtr<FNamespaceDomain> Self;
        const TFunction<void(TArray<Gs2::Log::Model::FInsightPtr>)> OnCollected;

    public:
        explicit FCollectInsightsTask(const TSharedPtr<FNamespaceDomain>& Self, TFunction<void(TArray<Gs2::Log::Model::FInsightPtr>)> OnCollected) : Self(Self), OnCollected(OnCollected) {}
        FCollectInsightsTask(const FCollectInsightsTask& From) : TGs2Future(From), Self(From.Self), OnCollected(From.OnCollected) {}
        virtual Gs2::Core::Model::FGs2ErrorPtr Action(TSharedPtr<TSharedPtr<TArray<Gs2::Log::Model::FInsightPtr>>> Result) override
        {
            TArray<Gs2::Log::Model::FInsightPtr> Items;
            auto Iterator = Self->Insights()->begin();
            while (Iterator.HasNext())
            {
                if (Iterator.IsError()) return Iterator.Error();
                if (Iterator.IsCurrentValid()) Items.Add(Iterator.Current());
                ++Iterator;
            }
            if (Iterator.IsError()) return Iterator.Error();
            *Result = MakeShared<TArray<Gs2::Log::Model::FInsightPtr>>(Items);
            if (OnCollected) OnCollected(Items);
            return nullptr;
        }
    };

    Gs2::Core::Domain::CallbackID FNamespaceDomain::SubscribeInsights(
        TFunction<void(TArray<Gs2::Log::Model::FInsightPtr>)> Callback
    )
    {
        const TWeakPtr<Gs2::Core::Domain::FGs2> WeakGs2 = this->Gs2;
        const TWeakPtr<Log::Domain::FGs2LogDomain> WeakService = this->Service;
        const auto QueryNamespaceName = NamespaceName;
        const auto Parent = Gs2::Log::Model::Cache::FInsightCache::CreateCacheParentKey(
        NamespaceName,
        TOptional<int32>()
    );
        return Gs2->Cache->ListSubscribeTyped(
            Gs2::Log::Model::FInsight::TypeName,
            Parent,
            [Callback, WeakGs2](const TArray<FGs2ObjectPtr>& Values)
            {
                if (!WeakGs2.Pin().IsValid()) return;
                TArray<Gs2::Log::Model::FInsightPtr> TypedValues;
                for (const auto& Value : Values) if (Value.IsValid()) TypedValues.Add(StaticCastSharedPtr<Gs2::Log::Model::FInsight>(Value));
                Callback(TypedValues);
            },
            [WeakGs2, WeakService, Callback, QueryNamespaceName]()
            {
                const auto Owner = WeakGs2.Pin();
                if (!Owner.IsValid()) return;
                const auto Domain = MakeShared<FNamespaceDomain>(Owner, WeakService.Pin(), QueryNamespaceName);
                const auto Task = Gs2::Core::Util::New<FAsyncTask<FCollectInsightsTask>>(Domain, Callback);
                Task->StartBackgroundTask();
            }
        );
    }

    void FNamespaceDomain::InvalidateInsights()
    {
        Gs2->Cache->ClearListCache(
            Gs2::Log::Model::FInsight::TypeName,
            Gs2::Log::Model::Cache::FInsightCache::CreateCacheParentKey(
        NamespaceName,
        TOptional<int32>()
    )
        );
    }

    FNamespaceDomain::FSubscribeInsightsWithInitialCallTask::FSubscribeInsightsWithInitialCallTask(const TSharedPtr<FNamespaceDomain>& Self, TFunction<void(TArray<Gs2::Log::Model::FInsightPtr>)> Callback) : Self(Self), Callback(Callback) {}
    FNamespaceDomain::FSubscribeInsightsWithInitialCallTask::FSubscribeInsightsWithInitialCallTask(const FSubscribeInsightsWithInitialCallTask& From) : TGs2Future(From), Self(From.Self), Callback(From.Callback) {}
    Gs2::Core::Model::FGs2ErrorPtr FNamespaceDomain::FSubscribeInsightsWithInitialCallTask::Action(TSharedPtr<TSharedPtr<Gs2::Core::Domain::CallbackID>> Result)
    {
        const auto Task = Gs2::Core::Util::New<FAsyncTask<FCollectInsightsTask>>(Self, TFunction<void(TArray<Gs2::Log::Model::FInsightPtr>)>());
        Task->StartSynchronousTask(); Task->EnsureCompletion();
        if (Task->GetTask().IsError()) return Task->GetTask().Error();
        const auto Values = Task->GetTask().Result();
        const auto CallbackId = Self->SubscribeInsights(Callback);
        Callback(*Values); *Result = MakeShared<Gs2::Core::Domain::CallbackID>(CallbackId);
        return nullptr;
    }
    TSharedPtr<FAsyncTask<FNamespaceDomain::FSubscribeInsightsWithInitialCallTask>> FNamespaceDomain::SubscribeInsightsWithInitialCall(TFunction<void(TArray<Gs2::Log::Model::FInsightPtr>)> Callback)
    {
        return Gs2::Core::Util::New<FAsyncTask<FSubscribeInsightsWithInitialCallTask>>(this->AsShared(), Callback);
    }

    TSharedPtr<Gs2::Log::Domain::Model::FInsightDomain> FNamespaceDomain::Insight(
        const FString InsightName
    )
    {
        return MakeShared<Gs2::Log::Domain::Model::FInsightDomain>(
            Gs2,
            Service,
            NamespaceName,
            InsightName == TEXT("") ? TOptional<FString>() : TOptional<FString>(InsightName)
        );
    }

    Gs2::Log::Domain::Iterator::FQueryAccessLogWithTelemetryIteratorPtr FNamespaceDomain::AccessLogWithTelemetry(
        const TOptional<FString> UserId,
        const TOptional<int64> Begin,
        const TOptional<int64> End,
        const TOptional<bool> LongTerm,
        const TOptional<FString> TimeOffsetToken
    ) const
    {
        return MakeShared<Gs2::Log::Domain::Iterator::FQueryAccessLogWithTelemetryIterator>(
            Gs2,
            Client,
            NamespaceName,
            UserId,
            Begin,
            End,
            LongTerm,
            TimeOffsetToken
        );
    }

    Gs2::Core::Domain::CallbackID FNamespaceDomain::SubscribeAccessLogWithTelemetry(
    TFunction<void()> Callback
    )
    {
        return Gs2->Cache->ListSubscribe(
            Gs2::Log::Model::FAccessLogWithTelemetry::TypeName,
            Gs2::Log::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
                NamespaceName,
                "AccessLogWithTelemetry"
            ),
            Callback,
            Callback
        );
    }
    void FNamespaceDomain::UnsubscribeAccessLogWithTelemetry(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        Gs2->Cache->ListUnsubscribe(
            Gs2::Log::Model::FAccessLogWithTelemetry::TypeName,
            Gs2::Log::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
                NamespaceName,
                "AccessLogWithTelemetry"
            ),
            CallbackID
        );
    }
    class FNamespaceDomain::FCollectAccessLogWithTelemetryTask : public Gs2::Core::Util::TGs2Future<TArray<Gs2::Log::Model::FAccessLogWithTelemetryPtr>>, public TSharedFromThis<FCollectAccessLogWithTelemetryTask>
    {
        const TSharedPtr<FNamespaceDomain> Self;
        const TFunction<void(TArray<Gs2::Log::Model::FAccessLogWithTelemetryPtr>)> OnCollected;
    const TOptional<FString> QueryUserId;const TOptional<int64> QueryBegin;const TOptional<int64> QueryEnd;const TOptional<bool> QueryLongTerm;const TOptional<FString> QueryTimeOffsetToken;
    public:
        explicit FCollectAccessLogWithTelemetryTask(const TSharedPtr<FNamespaceDomain>& Self, TFunction<void(TArray<Gs2::Log::Model::FAccessLogWithTelemetryPtr>)> OnCollected,const TOptional<FString> UserId,const TOptional<int64> Begin,const TOptional<int64> End,const TOptional<bool> LongTerm,const TOptional<FString> TimeOffsetToken) : Self(Self), OnCollected(OnCollected), QueryUserId(UserId), QueryBegin(Begin), QueryEnd(End), QueryLongTerm(LongTerm), QueryTimeOffsetToken(TimeOffsetToken) {}
        FCollectAccessLogWithTelemetryTask(const FCollectAccessLogWithTelemetryTask& From) : TGs2Future(From), Self(From.Self), OnCollected(From.OnCollected), QueryUserId(From.QueryUserId), QueryBegin(From.QueryBegin), QueryEnd(From.QueryEnd), QueryLongTerm(From.QueryLongTerm), QueryTimeOffsetToken(From.QueryTimeOffsetToken) {}
        virtual Gs2::Core::Model::FGs2ErrorPtr Action(TSharedPtr<TSharedPtr<TArray<Gs2::Log::Model::FAccessLogWithTelemetryPtr>>> Result) override
        {
            TArray<Gs2::Log::Model::FAccessLogWithTelemetryPtr> Items;
            auto Iterator = Self->AccessLogWithTelemetry(QueryUserId, QueryBegin, QueryEnd, QueryLongTerm, QueryTimeOffsetToken)->begin();
            while (Iterator.HasNext())
            {
                if (Iterator.IsError()) return Iterator.Error();
                if (Iterator.IsCurrentValid()) Items.Add(Iterator.Current());
                ++Iterator;
            }
            if (Iterator.IsError()) return Iterator.Error();
            *Result = MakeShared<TArray<Gs2::Log::Model::FAccessLogWithTelemetryPtr>>(Items);
            if (OnCollected) OnCollected(Items);
            return nullptr;
        }
    };

    Gs2::Core::Domain::CallbackID FNamespaceDomain::SubscribeAccessLogWithTelemetry(
        TFunction<void(TArray<Gs2::Log::Model::FAccessLogWithTelemetryPtr>)> Callback,const TOptional<FString> UserId,const TOptional<int64> Begin,const TOptional<int64> End,const TOptional<bool> LongTerm,const TOptional<FString> TimeOffsetToken
    )
    {
        const TWeakPtr<Gs2::Core::Domain::FGs2> WeakGs2 = this->Gs2;
        const TWeakPtr<Log::Domain::FGs2LogDomain> WeakService = this->Service;
        const auto QueryNamespaceName = NamespaceName;
        const auto QueryUserId = UserId;
        const auto QueryBegin = Begin;
        const auto QueryEnd = End;
        const auto QueryLongTerm = LongTerm;
        const auto QueryTimeOffsetToken = TimeOffsetToken;
        const auto Parent = Gs2::Log::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
        NamespaceName,
        "AccessLogWithTelemetry"
    );
        return Gs2->Cache->ListSubscribeTyped(
            Gs2::Log::Model::FAccessLogWithTelemetry::TypeName,
            Parent,
            [Callback, WeakGs2](const TArray<FGs2ObjectPtr>& Values)
            {
                if (!WeakGs2.Pin().IsValid()) return;
                TArray<Gs2::Log::Model::FAccessLogWithTelemetryPtr> TypedValues;
                for (const auto& Value : Values) if (Value.IsValid()) TypedValues.Add(StaticCastSharedPtr<Gs2::Log::Model::FAccessLogWithTelemetry>(Value));
                Callback(TypedValues);
            },
            [WeakGs2, WeakService, Callback, QueryNamespaceName, QueryUserId, QueryBegin, QueryEnd, QueryLongTerm, QueryTimeOffsetToken]()
            {
                const auto Owner = WeakGs2.Pin();
                if (!Owner.IsValid()) return;
                const auto Domain = MakeShared<FNamespaceDomain>(Owner, WeakService.Pin(), QueryNamespaceName);
                const auto Task = Gs2::Core::Util::New<FAsyncTask<FCollectAccessLogWithTelemetryTask>>(Domain, Callback, QueryUserId, QueryBegin, QueryEnd, QueryLongTerm, QueryTimeOffsetToken);
                Task->StartBackgroundTask();
            }
        );
    }

    void FNamespaceDomain::InvalidateAccessLogWithTelemetry(const TOptional<FString> UserId,const TOptional<int64> Begin,const TOptional<int64> End,const TOptional<bool> LongTerm,const TOptional<FString> TimeOffsetToken)
    {
        Gs2->Cache->ClearListCache(
            Gs2::Log::Model::FAccessLogWithTelemetry::TypeName,
            Gs2::Log::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
        NamespaceName,
        "AccessLogWithTelemetry"
    )
        );
    }

    FNamespaceDomain::FSubscribeAccessLogWithTelemetryWithInitialCallTask::FSubscribeAccessLogWithTelemetryWithInitialCallTask(const TSharedPtr<FNamespaceDomain>& Self, TFunction<void(TArray<Gs2::Log::Model::FAccessLogWithTelemetryPtr>)> Callback,const TOptional<FString> UserId,const TOptional<int64> Begin,const TOptional<int64> End,const TOptional<bool> LongTerm,const TOptional<FString> TimeOffsetToken) : Self(Self), Callback(Callback), QueryUserId(UserId), QueryBegin(Begin), QueryEnd(End), QueryLongTerm(LongTerm), QueryTimeOffsetToken(TimeOffsetToken) {}
    FNamespaceDomain::FSubscribeAccessLogWithTelemetryWithInitialCallTask::FSubscribeAccessLogWithTelemetryWithInitialCallTask(const FSubscribeAccessLogWithTelemetryWithInitialCallTask& From) : TGs2Future(From), Self(From.Self), Callback(From.Callback), QueryUserId(From.QueryUserId), QueryBegin(From.QueryBegin), QueryEnd(From.QueryEnd), QueryLongTerm(From.QueryLongTerm), QueryTimeOffsetToken(From.QueryTimeOffsetToken) {}
    Gs2::Core::Model::FGs2ErrorPtr FNamespaceDomain::FSubscribeAccessLogWithTelemetryWithInitialCallTask::Action(TSharedPtr<TSharedPtr<Gs2::Core::Domain::CallbackID>> Result)
    {
        const auto Task = Gs2::Core::Util::New<FAsyncTask<FCollectAccessLogWithTelemetryTask>>(Self, TFunction<void(TArray<Gs2::Log::Model::FAccessLogWithTelemetryPtr>)>(), QueryUserId, QueryBegin, QueryEnd, QueryLongTerm, QueryTimeOffsetToken);
        Task->StartSynchronousTask(); Task->EnsureCompletion();
        if (Task->GetTask().IsError()) return Task->GetTask().Error();
        const auto Values = Task->GetTask().Result();
        const auto CallbackId = Self->SubscribeAccessLogWithTelemetry(Callback, QueryUserId, QueryBegin, QueryEnd, QueryLongTerm, QueryTimeOffsetToken);
        Callback(*Values); *Result = MakeShared<Gs2::Core::Domain::CallbackID>(CallbackId);
        return nullptr;
    }
    TSharedPtr<FAsyncTask<FNamespaceDomain::FSubscribeAccessLogWithTelemetryWithInitialCallTask>> FNamespaceDomain::SubscribeAccessLogWithTelemetryWithInitialCall(TFunction<void(TArray<Gs2::Log::Model::FAccessLogWithTelemetryPtr>)> Callback,const TOptional<FString> UserId,const TOptional<int64> Begin,const TOptional<int64> End,const TOptional<bool> LongTerm,const TOptional<FString> TimeOffsetToken)
    {
        return Gs2::Core::Util::New<FAsyncTask<FSubscribeAccessLogWithTelemetryWithInitialCallTask>>(this->AsShared(), Callback, UserId, Begin, End, LongTerm, TimeOffsetToken);
    }

    TSharedPtr<Gs2::Log::Domain::Model::FUserDomain> FNamespaceDomain::User(
        const FString UserId
    )
    {
        return MakeShared<Gs2::Log::Domain::Model::FUserDomain>(
            Gs2,
            Service,
            NamespaceName,
            UserId == TEXT("") ? TOptional<FString>() : TOptional<FString>(UserId)
        );
    }

    TSharedPtr<Gs2::Log::Domain::Model::FUserAccessTokenDomain> FNamespaceDomain::AccessToken(
        Gs2::Auth::Model::FAccessTokenPtr AccessToken
    )
    {
        return MakeShared<Gs2::Log::Domain::Model::FUserAccessTokenDomain>(
            Gs2,
            Service,
            NamespaceName,
            AccessToken
        );
    }

    Gs2::Log::Domain::Iterator::FDescribeFacetModelsIteratorPtr FNamespaceDomain::FacetModels(
        const TOptional<FString> NamePrefix
    ) const
    {
        return MakeShared<Gs2::Log::Domain::Iterator::FDescribeFacetModelsIterator>(
            Gs2,
            Client,
            NamespaceName,
            NamePrefix
        );
    }

    Gs2::Core::Domain::CallbackID FNamespaceDomain::SubscribeFacetModels(
    TFunction<void()> Callback
    )
    {
        return Gs2->Cache->ListSubscribe(
            Gs2::Log::Model::FFacetModel::TypeName,
            Gs2::Log::Model::Cache::FFacetModelCache::CreateCacheParentKey(
                NamespaceName,
                TOptional<int32>()
            ),
            Callback,
            Callback
        );
    }
    void FNamespaceDomain::UnsubscribeFacetModels(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        Gs2->Cache->ListUnsubscribe(
            Gs2::Log::Model::FFacetModel::TypeName,
            Gs2::Log::Model::Cache::FFacetModelCache::CreateCacheParentKey(
                NamespaceName,
                TOptional<int32>()
            ),
            CallbackID
        );
    }
    class FNamespaceDomain::FCollectFacetModelsTask : public Gs2::Core::Util::TGs2Future<TArray<Gs2::Log::Model::FFacetModelPtr>>, public TSharedFromThis<FCollectFacetModelsTask>
    {
        const TSharedPtr<FNamespaceDomain> Self;
        const TFunction<void(TArray<Gs2::Log::Model::FFacetModelPtr>)> OnCollected;
    const TOptional<FString> QueryNamePrefix;
    public:
        explicit FCollectFacetModelsTask(const TSharedPtr<FNamespaceDomain>& Self, TFunction<void(TArray<Gs2::Log::Model::FFacetModelPtr>)> OnCollected,const TOptional<FString> NamePrefix) : Self(Self), OnCollected(OnCollected), QueryNamePrefix(NamePrefix) {}
        FCollectFacetModelsTask(const FCollectFacetModelsTask& From) : TGs2Future(From), Self(From.Self), OnCollected(From.OnCollected), QueryNamePrefix(From.QueryNamePrefix) {}
        virtual Gs2::Core::Model::FGs2ErrorPtr Action(TSharedPtr<TSharedPtr<TArray<Gs2::Log::Model::FFacetModelPtr>>> Result) override
        {
            TArray<Gs2::Log::Model::FFacetModelPtr> Items;
            auto Iterator = Self->FacetModels(QueryNamePrefix)->begin();
            while (Iterator.HasNext())
            {
                if (Iterator.IsError()) return Iterator.Error();
                if (Iterator.IsCurrentValid()) Items.Add(Iterator.Current());
                ++Iterator;
            }
            if (Iterator.IsError()) return Iterator.Error();
            *Result = MakeShared<TArray<Gs2::Log::Model::FFacetModelPtr>>(Items);
            if (OnCollected) OnCollected(Items);
            return nullptr;
        }
    };

    Gs2::Core::Domain::CallbackID FNamespaceDomain::SubscribeFacetModels(
        TFunction<void(TArray<Gs2::Log::Model::FFacetModelPtr>)> Callback,const TOptional<FString> NamePrefix
    )
    {
        const TWeakPtr<Gs2::Core::Domain::FGs2> WeakGs2 = this->Gs2;
        const TWeakPtr<Log::Domain::FGs2LogDomain> WeakService = this->Service;
        const auto QueryNamespaceName = NamespaceName;
        const auto QueryNamePrefix = NamePrefix;
        const auto Parent = Gs2::Log::Model::Cache::FFacetModelCache::CreateCacheParentKey(
        NamespaceName,
        TOptional<int32>()
    );
        return Gs2->Cache->ListSubscribeTyped(
            Gs2::Log::Model::FFacetModel::TypeName,
            Parent,
            [Callback, WeakGs2](const TArray<FGs2ObjectPtr>& Values)
            {
                if (!WeakGs2.Pin().IsValid()) return;
                TArray<Gs2::Log::Model::FFacetModelPtr> TypedValues;
                for (const auto& Value : Values) if (Value.IsValid()) TypedValues.Add(StaticCastSharedPtr<Gs2::Log::Model::FFacetModel>(Value));
                Callback(TypedValues);
            },
            [WeakGs2, WeakService, Callback, QueryNamespaceName, QueryNamePrefix]()
            {
                const auto Owner = WeakGs2.Pin();
                if (!Owner.IsValid()) return;
                const auto Domain = MakeShared<FNamespaceDomain>(Owner, WeakService.Pin(), QueryNamespaceName);
                const auto Task = Gs2::Core::Util::New<FAsyncTask<FCollectFacetModelsTask>>(Domain, Callback, QueryNamePrefix);
                Task->StartBackgroundTask();
            }
        );
    }

    void FNamespaceDomain::InvalidateFacetModels(const TOptional<FString> NamePrefix)
    {
        Gs2->Cache->ClearListCache(
            Gs2::Log::Model::FFacetModel::TypeName,
            Gs2::Log::Model::Cache::FFacetModelCache::CreateCacheParentKey(
        NamespaceName,
        TOptional<int32>()
    )
        );
    }

    FNamespaceDomain::FSubscribeFacetModelsWithInitialCallTask::FSubscribeFacetModelsWithInitialCallTask(const TSharedPtr<FNamespaceDomain>& Self, TFunction<void(TArray<Gs2::Log::Model::FFacetModelPtr>)> Callback,const TOptional<FString> NamePrefix) : Self(Self), Callback(Callback), QueryNamePrefix(NamePrefix) {}
    FNamespaceDomain::FSubscribeFacetModelsWithInitialCallTask::FSubscribeFacetModelsWithInitialCallTask(const FSubscribeFacetModelsWithInitialCallTask& From) : TGs2Future(From), Self(From.Self), Callback(From.Callback), QueryNamePrefix(From.QueryNamePrefix) {}
    Gs2::Core::Model::FGs2ErrorPtr FNamespaceDomain::FSubscribeFacetModelsWithInitialCallTask::Action(TSharedPtr<TSharedPtr<Gs2::Core::Domain::CallbackID>> Result)
    {
        const auto Task = Gs2::Core::Util::New<FAsyncTask<FCollectFacetModelsTask>>(Self, TFunction<void(TArray<Gs2::Log::Model::FFacetModelPtr>)>(), QueryNamePrefix);
        Task->StartSynchronousTask(); Task->EnsureCompletion();
        if (Task->GetTask().IsError()) return Task->GetTask().Error();
        const auto Values = Task->GetTask().Result();
        const auto CallbackId = Self->SubscribeFacetModels(Callback, QueryNamePrefix);
        Callback(*Values); *Result = MakeShared<Gs2::Core::Domain::CallbackID>(CallbackId);
        return nullptr;
    }
    TSharedPtr<FAsyncTask<FNamespaceDomain::FSubscribeFacetModelsWithInitialCallTask>> FNamespaceDomain::SubscribeFacetModelsWithInitialCall(TFunction<void(TArray<Gs2::Log::Model::FFacetModelPtr>)> Callback,const TOptional<FString> NamePrefix)
    {
        return Gs2::Core::Util::New<FAsyncTask<FSubscribeFacetModelsWithInitialCallTask>>(this->AsShared(), Callback, NamePrefix);
    }

    TSharedPtr<Gs2::Log::Domain::Model::FFacetModelDomain> FNamespaceDomain::FacetModel(
        const FString Field
    )
    {
        return MakeShared<Gs2::Log::Domain::Model::FFacetModelDomain>(
            Gs2,
            Service,
            NamespaceName,
            Field == TEXT("") ? TOptional<FString>() : TOptional<FString>(Field)
        );
    }

    Gs2::Log::Domain::Iterator::FDescribeDashboardsIteratorPtr FNamespaceDomain::Dashboards(
        const TOptional<FString> NamePrefix
    ) const
    {
        return MakeShared<Gs2::Log::Domain::Iterator::FDescribeDashboardsIterator>(
            Gs2,
            Client,
            NamespaceName,
            NamePrefix
        );
    }

    Gs2::Core::Domain::CallbackID FNamespaceDomain::SubscribeDashboards(
    TFunction<void()> Callback
    )
    {
        return Gs2->Cache->ListSubscribe(
            Gs2::Log::Model::FDashboard::TypeName,
            Gs2::Log::Model::Cache::FDashboardCache::CreateCacheParentKey(
                NamespaceName,
                TOptional<int32>()
            ),
            Callback,
            Callback
        );
    }
    void FNamespaceDomain::UnsubscribeDashboards(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        Gs2->Cache->ListUnsubscribe(
            Gs2::Log::Model::FDashboard::TypeName,
            Gs2::Log::Model::Cache::FDashboardCache::CreateCacheParentKey(
                NamespaceName,
                TOptional<int32>()
            ),
            CallbackID
        );
    }
    class FNamespaceDomain::FCollectDashboardsTask : public Gs2::Core::Util::TGs2Future<TArray<Gs2::Log::Model::FDashboardPtr>>, public TSharedFromThis<FCollectDashboardsTask>
    {
        const TSharedPtr<FNamespaceDomain> Self;
        const TFunction<void(TArray<Gs2::Log::Model::FDashboardPtr>)> OnCollected;
    const TOptional<FString> QueryNamePrefix;
    public:
        explicit FCollectDashboardsTask(const TSharedPtr<FNamespaceDomain>& Self, TFunction<void(TArray<Gs2::Log::Model::FDashboardPtr>)> OnCollected,const TOptional<FString> NamePrefix) : Self(Self), OnCollected(OnCollected), QueryNamePrefix(NamePrefix) {}
        FCollectDashboardsTask(const FCollectDashboardsTask& From) : TGs2Future(From), Self(From.Self), OnCollected(From.OnCollected), QueryNamePrefix(From.QueryNamePrefix) {}
        virtual Gs2::Core::Model::FGs2ErrorPtr Action(TSharedPtr<TSharedPtr<TArray<Gs2::Log::Model::FDashboardPtr>>> Result) override
        {
            TArray<Gs2::Log::Model::FDashboardPtr> Items;
            auto Iterator = Self->Dashboards(QueryNamePrefix)->begin();
            while (Iterator.HasNext())
            {
                if (Iterator.IsError()) return Iterator.Error();
                if (Iterator.IsCurrentValid()) Items.Add(Iterator.Current());
                ++Iterator;
            }
            if (Iterator.IsError()) return Iterator.Error();
            *Result = MakeShared<TArray<Gs2::Log::Model::FDashboardPtr>>(Items);
            if (OnCollected) OnCollected(Items);
            return nullptr;
        }
    };

    Gs2::Core::Domain::CallbackID FNamespaceDomain::SubscribeDashboards(
        TFunction<void(TArray<Gs2::Log::Model::FDashboardPtr>)> Callback,const TOptional<FString> NamePrefix
    )
    {
        const TWeakPtr<Gs2::Core::Domain::FGs2> WeakGs2 = this->Gs2;
        const TWeakPtr<Log::Domain::FGs2LogDomain> WeakService = this->Service;
        const auto QueryNamespaceName = NamespaceName;
        const auto QueryNamePrefix = NamePrefix;
        const auto Parent = Gs2::Log::Model::Cache::FDashboardCache::CreateCacheParentKey(
        NamespaceName,
        TOptional<int32>()
    );
        return Gs2->Cache->ListSubscribeTyped(
            Gs2::Log::Model::FDashboard::TypeName,
            Parent,
            [Callback, WeakGs2](const TArray<FGs2ObjectPtr>& Values)
            {
                if (!WeakGs2.Pin().IsValid()) return;
                TArray<Gs2::Log::Model::FDashboardPtr> TypedValues;
                for (const auto& Value : Values) if (Value.IsValid()) TypedValues.Add(StaticCastSharedPtr<Gs2::Log::Model::FDashboard>(Value));
                Callback(TypedValues);
            },
            [WeakGs2, WeakService, Callback, QueryNamespaceName, QueryNamePrefix]()
            {
                const auto Owner = WeakGs2.Pin();
                if (!Owner.IsValid()) return;
                const auto Domain = MakeShared<FNamespaceDomain>(Owner, WeakService.Pin(), QueryNamespaceName);
                const auto Task = Gs2::Core::Util::New<FAsyncTask<FCollectDashboardsTask>>(Domain, Callback, QueryNamePrefix);
                Task->StartBackgroundTask();
            }
        );
    }

    void FNamespaceDomain::InvalidateDashboards(const TOptional<FString> NamePrefix)
    {
        Gs2->Cache->ClearListCache(
            Gs2::Log::Model::FDashboard::TypeName,
            Gs2::Log::Model::Cache::FDashboardCache::CreateCacheParentKey(
        NamespaceName,
        TOptional<int32>()
    )
        );
    }

    FNamespaceDomain::FSubscribeDashboardsWithInitialCallTask::FSubscribeDashboardsWithInitialCallTask(const TSharedPtr<FNamespaceDomain>& Self, TFunction<void(TArray<Gs2::Log::Model::FDashboardPtr>)> Callback,const TOptional<FString> NamePrefix) : Self(Self), Callback(Callback), QueryNamePrefix(NamePrefix) {}
    FNamespaceDomain::FSubscribeDashboardsWithInitialCallTask::FSubscribeDashboardsWithInitialCallTask(const FSubscribeDashboardsWithInitialCallTask& From) : TGs2Future(From), Self(From.Self), Callback(From.Callback), QueryNamePrefix(From.QueryNamePrefix) {}
    Gs2::Core::Model::FGs2ErrorPtr FNamespaceDomain::FSubscribeDashboardsWithInitialCallTask::Action(TSharedPtr<TSharedPtr<Gs2::Core::Domain::CallbackID>> Result)
    {
        const auto Task = Gs2::Core::Util::New<FAsyncTask<FCollectDashboardsTask>>(Self, TFunction<void(TArray<Gs2::Log::Model::FDashboardPtr>)>(), QueryNamePrefix);
        Task->StartSynchronousTask(); Task->EnsureCompletion();
        if (Task->GetTask().IsError()) return Task->GetTask().Error();
        const auto Values = Task->GetTask().Result();
        const auto CallbackId = Self->SubscribeDashboards(Callback, QueryNamePrefix);
        Callback(*Values); *Result = MakeShared<Gs2::Core::Domain::CallbackID>(CallbackId);
        return nullptr;
    }
    TSharedPtr<FAsyncTask<FNamespaceDomain::FSubscribeDashboardsWithInitialCallTask>> FNamespaceDomain::SubscribeDashboardsWithInitialCall(TFunction<void(TArray<Gs2::Log::Model::FDashboardPtr>)> Callback,const TOptional<FString> NamePrefix)
    {
        return Gs2::Core::Util::New<FAsyncTask<FSubscribeDashboardsWithInitialCallTask>>(this->AsShared(), Callback, NamePrefix);
    }

    TSharedPtr<Gs2::Log::Domain::Model::FDashboardDomain> FNamespaceDomain::Dashboard(
        const FString DashboardName
    )
    {
        return MakeShared<Gs2::Log::Domain::Model::FDashboardDomain>(
            Gs2,
            Service,
            NamespaceName,
            DashboardName == TEXT("") ? TOptional<FString>() : TOptional<FString>(DashboardName)
        );
    }

    Gs2::Log::Domain::Iterator::FDescribeMetricsIteratorPtr FNamespaceDomain::Metrics(
        const TOptional<FString> NamePrefix
    ) const
    {
        return MakeShared<Gs2::Log::Domain::Iterator::FDescribeMetricsIterator>(
            Gs2,
            Client,
            NamespaceName,
            NamePrefix
        );
    }

    Gs2::Core::Domain::CallbackID FNamespaceDomain::SubscribeMetrics(
    TFunction<void()> Callback
    )
    {
        return Gs2->Cache->ListSubscribe(
            Gs2::Log::Model::FMetricModel::TypeName,
            Gs2::Log::Model::Cache::FMetricModelCache::CreateCacheParentKey(
                NamespaceName,
                TOptional<int32>()
            ),
            Callback,
            Callback
        );
    }
    void FNamespaceDomain::UnsubscribeMetrics(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        Gs2->Cache->ListUnsubscribe(
            Gs2::Log::Model::FMetricModel::TypeName,
            Gs2::Log::Model::Cache::FMetricModelCache::CreateCacheParentKey(
                NamespaceName,
                TOptional<int32>()
            ),
            CallbackID
        );
    }
    class FNamespaceDomain::FCollectMetricsTask : public Gs2::Core::Util::TGs2Future<TArray<Gs2::Log::Model::FMetricModelPtr>>, public TSharedFromThis<FCollectMetricsTask>
    {
        const TSharedPtr<FNamespaceDomain> Self;
        const TFunction<void(TArray<Gs2::Log::Model::FMetricModelPtr>)> OnCollected;
    const TOptional<FString> QueryNamePrefix;
    public:
        explicit FCollectMetricsTask(const TSharedPtr<FNamespaceDomain>& Self, TFunction<void(TArray<Gs2::Log::Model::FMetricModelPtr>)> OnCollected,const TOptional<FString> NamePrefix) : Self(Self), OnCollected(OnCollected), QueryNamePrefix(NamePrefix) {}
        FCollectMetricsTask(const FCollectMetricsTask& From) : TGs2Future(From), Self(From.Self), OnCollected(From.OnCollected), QueryNamePrefix(From.QueryNamePrefix) {}
        virtual Gs2::Core::Model::FGs2ErrorPtr Action(TSharedPtr<TSharedPtr<TArray<Gs2::Log::Model::FMetricModelPtr>>> Result) override
        {
            TArray<Gs2::Log::Model::FMetricModelPtr> Items;
            auto Iterator = Self->Metrics(QueryNamePrefix)->begin();
            while (Iterator.HasNext())
            {
                if (Iterator.IsError()) return Iterator.Error();
                if (Iterator.IsCurrentValid()) Items.Add(Iterator.Current());
                ++Iterator;
            }
            if (Iterator.IsError()) return Iterator.Error();
            *Result = MakeShared<TArray<Gs2::Log::Model::FMetricModelPtr>>(Items);
            if (OnCollected) OnCollected(Items);
            return nullptr;
        }
    };

    Gs2::Core::Domain::CallbackID FNamespaceDomain::SubscribeMetrics(
        TFunction<void(TArray<Gs2::Log::Model::FMetricModelPtr>)> Callback,const TOptional<FString> NamePrefix
    )
    {
        const TWeakPtr<Gs2::Core::Domain::FGs2> WeakGs2 = this->Gs2;
        const TWeakPtr<Log::Domain::FGs2LogDomain> WeakService = this->Service;
        const auto QueryNamespaceName = NamespaceName;
        const auto QueryNamePrefix = NamePrefix;
        const auto Parent = Gs2::Log::Model::Cache::FMetricModelCache::CreateCacheParentKey(
        NamespaceName,
        TOptional<int32>()
    );
        return Gs2->Cache->ListSubscribeTyped(
            Gs2::Log::Model::FMetricModel::TypeName,
            Parent,
            [Callback, WeakGs2](const TArray<FGs2ObjectPtr>& Values)
            {
                if (!WeakGs2.Pin().IsValid()) return;
                TArray<Gs2::Log::Model::FMetricModelPtr> TypedValues;
                for (const auto& Value : Values) if (Value.IsValid()) TypedValues.Add(StaticCastSharedPtr<Gs2::Log::Model::FMetricModel>(Value));
                Callback(TypedValues);
            },
            [WeakGs2, WeakService, Callback, QueryNamespaceName, QueryNamePrefix]()
            {
                const auto Owner = WeakGs2.Pin();
                if (!Owner.IsValid()) return;
                const auto Domain = MakeShared<FNamespaceDomain>(Owner, WeakService.Pin(), QueryNamespaceName);
                const auto Task = Gs2::Core::Util::New<FAsyncTask<FCollectMetricsTask>>(Domain, Callback, QueryNamePrefix);
                Task->StartBackgroundTask();
            }
        );
    }

    void FNamespaceDomain::InvalidateMetrics(const TOptional<FString> NamePrefix)
    {
        Gs2->Cache->ClearListCache(
            Gs2::Log::Model::FMetricModel::TypeName,
            Gs2::Log::Model::Cache::FMetricModelCache::CreateCacheParentKey(
        NamespaceName,
        TOptional<int32>()
    )
        );
    }

    FNamespaceDomain::FSubscribeMetricsWithInitialCallTask::FSubscribeMetricsWithInitialCallTask(const TSharedPtr<FNamespaceDomain>& Self, TFunction<void(TArray<Gs2::Log::Model::FMetricModelPtr>)> Callback,const TOptional<FString> NamePrefix) : Self(Self), Callback(Callback), QueryNamePrefix(NamePrefix) {}
    FNamespaceDomain::FSubscribeMetricsWithInitialCallTask::FSubscribeMetricsWithInitialCallTask(const FSubscribeMetricsWithInitialCallTask& From) : TGs2Future(From), Self(From.Self), Callback(From.Callback), QueryNamePrefix(From.QueryNamePrefix) {}
    Gs2::Core::Model::FGs2ErrorPtr FNamespaceDomain::FSubscribeMetricsWithInitialCallTask::Action(TSharedPtr<TSharedPtr<Gs2::Core::Domain::CallbackID>> Result)
    {
        const auto Task = Gs2::Core::Util::New<FAsyncTask<FCollectMetricsTask>>(Self, TFunction<void(TArray<Gs2::Log::Model::FMetricModelPtr>)>(), QueryNamePrefix);
        Task->StartSynchronousTask(); Task->EnsureCompletion();
        if (Task->GetTask().IsError()) return Task->GetTask().Error();
        const auto Values = Task->GetTask().Result();
        const auto CallbackId = Self->SubscribeMetrics(Callback, QueryNamePrefix);
        Callback(*Values); *Result = MakeShared<Gs2::Core::Domain::CallbackID>(CallbackId);
        return nullptr;
    }
    TSharedPtr<FAsyncTask<FNamespaceDomain::FSubscribeMetricsWithInitialCallTask>> FNamespaceDomain::SubscribeMetricsWithInitialCall(TFunction<void(TArray<Gs2::Log::Model::FMetricModelPtr>)> Callback,const TOptional<FString> NamePrefix)
    {
        return Gs2::Core::Util::New<FAsyncTask<FSubscribeMetricsWithInitialCallTask>>(this->AsShared(), Callback, NamePrefix);
    }

    TSharedPtr<Gs2::Log::Domain::Model::FMetricModelDomain> FNamespaceDomain::MetricModel(
        const FString Name
    )
    {
        return MakeShared<Gs2::Log::Domain::Model::FMetricModelDomain>(
            Gs2,
            Service,
            NamespaceName,
            Name
        );
    }

    Gs2::Log::Domain::Iterator::FDescribeLabelValuesIteratorPtr FNamespaceDomain::LabelValues(
        const FString MetricName,
        const TOptional<FString> LabelNamePrefix
    ) const
    {
        return MakeShared<Gs2::Log::Domain::Iterator::FDescribeLabelValuesIterator>(
            Gs2,
            Client,
            NamespaceName,
            MetricName,
            LabelNamePrefix
        );
    }

    Gs2::Core::Domain::CallbackID FNamespaceDomain::SubscribeLabelValues(
    TFunction<void()> Callback
    )
    {
        return Gs2->Cache->ListSubscribe(
            Gs2::Log::Model::FLabel::TypeName,
            "log:Label",
            Callback,
            Callback
        );
    }
    void FNamespaceDomain::UnsubscribeLabelValues(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        Gs2->Cache->ListUnsubscribe(
            Gs2::Log::Model::FLabel::TypeName,
            "log:Label",
            CallbackID
        );
    }
    class FNamespaceDomain::FCollectLabelValuesTask : public Gs2::Core::Util::TGs2Future<TArray<Gs2::Log::Model::FLabelPtr>>, public TSharedFromThis<FCollectLabelValuesTask>
    {
        const TSharedPtr<FNamespaceDomain> Self;
        const TFunction<void(TArray<Gs2::Log::Model::FLabelPtr>)> OnCollected;
    const FString QueryMetricName;const TOptional<FString> QueryLabelNamePrefix;
    public:
        explicit FCollectLabelValuesTask(const TSharedPtr<FNamespaceDomain>& Self, TFunction<void(TArray<Gs2::Log::Model::FLabelPtr>)> OnCollected,const FString MetricName,const TOptional<FString> LabelNamePrefix) : Self(Self), OnCollected(OnCollected), QueryMetricName(MetricName), QueryLabelNamePrefix(LabelNamePrefix) {}
        FCollectLabelValuesTask(const FCollectLabelValuesTask& From) : TGs2Future(From), Self(From.Self), OnCollected(From.OnCollected), QueryMetricName(From.QueryMetricName), QueryLabelNamePrefix(From.QueryLabelNamePrefix) {}
        virtual Gs2::Core::Model::FGs2ErrorPtr Action(TSharedPtr<TSharedPtr<TArray<Gs2::Log::Model::FLabelPtr>>> Result) override
        {
            TArray<Gs2::Log::Model::FLabelPtr> Items;
            auto Iterator = Self->LabelValues(QueryMetricName, QueryLabelNamePrefix)->begin();
            while (Iterator.HasNext())
            {
                if (Iterator.IsError()) return Iterator.Error();
                if (Iterator.IsCurrentValid()) Items.Add(Iterator.Current());
                ++Iterator;
            }
            if (Iterator.IsError()) return Iterator.Error();
            *Result = MakeShared<TArray<Gs2::Log::Model::FLabelPtr>>(Items);
            if (OnCollected) OnCollected(Items);
            return nullptr;
        }
    };

    Gs2::Core::Domain::CallbackID FNamespaceDomain::SubscribeLabelValues(
        TFunction<void(TArray<Gs2::Log::Model::FLabelPtr>)> Callback,const FString MetricName,const TOptional<FString> LabelNamePrefix
    )
    {
        const TWeakPtr<Gs2::Core::Domain::FGs2> WeakGs2 = this->Gs2;
        const TWeakPtr<Log::Domain::FGs2LogDomain> WeakService = this->Service;
        const auto QueryNamespaceName = NamespaceName;
        const auto QueryMetricName = MetricName;
        const auto QueryLabelNamePrefix = LabelNamePrefix;
        const auto Parent = "log:Label";
        return Gs2->Cache->ListSubscribeTyped(
            Gs2::Log::Model::FLabel::TypeName,
            Parent,
            [Callback, WeakGs2](const TArray<FGs2ObjectPtr>& Values)
            {
                if (!WeakGs2.Pin().IsValid()) return;
                TArray<Gs2::Log::Model::FLabelPtr> TypedValues;
                for (const auto& Value : Values) if (Value.IsValid()) TypedValues.Add(StaticCastSharedPtr<Gs2::Log::Model::FLabel>(Value));
                Callback(TypedValues);
            },
            [WeakGs2, WeakService, Callback, QueryNamespaceName, QueryMetricName, QueryLabelNamePrefix]()
            {
                const auto Owner = WeakGs2.Pin();
                if (!Owner.IsValid()) return;
                const auto Domain = MakeShared<FNamespaceDomain>(Owner, WeakService.Pin(), QueryNamespaceName);
                const auto Task = Gs2::Core::Util::New<FAsyncTask<FCollectLabelValuesTask>>(Domain, Callback, QueryMetricName, QueryLabelNamePrefix);
                Task->StartBackgroundTask();
            }
        );
    }

    void FNamespaceDomain::InvalidateLabelValues(const FString MetricName,const TOptional<FString> LabelNamePrefix)
    {
        Gs2->Cache->ClearListCache(
            Gs2::Log::Model::FLabel::TypeName,
            "log:Label"
        );
    }

    FNamespaceDomain::FSubscribeLabelValuesWithInitialCallTask::FSubscribeLabelValuesWithInitialCallTask(const TSharedPtr<FNamespaceDomain>& Self, TFunction<void(TArray<Gs2::Log::Model::FLabelPtr>)> Callback,const FString MetricName,const TOptional<FString> LabelNamePrefix) : Self(Self), Callback(Callback), QueryMetricName(MetricName), QueryLabelNamePrefix(LabelNamePrefix) {}
    FNamespaceDomain::FSubscribeLabelValuesWithInitialCallTask::FSubscribeLabelValuesWithInitialCallTask(const FSubscribeLabelValuesWithInitialCallTask& From) : TGs2Future(From), Self(From.Self), Callback(From.Callback), QueryMetricName(From.QueryMetricName), QueryLabelNamePrefix(From.QueryLabelNamePrefix) {}
    Gs2::Core::Model::FGs2ErrorPtr FNamespaceDomain::FSubscribeLabelValuesWithInitialCallTask::Action(TSharedPtr<TSharedPtr<Gs2::Core::Domain::CallbackID>> Result)
    {
        const auto Task = Gs2::Core::Util::New<FAsyncTask<FCollectLabelValuesTask>>(Self, TFunction<void(TArray<Gs2::Log::Model::FLabelPtr>)>(), QueryMetricName, QueryLabelNamePrefix);
        Task->StartSynchronousTask(); Task->EnsureCompletion();
        if (Task->GetTask().IsError()) return Task->GetTask().Error();
        const auto Values = Task->GetTask().Result();
        const auto CallbackId = Self->SubscribeLabelValues(Callback, QueryMetricName, QueryLabelNamePrefix);
        Callback(*Values); *Result = MakeShared<Gs2::Core::Domain::CallbackID>(CallbackId);
        return nullptr;
    }
    TSharedPtr<FAsyncTask<FNamespaceDomain::FSubscribeLabelValuesWithInitialCallTask>> FNamespaceDomain::SubscribeLabelValuesWithInitialCall(TFunction<void(TArray<Gs2::Log::Model::FLabelPtr>)> Callback,const FString MetricName,const TOptional<FString> LabelNamePrefix)
    {
        return Gs2::Core::Util::New<FAsyncTask<FSubscribeLabelValuesWithInitialCallTask>>(this->AsShared(), Callback, MetricName, LabelNamePrefix);
    }

    FString FNamespaceDomain::CreateCacheParentKey(
        TOptional<FString> NamespaceName,
        FString ChildType
    )
    {
        return FString("") +
            (NamespaceName.IsSet() ? *NamespaceName : "null") + ":" +
            ChildType;
    }

    FString FNamespaceDomain::CreateCacheKey(
        TOptional<FString> NamespaceName
    )
    {
        return FString("") +
            (NamespaceName.IsSet() ? *NamespaceName : "null");
    }

    FNamespaceDomain::FModelTask::FModelTask(
        const TSharedPtr<FNamespaceDomain> Self
    ): Self(Self)
    {

    }

    FNamespaceDomain::FModelTask::FModelTask(
        const FModelTask& From
    ): TGs2Future(From), Self(From.Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FNamespaceDomain::FModelTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Log::Model::FNamespace>> Result
    )
    {
        const auto ParentKey = FString("log:Namespace");
        const FString CacheKey = Gs2::Log::Domain::Model::FNamespaceDomain::CreateCacheKey(
            Self->NamespaceName
        );
        return Self->Gs2->Cache->ExecuteWithKeyLock(
            Gs2::Log::Model::FNamespace::TypeName,
            ParentKey,
            CacheKey,
            [this, Result, CacheKey, ParentKey]() -> Gs2::Core::Model::FGs2ErrorPtr
            {
                // ReSharper disable once CppLocalVariableMayBeConst
                TSharedPtr<Gs2::Log::Model::FNamespace> Value;
                auto bCacheHit = Self->Gs2->Cache->TryGet<Gs2::Log::Model::FNamespace>(
                    ParentKey,
                    CacheKey,
                    &Value
                );
                if (!bCacheHit) {
                    const auto Future = Self->Get(
                        MakeShared<Gs2::Log::Request::FGetNamespaceRequest>()
                    );
                    Future->StartSynchronousTask();
                    if (Future->GetTask().IsError())
                    {
                        const auto Error = Future->GetTask().Error();
                        if (!Error.IsValid() || Error->Type() != Gs2::Core::Model::FNotFoundError::TypeString)
                        {
                            return Error;
                        }
                        Self->Gs2->Cache->Put(
                            Gs2::Log::Model::FNamespace::TypeName,
                            ParentKey,
                            CacheKey,
                            nullptr,
                            FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                        );

                        if (!Error->GetErrors().IsValid() || Error->Count() == 0 || !Error->Detail(0).IsValid() || Error->Detail(0)->GetComponent() != "namespace")
                        {
                            return Error;
                        }
                    }
                    else
                    {
                        Value = Future->GetTask().Result();
                    }
                    Future->EnsureCompletion();
                }
                if (!bCacheHit)
                {
                    FGs2ObjectPtr ExistingObject;
                    const bool Existing = Self->Gs2->Cache->TryGet(
                        Gs2::Log::Model::FNamespace::TypeName,
                        ParentKey,
                        CacheKey,
                        &ExistingObject
                    );
                    if (!Existing || ExistingObject != Value)
                    {
                        Self->Gs2->Cache->Put(
                            Gs2::Log::Model::FNamespace::TypeName,
                            ParentKey,
                            CacheKey,
                            Value,
                            FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                        );
                    }
                }

                *Result = Value;

                return nullptr;
            }
        );
    }

    TSharedPtr<FAsyncTask<FNamespaceDomain::FModelTask>> FNamespaceDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FNamespaceDomain::FModelTask>>(this->AsShared());
    }

    Gs2::Core::Domain::CallbackID FNamespaceDomain::Subscribe(
        TFunction<void(Gs2::Log::Model::FNamespacePtr)> Callback
    )
    {
        const TWeakPtr<Gs2::Core::Domain::FGs2> WeakGs2 = Gs2;
        const TWeakPtr<Log::Domain::FGs2LogDomain> WeakService = Service;
        const FString RegisteredParentKey = ParentKey;
        const TOptional<FString> QueryNamespaceName = NamespaceName;

        return Gs2->Cache->Subscribe(
            Gs2::Log::Model::FNamespace::TypeName,
            ParentKey,
            Gs2::Log::Domain::Model::FNamespaceDomain::CreateCacheKey(
                NamespaceName
            ),
            [Callback](TSharedPtr<FGs2Object> obj)
            {
                Callback(StaticCastSharedPtr<Gs2::Log::Model::FNamespace>(obj));
            },
            [WeakGs2, WeakService, RegisteredParentKey, QueryNamespaceName]()
            {
                const auto Owner = WeakGs2.Pin();
                if (!Owner.IsValid())
                {
                    return;
                }
                const auto Domain = MakeShared<FNamespaceDomain>(
                    Owner,
                    WeakService.Pin(),
                    QueryNamespaceName
                );
                Domain->ParentKey = RegisteredParentKey;
                const auto Task = Domain->Model();
                Task->StartBackgroundTask();
            }
        );
    }

    void FNamespaceDomain::Unsubscribe(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        Gs2->Cache->Unsubscribe(
            Gs2::Log::Model::FNamespace::TypeName,
            ParentKey,
            Gs2::Log::Domain::Model::FNamespaceDomain::CreateCacheKey(
                NamespaceName
            ),
            CallbackID
        );
    }


    Gs2::Core::Domain::CallbackID FNamespaceDomain::SubscribeInGameLog(TFunction<void()> Callback){return Gs2->Cache->ListSubscribe(Gs2::Log::Model::FInGameLog::TypeName,Gs2::Log::Model::Cache::FInGameLogCache::CreateCacheParentKey(NamespaceName,TOptional<FString>(),TOptional<int32>()),Callback,Callback);}
    void FNamespaceDomain::UnsubscribeInGameLog(Gs2::Core::Domain::CallbackID CallbackID){Gs2->Cache->ListUnsubscribe(Gs2::Log::Model::FInGameLog::TypeName,Gs2::Log::Model::Cache::FInGameLogCache::CreateCacheParentKey(NamespaceName,TOptional<FString>(),TOptional<int32>()),CallbackID);}
    class FNamespaceDomain::FCollectInGameLogTask:public Gs2::Core::Util::TGs2Future<TArray<Gs2::Log::Model::FInGameLogPtr>>,public TSharedFromThis<FCollectInGameLogTask>{const TSharedPtr<FNamespaceDomain> Self;const TFunction<void(TArray<Gs2::Log::Model::FInGameLogPtr>)> OnCollected;const TOptional<FString> QueryUserId;const TSharedPtr<TArray<TSharedPtr<Gs2::Log::Model::FInGameLogTag>>> QueryTags;const TOptional<int64> QueryBegin;const TOptional<int64> QueryEnd;const TOptional<bool> QueryLongTerm;public:FCollectInGameLogTask(const TSharedPtr<FNamespaceDomain>& Self,TFunction<void(TArray<Gs2::Log::Model::FInGameLogPtr>)> OnCollected,const TOptional<FString> UserId=TOptional<FString>(),const TSharedPtr<TArray<TSharedPtr<Gs2::Log::Model::FInGameLogTag>>> Tags=nullptr,const TOptional<int64> Begin=TOptional<int64>(),const TOptional<int64> End=TOptional<int64>(),const TOptional<bool> LongTerm=TOptional<bool>()):Self(Self),OnCollected(OnCollected),QueryUserId(UserId),QueryTags(Tags),QueryBegin(Begin),QueryEnd(End),QueryLongTerm(LongTerm){}FCollectInGameLogTask(const FCollectInGameLogTask& From):TGs2Future(From),Self(From.Self),OnCollected(From.OnCollected),QueryUserId(From.QueryUserId),QueryTags(From.QueryTags),QueryBegin(From.QueryBegin),QueryEnd(From.QueryEnd),QueryLongTerm(From.QueryLongTerm){}Gs2::Core::Model::FGs2ErrorPtr Action(TSharedPtr<TSharedPtr<TArray<Gs2::Log::Model::FInGameLogPtr>>> Result)override{TArray<Gs2::Log::Model::FInGameLogPtr> Items;auto It=Self->InGameLog(QueryUserId,QueryTags,QueryBegin,QueryEnd,QueryLongTerm)->begin();while(It.HasNext()){if(It.IsError())return It.Error();if(It.IsCurrentValid())Items.Add(It.Current());++It;}if(It.IsError())return It.Error();*Result=MakeShared<TArray<Gs2::Log::Model::FInGameLogPtr>>(Items);if(OnCollected)OnCollected(Items);return nullptr;}};
    Gs2::Core::Domain::CallbackID FNamespaceDomain::SubscribeInGameLog(TFunction<void(TArray<Gs2::Log::Model::FInGameLogPtr>)> Callback){const TWeakPtr<Gs2::Core::Domain::FGs2> WeakGs2=Gs2;const TWeakPtr<Log::Domain::FGs2LogDomain> WeakService=Service;const auto QN=NamespaceName;const auto Parent=Gs2::Log::Model::Cache::FInGameLogCache::CreateCacheParentKey(NamespaceName,TOptional<FString>(),TOptional<int32>());return Gs2->Cache->ListSubscribeTyped(Gs2::Log::Model::FInGameLog::TypeName,Parent,[Callback,WeakGs2](const TArray<FGs2ObjectPtr>& Values){if(!WeakGs2.Pin().IsValid())return;TArray<Gs2::Log::Model::FInGameLogPtr> Out;for(const auto& V:Values)if(V.IsValid())Out.Add(StaticCastSharedPtr<Gs2::Log::Model::FInGameLog>(V));Callback(Out);},[WeakGs2,WeakService,Callback,QN](){auto O=WeakGs2.Pin();if(!O.IsValid())return;auto D=MakeShared<FNamespaceDomain>(O,WeakService.Pin(),QN);auto T=Gs2::Core::Util::New<FAsyncTask<FCollectInGameLogTask>>(D,Callback);T->StartBackgroundTask();});}
    FNamespaceDomain::FSubscribeInGameLogWithInitialCallTask::FSubscribeInGameLogWithInitialCallTask(const TSharedPtr<FNamespaceDomain>& Self,TFunction<void(TArray<Gs2::Log::Model::FInGameLogPtr>)> Callback,const TOptional<FString> UserId,const TSharedPtr<TArray<TSharedPtr<Gs2::Log::Model::FInGameLogTag>>> Tags,const TOptional<int64> Begin,const TOptional<int64> End,const TOptional<bool> LongTerm):Self(Self),Callback(Callback),QueryUserId(UserId),QueryTags(Tags),QueryBegin(Begin),QueryEnd(End),QueryLongTerm(LongTerm){}
    FNamespaceDomain::FSubscribeInGameLogWithInitialCallTask::FSubscribeInGameLogWithInitialCallTask(const FSubscribeInGameLogWithInitialCallTask& From):TGs2Future(From),Self(From.Self),Callback(From.Callback),QueryUserId(From.QueryUserId),QueryTags(From.QueryTags),QueryBegin(From.QueryBegin),QueryEnd(From.QueryEnd),QueryLongTerm(From.QueryLongTerm){}
    Gs2::Core::Model::FGs2ErrorPtr FNamespaceDomain::FSubscribeInGameLogWithInitialCallTask::Action(TSharedPtr<TSharedPtr<Gs2::Core::Domain::CallbackID>> Result){auto T=Gs2::Core::Util::New<FAsyncTask<FCollectInGameLogTask>>(Self,TFunction<void(TArray<Gs2::Log::Model::FInGameLogPtr>)>(),QueryUserId,QueryTags,QueryBegin,QueryEnd,QueryLongTerm);T->StartSynchronousTask();T->EnsureCompletion();if(T->GetTask().IsError())return T->GetTask().Error();auto V=T->GetTask().Result();auto ID=Self->SubscribeInGameLog(Callback);Callback(*V);*Result=MakeShared<Gs2::Core::Domain::CallbackID>(ID);return nullptr;}
    TSharedPtr<FAsyncTask<FNamespaceDomain::FSubscribeInGameLogWithInitialCallTask>> FNamespaceDomain::SubscribeInGameLogWithInitialCall(TFunction<void(TArray<Gs2::Log::Model::FInGameLogPtr>)> Callback,const TOptional<FString> UserId,const TSharedPtr<TArray<TSharedPtr<Gs2::Log::Model::FInGameLogTag>>> Tags,const TOptional<int64> Begin,const TOptional<int64> End,const TOptional<bool> LongTerm){return Gs2::Core::Util::New<FAsyncTask<FSubscribeInGameLogWithInitialCallTask>>(this->AsShared(),Callback,UserId,Tags,Begin,End,LongTerm);}

    Gs2::Log::Domain::Iterator::FQueryInGameLogIteratorPtr FNamespaceDomain::InGameLog(
        const TOptional<FString> UserId,
        const TSharedPtr<TArray<TSharedPtr<Gs2::Log::Model::FInGameLogTag>>> Tags,
        const TOptional<int64> Begin,
        const TOptional<int64> End,
        const TOptional<bool> LongTerm,
        const TOptional<FString> TimeOffsetToken
    ) const
    {
        auto* Self = const_cast<FNamespaceDomain*>(this);
        return MakeShared<Gs2::Log::Domain::Iterator::FQueryInGameLogIterator>(
            Gs2,
            Client,
            NamespaceName,
            UserId,
            Tags,
            Begin,
            End,
            LongTerm,
            TimeOffsetToken,
            [Self](TOptional<int64> Count) { Self->TotalCount = Count; }
        );
    }

}

#if defined(_MSC_VER)
#pragma warning (pop)
#elif defined(__clang__)
#pragma clang diagnostic pop
#endif
