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

#include "MegaField/Domain/Model/CurrentFieldMaster.h"
#include "MegaField/Domain/Model/Namespace.h"
#include "MegaField/Domain/Model/AreaModel.h"
#include "MegaField/Domain/Model/AreaModelMaster.h"
#include "MegaField/Domain/Model/LayerModel.h"
#include "MegaField/Domain/Model/LayerModelMaster.h"
#include "MegaField/Domain/Model/CurrentFieldMaster.h"
#include "MegaField/Domain/Model/User.h"
#include "MegaField/Domain/Model/UserAccessToken.h"
#include "MegaField/Domain/Model/Spatial.h"
#include "MegaField/Domain/Model/SpatialAccessToken.h"

#include "Core/Domain/Gs2.h"
#include "Core/Domain/Transaction/JobQueueJobDomainFactory.h"
#include "Core/Domain/Transaction/InternalTransactionDomainFactory.h"
#include "Core/Domain/Transaction/ManualTransactionDomain.h"

namespace Gs2::MegaField::Domain::Model
{

    FCurrentFieldMasterDomain::FCurrentFieldMasterDomain(
        const Core::Domain::FGs2Ptr& Gs2,
        const MegaField::Domain::FGs2MegaFieldDomainPtr& Service,
        const TOptional<FString> NamespaceName
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Gs2(Gs2),
        Service(Service),
        Client(MakeShared<Gs2::MegaField::FGs2MegaFieldRestClient>(Gs2->RestSession)),
        NamespaceName(NamespaceName),
        ParentKey(Gs2::MegaField::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
            NamespaceName,
            "CurrentFieldMaster"
        ))
    {
    }

    FCurrentFieldMasterDomain::FCurrentFieldMasterDomain(
        const FCurrentFieldMasterDomain& From
    ):
        Gs2(From.Gs2),
        Service(From.Service),
        Client(From.Client),
        NamespaceName(From.NamespaceName),
        ParentKey(From.ParentKey)
    {

    }

    FCurrentFieldMasterDomain::FExportMasterTask::FExportMasterTask(
        const TSharedPtr<FCurrentFieldMasterDomain>& Self,
        const Request::FExportMasterRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FCurrentFieldMasterDomain::FExportMasterTask::FExportMasterTask(
        const FExportMasterTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FCurrentFieldMasterDomain::FExportMasterTask::Action(
        TSharedPtr<TSharedPtr<Gs2::MegaField::Domain::Model::FCurrentFieldMasterDomain>> Result
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
                const auto ParentKey = Gs2::MegaField::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
                    Self->NamespaceName,
                    "CurrentFieldMaster"
                );
                const auto Key = Gs2::MegaField::Domain::Model::FCurrentFieldMasterDomain::CreateCacheKey(
                );
                Self->Gs2->Cache->Put(
                    Gs2::MegaField::Model::FCurrentFieldMaster::TypeName,
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

    TSharedPtr<FAsyncTask<FCurrentFieldMasterDomain::FExportMasterTask>> FCurrentFieldMasterDomain::ExportMaster(
        Request::FExportMasterRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FExportMasterTask>>(this->AsShared(), Request);
    }

    FCurrentFieldMasterDomain::FGetTask::FGetTask(
        const TSharedPtr<FCurrentFieldMasterDomain>& Self,
        const Request::FGetCurrentFieldMasterRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FCurrentFieldMasterDomain::FGetTask::FGetTask(
        const FGetTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FCurrentFieldMasterDomain::FGetTask::Action(
        TSharedPtr<TSharedPtr<Gs2::MegaField::Model::FCurrentFieldMaster>> Result
    )
    {
        Request
            ->WithNamespaceName(Self->NamespaceName);
        const auto Future = Self->Client->GetCurrentFieldMaster(
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
                const auto ParentKey = Gs2::MegaField::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
                    Self->NamespaceName,
                    "CurrentFieldMaster"
                );
                const auto Key = Gs2::MegaField::Domain::Model::FCurrentFieldMasterDomain::CreateCacheKey(
                );
                Self->Gs2->Cache->Put(
                    Gs2::MegaField::Model::FCurrentFieldMaster::TypeName,
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

    TSharedPtr<FAsyncTask<FCurrentFieldMasterDomain::FGetTask>> FCurrentFieldMasterDomain::Get(
        Request::FGetCurrentFieldMasterRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FGetTask>>(this->AsShared(), Request);
    }

    FCurrentFieldMasterDomain::FUpdateTask::FUpdateTask(
        const TSharedPtr<FCurrentFieldMasterDomain>& Self,
        const Request::FUpdateCurrentFieldMasterRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FCurrentFieldMasterDomain::FUpdateTask::FUpdateTask(
        const FUpdateTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FCurrentFieldMasterDomain::FUpdateTask::Action(
        TSharedPtr<TSharedPtr<Gs2::MegaField::Domain::Model::FCurrentFieldMasterDomain>> Result
    )
    {
        Request
            ->WithNamespaceName(Self->NamespaceName);
        const auto Future = Self->Client->UpdateCurrentFieldMaster(
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
                const auto ParentKey = Gs2::MegaField::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
                    Self->NamespaceName,
                    "CurrentFieldMaster"
                );
                const auto Key = Gs2::MegaField::Domain::Model::FCurrentFieldMasterDomain::CreateCacheKey(
                );
                Self->Gs2->Cache->Put(
                    Gs2::MegaField::Model::FCurrentFieldMaster::TypeName,
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

    TSharedPtr<FAsyncTask<FCurrentFieldMasterDomain::FUpdateTask>> FCurrentFieldMasterDomain::Update(
        Request::FUpdateCurrentFieldMasterRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FUpdateTask>>(this->AsShared(), Request);
    }

    FCurrentFieldMasterDomain::FUpdateFromGitHubTask::FUpdateFromGitHubTask(
        const TSharedPtr<FCurrentFieldMasterDomain>& Self,
        const Request::FUpdateCurrentFieldMasterFromGitHubRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FCurrentFieldMasterDomain::FUpdateFromGitHubTask::FUpdateFromGitHubTask(
        const FUpdateFromGitHubTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FCurrentFieldMasterDomain::FUpdateFromGitHubTask::Action(
        TSharedPtr<TSharedPtr<Gs2::MegaField::Domain::Model::FCurrentFieldMasterDomain>> Result
    )
    {
        Request
            ->WithNamespaceName(Self->NamespaceName);
        const auto Future = Self->Client->UpdateCurrentFieldMasterFromGitHub(
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
                const auto ParentKey = Gs2::MegaField::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
                    Self->NamespaceName,
                    "CurrentFieldMaster"
                );
                const auto Key = Gs2::MegaField::Domain::Model::FCurrentFieldMasterDomain::CreateCacheKey(
                );
                Self->Gs2->Cache->Put(
                    Gs2::MegaField::Model::FCurrentFieldMaster::TypeName,
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

    TSharedPtr<FAsyncTask<FCurrentFieldMasterDomain::FUpdateFromGitHubTask>> FCurrentFieldMasterDomain::UpdateFromGitHub(
        Request::FUpdateCurrentFieldMasterFromGitHubRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FUpdateFromGitHubTask>>(this->AsShared(), Request);
    }

    FString FCurrentFieldMasterDomain::CreateCacheParentKey(
        TOptional<FString> NamespaceName,
        FString ChildType
    )
    {
        return FString("") +
            (NamespaceName.IsSet() ? *NamespaceName : "null") + ":" +
            ChildType;
    }

    FString FCurrentFieldMasterDomain::CreateCacheKey(
    )
    {
        return "Singleton";
    }

    FCurrentFieldMasterDomain::FModelTask::FModelTask(
        const TSharedPtr<FCurrentFieldMasterDomain> Self
    ): Self(Self)
    {

    }

    FCurrentFieldMasterDomain::FModelTask::FModelTask(
        const FModelTask& From
    ): TGs2Future(From), Self(From.Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FCurrentFieldMasterDomain::FModelTask::Action(
        TSharedPtr<TSharedPtr<Gs2::MegaField::Model::FCurrentFieldMaster>> Result
    )
    {
        // ReSharper disable once CppLocalVariableMayBeConst
        TSharedPtr<Gs2::MegaField::Model::FCurrentFieldMaster> Value;
        auto bCacheHit = Self->Gs2->Cache->TryGet<Gs2::MegaField::Model::FCurrentFieldMaster>(
            Self->ParentKey,
            Gs2::MegaField::Domain::Model::FCurrentFieldMasterDomain::CreateCacheKey(
            ),
            &Value
        );
        if (!bCacheHit) {
            const auto Future = Self->Get(
                MakeShared<Gs2::MegaField::Request::FGetCurrentFieldMasterRequest>()
            );
            Future->StartSynchronousTask();
            if (Future->GetTask().IsError())
            {
                if (Future->GetTask().Error()->Type() != Gs2::Core::Model::FNotFoundError::TypeString)
                {
                    return Future->GetTask().Error();
                }

                const auto Key = Gs2::MegaField::Domain::Model::FCurrentFieldMasterDomain::CreateCacheKey(
                );
                Self->Gs2->Cache->Put(
                    Gs2::MegaField::Model::FCurrentFieldMaster::TypeName,
                    Self->ParentKey,
                    Key,
                    nullptr,
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );

                if (Future->GetTask().Error()->Detail(0)->GetComponent() != "currentFieldMaster")
                {
                    return Future->GetTask().Error();
                }
            }
            Self->Gs2->Cache->TryGet<Gs2::MegaField::Model::FCurrentFieldMaster>(
                Self->ParentKey,
                Gs2::MegaField::Domain::Model::FCurrentFieldMasterDomain::CreateCacheKey(
                ),
                &Value
            );
            Future->EnsureCompletion();
        }
        *Result = Value;

        return nullptr;
    }

    TSharedPtr<FAsyncTask<FCurrentFieldMasterDomain::FModelTask>> FCurrentFieldMasterDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FCurrentFieldMasterDomain::FModelTask>>(this->AsShared());
    }

    Gs2::Core::Domain::CallbackID FCurrentFieldMasterDomain::Subscribe(
        TFunction<void(Gs2::MegaField::Model::FCurrentFieldMasterPtr)> Callback
    )
    {
        return Gs2->Cache->Subscribe(
            Gs2::MegaField::Model::FCurrentFieldMaster::TypeName,
            ParentKey,
            Gs2::MegaField::Domain::Model::FCurrentFieldMasterDomain::CreateCacheKey(
            ),
            [Callback](TSharedPtr<Gs2Object> obj)
            {
                Callback(StaticCastSharedPtr<Gs2::MegaField::Model::FCurrentFieldMaster>(obj));
            }
        );
    }

    void FCurrentFieldMasterDomain::Unsubscribe(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        Gs2->Cache->Unsubscribe(
            Gs2::MegaField::Model::FCurrentFieldMaster::TypeName,
            ParentKey,
            Gs2::MegaField::Domain::Model::FCurrentFieldMasterDomain::CreateCacheKey(
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

