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

#include "Log/Domain/Model/Insight.h"
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

    FInsightDomain::FInsightDomain(
        const Core::Domain::FGs2Ptr& Gs2,
        const Log::Domain::FGs2LogDomainPtr& Service,
        const TOptional<FString> NamespaceName,
        const TOptional<FString> InsightName
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Gs2(Gs2),
        Service(Service),
        Client(MakeShared<Gs2::Log::FGs2LogRestClient>(Gs2->RestSession)),
        NamespaceName(NamespaceName),
        InsightName(InsightName),
        ParentKey(Gs2::Log::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
            NamespaceName,
            "Insight"
        ))
    {
    }

    FInsightDomain::FInsightDomain(
        const FInsightDomain& From
    ):
        Gs2(From.Gs2),
        Service(From.Service),
        Client(From.Client),
        NamespaceName(From.NamespaceName),
        InsightName(From.InsightName),
        ParentKey(From.ParentKey)
    {

    }

    FInsightDomain::FGetTask::FGetTask(
        const TSharedPtr<FInsightDomain>& Self,
        const Request::FGetInsightRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FInsightDomain::FGetTask::FGetTask(
        const FGetTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FInsightDomain::FGetTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Log::Model::FInsight>> Result
    )
    {
        Request
            ->WithContextStack(Self->Gs2->DefaultContextStack)
            ->WithNamespaceName(Self->NamespaceName)
            ->WithInsightName(Self->InsightName);
        const auto Future = Self->Client->GetInsight(
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
        *Result = ResultModel->GetItem();
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FInsightDomain::FGetTask>> FInsightDomain::Get(
        Request::FGetInsightRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FGetTask>>(this->AsShared(), Request);
    }

    FInsightDomain::FDeleteTask::FDeleteTask(
        const TSharedPtr<FInsightDomain>& Self,
        const Request::FDeleteInsightRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FInsightDomain::FDeleteTask::FDeleteTask(
        const FDeleteTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FInsightDomain::FDeleteTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Log::Domain::Model::FInsightDomain>> Result
    )
    {
        Request
            ->WithContextStack(Self->Gs2->DefaultContextStack)
            ->WithNamespaceName(Self->NamespaceName)
            ->WithInsightName(Self->InsightName);
        const auto Future = Self->Client->DeleteInsight(
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
                Self->Gs2->Cache->Delete(Gs2::Log::Model::FInsight::TypeName, ParentKey, Key);
            }
        }
        auto Domain = Self;

        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FInsightDomain::FDeleteTask>> FInsightDomain::Delete(
        Request::FDeleteInsightRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FDeleteTask>>(this->AsShared(), Request);
    }

    FString FInsightDomain::CreateCacheParentKey(
        TOptional<FString> NamespaceName,
        TOptional<FString> InsightName,
        FString ChildType
    )
    {
        return FString("") +
            (NamespaceName.IsSet() ? *NamespaceName : "null") + ":" +
            (InsightName.IsSet() ? *InsightName : "null") + ":" +
            ChildType;
    }

    FString FInsightDomain::CreateCacheKey(
        TOptional<FString> InsightName
    )
    {
        return FString("") +
            (InsightName.IsSet() ? *InsightName : "null");
    }

    FInsightDomain::FModelTask::FModelTask(
        const TSharedPtr<FInsightDomain> Self
    ): Self(Self)
    {

    }

    FInsightDomain::FModelTask::FModelTask(
        const FModelTask& From
    ): TGs2Future(From), Self(From.Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FInsightDomain::FModelTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Log::Model::FInsight>> Result
    )
    {
        // ReSharper disable once CppLocalVariableMayBeConst
        TSharedPtr<Gs2::Log::Model::FInsight> Value;
        auto bCacheHit = Self->Gs2->Cache->TryGet<Gs2::Log::Model::FInsight>(
            Self->ParentKey,
            Gs2::Log::Domain::Model::FInsightDomain::CreateCacheKey(
                Self->InsightName
            ),
            &Value
        );
        if (!bCacheHit) {
            const auto Future = Self->Get(
                MakeShared<Gs2::Log::Request::FGetInsightRequest>()
            );
            Future->StartSynchronousTask();
            if (Future->GetTask().IsError())
            {
                if (Future->GetTask().Error()->Type() != Gs2::Core::Model::FNotFoundError::TypeString)
                {
                    return Future->GetTask().Error();
                }

                const auto Key = Gs2::Log::Domain::Model::FInsightDomain::CreateCacheKey(
                    Self->InsightName
                );
                Self->Gs2->Cache->Put(
                    Gs2::Log::Model::FInsight::TypeName,
                    Self->ParentKey,
                    Key,
                    nullptr,
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );

                if (Future->GetTask().Error()->Detail(0)->GetComponent() != "insight")
                {
                    return Future->GetTask().Error();
                }
            }
            Self->Gs2->Cache->TryGet<Gs2::Log::Model::FInsight>(
                Self->ParentKey,
                Gs2::Log::Domain::Model::FInsightDomain::CreateCacheKey(
                    Self->InsightName
                ),
                &Value
            );
            Future->EnsureCompletion();
        }
        *Result = Value;

        return nullptr;
    }

    TSharedPtr<FAsyncTask<FInsightDomain::FModelTask>> FInsightDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FInsightDomain::FModelTask>>(this->AsShared());
    }

    Gs2::Core::Domain::CallbackID FInsightDomain::Subscribe(
        TFunction<void(Gs2::Log::Model::FInsightPtr)> Callback
    )
    {
        return Gs2->Cache->Subscribe(
            Gs2::Log::Model::FInsight::TypeName,
            ParentKey,
            Gs2::Log::Domain::Model::FInsightDomain::CreateCacheKey(
                InsightName
            ),
            [Callback](TSharedPtr<Gs2Object> obj)
            {
                Callback(StaticCastSharedPtr<Gs2::Log::Model::FInsight>(obj));
            }
        );
    }

    void FInsightDomain::Unsubscribe(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        Gs2->Cache->Unsubscribe(
            Gs2::Log::Model::FInsight::TypeName,
            ParentKey,
            Gs2::Log::Domain::Model::FInsightDomain::CreateCacheKey(
                InsightName
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

