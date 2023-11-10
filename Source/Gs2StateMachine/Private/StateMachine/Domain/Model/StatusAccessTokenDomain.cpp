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

#include "StateMachine/Domain/Model/StatusAccessToken.h"
#include "StateMachine/Domain/Model/Status.h"
#include "StateMachine/Domain/Model/Namespace.h"
#include "StateMachine/Domain/Model/StateMachineMaster.h"
#include "StateMachine/Domain/Model/Status.h"
#include "StateMachine/Domain/Model/StatusAccessToken.h"
#include "StateMachine/Domain/Model/User.h"
#include "StateMachine/Domain/Model/UserAccessToken.h"

#include "Core/Domain/Gs2.h"
#include "Core/Domain/Model/AutoStampSheetDomain.h"
#include "Core/Domain/Model/StampSheetDomain.h"

namespace Gs2::StateMachine::Domain::Model
{

    FStatusAccessTokenDomain::FStatusAccessTokenDomain(
        const Core::Domain::FGs2Ptr& Gs2,
        const StateMachine::Domain::FGs2StateMachineDomainPtr& Service,
        const TOptional<FString> NamespaceName,
        const Gs2::Auth::Model::FAccessTokenPtr& AccessToken,
        const TOptional<FString> StatusName
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Gs2(Gs2),
        Service(Service),
        Client(MakeShared<Gs2::StateMachine::FGs2StateMachineRestClient>(Gs2->RestSession)),
        NamespaceName(NamespaceName),
        AccessToken(AccessToken),
        StatusName(StatusName),
        ParentKey(Gs2::StateMachine::Domain::Model::FUserDomain::CreateCacheParentKey(
            NamespaceName,
            UserId(),
            "Status"
        ))
    {
    }

    FStatusAccessTokenDomain::FStatusAccessTokenDomain(
        const FStatusAccessTokenDomain& From
    ):
        Gs2(From.Gs2),
        Service(From.Service),
        Client(From.Client),
        NamespaceName(From.NamespaceName),
        AccessToken(From.AccessToken),
        StatusName(From.StatusName),
        ParentKey(From.ParentKey)
    {

    }

    FStatusAccessTokenDomain::FGetTask::FGetTask(
        const TSharedPtr<FStatusAccessTokenDomain>& Self,
        const Request::FGetStatusRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FStatusAccessTokenDomain::FGetTask::FGetTask(
        const FGetTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FStatusAccessTokenDomain::FGetTask::Action(
        TSharedPtr<TSharedPtr<Gs2::StateMachine::Model::FStatus>> Result
    )
    {
        Request
            ->WithNamespaceName(Self->NamespaceName)
            ->WithAccessToken(Self->AccessToken->GetToken())
            ->WithStatusName(Self->StatusName);
        const auto Future = Self->Client->GetStatus(
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
                const auto ParentKey = Gs2::StateMachine::Domain::Model::FUserDomain::CreateCacheParentKey(
                    Self->NamespaceName,
                    Self->UserId(),
                    "Status"
                );
                const auto Key = Gs2::StateMachine::Domain::Model::FStatusDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetName()
                );
                Self->Gs2->Cache->Put(
                    Gs2::StateMachine::Model::FStatus::TypeName,
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

    TSharedPtr<FAsyncTask<FStatusAccessTokenDomain::FGetTask>> FStatusAccessTokenDomain::Get(
        Request::FGetStatusRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FGetTask>>(this->AsShared(), Request);
    }

    FStatusAccessTokenDomain::FEmitTask::FEmitTask(
        const TSharedPtr<FStatusAccessTokenDomain>& Self,
        const Request::FEmitRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FStatusAccessTokenDomain::FEmitTask::FEmitTask(
        const FEmitTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FStatusAccessTokenDomain::FEmitTask::Action(
        TSharedPtr<TSharedPtr<Gs2::StateMachine::Domain::Model::FStatusAccessTokenDomain>> Result
    )
    {
        Request
            ->WithNamespaceName(Self->NamespaceName)
            ->WithAccessToken(Self->AccessToken->GetToken())
            ->WithStatusName(Self->StatusName);
        const auto Future = Self->Client->Emit(
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
                const auto ParentKey = Gs2::StateMachine::Domain::Model::FUserDomain::CreateCacheParentKey(
                    Self->NamespaceName,
                    Self->UserId(),
                    "Status"
                );
                const auto Key = Gs2::StateMachine::Domain::Model::FStatusDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetName()
                );
                Self->Gs2->Cache->Put(
                    Gs2::StateMachine::Model::FStatus::TypeName,
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

    TSharedPtr<FAsyncTask<FStatusAccessTokenDomain::FEmitTask>> FStatusAccessTokenDomain::Emit(
        Request::FEmitRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FEmitTask>>(this->AsShared(), Request);
    }

    FStatusAccessTokenDomain::FExitStateMachineTask::FExitStateMachineTask(
        const TSharedPtr<FStatusAccessTokenDomain>& Self,
        const Request::FExitStateMachineRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FStatusAccessTokenDomain::FExitStateMachineTask::FExitStateMachineTask(
        const FExitStateMachineTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FStatusAccessTokenDomain::FExitStateMachineTask::Action(
        TSharedPtr<TSharedPtr<Gs2::StateMachine::Domain::Model::FStatusAccessTokenDomain>> Result
    )
    {
        Request
            ->WithNamespaceName(Self->NamespaceName)
            ->WithAccessToken(Self->AccessToken->GetToken())
            ->WithStatusName(Self->StatusName);
        const auto Future = Self->Client->ExitStateMachine(
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
                const auto ParentKey = Gs2::StateMachine::Domain::Model::FUserDomain::CreateCacheParentKey(
                    Self->NamespaceName,
                    Self->UserId(),
                    "Status"
                );
                const auto Key = Gs2::StateMachine::Domain::Model::FStatusDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetName()
                );
                Self->Gs2->Cache->Delete(Gs2::StateMachine::Model::FStatus::TypeName, ParentKey, Key);
            }
        }
        auto Domain = Self;

        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FStatusAccessTokenDomain::FExitStateMachineTask>> FStatusAccessTokenDomain::ExitStateMachine(
        Request::FExitStateMachineRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FExitStateMachineTask>>(this->AsShared(), Request);
    }

    FString FStatusAccessTokenDomain::CreateCacheParentKey(
        TOptional<FString> NamespaceName,
        TOptional<FString> UserId,
        TOptional<FString> StatusName,
        FString ChildType
    )
    {
        return FString("") +
            (NamespaceName.IsSet() ? *NamespaceName : "null") + ":" +
            (UserId.IsSet() ? *UserId : "null") + ":" +
            (StatusName.IsSet() ? *StatusName : "null") + ":" +
            ChildType;
    }

    FString FStatusAccessTokenDomain::CreateCacheKey(
        TOptional<FString> StatusName
    )
    {
        return FString("") +
            (StatusName.IsSet() ? *StatusName : "null");
    }

    FStatusAccessTokenDomain::FModelTask::FModelTask(
        const TSharedPtr<FStatusAccessTokenDomain> Self
    ): Self(Self)
    {

    }

    FStatusAccessTokenDomain::FModelTask::FModelTask(
        const FModelTask& From
    ): TGs2Future(From), Self(From.Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FStatusAccessTokenDomain::FModelTask::Action(
        TSharedPtr<TSharedPtr<Gs2::StateMachine::Model::FStatus>> Result
    )
    {
        // ReSharper disable once CppLocalVariableMayBeConst
        TSharedPtr<Gs2::StateMachine::Model::FStatus> Value;
        auto bCacheHit = Self->Gs2->Cache->TryGet<Gs2::StateMachine::Model::FStatus>(
            Self->ParentKey,
            Gs2::StateMachine::Domain::Model::FStatusDomain::CreateCacheKey(
                Self->StatusName
            ),
            &Value
        );
        if (!bCacheHit) {
            const auto Future = Self->Get(
                MakeShared<Gs2::StateMachine::Request::FGetStatusRequest>()
            );
            Future->StartSynchronousTask();
            if (Future->GetTask().IsError())
            {
                if (Future->GetTask().Error()->Type() != Gs2::Core::Model::FNotFoundError::TypeString)
                {
                    return Future->GetTask().Error();
                }

                const auto Key = Gs2::StateMachine::Domain::Model::FStatusDomain::CreateCacheKey(
                    Self->StatusName
                );
                Self->Gs2->Cache->Put(
                    Gs2::StateMachine::Model::FStatus::TypeName,
                    Self->ParentKey,
                    Key,
                    nullptr,
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );

                if (Future->GetTask().Error()->Detail(0)->GetComponent() != "status")
                {
                    return Future->GetTask().Error();
                }
            }
            Self->Gs2->Cache->TryGet<Gs2::StateMachine::Model::FStatus>(
                Self->ParentKey,
                Gs2::StateMachine::Domain::Model::FStatusDomain::CreateCacheKey(
                    Self->StatusName
                ),
                &Value
            );
            Future->EnsureCompletion();
        }
        *Result = Value;

        return nullptr;
    }

    TSharedPtr<FAsyncTask<FStatusAccessTokenDomain::FModelTask>> FStatusAccessTokenDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FStatusAccessTokenDomain::FModelTask>>(this->AsShared());
    }

    Gs2::Core::Domain::CallbackID FStatusAccessTokenDomain::Subscribe(
        TFunction<void(Gs2::StateMachine::Model::FStatusPtr)> Callback
    )
    {
        return Gs2->Cache->Subscribe(
            Gs2::StateMachine::Model::FStatus::TypeName,
            ParentKey,
            Gs2::StateMachine::Domain::Model::FStatusDomain::CreateCacheKey(
                StatusName
            ),
            [Callback](TSharedPtr<Gs2Object> obj)
            {
                Callback(StaticCastSharedPtr<Gs2::StateMachine::Model::FStatus>(obj));
            }
        );
    }

    void FStatusAccessTokenDomain::Unsubscribe(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        Gs2->Cache->Unsubscribe(
            Gs2::StateMachine::Model::FStatus::TypeName,
            ParentKey,
            Gs2::StateMachine::Domain::Model::FStatusDomain::CreateCacheKey(
                StatusName
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

