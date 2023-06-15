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

#include "Inbox/Domain/Model/GlobalMessageMaster.h"
#include "Inbox/Domain/Model/Namespace.h"
#include "Inbox/Domain/Model/User.h"
#include "Inbox/Domain/Model/UserAccessToken.h"
#include "Inbox/Domain/Model/Message.h"
#include "Inbox/Domain/Model/MessageAccessToken.h"
#include "Inbox/Domain/Model/CurrentMessageMaster.h"
#include "Inbox/Domain/Model/GlobalMessageMaster.h"
#include "Inbox/Domain/Model/GlobalMessage.h"
#include "Inbox/Domain/Model/Received.h"
#include "Inbox/Domain/Model/ReceivedAccessToken.h"

#include "Core/Domain/Model/AutoStampSheetDomain.h"
#include "Core/Domain/Model/StampSheetDomain.h"

namespace Gs2::Inbox::Domain::Model
{

    FGlobalMessageMasterDomain::FGlobalMessageMasterDomain(
        const Core::Domain::FCacheDatabasePtr Cache,
        const Gs2::Core::Domain::Model::FJobQueueDomainPtr JobQueueDomain,
        const Gs2::Core::Domain::Model::FStampSheetConfigurationPtr StampSheetConfiguration,
        const Gs2::Core::Net::Rest::FGs2RestSessionPtr Session,
        const TOptional<FString> NamespaceName,
        const TOptional<FString> GlobalMessageName
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Cache(Cache),
        JobQueueDomain(JobQueueDomain),
        StampSheetConfiguration(StampSheetConfiguration),
        Session(Session),
        Client(MakeShared<Gs2::Inbox::FGs2InboxRestClient>(Session)),
        NamespaceName(NamespaceName),
        GlobalMessageName(GlobalMessageName),
        ParentKey(Gs2::Inbox::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
            NamespaceName,
            "GlobalMessageMaster"
        ))
    {
    }

    FGlobalMessageMasterDomain::FGlobalMessageMasterDomain(
        const FGlobalMessageMasterDomain& From
    ):
        Cache(From.Cache),
        JobQueueDomain(From.JobQueueDomain),
        StampSheetConfiguration(From.StampSheetConfiguration),
        Session(From.Session),
        Client(From.Client)
    {

    }

    FGlobalMessageMasterDomain::FGetTask::FGetTask(
        const TSharedPtr<FGlobalMessageMasterDomain> Self,
        const Request::FGetGlobalMessageMasterRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FGlobalMessageMasterDomain::FGetTask::FGetTask(
        const FGetTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FGlobalMessageMasterDomain::FGetTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Inbox::Model::FGlobalMessageMaster>> Result
    )
    {
        Request
            ->WithNamespaceName(Self->NamespaceName)
            ->WithGlobalMessageName(Self->GlobalMessageName);
        const auto Future = Self->Client->GetGlobalMessageMaster(
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
                const auto ParentKey = Gs2::Inbox::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
                    Self->NamespaceName,
                    "GlobalMessageMaster"
                );
                const auto Key = Gs2::Inbox::Domain::Model::FGlobalMessageMasterDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetName()
                );
                Self->Cache->Put(
                    Gs2::Inbox::Model::FGlobalMessageMaster::TypeName,
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

    TSharedPtr<FAsyncTask<FGlobalMessageMasterDomain::FGetTask>> FGlobalMessageMasterDomain::Get(
        Request::FGetGlobalMessageMasterRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FGetTask>>(this->AsShared(), Request);
    }

    FGlobalMessageMasterDomain::FUpdateTask::FUpdateTask(
        const TSharedPtr<FGlobalMessageMasterDomain> Self,
        const Request::FUpdateGlobalMessageMasterRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FGlobalMessageMasterDomain::FUpdateTask::FUpdateTask(
        const FUpdateTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FGlobalMessageMasterDomain::FUpdateTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Inbox::Domain::Model::FGlobalMessageMasterDomain>> Result
    )
    {
        Request
            ->WithNamespaceName(Self->NamespaceName)
            ->WithGlobalMessageName(Self->GlobalMessageName);
        const auto Future = Self->Client->UpdateGlobalMessageMaster(
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
                const auto ParentKey = Gs2::Inbox::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
                    Self->NamespaceName,
                    "GlobalMessageMaster"
                );
                const auto Key = Gs2::Inbox::Domain::Model::FGlobalMessageMasterDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetName()
                );
                Self->Cache->Put(
                    Gs2::Inbox::Model::FGlobalMessageMaster::TypeName,
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

    TSharedPtr<FAsyncTask<FGlobalMessageMasterDomain::FUpdateTask>> FGlobalMessageMasterDomain::Update(
        Request::FUpdateGlobalMessageMasterRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FUpdateTask>>(this->AsShared(), Request);
    }

    FGlobalMessageMasterDomain::FDeleteTask::FDeleteTask(
        const TSharedPtr<FGlobalMessageMasterDomain> Self,
        const Request::FDeleteGlobalMessageMasterRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FGlobalMessageMasterDomain::FDeleteTask::FDeleteTask(
        const FDeleteTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FGlobalMessageMasterDomain::FDeleteTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Inbox::Domain::Model::FGlobalMessageMasterDomain>> Result
    )
    {
        Request
            ->WithNamespaceName(Self->NamespaceName)
            ->WithGlobalMessageName(Self->GlobalMessageName);
        const auto Future = Self->Client->DeleteGlobalMessageMaster(
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
                const auto ParentKey = Gs2::Inbox::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
                    Self->NamespaceName,
                    "GlobalMessageMaster"
                );
                const auto Key = Gs2::Inbox::Domain::Model::FGlobalMessageMasterDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetName()
                );
                Self->Cache->Delete(Gs2::Inbox::Model::FGlobalMessageMaster::TypeName, ParentKey, Key);
            }
        }
        auto Domain = Self;

        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FGlobalMessageMasterDomain::FDeleteTask>> FGlobalMessageMasterDomain::Delete(
        Request::FDeleteGlobalMessageMasterRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FDeleteTask>>(this->AsShared(), Request);
    }

    FString FGlobalMessageMasterDomain::CreateCacheParentKey(
        TOptional<FString> NamespaceName,
        TOptional<FString> GlobalMessageName,
        FString ChildType
    )
    {
        return FString() +
            (NamespaceName.IsSet() ? *NamespaceName : "null") + ":" +
            (GlobalMessageName.IsSet() ? *GlobalMessageName : "null") + ":" +
            ChildType;
    }

    FString FGlobalMessageMasterDomain::CreateCacheKey(
        TOptional<FString> GlobalMessageName
    )
    {
        return FString() +
            (GlobalMessageName.IsSet() ? *GlobalMessageName : "null");
    }

    FGlobalMessageMasterDomain::FModelTask::FModelTask(
        const TSharedPtr<FGlobalMessageMasterDomain> Self
    ): Self(Self)
    {

    }

    FGlobalMessageMasterDomain::FModelTask::FModelTask(
        const FModelTask& From
    ): TGs2Future(From), Self(From.Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FGlobalMessageMasterDomain::FModelTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Inbox::Model::FGlobalMessageMaster>> Result
    )
    {
        // ReSharper disable once CppLocalVariableMayBeConst
        TSharedPtr<Gs2::Inbox::Model::FGlobalMessageMaster> Value;
        auto bCacheHit = Self->Cache->TryGet<Gs2::Inbox::Model::FGlobalMessageMaster>(
            Self->ParentKey,
            Gs2::Inbox::Domain::Model::FGlobalMessageMasterDomain::CreateCacheKey(
                Self->GlobalMessageName
            ),
            &Value
        );
        if (!bCacheHit) {
            const auto Future = Self->Get(
                MakeShared<Gs2::Inbox::Request::FGetGlobalMessageMasterRequest>()
            );
            Future->StartSynchronousTask();
            if (Future->GetTask().IsError())
            {
                if (Future->GetTask().Error()->Type() != Gs2::Core::Model::FNotFoundError::TypeString)
                {
                    return Future->GetTask().Error();
                }

                const auto Key = Gs2::Inbox::Domain::Model::FGlobalMessageMasterDomain::CreateCacheKey(
                    Self->GlobalMessageName
                );
                Self->Cache->Put(
                    Gs2::Inbox::Model::FGlobalMessageMaster::TypeName,
                    Self->ParentKey,
                    Key,
                    nullptr,
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );

                if (Future->GetTask().Error()->Detail(0)->GetComponent() != "globalMessageMaster")
                {
                    return Future->GetTask().Error();
                }
            }
            Self->Cache->TryGet<Gs2::Inbox::Model::FGlobalMessageMaster>(
                Self->ParentKey,
                Gs2::Inbox::Domain::Model::FGlobalMessageMasterDomain::CreateCacheKey(
                    Self->GlobalMessageName
                ),
                &Value
            );
            Future->EnsureCompletion();
        }
        *Result = Value;

        return nullptr;
    }

    TSharedPtr<FAsyncTask<FGlobalMessageMasterDomain::FModelTask>> FGlobalMessageMasterDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FGlobalMessageMasterDomain::FModelTask>>(this->AsShared());
    }
}

#if defined(_MSC_VER)
#pragma warning (pop)
#elif defined(__clang__)
#pragma clang diagnostic pop
#endif

