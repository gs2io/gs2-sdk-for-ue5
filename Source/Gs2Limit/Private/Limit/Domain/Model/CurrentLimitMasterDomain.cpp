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

#include "Core/Domain/Gs2.h"
#include "Core/Domain/Transaction/JobQueueJobDomainFactory.h"
#include "Core/Domain/Transaction/InternalTransactionDomainFactory.h"
#include "Core/Domain/Transaction/ManualTransactionDomain.h"

namespace Gs2::Limit::Domain::Model
{

    FCurrentLimitMasterDomain::FCurrentLimitMasterDomain(
        const Core::Domain::FGs2Ptr& Gs2,
        const Limit::Domain::FGs2LimitDomainPtr& Service,
        const TOptional<FString> NamespaceName
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Gs2(Gs2),
        Service(Service),
        Client(MakeShared<Gs2::Limit::FGs2LimitRestClient>(Gs2->RestSession)),
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
        Gs2(From.Gs2),
        Service(From.Service),
        Client(From.Client),
        NamespaceName(From.NamespaceName),
        ParentKey(From.ParentKey)
    {

    }

    FCurrentLimitMasterDomain::FExportMasterTask::FExportMasterTask(
        const TSharedPtr<FCurrentLimitMasterDomain>& Self,
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
            ->WithContextStack(Self->Gs2->DefaultContextStack)
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
                Self->Gs2->Cache->Put(
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
        const TSharedPtr<FCurrentLimitMasterDomain>& Self,
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
            ->WithContextStack(Self->Gs2->DefaultContextStack)
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
                Self->Gs2->Cache->Put(
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
        const TSharedPtr<FCurrentLimitMasterDomain>& Self,
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
            ->WithContextStack(Self->Gs2->DefaultContextStack)
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
                Self->Gs2->Cache->Put(
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
        const TSharedPtr<FCurrentLimitMasterDomain>& Self,
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
            ->WithContextStack(Self->Gs2->DefaultContextStack)
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
                Self->Gs2->Cache->Put(
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
        return FString("") +
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
        TSharedPtr<Gs2::Limit::Model::FCurrentLimitMaster> Value;
        auto bCacheHit = Self->Gs2->Cache->TryGet<Gs2::Limit::Model::FCurrentLimitMaster>(
            Self->ParentKey,
            Gs2::Limit::Domain::Model::FCurrentLimitMasterDomain::CreateCacheKey(
            ),
            &Value
        );
        if (!bCacheHit) {
            const auto Future = Self->Get(
                MakeShared<Gs2::Limit::Request::FGetCurrentLimitMasterRequest>()
            );
            Future->StartSynchronousTask();
            if (Future->GetTask().IsError())
            {
                if (Future->GetTask().Error()->Type() != Gs2::Core::Model::FNotFoundError::TypeString)
                {
                    return Future->GetTask().Error();
                }

                const auto Key = Gs2::Limit::Domain::Model::FCurrentLimitMasterDomain::CreateCacheKey(
                );
                Self->Gs2->Cache->Put(
                    Gs2::Limit::Model::FCurrentLimitMaster::TypeName,
                    Self->ParentKey,
                    Key,
                    nullptr,
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );

                if (Future->GetTask().Error()->Detail(0)->GetComponent() != "currentLimitMaster")
                {
                    return Future->GetTask().Error();
                }
            }
            Self->Gs2->Cache->TryGet<Gs2::Limit::Model::FCurrentLimitMaster>(
                Self->ParentKey,
                Gs2::Limit::Domain::Model::FCurrentLimitMasterDomain::CreateCacheKey(
                ),
                &Value
            );
            Future->EnsureCompletion();
        }
        *Result = Value;

        return nullptr;
    }

    TSharedPtr<FAsyncTask<FCurrentLimitMasterDomain::FModelTask>> FCurrentLimitMasterDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FCurrentLimitMasterDomain::FModelTask>>(this->AsShared());
    }

    Gs2::Core::Domain::CallbackID FCurrentLimitMasterDomain::Subscribe(
        TFunction<void(Gs2::Limit::Model::FCurrentLimitMasterPtr)> Callback
    )
    {
        return Gs2->Cache->Subscribe(
            Gs2::Limit::Model::FCurrentLimitMaster::TypeName,
            ParentKey,
            Gs2::Limit::Domain::Model::FCurrentLimitMasterDomain::CreateCacheKey(
            ),
            [Callback](TSharedPtr<FGs2Object> obj)
            {
                Callback(StaticCastSharedPtr<Gs2::Limit::Model::FCurrentLimitMaster>(obj));
            }
        );
    }

    void FCurrentLimitMasterDomain::Unsubscribe(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        Gs2->Cache->Unsubscribe(
            Gs2::Limit::Model::FCurrentLimitMaster::TypeName,
            ParentKey,
            Gs2::Limit::Domain::Model::FCurrentLimitMasterDomain::CreateCacheKey(
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

