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

#include "Money2/Domain/Model/CurrentModelMaster.h"
#include "Money2/Domain/Model/Namespace.h"
#include "Money2/Domain/Model/User.h"
#include "Money2/Domain/Model/UserAccessToken.h"
#include "Money2/Domain/Model/Wallet.h"
#include "Money2/Domain/Model/WalletAccessToken.h"
#include "Money2/Domain/Model/Event.h"
#include "Money2/Domain/Model/EventAccessToken.h"
#include "Money2/Domain/Model/StoreContentModel.h"
#include "Money2/Domain/Model/StoreContentModelMaster.h"
#include "Money2/Domain/Model/CurrentModelMaster.h"
#include "Money2/Domain/Model/DailyTransactionHistory.h"
#include "Money2/Domain/Model/UnusedBalance.h"

#include "Core/Domain/Gs2.h"
#include "Core/Domain/Transaction/JobQueueJobDomainFactory.h"
#include "Core/Domain/Transaction/InternalTransactionDomainFactory.h"
#include "Core/Domain/Transaction/ManualTransactionDomain.h"

namespace Gs2::Money2::Domain::Model
{

    FCurrentModelMasterDomain::FCurrentModelMasterDomain(
        const Core::Domain::FGs2Ptr& Gs2,
        const Money2::Domain::FGs2Money2DomainPtr& Service,
        const TOptional<FString> NamespaceName
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Gs2(Gs2),
        Service(Service),
        Client(MakeShared<Gs2::Money2::FGs2Money2RestClient>(Gs2->RestSession)),
        NamespaceName(NamespaceName),
        ParentKey(Gs2::Money2::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
            NamespaceName,
            "CurrentModelMaster"
        ))
    {
    }

    FCurrentModelMasterDomain::FCurrentModelMasterDomain(
        const FCurrentModelMasterDomain& From
    ):
        Gs2(From.Gs2),
        Service(From.Service),
        Client(From.Client),
        NamespaceName(From.NamespaceName),
        ParentKey(From.ParentKey)
    {

    }

    FCurrentModelMasterDomain::FExportMasterTask::FExportMasterTask(
        const TSharedPtr<FCurrentModelMasterDomain>& Self,
        const Request::FExportMasterRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FCurrentModelMasterDomain::FExportMasterTask::FExportMasterTask(
        const FExportMasterTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FCurrentModelMasterDomain::FExportMasterTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Money2::Domain::Model::FCurrentModelMasterDomain>> Result
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
                const auto ParentKey = Gs2::Money2::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
                    Self->NamespaceName,
                    "CurrentModelMaster"
                );
                const auto Key = Gs2::Money2::Domain::Model::FCurrentModelMasterDomain::CreateCacheKey(
                );
                Self->Gs2->Cache->Put(
                    Gs2::Money2::Model::FCurrentModelMaster::TypeName,
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

    TSharedPtr<FAsyncTask<FCurrentModelMasterDomain::FExportMasterTask>> FCurrentModelMasterDomain::ExportMaster(
        Request::FExportMasterRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FExportMasterTask>>(this->AsShared(), Request);
    }

    FCurrentModelMasterDomain::FGetTask::FGetTask(
        const TSharedPtr<FCurrentModelMasterDomain>& Self,
        const Request::FGetCurrentModelMasterRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FCurrentModelMasterDomain::FGetTask::FGetTask(
        const FGetTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FCurrentModelMasterDomain::FGetTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Money2::Model::FCurrentModelMaster>> Result
    )
    {
        Request
            ->WithContextStack(Self->Gs2->DefaultContextStack)
            ->WithNamespaceName(Self->NamespaceName);
        const auto Future = Self->Client->GetCurrentModelMaster(
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
                const auto ParentKey = Gs2::Money2::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
                    Self->NamespaceName,
                    "CurrentModelMaster"
                );
                const auto Key = Gs2::Money2::Domain::Model::FCurrentModelMasterDomain::CreateCacheKey(
                );
                Self->Gs2->Cache->Put(
                    Gs2::Money2::Model::FCurrentModelMaster::TypeName,
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

    TSharedPtr<FAsyncTask<FCurrentModelMasterDomain::FGetTask>> FCurrentModelMasterDomain::Get(
        Request::FGetCurrentModelMasterRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FGetTask>>(this->AsShared(), Request);
    }

    FCurrentModelMasterDomain::FUpdateTask::FUpdateTask(
        const TSharedPtr<FCurrentModelMasterDomain>& Self,
        const Request::FUpdateCurrentModelMasterRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FCurrentModelMasterDomain::FUpdateTask::FUpdateTask(
        const FUpdateTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FCurrentModelMasterDomain::FUpdateTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Money2::Domain::Model::FCurrentModelMasterDomain>> Result
    )
    {
        Request
            ->WithContextStack(Self->Gs2->DefaultContextStack)
            ->WithNamespaceName(Self->NamespaceName);
        const auto Future = Self->Client->UpdateCurrentModelMaster(
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
                const auto ParentKey = Gs2::Money2::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
                    Self->NamespaceName,
                    "CurrentModelMaster"
                );
                const auto Key = Gs2::Money2::Domain::Model::FCurrentModelMasterDomain::CreateCacheKey(
                );
                Self->Gs2->Cache->Put(
                    Gs2::Money2::Model::FCurrentModelMaster::TypeName,
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

    TSharedPtr<FAsyncTask<FCurrentModelMasterDomain::FUpdateTask>> FCurrentModelMasterDomain::Update(
        Request::FUpdateCurrentModelMasterRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FUpdateTask>>(this->AsShared(), Request);
    }

    FCurrentModelMasterDomain::FUpdateFromGitHubTask::FUpdateFromGitHubTask(
        const TSharedPtr<FCurrentModelMasterDomain>& Self,
        const Request::FUpdateCurrentModelMasterFromGitHubRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FCurrentModelMasterDomain::FUpdateFromGitHubTask::FUpdateFromGitHubTask(
        const FUpdateFromGitHubTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FCurrentModelMasterDomain::FUpdateFromGitHubTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Money2::Domain::Model::FCurrentModelMasterDomain>> Result
    )
    {
        Request
            ->WithContextStack(Self->Gs2->DefaultContextStack)
            ->WithNamespaceName(Self->NamespaceName);
        const auto Future = Self->Client->UpdateCurrentModelMasterFromGitHub(
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
                const auto ParentKey = Gs2::Money2::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
                    Self->NamespaceName,
                    "CurrentModelMaster"
                );
                const auto Key = Gs2::Money2::Domain::Model::FCurrentModelMasterDomain::CreateCacheKey(
                );
                Self->Gs2->Cache->Put(
                    Gs2::Money2::Model::FCurrentModelMaster::TypeName,
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

    TSharedPtr<FAsyncTask<FCurrentModelMasterDomain::FUpdateFromGitHubTask>> FCurrentModelMasterDomain::UpdateFromGitHub(
        Request::FUpdateCurrentModelMasterFromGitHubRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FUpdateFromGitHubTask>>(this->AsShared(), Request);
    }

    FString FCurrentModelMasterDomain::CreateCacheParentKey(
        TOptional<FString> NamespaceName,
        FString ChildType
    )
    {
        return FString("") +
            (NamespaceName.IsSet() ? *NamespaceName : "null") + ":" +
            ChildType;
    }

    FString FCurrentModelMasterDomain::CreateCacheKey(
    )
    {
        return "Singleton";
    }

    FCurrentModelMasterDomain::FModelTask::FModelTask(
        const TSharedPtr<FCurrentModelMasterDomain> Self
    ): Self(Self)
    {

    }

    FCurrentModelMasterDomain::FModelTask::FModelTask(
        const FModelTask& From
    ): TGs2Future(From), Self(From.Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FCurrentModelMasterDomain::FModelTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Money2::Model::FCurrentModelMaster>> Result
    )
    {
        // ReSharper disable once CppLocalVariableMayBeConst
        TSharedPtr<Gs2::Money2::Model::FCurrentModelMaster> Value;
        auto bCacheHit = Self->Gs2->Cache->TryGet<Gs2::Money2::Model::FCurrentModelMaster>(
            Self->ParentKey,
            Gs2::Money2::Domain::Model::FCurrentModelMasterDomain::CreateCacheKey(
            ),
            &Value
        );
        if (!bCacheHit) {
            const auto Future = Self->Get(
                MakeShared<Gs2::Money2::Request::FGetCurrentModelMasterRequest>()
            );
            Future->StartSynchronousTask();
            if (Future->GetTask().IsError())
            {
                if (Future->GetTask().Error()->Type() != Gs2::Core::Model::FNotFoundError::TypeString)
                {
                    return Future->GetTask().Error();
                }

                const auto Key = Gs2::Money2::Domain::Model::FCurrentModelMasterDomain::CreateCacheKey(
                );
                Self->Gs2->Cache->Put(
                    Gs2::Money2::Model::FCurrentModelMaster::TypeName,
                    Self->ParentKey,
                    Key,
                    nullptr,
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );

                if (Future->GetTask().Error()->Detail(0)->GetComponent() != "currentModelMaster")
                {
                    return Future->GetTask().Error();
                }
            }
            Self->Gs2->Cache->TryGet<Gs2::Money2::Model::FCurrentModelMaster>(
                Self->ParentKey,
                Gs2::Money2::Domain::Model::FCurrentModelMasterDomain::CreateCacheKey(
                ),
                &Value
            );
            Future->EnsureCompletion();
        }
        *Result = Value;

        return nullptr;
    }

    TSharedPtr<FAsyncTask<FCurrentModelMasterDomain::FModelTask>> FCurrentModelMasterDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FCurrentModelMasterDomain::FModelTask>>(this->AsShared());
    }

    Gs2::Core::Domain::CallbackID FCurrentModelMasterDomain::Subscribe(
        TFunction<void(Gs2::Money2::Model::FCurrentModelMasterPtr)> Callback
    )
    {
        return Gs2->Cache->Subscribe(
            Gs2::Money2::Model::FCurrentModelMaster::TypeName,
            ParentKey,
            Gs2::Money2::Domain::Model::FCurrentModelMasterDomain::CreateCacheKey(
            ),
            [Callback](TSharedPtr<FGs2Object> obj)
            {
                Callback(StaticCastSharedPtr<Gs2::Money2::Model::FCurrentModelMaster>(obj));
            }
        );
    }

    void FCurrentModelMasterDomain::Unsubscribe(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        Gs2->Cache->Unsubscribe(
            Gs2::Money2::Model::FCurrentModelMaster::TypeName,
            ParentKey,
            Gs2::Money2::Domain::Model::FCurrentModelMasterDomain::CreateCacheKey(
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

