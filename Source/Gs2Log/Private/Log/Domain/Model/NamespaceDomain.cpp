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
        const auto RequestModel = Request;
        const auto ResultModel = Future->GetTask().Result();
        Future->EnsureCompletion();
        if (ResultModel != nullptr) {
            
        }
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
            Gs2::Log::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
                NamespaceName,
                "AccessLog"
            ),
            Callback
        );
    }

    void FNamespaceDomain::UnsubscribeAccessLog(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        Gs2->Cache->ListUnsubscribe(
            Gs2::Log::Model::FAccessLog::TypeName,
            Gs2::Log::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
                NamespaceName,
                "AccessLog"
            ),
            CallbackID
        );
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

    Gs2::Log::Domain::Iterator::FQueryExecuteStampSheetLogIteratorPtr FNamespaceDomain::ExecuteStampSheetLog(
        const TOptional<FString> Service,
        const TOptional<FString> Method,
        const TOptional<FString> Action,
        const TOptional<FString> UserId,
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
            Gs2::Log::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
                NamespaceName,
                "ExecuteStampSheetLog"
            ),
            Callback
        );
    }

    void FNamespaceDomain::UnsubscribeExecuteStampSheetLog(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        Gs2->Cache->ListUnsubscribe(
            Gs2::Log::Model::FExecuteStampSheetLog::TypeName,
            Gs2::Log::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
                NamespaceName,
                "ExecuteStampSheetLog"
            ),
            CallbackID
        );
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
            Gs2::Log::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
                NamespaceName,
                "ExecuteStampTaskLog"
            ),
            Callback
        );
    }

    void FNamespaceDomain::UnsubscribeExecuteStampTaskLog(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        Gs2->Cache->ListUnsubscribe(
            Gs2::Log::Model::FExecuteStampTaskLog::TypeName,
            Gs2::Log::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
                NamespaceName,
                "ExecuteStampTaskLog"
            ),
            CallbackID
        );
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
            Gs2::Log::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
                NamespaceName,
                "IssueStampSheetLog"
            ),
            Callback
        );
    }

    void FNamespaceDomain::UnsubscribeIssueStampSheetLog(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        Gs2->Cache->ListUnsubscribe(
            Gs2::Log::Model::FIssueStampSheetLog::TypeName,
            Gs2::Log::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
                NamespaceName,
                "IssueStampSheetLog"
            ),
            CallbackID
        );
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
            Gs2::Log::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
                NamespaceName,
                "Insight"
            ),
            Callback
        );
    }

    void FNamespaceDomain::UnsubscribeInsights(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        Gs2->Cache->ListUnsubscribe(
            Gs2::Log::Model::FInsight::TypeName,
            Gs2::Log::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
                NamespaceName,
                "Insight"
            ),
            CallbackID
        );
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
        // ReSharper disable once CppLocalVariableMayBeConst
        TSharedPtr<Gs2::Log::Model::FNamespace> Value;
        auto bCacheHit = Self->Gs2->Cache->TryGet<Gs2::Log::Model::FNamespace>(
            ParentKey,
            Gs2::Log::Domain::Model::FNamespaceDomain::CreateCacheKey(
                Self->NamespaceName
            ),
            &Value
        );
        if (!bCacheHit) {
            const auto Future = Self->Get(
                MakeShared<Gs2::Log::Request::FGetNamespaceRequest>()
            );
            Future->StartSynchronousTask();
            if (Future->GetTask().IsError())
            {
                if (Future->GetTask().Error()->Type() != Gs2::Core::Model::FNotFoundError::TypeString)
                {
                    return Future->GetTask().Error();
                }

                const auto Key = Gs2::Log::Domain::Model::FNamespaceDomain::CreateCacheKey(
                    Self->NamespaceName
                );
                Self->Gs2->Cache->Put(
                    Gs2::Log::Model::FNamespace::TypeName,
                    ParentKey,
                    Key,
                    nullptr,
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );

                if (Future->GetTask().Error()->Detail(0)->GetComponent() != "namespace")
                {
                    return Future->GetTask().Error();
                }
            }
            Self->Gs2->Cache->TryGet<Gs2::Log::Model::FNamespace>(
                ParentKey,
                Gs2::Log::Domain::Model::FNamespaceDomain::CreateCacheKey(
                    Self->NamespaceName
                ),
                &Value
            );
            Future->EnsureCompletion();
        }
        *Result = Value;

        return nullptr;
    }

    TSharedPtr<FAsyncTask<FNamespaceDomain::FModelTask>> FNamespaceDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FNamespaceDomain::FModelTask>>(this->AsShared());
    }

    Gs2::Core::Domain::CallbackID FNamespaceDomain::Subscribe(
        TFunction<void(Gs2::Log::Model::FNamespacePtr)> Callback
    )
    {
        return Gs2->Cache->Subscribe(
            Gs2::Log::Model::FNamespace::TypeName,
            ParentKey,
            Gs2::Log::Domain::Model::FNamespaceDomain::CreateCacheKey(
                NamespaceName
            ),
            [Callback](TSharedPtr<Gs2Object> obj)
            {
                Callback(StaticCastSharedPtr<Gs2::Log::Model::FNamespace>(obj));
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

    Gs2::Log::Domain::Iterator::FQueryInGameLogIteratorPtr FNamespaceDomain::InGameLog(
        const TOptional<FString> UserId,
        const TSharedPtr<TArray<TSharedPtr<Gs2::Log::Model::FInGameLogTag>>> Tags,
        const TOptional<int64> Begin,
        const TOptional<int64> End,
        const TOptional<bool> LongTerm,
        const TOptional<FString> TimeOffsetToken
    ) const
    {
        return MakeShared<Gs2::Log::Domain::Iterator::FQueryInGameLogIterator>(
            Gs2,
            Client,
            NamespaceName,
            UserId,
            Tags,
            Begin,
            End,
            LongTerm,
            TimeOffsetToken
        );
    }

}

#if defined(_MSC_VER)
#pragma warning (pop)
#elif defined(__clang__)
#pragma clang diagnostic pop
#endif

