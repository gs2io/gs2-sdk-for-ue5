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

#include "Quest/Domain/Model/CurrentQuestMaster.h"
#include "Quest/Domain/Model/Namespace.h"
#include "Quest/Domain/Model/QuestGroupModelMaster.h"
#include "Quest/Domain/Model/QuestModelMaster.h"
#include "Quest/Domain/Model/CurrentQuestMaster.h"
#include "Quest/Domain/Model/Progress.h"
#include "Quest/Domain/Model/ProgressAccessToken.h"
#include "Quest/Domain/Model/CompletedQuestList.h"
#include "Quest/Domain/Model/CompletedQuestListAccessToken.h"
#include "Quest/Domain/Model/QuestGroupModel.h"
#include "Quest/Domain/Model/QuestModel.h"
#include "Quest/Domain/Model/User.h"
#include "Quest/Domain/Model/UserAccessToken.h"

#include "Core/Domain/Model/AutoStampSheetDomain.h"
#include "Core/Domain/Model/StampSheetDomain.h"

namespace Gs2::Quest::Domain::Model
{

    FCurrentQuestMasterDomain::FCurrentQuestMasterDomain(
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
        Client(MakeShared<Gs2::Quest::FGs2QuestRestClient>(Session)),
        NamespaceName(NamespaceName),
        ParentKey(Gs2::Quest::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
            NamespaceName,
            "CurrentQuestMaster"
        ))
    {
    }

    FCurrentQuestMasterDomain::FCurrentQuestMasterDomain(
        const FCurrentQuestMasterDomain& From
    ):
        Cache(From.Cache),
        JobQueueDomain(From.JobQueueDomain),
        StampSheetConfiguration(From.StampSheetConfiguration),
        Session(From.Session),
        Client(From.Client)
    {

    }

    FCurrentQuestMasterDomain::FExportMasterTask::FExportMasterTask(
        const TSharedPtr<FCurrentQuestMasterDomain> Self,
        const Request::FExportMasterRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FCurrentQuestMasterDomain::FExportMasterTask::FExportMasterTask(
        const FExportMasterTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FCurrentQuestMasterDomain::FExportMasterTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Quest::Domain::Model::FCurrentQuestMasterDomain>> Result
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
                const auto ParentKey = Gs2::Quest::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
                    Self->NamespaceName,
                    "CurrentQuestMaster"
                );
                const auto Key = Gs2::Quest::Domain::Model::FCurrentQuestMasterDomain::CreateCacheKey(
                );
                Self->Cache->Put<Gs2::Quest::Model::FCurrentQuestMaster>(
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

    TSharedPtr<FAsyncTask<FCurrentQuestMasterDomain::FExportMasterTask>> FCurrentQuestMasterDomain::ExportMaster(
        Request::FExportMasterRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FExportMasterTask>>(this->AsShared(), Request);
    }

    FCurrentQuestMasterDomain::FGetTask::FGetTask(
        const TSharedPtr<FCurrentQuestMasterDomain> Self,
        const Request::FGetCurrentQuestMasterRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FCurrentQuestMasterDomain::FGetTask::FGetTask(
        const FGetTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FCurrentQuestMasterDomain::FGetTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Quest::Model::FCurrentQuestMaster>> Result
    )
    {
        Request
            ->WithNamespaceName(Self->NamespaceName);
        const auto Future = Self->Client->GetCurrentQuestMaster(
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
                const auto ParentKey = Gs2::Quest::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
                    Self->NamespaceName,
                    "CurrentQuestMaster"
                );
                const auto Key = Gs2::Quest::Domain::Model::FCurrentQuestMasterDomain::CreateCacheKey(
                );
                Self->Cache->Put<Gs2::Quest::Model::FCurrentQuestMaster>(
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

    TSharedPtr<FAsyncTask<FCurrentQuestMasterDomain::FGetTask>> FCurrentQuestMasterDomain::Get(
        Request::FGetCurrentQuestMasterRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FGetTask>>(this->AsShared(), Request);
    }

    FCurrentQuestMasterDomain::FUpdateTask::FUpdateTask(
        const TSharedPtr<FCurrentQuestMasterDomain> Self,
        const Request::FUpdateCurrentQuestMasterRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FCurrentQuestMasterDomain::FUpdateTask::FUpdateTask(
        const FUpdateTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FCurrentQuestMasterDomain::FUpdateTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Quest::Domain::Model::FCurrentQuestMasterDomain>> Result
    )
    {
        Request
            ->WithNamespaceName(Self->NamespaceName);
        const auto Future = Self->Client->UpdateCurrentQuestMaster(
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
                const auto ParentKey = Gs2::Quest::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
                    Self->NamespaceName,
                    "CurrentQuestMaster"
                );
                const auto Key = Gs2::Quest::Domain::Model::FCurrentQuestMasterDomain::CreateCacheKey(
                );
                Self->Cache->Put<Gs2::Quest::Model::FCurrentQuestMaster>(
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

    TSharedPtr<FAsyncTask<FCurrentQuestMasterDomain::FUpdateTask>> FCurrentQuestMasterDomain::Update(
        Request::FUpdateCurrentQuestMasterRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FUpdateTask>>(this->AsShared(), Request);
    }

    FCurrentQuestMasterDomain::FUpdateFromGitHubTask::FUpdateFromGitHubTask(
        const TSharedPtr<FCurrentQuestMasterDomain> Self,
        const Request::FUpdateCurrentQuestMasterFromGitHubRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FCurrentQuestMasterDomain::FUpdateFromGitHubTask::FUpdateFromGitHubTask(
        const FUpdateFromGitHubTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FCurrentQuestMasterDomain::FUpdateFromGitHubTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Quest::Domain::Model::FCurrentQuestMasterDomain>> Result
    )
    {
        Request
            ->WithNamespaceName(Self->NamespaceName);
        const auto Future = Self->Client->UpdateCurrentQuestMasterFromGitHub(
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
                const auto ParentKey = Gs2::Quest::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
                    Self->NamespaceName,
                    "CurrentQuestMaster"
                );
                const auto Key = Gs2::Quest::Domain::Model::FCurrentQuestMasterDomain::CreateCacheKey(
                );
                Self->Cache->Put<Gs2::Quest::Model::FCurrentQuestMaster>(
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

    TSharedPtr<FAsyncTask<FCurrentQuestMasterDomain::FUpdateFromGitHubTask>> FCurrentQuestMasterDomain::UpdateFromGitHub(
        Request::FUpdateCurrentQuestMasterFromGitHubRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FUpdateFromGitHubTask>>(this->AsShared(), Request);
    }

    FString FCurrentQuestMasterDomain::CreateCacheParentKey(
        TOptional<FString> NamespaceName,
        FString ChildType
    )
    {
        return FString() +
            (NamespaceName.IsSet() ? *NamespaceName : "null") + ":" +
            ChildType;
    }

    FString FCurrentQuestMasterDomain::CreateCacheKey(
    )
    {
        return "Singleton";
    }

    FCurrentQuestMasterDomain::FModelTask::FModelTask(
        const TSharedPtr<FCurrentQuestMasterDomain> Self
    ): Self(Self)
    {

    }

    FCurrentQuestMasterDomain::FModelTask::FModelTask(
        const FModelTask& From
    ): TGs2Future(From), Self(From.Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FCurrentQuestMasterDomain::FModelTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Quest::Model::FCurrentQuestMaster>> Result
    )
    {
        // ReSharper disable once CppLocalVariableMayBeConst
        auto Value = Self->Cache->Get<Gs2::Quest::Model::FCurrentQuestMaster>(
            Self->ParentKey,
            Gs2::Quest::Domain::Model::FCurrentQuestMasterDomain::CreateCacheKey(
            )
        );
        if (Value == nullptr) {
            const auto Future = Self->Get(
                MakeShared<Gs2::Quest::Request::FGetCurrentQuestMasterRequest>()
            );
            Future->StartSynchronousTask();
            if (Future->GetTask().IsError())
            {
                if (Future->GetTask().Error()->Type() == Gs2::Core::Model::FNotFoundError::TypeString)
                {
                    if (Future->GetTask().Error()->Detail(0)->GetComponent() == "currentQuestMaster")
                    {
                        Self->Cache->Delete<Gs2::Quest::Model::FCurrentQuestMaster>(
                            Self->ParentKey,
                            Gs2::Quest::Domain::Model::FCurrentQuestMasterDomain::CreateCacheKey(
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
            Value = Self->Cache->Get<Gs2::Quest::Model::FCurrentQuestMaster>(
                Self->ParentKey,
                Gs2::Quest::Domain::Model::FCurrentQuestMasterDomain::CreateCacheKey(
                )
            );
            Future->EnsureCompletion();
        }
        *Result = Value;

        return nullptr;
    }

    TSharedPtr<FAsyncTask<FCurrentQuestMasterDomain::FModelTask>> FCurrentQuestMasterDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FCurrentQuestMasterDomain::FModelTask>>(this->AsShared());
    }
}

#if defined(_MSC_VER)
#pragma warning (pop)
#elif defined(__clang__)
#pragma clang diagnostic pop
#endif

