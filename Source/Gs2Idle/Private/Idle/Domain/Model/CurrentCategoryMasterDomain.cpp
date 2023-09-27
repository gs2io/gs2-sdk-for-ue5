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

#include "Idle/Domain/Model/CurrentCategoryMaster.h"
#include "Idle/Domain/Model/Namespace.h"
#include "Idle/Domain/Model/CategoryModelMaster.h"
#include "Idle/Domain/Model/CategoryModel.h"
#include "Idle/Domain/Model/User.h"
#include "Idle/Domain/Model/UserAccessToken.h"
#include "Idle/Domain/Model/Status.h"
#include "Idle/Domain/Model/StatusAccessToken.h"
#include "Idle/Domain/Model/CurrentCategoryMaster.h"

#include "Core/Domain/Model/AutoStampSheetDomain.h"
#include "Core/Domain/Model/StampSheetDomain.h"

namespace Gs2::Idle::Domain::Model
{

    FCurrentCategoryMasterDomain::FCurrentCategoryMasterDomain(
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
        Client(MakeShared<Gs2::Idle::FGs2IdleRestClient>(Session)),
        NamespaceName(NamespaceName),
        ParentKey(Gs2::Idle::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
            NamespaceName,
            "CurrentCategoryMaster"
        ))
    {
    }

    FCurrentCategoryMasterDomain::FCurrentCategoryMasterDomain(
        const FCurrentCategoryMasterDomain& From
    ):
        Cache(From.Cache),
        JobQueueDomain(From.JobQueueDomain),
        StampSheetConfiguration(From.StampSheetConfiguration),
        Session(From.Session),
        Client(From.Client),
        NamespaceName(From.NamespaceName),
        ParentKey(From.ParentKey)
    {

    }

    FCurrentCategoryMasterDomain::FExportMasterTask::FExportMasterTask(
        const TSharedPtr<FCurrentCategoryMasterDomain> Self,
        const Request::FExportMasterRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FCurrentCategoryMasterDomain::FExportMasterTask::FExportMasterTask(
        const FExportMasterTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FCurrentCategoryMasterDomain::FExportMasterTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Idle::Domain::Model::FCurrentCategoryMasterDomain>> Result
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
                const auto ParentKey = Gs2::Idle::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
                    Self->NamespaceName,
                    "CurrentCategoryMaster"
                );
                const auto Key = Gs2::Idle::Domain::Model::FCurrentCategoryMasterDomain::CreateCacheKey(
                );
                Self->Cache->Put(
                    Gs2::Idle::Model::FCurrentCategoryMaster::TypeName,
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

    TSharedPtr<FAsyncTask<FCurrentCategoryMasterDomain::FExportMasterTask>> FCurrentCategoryMasterDomain::ExportMaster(
        Request::FExportMasterRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FExportMasterTask>>(this->AsShared(), Request);
    }

    FCurrentCategoryMasterDomain::FGetTask::FGetTask(
        const TSharedPtr<FCurrentCategoryMasterDomain> Self,
        const Request::FGetCurrentCategoryMasterRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FCurrentCategoryMasterDomain::FGetTask::FGetTask(
        const FGetTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FCurrentCategoryMasterDomain::FGetTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Idle::Model::FCurrentCategoryMaster>> Result
    )
    {
        Request
            ->WithNamespaceName(Self->NamespaceName);
        const auto Future = Self->Client->GetCurrentCategoryMaster(
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
                const auto ParentKey = Gs2::Idle::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
                    Self->NamespaceName,
                    "CurrentCategoryMaster"
                );
                const auto Key = Gs2::Idle::Domain::Model::FCurrentCategoryMasterDomain::CreateCacheKey(
                );
                Self->Cache->Put(
                    Gs2::Idle::Model::FCurrentCategoryMaster::TypeName,
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

    TSharedPtr<FAsyncTask<FCurrentCategoryMasterDomain::FGetTask>> FCurrentCategoryMasterDomain::Get(
        Request::FGetCurrentCategoryMasterRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FGetTask>>(this->AsShared(), Request);
    }

    FCurrentCategoryMasterDomain::FUpdateTask::FUpdateTask(
        const TSharedPtr<FCurrentCategoryMasterDomain> Self,
        const Request::FUpdateCurrentCategoryMasterRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FCurrentCategoryMasterDomain::FUpdateTask::FUpdateTask(
        const FUpdateTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FCurrentCategoryMasterDomain::FUpdateTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Idle::Domain::Model::FCurrentCategoryMasterDomain>> Result
    )
    {
        Request
            ->WithNamespaceName(Self->NamespaceName);
        const auto Future = Self->Client->UpdateCurrentCategoryMaster(
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
                const auto ParentKey = Gs2::Idle::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
                    Self->NamespaceName,
                    "CurrentCategoryMaster"
                );
                const auto Key = Gs2::Idle::Domain::Model::FCurrentCategoryMasterDomain::CreateCacheKey(
                );
                Self->Cache->Put(
                    Gs2::Idle::Model::FCurrentCategoryMaster::TypeName,
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

    TSharedPtr<FAsyncTask<FCurrentCategoryMasterDomain::FUpdateTask>> FCurrentCategoryMasterDomain::Update(
        Request::FUpdateCurrentCategoryMasterRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FUpdateTask>>(this->AsShared(), Request);
    }

    FCurrentCategoryMasterDomain::FUpdateFromGitHubTask::FUpdateFromGitHubTask(
        const TSharedPtr<FCurrentCategoryMasterDomain> Self,
        const Request::FUpdateCurrentCategoryMasterFromGitHubRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FCurrentCategoryMasterDomain::FUpdateFromGitHubTask::FUpdateFromGitHubTask(
        const FUpdateFromGitHubTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FCurrentCategoryMasterDomain::FUpdateFromGitHubTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Idle::Domain::Model::FCurrentCategoryMasterDomain>> Result
    )
    {
        Request
            ->WithNamespaceName(Self->NamespaceName);
        const auto Future = Self->Client->UpdateCurrentCategoryMasterFromGitHub(
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
                const auto ParentKey = Gs2::Idle::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
                    Self->NamespaceName,
                    "CurrentCategoryMaster"
                );
                const auto Key = Gs2::Idle::Domain::Model::FCurrentCategoryMasterDomain::CreateCacheKey(
                );
                Self->Cache->Put(
                    Gs2::Idle::Model::FCurrentCategoryMaster::TypeName,
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

    TSharedPtr<FAsyncTask<FCurrentCategoryMasterDomain::FUpdateFromGitHubTask>> FCurrentCategoryMasterDomain::UpdateFromGitHub(
        Request::FUpdateCurrentCategoryMasterFromGitHubRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FUpdateFromGitHubTask>>(this->AsShared(), Request);
    }

    FString FCurrentCategoryMasterDomain::CreateCacheParentKey(
        TOptional<FString> NamespaceName,
        FString ChildType
    )
    {
        return FString("") +
            (NamespaceName.IsSet() ? *NamespaceName : "null") + ":" +
            ChildType;
    }

    FString FCurrentCategoryMasterDomain::CreateCacheKey(
    )
    {
        return "Singleton";
    }

    FCurrentCategoryMasterDomain::FModelTask::FModelTask(
        const TSharedPtr<FCurrentCategoryMasterDomain> Self
    ): Self(Self)
    {

    }

    FCurrentCategoryMasterDomain::FModelTask::FModelTask(
        const FModelTask& From
    ): TGs2Future(From), Self(From.Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FCurrentCategoryMasterDomain::FModelTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Idle::Model::FCurrentCategoryMaster>> Result
    )
    {
        // ReSharper disable once CppLocalVariableMayBeConst
        TSharedPtr<Gs2::Idle::Model::FCurrentCategoryMaster> Value;
        auto bCacheHit = Self->Cache->TryGet<Gs2::Idle::Model::FCurrentCategoryMaster>(
            Self->ParentKey,
            Gs2::Idle::Domain::Model::FCurrentCategoryMasterDomain::CreateCacheKey(
            ),
            &Value
        );
        if (!bCacheHit) {
            const auto Future = Self->Get(
                MakeShared<Gs2::Idle::Request::FGetCurrentCategoryMasterRequest>()
            );
            Future->StartSynchronousTask();
            if (Future->GetTask().IsError())
            {
                if (Future->GetTask().Error()->Type() != Gs2::Core::Model::FNotFoundError::TypeString)
                {
                    return Future->GetTask().Error();
                }

                const auto Key = Gs2::Idle::Domain::Model::FCurrentCategoryMasterDomain::CreateCacheKey(
                );
                Self->Cache->Put(
                    Gs2::Idle::Model::FCurrentCategoryMaster::TypeName,
                    Self->ParentKey,
                    Key,
                    nullptr,
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );

                if (Future->GetTask().Error()->Detail(0)->GetComponent() != "currentCategoryMaster")
                {
                    return Future->GetTask().Error();
                }
            }
            Self->Cache->TryGet<Gs2::Idle::Model::FCurrentCategoryMaster>(
                Self->ParentKey,
                Gs2::Idle::Domain::Model::FCurrentCategoryMasterDomain::CreateCacheKey(
                ),
                &Value
            );
            Future->EnsureCompletion();
        }
        *Result = Value;

        return nullptr;
    }

    TSharedPtr<FAsyncTask<FCurrentCategoryMasterDomain::FModelTask>> FCurrentCategoryMasterDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FCurrentCategoryMasterDomain::FModelTask>>(this->AsShared());
    }

    Gs2::Core::Domain::CallbackID FCurrentCategoryMasterDomain::Subscribe(
        TFunction<void(Gs2::Idle::Model::FCurrentCategoryMasterPtr)> Callback
    )
    {
        return Cache->Subscribe(
            Gs2::Idle::Model::FCurrentCategoryMaster::TypeName,
            ParentKey,
            Gs2::Idle::Domain::Model::FCurrentCategoryMasterDomain::CreateCacheKey(
            ),
            [Callback](TSharedPtr<Gs2Object> obj)
            {
                Callback(StaticCastSharedPtr<Gs2::Idle::Model::FCurrentCategoryMaster>(obj));
            }
        );
    }

    void FCurrentCategoryMasterDomain::Unsubscribe(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        Cache->Unsubscribe(
            Gs2::Idle::Model::FCurrentCategoryMaster::TypeName,
            ParentKey,
            Gs2::Idle::Domain::Model::FCurrentCategoryMasterDomain::CreateCacheKey(
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

