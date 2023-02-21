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

#include "Formation/Domain/Model/CurrentFormMaster.h"
#include "Formation/Domain/Model/Namespace.h"
#include "Formation/Domain/Model/FormModel.h"
#include "Formation/Domain/Model/FormModelMaster.h"
#include "Formation/Domain/Model/MoldModel.h"
#include "Formation/Domain/Model/MoldModelMaster.h"
#include "Formation/Domain/Model/CurrentFormMaster.h"
#include "Formation/Domain/Model/Mold.h"
#include "Formation/Domain/Model/MoldAccessToken.h"
#include "Formation/Domain/Model/Form.h"
#include "Formation/Domain/Model/FormAccessToken.h"
#include "Formation/Domain/Model/PropertyForm.h"
#include "Formation/Domain/Model/PropertyFormAccessToken.h"
#include "Formation/Domain/Model/User.h"
#include "Formation/Domain/Model/UserAccessToken.h"

#include "Core/Domain/Model/AutoStampSheetDomain.h"
#include "Core/Domain/Model/StampSheetDomain.h"

namespace Gs2::Formation::Domain::Model
{

    FCurrentFormMasterDomain::FCurrentFormMasterDomain(
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
        Client(MakeShared<Gs2::Formation::FGs2FormationRestClient>(Session)),
        NamespaceName(NamespaceName),
        ParentKey(Gs2::Formation::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
            NamespaceName,
            "CurrentFormMaster"
        ))
    {
    }

    FCurrentFormMasterDomain::FCurrentFormMasterDomain(
        const FCurrentFormMasterDomain& From
    ):
        Cache(From.Cache),
        JobQueueDomain(From.JobQueueDomain),
        StampSheetConfiguration(From.StampSheetConfiguration),
        Session(From.Session),
        Client(From.Client)
    {

    }

    FCurrentFormMasterDomain::FExportMasterTask::FExportMasterTask(
        const TSharedPtr<FCurrentFormMasterDomain> Self,
        const Request::FExportMasterRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FCurrentFormMasterDomain::FExportMasterTask::FExportMasterTask(
        const FExportMasterTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FCurrentFormMasterDomain::FExportMasterTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Formation::Domain::Model::FCurrentFormMasterDomain>> Result
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
                const auto ParentKey = Gs2::Formation::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
                    Self->NamespaceName,
                    "CurrentFormMaster"
                );
                const auto Key = Gs2::Formation::Domain::Model::FCurrentFormMasterDomain::CreateCacheKey(
                );
                Self->Cache->Put<Gs2::Formation::Model::FCurrentFormMaster>(
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

    TSharedPtr<FAsyncTask<FCurrentFormMasterDomain::FExportMasterTask>> FCurrentFormMasterDomain::ExportMaster(
        Request::FExportMasterRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FExportMasterTask>>(this->AsShared(), Request);
    }

    FCurrentFormMasterDomain::FGetTask::FGetTask(
        const TSharedPtr<FCurrentFormMasterDomain> Self,
        const Request::FGetCurrentFormMasterRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FCurrentFormMasterDomain::FGetTask::FGetTask(
        const FGetTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FCurrentFormMasterDomain::FGetTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Formation::Model::FCurrentFormMaster>> Result
    )
    {
        Request
            ->WithNamespaceName(Self->NamespaceName);
        const auto Future = Self->Client->GetCurrentFormMaster(
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
                const auto ParentKey = Gs2::Formation::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
                    Self->NamespaceName,
                    "CurrentFormMaster"
                );
                const auto Key = Gs2::Formation::Domain::Model::FCurrentFormMasterDomain::CreateCacheKey(
                );
                Self->Cache->Put<Gs2::Formation::Model::FCurrentFormMaster>(
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

    TSharedPtr<FAsyncTask<FCurrentFormMasterDomain::FGetTask>> FCurrentFormMasterDomain::Get(
        Request::FGetCurrentFormMasterRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FGetTask>>(this->AsShared(), Request);
    }

    FCurrentFormMasterDomain::FUpdateTask::FUpdateTask(
        const TSharedPtr<FCurrentFormMasterDomain> Self,
        const Request::FUpdateCurrentFormMasterRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FCurrentFormMasterDomain::FUpdateTask::FUpdateTask(
        const FUpdateTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FCurrentFormMasterDomain::FUpdateTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Formation::Domain::Model::FCurrentFormMasterDomain>> Result
    )
    {
        Request
            ->WithNamespaceName(Self->NamespaceName);
        const auto Future = Self->Client->UpdateCurrentFormMaster(
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
                const auto ParentKey = Gs2::Formation::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
                    Self->NamespaceName,
                    "CurrentFormMaster"
                );
                const auto Key = Gs2::Formation::Domain::Model::FCurrentFormMasterDomain::CreateCacheKey(
                );
                Self->Cache->Put<Gs2::Formation::Model::FCurrentFormMaster>(
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

    TSharedPtr<FAsyncTask<FCurrentFormMasterDomain::FUpdateTask>> FCurrentFormMasterDomain::Update(
        Request::FUpdateCurrentFormMasterRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FUpdateTask>>(this->AsShared(), Request);
    }

    FCurrentFormMasterDomain::FUpdateFromGitHubTask::FUpdateFromGitHubTask(
        const TSharedPtr<FCurrentFormMasterDomain> Self,
        const Request::FUpdateCurrentFormMasterFromGitHubRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FCurrentFormMasterDomain::FUpdateFromGitHubTask::FUpdateFromGitHubTask(
        const FUpdateFromGitHubTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FCurrentFormMasterDomain::FUpdateFromGitHubTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Formation::Domain::Model::FCurrentFormMasterDomain>> Result
    )
    {
        Request
            ->WithNamespaceName(Self->NamespaceName);
        const auto Future = Self->Client->UpdateCurrentFormMasterFromGitHub(
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
                const auto ParentKey = Gs2::Formation::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
                    Self->NamespaceName,
                    "CurrentFormMaster"
                );
                const auto Key = Gs2::Formation::Domain::Model::FCurrentFormMasterDomain::CreateCacheKey(
                );
                Self->Cache->Put<Gs2::Formation::Model::FCurrentFormMaster>(
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

    TSharedPtr<FAsyncTask<FCurrentFormMasterDomain::FUpdateFromGitHubTask>> FCurrentFormMasterDomain::UpdateFromGitHub(
        Request::FUpdateCurrentFormMasterFromGitHubRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FUpdateFromGitHubTask>>(this->AsShared(), Request);
    }

    FString FCurrentFormMasterDomain::CreateCacheParentKey(
        TOptional<FString> NamespaceName,
        FString ChildType
    )
    {
        return FString() +
            (NamespaceName.IsSet() ? *NamespaceName : "null") + ":" +
            ChildType;
    }

    FString FCurrentFormMasterDomain::CreateCacheKey(
    )
    {
        return "Singleton";
    }

    FCurrentFormMasterDomain::FModelTask::FModelTask(
        const TSharedPtr<FCurrentFormMasterDomain> Self
    ): Self(Self)
    {

    }

    FCurrentFormMasterDomain::FModelTask::FModelTask(
        const FModelTask& From
    ): TGs2Future(From), Self(From.Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FCurrentFormMasterDomain::FModelTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Formation::Model::FCurrentFormMaster>> Result
    )
    {
        // ReSharper disable once CppLocalVariableMayBeConst
        auto Value = Self->Cache->Get<Gs2::Formation::Model::FCurrentFormMaster>(
            Self->ParentKey,
            Gs2::Formation::Domain::Model::FCurrentFormMasterDomain::CreateCacheKey(
            )
        );
        if (Value == nullptr) {
            const auto Future = Self->Get(
                MakeShared<Gs2::Formation::Request::FGetCurrentFormMasterRequest>()
            );
            Future->StartSynchronousTask();
            if (Future->GetTask().IsError())
            {
                if (Future->GetTask().Error()->Type() == Gs2::Core::Model::FNotFoundError::TypeString)
                {
                    if (Future->GetTask().Error()->Detail(0)->GetComponent() == "currentFormMaster")
                    {
                        Self->Cache->Delete<Gs2::Formation::Model::FCurrentFormMaster>(
                            Self->ParentKey,
                            Gs2::Formation::Domain::Model::FCurrentFormMasterDomain::CreateCacheKey(
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
            Value = Self->Cache->Get<Gs2::Formation::Model::FCurrentFormMaster>(
                Self->ParentKey,
                Gs2::Formation::Domain::Model::FCurrentFormMasterDomain::CreateCacheKey(
                )
            );
            Future->EnsureCompletion();
        }
        *Result = Value;

        return nullptr;
    }

    TSharedPtr<FAsyncTask<FCurrentFormMasterDomain::FModelTask>> FCurrentFormMasterDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FCurrentFormMasterDomain::FModelTask>>(this->AsShared());
    }
}

#if defined(_MSC_VER)
#pragma warning (pop)
#elif defined(__clang__)
#pragma clang diagnostic pop
#endif

