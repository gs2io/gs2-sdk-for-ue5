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

#include "Schedule/Domain/Model/Trigger.h"
#include "Schedule/Domain/Model/Namespace.h"
#include "Schedule/Domain/Model/EventMaster.h"
#include "Schedule/Domain/Model/Trigger.h"
#include "Schedule/Domain/Model/TriggerAccessToken.h"
#include "Schedule/Domain/Model/Event.h"
#include "Schedule/Domain/Model/EventAccessToken.h"
#include "Schedule/Domain/Model/User.h"
#include "Schedule/Domain/Model/UserAccessToken.h"
#include "Schedule/Domain/Model/CurrentEventMaster.h"

#include "Core/Domain/Gs2.h"
#include "Core/Domain/Transaction/JobQueueJobDomainFactory.h"
#include "Core/Domain/Transaction/InternalTransactionDomainFactory.h"
#include "Core/Domain/Transaction/ManualTransactionDomain.h"

namespace Gs2::Schedule::Domain::Model
{

    FTriggerDomain::FTriggerDomain(
        const Core::Domain::FGs2Ptr& Gs2,
        const Schedule::Domain::FGs2ScheduleDomainPtr& Service,
        const TOptional<FString> NamespaceName,
        const TOptional<FString> UserId,
        const TOptional<FString> TriggerName
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Gs2(Gs2),
        Service(Service),
        Client(MakeShared<Gs2::Schedule::FGs2ScheduleRestClient>(Gs2->RestSession)),
        NamespaceName(NamespaceName),
        UserId(UserId),
        TriggerName(TriggerName),
        ParentKey(Gs2::Schedule::Domain::Model::FUserDomain::CreateCacheParentKey(
            NamespaceName,
            UserId,
            "Trigger"
        ))
    {
    }

    FTriggerDomain::FTriggerDomain(
        const FTriggerDomain& From
    ):
        Gs2(From.Gs2),
        Service(From.Service),
        Client(From.Client),
        NamespaceName(From.NamespaceName),
        UserId(From.UserId),
        TriggerName(From.TriggerName),
        ParentKey(From.ParentKey)
    {

    }

    FTriggerDomain::FGetTask::FGetTask(
        const TSharedPtr<FTriggerDomain>& Self,
        const Request::FGetTriggerByUserIdRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FTriggerDomain::FGetTask::FGetTask(
        const FGetTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FTriggerDomain::FGetTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Schedule::Model::FTrigger>> Result
    )
    {
        Request
            ->WithContextStack(Self->Gs2->DefaultContextStack)
            ->WithNamespaceName(Self->NamespaceName)
            ->WithUserId(Self->UserId)
            ->WithTriggerName(Self->TriggerName);
        const auto Future = Self->Client->GetTriggerByUserId(
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

    TSharedPtr<FAsyncTask<FTriggerDomain::FGetTask>> FTriggerDomain::Get(
        Request::FGetTriggerByUserIdRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FGetTask>>(this->AsShared(), Request);
    }

    FTriggerDomain::FTriggerTask::FTriggerTask(
        const TSharedPtr<FTriggerDomain>& Self,
        const Request::FTriggerByUserIdRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FTriggerDomain::FTriggerTask::FTriggerTask(
        const FTriggerTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FTriggerDomain::FTriggerTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Schedule::Domain::Model::FTriggerDomain>> Result
    )
    {
        Request
            ->WithContextStack(Self->Gs2->DefaultContextStack)
            ->WithNamespaceName(Self->NamespaceName)
            ->WithTriggerName(Self->TriggerName)
            ->WithUserId(Self->UserId);
        const auto Future = Self->Client->TriggerByUserId(
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

    TSharedPtr<FAsyncTask<FTriggerDomain::FTriggerTask>> FTriggerDomain::Trigger(
        Request::FTriggerByUserIdRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FTriggerTask>>(this->AsShared(), Request);
    }

    FTriggerDomain::FExtendTask::FExtendTask(
        const TSharedPtr<FTriggerDomain>& Self,
        const Request::FExtendTriggerByUserIdRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FTriggerDomain::FExtendTask::FExtendTask(
        const FExtendTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FTriggerDomain::FExtendTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Schedule::Domain::Model::FTriggerDomain>> Result
    )
    {
        Request
            ->WithContextStack(Self->Gs2->DefaultContextStack)
            ->WithNamespaceName(Self->NamespaceName)
            ->WithTriggerName(Self->TriggerName)
            ->WithUserId(Self->UserId);
        const auto Future = Self->Client->ExtendTriggerByUserId(
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

    TSharedPtr<FAsyncTask<FTriggerDomain::FExtendTask>> FTriggerDomain::Extend(
        Request::FExtendTriggerByUserIdRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FExtendTask>>(this->AsShared(), Request);
    }

    FTriggerDomain::FDeleteTask::FDeleteTask(
        const TSharedPtr<FTriggerDomain>& Self,
        const Request::FDeleteTriggerByUserIdRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FTriggerDomain::FDeleteTask::FDeleteTask(
        const FDeleteTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FTriggerDomain::FDeleteTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Schedule::Domain::Model::FTriggerDomain>> Result
    )
    {
        Request
            ->WithContextStack(Self->Gs2->DefaultContextStack)
            ->WithNamespaceName(Self->NamespaceName)
            ->WithUserId(Self->UserId)
            ->WithTriggerName(Self->TriggerName);
        const auto Future = Self->Client->DeleteTriggerByUserId(
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

    TSharedPtr<FAsyncTask<FTriggerDomain::FDeleteTask>> FTriggerDomain::Delete(
        Request::FDeleteTriggerByUserIdRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FDeleteTask>>(this->AsShared(), Request);
    }

    FTriggerDomain::FVerifyTask::FVerifyTask(
        const TSharedPtr<FTriggerDomain>& Self,
        const Request::FVerifyTriggerByUserIdRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FTriggerDomain::FVerifyTask::FVerifyTask(
        const FVerifyTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FTriggerDomain::FVerifyTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Schedule::Domain::Model::FTriggerDomain>> Result
    )
    {
        Request
            ->WithContextStack(Self->Gs2->DefaultContextStack)
            ->WithNamespaceName(Self->NamespaceName)
            ->WithUserId(Self->UserId)
            ->WithTriggerName(Self->TriggerName);
        const auto Future = Self->Client->VerifyTriggerByUserId(
            Request
        );
        Future->StartSynchronousTask();
        if (Future->GetTask().IsError())
        {
            return Future->GetTask().Error();
        }
        const auto ResultModel = Future->GetTask().Result();
        Future->EnsureCompletion();
        const auto Domain = Self;
        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FTriggerDomain::FVerifyTask>> FTriggerDomain::Verify(
        Request::FVerifyTriggerByUserIdRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FVerifyTask>>(this->AsShared(), Request);
    }

    FString FTriggerDomain::CreateCacheParentKey(
        TOptional<FString> NamespaceName,
        TOptional<FString> UserId,
        TOptional<FString> TriggerName,
        FString ChildType
    )
    {
        return FString("") +
            (NamespaceName.IsSet() ? *NamespaceName : "null") + ":" +
            (UserId.IsSet() ? *UserId : "null") + ":" +
            (TriggerName.IsSet() ? *TriggerName : "null") + ":" +
            ChildType;
    }

    FString FTriggerDomain::CreateCacheKey(
        TOptional<FString> TriggerName
    )
    {
        return FString("") +
            (TriggerName.IsSet() ? *TriggerName : "null");
    }

    FTriggerDomain::FModelTask::FModelTask(
        const TSharedPtr<FTriggerDomain> Self
    ): Self(Self)
    {

    }

    FTriggerDomain::FModelTask::FModelTask(
        const FModelTask& From
    ): TGs2Future(From), Self(From.Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FTriggerDomain::FModelTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Schedule::Model::FTrigger>> Result
    )
    {
        // ReSharper disable once CppLocalVariableMayBeConst
        TSharedPtr<Gs2::Schedule::Model::FTrigger> Value;
        auto bCacheHit = Self->Gs2->Cache->TryGet<Gs2::Schedule::Model::FTrigger>(
            Self->ParentKey,
            Gs2::Schedule::Domain::Model::FTriggerDomain::CreateCacheKey(
                Self->TriggerName
            ),
            &Value
        );
        if (!bCacheHit) {
            const auto Future = Self->Get(
                MakeShared<Gs2::Schedule::Request::FGetTriggerByUserIdRequest>()
            );
            Future->StartSynchronousTask();
            if (Future->GetTask().IsError())
            {
                if (Future->GetTask().Error()->Type() != Gs2::Core::Model::FNotFoundError::TypeString)
                {
                    return Future->GetTask().Error();
                }

                const auto Key = Gs2::Schedule::Domain::Model::FTriggerDomain::CreateCacheKey(
                    Self->TriggerName
                );
                Self->Gs2->Cache->Put(
                    Gs2::Schedule::Model::FTrigger::TypeName,
                    Self->ParentKey,
                    Key,
                    nullptr,
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );

                if (Future->GetTask().Error()->Detail(0)->GetComponent() != "trigger")
                {
                    return Future->GetTask().Error();
                }
            }
            Self->Gs2->Cache->TryGet<Gs2::Schedule::Model::FTrigger>(
                Self->ParentKey,
                Gs2::Schedule::Domain::Model::FTriggerDomain::CreateCacheKey(
                    Self->TriggerName
                ),
                &Value
            );
            Future->EnsureCompletion();
        }
        *Result = Value;

        return nullptr;
    }

    TSharedPtr<FAsyncTask<FTriggerDomain::FModelTask>> FTriggerDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FTriggerDomain::FModelTask>>(this->AsShared());
    }

    Gs2::Core::Domain::CallbackID FTriggerDomain::Subscribe(
        TFunction<void(Gs2::Schedule::Model::FTriggerPtr)> Callback
    )
    {
        return Gs2->Cache->Subscribe(
            Gs2::Schedule::Model::FTrigger::TypeName,
            ParentKey,
            Gs2::Schedule::Domain::Model::FTriggerDomain::CreateCacheKey(
                TriggerName
            ),
            [Callback](TSharedPtr<FGs2Object> obj)
            {
                Callback(StaticCastSharedPtr<Gs2::Schedule::Model::FTrigger>(obj));
            }
        );
    }

    void FTriggerDomain::Unsubscribe(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        Gs2->Cache->Unsubscribe(
            Gs2::Schedule::Model::FTrigger::TypeName,
            ParentKey,
            Gs2::Schedule::Domain::Model::FTriggerDomain::CreateCacheKey(
                TriggerName
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

