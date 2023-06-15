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

#include "Stamina/Domain/Model/CurrentStaminaMaster.h"
#include "Stamina/Domain/Model/Namespace.h"
#include "Stamina/Domain/Model/StaminaModelMaster.h"
#include "Stamina/Domain/Model/MaxStaminaTableMaster.h"
#include "Stamina/Domain/Model/RecoverIntervalTableMaster.h"
#include "Stamina/Domain/Model/RecoverValueTableMaster.h"
#include "Stamina/Domain/Model/CurrentStaminaMaster.h"
#include "Stamina/Domain/Model/StaminaModel.h"
#include "Stamina/Domain/Model/Stamina.h"
#include "Stamina/Domain/Model/StaminaAccessToken.h"
#include "Stamina/Domain/Model/User.h"
#include "Stamina/Domain/Model/UserAccessToken.h"

#include "Core/Domain/Model/AutoStampSheetDomain.h"
#include "Core/Domain/Model/StampSheetDomain.h"

namespace Gs2::Stamina::Domain::Model
{

    FCurrentStaminaMasterDomain::FCurrentStaminaMasterDomain(
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
        Client(MakeShared<Gs2::Stamina::FGs2StaminaRestClient>(Session)),
        NamespaceName(NamespaceName),
        ParentKey(Gs2::Stamina::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
            NamespaceName,
            "CurrentStaminaMaster"
        ))
    {
    }

    FCurrentStaminaMasterDomain::FCurrentStaminaMasterDomain(
        const FCurrentStaminaMasterDomain& From
    ):
        Cache(From.Cache),
        JobQueueDomain(From.JobQueueDomain),
        StampSheetConfiguration(From.StampSheetConfiguration),
        Session(From.Session),
        Client(From.Client)
    {

    }

    FCurrentStaminaMasterDomain::FExportMasterTask::FExportMasterTask(
        const TSharedPtr<FCurrentStaminaMasterDomain> Self,
        const Request::FExportMasterRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FCurrentStaminaMasterDomain::FExportMasterTask::FExportMasterTask(
        const FExportMasterTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FCurrentStaminaMasterDomain::FExportMasterTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Stamina::Domain::Model::FCurrentStaminaMasterDomain>> Result
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
                const auto ParentKey = Gs2::Stamina::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
                    Self->NamespaceName,
                    "CurrentStaminaMaster"
                );
                const auto Key = Gs2::Stamina::Domain::Model::FCurrentStaminaMasterDomain::CreateCacheKey(
                );
                Self->Cache->Put(
                    Gs2::Stamina::Model::FCurrentStaminaMaster::TypeName,
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

    TSharedPtr<FAsyncTask<FCurrentStaminaMasterDomain::FExportMasterTask>> FCurrentStaminaMasterDomain::ExportMaster(
        Request::FExportMasterRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FExportMasterTask>>(this->AsShared(), Request);
    }

    FCurrentStaminaMasterDomain::FGetTask::FGetTask(
        const TSharedPtr<FCurrentStaminaMasterDomain> Self,
        const Request::FGetCurrentStaminaMasterRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FCurrentStaminaMasterDomain::FGetTask::FGetTask(
        const FGetTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FCurrentStaminaMasterDomain::FGetTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Stamina::Model::FCurrentStaminaMaster>> Result
    )
    {
        Request
            ->WithNamespaceName(Self->NamespaceName);
        const auto Future = Self->Client->GetCurrentStaminaMaster(
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
                const auto ParentKey = Gs2::Stamina::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
                    Self->NamespaceName,
                    "CurrentStaminaMaster"
                );
                const auto Key = Gs2::Stamina::Domain::Model::FCurrentStaminaMasterDomain::CreateCacheKey(
                );
                Self->Cache->Put(
                    Gs2::Stamina::Model::FCurrentStaminaMaster::TypeName,
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

    TSharedPtr<FAsyncTask<FCurrentStaminaMasterDomain::FGetTask>> FCurrentStaminaMasterDomain::Get(
        Request::FGetCurrentStaminaMasterRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FGetTask>>(this->AsShared(), Request);
    }

    FCurrentStaminaMasterDomain::FUpdateTask::FUpdateTask(
        const TSharedPtr<FCurrentStaminaMasterDomain> Self,
        const Request::FUpdateCurrentStaminaMasterRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FCurrentStaminaMasterDomain::FUpdateTask::FUpdateTask(
        const FUpdateTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FCurrentStaminaMasterDomain::FUpdateTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Stamina::Domain::Model::FCurrentStaminaMasterDomain>> Result
    )
    {
        Request
            ->WithNamespaceName(Self->NamespaceName);
        const auto Future = Self->Client->UpdateCurrentStaminaMaster(
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
                const auto ParentKey = Gs2::Stamina::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
                    Self->NamespaceName,
                    "CurrentStaminaMaster"
                );
                const auto Key = Gs2::Stamina::Domain::Model::FCurrentStaminaMasterDomain::CreateCacheKey(
                );
                Self->Cache->Put(
                    Gs2::Stamina::Model::FCurrentStaminaMaster::TypeName,
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

    TSharedPtr<FAsyncTask<FCurrentStaminaMasterDomain::FUpdateTask>> FCurrentStaminaMasterDomain::Update(
        Request::FUpdateCurrentStaminaMasterRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FUpdateTask>>(this->AsShared(), Request);
    }

    FCurrentStaminaMasterDomain::FUpdateFromGitHubTask::FUpdateFromGitHubTask(
        const TSharedPtr<FCurrentStaminaMasterDomain> Self,
        const Request::FUpdateCurrentStaminaMasterFromGitHubRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FCurrentStaminaMasterDomain::FUpdateFromGitHubTask::FUpdateFromGitHubTask(
        const FUpdateFromGitHubTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FCurrentStaminaMasterDomain::FUpdateFromGitHubTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Stamina::Domain::Model::FCurrentStaminaMasterDomain>> Result
    )
    {
        Request
            ->WithNamespaceName(Self->NamespaceName);
        const auto Future = Self->Client->UpdateCurrentStaminaMasterFromGitHub(
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
                const auto ParentKey = Gs2::Stamina::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
                    Self->NamespaceName,
                    "CurrentStaminaMaster"
                );
                const auto Key = Gs2::Stamina::Domain::Model::FCurrentStaminaMasterDomain::CreateCacheKey(
                );
                Self->Cache->Put(
                    Gs2::Stamina::Model::FCurrentStaminaMaster::TypeName,
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

    TSharedPtr<FAsyncTask<FCurrentStaminaMasterDomain::FUpdateFromGitHubTask>> FCurrentStaminaMasterDomain::UpdateFromGitHub(
        Request::FUpdateCurrentStaminaMasterFromGitHubRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FUpdateFromGitHubTask>>(this->AsShared(), Request);
    }

    FString FCurrentStaminaMasterDomain::CreateCacheParentKey(
        TOptional<FString> NamespaceName,
        FString ChildType
    )
    {
        return FString() +
            (NamespaceName.IsSet() ? *NamespaceName : "null") + ":" +
            ChildType;
    }

    FString FCurrentStaminaMasterDomain::CreateCacheKey(
    )
    {
        return "Singleton";
    }

    FCurrentStaminaMasterDomain::FModelTask::FModelTask(
        const TSharedPtr<FCurrentStaminaMasterDomain> Self
    ): Self(Self)
    {

    }

    FCurrentStaminaMasterDomain::FModelTask::FModelTask(
        const FModelTask& From
    ): TGs2Future(From), Self(From.Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FCurrentStaminaMasterDomain::FModelTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Stamina::Model::FCurrentStaminaMaster>> Result
    )
    {
        // ReSharper disable once CppLocalVariableMayBeConst
        TSharedPtr<Gs2::Stamina::Model::FCurrentStaminaMaster> Value;
        auto bCacheHit = Self->Cache->TryGet<Gs2::Stamina::Model::FCurrentStaminaMaster>(
            Self->ParentKey,
            Gs2::Stamina::Domain::Model::FCurrentStaminaMasterDomain::CreateCacheKey(
            ),
            &Value
        );
        if (!bCacheHit) {
            const auto Future = Self->Get(
                MakeShared<Gs2::Stamina::Request::FGetCurrentStaminaMasterRequest>()
            );
            Future->StartSynchronousTask();
            if (Future->GetTask().IsError())
            {
                if (Future->GetTask().Error()->Type() != Gs2::Core::Model::FNotFoundError::TypeString)
                {
                    return Future->GetTask().Error();
                }

                const auto Key = Gs2::Stamina::Domain::Model::FCurrentStaminaMasterDomain::CreateCacheKey(
                );
                Self->Cache->Put(
                    Gs2::Stamina::Model::FCurrentStaminaMaster::TypeName,
                    Self->ParentKey,
                    Key,
                    nullptr,
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );

                if (Future->GetTask().Error()->Detail(0)->GetComponent() != "currentStaminaMaster")
                {
                    return Future->GetTask().Error();
                }
            }
            Self->Cache->TryGet<Gs2::Stamina::Model::FCurrentStaminaMaster>(
                Self->ParentKey,
                Gs2::Stamina::Domain::Model::FCurrentStaminaMasterDomain::CreateCacheKey(
                ),
                &Value
            );
            Future->EnsureCompletion();
        }
        *Result = Value;

        return nullptr;
    }

    TSharedPtr<FAsyncTask<FCurrentStaminaMasterDomain::FModelTask>> FCurrentStaminaMasterDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FCurrentStaminaMasterDomain::FModelTask>>(this->AsShared());
    }
}

#if defined(_MSC_VER)
#pragma warning (pop)
#elif defined(__clang__)
#pragma clang diagnostic pop
#endif

