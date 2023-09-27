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

#include "SkillTree/Domain/Model/CurrentTreeMaster.h"
#include "SkillTree/Domain/Model/Namespace.h"
#include "SkillTree/Domain/Model/NodeModel.h"
#include "SkillTree/Domain/Model/NodeModelMaster.h"
#include "SkillTree/Domain/Model/Status.h"
#include "SkillTree/Domain/Model/StatusAccessToken.h"
#include "SkillTree/Domain/Model/CurrentTreeMaster.h"
#include "SkillTree/Domain/Model/User.h"
#include "SkillTree/Domain/Model/UserAccessToken.h"

#include "Core/Domain/Model/AutoStampSheetDomain.h"
#include "Core/Domain/Model/StampSheetDomain.h"

namespace Gs2::SkillTree::Domain::Model
{

    FCurrentTreeMasterDomain::FCurrentTreeMasterDomain(
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
        Client(MakeShared<Gs2::SkillTree::FGs2SkillTreeRestClient>(Session)),
        NamespaceName(NamespaceName),
        ParentKey(Gs2::SkillTree::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
            NamespaceName,
            "CurrentTreeMaster"
        ))
    {
    }

    FCurrentTreeMasterDomain::FCurrentTreeMasterDomain(
        const FCurrentTreeMasterDomain& From
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

    FCurrentTreeMasterDomain::FExportMasterTask::FExportMasterTask(
        const TSharedPtr<FCurrentTreeMasterDomain> Self,
        const Request::FExportMasterRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FCurrentTreeMasterDomain::FExportMasterTask::FExportMasterTask(
        const FExportMasterTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FCurrentTreeMasterDomain::FExportMasterTask::Action(
        TSharedPtr<TSharedPtr<Gs2::SkillTree::Domain::Model::FCurrentTreeMasterDomain>> Result
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
                const auto ParentKey = Gs2::SkillTree::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
                    Self->NamespaceName,
                    "CurrentTreeMaster"
                );
                const auto Key = Gs2::SkillTree::Domain::Model::FCurrentTreeMasterDomain::CreateCacheKey(
                );
                Self->Cache->Put(
                    Gs2::SkillTree::Model::FCurrentTreeMaster::TypeName,
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

    TSharedPtr<FAsyncTask<FCurrentTreeMasterDomain::FExportMasterTask>> FCurrentTreeMasterDomain::ExportMaster(
        Request::FExportMasterRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FExportMasterTask>>(this->AsShared(), Request);
    }

    FCurrentTreeMasterDomain::FGetTask::FGetTask(
        const TSharedPtr<FCurrentTreeMasterDomain> Self,
        const Request::FGetCurrentTreeMasterRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FCurrentTreeMasterDomain::FGetTask::FGetTask(
        const FGetTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FCurrentTreeMasterDomain::FGetTask::Action(
        TSharedPtr<TSharedPtr<Gs2::SkillTree::Model::FCurrentTreeMaster>> Result
    )
    {
        Request
            ->WithNamespaceName(Self->NamespaceName);
        const auto Future = Self->Client->GetCurrentTreeMaster(
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
                const auto ParentKey = Gs2::SkillTree::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
                    Self->NamespaceName,
                    "CurrentTreeMaster"
                );
                const auto Key = Gs2::SkillTree::Domain::Model::FCurrentTreeMasterDomain::CreateCacheKey(
                );
                Self->Cache->Put(
                    Gs2::SkillTree::Model::FCurrentTreeMaster::TypeName,
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

    TSharedPtr<FAsyncTask<FCurrentTreeMasterDomain::FGetTask>> FCurrentTreeMasterDomain::Get(
        Request::FGetCurrentTreeMasterRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FGetTask>>(this->AsShared(), Request);
    }

    FCurrentTreeMasterDomain::FUpdateTask::FUpdateTask(
        const TSharedPtr<FCurrentTreeMasterDomain> Self,
        const Request::FUpdateCurrentTreeMasterRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FCurrentTreeMasterDomain::FUpdateTask::FUpdateTask(
        const FUpdateTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FCurrentTreeMasterDomain::FUpdateTask::Action(
        TSharedPtr<TSharedPtr<Gs2::SkillTree::Domain::Model::FCurrentTreeMasterDomain>> Result
    )
    {
        Request
            ->WithNamespaceName(Self->NamespaceName);
        const auto Future = Self->Client->UpdateCurrentTreeMaster(
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
                const auto ParentKey = Gs2::SkillTree::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
                    Self->NamespaceName,
                    "CurrentTreeMaster"
                );
                const auto Key = Gs2::SkillTree::Domain::Model::FCurrentTreeMasterDomain::CreateCacheKey(
                );
                Self->Cache->Put(
                    Gs2::SkillTree::Model::FCurrentTreeMaster::TypeName,
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

    TSharedPtr<FAsyncTask<FCurrentTreeMasterDomain::FUpdateTask>> FCurrentTreeMasterDomain::Update(
        Request::FUpdateCurrentTreeMasterRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FUpdateTask>>(this->AsShared(), Request);
    }

    FCurrentTreeMasterDomain::FUpdateFromGitHubTask::FUpdateFromGitHubTask(
        const TSharedPtr<FCurrentTreeMasterDomain> Self,
        const Request::FUpdateCurrentTreeMasterFromGitHubRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FCurrentTreeMasterDomain::FUpdateFromGitHubTask::FUpdateFromGitHubTask(
        const FUpdateFromGitHubTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FCurrentTreeMasterDomain::FUpdateFromGitHubTask::Action(
        TSharedPtr<TSharedPtr<Gs2::SkillTree::Domain::Model::FCurrentTreeMasterDomain>> Result
    )
    {
        Request
            ->WithNamespaceName(Self->NamespaceName);
        const auto Future = Self->Client->UpdateCurrentTreeMasterFromGitHub(
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
                const auto ParentKey = Gs2::SkillTree::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
                    Self->NamespaceName,
                    "CurrentTreeMaster"
                );
                const auto Key = Gs2::SkillTree::Domain::Model::FCurrentTreeMasterDomain::CreateCacheKey(
                );
                Self->Cache->Put(
                    Gs2::SkillTree::Model::FCurrentTreeMaster::TypeName,
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

    TSharedPtr<FAsyncTask<FCurrentTreeMasterDomain::FUpdateFromGitHubTask>> FCurrentTreeMasterDomain::UpdateFromGitHub(
        Request::FUpdateCurrentTreeMasterFromGitHubRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FUpdateFromGitHubTask>>(this->AsShared(), Request);
    }

    FString FCurrentTreeMasterDomain::CreateCacheParentKey(
        TOptional<FString> NamespaceName,
        FString ChildType
    )
    {
        return FString("") +
            (NamespaceName.IsSet() ? *NamespaceName : "null") + ":" +
            ChildType;
    }

    FString FCurrentTreeMasterDomain::CreateCacheKey(
    )
    {
        return "Singleton";
    }

    FCurrentTreeMasterDomain::FModelTask::FModelTask(
        const TSharedPtr<FCurrentTreeMasterDomain> Self
    ): Self(Self)
    {

    }

    FCurrentTreeMasterDomain::FModelTask::FModelTask(
        const FModelTask& From
    ): TGs2Future(From), Self(From.Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FCurrentTreeMasterDomain::FModelTask::Action(
        TSharedPtr<TSharedPtr<Gs2::SkillTree::Model::FCurrentTreeMaster>> Result
    )
    {
        // ReSharper disable once CppLocalVariableMayBeConst
        TSharedPtr<Gs2::SkillTree::Model::FCurrentTreeMaster> Value;
        auto bCacheHit = Self->Cache->TryGet<Gs2::SkillTree::Model::FCurrentTreeMaster>(
            Self->ParentKey,
            Gs2::SkillTree::Domain::Model::FCurrentTreeMasterDomain::CreateCacheKey(
            ),
            &Value
        );
        if (!bCacheHit) {
            const auto Future = Self->Get(
                MakeShared<Gs2::SkillTree::Request::FGetCurrentTreeMasterRequest>()
            );
            Future->StartSynchronousTask();
            if (Future->GetTask().IsError())
            {
                if (Future->GetTask().Error()->Type() != Gs2::Core::Model::FNotFoundError::TypeString)
                {
                    return Future->GetTask().Error();
                }

                const auto Key = Gs2::SkillTree::Domain::Model::FCurrentTreeMasterDomain::CreateCacheKey(
                );
                Self->Cache->Put(
                    Gs2::SkillTree::Model::FCurrentTreeMaster::TypeName,
                    Self->ParentKey,
                    Key,
                    nullptr,
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );

                if (Future->GetTask().Error()->Detail(0)->GetComponent() != "currentTreeMaster")
                {
                    return Future->GetTask().Error();
                }
            }
            Self->Cache->TryGet<Gs2::SkillTree::Model::FCurrentTreeMaster>(
                Self->ParentKey,
                Gs2::SkillTree::Domain::Model::FCurrentTreeMasterDomain::CreateCacheKey(
                ),
                &Value
            );
            Future->EnsureCompletion();
        }
        *Result = Value;

        return nullptr;
    }

    TSharedPtr<FAsyncTask<FCurrentTreeMasterDomain::FModelTask>> FCurrentTreeMasterDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FCurrentTreeMasterDomain::FModelTask>>(this->AsShared());
    }

    Gs2::Core::Domain::CallbackID FCurrentTreeMasterDomain::Subscribe(
        TFunction<void(Gs2::SkillTree::Model::FCurrentTreeMasterPtr)> Callback
    )
    {
        return Cache->Subscribe(
            Gs2::SkillTree::Model::FCurrentTreeMaster::TypeName,
            ParentKey,
            Gs2::SkillTree::Domain::Model::FCurrentTreeMasterDomain::CreateCacheKey(
            ),
            [Callback](TSharedPtr<Gs2Object> obj)
            {
                Callback(StaticCastSharedPtr<Gs2::SkillTree::Model::FCurrentTreeMaster>(obj));
            }
        );
    }

    void FCurrentTreeMasterDomain::Unsubscribe(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        Cache->Unsubscribe(
            Gs2::SkillTree::Model::FCurrentTreeMaster::TypeName,
            ParentKey,
            Gs2::SkillTree::Domain::Model::FCurrentTreeMasterDomain::CreateCacheKey(
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

