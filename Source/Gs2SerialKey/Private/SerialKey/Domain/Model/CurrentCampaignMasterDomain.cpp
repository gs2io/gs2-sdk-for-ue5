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

#include "SerialKey/Domain/Model/CurrentCampaignMaster.h"
#include "SerialKey/Domain/Model/Namespace.h"
#include "SerialKey/Domain/Model/IssueJob.h"
#include "SerialKey/Domain/Model/SerialKey.h"
#include "SerialKey/Domain/Model/SerialKeyAccessToken.h"
#include "SerialKey/Domain/Model/User.h"
#include "SerialKey/Domain/Model/UserAccessToken.h"
#include "SerialKey/Domain/Model/CampaignModel.h"
#include "SerialKey/Domain/Model/CampaignModelMaster.h"
#include "SerialKey/Domain/Model/CurrentCampaignMaster.h"

#include "Core/Domain/Model/AutoStampSheetDomain.h"
#include "Core/Domain/Model/StampSheetDomain.h"

namespace Gs2::SerialKey::Domain::Model
{

    FCurrentCampaignMasterDomain::FCurrentCampaignMasterDomain(
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
        Client(MakeShared<Gs2::SerialKey::FGs2SerialKeyRestClient>(Session)),
        NamespaceName(NamespaceName),
        ParentKey(Gs2::SerialKey::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
            NamespaceName,
            "CurrentCampaignMaster"
        ))
    {
    }

    FCurrentCampaignMasterDomain::FCurrentCampaignMasterDomain(
        const FCurrentCampaignMasterDomain& From
    ):
        Cache(From.Cache),
        JobQueueDomain(From.JobQueueDomain),
        StampSheetConfiguration(From.StampSheetConfiguration),
        Session(From.Session),
        Client(From.Client)
    {

    }

    FCurrentCampaignMasterDomain::FExportMasterTask::FExportMasterTask(
        const TSharedPtr<FCurrentCampaignMasterDomain> Self,
        const Request::FExportMasterRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FCurrentCampaignMasterDomain::FExportMasterTask::FExportMasterTask(
        const FExportMasterTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FCurrentCampaignMasterDomain::FExportMasterTask::Action(
        TSharedPtr<TSharedPtr<Gs2::SerialKey::Domain::Model::FCurrentCampaignMasterDomain>> Result
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
                const auto ParentKey = Gs2::SerialKey::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
                    Self->NamespaceName,
                    "CurrentCampaignMaster"
                );
                const auto Key = Gs2::SerialKey::Domain::Model::FCurrentCampaignMasterDomain::CreateCacheKey(
                );
                Self->Cache->Put(
                    Gs2::SerialKey::Model::FCurrentCampaignMaster::TypeName,
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

    TSharedPtr<FAsyncTask<FCurrentCampaignMasterDomain::FExportMasterTask>> FCurrentCampaignMasterDomain::ExportMaster(
        Request::FExportMasterRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FExportMasterTask>>(this->AsShared(), Request);
    }

    FCurrentCampaignMasterDomain::FGetTask::FGetTask(
        const TSharedPtr<FCurrentCampaignMasterDomain> Self,
        const Request::FGetCurrentCampaignMasterRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FCurrentCampaignMasterDomain::FGetTask::FGetTask(
        const FGetTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FCurrentCampaignMasterDomain::FGetTask::Action(
        TSharedPtr<TSharedPtr<Gs2::SerialKey::Model::FCurrentCampaignMaster>> Result
    )
    {
        Request
            ->WithNamespaceName(Self->NamespaceName);
        const auto Future = Self->Client->GetCurrentCampaignMaster(
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
                const auto ParentKey = Gs2::SerialKey::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
                    Self->NamespaceName,
                    "CurrentCampaignMaster"
                );
                const auto Key = Gs2::SerialKey::Domain::Model::FCurrentCampaignMasterDomain::CreateCacheKey(
                );
                Self->Cache->Put(
                    Gs2::SerialKey::Model::FCurrentCampaignMaster::TypeName,
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

    TSharedPtr<FAsyncTask<FCurrentCampaignMasterDomain::FGetTask>> FCurrentCampaignMasterDomain::Get(
        Request::FGetCurrentCampaignMasterRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FGetTask>>(this->AsShared(), Request);
    }

    FCurrentCampaignMasterDomain::FUpdateTask::FUpdateTask(
        const TSharedPtr<FCurrentCampaignMasterDomain> Self,
        const Request::FUpdateCurrentCampaignMasterRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FCurrentCampaignMasterDomain::FUpdateTask::FUpdateTask(
        const FUpdateTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FCurrentCampaignMasterDomain::FUpdateTask::Action(
        TSharedPtr<TSharedPtr<Gs2::SerialKey::Domain::Model::FCurrentCampaignMasterDomain>> Result
    )
    {
        Request
            ->WithNamespaceName(Self->NamespaceName);
        const auto Future = Self->Client->UpdateCurrentCampaignMaster(
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
                const auto ParentKey = Gs2::SerialKey::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
                    Self->NamespaceName,
                    "CurrentCampaignMaster"
                );
                const auto Key = Gs2::SerialKey::Domain::Model::FCurrentCampaignMasterDomain::CreateCacheKey(
                );
                Self->Cache->Put(
                    Gs2::SerialKey::Model::FCurrentCampaignMaster::TypeName,
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

    TSharedPtr<FAsyncTask<FCurrentCampaignMasterDomain::FUpdateTask>> FCurrentCampaignMasterDomain::Update(
        Request::FUpdateCurrentCampaignMasterRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FUpdateTask>>(this->AsShared(), Request);
    }

    FCurrentCampaignMasterDomain::FUpdateFromGitHubTask::FUpdateFromGitHubTask(
        const TSharedPtr<FCurrentCampaignMasterDomain> Self,
        const Request::FUpdateCurrentCampaignMasterFromGitHubRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FCurrentCampaignMasterDomain::FUpdateFromGitHubTask::FUpdateFromGitHubTask(
        const FUpdateFromGitHubTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FCurrentCampaignMasterDomain::FUpdateFromGitHubTask::Action(
        TSharedPtr<TSharedPtr<Gs2::SerialKey::Domain::Model::FCurrentCampaignMasterDomain>> Result
    )
    {
        Request
            ->WithNamespaceName(Self->NamespaceName);
        const auto Future = Self->Client->UpdateCurrentCampaignMasterFromGitHub(
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
                const auto ParentKey = Gs2::SerialKey::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
                    Self->NamespaceName,
                    "CurrentCampaignMaster"
                );
                const auto Key = Gs2::SerialKey::Domain::Model::FCurrentCampaignMasterDomain::CreateCacheKey(
                );
                Self->Cache->Put(
                    Gs2::SerialKey::Model::FCurrentCampaignMaster::TypeName,
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

    TSharedPtr<FAsyncTask<FCurrentCampaignMasterDomain::FUpdateFromGitHubTask>> FCurrentCampaignMasterDomain::UpdateFromGitHub(
        Request::FUpdateCurrentCampaignMasterFromGitHubRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FUpdateFromGitHubTask>>(this->AsShared(), Request);
    }

    FString FCurrentCampaignMasterDomain::CreateCacheParentKey(
        TOptional<FString> NamespaceName,
        FString ChildType
    )
    {
        return FString() +
            (NamespaceName.IsSet() ? *NamespaceName : "null") + ":" +
            ChildType;
    }

    FString FCurrentCampaignMasterDomain::CreateCacheKey(
    )
    {
        return "Singleton";
    }

    FCurrentCampaignMasterDomain::FModelTask::FModelTask(
        const TSharedPtr<FCurrentCampaignMasterDomain> Self
    ): Self(Self)
    {

    }

    FCurrentCampaignMasterDomain::FModelTask::FModelTask(
        const FModelTask& From
    ): TGs2Future(From), Self(From.Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FCurrentCampaignMasterDomain::FModelTask::Action(
        TSharedPtr<TSharedPtr<Gs2::SerialKey::Model::FCurrentCampaignMaster>> Result
    )
    {
        // ReSharper disable once CppLocalVariableMayBeConst
        auto Value = Self->Cache->Get<Gs2::SerialKey::Model::FCurrentCampaignMaster>(
            Self->ParentKey,
            Gs2::SerialKey::Domain::Model::FCurrentCampaignMasterDomain::CreateCacheKey(
            )
        );
        if (Value == nullptr) {
            const auto Future = Self->Get(
                MakeShared<Gs2::SerialKey::Request::FGetCurrentCampaignMasterRequest>()
            );
            Future->StartSynchronousTask();
            if (Future->GetTask().IsError())
            {
                if (Future->GetTask().Error()->Type() == Gs2::Core::Model::FNotFoundError::TypeString)
                {
                    if (Future->GetTask().Error()->Detail(0)->GetComponent() == "currentCampaignMaster")
                    {
                        Self->Cache->Delete(
                            Gs2::SerialKey::Model::FCurrentCampaignMaster::TypeName,
                            Self->ParentKey,
                            Gs2::SerialKey::Domain::Model::FCurrentCampaignMasterDomain::CreateCacheKey(
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
            Value = Self->Cache->Get<Gs2::SerialKey::Model::FCurrentCampaignMaster>(
                Self->ParentKey,
                Gs2::SerialKey::Domain::Model::FCurrentCampaignMasterDomain::CreateCacheKey(
                )
            );
            Future->EnsureCompletion();
        }
        *Result = Value;

        return nullptr;
    }

    TSharedPtr<FAsyncTask<FCurrentCampaignMasterDomain::FModelTask>> FCurrentCampaignMasterDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FCurrentCampaignMasterDomain::FModelTask>>(this->AsShared());
    }
}

#if defined(_MSC_VER)
#pragma warning (pop)
#elif defined(__clang__)
#pragma clang diagnostic pop
#endif

