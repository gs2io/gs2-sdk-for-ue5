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

#include "Showcase/Domain/Model/CurrentShowcaseMaster.h"
#include "Showcase/Domain/Model/Namespace.h"
#include "Showcase/Domain/Model/SalesItemMaster.h"
#include "Showcase/Domain/Model/SalesItemGroupMaster.h"
#include "Showcase/Domain/Model/ShowcaseMaster.h"
#include "Showcase/Domain/Model/CurrentShowcaseMaster.h"
#include "Showcase/Domain/Model/Showcase.h"
#include "Showcase/Domain/Model/ShowcaseAccessToken.h"
#include "Showcase/Domain/Model/DisplayItem.h"
#include "Showcase/Domain/Model/DisplayItemAccessToken.h"
#include "Showcase/Domain/Model/RandomShowcaseMaster.h"
#include "Showcase/Domain/Model/RandomShowcase.h"
#include "Showcase/Domain/Model/RandomShowcaseAccessToken.h"
#include "Showcase/Domain/Model/User.h"
#include "Showcase/Domain/Model/UserAccessToken.h"
#include "Showcase/Domain/Model/RandomShowcaseStatus.h"
#include "Showcase/Domain/Model/RandomShowcaseStatusAccessToken.h"
#include "Showcase/Domain/Model/RandomDisplayItem.h"
#include "Showcase/Domain/Model/RandomDisplayItemAccessToken.h"

#include "Core/Domain/Model/AutoStampSheetDomain.h"
#include "Core/Domain/Model/StampSheetDomain.h"

namespace Gs2::Showcase::Domain::Model
{

    FCurrentShowcaseMasterDomain::FCurrentShowcaseMasterDomain(
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
        Client(MakeShared<Gs2::Showcase::FGs2ShowcaseRestClient>(Session)),
        NamespaceName(NamespaceName),
        ParentKey(Gs2::Showcase::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
            NamespaceName,
            "CurrentShowcaseMaster"
        ))
    {
    }

    FCurrentShowcaseMasterDomain::FCurrentShowcaseMasterDomain(
        const FCurrentShowcaseMasterDomain& From
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

    FCurrentShowcaseMasterDomain::FExportMasterTask::FExportMasterTask(
        const TSharedPtr<FCurrentShowcaseMasterDomain> Self,
        const Request::FExportMasterRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FCurrentShowcaseMasterDomain::FExportMasterTask::FExportMasterTask(
        const FExportMasterTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FCurrentShowcaseMasterDomain::FExportMasterTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Showcase::Domain::Model::FCurrentShowcaseMasterDomain>> Result
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
                const auto ParentKey = Gs2::Showcase::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
                    Self->NamespaceName,
                    "CurrentShowcaseMaster"
                );
                const auto Key = Gs2::Showcase::Domain::Model::FCurrentShowcaseMasterDomain::CreateCacheKey(
                );
                Self->Cache->Put(
                    Gs2::Showcase::Model::FCurrentShowcaseMaster::TypeName,
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

    TSharedPtr<FAsyncTask<FCurrentShowcaseMasterDomain::FExportMasterTask>> FCurrentShowcaseMasterDomain::ExportMaster(
        Request::FExportMasterRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FExportMasterTask>>(this->AsShared(), Request);
    }

    FCurrentShowcaseMasterDomain::FGetTask::FGetTask(
        const TSharedPtr<FCurrentShowcaseMasterDomain> Self,
        const Request::FGetCurrentShowcaseMasterRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FCurrentShowcaseMasterDomain::FGetTask::FGetTask(
        const FGetTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FCurrentShowcaseMasterDomain::FGetTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Showcase::Model::FCurrentShowcaseMaster>> Result
    )
    {
        Request
            ->WithNamespaceName(Self->NamespaceName);
        const auto Future = Self->Client->GetCurrentShowcaseMaster(
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
                const auto ParentKey = Gs2::Showcase::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
                    Self->NamespaceName,
                    "CurrentShowcaseMaster"
                );
                const auto Key = Gs2::Showcase::Domain::Model::FCurrentShowcaseMasterDomain::CreateCacheKey(
                );
                Self->Cache->Put(
                    Gs2::Showcase::Model::FCurrentShowcaseMaster::TypeName,
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

    TSharedPtr<FAsyncTask<FCurrentShowcaseMasterDomain::FGetTask>> FCurrentShowcaseMasterDomain::Get(
        Request::FGetCurrentShowcaseMasterRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FGetTask>>(this->AsShared(), Request);
    }

    FCurrentShowcaseMasterDomain::FUpdateTask::FUpdateTask(
        const TSharedPtr<FCurrentShowcaseMasterDomain> Self,
        const Request::FUpdateCurrentShowcaseMasterRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FCurrentShowcaseMasterDomain::FUpdateTask::FUpdateTask(
        const FUpdateTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FCurrentShowcaseMasterDomain::FUpdateTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Showcase::Domain::Model::FCurrentShowcaseMasterDomain>> Result
    )
    {
        Request
            ->WithNamespaceName(Self->NamespaceName);
        const auto Future = Self->Client->UpdateCurrentShowcaseMaster(
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
                const auto ParentKey = Gs2::Showcase::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
                    Self->NamespaceName,
                    "CurrentShowcaseMaster"
                );
                const auto Key = Gs2::Showcase::Domain::Model::FCurrentShowcaseMasterDomain::CreateCacheKey(
                );
                Self->Cache->Put(
                    Gs2::Showcase::Model::FCurrentShowcaseMaster::TypeName,
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

    TSharedPtr<FAsyncTask<FCurrentShowcaseMasterDomain::FUpdateTask>> FCurrentShowcaseMasterDomain::Update(
        Request::FUpdateCurrentShowcaseMasterRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FUpdateTask>>(this->AsShared(), Request);
    }

    FCurrentShowcaseMasterDomain::FUpdateFromGitHubTask::FUpdateFromGitHubTask(
        const TSharedPtr<FCurrentShowcaseMasterDomain> Self,
        const Request::FUpdateCurrentShowcaseMasterFromGitHubRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FCurrentShowcaseMasterDomain::FUpdateFromGitHubTask::FUpdateFromGitHubTask(
        const FUpdateFromGitHubTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FCurrentShowcaseMasterDomain::FUpdateFromGitHubTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Showcase::Domain::Model::FCurrentShowcaseMasterDomain>> Result
    )
    {
        Request
            ->WithNamespaceName(Self->NamespaceName);
        const auto Future = Self->Client->UpdateCurrentShowcaseMasterFromGitHub(
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
                const auto ParentKey = Gs2::Showcase::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
                    Self->NamespaceName,
                    "CurrentShowcaseMaster"
                );
                const auto Key = Gs2::Showcase::Domain::Model::FCurrentShowcaseMasterDomain::CreateCacheKey(
                );
                Self->Cache->Put(
                    Gs2::Showcase::Model::FCurrentShowcaseMaster::TypeName,
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

    TSharedPtr<FAsyncTask<FCurrentShowcaseMasterDomain::FUpdateFromGitHubTask>> FCurrentShowcaseMasterDomain::UpdateFromGitHub(
        Request::FUpdateCurrentShowcaseMasterFromGitHubRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FUpdateFromGitHubTask>>(this->AsShared(), Request);
    }

    FString FCurrentShowcaseMasterDomain::CreateCacheParentKey(
        TOptional<FString> NamespaceName,
        FString ChildType
    )
    {
        return FString("") +
            (NamespaceName.IsSet() ? *NamespaceName : "null") + ":" +
            ChildType;
    }

    FString FCurrentShowcaseMasterDomain::CreateCacheKey(
    )
    {
        return "Singleton";
    }

    FCurrentShowcaseMasterDomain::FModelTask::FModelTask(
        const TSharedPtr<FCurrentShowcaseMasterDomain> Self
    ): Self(Self)
    {

    }

    FCurrentShowcaseMasterDomain::FModelTask::FModelTask(
        const FModelTask& From
    ): TGs2Future(From), Self(From.Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FCurrentShowcaseMasterDomain::FModelTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Showcase::Model::FCurrentShowcaseMaster>> Result
    )
    {
        // ReSharper disable once CppLocalVariableMayBeConst
        TSharedPtr<Gs2::Showcase::Model::FCurrentShowcaseMaster> Value;
        auto bCacheHit = Self->Cache->TryGet<Gs2::Showcase::Model::FCurrentShowcaseMaster>(
            Self->ParentKey,
            Gs2::Showcase::Domain::Model::FCurrentShowcaseMasterDomain::CreateCacheKey(
            ),
            &Value
        );
        if (!bCacheHit) {
            const auto Future = Self->Get(
                MakeShared<Gs2::Showcase::Request::FGetCurrentShowcaseMasterRequest>()
            );
            Future->StartSynchronousTask();
            if (Future->GetTask().IsError())
            {
                if (Future->GetTask().Error()->Type() != Gs2::Core::Model::FNotFoundError::TypeString)
                {
                    return Future->GetTask().Error();
                }

                const auto Key = Gs2::Showcase::Domain::Model::FCurrentShowcaseMasterDomain::CreateCacheKey(
                );
                Self->Cache->Put(
                    Gs2::Showcase::Model::FCurrentShowcaseMaster::TypeName,
                    Self->ParentKey,
                    Key,
                    nullptr,
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );

                if (Future->GetTask().Error()->Detail(0)->GetComponent() != "currentShowcaseMaster")
                {
                    return Future->GetTask().Error();
                }
            }
            Self->Cache->TryGet<Gs2::Showcase::Model::FCurrentShowcaseMaster>(
                Self->ParentKey,
                Gs2::Showcase::Domain::Model::FCurrentShowcaseMasterDomain::CreateCacheKey(
                ),
                &Value
            );
            Future->EnsureCompletion();
        }
        *Result = Value;

        return nullptr;
    }

    TSharedPtr<FAsyncTask<FCurrentShowcaseMasterDomain::FModelTask>> FCurrentShowcaseMasterDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FCurrentShowcaseMasterDomain::FModelTask>>(this->AsShared());
    }

    Gs2::Core::Domain::CallbackID FCurrentShowcaseMasterDomain::Subscribe(
        TFunction<void(Gs2::Showcase::Model::FCurrentShowcaseMasterPtr)> Callback
    )
    {
        return Cache->Subscribe(
            Gs2::Showcase::Model::FCurrentShowcaseMaster::TypeName,
            ParentKey,
            Gs2::Showcase::Domain::Model::FCurrentShowcaseMasterDomain::CreateCacheKey(
            ),
            [Callback](TSharedPtr<Gs2Object> obj)
            {
                Callback(StaticCastSharedPtr<Gs2::Showcase::Model::FCurrentShowcaseMaster>(obj));
            }
        );
    }

    void FCurrentShowcaseMasterDomain::Unsubscribe(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        Cache->Unsubscribe(
            Gs2::Showcase::Model::FCurrentShowcaseMaster::TypeName,
            ParentKey,
            Gs2::Showcase::Domain::Model::FCurrentShowcaseMasterDomain::CreateCacheKey(
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

