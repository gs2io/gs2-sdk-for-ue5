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

#include "Showcase/Domain/Model/ShowcaseMaster.h"
#include "Showcase/Domain/Model/Namespace.h"
#include "Showcase/Domain/Model/SalesItemMaster.h"
#include "Showcase/Domain/Model/SalesItemGroupMaster.h"
#include "Showcase/Domain/Model/ShowcaseMaster.h"
#include "Showcase/Domain/Model/CurrentShowcaseMaster.h"
#include "Showcase/Domain/Model/Showcase.h"
#include "Showcase/Domain/Model/ShowcaseAccessToken.h"
#include "Showcase/Domain/Model/User.h"
#include "Showcase/Domain/Model/UserAccessToken.h"

#include "Core/Domain/Model/AutoStampSheetDomain.h"
#include "Core/Domain/Model/StampSheetDomain.h"

namespace Gs2::Showcase::Domain::Model
{

    FShowcaseMasterDomain::FShowcaseMasterDomain(
        const Core::Domain::FCacheDatabasePtr Cache,
        const Gs2::Core::Domain::Model::FJobQueueDomainPtr JobQueueDomain,
        const Gs2::Core::Domain::Model::FStampSheetConfigurationPtr StampSheetConfiguration,
        const Gs2::Core::Net::Rest::FGs2RestSessionPtr Session,
        const TOptional<FString> NamespaceName,
        const TOptional<FString> ShowcaseName
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Cache(Cache),
        JobQueueDomain(JobQueueDomain),
        StampSheetConfiguration(StampSheetConfiguration),
        Session(Session),
        Client(MakeShared<Gs2::Showcase::FGs2ShowcaseRestClient>(Session)),
        NamespaceName(NamespaceName),
        ShowcaseName(ShowcaseName),
        ParentKey(Gs2::Showcase::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
            NamespaceName,
            "ShowcaseMaster"
        ))
    {
    }

    FShowcaseMasterDomain::FShowcaseMasterDomain(
        const FShowcaseMasterDomain& From
    ):
        Cache(From.Cache),
        JobQueueDomain(From.JobQueueDomain),
        StampSheetConfiguration(From.StampSheetConfiguration),
        Session(From.Session),
        Client(From.Client)
    {

    }

    FShowcaseMasterDomain::FGetTask::FGetTask(
        const TSharedPtr<FShowcaseMasterDomain> Self,
        const Request::FGetShowcaseMasterRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FShowcaseMasterDomain::FGetTask::FGetTask(
        const FGetTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FShowcaseMasterDomain::FGetTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Showcase::Model::FShowcaseMaster>> Result
    )
    {
        Request
            ->WithNamespaceName(Self->NamespaceName)
            ->WithShowcaseName(Self->ShowcaseName);
        const auto Future = Self->Client->GetShowcaseMaster(
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
                    "ShowcaseMaster"
                );
                const auto Key = Gs2::Showcase::Domain::Model::FShowcaseMasterDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetName()
                );
                Self->Cache->Put(
                    Gs2::Showcase::Model::FShowcaseMaster::TypeName,
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

    TSharedPtr<FAsyncTask<FShowcaseMasterDomain::FGetTask>> FShowcaseMasterDomain::Get(
        Request::FGetShowcaseMasterRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FGetTask>>(this->AsShared(), Request);
    }

    FShowcaseMasterDomain::FUpdateTask::FUpdateTask(
        const TSharedPtr<FShowcaseMasterDomain> Self,
        const Request::FUpdateShowcaseMasterRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FShowcaseMasterDomain::FUpdateTask::FUpdateTask(
        const FUpdateTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FShowcaseMasterDomain::FUpdateTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Showcase::Domain::Model::FShowcaseMasterDomain>> Result
    )
    {
        Request
            ->WithNamespaceName(Self->NamespaceName)
            ->WithShowcaseName(Self->ShowcaseName);
        const auto Future = Self->Client->UpdateShowcaseMaster(
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
                    "ShowcaseMaster"
                );
                const auto Key = Gs2::Showcase::Domain::Model::FShowcaseMasterDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetName()
                );
                Self->Cache->Put(
                    Gs2::Showcase::Model::FShowcaseMaster::TypeName,
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

    TSharedPtr<FAsyncTask<FShowcaseMasterDomain::FUpdateTask>> FShowcaseMasterDomain::Update(
        Request::FUpdateShowcaseMasterRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FUpdateTask>>(this->AsShared(), Request);
    }

    FShowcaseMasterDomain::FDeleteTask::FDeleteTask(
        const TSharedPtr<FShowcaseMasterDomain> Self,
        const Request::FDeleteShowcaseMasterRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FShowcaseMasterDomain::FDeleteTask::FDeleteTask(
        const FDeleteTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FShowcaseMasterDomain::FDeleteTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Showcase::Domain::Model::FShowcaseMasterDomain>> Result
    )
    {
        Request
            ->WithNamespaceName(Self->NamespaceName)
            ->WithShowcaseName(Self->ShowcaseName);
        const auto Future = Self->Client->DeleteShowcaseMaster(
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
                    "ShowcaseMaster"
                );
                const auto Key = Gs2::Showcase::Domain::Model::FShowcaseMasterDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetName()
                );
                Self->Cache->Delete(Gs2::Showcase::Model::FShowcaseMaster::TypeName, ParentKey, Key);
            }
        }
        auto Domain = Self;

        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FShowcaseMasterDomain::FDeleteTask>> FShowcaseMasterDomain::Delete(
        Request::FDeleteShowcaseMasterRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FDeleteTask>>(this->AsShared(), Request);
    }

    FString FShowcaseMasterDomain::CreateCacheParentKey(
        TOptional<FString> NamespaceName,
        TOptional<FString> ShowcaseName,
        FString ChildType
    )
    {
        return FString() +
            (NamespaceName.IsSet() ? *NamespaceName : "null") + ":" +
            (ShowcaseName.IsSet() ? *ShowcaseName : "null") + ":" +
            ChildType;
    }

    FString FShowcaseMasterDomain::CreateCacheKey(
        TOptional<FString> ShowcaseName
    )
    {
        return FString() +
            (ShowcaseName.IsSet() ? *ShowcaseName : "null");
    }

    FShowcaseMasterDomain::FModelTask::FModelTask(
        const TSharedPtr<FShowcaseMasterDomain> Self
    ): Self(Self)
    {

    }

    FShowcaseMasterDomain::FModelTask::FModelTask(
        const FModelTask& From
    ): TGs2Future(From), Self(From.Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FShowcaseMasterDomain::FModelTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Showcase::Model::FShowcaseMaster>> Result
    )
    {
        // ReSharper disable once CppLocalVariableMayBeConst
        TSharedPtr<Gs2::Showcase::Model::FShowcaseMaster> Value;
        auto bCacheHit = Self->Cache->TryGet<Gs2::Showcase::Model::FShowcaseMaster>(
            Self->ParentKey,
            Gs2::Showcase::Domain::Model::FShowcaseMasterDomain::CreateCacheKey(
                Self->ShowcaseName
            ),
            &Value
        );
        if (!bCacheHit) {
            const auto Future = Self->Get(
                MakeShared<Gs2::Showcase::Request::FGetShowcaseMasterRequest>()
            );
            Future->StartSynchronousTask();
            if (Future->GetTask().IsError())
            {
                if (Future->GetTask().Error()->Type() != Gs2::Core::Model::FNotFoundError::TypeString)
                {
                    return Future->GetTask().Error();
                }

                const auto Key = Gs2::Showcase::Domain::Model::FShowcaseMasterDomain::CreateCacheKey(
                    Self->ShowcaseName
                );
                Self->Cache->Put(
                    Gs2::Showcase::Model::FShowcaseMaster::TypeName,
                    Self->ParentKey,
                    Key,
                    nullptr,
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );

                if (Future->GetTask().Error()->Detail(0)->GetComponent() != "showcaseMaster")
                {
                    return Future->GetTask().Error();
                }
            }
            Self->Cache->TryGet<Gs2::Showcase::Model::FShowcaseMaster>(
                Self->ParentKey,
                Gs2::Showcase::Domain::Model::FShowcaseMasterDomain::CreateCacheKey(
                    Self->ShowcaseName
                ),
                &Value
            );
            Future->EnsureCompletion();
        }
        *Result = Value;

        return nullptr;
    }

    TSharedPtr<FAsyncTask<FShowcaseMasterDomain::FModelTask>> FShowcaseMasterDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FShowcaseMasterDomain::FModelTask>>(this->AsShared());
    }
}

#if defined(_MSC_VER)
#pragma warning (pop)
#elif defined(__clang__)
#pragma clang diagnostic pop
#endif

