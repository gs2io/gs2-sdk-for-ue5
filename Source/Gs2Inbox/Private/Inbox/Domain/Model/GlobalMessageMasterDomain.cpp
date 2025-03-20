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

#include "Core/Domain/Gs2.h"
#include "Core/Domain/Transaction/JobQueueJobDomainFactory.h"
#include "Core/Domain/Transaction/InternalTransactionDomainFactory.h"
#include "Core/Domain/Transaction/ManualTransactionDomain.h"

namespace Gs2::Inbox::Domain::Model
{

    FGlobalMessageMasterDomain::FGlobalMessageMasterDomain(
        const Core::Domain::FGs2Ptr& Gs2,
        const Inbox::Domain::FGs2InboxDomainPtr& Service,
        const TOptional<FString> NamespaceName,
        const TOptional<FString> GlobalMessageName
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Gs2(Gs2),
        Service(Service),
        Client(MakeShared<Gs2::Inbox::FGs2InboxRestClient>(Gs2->RestSession)),
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
        Gs2(From.Gs2),
        Service(From.Service),
        Client(From.Client),
        NamespaceName(From.NamespaceName),
        GlobalMessageName(From.GlobalMessageName),
        ParentKey(From.ParentKey)
    {

    }

    FGlobalMessageMasterDomain::FGetTask::FGetTask(
        const TSharedPtr<FGlobalMessageMasterDomain>& Self,
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
            ->WithContextStack(Self->Gs2->DefaultContextStack)
            ->WithNamespaceName(Self->NamespaceName)
            ->WithGlobalMessageName(Self->GlobalMessageName);
        *Result = ResultModel->GetItem();
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FGlobalMessageMasterDomain::FGetTask>> FGlobalMessageMasterDomain::Get(
        Request::FGetGlobalMessageMasterRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FGetTask>>(this->AsShared(), Request);
    }

    FGlobalMessageMasterDomain::FUpdateTask::FUpdateTask(
        const TSharedPtr<FGlobalMessageMasterDomain>& Self,
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
            ->WithContextStack(Self->Gs2->DefaultContextStack)
            ->WithNamespaceName(Self->NamespaceName)
            ->WithGlobalMessageName(Self->GlobalMessageName);
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
        const TSharedPtr<FGlobalMessageMasterDomain>& Self,
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
            ->WithContextStack(Self->Gs2->DefaultContextStack)
            ->WithNamespaceName(Self->NamespaceName)
            ->WithGlobalMessageName(Self->GlobalMessageName);
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
        return FString("") +
            (NamespaceName.IsSet() ? *NamespaceName : "null") + ":" +
            (GlobalMessageName.IsSet() ? *GlobalMessageName : "null") + ":" +
            ChildType;
    }

    FString FGlobalMessageMasterDomain::CreateCacheKey(
        TOptional<FString> GlobalMessageName
    )
    {
        return FString("") +
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
        auto bCacheHit = Self->Gs2->Cache->TryGet<Gs2::Inbox::Model::FGlobalMessageMaster>(
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
                Self->Gs2->Cache->Put(
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
            Self->Gs2->Cache->TryGet<Gs2::Inbox::Model::FGlobalMessageMaster>(
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

    Gs2::Core::Domain::CallbackID FGlobalMessageMasterDomain::Subscribe(
        TFunction<void(Gs2::Inbox::Model::FGlobalMessageMasterPtr)> Callback
    )
    {
        return Gs2->Cache->Subscribe(
            Gs2::Inbox::Model::FGlobalMessageMaster::TypeName,
            ParentKey,
            Gs2::Inbox::Domain::Model::FGlobalMessageMasterDomain::CreateCacheKey(
                GlobalMessageName
            ),
            [Callback](TSharedPtr<FGs2Object> obj)
            {
                Callback(StaticCastSharedPtr<Gs2::Inbox::Model::FGlobalMessageMaster>(obj));
            }
        );
    }

    void FGlobalMessageMasterDomain::Unsubscribe(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        Gs2->Cache->Unsubscribe(
            Gs2::Inbox::Model::FGlobalMessageMaster::TypeName,
            ParentKey,
            Gs2::Inbox::Domain::Model::FGlobalMessageMasterDomain::CreateCacheKey(
                GlobalMessageName
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

