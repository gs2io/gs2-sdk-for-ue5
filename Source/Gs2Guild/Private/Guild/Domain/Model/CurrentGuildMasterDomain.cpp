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

#include "Guild/Domain/Model/CurrentGuildMaster.h"
#include "Guild/Domain/Model/Namespace.h"
#include "Guild/Domain/Model/GuildModelMaster.h"
#include "Guild/Domain/Model/GuildModel.h"
#include "Guild/Domain/Model/User.h"
#include "Guild/Domain/Model/UserAccessToken.h"
#include "Guild/Domain/Model/Guild.h"
#include "Guild/Domain/Model/JoinedGuild.h"
#include "Guild/Domain/Model/JoinedGuildAccessToken.h"
#include "Guild/Domain/Model/CurrentGuildMaster.h"
#include "Guild/Domain/Model/ReceiveMemberRequest.h"
#include "Guild/Domain/Model/SendMemberRequest.h"
#include "Guild/Domain/Model/SendMemberRequestAccessToken.h"
#include "Guild/Domain/Model/IgnoreUser.h"

#include "Core/Domain/Gs2.h"
#include "Core/Domain/Transaction/JobQueueJobDomainFactory.h"
#include "Core/Domain/Transaction/InternalTransactionDomainFactory.h"
#include "Core/Domain/Transaction/ManualTransactionDomain.h"

namespace Gs2::Guild::Domain::Model
{

    FCurrentGuildMasterDomain::FCurrentGuildMasterDomain(
        const Core::Domain::FGs2Ptr& Gs2,
        const Guild::Domain::FGs2GuildDomainPtr& Service,
        const TOptional<FString> NamespaceName
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Gs2(Gs2),
        Service(Service),
        Client(MakeShared<Gs2::Guild::FGs2GuildRestClient>(Gs2->RestSession)),
        NamespaceName(NamespaceName),
        ParentKey(Gs2::Guild::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
            NamespaceName,
            "CurrentGuildMaster"
        ))
    {
    }

    FCurrentGuildMasterDomain::FCurrentGuildMasterDomain(
        const FCurrentGuildMasterDomain& From
    ):
        Gs2(From.Gs2),
        Service(From.Service),
        Client(From.Client),
        NamespaceName(From.NamespaceName),
        ParentKey(From.ParentKey)
    {

    }

    FCurrentGuildMasterDomain::FExportMasterTask::FExportMasterTask(
        const TSharedPtr<FCurrentGuildMasterDomain>& Self,
        const Request::FExportMasterRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FCurrentGuildMasterDomain::FExportMasterTask::FExportMasterTask(
        const FExportMasterTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FCurrentGuildMasterDomain::FExportMasterTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Guild::Domain::Model::FCurrentGuildMasterDomain>> Result
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
                const auto ParentKey = Gs2::Guild::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
                    Self->NamespaceName,
                    "CurrentGuildMaster"
                );
                const auto Key = Gs2::Guild::Domain::Model::FCurrentGuildMasterDomain::CreateCacheKey(
                );
                Self->Gs2->Cache->Put(
                    Gs2::Guild::Model::FCurrentGuildMaster::TypeName,
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

    TSharedPtr<FAsyncTask<FCurrentGuildMasterDomain::FExportMasterTask>> FCurrentGuildMasterDomain::ExportMaster(
        Request::FExportMasterRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FExportMasterTask>>(this->AsShared(), Request);
    }

    FCurrentGuildMasterDomain::FGetTask::FGetTask(
        const TSharedPtr<FCurrentGuildMasterDomain>& Self,
        const Request::FGetCurrentGuildMasterRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FCurrentGuildMasterDomain::FGetTask::FGetTask(
        const FGetTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FCurrentGuildMasterDomain::FGetTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Guild::Model::FCurrentGuildMaster>> Result
    )
    {
        Request
            ->WithContextStack(Self->Gs2->DefaultContextStack)
            ->WithNamespaceName(Self->NamespaceName);
        const auto Future = Self->Client->GetCurrentGuildMaster(
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
                const auto ParentKey = Gs2::Guild::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
                    Self->NamespaceName,
                    "CurrentGuildMaster"
                );
                const auto Key = Gs2::Guild::Domain::Model::FCurrentGuildMasterDomain::CreateCacheKey(
                );
                Self->Gs2->Cache->Put(
                    Gs2::Guild::Model::FCurrentGuildMaster::TypeName,
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

    TSharedPtr<FAsyncTask<FCurrentGuildMasterDomain::FGetTask>> FCurrentGuildMasterDomain::Get(
        Request::FGetCurrentGuildMasterRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FGetTask>>(this->AsShared(), Request);
    }

    FCurrentGuildMasterDomain::FUpdateTask::FUpdateTask(
        const TSharedPtr<FCurrentGuildMasterDomain>& Self,
        const Request::FUpdateCurrentGuildMasterRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FCurrentGuildMasterDomain::FUpdateTask::FUpdateTask(
        const FUpdateTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FCurrentGuildMasterDomain::FUpdateTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Guild::Domain::Model::FCurrentGuildMasterDomain>> Result
    )
    {
        Request
            ->WithContextStack(Self->Gs2->DefaultContextStack)
            ->WithNamespaceName(Self->NamespaceName);
        const auto Future = Self->Client->UpdateCurrentGuildMaster(
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
                const auto ParentKey = Gs2::Guild::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
                    Self->NamespaceName,
                    "CurrentGuildMaster"
                );
                const auto Key = Gs2::Guild::Domain::Model::FCurrentGuildMasterDomain::CreateCacheKey(
                );
                Self->Gs2->Cache->Put(
                    Gs2::Guild::Model::FCurrentGuildMaster::TypeName,
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

    TSharedPtr<FAsyncTask<FCurrentGuildMasterDomain::FUpdateTask>> FCurrentGuildMasterDomain::Update(
        Request::FUpdateCurrentGuildMasterRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FUpdateTask>>(this->AsShared(), Request);
    }

    FCurrentGuildMasterDomain::FUpdateFromGitHubTask::FUpdateFromGitHubTask(
        const TSharedPtr<FCurrentGuildMasterDomain>& Self,
        const Request::FUpdateCurrentGuildMasterFromGitHubRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FCurrentGuildMasterDomain::FUpdateFromGitHubTask::FUpdateFromGitHubTask(
        const FUpdateFromGitHubTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FCurrentGuildMasterDomain::FUpdateFromGitHubTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Guild::Domain::Model::FCurrentGuildMasterDomain>> Result
    )
    {
        Request
            ->WithContextStack(Self->Gs2->DefaultContextStack)
            ->WithNamespaceName(Self->NamespaceName);
        const auto Future = Self->Client->UpdateCurrentGuildMasterFromGitHub(
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
                const auto ParentKey = Gs2::Guild::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
                    Self->NamespaceName,
                    "CurrentGuildMaster"
                );
                const auto Key = Gs2::Guild::Domain::Model::FCurrentGuildMasterDomain::CreateCacheKey(
                );
                Self->Gs2->Cache->Put(
                    Gs2::Guild::Model::FCurrentGuildMaster::TypeName,
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

    TSharedPtr<FAsyncTask<FCurrentGuildMasterDomain::FUpdateFromGitHubTask>> FCurrentGuildMasterDomain::UpdateFromGitHub(
        Request::FUpdateCurrentGuildMasterFromGitHubRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FUpdateFromGitHubTask>>(this->AsShared(), Request);
    }

    FString FCurrentGuildMasterDomain::CreateCacheParentKey(
        TOptional<FString> NamespaceName,
        FString ChildType
    )
    {
        return FString("") +
            (NamespaceName.IsSet() ? *NamespaceName : "null") + ":" +
            ChildType;
    }

    FString FCurrentGuildMasterDomain::CreateCacheKey(
    )
    {
        return "Singleton";
    }

    FCurrentGuildMasterDomain::FModelTask::FModelTask(
        const TSharedPtr<FCurrentGuildMasterDomain> Self
    ): Self(Self)
    {

    }

    FCurrentGuildMasterDomain::FModelTask::FModelTask(
        const FModelTask& From
    ): TGs2Future(From), Self(From.Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FCurrentGuildMasterDomain::FModelTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Guild::Model::FCurrentGuildMaster>> Result
    )
    {
        // ReSharper disable once CppLocalVariableMayBeConst
        TSharedPtr<Gs2::Guild::Model::FCurrentGuildMaster> Value;
        auto bCacheHit = Self->Gs2->Cache->TryGet<Gs2::Guild::Model::FCurrentGuildMaster>(
            Self->ParentKey,
            Gs2::Guild::Domain::Model::FCurrentGuildMasterDomain::CreateCacheKey(
            ),
            &Value
        );
        if (!bCacheHit) {
            const auto Future = Self->Get(
                MakeShared<Gs2::Guild::Request::FGetCurrentGuildMasterRequest>()
            );
            Future->StartSynchronousTask();
            if (Future->GetTask().IsError())
            {
                if (Future->GetTask().Error()->Type() != Gs2::Core::Model::FNotFoundError::TypeString)
                {
                    return Future->GetTask().Error();
                }

                const auto Key = Gs2::Guild::Domain::Model::FCurrentGuildMasterDomain::CreateCacheKey(
                );
                Self->Gs2->Cache->Put(
                    Gs2::Guild::Model::FCurrentGuildMaster::TypeName,
                    Self->ParentKey,
                    Key,
                    nullptr,
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );

                if (Future->GetTask().Error()->Detail(0)->GetComponent() != "currentGuildMaster")
                {
                    return Future->GetTask().Error();
                }
            }
            Self->Gs2->Cache->TryGet<Gs2::Guild::Model::FCurrentGuildMaster>(
                Self->ParentKey,
                Gs2::Guild::Domain::Model::FCurrentGuildMasterDomain::CreateCacheKey(
                ),
                &Value
            );
            Future->EnsureCompletion();
        }
        *Result = Value;

        return nullptr;
    }

    TSharedPtr<FAsyncTask<FCurrentGuildMasterDomain::FModelTask>> FCurrentGuildMasterDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FCurrentGuildMasterDomain::FModelTask>>(this->AsShared());
    }

    Gs2::Core::Domain::CallbackID FCurrentGuildMasterDomain::Subscribe(
        TFunction<void(Gs2::Guild::Model::FCurrentGuildMasterPtr)> Callback
    )
    {
        return Gs2->Cache->Subscribe(
            Gs2::Guild::Model::FCurrentGuildMaster::TypeName,
            ParentKey,
            Gs2::Guild::Domain::Model::FCurrentGuildMasterDomain::CreateCacheKey(
            ),
            [Callback](TSharedPtr<Gs2Object> obj)
            {
                Callback(StaticCastSharedPtr<Gs2::Guild::Model::FCurrentGuildMaster>(obj));
            }
        );
    }

    void FCurrentGuildMasterDomain::Unsubscribe(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        Gs2->Cache->Unsubscribe(
            Gs2::Guild::Model::FCurrentGuildMaster::TypeName,
            ParentKey,
            Gs2::Guild::Domain::Model::FCurrentGuildMasterDomain::CreateCacheKey(
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

