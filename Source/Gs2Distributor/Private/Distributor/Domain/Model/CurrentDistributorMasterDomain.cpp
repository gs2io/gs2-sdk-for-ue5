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

#include "Distributor/Domain/Model/CurrentDistributorMaster.h"
#include "Distributor/Domain/Model/Namespace.h"
#include "Distributor/Domain/Model/DistributorModelMaster.h"
#include "Distributor/Domain/Model/DistributorModel.h"
#include "Distributor/Domain/Model/CurrentDistributorMaster.h"
#include "Distributor/Domain/Model/Distribute.h"
#include "Distributor/Domain/Model/User.h"
#include "Distributor/Domain/Model/UserAccessToken.h"
#include "Distributor/Domain/Model/StampSheetResult.h"
#include "Distributor/Domain/Model/StampSheetResultAccessToken.h"

#include "Core/Domain/Model/AutoStampSheetDomain.h"
#include "Core/Domain/Model/StampSheetDomain.h"

namespace Gs2::Distributor::Domain::Model
{

    FCurrentDistributorMasterDomain::FCurrentDistributorMasterDomain(
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
        Client(MakeShared<Gs2::Distributor::FGs2DistributorRestClient>(Session)),
        NamespaceName(NamespaceName),
        ParentKey(Gs2::Distributor::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
            NamespaceName,
            "CurrentDistributorMaster"
        ))
    {
    }

    FCurrentDistributorMasterDomain::FCurrentDistributorMasterDomain(
        const FCurrentDistributorMasterDomain& From
    ):
        Cache(From.Cache),
        JobQueueDomain(From.JobQueueDomain),
        StampSheetConfiguration(From.StampSheetConfiguration),
        Session(From.Session),
        Client(From.Client)
    {

    }

    FCurrentDistributorMasterDomain::FExportMasterTask::FExportMasterTask(
        const TSharedPtr<FCurrentDistributorMasterDomain> Self,
        const Request::FExportMasterRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FCurrentDistributorMasterDomain::FExportMasterTask::FExportMasterTask(
        const FExportMasterTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FCurrentDistributorMasterDomain::FExportMasterTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Distributor::Domain::Model::FCurrentDistributorMasterDomain>> Result
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
                const auto ParentKey = Gs2::Distributor::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
                    Self->NamespaceName,
                    "CurrentDistributorMaster"
                );
                const auto Key = Gs2::Distributor::Domain::Model::FCurrentDistributorMasterDomain::CreateCacheKey(
                );
                Self->Cache->Put(
                    Gs2::Distributor::Model::FCurrentDistributorMaster::TypeName,
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

    TSharedPtr<FAsyncTask<FCurrentDistributorMasterDomain::FExportMasterTask>> FCurrentDistributorMasterDomain::ExportMaster(
        Request::FExportMasterRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FExportMasterTask>>(this->AsShared(), Request);
    }

    FCurrentDistributorMasterDomain::FGetTask::FGetTask(
        const TSharedPtr<FCurrentDistributorMasterDomain> Self,
        const Request::FGetCurrentDistributorMasterRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FCurrentDistributorMasterDomain::FGetTask::FGetTask(
        const FGetTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FCurrentDistributorMasterDomain::FGetTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Distributor::Model::FCurrentDistributorMaster>> Result
    )
    {
        Request
            ->WithNamespaceName(Self->NamespaceName);
        const auto Future = Self->Client->GetCurrentDistributorMaster(
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
                const auto ParentKey = Gs2::Distributor::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
                    Self->NamespaceName,
                    "CurrentDistributorMaster"
                );
                const auto Key = Gs2::Distributor::Domain::Model::FCurrentDistributorMasterDomain::CreateCacheKey(
                );
                Self->Cache->Put(
                    Gs2::Distributor::Model::FCurrentDistributorMaster::TypeName,
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

    TSharedPtr<FAsyncTask<FCurrentDistributorMasterDomain::FGetTask>> FCurrentDistributorMasterDomain::Get(
        Request::FGetCurrentDistributorMasterRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FGetTask>>(this->AsShared(), Request);
    }

    FCurrentDistributorMasterDomain::FUpdateTask::FUpdateTask(
        const TSharedPtr<FCurrentDistributorMasterDomain> Self,
        const Request::FUpdateCurrentDistributorMasterRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FCurrentDistributorMasterDomain::FUpdateTask::FUpdateTask(
        const FUpdateTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FCurrentDistributorMasterDomain::FUpdateTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Distributor::Domain::Model::FCurrentDistributorMasterDomain>> Result
    )
    {
        Request
            ->WithNamespaceName(Self->NamespaceName);
        const auto Future = Self->Client->UpdateCurrentDistributorMaster(
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
                const auto ParentKey = Gs2::Distributor::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
                    Self->NamespaceName,
                    "CurrentDistributorMaster"
                );
                const auto Key = Gs2::Distributor::Domain::Model::FCurrentDistributorMasterDomain::CreateCacheKey(
                );
                Self->Cache->Put(
                    Gs2::Distributor::Model::FCurrentDistributorMaster::TypeName,
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

    TSharedPtr<FAsyncTask<FCurrentDistributorMasterDomain::FUpdateTask>> FCurrentDistributorMasterDomain::Update(
        Request::FUpdateCurrentDistributorMasterRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FUpdateTask>>(this->AsShared(), Request);
    }

    FCurrentDistributorMasterDomain::FUpdateFromGitHubTask::FUpdateFromGitHubTask(
        const TSharedPtr<FCurrentDistributorMasterDomain> Self,
        const Request::FUpdateCurrentDistributorMasterFromGitHubRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FCurrentDistributorMasterDomain::FUpdateFromGitHubTask::FUpdateFromGitHubTask(
        const FUpdateFromGitHubTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FCurrentDistributorMasterDomain::FUpdateFromGitHubTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Distributor::Domain::Model::FCurrentDistributorMasterDomain>> Result
    )
    {
        Request
            ->WithNamespaceName(Self->NamespaceName);
        const auto Future = Self->Client->UpdateCurrentDistributorMasterFromGitHub(
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
                const auto ParentKey = Gs2::Distributor::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
                    Self->NamespaceName,
                    "CurrentDistributorMaster"
                );
                const auto Key = Gs2::Distributor::Domain::Model::FCurrentDistributorMasterDomain::CreateCacheKey(
                );
                Self->Cache->Put(
                    Gs2::Distributor::Model::FCurrentDistributorMaster::TypeName,
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

    TSharedPtr<FAsyncTask<FCurrentDistributorMasterDomain::FUpdateFromGitHubTask>> FCurrentDistributorMasterDomain::UpdateFromGitHub(
        Request::FUpdateCurrentDistributorMasterFromGitHubRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FUpdateFromGitHubTask>>(this->AsShared(), Request);
    }

    FString FCurrentDistributorMasterDomain::CreateCacheParentKey(
        TOptional<FString> NamespaceName,
        FString ChildType
    )
    {
        return FString() +
            (NamespaceName.IsSet() ? *NamespaceName : "null") + ":" +
            ChildType;
    }

    FString FCurrentDistributorMasterDomain::CreateCacheKey(
    )
    {
        return "Singleton";
    }

    FCurrentDistributorMasterDomain::FModelTask::FModelTask(
        const TSharedPtr<FCurrentDistributorMasterDomain> Self
    ): Self(Self)
    {

    }

    FCurrentDistributorMasterDomain::FModelTask::FModelTask(
        const FModelTask& From
    ): TGs2Future(From), Self(From.Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FCurrentDistributorMasterDomain::FModelTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Distributor::Model::FCurrentDistributorMaster>> Result
    )
    {
        // ReSharper disable once CppLocalVariableMayBeConst
        TSharedPtr<Gs2::Distributor::Model::FCurrentDistributorMaster> Value;
        auto bCacheHit = Self->Cache->TryGet<Gs2::Distributor::Model::FCurrentDistributorMaster>(
            Self->ParentKey,
            Gs2::Distributor::Domain::Model::FCurrentDistributorMasterDomain::CreateCacheKey(
            ),
            &Value
        );
        if (!bCacheHit) {
            const auto Future = Self->Get(
                MakeShared<Gs2::Distributor::Request::FGetCurrentDistributorMasterRequest>()
            );
            Future->StartSynchronousTask();
            if (Future->GetTask().IsError())
            {
                if (Future->GetTask().Error()->Type() != Gs2::Core::Model::FNotFoundError::TypeString)
                {
                    return Future->GetTask().Error();
                }

                const auto Key = Gs2::Distributor::Domain::Model::FCurrentDistributorMasterDomain::CreateCacheKey(
                );
                Self->Cache->Put(
                    Gs2::Distributor::Model::FCurrentDistributorMaster::TypeName,
                    Self->ParentKey,
                    Key,
                    nullptr,
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );

                if (Future->GetTask().Error()->Detail(0)->GetComponent() != "currentDistributorMaster")
                {
                    return Future->GetTask().Error();
                }
            }
            Self->Cache->TryGet<Gs2::Distributor::Model::FCurrentDistributorMaster>(
                Self->ParentKey,
                Gs2::Distributor::Domain::Model::FCurrentDistributorMasterDomain::CreateCacheKey(
                ),
                &Value
            );
            Future->EnsureCompletion();
        }
        *Result = Value;

        return nullptr;
    }

    TSharedPtr<FAsyncTask<FCurrentDistributorMasterDomain::FModelTask>> FCurrentDistributorMasterDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FCurrentDistributorMasterDomain::FModelTask>>(this->AsShared());
    }
}

#if defined(_MSC_VER)
#pragma warning (pop)
#elif defined(__clang__)
#pragma clang diagnostic pop
#endif

