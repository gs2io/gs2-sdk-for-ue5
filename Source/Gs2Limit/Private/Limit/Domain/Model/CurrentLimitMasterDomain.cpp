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

#include "Limit/Domain/Model/CurrentLimitMaster.h"
#include "Limit/Domain/Model/Namespace.h"
#include "Limit/Domain/Model/Counter.h"
#include "Limit/Domain/Model/CounterAccessToken.h"
#include "Limit/Domain/Model/LimitModelMaster.h"
#include "Limit/Domain/Model/CurrentLimitMaster.h"
#include "Limit/Domain/Model/LimitModel.h"
#include "Limit/Domain/Model/User.h"
#include "Limit/Domain/Model/UserAccessToken.h"

#include "Core/Domain/Model/AutoStampSheetDomain.h"
#include "Core/Domain/Model/StampSheetDomain.h"

namespace Gs2::Limit::Domain::Model
{

    FCurrentLimitMasterDomain::FCurrentLimitMasterDomain(
        const Core::Domain::FCacheDatabasePtr Cache,
        const Gs2::Core::Domain::Model::FJobQueueDomainPtr JobQueueDomain,
        const Gs2::Core::Domain::Model::FStampSheetConfigurationPtr StampSheetConfiguration,
        const Gs2::Core::Net::Rest::FGs2RestSessionPtr Session,
        const TOptional<FString> NamespaceName
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Cache(Cache),
        JobQueueDomain(JobQueueDomain),
        StampSheetConfiguration(StampSheetConfiguration),
        Session(Session),
        Client(MakeShared<Gs2::Limit::FGs2LimitRestClient>(Session)),
        NamespaceName(NamespaceName),
        ParentKey(Gs2::Limit::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
            NamespaceName,
            "CurrentLimitMaster"
        ))
    {
    }

    FCurrentLimitMasterDomain::FCurrentLimitMasterDomain(
        const FCurrentLimitMasterDomain& From
    ):
        Cache(From.Cache),
        JobQueueDomain(From.JobQueueDomain),
        StampSheetConfiguration(From.StampSheetConfiguration),
        Session(From.Session),
        Client(From.Client)
    {

    }

    FCurrentLimitMasterDomain::FExportMasterTask::FExportMasterTask(
        const TSharedPtr<FCurrentLimitMasterDomain> Self,
        const Request::FExportMasterRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FCurrentLimitMasterDomain::FExportMasterTask::FExportMasterTask(
        const FExportMasterTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FCurrentLimitMasterDomain::FExportMasterTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Limit::Domain::Model::FCurrentLimitMasterDomain>> Result
    )
    {
        Request
            ->WithNamespaceName(Self->NamespaceName);
        const auto Future = Self->Client->ExportMaster(
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
                const auto ParentKey = Gs2::Limit::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
                    Self->NamespaceName,
                    "CurrentLimitMaster"
                );
                const auto Key = Gs2::Limit::Domain::Model::FCurrentLimitMasterDomain::CreateCacheKey(
                );
                Self->Cache->Put(
                    Gs2::Limit::Model::FCurrentLimitMaster::TypeName,
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

    TSharedPtr<FAsyncTask<FCurrentLimitMasterDomain::FExportMasterTask>> FCurrentLimitMasterDomain::ExportMaster(
        Request::FExportMasterRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FExportMasterTask>>(this->AsShared(), Request);
    }

    FCurrentLimitMasterDomain::FGetTask::FGetTask(
        const TSharedPtr<FCurrentLimitMasterDomain> Self,
        const Request::FGetCurrentLimitMasterRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FCurrentLimitMasterDomain::FGetTask::FGetTask(
        const FGetTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FCurrentLimitMasterDomain::FGetTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Limit::Model::FCurrentLimitMaster>> Result
    )
    {
        Request
            ->WithNamespaceName(Self->NamespaceName);
        const auto Future = Self->Client->GetCurrentLimitMaster(
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
                const auto ParentKey = Gs2::Limit::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
                    Self->NamespaceName,
                    "CurrentLimitMaster"
                );
                const auto Key = Gs2::Limit::Domain::Model::FCurrentLimitMasterDomain::CreateCacheKey(
                );
                Self->Cache->Put(
                    Gs2::Limit::Model::FCurrentLimitMaster::TypeName,
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

    TSharedPtr<FAsyncTask<FCurrentLimitMasterDomain::FGetTask>> FCurrentLimitMasterDomain::Get(
        Request::FGetCurrentLimitMasterRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FGetTask>>(this->AsShared(), Request);
    }

    FCurrentLimitMasterDomain::FUpdateTask::FUpdateTask(
        const TSharedPtr<FCurrentLimitMasterDomain> Self,
        const Request::FUpdateCurrentLimitMasterRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FCurrentLimitMasterDomain::FUpdateTask::FUpdateTask(
        const FUpdateTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FCurrentLimitMasterDomain::FUpdateTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Limit::Domain::Model::FCurrentLimitMasterDomain>> Result
    )
    {
        Request
            ->WithNamespaceName(Self->NamespaceName);
        const auto Future = Self->Client->UpdateCurrentLimitMaster(
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
                const auto ParentKey = Gs2::Limit::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
                    Self->NamespaceName,
                    "CurrentLimitMaster"
                );
                const auto Key = Gs2::Limit::Domain::Model::FCurrentLimitMasterDomain::CreateCacheKey(
                );
                Self->Cache->Put(
                    Gs2::Limit::Model::FCurrentLimitMaster::TypeName,
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

    TSharedPtr<FAsyncTask<FCurrentLimitMasterDomain::FUpdateTask>> FCurrentLimitMasterDomain::Update(
        Request::FUpdateCurrentLimitMasterRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FUpdateTask>>(this->AsShared(), Request);
    }

    FCurrentLimitMasterDomain::FUpdateFromGitHubTask::FUpdateFromGitHubTask(
        const TSharedPtr<FCurrentLimitMasterDomain> Self,
        const Request::FUpdateCurrentLimitMasterFromGitHubRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FCurrentLimitMasterDomain::FUpdateFromGitHubTask::FUpdateFromGitHubTask(
        const FUpdateFromGitHubTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FCurrentLimitMasterDomain::FUpdateFromGitHubTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Limit::Domain::Model::FCurrentLimitMasterDomain>> Result
    )
    {
        Request
            ->WithNamespaceName(Self->NamespaceName);
        const auto Future = Self->Client->UpdateCurrentLimitMasterFromGitHub(
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
                const auto ParentKey = Gs2::Limit::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
                    Self->NamespaceName,
                    "CurrentLimitMaster"
                );
                const auto Key = Gs2::Limit::Domain::Model::FCurrentLimitMasterDomain::CreateCacheKey(
                );
                Self->Cache->Put(
                    Gs2::Limit::Model::FCurrentLimitMaster::TypeName,
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

    TSharedPtr<FAsyncTask<FCurrentLimitMasterDomain::FUpdateFromGitHubTask>> FCurrentLimitMasterDomain::UpdateFromGitHub(
        Request::FUpdateCurrentLimitMasterFromGitHubRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FUpdateFromGitHubTask>>(this->AsShared(), Request);
    }

    FString FCurrentLimitMasterDomain::CreateCacheParentKey(
        TOptional<FString> NamespaceName,
        FString ChildType
    )
    {
        return FString() +
            (NamespaceName.IsSet() ? *NamespaceName : "null") + ":" +
            ChildType;
    }

    FString FCurrentLimitMasterDomain::CreateCacheKey(
    )
    {
        return "Singleton";
    }

    FCurrentLimitMasterDomain::FModelTask::FModelTask(
        const TSharedPtr<FCurrentLimitMasterDomain> Self
    ): Self(Self)
    {

    }

    FCurrentLimitMasterDomain::FModelTask::FModelTask(
        const FModelTask& From
    ): TGs2Future(From), Self(From.Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FCurrentLimitMasterDomain::FModelTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Limit::Model::FCurrentLimitMaster>> Result
    )
    {
        // ReSharper disable once CppLocalVariableMayBeConst
        auto Value = Self->Cache->Get<Gs2::Limit::Model::FCurrentLimitMaster>(
            Self->ParentKey,
            Gs2::Limit::Domain::Model::FCurrentLimitMasterDomain::CreateCacheKey(
            )
        );
        if (Value == nullptr) {
            const auto Future = Self->Get(
                MakeShared<Gs2::Limit::Request::FGetCurrentLimitMasterRequest>()
            );
            Future->StartSynchronousTask();
            if (Future->GetTask().IsError())
            {
                if (Future->GetTask().Error()->Type() == Gs2::Core::Model::FNotFoundError::TypeString)
                {
                    if (Future->GetTask().Error()->Detail(0)->GetComponent() == "currentLimitMaster")
                    {
                        Self->Cache->Delete(
                            Gs2::Limit::Model::FCurrentLimitMaster::TypeName,
                            Self->ParentKey,
                            Gs2::Limit::Domain::Model::FCurrentLimitMasterDomain::CreateCacheKey(
                            )
                        );
                    }
                    else
                    {
                        return Future->GetTask().Error();
                    }
                }
                else
                {
                    return Future->GetTask().Error();
                }
            }
            Value = Self->Cache->Get<Gs2::Limit::Model::FCurrentLimitMaster>(
                Self->ParentKey,
                Gs2::Limit::Domain::Model::FCurrentLimitMasterDomain::CreateCacheKey(
                )
            );
            Future->EnsureCompletion();
        }
        *Result = Value;

        return nullptr;
    }

    TSharedPtr<FAsyncTask<FCurrentLimitMasterDomain::FModelTask>> FCurrentLimitMasterDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FCurrentLimitMasterDomain::FModelTask>>(this->AsShared());
    }
}

#if defined(_MSC_VER)
#pragma warning (pop)
#elif defined(__clang__)
#pragma clang diagnostic pop
#endif

