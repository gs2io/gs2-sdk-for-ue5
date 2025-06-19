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

#include "StateMachine/Domain/Model/StateMachineMaster.h"
#include "StateMachine/Domain/Model/Namespace.h"
#include "StateMachine/Domain/Model/StateMachineMaster.h"
#include "StateMachine/Domain/Model/Status.h"
#include "StateMachine/Domain/Model/StatusAccessToken.h"
#include "StateMachine/Domain/Model/User.h"
#include "StateMachine/Domain/Model/UserAccessToken.h"

#include "Core/Domain/Gs2.h"
#include "Core/Domain/Transaction/JobQueueJobDomainFactory.h"
#include "Core/Domain/Transaction/InternalTransactionDomainFactory.h"
#include "Core/Domain/Transaction/ManualTransactionDomain.h"

namespace Gs2::StateMachine::Domain::Model
{

    FStateMachineMasterDomain::FStateMachineMasterDomain(
        const Core::Domain::FGs2Ptr& Gs2,
        const StateMachine::Domain::FGs2StateMachineDomainPtr& Service,
        const TOptional<FString> NamespaceName,
        const TOptional<int64> Version
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Gs2(Gs2),
        Service(Service),
        Client(MakeShared<Gs2::StateMachine::FGs2StateMachineRestClient>(Gs2->RestSession)),
        NamespaceName(NamespaceName),
        Version(Version),
        ParentKey(Gs2::StateMachine::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
            NamespaceName,
            "StateMachineMaster"
        ))
    {
    }

    FStateMachineMasterDomain::FStateMachineMasterDomain(
        const FStateMachineMasterDomain& From
    ):
        Gs2(From.Gs2),
        Service(From.Service),
        Client(From.Client),
        NamespaceName(From.NamespaceName),
        Version(From.Version),
        ParentKey(From.ParentKey)
    {

    }

    FStateMachineMasterDomain::FGetTask::FGetTask(
        const TSharedPtr<FStateMachineMasterDomain>& Self,
        const Request::FGetStateMachineMasterRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FStateMachineMasterDomain::FGetTask::FGetTask(
        const FGetTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FStateMachineMasterDomain::FGetTask::Action(
        TSharedPtr<TSharedPtr<Gs2::StateMachine::Model::FStateMachineMaster>> Result
    )
    {
        Request
            ->WithContextStack(Self->Gs2->DefaultContextStack)
            ->WithNamespaceName(Self->NamespaceName)
            ->WithVersion(Self->Version);
        const auto Future = Self->Client->GetStateMachineMaster(
            Request
        );
        Future->StartSynchronousTask();
        if (Future->GetTask().IsError())
        {
            return Future->GetTask().Error();
        }
        const auto ResultModel = Future->GetTask().Result();
        Future->EnsureCompletion();
        *Result = ResultModel->GetItem();
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FStateMachineMasterDomain::FGetTask>> FStateMachineMasterDomain::Get(
        Request::FGetStateMachineMasterRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FGetTask>>(this->AsShared(), Request);
    }

    FStateMachineMasterDomain::FDeleteTask::FDeleteTask(
        const TSharedPtr<FStateMachineMasterDomain>& Self,
        const Request::FDeleteStateMachineMasterRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FStateMachineMasterDomain::FDeleteTask::FDeleteTask(
        const FDeleteTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FStateMachineMasterDomain::FDeleteTask::Action(
        TSharedPtr<TSharedPtr<Gs2::StateMachine::Domain::Model::FStateMachineMasterDomain>> Result
    )
    {
        Request
            ->WithContextStack(Self->Gs2->DefaultContextStack)
            ->WithNamespaceName(Self->NamespaceName)
            ->WithVersion(Self->Version);
        const auto Future = Self->Client->DeleteStateMachineMaster(
            Request
        );
        Future->StartSynchronousTask();
        if (Future->GetTask().IsError())
        {
            return Future->GetTask().Error();
        }
        const auto ResultModel = Future->GetTask().Result();
        Future->EnsureCompletion();
        auto Domain = Self;

        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FStateMachineMasterDomain::FDeleteTask>> FStateMachineMasterDomain::Delete(
        Request::FDeleteStateMachineMasterRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FDeleteTask>>(this->AsShared(), Request);
    }

    FString FStateMachineMasterDomain::CreateCacheParentKey(
        TOptional<FString> NamespaceName,
        TOptional<int64> Version,
        FString ChildType
    )
    {
        return FString("") +
            (NamespaceName.IsSet() ? *NamespaceName : "null") + ":" +
            (Version.IsSet() ? FString::FromInt(*Version) : "null") + ":" +
            ChildType;
    }

    FString FStateMachineMasterDomain::CreateCacheKey(
        TOptional<int64> Version
    )
    {
        return FString("") +
            (Version.IsSet() ? FString::FromInt(*Version) : "null");
    }

    FStateMachineMasterDomain::FModelTask::FModelTask(
        const TSharedPtr<FStateMachineMasterDomain> Self
    ): Self(Self)
    {

    }

    FStateMachineMasterDomain::FModelTask::FModelTask(
        const FModelTask& From
    ): TGs2Future(From), Self(From.Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FStateMachineMasterDomain::FModelTask::Action(
        TSharedPtr<TSharedPtr<Gs2::StateMachine::Model::FStateMachineMaster>> Result
    )
    {
        // ReSharper disable once CppLocalVariableMayBeConst
        TSharedPtr<Gs2::StateMachine::Model::FStateMachineMaster> Value;
        auto bCacheHit = Self->Gs2->Cache->TryGet<Gs2::StateMachine::Model::FStateMachineMaster>(
            Self->ParentKey,
            Gs2::StateMachine::Domain::Model::FStateMachineMasterDomain::CreateCacheKey(
                Self->Version
            ),
            &Value
        );
        if (!bCacheHit) {
            const auto Future = Self->Get(
                MakeShared<Gs2::StateMachine::Request::FGetStateMachineMasterRequest>()
            );
            Future->StartSynchronousTask();
            if (Future->GetTask().IsError())
            {
                if (Future->GetTask().Error()->Type() != Gs2::Core::Model::FNotFoundError::TypeString)
                {
                    return Future->GetTask().Error();
                }

                const auto Key = Gs2::StateMachine::Domain::Model::FStateMachineMasterDomain::CreateCacheKey(
                    Self->Version
                );
                Self->Gs2->Cache->Put(
                    Gs2::StateMachine::Model::FStateMachineMaster::TypeName,
                    Self->ParentKey,
                    Key,
                    nullptr,
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );

                if (Future->GetTask().Error()->Detail(0)->GetComponent() != "stateMachineMaster")
                {
                    return Future->GetTask().Error();
                }
            }
            Self->Gs2->Cache->TryGet<Gs2::StateMachine::Model::FStateMachineMaster>(
                Self->ParentKey,
                Gs2::StateMachine::Domain::Model::FStateMachineMasterDomain::CreateCacheKey(
                    Self->Version
                ),
                &Value
            );
            Future->EnsureCompletion();
        }
        *Result = Value;

        return nullptr;
    }

    TSharedPtr<FAsyncTask<FStateMachineMasterDomain::FModelTask>> FStateMachineMasterDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FStateMachineMasterDomain::FModelTask>>(this->AsShared());
    }

    Gs2::Core::Domain::CallbackID FStateMachineMasterDomain::Subscribe(
        TFunction<void(Gs2::StateMachine::Model::FStateMachineMasterPtr)> Callback
    )
    {
        return Gs2->Cache->Subscribe(
            Gs2::StateMachine::Model::FStateMachineMaster::TypeName,
            ParentKey,
            Gs2::StateMachine::Domain::Model::FStateMachineMasterDomain::CreateCacheKey(
                Version
            ),
            [Callback](TSharedPtr<FGs2Object> obj)
            {
                Callback(StaticCastSharedPtr<Gs2::StateMachine::Model::FStateMachineMaster>(obj));
            }
        );
    }

    void FStateMachineMasterDomain::Unsubscribe(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        Gs2->Cache->Unsubscribe(
            Gs2::StateMachine::Model::FStateMachineMaster::TypeName,
            ParentKey,
            Gs2::StateMachine::Domain::Model::FStateMachineMasterDomain::CreateCacheKey(
                Version
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

