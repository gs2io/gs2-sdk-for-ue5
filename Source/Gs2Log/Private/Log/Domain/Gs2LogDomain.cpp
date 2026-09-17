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

// ReSharper disable CppUnusedIncludeDirective

#include "Log/Domain/Gs2Log.h"
#include "Log/Domain/Model/Namespace.h"
#include "Log/Domain/Model/AccessLog.h"
#include "Log/Domain/Model/IssueStampSheetLog.h"
#include "Log/Domain/Model/ExecuteStampSheetLog.h"
#include "Log/Domain/Model/ExecuteStampTaskLog.h"
#include "Log/Domain/Model/InGameLog.h"
#include "Log/Domain/Model/AccessLogWithTelemetry.h"
#include "Log/Domain/Model/User.h"
#include "Log/Domain/Model/UserAccessToken.h"
#include "Log/Domain/Model/Insight.h"
#include "Log/Domain/Model/FacetModel.h"
#include "Log/Domain/Model/Dashboard.h"
#include "Log/Domain/Model/LogEntry.h"
#include "Log/Domain/Model/MetricModel.h"

#include "Log/Model/Cache/Namespace.h"
#include "Log/Model/Cache/Insight.h"
#include "Log/Model/Cache/Dashboard.h"
#include "Log/Model/Cache/MetricModel.h"
#include "Log/Model/Cache/InGameLog.h"
#include "Log/Model/Cache/FacetModel.h"
#include "Log/Model/Cache/LogEntry.h"

#include "Core/Domain/Gs2.h"

namespace Gs2::Log::Domain
{

    FGs2LogDomain::FGs2LogDomain(
        const Core::Domain::FGs2Ptr& Gs2
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Gs2(Gs2),
        Client(MakeShared<Gs2::Log::FGs2LogRestClient>(Gs2->RestSession)),
        ParentKey("log")
    {
    }

    FGs2LogDomain::FGs2LogDomain(
        const FGs2LogDomain& From
    ):
        Gs2(From.Gs2),
        Client(From.Client),
        ParentKey(From.ParentKey)
    {

    }

    FGs2LogDomain::FCreateNamespaceTask::FCreateNamespaceTask(
        const TSharedPtr<FGs2LogDomain>& Self,
        const Request::FCreateNamespaceRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FGs2LogDomain::FCreateNamespaceTask::FCreateNamespaceTask(
        const FCreateNamespaceTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FGs2LogDomain::FCreateNamespaceTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Log::Domain::Model::FNamespaceDomain>> Result
    )
    {
        const auto Future = Self->Client->CreateNamespace(
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


        Gs2::Log::Model::Cache::FNamespaceCache::Put(
            Self->Gs2->Cache,

            ResultModel->GetItem()->GetName(),
            TOptional<int32>(),
            ResultModel->GetItem()
        );
            }
        auto Domain = MakeShared<Gs2::Log::Domain::Model::FNamespaceDomain>(
            Self->Gs2,
            Self,
            ResultModel->GetItem()->GetName()
        );
        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FGs2LogDomain::FCreateNamespaceTask>> FGs2LogDomain::CreateNamespace(
        Request::FCreateNamespaceRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FCreateNamespaceTask>>(this->AsShared(), Request);
    }

    Gs2::Log::Domain::Iterator::FDescribeNamespacesIteratorPtr FGs2LogDomain::Namespaces(
    ) const
    {
        return MakeShared<Gs2::Log::Domain::Iterator::FDescribeNamespacesIterator>(
            Gs2,
            Client
        );
    }

    Gs2::Core::Domain::CallbackID FGs2LogDomain::SubscribeNamespaces(
    TFunction<void()> Callback

    )
    {
        return Gs2->Cache->ListSubscribe(
            Gs2::Log::Model::FNamespace::TypeName,
            Gs2::Log::Model::Cache::FNamespaceCache::CreateCacheParentKey(
                TOptional<int32>()
            ),
            Callback,
            Callback
        );
    }
    void FGs2LogDomain::UnsubscribeNamespaces(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        Gs2->Cache->ListUnsubscribe(
            Gs2::Log::Model::FNamespace::TypeName,
            Gs2::Log::Model::Cache::FNamespaceCache::CreateCacheParentKey(
                TOptional<int32>()
            ),
            CallbackID
        );
    }
    class FGs2LogDomain::FCollectNamespacesTask : public Gs2::Core::Util::TGs2Future<TArray<Gs2::Log::Model::FNamespacePtr>>, public TSharedFromThis<FCollectNamespacesTask>
    {
        const TSharedPtr<FGs2LogDomain> Self;
        const TFunction<void(TArray<Gs2::Log::Model::FNamespacePtr>)> OnCollected;

    public:
        explicit FCollectNamespacesTask(const TSharedPtr<FGs2LogDomain>& Self, TFunction<void(TArray<Gs2::Log::Model::FNamespacePtr>)> OnCollected) : Self(Self), OnCollected(OnCollected) {}
        FCollectNamespacesTask(const FCollectNamespacesTask& From) : TGs2Future(From), Self(From.Self), OnCollected(From.OnCollected) {}
        virtual Gs2::Core::Model::FGs2ErrorPtr Action(TSharedPtr<TSharedPtr<TArray<Gs2::Log::Model::FNamespacePtr>>> Result) override
        {
            TArray<Gs2::Log::Model::FNamespacePtr> Items;
            auto Iterator = Self->Namespaces()->begin();
            while (Iterator.HasNext())
            {
                if (Iterator.IsError()) return Iterator.Error();
                if (Iterator.IsCurrentValid()) Items.Add(Iterator.Current());
                ++Iterator;
            }
            if (Iterator.IsError()) return Iterator.Error();
            *Result = MakeShared<TArray<Gs2::Log::Model::FNamespacePtr>>(Items);
            if (OnCollected) OnCollected(Items);
            return nullptr;
        }
    };

    Gs2::Core::Domain::CallbackID FGs2LogDomain::SubscribeNamespaces(
        TFunction<void(TArray<Gs2::Log::Model::FNamespacePtr>)> Callback
    )
    {
        const TWeakPtr<Gs2::Core::Domain::FGs2> WeakGs2 = this->Gs2;
        const auto Parent = Gs2::Log::Model::Cache::FNamespaceCache::CreateCacheParentKey(
        TOptional<int32>()
    );
        return Gs2->Cache->ListSubscribeTyped(
            Gs2::Log::Model::FNamespace::TypeName,
            Parent,
            [Callback, WeakGs2](const TArray<FGs2ObjectPtr>& Values)
            {
                if (!WeakGs2.Pin().IsValid()) return;
                TArray<Gs2::Log::Model::FNamespacePtr> TypedValues;
                for (const auto& Value : Values) if (Value.IsValid()) TypedValues.Add(StaticCastSharedPtr<Gs2::Log::Model::FNamespace>(Value));
                Callback(TypedValues);
            },
            [WeakGs2, Callback]()
            {
                const auto Owner = WeakGs2.Pin();
                if (!Owner.IsValid()) return;
                const auto Domain = MakeShared<FGs2LogDomain>(Owner);
                const auto Task = Gs2::Core::Util::New<FAsyncTask<FCollectNamespacesTask>>(Domain, Callback);
                Task->StartBackgroundTask();
            }
        );
    }

    void FGs2LogDomain::InvalidateNamespaces()
    {
        Gs2->Cache->ClearListCache(
            Gs2::Log::Model::FNamespace::TypeName,
            Gs2::Log::Model::Cache::FNamespaceCache::CreateCacheParentKey(
        TOptional<int32>()
    )
        );
    }

    FGs2LogDomain::FSubscribeNamespacesWithInitialCallTask::FSubscribeNamespacesWithInitialCallTask(const TSharedPtr<FGs2LogDomain>& Self, TFunction<void(TArray<Gs2::Log::Model::FNamespacePtr>)> Callback) : Self(Self), Callback(Callback) {}
    FGs2LogDomain::FSubscribeNamespacesWithInitialCallTask::FSubscribeNamespacesWithInitialCallTask(const FSubscribeNamespacesWithInitialCallTask& From) : TGs2Future(From), Self(From.Self), Callback(From.Callback) {}
    Gs2::Core::Model::FGs2ErrorPtr FGs2LogDomain::FSubscribeNamespacesWithInitialCallTask::Action(TSharedPtr<TSharedPtr<Gs2::Core::Domain::CallbackID>> Result)
    {
        const auto Task = Gs2::Core::Util::New<FAsyncTask<FCollectNamespacesTask>>(Self, TFunction<void(TArray<Gs2::Log::Model::FNamespacePtr>)>());
        Task->StartSynchronousTask(); Task->EnsureCompletion();
        if (Task->GetTask().IsError()) return Task->GetTask().Error();
        const auto Values = Task->GetTask().Result();
        const auto CallbackId = Self->SubscribeNamespaces(Callback);
        Callback(*Values); *Result = MakeShared<Gs2::Core::Domain::CallbackID>(CallbackId);
        return nullptr;
    }
    TSharedPtr<FAsyncTask<FGs2LogDomain::FSubscribeNamespacesWithInitialCallTask>> FGs2LogDomain::SubscribeNamespacesWithInitialCall(TFunction<void(TArray<Gs2::Log::Model::FNamespacePtr>)> Callback)
    {
        return Gs2::Core::Util::New<FAsyncTask<FSubscribeNamespacesWithInitialCallTask>>(this->AsShared(), Callback);
    }

    TSharedPtr<Gs2::Log::Domain::Model::FNamespaceDomain> FGs2LogDomain::Namespace(
        const FString NamespaceName
    )
    {
        return MakeShared<Gs2::Log::Domain::Model::FNamespaceDomain>(
            Gs2,
            AsShared(),
            NamespaceName == TEXT("") ? TOptional<FString>() : TOptional<FString>(NamespaceName)
        );
    }

    Gs2::Log::Domain::Iterator::FQueryLogIteratorPtr FGs2LogDomain::Log(
        const FString NamespaceName,
        const TOptional<int64> Begin,
        const TOptional<int64> End,
        const TOptional<FString> Query
    ) const
    {
        return MakeShared<Gs2::Log::Domain::Iterator::FQueryLogIterator>(
            Gs2,
            Client,
            NamespaceName,
            Begin,
            End,
            Query
        );
    }

    Gs2::Core::Domain::CallbackID FGs2LogDomain::SubscribeLog(
    TFunction<void()> Callback

    )
    {
        return Gs2->Cache->ListSubscribe(
            Gs2::Log::Model::FLogEntry::TypeName,
            Gs2::Log::Model::Cache::FLogEntryCache::CreateCacheParentKey(
                TOptional<int32>()
            ),
            Callback,
            Callback
        );
    }
    void FGs2LogDomain::UnsubscribeLog(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        Gs2->Cache->ListUnsubscribe(
            Gs2::Log::Model::FLogEntry::TypeName,
            Gs2::Log::Model::Cache::FLogEntryCache::CreateCacheParentKey(
                TOptional<int32>()
            ),
            CallbackID
        );
    }
    class FGs2LogDomain::FCollectLogTask : public Gs2::Core::Util::TGs2Future<TArray<Gs2::Log::Model::FLogEntryPtr>>, public TSharedFromThis<FCollectLogTask>
    {
        const TSharedPtr<FGs2LogDomain> Self;
        const TFunction<void(TArray<Gs2::Log::Model::FLogEntryPtr>)> OnCollected;
    const FString QueryNamespaceName;const TOptional<int64> QueryBegin;const TOptional<int64> QueryEnd;const TOptional<FString> QueryQuery;
    public:
        explicit FCollectLogTask(const TSharedPtr<FGs2LogDomain>& Self, TFunction<void(TArray<Gs2::Log::Model::FLogEntryPtr>)> OnCollected,const FString NamespaceName,const TOptional<int64> Begin,const TOptional<int64> End,const TOptional<FString> Query) : Self(Self), OnCollected(OnCollected), QueryNamespaceName(NamespaceName), QueryBegin(Begin), QueryEnd(End), QueryQuery(Query) {}
        FCollectLogTask(const FCollectLogTask& From) : TGs2Future(From), Self(From.Self), OnCollected(From.OnCollected), QueryNamespaceName(From.QueryNamespaceName), QueryBegin(From.QueryBegin), QueryEnd(From.QueryEnd), QueryQuery(From.QueryQuery) {}
        virtual Gs2::Core::Model::FGs2ErrorPtr Action(TSharedPtr<TSharedPtr<TArray<Gs2::Log::Model::FLogEntryPtr>>> Result) override
        {
            TArray<Gs2::Log::Model::FLogEntryPtr> Items;
            auto Iterator = Self->Log(QueryNamespaceName, QueryBegin, QueryEnd, QueryQuery)->begin();
            while (Iterator.HasNext())
            {
                if (Iterator.IsError()) return Iterator.Error();
                if (Iterator.IsCurrentValid()) Items.Add(Iterator.Current());
                ++Iterator;
            }
            if (Iterator.IsError()) return Iterator.Error();
            *Result = MakeShared<TArray<Gs2::Log::Model::FLogEntryPtr>>(Items);
            if (OnCollected) OnCollected(Items);
            return nullptr;
        }
    };

    Gs2::Core::Domain::CallbackID FGs2LogDomain::SubscribeLog(
        TFunction<void(TArray<Gs2::Log::Model::FLogEntryPtr>)> Callback,const FString NamespaceName,const TOptional<int64> Begin,const TOptional<int64> End,const TOptional<FString> Query
    )
    {
        const TWeakPtr<Gs2::Core::Domain::FGs2> WeakGs2 = this->Gs2;
        const auto QueryNamespaceName = NamespaceName;
        const auto QueryBegin = Begin;
        const auto QueryEnd = End;
        const auto QueryQuery = Query;
        const auto Parent = Gs2::Log::Model::Cache::FLogEntryCache::CreateCacheParentKey(
        TOptional<int32>()
    );
        return Gs2->Cache->ListSubscribeTyped(
            Gs2::Log::Model::FLogEntry::TypeName,
            Parent,
            [Callback, WeakGs2](const TArray<FGs2ObjectPtr>& Values)
            {
                if (!WeakGs2.Pin().IsValid()) return;
                TArray<Gs2::Log::Model::FLogEntryPtr> TypedValues;
                for (const auto& Value : Values) if (Value.IsValid()) TypedValues.Add(StaticCastSharedPtr<Gs2::Log::Model::FLogEntry>(Value));
                Callback(TypedValues);
            },
            [WeakGs2, Callback, QueryNamespaceName, QueryBegin, QueryEnd, QueryQuery]()
            {
                const auto Owner = WeakGs2.Pin();
                if (!Owner.IsValid()) return;
                const auto Domain = MakeShared<FGs2LogDomain>(Owner);
                const auto Task = Gs2::Core::Util::New<FAsyncTask<FCollectLogTask>>(Domain, Callback, QueryNamespaceName, QueryBegin, QueryEnd, QueryQuery);
                Task->StartBackgroundTask();
            }
        );
    }

    void FGs2LogDomain::InvalidateLog(const FString NamespaceName,const TOptional<int64> Begin,const TOptional<int64> End,const TOptional<FString> Query)
    {
        Gs2->Cache->ClearListCache(
            Gs2::Log::Model::FLogEntry::TypeName,
            Gs2::Log::Model::Cache::FLogEntryCache::CreateCacheParentKey(
        TOptional<int32>()
    )
        );
    }

    FGs2LogDomain::FSubscribeLogWithInitialCallTask::FSubscribeLogWithInitialCallTask(const TSharedPtr<FGs2LogDomain>& Self, TFunction<void(TArray<Gs2::Log::Model::FLogEntryPtr>)> Callback,const FString NamespaceName,const TOptional<int64> Begin,const TOptional<int64> End,const TOptional<FString> Query) : Self(Self), Callback(Callback), QueryNamespaceName(NamespaceName), QueryBegin(Begin), QueryEnd(End), QueryQuery(Query) {}
    FGs2LogDomain::FSubscribeLogWithInitialCallTask::FSubscribeLogWithInitialCallTask(const FSubscribeLogWithInitialCallTask& From) : TGs2Future(From), Self(From.Self), Callback(From.Callback), QueryNamespaceName(From.QueryNamespaceName), QueryBegin(From.QueryBegin), QueryEnd(From.QueryEnd), QueryQuery(From.QueryQuery) {}
    Gs2::Core::Model::FGs2ErrorPtr FGs2LogDomain::FSubscribeLogWithInitialCallTask::Action(TSharedPtr<TSharedPtr<Gs2::Core::Domain::CallbackID>> Result)
    {
        const auto Task = Gs2::Core::Util::New<FAsyncTask<FCollectLogTask>>(Self, TFunction<void(TArray<Gs2::Log::Model::FLogEntryPtr>)>(), QueryNamespaceName, QueryBegin, QueryEnd, QueryQuery);
        Task->StartSynchronousTask(); Task->EnsureCompletion();
        if (Task->GetTask().IsError()) return Task->GetTask().Error();
        const auto Values = Task->GetTask().Result();
        const auto CallbackId = Self->SubscribeLog(Callback, QueryNamespaceName, QueryBegin, QueryEnd, QueryQuery);
        Callback(*Values); *Result = MakeShared<Gs2::Core::Domain::CallbackID>(CallbackId);
        return nullptr;
    }
    TSharedPtr<FAsyncTask<FGs2LogDomain::FSubscribeLogWithInitialCallTask>> FGs2LogDomain::SubscribeLogWithInitialCall(TFunction<void(TArray<Gs2::Log::Model::FLogEntryPtr>)> Callback,const FString NamespaceName,const TOptional<int64> Begin,const TOptional<int64> End,const TOptional<FString> Query)
    {
        return Gs2::Core::Util::New<FAsyncTask<FSubscribeLogWithInitialCallTask>>(this->AsShared(), Callback, NamespaceName, Begin, End, Query);
    }

    Gs2::Log::Domain::Iterator::FQueryTimeseriesIteratorPtr FGs2LogDomain::Timeseries(
        const FString NamespaceName,
        const TSharedPtr<Gs2::Log::Model::FAggregationConfig> Aggregation,
        const TOptional<int64> Begin,
        const TOptional<int64> End,
        const TOptional<FString> Query,
        const TSharedPtr<TArray<FString>> GroupBy,
        const TOptional<int32> Interval,
        const TOptional<int32> SeriesLimit
    ) const
    {
        return MakeShared<Gs2::Log::Domain::Iterator::FQueryTimeseriesIterator>(
            Gs2,
            Client,
            NamespaceName,
            Aggregation,
            Begin,
            End,
            Query,
            GroupBy,
            Interval,
            SeriesLimit
        );
    }

    Gs2::Core::Domain::CallbackID FGs2LogDomain::SubscribeTimeseries(
    TFunction<void()> Callback

    )
    {
        return Gs2->Cache->ListSubscribe(
            Gs2::Log::Model::FTimeseriesPoint::TypeName,
            "log:TimeseriesPoint",
            Callback,
            Callback
        );
    }
    void FGs2LogDomain::UnsubscribeTimeseries(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        Gs2->Cache->ListUnsubscribe(
            Gs2::Log::Model::FTimeseriesPoint::TypeName,
            "log:TimeseriesPoint",
            CallbackID
        );
    }
    class FGs2LogDomain::FCollectTimeseriesTask : public Gs2::Core::Util::TGs2Future<TArray<Gs2::Log::Model::FTimeseriesPointPtr>>, public TSharedFromThis<FCollectTimeseriesTask>
    {
        const TSharedPtr<FGs2LogDomain> Self;
        const TFunction<void(TArray<Gs2::Log::Model::FTimeseriesPointPtr>)> OnCollected;
    const FString QueryNamespaceName;const TSharedPtr<Gs2::Log::Model::FAggregationConfig> QueryAggregation;const TOptional<int64> QueryBegin;const TOptional<int64> QueryEnd;const TOptional<FString> QueryQuery;const TSharedPtr<TArray<FString>> QueryGroupBy;const TOptional<int32> QueryInterval;const TOptional<int32> QuerySeriesLimit;
    public:
        explicit FCollectTimeseriesTask(const TSharedPtr<FGs2LogDomain>& Self, TFunction<void(TArray<Gs2::Log::Model::FTimeseriesPointPtr>)> OnCollected,const FString NamespaceName,const TSharedPtr<Gs2::Log::Model::FAggregationConfig> Aggregation,const TOptional<int64> Begin,const TOptional<int64> End,const TOptional<FString> Query,const TSharedPtr<TArray<FString>> GroupBy,const TOptional<int32> Interval,const TOptional<int32> SeriesLimit) : Self(Self), OnCollected(OnCollected), QueryNamespaceName(NamespaceName), QueryAggregation(Aggregation), QueryBegin(Begin), QueryEnd(End), QueryQuery(Query), QueryGroupBy(GroupBy), QueryInterval(Interval), QuerySeriesLimit(SeriesLimit) {}
        FCollectTimeseriesTask(const FCollectTimeseriesTask& From) : TGs2Future(From), Self(From.Self), OnCollected(From.OnCollected), QueryNamespaceName(From.QueryNamespaceName), QueryAggregation(From.QueryAggregation), QueryBegin(From.QueryBegin), QueryEnd(From.QueryEnd), QueryQuery(From.QueryQuery), QueryGroupBy(From.QueryGroupBy), QueryInterval(From.QueryInterval), QuerySeriesLimit(From.QuerySeriesLimit) {}
        virtual Gs2::Core::Model::FGs2ErrorPtr Action(TSharedPtr<TSharedPtr<TArray<Gs2::Log::Model::FTimeseriesPointPtr>>> Result) override
        {
            TArray<Gs2::Log::Model::FTimeseriesPointPtr> Items;
            auto Iterator = Self->Timeseries(QueryNamespaceName, QueryAggregation, QueryBegin, QueryEnd, QueryQuery, QueryGroupBy, QueryInterval, QuerySeriesLimit)->begin();
            while (Iterator.HasNext())
            {
                if (Iterator.IsError()) return Iterator.Error();
                if (Iterator.IsCurrentValid()) Items.Add(Iterator.Current());
                ++Iterator;
            }
            if (Iterator.IsError()) return Iterator.Error();
            *Result = MakeShared<TArray<Gs2::Log::Model::FTimeseriesPointPtr>>(Items);
            if (OnCollected) OnCollected(Items);
            return nullptr;
        }
    };

    Gs2::Core::Domain::CallbackID FGs2LogDomain::SubscribeTimeseries(
        TFunction<void(TArray<Gs2::Log::Model::FTimeseriesPointPtr>)> Callback,const FString NamespaceName,const TSharedPtr<Gs2::Log::Model::FAggregationConfig> Aggregation,const TOptional<int64> Begin,const TOptional<int64> End,const TOptional<FString> Query,const TSharedPtr<TArray<FString>> GroupBy,const TOptional<int32> Interval,const TOptional<int32> SeriesLimit
    )
    {
        const TWeakPtr<Gs2::Core::Domain::FGs2> WeakGs2 = this->Gs2;
        const auto QueryNamespaceName = NamespaceName;
        const auto QueryAggregation = Aggregation;
        const auto QueryBegin = Begin;
        const auto QueryEnd = End;
        const auto QueryQuery = Query;
        const auto QueryGroupBy = GroupBy;
        const auto QueryInterval = Interval;
        const auto QuerySeriesLimit = SeriesLimit;
        const auto Parent = "log:TimeseriesPoint";
        return Gs2->Cache->ListSubscribeTyped(
            Gs2::Log::Model::FTimeseriesPoint::TypeName,
            Parent,
            [Callback, WeakGs2](const TArray<FGs2ObjectPtr>& Values)
            {
                if (!WeakGs2.Pin().IsValid()) return;
                TArray<Gs2::Log::Model::FTimeseriesPointPtr> TypedValues;
                for (const auto& Value : Values) if (Value.IsValid()) TypedValues.Add(StaticCastSharedPtr<Gs2::Log::Model::FTimeseriesPoint>(Value));
                Callback(TypedValues);
            },
            [WeakGs2, Callback, QueryNamespaceName, QueryAggregation, QueryBegin, QueryEnd, QueryQuery, QueryGroupBy, QueryInterval, QuerySeriesLimit]()
            {
                const auto Owner = WeakGs2.Pin();
                if (!Owner.IsValid()) return;
                const auto Domain = MakeShared<FGs2LogDomain>(Owner);
                const auto Task = Gs2::Core::Util::New<FAsyncTask<FCollectTimeseriesTask>>(Domain, Callback, QueryNamespaceName, QueryAggregation, QueryBegin, QueryEnd, QueryQuery, QueryGroupBy, QueryInterval, QuerySeriesLimit);
                Task->StartBackgroundTask();
            }
        );
    }

    void FGs2LogDomain::InvalidateTimeseries(const FString NamespaceName,const TSharedPtr<Gs2::Log::Model::FAggregationConfig> Aggregation,const TOptional<int64> Begin,const TOptional<int64> End,const TOptional<FString> Query,const TSharedPtr<TArray<FString>> GroupBy,const TOptional<int32> Interval,const TOptional<int32> SeriesLimit)
    {
        Gs2->Cache->ClearListCache(
            Gs2::Log::Model::FTimeseriesPoint::TypeName,
            "log:TimeseriesPoint"
        );
    }

    FGs2LogDomain::FSubscribeTimeseriesWithInitialCallTask::FSubscribeTimeseriesWithInitialCallTask(const TSharedPtr<FGs2LogDomain>& Self, TFunction<void(TArray<Gs2::Log::Model::FTimeseriesPointPtr>)> Callback,const FString NamespaceName,const TSharedPtr<Gs2::Log::Model::FAggregationConfig> Aggregation,const TOptional<int64> Begin,const TOptional<int64> End,const TOptional<FString> Query,const TSharedPtr<TArray<FString>> GroupBy,const TOptional<int32> Interval,const TOptional<int32> SeriesLimit) : Self(Self), Callback(Callback), QueryNamespaceName(NamespaceName), QueryAggregation(Aggregation), QueryBegin(Begin), QueryEnd(End), QueryQuery(Query), QueryGroupBy(GroupBy), QueryInterval(Interval), QuerySeriesLimit(SeriesLimit) {}
    FGs2LogDomain::FSubscribeTimeseriesWithInitialCallTask::FSubscribeTimeseriesWithInitialCallTask(const FSubscribeTimeseriesWithInitialCallTask& From) : TGs2Future(From), Self(From.Self), Callback(From.Callback), QueryNamespaceName(From.QueryNamespaceName), QueryAggregation(From.QueryAggregation), QueryBegin(From.QueryBegin), QueryEnd(From.QueryEnd), QueryQuery(From.QueryQuery), QueryGroupBy(From.QueryGroupBy), QueryInterval(From.QueryInterval), QuerySeriesLimit(From.QuerySeriesLimit) {}
    Gs2::Core::Model::FGs2ErrorPtr FGs2LogDomain::FSubscribeTimeseriesWithInitialCallTask::Action(TSharedPtr<TSharedPtr<Gs2::Core::Domain::CallbackID>> Result)
    {
        const auto Task = Gs2::Core::Util::New<FAsyncTask<FCollectTimeseriesTask>>(Self, TFunction<void(TArray<Gs2::Log::Model::FTimeseriesPointPtr>)>(), QueryNamespaceName, QueryAggregation, QueryBegin, QueryEnd, QueryQuery, QueryGroupBy, QueryInterval, QuerySeriesLimit);
        Task->StartSynchronousTask(); Task->EnsureCompletion();
        if (Task->GetTask().IsError()) return Task->GetTask().Error();
        const auto Values = Task->GetTask().Result();
        const auto CallbackId = Self->SubscribeTimeseries(Callback, QueryNamespaceName, QueryAggregation, QueryBegin, QueryEnd, QueryQuery, QueryGroupBy, QueryInterval, QuerySeriesLimit);
        Callback(*Values); *Result = MakeShared<Gs2::Core::Domain::CallbackID>(CallbackId);
        return nullptr;
    }
    TSharedPtr<FAsyncTask<FGs2LogDomain::FSubscribeTimeseriesWithInitialCallTask>> FGs2LogDomain::SubscribeTimeseriesWithInitialCall(TFunction<void(TArray<Gs2::Log::Model::FTimeseriesPointPtr>)> Callback,const FString NamespaceName,const TSharedPtr<Gs2::Log::Model::FAggregationConfig> Aggregation,const TOptional<int64> Begin,const TOptional<int64> End,const TOptional<FString> Query,const TSharedPtr<TArray<FString>> GroupBy,const TOptional<int32> Interval,const TOptional<int32> SeriesLimit)
    {
        return Gs2::Core::Util::New<FAsyncTask<FSubscribeTimeseriesWithInitialCallTask>>(this->AsShared(), Callback, NamespaceName, Aggregation, Begin, End, Query, GroupBy, Interval, SeriesLimit);
    }

    TSharedPtr<Gs2::Log::Domain::Model::FLogEntryDomain> FGs2LogDomain::LogEntry(
    )
    {
        return MakeShared<Gs2::Log::Domain::Model::FLogEntryDomain>(
            Gs2,
            AsShared()
        );
    }

    void FGs2LogDomain::UpdateCacheFromStampSheet(
        const FString Method,
        const FString Request,
        const FString Result,
        const TOptional<int32> TimeOffset
    ) {
    }

    void FGs2LogDomain::UpdateCacheFromStampTask(
        const FString Method,
        const FString Request,
        const FString Result,
        const TOptional<int32> TimeOffset
    ) {
    }

    void FGs2LogDomain::UpdateCacheFromJobResult(
        const FString Method,
        const Gs2::JobQueue::Model::FJobPtr Job,
        const Gs2::JobQueue::Model::FJobResultBodyPtr Result,
        const TOptional<int32> TimeOffset
    ) {
    }

    void FGs2LogDomain::HandleNotification(
        const FString Action,
        const FString Payload
    ) {
    }
}

#if defined(_MSC_VER)
#pragma warning (pop)
#elif defined(__clang__)
#pragma clang diagnostic pop
#endif
