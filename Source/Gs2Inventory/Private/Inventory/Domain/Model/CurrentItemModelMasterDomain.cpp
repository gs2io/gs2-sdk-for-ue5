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

#include "Inventory/Domain/Model/CurrentItemModelMaster.h"
#include "Inventory/Domain/Model/Namespace.h"
#include "Inventory/Domain/Model/InventoryModelMaster.h"
#include "Inventory/Domain/Model/InventoryModel.h"
#include "Inventory/Domain/Model/ItemModelMaster.h"
#include "Inventory/Domain/Model/ItemModel.h"
#include "Inventory/Domain/Model/CurrentItemModelMaster.h"
#include "Inventory/Domain/Model/Inventory.h"
#include "Inventory/Domain/Model/InventoryAccessToken.h"
#include "Inventory/Domain/Model/ItemSet.h"
#include "Inventory/Domain/Model/ItemSetAccessToken.h"
#include "Inventory/Domain/Model/ReferenceOf.h"
#include "Inventory/Domain/Model/ReferenceOfAccessToken.h"
#include "Inventory/Domain/Model/User.h"
#include "Inventory/Domain/Model/UserAccessToken.h"
#include "Inventory/Domain/Model/ItemSetEntry.h"

#include "Core/Domain/Model/AutoStampSheetDomain.h"
#include "Core/Domain/Model/StampSheetDomain.h"

namespace Gs2::Inventory::Domain::Model
{

    FCurrentItemModelMasterDomain::FCurrentItemModelMasterDomain(
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
        Client(MakeShared<Gs2::Inventory::FGs2InventoryRestClient>(Session)),
        NamespaceName(NamespaceName),
        ParentKey(Gs2::Inventory::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
            NamespaceName,
            "CurrentItemModelMaster"
        ))
    {
    }

    FCurrentItemModelMasterDomain::FCurrentItemModelMasterDomain(
        const FCurrentItemModelMasterDomain& From
    ):
        Cache(From.Cache),
        JobQueueDomain(From.JobQueueDomain),
        StampSheetConfiguration(From.StampSheetConfiguration),
        Session(From.Session),
        Client(From.Client)
    {

    }

    FCurrentItemModelMasterDomain::FExportMasterTask::FExportMasterTask(
        const TSharedPtr<FCurrentItemModelMasterDomain> Self,
        const Request::FExportMasterRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FCurrentItemModelMasterDomain::FExportMasterTask::FExportMasterTask(
        const FExportMasterTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FCurrentItemModelMasterDomain::FExportMasterTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Inventory::Domain::Model::FCurrentItemModelMasterDomain>> Result
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
                const auto ParentKey = Gs2::Inventory::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
                    Self->NamespaceName,
                    "CurrentItemModelMaster"
                );
                const auto Key = Gs2::Inventory::Domain::Model::FCurrentItemModelMasterDomain::CreateCacheKey(
                );
                Self->Cache->Put(
                    Gs2::Inventory::Model::FCurrentItemModelMaster::TypeName,
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

    TSharedPtr<FAsyncTask<FCurrentItemModelMasterDomain::FExportMasterTask>> FCurrentItemModelMasterDomain::ExportMaster(
        Request::FExportMasterRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FExportMasterTask>>(this->AsShared(), Request);
    }

    FCurrentItemModelMasterDomain::FGetTask::FGetTask(
        const TSharedPtr<FCurrentItemModelMasterDomain> Self,
        const Request::FGetCurrentItemModelMasterRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FCurrentItemModelMasterDomain::FGetTask::FGetTask(
        const FGetTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FCurrentItemModelMasterDomain::FGetTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Inventory::Model::FCurrentItemModelMaster>> Result
    )
    {
        Request
            ->WithNamespaceName(Self->NamespaceName);
        const auto Future = Self->Client->GetCurrentItemModelMaster(
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
                const auto ParentKey = Gs2::Inventory::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
                    Self->NamespaceName,
                    "CurrentItemModelMaster"
                );
                const auto Key = Gs2::Inventory::Domain::Model::FCurrentItemModelMasterDomain::CreateCacheKey(
                );
                Self->Cache->Put(
                    Gs2::Inventory::Model::FCurrentItemModelMaster::TypeName,
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

    TSharedPtr<FAsyncTask<FCurrentItemModelMasterDomain::FGetTask>> FCurrentItemModelMasterDomain::Get(
        Request::FGetCurrentItemModelMasterRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FGetTask>>(this->AsShared(), Request);
    }

    FCurrentItemModelMasterDomain::FUpdateTask::FUpdateTask(
        const TSharedPtr<FCurrentItemModelMasterDomain> Self,
        const Request::FUpdateCurrentItemModelMasterRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FCurrentItemModelMasterDomain::FUpdateTask::FUpdateTask(
        const FUpdateTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FCurrentItemModelMasterDomain::FUpdateTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Inventory::Domain::Model::FCurrentItemModelMasterDomain>> Result
    )
    {
        Request
            ->WithNamespaceName(Self->NamespaceName);
        const auto Future = Self->Client->UpdateCurrentItemModelMaster(
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
                const auto ParentKey = Gs2::Inventory::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
                    Self->NamespaceName,
                    "CurrentItemModelMaster"
                );
                const auto Key = Gs2::Inventory::Domain::Model::FCurrentItemModelMasterDomain::CreateCacheKey(
                );
                Self->Cache->Put(
                    Gs2::Inventory::Model::FCurrentItemModelMaster::TypeName,
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

    TSharedPtr<FAsyncTask<FCurrentItemModelMasterDomain::FUpdateTask>> FCurrentItemModelMasterDomain::Update(
        Request::FUpdateCurrentItemModelMasterRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FUpdateTask>>(this->AsShared(), Request);
    }

    FCurrentItemModelMasterDomain::FUpdateFromGitHubTask::FUpdateFromGitHubTask(
        const TSharedPtr<FCurrentItemModelMasterDomain> Self,
        const Request::FUpdateCurrentItemModelMasterFromGitHubRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FCurrentItemModelMasterDomain::FUpdateFromGitHubTask::FUpdateFromGitHubTask(
        const FUpdateFromGitHubTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FCurrentItemModelMasterDomain::FUpdateFromGitHubTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Inventory::Domain::Model::FCurrentItemModelMasterDomain>> Result
    )
    {
        Request
            ->WithNamespaceName(Self->NamespaceName);
        const auto Future = Self->Client->UpdateCurrentItemModelMasterFromGitHub(
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
                const auto ParentKey = Gs2::Inventory::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
                    Self->NamespaceName,
                    "CurrentItemModelMaster"
                );
                const auto Key = Gs2::Inventory::Domain::Model::FCurrentItemModelMasterDomain::CreateCacheKey(
                );
                Self->Cache->Put(
                    Gs2::Inventory::Model::FCurrentItemModelMaster::TypeName,
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

    TSharedPtr<FAsyncTask<FCurrentItemModelMasterDomain::FUpdateFromGitHubTask>> FCurrentItemModelMasterDomain::UpdateFromGitHub(
        Request::FUpdateCurrentItemModelMasterFromGitHubRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FUpdateFromGitHubTask>>(this->AsShared(), Request);
    }

    FString FCurrentItemModelMasterDomain::CreateCacheParentKey(
        TOptional<FString> NamespaceName,
        FString ChildType
    )
    {
        return FString() +
            (NamespaceName.IsSet() ? *NamespaceName : "null") + ":" +
            ChildType;
    }

    FString FCurrentItemModelMasterDomain::CreateCacheKey(
    )
    {
        return "Singleton";
    }

    FCurrentItemModelMasterDomain::FModelTask::FModelTask(
        const TSharedPtr<FCurrentItemModelMasterDomain> Self
    ): Self(Self)
    {

    }

    FCurrentItemModelMasterDomain::FModelTask::FModelTask(
        const FModelTask& From
    ): TGs2Future(From), Self(From.Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FCurrentItemModelMasterDomain::FModelTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Inventory::Model::FCurrentItemModelMaster>> Result
    )
    {
        // ReSharper disable once CppLocalVariableMayBeConst
        TSharedPtr<Gs2::Inventory::Model::FCurrentItemModelMaster> Value;
        auto bCacheHit = Self->Cache->TryGet<Gs2::Inventory::Model::FCurrentItemModelMaster>(
            Self->ParentKey,
            Gs2::Inventory::Domain::Model::FCurrentItemModelMasterDomain::CreateCacheKey(
            ),
            &Value
        );
        if (!bCacheHit) {
            const auto Future = Self->Get(
                MakeShared<Gs2::Inventory::Request::FGetCurrentItemModelMasterRequest>()
            );
            Future->StartSynchronousTask();
            if (Future->GetTask().IsError())
            {
                if (Future->GetTask().Error()->Type() != Gs2::Core::Model::FNotFoundError::TypeString)
                {
                    return Future->GetTask().Error();
                }

                const auto Key = Gs2::Inventory::Domain::Model::FCurrentItemModelMasterDomain::CreateCacheKey(
                );
                Self->Cache->Put(
                    Gs2::Inventory::Model::FCurrentItemModelMaster::TypeName,
                    Self->ParentKey,
                    Key,
                    nullptr,
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );

                if (Future->GetTask().Error()->Detail(0)->GetComponent() != "currentItemModelMaster")
                {
                    return Future->GetTask().Error();
                }
            }
            Self->Cache->TryGet<Gs2::Inventory::Model::FCurrentItemModelMaster>(
                Self->ParentKey,
                Gs2::Inventory::Domain::Model::FCurrentItemModelMasterDomain::CreateCacheKey(
                ),
                &Value
            );
            Future->EnsureCompletion();
        }
        *Result = Value;

        return nullptr;
    }

    TSharedPtr<FAsyncTask<FCurrentItemModelMasterDomain::FModelTask>> FCurrentItemModelMasterDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FCurrentItemModelMasterDomain::FModelTask>>(this->AsShared());
    }
}

#if defined(_MSC_VER)
#pragma warning (pop)
#elif defined(__clang__)
#pragma clang diagnostic pop
#endif

