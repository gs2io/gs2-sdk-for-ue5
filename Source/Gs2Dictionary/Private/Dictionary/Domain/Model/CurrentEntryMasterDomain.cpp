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

#include "Dictionary/Domain/Model/CurrentEntryMaster.h"
#include "Dictionary/Domain/Model/Namespace.h"
#include "Dictionary/Domain/Model/EntryModel.h"
#include "Dictionary/Domain/Model/EntryModelMaster.h"
#include "Dictionary/Domain/Model/Entry.h"
#include "Dictionary/Domain/Model/EntryAccessToken.h"
#include "Dictionary/Domain/Model/CurrentEntryMaster.h"
#include "Dictionary/Domain/Model/User.h"
#include "Dictionary/Domain/Model/UserAccessToken.h"

#include "Core/Domain/Model/AutoStampSheetDomain.h"
#include "Core/Domain/Model/StampSheetDomain.h"

namespace Gs2::Dictionary::Domain::Model
{

    FCurrentEntryMasterDomain::FCurrentEntryMasterDomain(
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
        Client(MakeShared<Gs2::Dictionary::FGs2DictionaryRestClient>(Session)),
        NamespaceName(NamespaceName),
        ParentKey(Gs2::Dictionary::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
            NamespaceName,
            "CurrentEntryMaster"
        ))
    {
    }

    FCurrentEntryMasterDomain::FCurrentEntryMasterDomain(
        const FCurrentEntryMasterDomain& From
    ):
        Cache(From.Cache),
        JobQueueDomain(From.JobQueueDomain),
        StampSheetConfiguration(From.StampSheetConfiguration),
        Session(From.Session),
        Client(From.Client)
    {

    }

    FCurrentEntryMasterDomain::FExportMasterTask::FExportMasterTask(
        const TSharedPtr<FCurrentEntryMasterDomain> Self,
        const Request::FExportMasterRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FCurrentEntryMasterDomain::FExportMasterTask::FExportMasterTask(
        const FExportMasterTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FCurrentEntryMasterDomain::FExportMasterTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Dictionary::Domain::Model::FCurrentEntryMasterDomain>> Result
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
                const auto ParentKey = Gs2::Dictionary::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
                    Self->NamespaceName,
                    "CurrentEntryMaster"
                );
                const auto Key = Gs2::Dictionary::Domain::Model::FCurrentEntryMasterDomain::CreateCacheKey(
                );
                Self->Cache->Put(
                    Gs2::Dictionary::Model::FCurrentEntryMaster::TypeName,
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

    TSharedPtr<FAsyncTask<FCurrentEntryMasterDomain::FExportMasterTask>> FCurrentEntryMasterDomain::ExportMaster(
        Request::FExportMasterRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FExportMasterTask>>(this->AsShared(), Request);
    }

    FCurrentEntryMasterDomain::FGetTask::FGetTask(
        const TSharedPtr<FCurrentEntryMasterDomain> Self,
        const Request::FGetCurrentEntryMasterRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FCurrentEntryMasterDomain::FGetTask::FGetTask(
        const FGetTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FCurrentEntryMasterDomain::FGetTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Dictionary::Model::FCurrentEntryMaster>> Result
    )
    {
        Request
            ->WithNamespaceName(Self->NamespaceName);
        const auto Future = Self->Client->GetCurrentEntryMaster(
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
                const auto ParentKey = Gs2::Dictionary::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
                    Self->NamespaceName,
                    "CurrentEntryMaster"
                );
                const auto Key = Gs2::Dictionary::Domain::Model::FCurrentEntryMasterDomain::CreateCacheKey(
                );
                Self->Cache->Put(
                    Gs2::Dictionary::Model::FCurrentEntryMaster::TypeName,
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

    TSharedPtr<FAsyncTask<FCurrentEntryMasterDomain::FGetTask>> FCurrentEntryMasterDomain::Get(
        Request::FGetCurrentEntryMasterRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FGetTask>>(this->AsShared(), Request);
    }

    FCurrentEntryMasterDomain::FUpdateTask::FUpdateTask(
        const TSharedPtr<FCurrentEntryMasterDomain> Self,
        const Request::FUpdateCurrentEntryMasterRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FCurrentEntryMasterDomain::FUpdateTask::FUpdateTask(
        const FUpdateTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FCurrentEntryMasterDomain::FUpdateTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Dictionary::Domain::Model::FCurrentEntryMasterDomain>> Result
    )
    {
        Request
            ->WithNamespaceName(Self->NamespaceName);
        const auto Future = Self->Client->UpdateCurrentEntryMaster(
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
                const auto ParentKey = Gs2::Dictionary::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
                    Self->NamespaceName,
                    "CurrentEntryMaster"
                );
                const auto Key = Gs2::Dictionary::Domain::Model::FCurrentEntryMasterDomain::CreateCacheKey(
                );
                Self->Cache->Put(
                    Gs2::Dictionary::Model::FCurrentEntryMaster::TypeName,
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

    TSharedPtr<FAsyncTask<FCurrentEntryMasterDomain::FUpdateTask>> FCurrentEntryMasterDomain::Update(
        Request::FUpdateCurrentEntryMasterRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FUpdateTask>>(this->AsShared(), Request);
    }

    FCurrentEntryMasterDomain::FUpdateFromGitHubTask::FUpdateFromGitHubTask(
        const TSharedPtr<FCurrentEntryMasterDomain> Self,
        const Request::FUpdateCurrentEntryMasterFromGitHubRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FCurrentEntryMasterDomain::FUpdateFromGitHubTask::FUpdateFromGitHubTask(
        const FUpdateFromGitHubTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FCurrentEntryMasterDomain::FUpdateFromGitHubTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Dictionary::Domain::Model::FCurrentEntryMasterDomain>> Result
    )
    {
        Request
            ->WithNamespaceName(Self->NamespaceName);
        const auto Future = Self->Client->UpdateCurrentEntryMasterFromGitHub(
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
                const auto ParentKey = Gs2::Dictionary::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
                    Self->NamespaceName,
                    "CurrentEntryMaster"
                );
                const auto Key = Gs2::Dictionary::Domain::Model::FCurrentEntryMasterDomain::CreateCacheKey(
                );
                Self->Cache->Put(
                    Gs2::Dictionary::Model::FCurrentEntryMaster::TypeName,
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

    TSharedPtr<FAsyncTask<FCurrentEntryMasterDomain::FUpdateFromGitHubTask>> FCurrentEntryMasterDomain::UpdateFromGitHub(
        Request::FUpdateCurrentEntryMasterFromGitHubRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FUpdateFromGitHubTask>>(this->AsShared(), Request);
    }

    FString FCurrentEntryMasterDomain::CreateCacheParentKey(
        TOptional<FString> NamespaceName,
        FString ChildType
    )
    {
        return FString() +
            (NamespaceName.IsSet() ? *NamespaceName : "null") + ":" +
            ChildType;
    }

    FString FCurrentEntryMasterDomain::CreateCacheKey(
    )
    {
        return "Singleton";
    }

    FCurrentEntryMasterDomain::FModelTask::FModelTask(
        const TSharedPtr<FCurrentEntryMasterDomain> Self
    ): Self(Self)
    {

    }

    FCurrentEntryMasterDomain::FModelTask::FModelTask(
        const FModelTask& From
    ): TGs2Future(From), Self(From.Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FCurrentEntryMasterDomain::FModelTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Dictionary::Model::FCurrentEntryMaster>> Result
    )
    {
        // ReSharper disable once CppLocalVariableMayBeConst
        auto Value = Self->Cache->Get<Gs2::Dictionary::Model::FCurrentEntryMaster>(
            Self->ParentKey,
            Gs2::Dictionary::Domain::Model::FCurrentEntryMasterDomain::CreateCacheKey(
            )
        );
        if (Value == nullptr) {
            const auto Future = Self->Get(
                MakeShared<Gs2::Dictionary::Request::FGetCurrentEntryMasterRequest>()
            );
            Future->StartSynchronousTask();
            if (Future->GetTask().IsError())
            {
                if (Future->GetTask().Error()->Type() == Gs2::Core::Model::FNotFoundError::TypeString)
                {
                    if (Future->GetTask().Error()->Detail(0)->GetComponent() == "currentEntryMaster")
                    {
                        Self->Cache->Delete(
                            Gs2::Dictionary::Model::FCurrentEntryMaster::TypeName,
                            Self->ParentKey,
                            Gs2::Dictionary::Domain::Model::FCurrentEntryMasterDomain::CreateCacheKey(
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
            Value = Self->Cache->Get<Gs2::Dictionary::Model::FCurrentEntryMaster>(
                Self->ParentKey,
                Gs2::Dictionary::Domain::Model::FCurrentEntryMasterDomain::CreateCacheKey(
                )
            );
            Future->EnsureCompletion();
        }
        *Result = Value;

        return nullptr;
    }

    TSharedPtr<FAsyncTask<FCurrentEntryMasterDomain::FModelTask>> FCurrentEntryMasterDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FCurrentEntryMasterDomain::FModelTask>>(this->AsShared());
    }
}

#if defined(_MSC_VER)
#pragma warning (pop)
#elif defined(__clang__)
#pragma clang diagnostic pop
#endif

